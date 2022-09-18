/*!
*  \file      test_CMapObject.cpp
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
#include "CObject.h"

#include "gtest/gtest.h"

#include "CNumericValue.h"

using namespace testing;

namespace JSON::Parser::Tests
{
    namespace Core
    {
        using tToken = JSON::Scanner::CToken;

        TEST(CObject, EmptyList)
        {
            CObject f;
            EXPECT_EQ(f.firstValue(""), static_cast<const CNode*>(nullptr));
            EXPECT_TRUE(f.isEmpty());
            EXPECT_FALSE(f.contains(""));
            EXPECT_EQ(f.keys().size(), 0);
            EXPECT_EQ(f.uniqueKeys().size(), 0);
            EXPECT_EQ(f.values("").size(), 0);
        }

        TEST(CObject, OneValue)
        {
            CObject f;
            f.insert("key", new CNumericValue(tToken(), "1"));
            EXPECT_FALSE(f.isEmpty());
            EXPECT_TRUE(f.contains("key"));
            EXPECT_FALSE(f.contains("key2"));
            EXPECT_EQ(f.keys().size(), 1);
            EXPECT_EQ(f.keys().first(), QStringLiteral("key"));
            EXPECT_EQ(f.uniqueKeys().size(), 1);
            EXPECT_EQ(f.uniqueKeys().first(), QStringLiteral("key"));
            EXPECT_EQ(f.values("key").size(), 1);
            EXPECT_EQ(f.values("key").first()->toString(), QStringLiteral("1"));
            EXPECT_EQ(f.values("key2").size(), 0);
        }

        TEST(CObject, TwoValues)
        {
            CObject f;
            f.insert("key1", new CNumericValue(tToken(), "1"));
            f.insert("key2", new CNumericValue(tToken(), "2"));
            EXPECT_FALSE(f.isEmpty());
            EXPECT_TRUE(f.contains("key1"));
            EXPECT_TRUE(f.contains("key2"));
            EXPECT_EQ(f.keys().size(), 2);
            EXPECT_EQ(f.keys().first(), QStringLiteral("key1"));
            EXPECT_EQ(f.keys().last(), QStringLiteral("key2"));
            EXPECT_EQ(f.uniqueKeys().size(), 2);
            EXPECT_EQ(f.uniqueKeys().first(), QStringLiteral("key1"));
            EXPECT_EQ(f.uniqueKeys().last(), QStringLiteral("key2"));
            EXPECT_EQ(f.values("key1").size(), 1);
            EXPECT_EQ(f.values("key1").first()->toString(), QStringLiteral("1"));
            EXPECT_EQ(f.values("key2").size(), 1);
            EXPECT_EQ(f.values("key2").first()->toString(), QStringLiteral("2"));
        }

        TEST(CObject, SameKeywordValue)
        {
            CObject f;
            f.insert("key", new CNumericValue(tToken(), "1"));
            f.insert("key", new CNumericValue(tToken(), "2"));
            EXPECT_FALSE(f.isEmpty());
            EXPECT_TRUE(f.contains("key"));
            EXPECT_EQ(f.keys().size(), 2);
            EXPECT_EQ(f.keys().first(), QStringLiteral("key"));
            EXPECT_EQ(f.keys().last(), QStringLiteral("key"));
            EXPECT_EQ(f.uniqueKeys().size(), 1);
            EXPECT_EQ(f.uniqueKeys().first(), QStringLiteral("key"));
            EXPECT_EQ(f.values("key").size(), 2);
            EXPECT_EQ(f.values("key").first()->toString(), QStringLiteral("1"));
            EXPECT_EQ(f.values("key").last()->toString(), QStringLiteral("2"));
        }

        TEST(CObject, RGBColor_White)
        {
            CObject f;
            f.insert("red", new CNumericValue(tToken(), "255"));
            f.insert("green", new CNumericValue(tToken(), "255"));
            f.insert("blue", new CNumericValue(tToken(), "255"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CObject, RGBColor_Black)
        {
            CObject f;
            f.insert("red", new CNumericValue(tToken(), "0"));
            f.insert("green", new CNumericValue(tToken(), "0"));
            f.insert("blue", new CNumericValue(tToken(), "0"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CObject, RGBColor_Gray)
        {
            CObject f;
            f.insert("red", new CNumericValue(tToken(), "128"));
            f.insert("green", new CNumericValue(tToken(), "128"));
            f.insert("blue", new CNumericValue(tToken(), "128"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CObject, RGBColor_Red)
        {
            CObject f;
            f.insert("red", new CNumericValue(tToken(), "255"));
            f.insert("green", new CNumericValue(tToken(), "0"));
            f.insert("blue", new CNumericValue(tToken(), "0"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CObject, RGBColor_Green)
        {
            CObject f;
            f.insert("red", new CNumericValue(tToken(), "0"));
            f.insert("green", new CNumericValue(tToken(), "255"));
            f.insert("blue", new CNumericValue(tToken(), "0"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CObject, RGBColor_Blue)
        {
            CObject f;
            f.insert("red", new CNumericValue(tToken(), "0"));
            f.insert("green", new CNumericValue(tToken(), "0"));
            f.insert("blue", new CNumericValue(tToken(), "255"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }

        TEST(CObject, HSLColor_White)
        {
            CObject f;
            f.insert("hue", new CNumericValue(tToken(), "0"));
            f.insert("saturation", new CNumericValue(tToken(), "100"));
            f.insert("lightness", new CNumericValue(tToken(), "100"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CObject, HSLColor_Gray)
        {
            CObject f;
            f.insert("hue", new CNumericValue(tToken(), "0"));
            f.insert("saturation", new CNumericValue(tToken(), "0"));
            f.insert("lightness", new CNumericValue(tToken(), "50"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CObject, HSLColor_Red)
        {
            CObject f;
            f.insert("hue", new CNumericValue(tToken(), "0"));
            f.insert("saturation", new CNumericValue(tToken(), "100"));
            f.insert("lightness", new CNumericValue(tToken(), "50"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CObject, HSLColor_Black)
        {
            CObject f;
            f.insert("hue", new CNumericValue(tToken(), "0"));
            f.insert("saturation", new CNumericValue(tToken(), "100"));
            f.insert("lightness", new CNumericValue(tToken(), "0"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CObject, HSLColor_Green)
        {
            CObject f;
            f.insert("hue", new CNumericValue(tToken(), "120"));
            f.insert("saturation", new CNumericValue(tToken(), "100"));
            f.insert("lightness", new CNumericValue(tToken(), "50"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CObject, HSLColor_Blue)
        {
            CObject f;
            f.insert("hue", new CNumericValue(tToken(), "240"));
            f.insert("saturation", new CNumericValue(tToken(), "100"));
            f.insert("lightness", new CNumericValue(tToken(), "50"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }
    }
}
