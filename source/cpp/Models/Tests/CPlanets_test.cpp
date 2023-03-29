/*!
*  \file      CPlanets_test.cpp
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

#include "CPlanets.h"
#include <CEquCoordinates.h>

#undef RA_TO_RAD
#define RA_TO_RAD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 12 * M_PI)

#undef DEC_TO_RAD
#define DEC_TO_RAD(d, m, s) (((d) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 180 * M_PI)

#define KM_TO_AU(km) (static_cast<double>(km) / 149597870.700)

// January 1, 2022, 0:00 UTC
static const double JD0 = 2459580.5 + 69 / 86400.0;

// Sun ephemerides for JD0 (RA, Dec, distance, 
static const double Sun[3] = { RA_TO_RAD(18, 45, 48.6), -DEC_TO_RAD(23, 1, 16.4), 0.98 };

// Moon ephemerides for JD0 (J2000)
static const double Moon[4] = { RA_TO_RAD(16, 56, 25.31), -DEC_TO_RAD(24, 20, 17.6), KM_TO_AU(364211.388), 0.05 };

// Mercury ephemerides for JD0
static const double Mercury[4] = { RA_TO_RAD(20, 02, 42.6), -DEC_TO_RAD(22, 18, 30.4), 1.14, 0.78 };

// Venus ephemerides for JD0
static const double Venus[4] = { RA_TO_RAD(19, 38, 28.8), -DEC_TO_RAD(18, 35, 24.3), 0.27, 0.02 };

// Mars ephemerides for JD0
static const double Mars[4] = { RA_TO_RAD(16, 46, 38.6), -DEC_TO_RAD(22, 30, 02.0), 2.34, 0.98 };

// Jupiter ephemerides for JD0
static const double Jupiter[3] = { RA_TO_RAD(22, 11, 53.3), -DEC_TO_RAD(12, 12, 36.5), 5.57 };

// Saturn ephemerides for JD0
static const double Saturn[3] = { RA_TO_RAD(20, 58, 23.8), -DEC_TO_RAD(18, 00, 44.8), 14.94 };

// Uranus ephemerides for JD0
static const double Uranus[3] = { RA_TO_RAD(02, 34, 38.2), DEC_TO_RAD(14, 43, 34.4), 19.2 };

// Neptune ephemerides for JD0
static const double Neptune[3] = { RA_TO_RAD(23, 27, 30.1), -DEC_TO_RAD(4, 44, 25.0), 30.24 };

// Pluto ephemerides for JD0
//static const double Pluto[3] = { RA_TO_RAD(19, 53, 05.9), -DEC_TO_RAD(22, 39, 21.6), 35.38 };

static double CompareAngles(double alpha, double beta)
{
	while (alpha > 2 * M_PI)
		alpha -= 2 * M_PI;
	while (alpha < 0)
		alpha += 2 * M_PI;
	while (beta > 2 * M_PI)
		beta -= 2 * M_PI;
	while (beta < 0)
		beta += 2 * M_PI;

	double diff = fabs(alpha - beta);
	if (diff > M_PI)
		diff = 2 * M_PI - diff;
	return diff;
}

static void PrintAngularDist(std::string prefix, double _rad1, double _rad2)
{
	//std::cout << prefix << "computed: " << radToString(_rad1) << std::endl;
	//std::cout << prefix << "expected: " << radToString(_rad2) << std::endl;

	double rad = CompareAngles(_rad1, _rad2);
	if (rad > M_PI)
		rad = 2 * M_PI - rad;
	double d = (fabs(rad) / M_PI * 180 * 3600 + 0.5);
	std::cout << prefix << " difference: " << d << " arcsec " << std::endl;
}

TEST(CPlanets, Sun) {
	CVector3d xyz(CPlanets(JD0).Sun());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Sun[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Sun[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Sun[0]), DEC_TO_RAD(0, 1, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Sun[1]), DEC_TO_RAD(0, 1, 0));
	EXPECT_NEAR(xyz.length(), Sun[2], 0.01);
}

TEST(CPlanets, Moon) {
	CVector3d xyz(CPlanets(JD0).Moon());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Moon[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Moon[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Moon[0]), DEC_TO_RAD(0, 30, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Moon[1]), DEC_TO_RAD(0, 30, 0));
}

TEST(CPlanets, Mercury) {
	CVector3d xyz(CPlanets(JD0).Mercury());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Mercury[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Mercury[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Mercury[0]), DEC_TO_RAD(0, 5, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Mercury[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Venus) {
	CVector3d xyz(CPlanets(JD0).Venus());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Venus[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Venus[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Venus[0]), DEC_TO_RAD(0, 5, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Venus[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Mars) {
	CVector3d xyz(CPlanets(JD0).Mars());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Mars[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Mars[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Mars[0]), DEC_TO_RAD(0, 5, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Mars[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Jupiter) {
	CVector3d xyz(CPlanets(JD0).Jupiter());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Jupiter[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Jupiter[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Jupiter[0]), DEC_TO_RAD(0, 5, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Jupiter[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Saturn) {
	CVector3d xyz(CPlanets(JD0).Saturn());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Saturn[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Saturn[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Saturn[0]), DEC_TO_RAD(0, 5, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Saturn[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Uranus) {
	CVector3d xyz(CPlanets(JD0).Uranus());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Uranus[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Uranus[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Uranus[0]), DEC_TO_RAD(0, 2, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Uranus[1]), DEC_TO_RAD(0, 2, 0));
}

TEST(CPlanets, Neptune) {
	CVector3d xyz(CPlanets(JD0).Neptune());
	CEquCoordinates equ(Utils::vsop87ToFK5(xyz));
	PrintAngularDist("Longitude: ", Neptune[0], equ.rightAscension().radians());
	PrintAngularDist("Latitude:  ", Neptune[1], equ.declination().radians());
	EXPECT_LT(CompareAngles(equ.rightAscension().radians(), Neptune[0]), DEC_TO_RAD(0, 2, 0));
	EXPECT_LT(CompareAngles(equ.declination().radians(), Neptune[1]), DEC_TO_RAD(0, 2, 0));
}
