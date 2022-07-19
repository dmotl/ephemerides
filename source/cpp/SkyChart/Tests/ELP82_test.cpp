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

#include "elp82.h"
#include "elp82_chk.h"

// astronomical unit (m)
#define AU 149597870691.0

#define KM_TO_AU(km) ((km) * 1000.0 / AU)

TEST(ELP82, ELP82_Moon)
{
	static const tELP82TestXYZ* tab = elp82_MOON_A; 
	int size = sizeof(elp82_MOON_A) / sizeof(tELP82TestXYZ);
	static const double error = 3.5e-7; // AU

	for (int i = 0; i < size; i++) {
		tELP82_Rect out; 
		EXPECT_EQ(elp82b(0, tab[i].jd, &out), 0); 
		EXPECT_NEAR(out.X[0], KM_TO_AU(tab[i].X), error);
		EXPECT_NEAR(out.X[1], KM_TO_AU(tab[i].Y), error);
		EXPECT_NEAR(out.X[2], KM_TO_AU(tab[i].Z), error);
	}
}
