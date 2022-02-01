#pragma once

#include <QtCore>

#include "CGeoLocation.h"

class CSharedData : public QObject
{
	Q_OBJECT

public:
	// Constructor
	explicit CSharedData(QObject* parent = NULL) : QObject(parent), m_twilight(12)
	{ 
		m_localDateTime = QDateTime::currentDateTime(); 
		m_geoloc.longitude().setDegrees(16.6103878);
		m_geoloc.latitude().setDegrees(49.1944631);
	}

	// Save permanent data
	void Save(void) {}

	// Selected local date and time
	QDateTime getSelectedLocalDateTime(void) const { return m_localDateTime; }
	void setLocalDateTime(const QDateTime& timestamp);

	// Location
	const CGeoLocation& geoLocation() const { return m_geoloc; }
	void setGeoLocation(const CGeoLocation& geoloc);

	// Twilight sun elevation 
	double twilightElevation(void) const { return m_twilight;  }
	void setTwilightElevation(double degrees) { m_twilight = degrees; }

signals:
	void dateTimeChanged();

	void geoLocationChanged();

private:
	QDateTime m_localDateTime;
	CGeoLocation m_geoloc;
	double m_twilight;
};
