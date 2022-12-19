/*!
*  \file      CSharedData.h
*  \author    David Motl
*  \date      2022-01-31
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
#pragma once

#include <QtCore>

#include "CGeoCoordinates.h"
#include "CEquCoordinates.h"
#include "Utils.h"
#include "CBound.h"
#include "CLines.h"
#include "CBSC1991.h"

/*
* \brief Shared data
* 
* The CSharedData class holds data shared by tools and widgets.
* 
* It is derived from QObject and emits a signal whenever a datum 
* changes. The tools and widgets are expected to connect to the 
* signals and update their content.
*
*/

class CSharedData : public QObject
{
	Q_OBJECT

public:
	/*
	* Constructor
	* 
	* The constructor initialize its content from the configuration
	* file. If this is the first run, it sets values to defaults.
	*
	*/ 
	explicit CSharedData(QObject* parent = NULL) : QObject(parent), m_twilight(12), m_constBound(NULL),
		m_constLines(NULL), m_bsc(NULL)
	{
		m_localDateTime = QDateTime::currentDateTime();
		m_geoloc.longitude().setDegrees(16.6103878);
		m_geoloc.latitude().setDegrees(49.1944631);
		m_equloc.rightAscension().setRadians(RA_TO_RAD(18, 45, 48.6));
		m_equloc.declination().setRadians(-DEC_TO_RAD(23, 1, 16.4));

		m_bsc = new CBSC1991_Embedded();
		m_constBound = new CBound();
		m_constLines = new CLines(*m_bsc);
	}

	~CSharedData(void) override {
		delete m_constBound;
		delete m_constLines;
		delete m_bsc;
	}

	// Constellation boundary data
	const CBound* constBound(void) const { return m_constBound; }

	// Constellation lines data
	const CLines* constLines(void) const { return m_constLines; }

	// Bright star catalog
	const CBSC1991_Embedded* bsc(void) const { return m_bsc; }

	/*
	* \brief Save permanent data
	* 
	* The function saves data that should be preserved between runs of
	* the application to the configuration file in user's application data.
	* 
	*/
	void Save(void) {}

	/*
	* \brief Set local date and time
	* 
	* The function updates the stored time stamp and emits the dateTimeChanged()
	* signal. The time stamp should be in user's local time zone.
	* 
	* \sa getSelectedLocalDateTime()
	*
	* \timestamp time stamp (local time)
	*/
	void setLocalDateTime(const QDateTime& timestamp);

	/*
	* \brief Local date and time
	* 
	* The function gets the stored time stamp. The date time is stored
	* in user's local time zone.
	*/
	QDateTime getSelectedLocalDateTime(void) const { return m_localDateTime; }

	/*
	* \brief Geographic coordinates
	*
	* The function gets the stored time stamp. The date time is stored
	* in user's local time zone.
	*/
	const CGeoCoordinates& geoLocation() const { return m_geoloc; }

	/*
	* \brief Selected geographic coordinates
	*
	* The function updates the stored observer's geographic coordinates and emits the geoLocationChanged()
	* signal. See the CGeoCoordinates class for description of coordinates.
	*
	* \sa geoLocation()
	*
	* \timestamp geographic coordinates
	*/
	void setGeoLocation(const CGeoCoordinates& geoloc);

	/*
	* \brief Equatorial celestial coordinates
	*
	*/
	const CEquCoordinates& equLocation() const { return m_equloc; }

	/*
	* \brief Selected equatorial celestial coordinates
	*/
	void setEquLocation(const CEquCoordinates& equloc);

	/*
	* \brief Twilight start/end elevation 
	* 
	* The function returns an absolute value of elevation of the Sun for computation of start and
	* end of twilight. The values is stored in degrees and it is always positive value.
	* 
	* The default value is 12 degrees.
	* 
	* \sa setTwilightElevation()
	*/
	double twilightElevation(void) const { return m_twilight;  }

	/*
	* \brief Set twilight start/end  elevation
	*
	* The function sets an absolute value of elevation of the Sun for computation of start and
	* end of twilight. The values is specified in degrees and it is always positive value.
	*
	* \sa twilightElevation()
	* 
	* \param degrees elevation in degrees (absolute value)
	*/
	void setTwilightElevation(double degrees) { m_twilight = degrees; }

signals:
	/* \brief The signal is emited when the stored local date and time changes */
	void dateTimeChanged();

	/* \brief The signal is emited when the observer's geographical coordinates changes */
	void geoLocationChanged();

	/* \brief The signal is emited when the object's equatorial coordinates changes */
	void equLocationChanged();

private:
	// Date and time
	QDateTime m_localDateTime;

	// Geographic coordinates of an observer
	CGeoCoordinates m_geoloc;

	// Equatorial coordinates on an object
	CEquCoordinates m_equloc;

	// Twilight start/end elevation
	double m_twilight;

	// Constellation boundary data
	CBound* m_constBound;

	// Constellation lines data
	CLines* m_constLines;

	// Bright star catalog
	CBSC1991_Embedded* m_bsc;
};
