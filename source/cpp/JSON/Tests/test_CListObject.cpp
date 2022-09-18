/*!
*  \file      test_CListObject.cpp
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
#include "CArray.h"

#include "gtest/gtest.h"

#include "CNullObject.h"
#include "CNumericValue.h"

using namespace testing;

namespace JSON::Parser::Tests
{
    namespace Core
    {
        using tToken = JSON::Scanner::CToken;

        TEST(CArray, EmptyList)
        {
            CArray f;
            EXPECT_EQ(f.size(), 0);
            EXPECT_EQ(f.firstValue(), static_cast<const CNode*>(nullptr));
            EXPECT_TRUE(f.isEmpty());
        }

        TEST(CArray, OneItem)
        {
            CArray f;
            f.append(new CNullObject(tToken()));

            EXPECT_EQ(f.size(), 1);
            EXPECT_NE(f.firstValue(), static_cast<const CNode*>(nullptr));
            EXPECT_TRUE(f.firstValue()->isNull());
        }

        TEST(CArray, TwoValues)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "1"));
            f.append(new CNumericValue(tToken(), "2"));

            int i = 0;
            EXPECT_EQ(f.size(), 2);
            for (const CNode* ptr = f.firstValue(); ptr != NULL; ptr = ptr->nextValue()) {
                bool ok = false;
                EXPECT_TRUE(ptr->toInt(&ok) == ++i && ok);
            }
        }

        TEST(CArray, toDoubleArray)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "1"));
            f.append(new CNumericValue(tToken(), "2"));

            double x, y;
            double* values[] = { &x, &y };
            EXPECT_EQ(f.toDoubleArray(values, 2, 1, 2, NULL), 2);
            EXPECT_EQ(x, 1);
            EXPECT_EQ(y, 2);
        }

        TEST(CArray, toDoubleArray2)
        {
            CArray f;

            double x = 0, y = 0;
            double* values[] = { &x, &y };
            EXPECT_EQ(f.toDoubleArray(values, 2, 1, 2, NULL), 0);
            EXPECT_EQ(x, 0);
            EXPECT_EQ(y, 0);
        }

        TEST(CArray, toStringList)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "1"));
            f.append(new CNumericValue(tToken(), "2"));

            QStringList values = f.toStringList(NULL);
            EXPECT_EQ(values.size(), 2);
            EXPECT_EQ(values.first(), "1");
            EXPECT_EQ(values.last(), "2");
        }

        TEST(CArray, toStringList2)
        {
            CArray f;
            EXPECT_TRUE(f.toStringList(NULL).isEmpty());
        }

        TEST(CArray, RGBColor_White)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "255"));
            f.append(new CNumericValue(tToken(), "255"));
            f.append(new CNumericValue(tToken(), "255"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 255, 255));
        }

        TEST(CArray, RGBColor_Black)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "0"));
            f.append(new CNumericValue(tToken(), "0"));
            f.append(new CNumericValue(tToken(), "0"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 0));
        }

        TEST(CArray, RGBColor_Gray)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "128"));
            f.append(new CNumericValue(tToken(), "128"));
            f.append(new CNumericValue(tToken(), "128"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(128, 128, 128));
        }

        TEST(CArray, RGBColor_Red)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "255"));
            f.append(new CNumericValue(tToken(), "0"));
            f.append(new CNumericValue(tToken(), "0"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(255, 0, 0));
        }

        TEST(CArray, RGBColor_Green)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "0"));
            f.append(new CNumericValue(tToken(), "255"));
            f.append(new CNumericValue(tToken(), "0"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 255, 0));
        }

        TEST(CArray, RGBColor_Blue)
        {
            CArray f;
            f.append(new CNumericValue(tToken(), "0"));
            f.append(new CNumericValue(tToken(), "0"));
            f.append(new CNumericValue(tToken(), "255"));

            bool ok = false;
            QRgb color = f.toColor(&ok);
            EXPECT_TRUE(ok);
            EXPECT_EQ(color, qRgb(0, 0, 255));
        }
    }
}
