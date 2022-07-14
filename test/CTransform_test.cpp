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

#define _USE_MATH_DEFINES

#include <math.h>

#include "CTransform.h"

TEST(CTransform, default_constructor)
{
	CTransform<int> t;
	EXPECT_EQ(t.at(0, 0), 1);
	EXPECT_EQ(t.at(0, 1), 0);
	EXPECT_EQ(t.at(0, 2), 0);

	EXPECT_EQ(t.at(1, 0), 0);
	EXPECT_EQ(t.at(1, 1), 1);
	EXPECT_EQ(t.at(1, 2), 0);

	EXPECT_EQ(t.at(2, 0), 0);
	EXPECT_EQ(t.at(2, 1), 0);
	EXPECT_EQ(t.at(2, 2), 1);
}

TEST(CTransform, from_values)
{
	CTransform<int> t(1, 2, 3, 4, 5, 6);
	EXPECT_EQ(t.at(0, 0), 1);
	EXPECT_EQ(t.at(0, 1), 2);
	EXPECT_EQ(t.at(0, 2), 0);

	EXPECT_EQ(t.at(1, 0), 3);
	EXPECT_EQ(t.at(1, 1), 4);
	EXPECT_EQ(t.at(1, 2), 0);

	EXPECT_EQ(t.at(2, 0), 5);
	EXPECT_EQ(t.at(2, 1), 6);
	EXPECT_EQ(t.at(2, 2), 1);

	EXPECT_EQ(t.dx(), 5);
	EXPECT_EQ(t.dy(), 6);
}

TEST(CTransform, identity)
{
	CTransform<int> t = CMatrix3<int>::identity();
	EXPECT_EQ(t.at(0, 0), 1);
	EXPECT_EQ(t.at(0, 1), 0);
	EXPECT_EQ(t.at(0, 2), 0);

	EXPECT_EQ(t.at(1, 0), 0);
	EXPECT_EQ(t.at(1, 1), 1);
	EXPECT_EQ(t.at(1, 2), 0);

	EXPECT_EQ(t.at(2, 0), 0);
	EXPECT_EQ(t.at(2, 1), 0);
	EXPECT_EQ(t.at(2, 2), 1);
}

TEST(CTransform, dxdy)
{
	CTransform<int> t(1, 0, 0, 1, 5, 6);
	EXPECT_EQ(t.dx(), 5);
	EXPECT_EQ(t.dy(), 6);
}

TEST(CTransform, reset)
{
	CTransform<int> t(1, 2, 3, 4, 5, 6);
	t.reset();
	EXPECT_EQ(t, CTransform<int>::identity());
}

TEST(CTransform, equal)
{
	CTransform<int> t(1, 2, 3, 4, 5, 6);
	EXPECT_EQ(t, t);
}

TEST(CTransform, product)
{
	CTransform<int> t(1, 2, 3, 4, 5, 6);
	EXPECT_EQ(t * CTransform<int>(), t);
	EXPECT_EQ(CTransform<int>() * t, t);
}

TEST(CTransform, product_assign)
{
	CTransform<int> t(1, 2, 3, 4, 5, 6);
	EXPECT_EQ(t *= CTransform<int>(), t);
	EXPECT_EQ(CTransform<int>() *= t, t);
}

TEST(CTransform, from_scale)
{
	CTransform<int> t = CTransform<int>::fromScale(2, 3);
	EXPECT_EQ(t.m11(), 2);
	EXPECT_EQ(t.m22(), 3);
}

TEST(CTransform, from_translate)
{
	CTransform<int> t = CTransform<int>::fromTranslate(2, 3);
	EXPECT_EQ(t.dx(), 2);
	EXPECT_EQ(t.dy(), 3);
}

TEST(CTransform, from_rotation)
{
	CTransform<double> t = CTransform<double>::fromRotation(M_PI_2);
	EXPECT_EQ(t.m11(), 0.5 * sqrt(2.0));
	EXPECT_EQ(t.m12(), 0.5 * sqrt(2.0));
	EXPECT_EQ(t.m21(), 0.5 * sqrt(2.0));
	EXPECT_EQ(t.m22(), 0.5 * sqrt(2.0));
}
