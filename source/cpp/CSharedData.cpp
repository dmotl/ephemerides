#include "CSharedData.h"

void CSharedData::setLocalDateTime(const QDateTime& timestamp)
{
	if (timestamp != m_localDateTime && timestamp.isValid())
	{
		m_localDateTime = timestamp;
		emit dateTimeChanged();
	}
}

void CSharedData::setGeoLocation(const CGeoLocation& geoloc)
{
	if (geoloc != m_geoloc) 
	{
		m_geoloc = geoloc;
		emit geoLocationChanged();
	}
}
