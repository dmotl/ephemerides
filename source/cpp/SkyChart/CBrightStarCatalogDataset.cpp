#include "CBrightStarCatalogDataset.h"

#include "CBSC1991.h"

#define MAG_LIMIT 6.0

CBrightStarCatalogDataset::CBrightStarCatalogDataset(QObject* parent) : CSkyChartDataset(parent)
{
	m_bsc = new CBSC1991();
	if (m_bsc->load("d:\\projekty\\ephemerides\\share\\bsc1991")) {
		auto begin = m_bsc->data().begin(), end = m_bsc->data().end();
		while (begin != end) {
			if ((*begin)->magnitude() < MAG_LIMIT) {
				CEquCoordinates equ = (*begin)->equatorialJ2000();
				double ra = equ.rightAscension().radians(), dec = equ.declination().radians();
				tObject obj;
				obj.pos = QVector3D(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec));
				obj.rsize = (MAG_LIMIT - (*begin)->magnitude()) / 3;
				m_data.push_back(obj);
			}
			++begin;
		}
	}
}

CBrightStarCatalogDataset::~CBrightStarCatalogDataset()
{
	delete m_bsc;
}

void CBrightStarCatalogDataset::paint(QPainter& painter, const QQuaternion& q, const QTransform& m)
{
	Qt::GlobalColor color = Qt::transparent;

	painter.setBrush(Qt::white);

	// Equatorial grid
	auto begin = m_data.begin(), end = m_data.end();
	while (begin != end) {
		QVector3D r3d = q.rotatedVector(begin->pos).normalized();
		if (r3d.z() >= 0) {
			if (begin->rsize < 0.5) {
				if (color != Qt::gray) {
					painter.setPen(Qt::gray);
					color = Qt::gray;
				}
				painter.drawPoint(m.map(r3d.toPointF()));
			}
			else {
				if (color != Qt::white) {
					painter.setPen(Qt::white);
					color = Qt::white;
				}
				if (begin->rsize < 1)
					painter.drawPoint(m.map(r3d.toPointF()));
				else
					painter.drawEllipse(m.map(r3d.toPointF()), begin->rsize, begin->rsize);
			}
		}
		++begin;
	}
}
