/*!
*  \file      CNGC2000_test.cpp
*  \author    David Motl
*  \date      2022-03-22
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
#include <filesystem>

#include "CNGC2000.h"

#include "test_config.h"

#define RA_TO_RAD(h, m) (((h) + static_cast<double>(m) / 60) / 12 * M_PI)
#define DEC_TO_RAD(d, m) ((abs(d) + static_cast<double>(m) / 60) / 180 * M_PI)

/*    1  Gx  0 07.3  +27 43 s  Peg   1.9  13. p F, S, R, bet *11 and *14                          */
static const double NGC_1[3] = { RA_TO_RAD(0, 7.3), DEC_TO_RAD(27, 43), 13.0 };

/* I   1  D*  0 08.4  +27 43 x  Peg              D*, 13 & 13, one nebs */
static const double IC_1[3] = { RA_TO_RAD(0, 8.4), DEC_TO_RAD(27, 43), CNGC2000::invalidMagnitude() };

/*  1952  Nb  5 34.5  +22 01 s  Tau   6.    8.4  vB, vL, E 135deg +/- , vglbM, r; = M1              */
static const double M_1[3] = { RA_TO_RAD(5, 34.5), DEC_TO_RAD(22, 01), 8.4 };

/* Directory */
static const std::filesystem::path src_dir = std::filesystem::path(CMAKE_SOURCE_DIR).lexically_normal() / "share" / "ngc2000";

TEST(CNGC2000, Size)
{
	CNGC2000 file;

	EXPECT_TRUE(file.load(src_dir.string().c_str()));
	EXPECT_EQ(file.data().size(), 13226);
}

TEST(CNGC2000, NGC_1)
{
	CNGC2000 file;

	EXPECT_TRUE(file.load(src_dir.string().c_str()));

	CNGC2000::CObject* obj = file.find_ngc(1);
	EXPECT_FALSE(obj == nullptr);
	EXPECT_NEAR(obj->pos().rightAscension().radians(), NGC_1[0], 1e-6);
	EXPECT_NEAR(obj->pos().declination().radians(), NGC_1[1], 1e-6);
	EXPECT_NEAR(obj->magnitude(), NGC_1[2], 1e-6);
}

TEST(CNGC2000, IC_1)
{
	CNGC2000 file;

	EXPECT_TRUE(file.load(src_dir.string().c_str()));

	CNGC2000::CObject* obj = file.find_ic(1);
	EXPECT_FALSE(obj == nullptr);
	EXPECT_NEAR(obj->pos().rightAscension().radians(), IC_1[0], 1e-6);
	EXPECT_NEAR(obj->pos().declination().radians(), IC_1[1], 1e-6);
	EXPECT_NEAR(obj->magnitude(), IC_1[2], 1e-6);
}

TEST(CNGC2000, M_1)
{
	CNGC2000 file;

	EXPECT_TRUE(file.load(src_dir.string().c_str()));

	CNGC2000::CObject* obj = file.find_messier(1);
	EXPECT_FALSE(obj == nullptr);
	EXPECT_NEAR(obj->pos().rightAscension().radians(), M_1[0], 1e-6);
	EXPECT_NEAR(obj->pos().declination().radians(), M_1[1], 1e-6);
	EXPECT_NEAR(obj->magnitude(), M_1[2], 1e-6);
}
