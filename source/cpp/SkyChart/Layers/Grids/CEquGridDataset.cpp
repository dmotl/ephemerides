#include "CEquGridDataset.h"

#include "CDeclination.h"
#include "CRightAscension.h"
#include "SkyChartUtils.h"

static bool checkBoundingRects(int n, const CPointd* points, const QRectF& paint_rect)
{
	double x_min, x_max, y_min, y_max;
	x_min = x_max = points[0].x();
	y_min = y_max = points[0].y();
	for (int j = 1; j < n; j++) {
		if (points[j].x() > x_max)
			x_max = points[j].x();
		if (points[j].x() < x_min)
			x_min = points[j].x();
		if (points[j].y() > y_max)
			y_max = points[j].y();
		if (points[j].y() < y_min)
			y_min = points[j].y();
	}
	if (x_max < paint_rect.left() || y_max < paint_rect.top() || x_min > paint_rect.right() || y_min > paint_rect.bottom())
		return false;
	return true;
}

static bool checkDotProducts(int n, const CPointd* points)
{
	for (int j = 1; j < n - 1; j++) {
		for (int i = j + 1; i < n; i++) {
			if (CPointd::dotProduct(points[j] - points[0], points[i] - points[0]) < 0)
				return false;
		}
	}
	for (int j = 0; j < n - 1; j++) {
		for (int i = j + 1; i < n; i++) {
			if (CPointd::dotProduct(points[j] - points[i], points[j] - points[i]) > 1e9)
				return false;
		}
	}
	return true;
}

void CEquGridDataset::paint(QPainter& painter, const CMatrix3d& q,
	const CProjection& p, const CTransformd& m, const QRectF& paint_rect)
{
	if (m_dirty)
		updatePoints();

	painter.setPen(QPen(Qt::darkRed));
	painter.setBrush(QBrush());

	// Equatorial grid
	switch (m_style)
	{
	case tStyle::DOTS:
		for (const CVector3d& equ3d : m_dots) {
			CVector3d r3d = q * equ3d;
			p.project(r3d);
			if (r3d.z() >= 0) {
				CPointd xy = m.map(r3d.toPointF());
				painter.drawPoint(xy.x(), xy.y());
			}
		}
		break;

	case tStyle::LINES:
		for(const CCurve& curve : m_lines) {
			auto path = curve.toPath(q, p, m, paint_rect);
			if (path)
				painter.drawPath(*path);
		}
		break;
	}
}

std::optional<QPainterPath> CEquGridDataset::CCurve::toPath(const CMatrix3d& q, const CProjection& p, const CTransformd& m,
	const QRectF& paint_rect) const
{
	size_t size = m_pts.size();

	std::vector<CPointd> xy(size);
	std::vector<double> z(size);

	int i = 0;
	auto begin = m_pts.cbegin(), end = m_pts.cend();
	while (begin != end) {
		CVector3d r3d = q * (*begin);
		p.project(r3d);
		xy[i] = m.map(r3d.toPointF());
		z[i] = r3d.z();
		++begin;
		++i;
	}

	std::optional<QPainterPath> retval;
	for (int i = 1; i < size - 2; i += 3) {
		if (z[i - 1] >= 0 && z[i] >= 0 && z[i + 1] >= 0 && z[i + 2] >= 0 && checkBoundingRects(4, &xy[i - 1], paint_rect), checkDotProducts(4, &xy[i - 1])) {
			//qDebug() << xy[i - 1].x() << "; " << xy[i - 1].y() << " - " << xy[i].x() << "; " << xy[i].y() << " - " << xy[i + 1].x() << "; " << xy[i + 1].y() << 
			//	" - " << xy[i + 2].x() << "; " << xy[i + 2].y();
			if (!retval) {
				retval = QPainterPath(QPointF(xy[i - 1].x(), xy[i - 1].y()));
				retval->cubicTo(xy[i].x(), xy[i].y(), xy[i + 1].x(), xy[i + 1].y(), xy[i + 2].x(), xy[i + 2].y());
			}
			else {
				retval->moveTo(xy[i - 1].x(), xy[i - 1].y());
				retval->cubicTo(xy[i].x(), xy[i].y(), xy[i + 1].x(), xy[i + 1].y(), xy[i + 2].x(), xy[i + 2].y());
			}
		}
	}
	return retval;
}

