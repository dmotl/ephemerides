/*!
*  \file      CJulianDate.cpp
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
#include "CJulianDate.h"

#define _USE_MATH_DEFINES

#include <math.h>

//
// Normalize angle to the range 0..2pi
// 
static double normalizeAngle(double rad)
{
	double i;

	if (rad > 2 * M_PI) {
		rad = modf(rad / (2 * M_PI), &i);
		rad = rad * (2 * M_PI);
	}
	else if (rad < 0) {
		rad = modf(-rad / (2 * M_PI), &i);
		rad = (1 - rad) * (2 * M_PI);
	}
	if (rad == 2 * M_PI)
		return 0;
	return rad;
}

//
// Crop angle to the range -pi..pi
//
static double cropAngle(double rad)
{
	if (rad > M_PI_2)
		return M_PI_2;
	else if (rad < -M_PI_2)
		return -M_PI_2;
	else
		return rad;
}


//
// Convert JD to year, month and day
// The function returns time since midnight as fractions of day
//
double CJulianDate::FromJD(double jd, int& year, int& month, int& day)
{
	int a, b, c, e, x, z;

	/* Check Julian date */
	if (jd <= 0.0) {
		year = month = day = 0;
		return 0;
	}

	/* Compute citizen date: year, month and day from input Julian date. */
	/* Only for JD>0! Tested for YEAR>0 except 1582-10-07/15. */
	z = (int)(jd + 0.5);
	if (z >= 2299163) {
		int alpha = (int)((z - 1867216.25) / 36524.25);
		a = z + 1 + alpha - (alpha / 4);
	}
	else {
		a = z;
	}
	b = a + 1524;
	c = (int)((b - 122.1) / 365.25);
	x = (int)(365.25 * c);
	e = (int)((b - x) / 30.6001);

	month = (e <= 13 ? e - 1 : e - 13);
	year = (month >= 3 ? c - 4716 : c - 4715);
	day = b - x - (int)(30.6001 * e);

	return jd + 0.5 - z;
}


//
// Convert year, month and day to JD
// The function returns only integer part, you have to 
// add 0.5 to get Julian date at midnight.
//
int CJulianDate::ToJD(int year, int month, int day)
{
	int jd1, before, d1, d2;

	/* Check date and time */
	if (day <= 0 || month <= 0 || year <= 0)
		return 0;

	/* Compute Julian date from input citizen year, month and day. */
	/* Tested for YEAR>0 except 1582-10-07/15 */
	if (year > 1582) {
		before = 0;
	}
	else if (year < 1582) {
		before = 1;
	}
	else
		if (month > 10) {
			before = 0;
		}
		else if (month < 10) {
			before = 1;
		}
		else
			if (day >= 15) {
				before = 0;
			}
			else {
				before = 1;
			}
	if (month <= 2) {
		d1 = (int)(365.25 * (year - 1));
		d2 = (int)(30.6001 * (month + 13));
	}
	else {
		d1 = (int)(365.25 * (year));
		d2 = (int)(30.6001 * (month + 1));
	}
	jd1 = 1720994 + d1 + d2 + day;

	if (before) {
		if (year < 0)
			return jd1 - 1;
		else
			return jd1;
	}
	else {
		return jd1 + 2 - (year / 100) + (year / 400);
	}
}

#define ZERO(ptr) { if (ptr) *(ptr) = 0; }
#define SET(ptr, value) { if (ptr) *(ptr) = (value); }

//
// Equatorial coordinates to ecliptical coordinates
//
void CJulianDate::RaDeToLaBe(double ra, double de, double& la, double& be) const
{
	double VT2000 = (m_jd - 24515450) / 36525;
	double eps = (23.4392911 - 0.0130042 * VT2000 - 0.00000164 * VT2000 * VT2000 + 0.000000503 * VT2000 * VT2000 * VT2000) / 180 * M_PI;

	// To 0..2pi 
	ra = normalizeAngle(ra);
	de = cropAngle(de);

	// Singularities
	if (de == M_PI / 2) {
		la = M_PI / 2;
		be = M_PI / 2 - eps;
	}
	else if (de == -M_PI / 2) {
		la = 3 * M_PI / 2;
		be = eps - M_PI / 2;
	}
	else if (ra == M_PI / 2) {
		la = M_PI / 2;
		be = de - eps;
	}
	else if (ra == 3 * M_PI / 2) {
		la = 3 * M_PI / 2;
		be = de + eps;
	}
	else {
		be = asin(cos(eps) * sin(de) - sin(eps) * cos(de) * sin(ra));
		la = atan((sin(eps) * sin(de) + cos(eps) * cos(de) * sin(ra)) / (cos(de) * cos(ra)));
		if (cos(ra) < 0)
			la = la + M_PI; // To correct quadrant
	}
}


