/*!
*  \file      Utils_test.cpp
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

#include "Utils.h"

TEST(Utils, AngularDistance)
{
	double ra0 = 101.28750 / 180 * M_PI;   // 06 45 08.91728
	double dec0 = -16.716111 / 180 * M_PI; //  -16 42 58.0171
	double ra1 = 279.23333 / 180 * M_PI;   // 18 36 56.33635
	double dec1 = 38.783611 / 180 * M_PI;  //  +38 47 01.2802
	EXPECT_NEAR(Utils::AngularDistance(ra0, dec0, ra1, dec1), 157.8594 / 180 * M_PI, 0.0001);
}
