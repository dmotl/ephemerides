/*!
*  \file      CConstLinesDataset.cpp
*  \author    David Motl
*  \date      2022-06-10
*
*  \copyright
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions
*      and the following disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list
*      of conditions and the following disclaimer in the documentation and/or other materials provided
*      with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of its contributors may be used
*      to endorse or promote products derived from this software without specific prior written
*      permission.
*/
#include "CConstLinesDataset.h"

#include "CLines.h"

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

CConstLinesDataset::CConstLinesDataset(const CLines* file, QObject* parent) : CSkyChartDataset(parent)
{
	tConstellation cons_last = tConstellation::EndOfConstellations;
	CVector3d previous_pos;
	QList<QPair<CVector3d, CVector3d>> pairs;
	
	if (file) {
		auto begin = file->data().begin(), end = file->data().end();
		while (begin != end) {
			pairs.append(qMakePair(begin->startJ2000().toXYZ(), begin->end2000().toXYZ()));
			++begin;
		}

		if (!pairs.empty()) {
			QVector<bool> processed(pairs.length());
			QList<CVector3d> pt_list;
			int first_i = processed.indexOf(false);
			while (first_i >= 0) {
				auto current_pair = pairs[first_i];
				pt_list << current_pair.first << current_pair.second;
				processed[first_i] = true;
				int next_i;
				do {
					next_i = -1;
					for (int j = 0; j < pairs.length(); j++) {
						if (!processed[j] && (pairs[j].first != current_pair.second || pairs[j].second != current_pair.first) && (pairs[j].first == current_pair.second || pairs[j].second == current_pair.second)) {
							next_i = j;
							break;
						}
					}
					if (next_i >= 0) {
						if (pairs[next_i].first == current_pair.second) {
							current_pair.second = pairs[next_i].second;
							current_pair.first = pairs[next_i].first;
						}
						else {
							current_pair.second = pairs[next_i].first;
							current_pair.first = pairs[next_i].second;
						}
						pt_list << current_pair.second;
						processed[next_i] = true;
					}
				} while (next_i >= 0);
				if (pt_list.size() >= 2) {
					std::vector<CVector3d> curve;
					CVector3d previous_pos = pt_list.first();
					for (int i = 1; i < pt_list.length(); i++) {
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
					m_data.push_back(curve);
				}
				pt_list.clear();
				first_i = processed.indexOf(false);
			}
		}
	}
}

void CConstLinesDataset::paint(QPainter& painter, const CMatrix3d& q, const CProjection& p, const CTransformd& m, const QRectF& paint_rect)
{
	painter.setBrush(QBrush());
	painter.setPen(Qt::gray);

	auto begin = m_data.begin(), end = m_data.end();
	while (begin != end) {
		auto path = begin->toPath(q, p, m, paint_rect);
		if (path)
			painter.drawPath(*path);
		++begin;
	}
}


std::optional<QPainterPath> CConstLinesDataset::CPolyline::toPath(const CMatrix3d& q, const CProjection& p, const CTransformd& m,
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
