/*!
*  \file      CLatitude_test.cpp
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

#include "CLatitude.h"

#define DEG_TO_RAD(d) ((d) / 180 * M_PI)

// Brno
static const double LAT_DEG = 49.1944631 / 180 * M_PI; // 49d 11m 40.07s
static const double LAT_RAD = DEG_TO_RAD(LAT_DEG);

static double CompareAngles(double alpha, double beta)
{
	if (alpha > M_PI)
		alpha = M_PI;
	if (alpha < -M_PI)
		alpha = -M_PI;
	if (beta > M_PI)
		beta = M_PI;
	if (beta < -M_PI)
		beta = -M_PI;

	return fabs(alpha - beta);
}

TEST(CLatitude, fromDegrees)
{
	CLatitude lon = CLatitude::fromDegrees(LAT_DEG);
	EXPECT_TRUE(lon.isValid());
	EXPECT_NEAR(lon.radians(), LAT_RAD, 1e-6);
	EXPECT_NEAR(lon.degrees(), LAT_DEG, 1e-6);
}

TEST(CLatitude, fromRadians)
{
	CLatitude lon(LAT_RAD);
	EXPECT_TRUE(lon.isValid());
	EXPECT_NEAR(lon.radians(), LAT_RAD, 1e-6);
	EXPECT_NEAR(lon.degrees(), LAT_DEG, 1e-6);
}

TEST(CLatitude, setDegrees)
{
	CLatitude lon;
	lon.setDegrees(LAT_DEG);
	EXPECT_TRUE(lon.isValid());
	EXPECT_NEAR(lon.radians(), LAT_RAD, 1e-6);
	EXPECT_NEAR(lon.degrees(), LAT_DEG, 1e-6);
}

TEST(CLatitude, setRadians)
{
	CLatitude lon;
	lon.setRadians(LAT_RAD);
	EXPECT_TRUE(lon.isValid());
	EXPECT_NEAR(lon.radians(), LAT_RAD, 1e-6);
	EXPECT_NEAR(lon.degrees(), LAT_DEG, 1e-6);
}

TEST(CLatitude, invalidValue)
{
	CLatitude lon;
	EXPECT_FALSE(lon.isValid());
}

