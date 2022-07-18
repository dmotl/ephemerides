/*!
*  \file      VSOP87_test.cpp
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

#include "vsop87.h"

#include "vsop87.chk.h"
#include <SkyChartUtils.h>
#include <CEquCoordinates.h>

#undef DEG_TO_RAD
#undef RAD_TO_DEG

#define VSOP87_RECT_TEST(ib, iv, testTab, error) \
	static const tVSOP87TestXYZ* tab = vsop87_ ## testTab; \
	int size = sizeof(vsop87_ ## testTab) / sizeof(tVSOP87TestXYZ); \
	\
	for (int i = 0; i < size; i++) { \
		tVSOP87_Rect out; \
		EXPECT_EQ(vsop87 ## iv ((ib), tab[i].jd, &out), 0); \
		EXPECT_NEAR(out.X[0], tab[i].X, error); \
		EXPECT_NEAR(out.X[1], tab[i].Y, error); \
		EXPECT_NEAR(out.X[2], tab[i].Z, error); \
		EXPECT_NEAR(out.X[3], tab[i].Xdot, error); \
		EXPECT_NEAR(out.X[4], tab[i].Ydot, error); \
		EXPECT_NEAR(out.X[5], tab[i].Zdot, error); \
	}

TEST(VSOP87, VSPO87A_Mercury) 
{
	VSOP87_RECT_TEST(1, a, MERCURY_A, 6e-9);
}

TEST(VSOP87, VSPO87A_Venus)
{
	VSOP87_RECT_TEST(2, a, VENUS_A, 2.5e-8);
}

TEST(VSOP87, VSPO87A_Earth)
{
	VSOP87_RECT_TEST(3, a, EARTH_A, 1e-8);
}

TEST(VSOP87, VSPO87A_Mars)
{
	VSOP87_RECT_TEST(4, a, MARS_A, 1e-7);
}

TEST(VSOP87, VSPO87A_Jupiter)
{
	VSOP87_RECT_TEST(5, a, JUPITER_A, 4e-7);
}

TEST(VSOP87, VSPO87A_Saturn)
{
	VSOP87_RECT_TEST(6, a, SATURN_A, 7e-7);
}

TEST(VSOP87, VSPO87A_Uranus)
{
	VSOP87_RECT_TEST(7, a, URANUS_A, 8e-8);
}

TEST(VSOP87, VSPO87A_Neptune)
{
	VSOP87_RECT_TEST(8, a, NEPTUNE_A, 4.2e-7);
}

//-------------------------------------------------------------------------

TEST(VSOP87, VSPO87C_Mercury)
{
	VSOP87_RECT_TEST(1, c, MERCURY_C, 6e-9);
}

TEST(VSOP87, VSPO87C_Venus)
{
	VSOP87_RECT_TEST(2, c, VENUS_C, 2.5e-8);
}

TEST(VSOP87, VSPO87C_Earth)
{
	VSOP87_RECT_TEST(3, c, EARTH_C, 1e-8);
}

TEST(VSOP87, VSPO87C_Mars)
{
	VSOP87_RECT_TEST(4, c, MARS_C, 1e-7);
}

TEST(VSOP87, VSPO87C_Jupiter)
{
	VSOP87_RECT_TEST(5, c, JUPITER_C, 3.5e-7);
}

TEST(VSOP87, VSPO87C_Saturn)
{
	VSOP87_RECT_TEST(6, c, SATURN_C, 7e-7);
}

TEST(VSOP87, VSPO87C_Uranus)
{
	VSOP87_RECT_TEST(7, c, URANUS_C, 8e-5);
}

TEST(VSOP87, VSPO87C_Neptune)
{
	VSOP87_RECT_TEST(8, c, NEPTUNE_C, 5e-5);
}

//-------------------------------------------------------------------------

#undef HMS_TO_RAD
#undef DEC_TO_RAD

#define HMS_TO_RAD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 12 * M_PI)
#define DEC_TO_RAD(d, m, s) ((abs(d) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 180 * M_PI)

#define KM_TO_AU(km) (static_cast<double>(km) / 149597870.700)

// January 1, 2022, 0:00 UTC
static const double JD0 = 2459580.5 + 69 / 86400.0;

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

static std::string radToString(double rad)
{
	int i = (fabs(rad) / M_PI * 12 * 3600 + 0.5);
	
	std::ostringstream s;
	s << i / 3600 << " h " << (i / 60) % 60 << " m " << (i % 60) << " s ";

	i = (fabs(rad) / M_PI * 180 * 3600 + 0.5);
	s << i / 3600 << " d " << (i / 60) % 60 << " m " << (i % 60) << " s ";

	return s.str();
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

#define VSOP87_TEST_J2000(PlanetID, posRA, posDEC, epsRA, epsDEC) \
	\
	tVSOP87_Rect planet, earth; \
	EXPECT_EQ(vsop87a((PlanetID), JD0, &planet), 0); \
	EXPECT_EQ(vsop87a(3, JD0, &earth), 0); \
		\
	CVector3d dist = CVector3d(planet.X[0], planet.X[1], planet.X[2]) - CVector3d(earth.X[0], earth.X[1], earth.X[2]); \
	CVector3d ap = Utils::aberrationPush(dist.length(), CVector3d(earth.X[3], earth.X[4], earth.X[5])); \
	CEquCoordinates pos(Utils::vsop87ToFK5(dist + ap)); \
	double r = pos.rightAscension().radians(), d = pos.declination().radians(); \
    PrintAngularDist("Lon:", r, (posRA)); \
    PrintAngularDist("Lat:", d, (posDEC)); \
	EXPECT_LT(CompareAngles(r, (posRA)), (epsRA));\
	EXPECT_LT(CompareAngles(d, (posDEC)), (epsDEC));

TEST(VSOP87, Sun_J2000)
{
	static const double posRA = HMS_TO_RAD(18, 44, 29.6), posDEC = -DEC_TO_RAD(23, 02, 37.6);

	tVSOP87_Rect earth;
	EXPECT_EQ(vsop87a(3, JD0, &earth), 0);
	CVector3d dist = CVector3d(earth.X[0], earth.X[1], earth.X[2]) * (-1.0);
	CVector3d ap = Utils::aberrationPush(CVector3d(earth.X[0], earth.X[1], earth.X[2]).length(), CVector3d(earth.X[3], earth.X[4], earth.X[5]));
	CEquCoordinates pos(Utils::vsop87ToFK5(dist + ap));
	double r = pos.rightAscension().radians(), d = pos.declination().radians();
	PrintAngularDist("Lon:", r, (posRA));
	PrintAngularDist("Lat:", d, (posDEC));
	EXPECT_LT(CompareAngles(r, posRA), DEC_TO_RAD(0, 0, 5));
	EXPECT_LT(CompareAngles(d, posDEC), DEC_TO_RAD(0, 0, 5));
	EXPECT_NEAR(dist.length(), 0.98, 0.01);
}

TEST(VSOP87, Mercury_J2000) 
{
	static const double Mercury[2] = { 1.14, 0.78 };
	VSOP87_TEST_J2000(1, HMS_TO_RAD(20, 01, 25.5), -DEC_TO_RAD(22, 22, 08.0), 
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Venus_J2000)
{
	static const double Venus[2] = { 0.27, 0.02 };
	VSOP87_TEST_J2000(2, HMS_TO_RAD(19, 37, 13.2), -DEC_TO_RAD(18, 38, 20.4),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Mars_J2000)
{
	static const double Mars[2] = { 2.34, 0.98 };
	VSOP87_TEST_J2000(4, HMS_TO_RAD(16, 45, 20.4), -DEC_TO_RAD(22, 27, 40.0),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Jupiter_J2000)
{
	static const double Jupiter[1] = { 5.57 };
	VSOP87_TEST_J2000(5, HMS_TO_RAD(22, 10, 43.6), -DEC_TO_RAD(12, 19, 01.8),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Saturn_J2000)
{
	static const double Saturn[1] = { 14.94 };
	VSOP87_TEST_J2000(6, HMS_TO_RAD(20, 57, 10.2), -DEC_TO_RAD(18, 05, 46.7),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Uranus_J2000)
{
	static const double Uranus[1] = { 19.2 };
	VSOP87_TEST_J2000(7, HMS_TO_RAD(02, 33, 26.7), DEC_TO_RAD(14, 37, 51.2),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Neptune_J2000)
{
	static const double Neptune[1] = { 30.24 };
	VSOP87_TEST_J2000(8, HMS_TO_RAD(23, 26, 22.9), -DEC_TO_RAD(4, 51, 35.2),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

//-------------------------------------------------------------------------

#define VSOP87_TEST_DATE(PlanetID, posRA, posDEC, epsRA, epsDEC) \
	\
	tVSOP87_Rect planet, earth; \
	EXPECT_EQ(vsop87c((PlanetID), JD0, &planet), 0); \
	EXPECT_EQ(vsop87c(3, JD0, &earth), 0); \
		\
	CVector3d dist = CVector3d(planet.X[0], planet.X[1], planet.X[2]) - CVector3d(earth.X[0], earth.X[1], earth.X[2]); \
	CVector3d ap = Utils::aberrationPush(dist.length(), CVector3d(earth.X[3], earth.X[4], earth.X[5])); \
	CEquCoordinates pos(Utils::vsop87ToFK5(dist + ap)); \
	double r = pos.rightAscension().radians(), d = pos.declination().radians(); \
	PrintAngularDist("Lon:", r, (posRA)); \
	PrintAngularDist("Lat:", d, (posDEC)); \
	EXPECT_LT(CompareAngles(r, (posRA)), (epsRA));\
	EXPECT_LT(CompareAngles(d, (posDEC)), (epsDEC));

TEST(VSOP87, Sun_DATE)
{
	static const double posRA = HMS_TO_RAD(18, 45, 48.6), posDEC = -DEC_TO_RAD(23, 1, 16.4);

	tVSOP87_Rect earth;
	EXPECT_EQ(vsop87c(3, JD0, &earth), 0);
	CVector3d dist = CVector3d(earth.X[0], earth.X[1], earth.X[2]) * (-1.0);
	CVector3d ap = Utils::aberrationPush(dist.length(), CVector3d(earth.X[3], earth.X[4], earth.X[5]));
	CEquCoordinates pos(Utils::vsop87ToFK5(dist + ap));
	double r = pos.rightAscension().radians(), d = pos.declination().radians();
	PrintAngularDist("Lon:", r, (posRA)); \
	PrintAngularDist("Lat:", d, (posDEC)); \
	EXPECT_LT(CompareAngles(r, posRA), HMS_TO_RAD(0, 0, 2));
	EXPECT_LT(CompareAngles(d, posDEC), DEC_TO_RAD(0, 0, 10));
	EXPECT_NEAR(dist.length(), 0.98, 0.01);
}

TEST(VSOP87, Mercury_DATE)
{
	static const double Mercury[2] = { 1.14, 0.78 };
	VSOP87_TEST_DATE(1, HMS_TO_RAD(20, 02, 42.6), -DEC_TO_RAD(22, 18, 30.4),
		HMS_TO_RAD(0, 0, 5), DEC_TO_RAD(0, 0, 10));
}

TEST(VSOP87, Venus_DATE)
{
	static const double Venus[2] = { 0.27, 0.02 };
	VSOP87_TEST_DATE(2, HMS_TO_RAD(19, 38, 28.8), -DEC_TO_RAD(18, 35, 24.3),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Mars_DATE)
{
	static const double Mars[2] = { 2.34, 0.98 };
	VSOP87_TEST_DATE(4, HMS_TO_RAD(16, 46, 38.6), -DEC_TO_RAD(22, 30, 02.0),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Jupiter_DATE)
{
	static const double Jupiter[1] = { 5.57 };
	VSOP87_TEST_DATE(5, HMS_TO_RAD(22, 11, 53.3), -DEC_TO_RAD(12, 12, 36.5),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Saturn_DATE)
{
	static const double Saturn[1] = { 14.94 };
	VSOP87_TEST_DATE(6, HMS_TO_RAD(20, 58, 23.8), -DEC_TO_RAD(18, 00, 44.8),
		DEC_TO_RAD(0, 0, 45), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Uranus_DATE)
{
	static const double Uranus[1] = { 19.2 };
	VSOP87_TEST_DATE(7, HMS_TO_RAD(02, 34, 38.2), DEC_TO_RAD(14, 43, 34.4),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}

TEST(VSOP87, Neptune_DATE)
{
	static const double Neptune[1] = { 30.24 };
	VSOP87_TEST_DATE(8, HMS_TO_RAD(23, 27, 30.1), -DEC_TO_RAD(4, 44, 25.0),
		DEC_TO_RAD(0, 0, 30), DEC_TO_RAD(0, 0, 30));
}