//
// Sun ephemerides (distance, ecliptical length)
//
void CJulianDate::Sun(double& rs, double& las) const
{
	// Vypocet ekl.delky slunce a vzdalenosti zeme - slunce 
	double t = m_jd - 2451545;
	double vt = 1 + (t / 36525);
	double ls = (0.779072 + 0.00273790931 * t) * 2 * M_PI;
	double ms = (0.993126 + 0.00273777850 * t) * 2 * M_PI;
	double m5 = (0.056531 + 0.00023080893 * t) * 2 * M_PI;
	double m4 = (0.053856 + 0.00145561327 * t) * 2 * M_PI;
	double m2 = (0.140023 + 0.00445036173 * t) * 2 * M_PI;
	double lm = (0.606434 + 0.03660110129 * t) * 2 * M_PI;
	las = ls * 3600 * 180 / M_PI + 6910 * sin(ms)
		+ 72 * sin(2 * ms)
		- 17 * vt * sin(ms)
		- 7 * cos(ms - m5)
		+ 6 * sin(lm - ls)
		+ 5 * sin(4 * ms + 8 * m4 + 3 * m5)
		- 5 * cos(2 * ms - 2 * m2)
		- 4 * sin(ms - m2)
		+ 4 * cos(4 * ms - 8 * m4 + 3 * m5)
		+ 3 * sin(2 * ms - 2 * m2)
		- 3 * sin(m5)
		- 3 * sin(2 * ms - 2 * m5);
	// Ekl. length of sun in radians
	las = normalizeAngle(las / 3600 / 180 * M_PI);
	// Earth-Sun distance in AU
	rs = 1.00014 - 0.01675 * cos(ms) - 0.00014 * cos(2 * ms); 
}


//
// To date and time
//
CDateTime CJulianDate::toDateTime(void) const
{
	int y, m, d;
	double fracd = FromJD(m_jd, y, m, d);
	if (m > 0 && d > 0) {
		int msecs = (int)(fracd * 86400000.0 + 0.5);
		int hour = (msecs / 3600000);
		int minute = (msecs / 60000) % 60;
		int second = (msecs / 1000) % 60;
		int millisecond = msecs % 1000;
		return CDateTime(y, m, d, hour, minute, second, millisecond);
	}
	return CDateTime();
}


//
// To date and time
//
void CJulianDate::toDateTime(int* year, int* month, int* day, int* hour, int* minute, int* second, int* millisecond) const
{
	ZERO(year);
	ZERO(month);
	ZERO(day);
	ZERO(hour);
	ZERO(minute);
	ZERO(second);
	ZERO(millisecond);

	int y, m, d;
	double fracd = FromJD(m_jd, y, m, d);
	if (m > 0 && d > 0) {
		SET(year, (int)y);
		SET(month, (int)m);
		SET(day, (int)d);

		int msecs = (int)(fracd * 86400000.0 + 0.5);
		SET(hour, (msecs / 3600000));
		SET(minute, (msecs / 60000) % 60);
		SET(second, (msecs / 1000) % 60);
		SET(millisecond, msecs % 1000);
	}
}


//
// Constructor
//
CJulianDate::CJulianDate(int year, int month, int day, int hour, int minute, int second, int millisecond)
{
	m_jd = ToJD(year, month, day) + 0.5 + 
		(double)hour / 24 + ((double)minute / 1440.0) + ((double)second / 86400.0) + ((double)millisecond / 86400000.0);
}


//
// Constructor
//
CJulianDate::CJulianDate(const CDateTime& dt)
{
	m_jd = ToJD(dt.year(), dt.month(), dt.day()) + 0.5 + 
		(double)dt.hour() / 24 + ((double)dt.minute() / 1440.0) + ((double)dt.second() / 86400.0) + ((double)dt.millisecond() / 86400000.0);
}


//
// Heliocentric correction
//
double CJulianDate::HeliocentricCorrection(double RA, double DE) const
{
	double jd = m_jd;
	if (jd < 2000000)
		jd += 2400000;
	double la, be;
	RaDeToLaBe(RA, DE, la, be);
	double las, rs;
	Sun(rs, las);
	return -0.00577552 * rs * cos(be) * cos(la - las);
}


//
// Air mass coefficient
//
double CJulianDate::AirMass(double RA, double DEC, double LON, double LAT) const
{
	// Hour angle
	double HA = siderealtime() * (2 * M_PI) + (LON - RA);
	// sec of zenital distance
	double lat = LAT / 180.0 * M_PI;
	double dec = DEC / 180.0 * M_PI;
	double ha = HA / 12.0 * M_PI;
	double z = sin(lat) * sin(dec) + cos(lat) * cos(dec) * cos(ha);
	// Is the star above the horizon?
	if (z >= 0.05) {
		double secz = 1.0 / z;
		// Air mass coefficient
		return secz - 0.0018167 * (secz - 1) - 0.002875 * (secz - 1) * (secz - 1) - 0.0008083 * (secz - 1) * (secz - 1) * (secz - 1);
	}
	return -1;
}


