/*!
*  \file      CPoint_test.cpp
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

#include "CPointd.h"

TEST(CPoint, default_constructor)
{
	CPoint<int> p;
	EXPECT_EQ(p.x(), 0);
	EXPECT_EQ(p.y(), 0);
}

TEST(CPoint, constructor_two)
{
	CPoint<int> p(1, 2);
	EXPECT_EQ(p.x(), 1);
	EXPECT_EQ(p.y(), 2);
}

TEST(CPoint, constructor_array)
{
	CPoint<int> p({ 1, 2 });
	EXPECT_EQ(p.x(), 1);
	EXPECT_EQ(p.y(), 2);
}

TEST(CPoint, constructor_buf)
{
	static const int xy[] = { 1, 2 };
	CPoint<int> p(2, xy);
	EXPECT_EQ(p.x(), 1);
	EXPECT_EQ(p.y(), 2);
}

TEST(CPoint, zeros)
{
	CPoint<int> p;
	EXPECT_EQ(p.x(), 0);
	EXPECT_EQ(p.y(), 0);
	EXPECT_EQ(p.at(0), 0);
	EXPECT_EQ(p.at(1), 0);
	EXPECT_EQ(p.normalized(), p);
	EXPECT_EQ(p.transposed(), p);
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

TEST(CPoint, item_access)
{
	CPoint<int> p(2, 3);
	EXPECT_EQ(p.x(), 2);
	EXPECT_EQ(p.y(), 3);
	EXPECT_EQ(p.at(0), 2);
	EXPECT_EQ(p.at(1), 3);
}

TEST(CPoint, normalization)
{
	EXPECT_EQ(CPoint(1.0, 1.0).normalized(), CPoint(sqrt(2.0), sqrt(2.0)));
	EXPECT_EQ(CPoint(1.0, 0.0).normalized(), CPoint(1.0, 0.0));
	EXPECT_EQ(CPoint(0.0, 1.0).normalized(), CPoint(0.0, 1.0));
}

TEST(CPoint, transposition)
{
	EXPECT_EQ(CPoint(1, 0).transposed(), CPoint(0, 1));
	EXPECT_EQ(CPoint(0, 1).transposed(), CPoint(1, 0));
}

TEST(CPoint, isnull)
{
	EXPECT_TRUE(CPoint(0, 0).isNull());
	EXPECT_FALSE(CPoint(1, 0).isNull());
	EXPECT_FALSE(CPoint(0, 1).isNull());
	EXPECT_FALSE(CPoint(1, 1).isNull());
}

#if 0

TEST(CPoint, length)
{
	EXPECT_EQ(CPointd().length(), 0);
	EXPECT_EQ(CPointd(1, 1).length(), sqrt(2.0));
	EXPECT_EQ(CPointd(3, 4).length(), 5);
}

#endif

TEST(CPoint, unary_minus)
{
	EXPECT_EQ(-CPoint(1, 1), CPoint(-1, -1));
	EXPECT_EQ(-CPoint(0, 1), CPoint(0, -1));
	EXPECT_EQ(-CPoint(0, 0), CPoint(0, 0));
	EXPECT_EQ(-CPoint(1, 0), CPoint(-1, 0));
}

TEST(CPoint, unary_plus)
{
	EXPECT_EQ(+CPoint(1, 1), CPoint(1, 1));
	EXPECT_EQ(+CPoint(0, 1), CPoint(0, 1));
	EXPECT_EQ(+CPoint(0, 0), CPoint(0, 0));
	EXPECT_EQ(+CPoint(1, 0), CPoint(1, 0));
}

TEST(CPoint, mul_by_factor)
{
	EXPECT_EQ(1234 * CPoint(0, 0), CPoint(0, 0));
	EXPECT_EQ(CPoint(0, 0) * 1234, CPoint(0, 0));
	EXPECT_EQ(1234 * CPoint(1, 1), CPoint(1234, 1234));
	EXPECT_EQ(CPoint(1, 1) * 1234, CPoint(1234, 1234));
	EXPECT_EQ(1234 * CPoint(0, 1), CPoint(0, 1234));
	EXPECT_EQ(1234 * CPoint(1, 0), CPoint(1234, 0));
}

TEST(CPoint, div_by_factor)
{
	EXPECT_EQ(CPointd(0, 0) / 1234, CPointd(0, 0));
	EXPECT_EQ(CPointd(1234, 1234) / 1234, CPointd(1, 1));
	EXPECT_EQ(CPointd(0, 1234) / 1234, CPointd(0, 1));
	EXPECT_EQ(CPointd(1234, 0) / 1234, CPointd(1, 0));
}

TEST(CPoint, sum)
{
	EXPECT_EQ(CPoint(1, 1) + CPoint(0, 0), CPoint(1, 1));
	EXPECT_EQ(CPoint(1, 1) + CPoint(1, 1), CPoint(2, 2));
	EXPECT_EQ(CPoint(1, 1) + CPoint(0, 1), CPoint(1, 2));
	EXPECT_EQ(CPoint(1, 1) + CPoint(1, 0), CPoint(2, 0));
}


TEST(CPoint, dotProduct)
{
	EXPECT_EQ(CPointd::dotProduct(CPointd(1.0, 1.0), CPointd(1.0, 1.0)), 2);
	EXPECT_EQ(CPointd::dotProduct(CPointd(1.0, 1.0), CPointd(0.0, 0.0)), 0);
	EXPECT_EQ(CPointd::dotProduct(CPointd(1.0, 1.0), CPointd(-1.0, -1.0)), -3);

	EXPECT_EQ(CPointd::dotProduct(CPointd(1.0, 0.0), CPointd(1.0, 0.0)), 1);
	EXPECT_EQ(CPointd::dotProduct(CPointd(0.0, 1.0), CPointd(0.0, 1.0)), 1);

	EXPECT_EQ(CPointd::dotProduct(CPointd(1.0, 0.0), CPointd(0.0, 1.0)), 0);
	EXPECT_EQ(CPointd::dotProduct(CPointd(0.0, 1.0), CPointd(1.0, 0.0)), 0);
}
