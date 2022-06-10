#include "CEquGridDataset.h"
#include <CDeclination.h>
#include <CRightAscension.h>

void CEquGridDataset::paint(QPainter& painter, const QQuaternion& q, const CProjection& p, const QTransform& m)
{
	painter.setPen(QPen(Qt::red));

	// Equatorial grid
	for (int i = -8; i <= 8; i++) {
		double dec = CDeclination::fromDegrees(i * 10).radians();
		for (int j = 0; j < 24; j++) {
			double ra = CRightAscension::fromHours(j).radians();
			QVector3D equ3d(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec));
			QVector3D r3d = q.rotatedVector(equ3d).normalized();
			p.project(r3d);
			if (r3d.z() >= 0) 
				painter.drawPoint(m.map(r3d.toPointF()));
		}
	}
}