//
// Mean sidereal time
//
double CJulianDate::siderealtime(void) const
{
	// Computes Greenwich mean sidereal time in hours
	// JD at 0h UT
	double jd0 = floor(m_jd) + 0.5;
	// Julian centuries
	double t3 = (jd0 - 2451545.0) / 36525.0;
	// Mean sidereal time for 0h UT
	double s0 = 6.697374558 + 2400.05133691 * t3 + 0.0000258622 * t3 * t3 - 0.0000000017 * t3 * t3 * t3;
	// Mean sidereal time
	double s1 = s0 / 24.0 + 1.0027379093 * (m_jd - jd0);
	return s1 - floor(s1);
}


//
// Equatorial coordinates to azimuth and elevation
//
void CJulianDate::RaDeToAzAlt(double RA, double DE, double LON, double LAT, double* az, double* alt) const
{
	// Hour angle [rad]
	double ha = siderealtime() * (2 * M_PI) + (LON - RA);
	if (alt)
		*alt = asin(sin(DE) * sin(LAT) + cos(DE) * cos(ha) * cos(LAT));
	if (az) {
		*az = 3 * M_PI / 2 - atan2(cos(DE) * cos(ha) * sin(LAT) - sin(DE) * cos(LAT), cos(DE) * sin(ha));
		if (*az > 2 * M_PI)
			*az -= 2 * M_PI;
	}
}


//
// Meridian transit time of an object
//
double CJulianDate::RaDeToTransit(double RA, double DE, double LON, double LAT, tRiseSetType type) const
{
	// Hour angle [rad]
	double ha = siderealtime() * (2 * M_PI) + (LON - RA);
	double TTrans = -ha / (2 * M_PI);
	TTrans = TTrans - floor(TTrans);
	if ((type == rtNearest && TTrans > 0.5) || (type == rtBefore && TTrans > 0.0))
		TTrans -= 1.0;
	return m_jd + TTrans / 1.0027379093;
}


//
// Moon ephemerides
//
double CJulianDate::MoonPhase(double a0, double a1, double a2, double a3)
{
	int day, month, year;

	FromJD(m_jd - 28, year, month, day);
	double k = floor(12.3685 * (year + month / 12 - 1900)) + a1 * 0.25 + a2 * 0.5 + a3 * 0.75;
	double T1 = k / 1236.85;
	double jdf = 2415020.75933 + 29.53058868 * k + 0.0001178 * T1 * T1 - 0.000000155 * T1 * T1 * T1 + 0.00033 * sin(2.90702 + 2.319019 * T1 - 0.000160099 * T1 * T1);
	double ms0 = (359.2242 + 29.10535608 * k - 0.0000333 * T1 * T1 - 0.00000347 * T1 * T1 * T1) / 180 * M_PI;
	double mm0 = (306.0253 + 385.81691806 * k + 0.0107306 * T1 * T1 + 0.00001236 * T1 * T1 * T1) / 180 * M_PI;
	double um0 = (21.2964 + 390.67050646 * k - 0.0016528 * T1 * T1 - 0.00000239 * T1 * T1 * T1) / 180 * M_PI;
	double Result = jdf +
		(a0 + a2) * (
			(0.1734 - 0.000393 * T1) * sin(ms0)
			- 0.4068 * sin(mm0)
			+ 0.0161 * sin(2 * mm0)
			+ 0.0104 * sin(2 * um0)
			- 0.0074 * sin(ms0 - mm0)
			- 0.0051 * sin(ms0 + mm0)
			+ 0.0021 * sin(2 * ms0)
			+ 0.0010 * sin(2 * um0 - mm0)
			- 0.0006 * sin(2 * um0 + mm0)
			+ 0.0005 * sin(ms0 + 2 * mm0)
			- 0.0004 * sin(3 * mm0)
			+ 0.0004 * sin(2 * um0 + ms0)
			- 0.0004 * sin(2 * um0 - ms0))
		+ (a1 + a3) * (
			(0.1721 - 0.0004 * T1) * sin(ms0)
			- 0.6280 * sin(mm0)
			- 0.0119 * sin(ms0 + mm0)
			+ 0.0089 * sin(2 * mm0)
			+ 0.0079 * sin(2 * um0)
			- 0.0047 * sin(ms0 - mm0)
			+ 0.0021 * sin(2 * um0 - mm0)
			+ 0.0021 * sin(2 * ms0)
			- 0.0006 * sin(2 * um0 + mm0)
			- 0.0004 * sin(3 * mm0)
			- 0.0004 * sin(2 * um0 - ms0)
			+ 0.0004 * sin(ms0 - 2 * mm0)
			+ 0.0003 * sin(2 * um0 + ms0)
			+ 0.0003 * sin(ms0 + 2 * mm0)
			- 0.0003 * sin(2 * ms0 + mm0))
		+ (a1 - a3) * (
			0.0028
			- 0.0004 * cos(ms0)
			+ 0.0003 * cos(mm0));
	return Result;
}