void CEquGridDataset::updatePoints()
{
	m_dots.clear();
	m_lines.clear();
	
	switch (m_style)
	{
	case tStyle::DOTS:
	{
		// North pole
		m_dots.push_back(CVector3d(0, 0, 1));
		// South pole
		m_dots.push_back(CVector3d(0, 0, -1));
		// Other
		if (m_latitudeStep > 0 && m_longitudeStep > 0) {
			for (int i = -90 + m_latitudeStep; i < 90; i += m_latitudeStep) {
				double dec = DEG_TO_RAD(i);
				for (int j = 0; j < 360; j += m_longitudeStep) {
					double ra = DEG_TO_RAD(j);
					m_dots.push_back(CVector3d(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec)));
				}
			}
		}
		break;
	}

	case tStyle::LINES:
	{
		if (m_latitudeStep > 0) {
			// Latitude circles
			for (int i = -90 + m_latitudeStep; i < 90; i += m_latitudeStep) {
				double dec = DEG_TO_RAD(i);
				std::vector<CVector3d> pt_list;
				for (int j = 0; j <= 360; j += 15) {
					double ra = DEG_TO_RAD(j);
					pt_list.push_back(CVector3d(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec)));
				}
				std::vector<CVector3d> curve;
				CVector3d previous_pos = pt_list[0];
				for (int i = 1; i < pt_list.size(); i++) {
					CVector3d pts[4], current_pos = pt_list[i];
					assert(previous_pos != current_pos);
					Utils::cubic(pts, previous_pos, current_pos);
					if (i == 1)
						curve.push_back(pts[0]);
					curve.push_back(pts[1]);
					curve.push_back(pts[2]);
					curve.push_back(pts[3]);
					previous_pos = pt_list[i];
				}
				m_lines.push_back(curve);
			}
		}
		else {
			// Equator only
			std::vector<CVector3d> pt_list;
			for (int j = 0; j <= 360; j += 15) {
				double ra = DEG_TO_RAD(j);
				pt_list.push_back(CVector3d(cos(ra), sin(ra), 0));
			}
			std::vector<CVector3d> curve;
			CVector3d previous_pos = pt_list[0];
			for (int i = 1; i < pt_list.size(); i++) {
				CVector3d pts[4], current_pos = pt_list[i];
				assert(previous_pos != current_pos);
				Utils::cubic(pts, previous_pos, current_pos);
				if (i == 1)
					curve.push_back(pts[0]);
				curve.push_back(pts[1]);
				curve.push_back(pts[2]);
				curve.push_back(pts[3]);
				previous_pos = pt_list[i];
			}
			m_lines.push_back(curve);
		}
		// Longitude lines
		if (m_longitudeStep > 0) {
			for (int j = 0; j < 360; j += m_longitudeStep) {
				double ra = DEG_TO_RAD(j);
				std::vector<CVector3d> pt_list;
				for (int i = -90; i <= 90; i += 30) {
					double dec = DEG_TO_RAD(i);
					pt_list.push_back(CVector3d(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec)));
				}
				std::vector<CVector3d> curve;
				CVector3d previous_pos = pt_list[0];
				for (int i = 1; i < pt_list.size(); i++) {
					CVector3d pts[4], current_pos = pt_list[i];
					assert(previous_pos != current_pos);
					Utils::cubic(pts, previous_pos, current_pos);
					if (i == 1)
						curve.push_back(pts[0]);
					curve.push_back(pts[1]);
					curve.push_back(pts[2]);
					curve.push_back(pts[3]);
					previous_pos = pt_list[i];
				}
				m_lines.push_back(curve);
			}
		}
		else {
			// Prime meridian only
			std::vector<CVector3d> pt_list;
			for (int i = -90; i <= 90; i += 30) {
				double dec = DEG_TO_RAD(i);
				pt_list.push_back(CVector3d(cos(dec), 0, sin(dec)));
			}
			std::vector<CVector3d> curve;
			CVector3d previous_pos = pt_list[0];
			for (int i = 1; i < pt_list.size(); i++) {
				CVector3d pts[4], current_pos = pt_list[i];
				assert(previous_pos != current_pos);
				Utils::cubic(pts, previous_pos, current_pos);
				if (i == 1)
					curve.push_back(pts[0]);
				curve.push_back(pts[1]);
				curve.push_back(pts[2]);
				curve.push_back(pts[3]);
				previous_pos = pt_list[i];
			}
			m_lines.push_back(curve);
		}
		break;
	}
	}

	m_dirty = false;
}