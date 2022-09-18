/*!
*  \file      test_CNumericValue.cpp
*  \author    David Motl
*  \date      2022-09-18
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
#include "CNumericValue.h"

#include "gtest/gtest.h"

using namespace testing;

namespace JSON::Parser::Tests
{
    namespace Core
    {
        using tToken = JSON::Scanner::CToken;

        TEST(CNumericValue, Zero)
        {
            CNumericValue f(tToken(), "0");

            bool ok = false;
            EXPECT_TRUE(f.toInt(&ok) == 0 && ok);
        }

        TEST(CNumericValue, PositiveValue)
        {
            CNumericValue f(tToken(), "1234");

            bool ok = false;
            EXPECT_TRUE(f.toInt(&ok) == 1234 && ok);
        }

        TEST(CNumericValue, NegativeValue)
        {
            CNumericValue f(tToken(), "-1234");

            bool ok = false;
            EXPECT_TRUE(f.toInt(&ok) == -1234 && ok);
        }

        TEST(CNumericValue, DecimalNumber)
        {
            CNumericValue f(tToken(), "0.5");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == 0.5 && ok);
        }

        TEST(CNumericValue, DecimalNumber2)
        {
            CNumericValue f(tToken(), ".5");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == 0.5 && ok);
        }

        TEST(CNumericValue, NegativeDecimalNumber)
        {
            CNumericValue f(tToken(), "-0.5");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == -0.5 && ok);
        }

        TEST(CNumericValue, NegativeDecimalNumber2)
        {
            CNumericValue f(tToken(), "-.5");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == -.5 && ok);
        }

        TEST(CNumericValue, ExponentialNumber)
        {
            CNumericValue f(tToken(), "1e5");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == 1e5 && ok);
        }

        TEST(CNumericValue, ExponentialNumber2)
        {
            CNumericValue f(tToken(), "1e-5");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == 1e-5 && ok);
        }

        TEST(CNumericValue, NegativeExponentialNumber)
        {
            CNumericValue f(tToken(), "-1e5");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == -1e5 && ok);
        }

        TEST(CNumericValue, NegativeExponentialNumber2)
        {
            CNumericValue f(tToken(), "-1e-5");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == -1e-5 && ok);
        }

        TEST(CNumericValue, HexNumber)
        {
            CNumericValue f(tToken(), "0x1234abcd");

            bool ok = false;
            EXPECT_TRUE(f.toInt(&ok) == 0x1234abcd && ok);
        }

        TEST(CNumericValue, RGBColor_White)
        {
            QString str = QString::number(0xFFFFFFul);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CNumericValue, RGBColor_Black)
        {
            QString str = QString::number(0ul);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CNumericValue, RGBColor_Gray)
        {
            QString str = QString::number(0x808080ul);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CNumericValue, RGBColor_Red)
        {
            QString str = QString::number(0xFF0000ul);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CNumericValue, RGBColor_Green)
        {
            QString str = QString::number(0x00FF00ul);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CNumericValue, RGBColor_Blue)
        {
            QString str = QString::number(0x0000FFul);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }

        TEST(CNumericValue, RGBColor_White_Hex)
        {
            QString str = QStringLiteral("0x") + QString::number(0xFFFFFFul, 16);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CNumericValue, RGBColor_Black_Hex)
        {
            QString str = QStringLiteral("0x") + QString::number(0ul, 16);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CNumericValue, RGBColor_Gray_Hex)
        {
            QString str = QStringLiteral("0x") + QString::number(0x808080ul, 16);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CNumericValue, RGBColor_Red_Hex)
        {
            QString str = QStringLiteral("0x") + QString::number(0xFF0000ul, 16);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CNumericValue, RGBColor_Green_Hex)
        {
            QString str = QStringLiteral("0x") + QString::number(0x00FF00ul, 16);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CNumericValue, RGBColor_Blue_Hex)
        {
            QString str = QStringLiteral("0x") + QString::number(0x0000FFul, 16);
            CNumericValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }
    }
}
