/*!
*  \file      CLongitude_test.cpp
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

#include "CLongitude.h"

#define DEG_TO_RAD(d) ((d) / 180 * M_PI)

// Brno
static const double LON_DEG = 16.6103878; // 16d 36m 37.40s
static const double LON_RAD = DEG_TO_RAD(LON_DEG);

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

TEST(CLongitude, fromDegrees)
{
	CLongitude lon = CLongitude::fromDegrees(LON_DEG);
	EXPECT_TRUE(lon.isValid());
	EXPECT_NEAR(lon.radians(), LON_RAD, 1e-6);
	EXPECT_NEAR(lon.degrees(), LON_DEG, 1e-6);
}

TEST(CLongitude, fromRadians)
{
	CLongitude lon(LON_RAD);
	EXPECT_TRUE(lon.isValid());
	EXPECT_NEAR(lon.radians(), LON_RAD, 1e-6);
	EXPECT_NEAR(lon.degrees(), LON_DEG, 1e-6);
}

TEST(CLongitude, setDegrees)
{
	CLongitude lon;
	lon.setDegrees(LON_DEG);
	EXPECT_TRUE(lon.isValid());
	EXPECT_NEAR(lon.radians(), LON_RAD, 1e-6);
	EXPECT_NEAR(lon.degrees(), LON_DEG, 1e-6);
}

TEST(CLongitude, setRadians)
{
	CLongitude lon;
	lon.setRadians(LON_RAD);
	EXPECT_TRUE(lon.isValid());
	EXPECT_NEAR(lon.radians(), LON_RAD, 1e-6);
	EXPECT_NEAR(lon.degrees(), LON_DEG, 1e-6);
}

TEST(CLongitude, invalidValue)
{
	CLongitude lon;
	EXPECT_FALSE(lon.isValid());
}

