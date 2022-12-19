/*!
*  \file      CBSC1991_test.cpp
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

#include "CBSC1991.h"

#include "tests_config.h"

#undef RA_TO_RAD
#define RA_TO_RAD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 12 * M_PI)

#undef DEC_TO_RAD
#define DEC_TO_RAD(d, m, s) ((abs(d) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 180 * M_PI)

/*2491  9Alp CMaBD-16 1591  48915151881 257I   5423           064044.6-163444064508.9-164258227.22-08.88-1.46   0.00 -0.05 -0.03   A1Vm               -0.553-1.205 +.375-008SBO    13 10.3  11.2AB   4* */
static const double Sirius[3] = { RA_TO_RAD(06, 45, 08.9), -DEC_TO_RAD(16, 42, 58), -1.46 };

TEST(CBSC1991_Embedded, Size)
{
	CBSC1991_Embedded file;

	EXPECT_EQ(file.data().size(), 9096);
}

TEST(CBSC1991_Embedded, Sirius)
{
	CBSC1991_Embedded file;

	CBSC1991_Embedded::CObject* obj = file.find_bs(2491);
	EXPECT_FALSE(obj == nullptr);
	EXPECT_NEAR(obj->equatorialJ2000().rightAscension().radians(), Sirius[0], 1e-6);
	EXPECT_NEAR(obj->equatorialJ2000().declination().radians(), Sirius[1], 1e-6);
	EXPECT_NEAR(obj->magnitude(), Sirius[2], 1e-6);
}
