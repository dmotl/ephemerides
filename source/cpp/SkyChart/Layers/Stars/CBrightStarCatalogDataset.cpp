#include "CBrightStarCatalogDataset.h"

#include "CBSC1991.h"

#define MAG_LIMIT 6.0

CBrightStarCatalogDataset::CBrightStarCatalogDataset(const CBSC1991* file, QObject* parent) : CSkyChartDataset(parent)
{
	if (file) {
		auto begin = file->data().begin(), end = file->data().end();
		while (begin != end) {
			if ((*begin)->magnitude() < MAG_LIMIT) {
				CEquCoordinates equ = (*begin)->equatorialJ2000();
				double ra = equ.rightAscension().radians(), dec = equ.declination().radians();
				tObject obj;
				obj.pos = CVector3d(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec));
				obj.rsize = (MAG_LIMIT - (*begin)->magnitude()) / 3;
				m_data.push_back(obj);
			}
			++begin;
		}
	}
}

void CBrightStarCatalogDataset::paint(QPainter& painter, const CMatrix3d& q, const CProjection& p, const CTransformd& m, const QRectF& paint_rect)
{
	Qt::GlobalColor color = Qt::transparent;

	painter.setBrush(Qt::white);

	// Equatorial grid
	auto begin = m_data.begin(), end = m_data.end();
	while (begin != end) {
		CVector3d r3d = (q * begin->pos);
		p.project(r3d);
		if (r3d.z() >= 0) {
			if (begin->rsize < 0.5) {
				if (color != Qt::gray) {
					painter.setPen(Qt::gray);
					color = Qt::gray;
				}
				CPointd xy = m.map(r3d.toPointF());
				painter.drawPoint(xy.x(), xy.y());
			}
			else {
				if (color != Qt::white) {
					painter.setPen(Qt::white);
					color = Qt::white;
				}
				CPointd xy = m.map(r3d.toPointF());
				if (begin->rsize < 1)
					painter.drawPoint(xy.x(), xy.y());
				else
					painter.drawEllipse(xy.x(), xy.y(), begin->rsize, begin->rsize);
			}
		}
		++begin;
	}
}
