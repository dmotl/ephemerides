/*!
*  \file      UtilsQt.h
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

#include "Utils.h"
#include "CAzimuth.h"

namespace UtilsQt
{
	/*
	* Lower bound for a valid Julian date
	*
	* This corresponds to January 1, 1583
	*/
	static const int min_jd = 2299238;

	/*
	*
	* Upper bound for a valid Julian date
	*
	* This corresponds to January 1, 3500
	*/
	static const int max_jd = 2999408;

	/*
	* \brief Convert local date time to UTC Julian date
	*
	* The function takes a local time stamp on input and returns its
	* representation as Julian date and fractions of the day.
	*
	* \param dateTime local time
	* \return Julian date (UTC)
	*/
	inline double toJulianDate(const QDateTime& dateTime)
	{
		if (!dateTime.isNull()) {
			QDateTime utc = dateTime.toUTC();
			__int64 msecs = (utc.date().toJulianDay() - 0.5) * 86400000 + utc.time().msecsSinceStartOfDay();
			return static_cast<double>(msecs) / 86400000.0;
		}
		return 0;
	}

	/*
	* \brief Convert UTC Julian date to local date and time
	*
	* The function takes time as Julian date in UTC and returns
	* corresponding local date and time.
	*
	* \param dateTime local time
	* \return Julian date
	*/
	inline QDateTime fromJulianDate(double jd_utc)
	{
		if (jd_utc >= min_jd && jd_utc <= max_jd) {
			__int64 msecs = (__int64)((jd_utc + 0.5) * 86400000.0);
			return QDateTime(QDate::fromJulianDay(msecs / 86400000), QTime::fromMSecsSinceStartOfDay(msecs % 86400000), Qt::UTC).toLocalTime();
		}
		return QDateTime();
	}

	/*
	* \brief Compass point name
	* 
	* The function returns a name of a specified point on 16-point 
	* compass rose, e.g. S, SW, SSW, ...
	* 
	* \param pt compass point
	* \return compass point name
	*/
	QString compassPointName(CAzimuth::tCompassPoint pt);
}
