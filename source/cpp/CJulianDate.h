/*!
*  \file      CJulianDate.h
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

#include "CDateTime.h"

/*! 
* \brief Timestamp as Julian date
* 
* The CJulianDate class holds a timestamp (date and time) as a double precision 
* floating point number, represented as Julian date. The class is used to
* provide Qt-independent means to represent a date and time and convert dates and
* times from and to Julian date.
*
* Please note, that the conversion to and from Julian date is limited.
*/
class CJulianDate
{
public:
	/*! \brief Search direction for finding rise and set of an object */
	enum tRiseSetType
	{
		/*! \brief Search nearest rise (set) either before or after the reference timestamp */
		rtNearest, 
		
		/*! \brief Return nearest rise (set) BEFORE the reference timestamp */
		rtBefore, 
		
		/*! \brief Return nearest rise (set) AFTER the reference timestamp */
		rtAfter
	};

	/*! \brief Return codes for finding rise and set of an object */
	enum tRiseSetResult
	{
		/*! \breif Success */
		rcOK, 
		
		/*! \brief The object is always ABOVE the horizon */
		rcAlwaysAbove, 
		
		/*! \brief The object is always BELOW the horizon */
		rcAlwaysBelow
	};

	/*! 
	* \brief Constructor
	* \param jd Julian date
	*/
	explicit CJulianDate(const double jd = 0) : m_jd(jd) {}

	/*! 
	* \brief Constructor from date and time 
	* 
	* The constructor create a timestamp from CDateTime instance.
	* 
	* \param dateTime date and time
	*/
	explicit CJulianDate(const CDateTime& dateTime);

	/*! 
	* \brief Constructor from date and time
	* 
	* The constructor creates a timestamp from year, month, day of month, hour, minute, second and millisecond.
	* 
	* \param year year
	* \param month month (1-12)
	* \param day day of month (1-31)
	* \param hour hour (0 - 23)
	* \param minute minute (0 - 59)
	* \param second second (0 - 59)
	* \param millisecond millisecond (0 - 999)
	*/
	CJulianDate(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0);

	/*! 
	* \brief Returns true if JD is zero. 
	* 
	* This zero JD is used as a return value to indicate a failure, unknown or invalid timestamp 
	*/
	bool isNull(void) const { return m_jd == 0; }

	/*! \brief Julian date */
	double jd_utc(void) const { return m_jd; }

	/*! \breif Convert to date & time */
	CDateTime toDateTime(void) const;

	/*! 
	* Convert to date & time 
	* 
	* The function returns timestamp as year, month, day of month, hour, minute, second and millisecond.
	*
	* \param[out] year year
	* \param[out] month month (1-12)
	* \param[out] day day of month (1-31)
	* \param[out] hour hour (0 - 23)
	* \param[out] minute minute (0 - 59)
	* \param[out] second second (0 - 59)
	* \param[out] millisecond millisecond (0 - 999)
	*/
	void toDateTime(int* year,int* month, int* day, int* hour, int* minute, int* second, int* millisecond) const;

	/*! 
	* \brief Heliocentric correction
	* 
	* JD heliocentric = JD geocentric + Heliocentric correction
	* 
	* \param RA equatorial coordinates of an object, right ascension in radians
	* \param DE equatorial coordinates of an object, declination in radians
	* \return heliocentric correction in fractions of day
	*/
	double HeliocentricCorrection(double RA, double DE) const;

	/*! 
	* \brief Greenwich Mean Sidereal Time 
	* 
	* The function computes Greenwich Mean Sidereal Time in days
	*/
	double siderealtime(void) const;

	/*! 
	* \brief Azimuth and elevation of a object
	* 
	* The function computes azimuth and elevation of an object
	* \param RA equatorial coordinates of an object, right ascension in radians
	* \param DE equatorial coordinates of an object, declination in radians
	* \param LON geographic coordinates of an observer, longitude in radians, positive EAST
	* \param LAT geographic coordinates of an observer, latitude in radians, positive NORTH
	* \param[out] AZ azimuth in radians, zero is NORTH, grows positive towards EAST
	*/
	void RaDeToAzAlt(double RA, double DE, double LON, double LAT, double* AZ, double* EL) const;

	/*! 
	* \brief Lunar phases ephemeris
	* 
	* The method computes ephemeris for Lunar phases.
	* 
	* <table>
	* <tr><th>Phase    <th>a0 <th>a1 <th>a2 <th>a3
	* <tr><td>New moon <td>1  <td>0  <td>0  <td>0
	* <tr><td>First quarter <td>0  <td>1  <td>0  <td>0
	* <tr><td>Full moon <td>0  <td>0  <td>1  <td>0
	* <tr><td>Last quarter <td>0  <td>0  <td>0  <td>1
	* </table>
	* 
	* \param a0 see description
	* \param a1 see description
	* \param a2 see description
	* \param a3 see description
	* \return time of the phase as Julian date UTC
	*/ 
	double MoonPhase(double a0, double a1, double a2, double a3);

