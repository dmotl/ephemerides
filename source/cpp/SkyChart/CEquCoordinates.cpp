#include "CEquCoordinates.h"

#include "SkyChartUtils.h"

CEquCoordinates::CEquCoordinates(const CVector3d& rect)
{
	if (!rect.isNull()) {
		double ra, dec;
		Utils::rectangularToSperical(rect, &ra, &dec);
		m_rightAscension = ra;
		m_declination = dec;
	}
}