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

#define RA_TO_RAD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 12 * M_PI)
#define DEC_TO_RAD(d, m, s) ((abs(d) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 180 * M_PI)

#define KM_TO_AU(km) (static_cast<double>(km) / 149597870.700)

// January 1, 2022, 0:00 UTC
static const double JD0 = 2459580.5;

// Sun ephemerides for JD0 (RA, Dec, distance, 
static const double Sun[3] = { RA_TO_RAD(18, 45, 48.6), -DEC_TO_RAD(23, 1, 16.4), 0.98 };

// Moon ephemerides for JD0
static const double Moon[4] = { RA_TO_RAD(16, 58, 18.5), -DEC_TO_RAD(24, 24, 56.7), KM_TO_AU(363634.41), 0.05 };

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
static const double Pluto[3] = { RA_TO_RAD(19, 53, 05.9), -DEC_TO_RAD(22, 39, 21.6), 35.38 };

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

static void PrintRaDiff(double rad)
{
	if (rad > M_PI)
		rad = 2 * M_PI - rad;
	int i = (fabs(rad) / M_PI * 12 * 3600 + 0.5);
	int h = i / 3600, m = (i / 60) % 60, s = (i % 60);
	std::cout << h << ":" << m << ":" << s << std::endl;
}

static void PrintDecDiff(double rad)
{
	int i = (rad / M_PI * 180 * 3600 + 0.5);
	if (i >= 0) {
		int h = i / 3600, m = (i / 60) % 60, s = (i % 60);
		std::cout << h << ":" << m << ":" << s << std::endl;
	}
	else {
		i = abs(i);
		int h = i / 3600, m = (i / 60) % 60, s = (i % 60);
		std::cout << "-" << h << ":" << m << ":" << s << std::endl;
	}
}

TEST(CPlanets, Sun) {
	CPlanets pl(JD0);

	double r, d, D;
	pl.Sun(&r, &d, &D);
	PrintRaDiff(fabs(Sun[0] - r));
	PrintDecDiff(fabs(Sun[1] - d));
	EXPECT_LT(CompareAngles(r, Sun[0]), DEC_TO_RAD(0, 1, 0));
	EXPECT_LT(CompareAngles(d, Sun[1]), DEC_TO_RAD(0, 1, 0));
	EXPECT_NEAR(D, Sun[2], 0.01);
}

TEST(CPlanets, Moon) {
	CPlanets pl(JD0);

	double r, d;
	pl.Moon(&r, &d);
	PrintRaDiff(fabs(Moon[0] - r));
	PrintDecDiff(fabs(Moon[1] - d));
	EXPECT_LT(CompareAngles(r, Moon[0]), DEC_TO_RAD(0, 40, 0));
	EXPECT_LT(CompareAngles(d, Moon[1]), DEC_TO_RAD(0, 30, 0));
}

TEST(CPlanets, Mercury) {
	CPlanets pl(JD0);

	double r, d;
	pl.Mercury(&r, &d);
	PrintRaDiff(fabs(Mercury[0] - r));
	PrintDecDiff(fabs(Mercury[1] - d));
	EXPECT_LT(CompareAngles(r, Mercury[0]), DEC_TO_RAD(0, 1, 0));
	EXPECT_LT(CompareAngles(d, Mercury[1]), DEC_TO_RAD(0, 1, 0));
}

TEST(CPlanets, Venus) {
	CPlanets pl(JD0);

	double r, d;
	pl.Venus(&r, &d);
	PrintRaDiff(fabs(Venus[0] - r));
	PrintDecDiff(fabs(Venus[1] - d));
	EXPECT_LT(CompareAngles(r, Venus[0]), DEC_TO_RAD(0, 20, 0));
	EXPECT_LT(CompareAngles(d, Venus[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Mars) {
	CPlanets pl(JD0);

	double r, d;
	pl.Mars(&r, &d);
	PrintRaDiff(fabs(Mars[0] - r));
	PrintDecDiff(fabs(Mars[1] - d));
	EXPECT_LT(CompareAngles(r, Mars[0]), DEC_TO_RAD(0, 5, 0));
	EXPECT_LT(CompareAngles(d, Mars[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Jupiter) {
	CPlanets pl(JD0);

	double r, d;
	pl.Jupiter(&r, &d);
	PrintRaDiff(fabs(Jupiter[0] - r));
	PrintDecDiff(fabs(Jupiter[1] - d));
	EXPECT_LT(CompareAngles(r, Jupiter[0]), DEC_TO_RAD(0, 5, 0));
	EXPECT_LT(CompareAngles(d, Jupiter[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Saturn) {
	CPlanets pl(JD0);

	double r, d;
	pl.Saturn(&r, &d);
	PrintRaDiff(fabs(Saturn[0] - r));
	PrintDecDiff(fabs(Saturn[1] - d));
	EXPECT_LT(CompareAngles(r, Saturn[0]), DEC_TO_RAD(0, 5, 0));
	EXPECT_LT(CompareAngles(d, Saturn[1]), DEC_TO_RAD(0, 5, 0));
}

TEST(CPlanets, Uranus) {
	CPlanets pl(JD0);

	double r, d;
	pl.Uranus(&r, &d);
	PrintRaDiff(fabs(Uranus[0] - r));
	PrintDecDiff(fabs(Uranus[1] - d));
	EXPECT_LT(CompareAngles(r, Uranus[0]), DEC_TO_RAD(0, 2, 0));
	EXPECT_LT(CompareAngles(d, Uranus[1]), DEC_TO_RAD(0, 2, 0));
}

TEST(CPlanets, Neptune) {
	CPlanets pl(JD0);

	double r, d;
	pl.Neptune(&r, &d);
	PrintRaDiff(fabs(Neptune[0] - r));
	PrintDecDiff(fabs(Neptune[1] - d));
	EXPECT_LT(CompareAngles(r, Neptune[0]), DEC_TO_RAD(0, 2, 0));
	EXPECT_LT(CompareAngles(d, Neptune[1]), DEC_TO_RAD(0, 2, 0));
}

TEST(CPlanets, Pluto) {
	CPlanets pl(JD0);

	double r, d;
	pl.Pluto(&r, &d);
	PrintRaDiff(fabs(Pluto[0] - r));
	PrintDecDiff(fabs(Pluto[1] - d));
	EXPECT_LT(CompareAngles(r, Pluto[0]), DEC_TO_RAD(0, 30, 0));
	EXPECT_LT(CompareAngles(d, Pluto[1]), DEC_TO_RAD(0, 5, 0));
}