	double Moon_NewMoon() { return MoonPhase(1, 0, 0, 0); }
	double Moon_FirstQuarter() { return MoonPhase(0, 1, 0, 0); }
	double Moon_FullMoon() { return MoonPhase(0, 0, 1, 0); }
	double Moon_LastQuarter() { return MoonPhase(0, 0, 0, 1); }

	/*! 
	* \brief Meridian transit time 
	* 
	* The function computes time of Meridian transit of an object
	* 
	* \param RA equatorial coordinates of an object, right ascension in radians
	* \param DE equatorial coordinates of an object, declination in radians
	* \param LON geographic coordinates of an observer, longitude in radians, positive EAST
	* \param LAT geographic coordinates of an observer, latitude in radians, positive NORTH
	* \param type search direction
	* \return time of the phase as Julian date UTC
	*/
	double RaDeToTransit(double RA, double DE, double LON, double LAT, tRiseSetType type) const;

	/*! 
	* \brief Rise time 
	* 
	* The function computes rise time of an object. When the EL parameter is nonzero, the function 
	* computes time when the object raises above the specified elevation angle.
	*
	* \param RA equatorial coordinates of an object, right ascension in radians
	* \param DE equatorial coordinates of an object, declination in radians
	* \param LON geographic coordinates of an observer, longitude in radians, positive EAST
	* \param LAT geographic coordinates of an observer, latitude in radians, positive NORTH
	* \param EL elevation angle in radians (positive above horizon)
	* \param type search direction
	* \return rise time as Julian date UTC
	*/
	tRiseSetResult RaDeToRise(double RA, double DE, double LON, double LAT, double* jd, double EL = 0, tRiseSetType type = rtAfter) const;

	/*! 
	* \brief Rise time
	*
	* The function computes set time of an object. When the EL parameter is nonzero, the function
	* computes time when the object sets below the specified elevation angle.
	*
	* \param RA equatorial coordinates of an object, right ascension in radians
	* \param DE equatorial coordinates of an object, declination in radians
	* \param LON geographic coordinates of an observer, longitude in radians, positive EAST
	* \param LAT geographic coordinates of an observer, latitude in radians, positive NORTH
	* \param EL elevation angle in radians (positive above horizon)
	* \param type search direction
	* \return set time as Julian date UTC
	*/
	tRiseSetResult RaDeToSet(double RA, double DE, double LON, double LAT, double* jd, double EL = 0, tRiseSetType type = rtBefore) const;

	/*! 
	* \brief Air-mass coefficient
	* 
	* The function computes an air-mass coefficient for an object
	* 
	* \param RA equatorial coordinates of an object, right ascension in radians
	* \param DE equatorial coordinates of an object, declination in radians
	* \param LON geographic coordinates of an observer, longitude in radians, positive EAST
	* \param LAT geographic coordinates of an observer, latitude in radians, positive NORTH
	* \return air-mass coefficient or a negative value if the object is too close the horizon or below horizon
	*/ 
	double AirMass(double RA, double DE, double LON, double LAT) const;

	/*! 
	* \brief Convert Julian date to year, month and day 
	*
	* The function converts a Julian date to year, month and day and fractional part
	* of a day.
	* \param jd Julian date
	* \param[out] year year
	* \param[out] month month (1 - 12)
	* \param[out] day day of month (1 - 31)
	* \return fractional part of a day since midnight
	*/ 
	static double FromJD(double jd, int& year, int& month, int& day);

	/*! 
	* \brief Julian date from year, month and day
	* 
	* The function computes Julian date from year, month and day of month.
	* It returns only an integer part. In order to get Julian date for midnight,
	* you have to add 0.5. 
	* \param year year
	* \param month month (1 - 12)
	* \param day day of month (1 - 31)
	* \return Julian date
	*/ 
	static int ToJD(int year, int month, int day);

	/*! \brief Comparison operator */
	inline bool operator==(const CJulianDate& other) const { return m_jd == other.m_jd; }

	/*! \brief Comparison operator */
	inline bool operator!=(const CJulianDate& other) const { return !this->operator==(other); }

	/*! \brief Comparison operator */
	inline bool operator<(const  CJulianDate& other) const { return m_jd < other.m_jd; }

	/*! \brief Comparison operator */
	inline bool operator<=(const  CJulianDate& other) const { return !other.operator<(*this); }

	/*! \brief Comparison operator */
	inline bool operator>(const  CJulianDate& other) const { return other.operator<(*this); }

	/*! \brief Comparison operator */
	inline bool operator>=(const  CJulianDate& other) const { return !this->operator<(other); }

private:
	// Julian date
	double m_jd;

	// Sun ephemeris
	void Sun(double& rs, double& las) const;

	// Equatorial coordinates to ecliptical coordinates
	void RaDeToLaBe(double RA, double DE, double& LA, double& BE) const;
};
