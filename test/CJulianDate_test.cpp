/*!
*  \file      CJulianDate_test.cpp
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
#include "gtest/gtest.h"

#define _USE_MATH_DEFINES

#include <math.h>

#include "CJulianDate.h"
#include "CPlanets.h"

#undef DEG_TO_RAD
#undef RAD_TO_DEG

#define RA_TO_RAD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 12 * M_PI)
#define DEC_TO_RAD(d, m, s) DMS_TO_RAD(d, m, s)
#define DEG_TO_RAD(deg) ((deg) / 180 * M_PI)
#define RAD_TO_DEG(rad) ((rad) / M_PI * 180)
#define DMS_TO_RAD(d, m, s) ((abs(d) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 180 * M_PI)
#define HMS_TO_JD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 24)

// January 1, 2022, 0:00 UTC
static const double JD0 = 2459580.5;

// Brno, longitude in radians
static const double LON = 16.6103878 / 180 * M_PI; // 16d 36m 37.40s

// Brno, latitude in radians
static const double LAT = 49.1944631 / 180 * M_PI; // 49d 11m 40.07s

TEST(CJulianDate, InvalidJD) {
	EXPECT_TRUE(CJulianDate().isNull());
}

TEST(CJulianDate, InvalidJD2) {
	EXPECT_TRUE(CJulianDate(0).isNull());
}

TEST(CJulianDate, InvalidJD3) {
	EXPECT_FALSE(CJulianDate().toDateTime().isValid());
}

TEST(CJulianDate, ToDateTime) {
	CDateTime dt = CJulianDate(JD0).toDateTime();

	EXPECT_TRUE(dt.isValid());

	EXPECT_EQ(dt.year(), 2022);
	EXPECT_EQ(dt.month(), 1);
	EXPECT_EQ(dt.day(), 1);

	EXPECT_EQ(dt.hour(), 0);
	EXPECT_EQ(dt.minute(), 0);
	EXPECT_EQ(dt.second(), 0);
	EXPECT_EQ(dt.millisecond(), 0);
}

TEST(CJulianDate, SunRise) 
{
	// Celestial coordinates of Sun for January 1, 2022 6:55 am UTC
	static const double RA = RA_TO_RAD(18, 47, 05.2), DEC = -DEC_TO_RAD(22, 59, 55.1);
	// JD for January 1, 2022 6:55 am UTC
	static const double JD_SUNRISE = JD0 + HMS_TO_JD(6, 55, 00);

	double jd_rise;
	EXPECT_EQ(CJulianDate(JD0).RaDeToRise(CEquCoordinates(RA, DEC), CGeoCoordinates(LON, LAT), &jd_rise, 0, CJulianDate::tRiseSetType::rtAfter), CJulianDate::tRiseSetResult::rcOK);
	EXPECT_NEAR(jd_rise, JD_SUNRISE, HMS_TO_JD(0, 0, 30));
}

TEST(CJulianDate, SunSet)
{
	// Celestial coordinates of Sun for December 31, 2022 2:59 pm
	static const double RA = RA_TO_RAD(18, 44, 08.4), DEC = -DEC_TO_RAD(23, 3, 6.6);
	// JD for December 31, 2022 2:59 pm
	static const double JD_SUNSET = JD0 + HMS_TO_JD(14, 59, 0) - 1;

	double jd_set;
	EXPECT_EQ(CJulianDate(JD0).RaDeToSet(CEquCoordinates(RA, DEC), CGeoCoordinates(LON, LAT), &jd_set, 0, CJulianDate::tRiseSetType::rtBefore), CJulianDate::tRiseSetResult::rcOK);
	EXPECT_NEAR(jd_set, JD_SUNSET, HMS_TO_JD(0, 0, 30));
}

TEST(CJulianDate, SunTransit)
{
	// Celestial coordinates of Sun for January 1, 2022 10:57 am
	static const double RA = RA_TO_RAD(18, 47, 49.3), DEC = -DEC_TO_RAD(22, 59, 5.8);
	// JD for January 1, 2022 10:57 am
	static const double JD_TRANSIT = JD0 + HMS_TO_JD(10, 57, 0);

	double jd_trans = CJulianDate(JD0).RaDeToTransit(CEquCoordinates(RA, DEC), CGeoCoordinates(LON, LAT), CJulianDate::tRiseSetType::rtAfter);
	EXPECT_NEAR(jd_trans, JD_TRANSIT, HMS_TO_JD(0, 0, 10));
}

TEST(CJulianDate, TwilightEnd) 
{
	// Celestial coordinates of Sun for January 1, 2022 5:31 am
	static const double RA = RA_TO_RAD(18, 46, 49.8), DEC = -DEC_TO_RAD(23, 0, 11.5), EL = -DEG_TO_RAD(12);
	// JD for January 1, 2022 5:31 am
	static const double JD_TWILIGHT = JD0 + HMS_TO_JD(5, 31, 0);

	double tw_end;
	EXPECT_EQ(CJulianDate(JD0).RaDeToRise(CEquCoordinates(RA, DEC), CGeoCoordinates(LON, LAT), &tw_end, EL, CJulianDate::tRiseSetType::rtAfter), CJulianDate::tRiseSetResult::rcOK);
	EXPECT_NEAR(tw_end, JD_TWILIGHT, HMS_TO_JD(0, 0, 30));
}

TEST(CJulianDate, TwilightStart)
{
	// Celestial coordinates of Sun for December 31, 2022 4:23 pm
	static const double RA = RA_TO_RAD(18, 44, 23.9), DEC = -DEC_TO_RAD(23, 2, 49.4), ALT = -DEG_TO_RAD(12);
	// JD for January 1, 2022 5:31 am
	static const double JD_TWILIGHT = JD0 + HMS_TO_JD(16, 23, 0) - 1;

	double tw_start;
	EXPECT_EQ(CJulianDate(JD0).RaDeToSet(CEquCoordinates(RA, DEC), CGeoCoordinates(LON, LAT), &tw_start, ALT, CJulianDate::tRiseSetType::rtBefore), CJulianDate::tRiseSetResult::rcOK);
	EXPECT_NEAR(tw_start, JD_TWILIGHT, HMS_TO_JD(0, 0, 30));
}

TEST(CJulianDate, SiderealTime) 
{
	// Greenwich Mean Sidereal Time for JD0 is 6:42:31.2
	static const double ST0 = HMS_TO_JD(6, 42, 31);

	EXPECT_NEAR(CJulianDate(JD0).siderealtime(), ST0, HMS_TO_JD(0, 0, 1));
}

TEST(CJulianDate, HeliocentricCorrection1)
{
	// Celestial coordinates of Sun for January 1, 2022 0:00 am
	static const double RA = RA_TO_RAD(18, 45, 26.2), DEC = -DEC_TO_RAD(23, 1, 40.4);

	// Heliocentric correction is -8.178 minutes
	static const double HELCOR = -HMS_TO_JD(0, 8.178, 0);

	EXPECT_NEAR(CJulianDate(JD0).HeliocentricCorrection(CEquCoordinates(RA, DEC)), HELCOR, HMS_TO_JD(0, 0, 1));
}

TEST(CJulianDate, HeliocentricCorrection2)
{
	// Celestial coordinates of Sirius for January 1, 2022 0:00 am
	static const double RA = RA_TO_RAD(6, 45, 8.92), DEC = -DEC_TO_RAD(16, 42, 58.02);

	// Heliocentric correction is 6.287 minutes
	static const double HELCOR = HMS_TO_JD(0, 6.287, 0);

	EXPECT_NEAR(CJulianDate(JD0).HeliocentricCorrection(CEquCoordinates(RA, DEC)), HELCOR, HMS_TO_JD(0, 0, 1));
}

TEST(CJulianDate, RaDeToAltAz)
{
	// Celestial coordinates of Sun for January 1, 2022 0:00 am
	static const double RA = RA_TO_RAD(18, 45, 26.3), DEC = -DEC_TO_RAD(23, 1, 40.5);

	static const double AZ = DMS_TO_RAD(31, 07, 12), ALT = -DMS_TO_RAD(61, 01, 48);

	double az, alt;
	CAzAltCoordinates z = CJulianDate(JD0).RaDeToAzAlt(CEquCoordinates(RA, DEC), CGeoCoordinates(LON, LAT));
	EXPECT_NEAR(z.azimuth().radians(), AZ, DEG_TO_RAD(1));
	EXPECT_NEAR(z.elevation().radians(), ALT, DEG_TO_RAD(1));
}

TEST(CJulianDate, AirMass)
{
	// Celestial coordinates of Sun for January 1, 2022 10:57 am
	static const double RA = RA_TO_RAD(18, 47, 49.3), DEC = -DEC_TO_RAD(22, 59, 5.8);
	// JD for January 1, 2022 10:57 am
	static const double JD1 = JD0 + HMS_TO_JD(10, 57, 0);
	// Airmass (expected value)
	static const double AIRMASS = 1.0;

	double x = CJulianDate(JD1).AirMass(CEquCoordinates(RA, DEC), CGeoCoordinates(LON, LAT));
	EXPECT_NEAR(x, AIRMASS, 0.001);
}
