/*!
*  \file      CVector3_test.cpp
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

#include <QtGui>

#if 0

#define _USE_MATH_DEFINES

#include <math.h>

#endif

#include "CVector3.h"

using CVector3d = QVector3D;

TEST(CVector3, default_constructor)
{
	CVector3<int> p;
	EXPECT_EQ(p.x(), 0);
	EXPECT_EQ(p.y(), 0);
	EXPECT_EQ(p.z(), 0);
}

TEST(CVector3, from_point)
{
	CVector3<int> p(CPoint(2, 3), 4);
	EXPECT_EQ(p.x(), 2);
	EXPECT_EQ(p.y(), 3);
	EXPECT_EQ(p.z(), 4);
}

TEST(CVector3, constructor_three)
{
	CVector3<int> p(1, 2, 3);
	EXPECT_EQ(p.x(), 1);
	EXPECT_EQ(p.y(), 2);
	EXPECT_EQ(p.z(), 3);
}

TEST(CVector3, constructor_array)
{
	CVector3<int> p({ 1, 2, 3 });
	EXPECT_EQ(p.x(), 1);
	EXPECT_EQ(p.y(), 2);
	EXPECT_EQ(p.z(), 3);
}

TEST(CVector3, constructor_buf)
{
	static const int xyz[] = { 1, 2, 3 };
	CVector3<int> p(3, xyz);
	EXPECT_EQ(p.x(), 1);
	EXPECT_EQ(p.y(), 2);
	EXPECT_EQ(p.z(), 2);
}

TEST(CVector3, to_point)
{
	EXPECT_EQ(CVector3<int>(1, 2, 3).toPoint(), CPoint(1, 2));
}

TEST(CVector3, zeros)
{
	CVector3<int> p;
	EXPECT_EQ(p.x(), 0);
	EXPECT_EQ(p.y(), 0);
	EXPECT_EQ(p.z(), 0);
	EXPECT_EQ(p.at(0), 0);
	EXPECT_EQ(p.at(1), 0);
	EXPECT_EQ(p.at(2), 0);
	EXPECT_EQ(p.normalized(), p);
	EXPECT_TRUE(p.isNull());
	EXPECT_EQ(p.length(), 0);
	EXPECT_EQ(-p, p);
	EXPECT_EQ(+p, p);
	EXPECT_EQ(1234 * p, p);
	EXPECT_EQ(p * 1234, p);
	EXPECT_EQ(p / 3, p);
	EXPECT_EQ(p / 3, p);
	EXPECT_EQ(p + p, p);
}

TEST(CVector3, item_access)
{
	CVector3<int> p(2, 3, 4);
	EXPECT_EQ(p.x(), 2);
	EXPECT_EQ(p.y(), 3);
	EXPECT_EQ(p.z(), 4);
	EXPECT_EQ(p.at(0), 2);
	EXPECT_EQ(p.at(1), 3);
	EXPECT_EQ(p.at(2), 4);
}

TEST(CVector3, normalization)
{
	EXPECT_EQ(CVector3(1.0, 1.0, 0.0).normalized(), CVector3(sqrt(2.0), sqrt(2.0), 0.0));
	EXPECT_EQ(CVector3(1.0, 0.0, 1.0).normalized(), CVector3(sqrt(2.0), 0.0, sqrt(2.0)));
	EXPECT_EQ(CVector3(0.0, 1.0, 1.0).normalized(), CVector3(0.0, sqrt(2.0), sqrt(2.0)));

	EXPECT_EQ(CVector3(1.0, 0.0, 0.0).normalized(), CVector3(1.0, 0.0, 0.0));
	EXPECT_EQ(CVector3(0.0, 0.0, 1.0).normalized(), CVector3(0.0, 0.0, 1.0));
	EXPECT_EQ(CVector3(0.0, 1.0, 0.0).normalized(), CVector3(0.0, 1.0, 0.0));
}

TEST(CVector3, isnull)
{
	EXPECT_TRUE(CVector3(0, 0, 0).isNull());
	EXPECT_FALSE(CVector3(1, 0, 0).isNull());
	EXPECT_FALSE(CVector3(0, 1, 0).isNull());
	EXPECT_FALSE(CVector3(0, 0, 1).isNull());
}

TEST(CVector3, length)
{
	EXPECT_EQ(CVector3d().length(), 0);
	EXPECT_EQ(CVector3d(1, 1, 1).length(), sqrt(3.0));
	EXPECT_EQ(CVector3d(3, 4, 5).length(), sqrt(9.0 + 16.0 + 25.0));
}

TEST(CVector3, unary_minus)
{
	EXPECT_EQ(-CVector3(1, 1, 1), CVector3(-1, -1, -1));
	EXPECT_EQ(-CVector3(0, 0, 0), CVector3(0, 0, 0));
	EXPECT_EQ(-CVector3(1, 0, 0), CVector3(-1, 0, 0));
	EXPECT_EQ(-CVector3(0, 1, 0), CVector3(0, -1, 0));
	EXPECT_EQ(-CVector3(0, 0, 1), CVector3(0, 0, -1));
	EXPECT_EQ(-CVector3(1, 1, 0), CVector3(0, -1, -1));
	EXPECT_EQ(-CVector3(0, 1, 1), CVector3(0, -1, -1));
	EXPECT_EQ(-CVector3(1, 0, 1), CVector3(-1, 0, -1));
}

TEST(CVector3, unary_plus)
{
	EXPECT_EQ(+CVector3(1, 1, 1), CVector3(1, 1, 1));
	EXPECT_EQ(+CVector3(0, 0, 0), CVector3(0, 0, 0));
	EXPECT_EQ(+CVector3(1, 0, 0), CVector3(1, 0, 0));
	EXPECT_EQ(+CVector3(0, 1, 0), CVector3(0, 1, 0));
	EXPECT_EQ(+CVector3(0, 0, 1), CVector3(0, 0, 1));
	EXPECT_EQ(+CVector3(1, 1, 0), CVector3(0, 1, 1));
	EXPECT_EQ(+CVector3(0, 1, 1), CVector3(0, 1, 1));
	EXPECT_EQ(+CVector3(1, 0, 1), CVector3(1, 0, 1));
}

TEST(CVector3, mul_by_factor)
{
	EXPECT_EQ(1234 * CVector3(0, 0, 0), CVector3(0, 0, 0));
	EXPECT_EQ(CVector3(0, 0, 0) * 1234, CVector3(0, 0, 0));
	EXPECT_EQ(1234 * CVector3(1, 1, 1), CVector3(1234, 1234, 1234));
	EXPECT_EQ(CVector3(1, 1, 1) * 1234, CVector3(1234, 1234, 1234));
	EXPECT_EQ(1234 * CVector3(0, 1, 1), CVector3(0, 1234, 1234));
	EXPECT_EQ(1234 * CVector3(1, 0, 1), CVector3(1234, 0, 1234));
	EXPECT_EQ(1234 * CVector3(0, 1, 0), CVector3(0, 1234, 0));
	EXPECT_EQ(1234 * CVector3(1, 0, 0), CVector3(1234, 0, 0));
	EXPECT_EQ(1234 * CVector3(0, 0, 1), CVector3(0, 0, 1234));
}

TEST(CVector3, div_by_factor)
{
	EXPECT_EQ(CVector3d(0, 0, 0) / 1234, CVector3d(0, 0, 0));
	EXPECT_EQ(CVector3d(1234, 1234, 1234) / 1234, CVector3d(1, 1, 1));
	EXPECT_EQ(CVector3d(0, 1234, 1234) / 1234, CVector3d(0, 1, 1));
	EXPECT_EQ(CVector3d(1234, 0, 1234) / 1234, CVector3d(1, 0, 1));
	EXPECT_EQ(CVector3d(0, 1234, 0) / 1234, CVector3d(0, 1, 0));
	EXPECT_EQ(CVector3d(1234, 0, 0) / 1234, CVector3d(1, 0, 0));
	EXPECT_EQ(CVector3d(0, 0, 1234) / 1234, CVector3d(0, 0, 1));
}

TEST(CVector3, sum)
{
	EXPECT_EQ(CVector3(1, 1, 1) + CVector3(0, 0, 0), CVector3(1, 1, 1));
	EXPECT_EQ(CVector3(1, 1, 1) + CVector3(1, 1, 1), CVector3(2, 2, 2));
	EXPECT_EQ(CVector3(1, 1, 1) + CVector3(0, 1, 1), CVector3(1, 2, 2));
	EXPECT_EQ(CVector3(1, 1, 1) + CVector3(1, 0, 1), CVector3(2, 0, 2));
	EXPECT_EQ(CVector3(1, 1, 1) + CVector3(1, 0, 0), CVector3(2, 1, 1));
	EXPECT_EQ(CVector3(1, 1, 1) + CVector3(0, 1, 0), CVector3(1, 2, 1));
	EXPECT_EQ(CVector3(1, 1, 1) + CVector3(0, 0, 1), CVector3(1, 1, 2));
}

TEST(CVector3, dotProduct)
{
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(1.0, 1.0, 1.0), CVector3d(1.0, 1.0, 1.0)), 3);
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(1.0, 1.0, 1.0), CVector3d(0.0, 0.0, 0.0)), 0);
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(1.0, 1.0, 1.0), CVector3d(-1.0, -1.0, -1.0)), -3);

	EXPECT_EQ(CVector3d::dotProduct(CVector3d(1.0, 0.0, 0.0), CVector3d(1.0, 0.0, 0.0)), 1);
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(0.0, 1.0, 0.0), CVector3d(0.0, 1.0, 0.0)), 1);
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(0.0, 0.0, 1.0), CVector3d(0.0, 0.0, 1.0)), 1);

	EXPECT_EQ(CVector3d::dotProduct(CVector3d(1.0, 0.0, 0.0), CVector3d(0.0, 1.0, 0.0)), 0);
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(0.0, 1.0, 0.0), CVector3d(0.0, 0.0, 1.0)), 0);
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(0.0, 0.0, 1.0), CVector3d(1.0, 0.0, 0.0)), 0);

	EXPECT_EQ(CVector3d::dotProduct(CVector3d(1.0, 0.0, 0.0), CVector3d(0.0, 0.0, 1.0)), 0);
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(0.0, 1.0, 0.0), CVector3d(1.0, 0.0, 0.0)), 0);
	EXPECT_EQ(CVector3d::dotProduct(CVector3d(0.0, 0.0, 1.0), CVector3d(0.0, 1.0, 0.0)), 0);
}

TEST(CVector3, crossProduct)
{
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(1.0, 1.0, 1.0), CVector3d(1.0, 1.0, 1.0)), CVector3d());
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(1.0, 1.0, 1.0), CVector3d(0.0, 0.0, 0.0)), CVector3d());
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(1.0, 1.0, 1.0), CVector3d(-1.0, -1.0, -1.0)), CVector3d());

	EXPECT_EQ(CVector3d::crossProduct(CVector3d(1.0, 0.0, 0.0), CVector3d(1.0, 0.0, 0.0)), CVector3d());
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(0.0, 1.0, 0.0), CVector3d(0.0, 1.0, 0.0)), CVector3d());
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(0.0, 0.0, 1.0), CVector3d(0.0, 0.0, 1.0)), CVector3d());

	EXPECT_EQ(CVector3d::crossProduct(CVector3d(1.0, 0.0, 0.0), CVector3d(0.0, 1.0, 0.0)), CVector3d());
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(0.0, 1.0, 0.0), CVector3d(0.0, 0.0, 1.0)), CVector3d());
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(0.0, 0.0, 1.0), CVector3d(1.0, 0.0, 0.0)), CVector3d());

	EXPECT_EQ(CVector3d::crossProduct(CVector3d(1.0, 0.0, 0.0), CVector3d(0.0, 0.0, 1.0)), CVector3d());
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(0.0, 1.0, 0.0), CVector3d(1.0, 0.0, 0.0)), CVector3d());
	EXPECT_EQ(CVector3d::crossProduct(CVector3d(0.0, 0.0, 1.0), CVector3d(0.0, 1.0, 0.0)), CVector3d());
}