//
// Rise of an object
//
CJulianDate::tRiseSetResult CJulianDate::RaDeToRise(double RA, double DE, double LON, double LAT, double* jd, double EL, tRiseSetType type) const
{
	static const double eps = 5e-6;  // cca 1"

	if (LAT == M_PI_2 - eps) {
		// Terrestrial north pole: Stars with dec>=0 are above horizon, dec<0 below horizon
		if (DE < 0)
			return rcAlwaysBelow;
		else
			return rcAlwaysAbove;
	}
	else if (LAT == -M_PI_2 + eps) {
		// Terrestrial south pole: Stars with dec>0 are below horizon, dec<=0 above horizon
		if (DE > 0)
			return rcAlwaysBelow;
		else
			return rcAlwaysAbove;
	}
	else if (DE == M_PI_2 - eps) {
		// Celestial north pole: For observers with lat>=0 star is above horizon, lat<0 below horizon
		if (LAT < 0)
			return rcAlwaysBelow;
		else
			return rcAlwaysAbove;
	}
	else if (DE == -M_PI_2 + eps) {
		// Celestial south pole: For observers with lat>0 star is below horizon, lat<=0 above horizon
		if (LAT < 0)
			return rcAlwaysBelow;
		else
			return rcAlwaysAbove;
	}
	else {
		double x = (sin(EL) - sin(LAT) * sin(DE)) / cos(LAT) / cos(DE);
		if (x >= 1) {
			// Star is always below horizon
			return rcAlwaysBelow;
		}
		else if (x <= -1) {
			// Star is always above horizon
			return rcAlwaysAbove;
		}
		else {
			// Star rises and sets
			if (jd) {
				double ha = siderealtime() * (2 * M_PI) + (LON - RA);
				double TRise = -(ha + acos(x)) / (2 * M_PI);
				TRise = TRise - floor(TRise);
				if (type == rtNearest && TRise > 0.5)
					TRise = TRise - 1.0;
				else if (type == rtBefore && TRise > 0.0)
					TRise = TRise - 1.0;
				*jd = m_jd + TRise / 1.0027379093;
			}
			return rcOK;
		}
	}
}


//
// Set of an object
//
CJulianDate::tRiseSetResult CJulianDate::RaDeToSet(double RA, double DE, double LON, double LAT, double* jd, double EL, tRiseSetType type) const
{
	static const double eps = 5e-6;  // cca 1"

	if (LAT == M_PI - eps) {
		// Terrestrial north pole: Stars with dec>=0 are above horizon, dec<0 below horizon
		if (DE < 0)
			return rcAlwaysBelow;
		else
			return rcAlwaysAbove;
	}
	else if (LAT == -M_PI + eps) {
		// Terrestrial south pole: Stars with dec>0 are below horizon, dec<=0 above horizon
		if (DE > 0)
			return rcAlwaysBelow;
		else
			return rcAlwaysAbove;
	}
	else if (DE == M_PI - eps) {
		// Celestial north pole: For observers with lat>=0 star is above horizon, lat<0 below horizon
		if (LAT < 0)
			return rcAlwaysBelow;
		else
			return rcAlwaysAbove;
	}
	else if (DE == -M_PI + eps) {
		// Celestial south pole: For observers with lat>0 star is below horizon, lat<=0 above horizon
		if (LAT < 0)
			return rcAlwaysBelow;
		else
			return rcAlwaysAbove;
	}
	else {
		double x = (sin(EL) - sin(LAT) * sin(DE)) / cos(LAT) / cos(DE);
		if (x >= 1) {
			// Star is always below horizon
			return rcAlwaysBelow;
		}
		else if (x <= -1) {
			// Star is always above horizon
			return rcAlwaysAbove;
		}
		else {
			// Star rises and sets
			if (jd) {
				double ha = siderealtime() * (2 * M_PI) + (LON - RA);
				double TSet = -(ha - acos(x)) / (M_PI * 2);
				TSet = TSet - floor(TSet);
				if (type == rtNearest && TSet > 0.5)
					TSet = TSet - 1.0;
				else if (type == rtBefore && TSet > 0.0)
					TSet = TSet - 1.0;
				*jd = m_jd + TSet / 1.0027379093;
			}
			return rcOK;
		}
	}
}
