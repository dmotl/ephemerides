/*!
*  \file      test_CLogicValue.cpp
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
#include "CLogicValue.h"

#include "gtest/gtest.h"

using namespace testing;

namespace JSON::Parser::Tests
{
    namespace Core
    {
        using tToken = JSON::Scanner::CToken;

        TEST(CLogicValue, False)
        {
            CLogicValue f(tToken(), false);

            bool ok = false;
            EXPECT_TRUE(f.toBool(&ok) == false && ok);
        }

        TEST(CLogicValue, True)
        {
            CLogicValue f(tToken(), true);

            bool ok = false;
            EXPECT_TRUE(f.toBool(&ok) == true && ok);
        }
    }
}
