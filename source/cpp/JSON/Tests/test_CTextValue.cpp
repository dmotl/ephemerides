/*!
*  \file      test_CTextValue.cpp
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
#include "CTextValue.h"

#include "gtest/gtest.h"

using namespace testing;

namespace JSON::Parser::Tests
{
    namespace Core
    {
        using tToken = JSON::Scanner::CToken;

        TEST(CTextValue, EmptyString)
        {
            CTextValue f(tToken(), "");

            bool ok = false;
            EXPECT_TRUE(f.toString(&ok) == "" && ok);
        }

        TEST(CTextValue, SimpleString)
        {
            CTextValue f(tToken(), "foo");

            bool ok = false;
            EXPECT_TRUE(f.toString(&ok) == "foo" && ok);
        }

        TEST(CTextValue, NumericValueAsString)
        {
            CTextValue f(tToken(), "1234");

            bool ok = false;
            EXPECT_TRUE(f.toInt(&ok) == 1234 && ok);
        }

        TEST(CTextValue, NumericValueAsString2)
        {
            CTextValue f(tToken(), "12.34");

            bool ok = false;
            EXPECT_TRUE(f.toDouble(&ok) == 12.34 && ok);
        }

        TEST(CTextValue, LogicValueAsString)
        {
            CTextValue f(tToken(), "true");

            bool ok = false;
            EXPECT_TRUE(f.toBool(&ok) == true && ok);
        }

        TEST(CTextValue, LogicValueAsString2)
        {
            CTextValue f(tToken(), "True");

            bool ok = false;
            EXPECT_TRUE(f.toBool(&ok) == true && ok);
        }

        TEST(CTextValue, LogicValueAsString3)
        {
            CTextValue f(tToken(), "1");

            bool ok = false;
            EXPECT_TRUE(f.toBool(&ok) == true && ok);
        }

        TEST(CTextValue, LogicValueAsString4)
        {
            CTextValue f(tToken(), "false");

            bool ok = false;
            EXPECT_TRUE(f.toBool(&ok) == false && ok);
        }

        TEST(CTextValue, LogicValueAsString5)
        {
            CTextValue f(tToken(), "False");

            bool ok = false;
            EXPECT_TRUE(f.toBool(&ok) == false && ok);
        }

        TEST(CTextValue, LogicValueAsString6)
        {
            CTextValue f(tToken(), "0");

            bool ok = false;
            EXPECT_TRUE(f.toBool(&ok) == false && ok);
        }

        TEST(CTextValue, RGBColor_White)
        {
            QString str = QString::number(0xFFFFFFul);
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CTextValue, RGBColor_Black)
        {
            QString str = QString::number(0ul);
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CTextValue, RGBColor_Gray)
        {
            QString str = QString::number(0x808080ul);
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CTextValue, RGBColor_Red)
        {
            QString str = QString::number(0xFF0000ul);
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CTextValue, RGBColor_Green)
        {
            QString str = QString::number(0x00FF00ul);
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CTextValue, RGBColor_Blue)
        {
            QString str = QString::number(0x0000FFul);
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }

        TEST(CTextValue, RGBColor_White_Hex)
        {
            QString str = QStringLiteral("#FFFFFF");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CTextValue, RGBColor_Black_Hex)
        {
            QString str = QStringLiteral("#000000");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CTextValue, RGBColor_Gray_Hex)
        {
            QString str = QStringLiteral("#808080");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CTextValue, RGBColor_Red_Hex)
        {
            QString str = QStringLiteral("#FF0000");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CTextValue, RGBColor_Green_Hex)
        {
            QString str = QStringLiteral("#00FF00");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CTextValue, RGBColor_Blue_Hex)
        {
            QString str = QStringLiteral("#0000FF");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }

        TEST(CTextValue, RGBColor_White_3C)
        {
            QString str = QStringLiteral("255 255 255");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CTextValue, RGBColor_Black_3C)
        {
            QString str = QStringLiteral("0 0 0");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CTextValue, RGBColor_Gray_3C)
        {
            QString str = QStringLiteral("128 128 128");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CTextValue, RGBColor_Red_3C)
        {
            QString str = QStringLiteral("255 0 0");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CTextValue, RGBColor_Green_3C)
        {
            QString str = QStringLiteral("0 255 0");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CTextValue, RGBColor_Blue_3C)
        {
            QString str = QStringLiteral("0 0 255");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }

        TEST(CTextValue, RGBColor_White_Names)
        {
            QString str = QStringLiteral("white");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CTextValue, RGBColor_Black_Names)
        {
            QString str = QStringLiteral("black");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CTextValue, RGBColor_Gray_Names)
        {
            QString str = QStringLiteral("gray");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CTextValue, RGBColor_Red_Names)
        {
            QString str = QStringLiteral("red");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CTextValue, RGBColor_Green_Names)
        {
            QString str = QStringLiteral("lime");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CTextValue, RGBColor_Blue_Names)
        {
            QString str = QStringLiteral("blue");
            CTextValue f(tToken(), str);

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }
    }
}
