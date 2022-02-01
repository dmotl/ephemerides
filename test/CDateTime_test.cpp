/*!
*  \file      CDateTime_test.cpp
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

#include "CDateTime.h"

// January 1, 2022, 0:00 UTC
static const double JD0 = 2459580.5;

TEST(CDateTime, InvalidDT) {
	EXPECT_FALSE(CDateTime().isValid());
}

TEST(CDateTime, InvalidDT2) {
	EXPECT_EQ(CDateTime().toJD(), 0);
}

TEST(CDateTime, ToJD) {
	double jd = CDateTime(2022, 1, 1, 0, 0, 0, 0).toJD();
	EXPECT_EQ(jd, JD0);
}

TEST(CDateTime, FromJD) {
	CDateTime dt(JD0);
	EXPECT_EQ(dt.year(), 2022);
	EXPECT_EQ(dt.month(), 1);
	EXPECT_EQ(dt.day(), 1);
	EXPECT_EQ(dt.hour(), 0);
	EXPECT_EQ(dt.minute(), 0);
	EXPECT_EQ(dt.second(), 0);
	EXPECT_EQ(dt.millisecond(), 0);
}
