/*!
*  \file      test_Scanner.cpp
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
#include "CScanner.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

static const QString ENCODING_TEST = QString::fromUtf8("\xC4\x9B\xC5\xA1\xC4\x8D\xC5\x99\xC5\xBE\xC3\xBD\xC3\xA1\xC3\xAD\xC3\xA9");

namespace JSON::Scanner
{
    // Operator== must be in the same namespace as Token and
    // it must be defined as a free function, not as a Token's method.

    bool operator==(const CToken& rhs, const CToken& lhs) {
        return rhs.token == lhs.token && rhs.tok_value == lhs.tok_value;
    }
    bool operator!=(const CToken& rhs, const CToken& lhs) {
        return !operator==(rhs, lhs);
    }
}

using namespace testing;

namespace JSON::Scanner::Tests
{
    class MockScanner : public CScanner
    {
    public:
        explicit MockScanner(const QString& str) : CScanner(str) {}

        // Handles driver errors
        MOCK_METHOD1(error, bool(const CError&));
        MOCK_METHOD1(warning, void(const QString&));
        MOCK_METHOD1(processToken, bool(const CToken&));
        MOCK_METHOD1(endOfFile, bool(const CToken&));
    };

    TEST(Scanner, StringLiterals)
    {
        MockScanner scanner("a aaa a1a1a1 _a_ a_a");

        // Sequence of EXPECT_CALLs is evaluated backwards, this is counter-intuitive.
        // When use matchers, place more specialized matchers down and general matchers
        // up.

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_ID, QStringLiteral("a"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_ID, QStringLiteral("aaa"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_ID, QStringLiteral("a1a1a1"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_ID, QStringLiteral("_a_"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_ID, QStringLiteral("a_a"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, error(_))
            .Times(0);
        EXPECT_CALL(scanner, endOfFile(_))
            .WillOnce(Return(true));

        EXPECT_TRUE(scanner.parse());
    }

    TEST(Scanner, WhiteSpaces)
    {
        MockScanner scanner(" \t\n\f\v");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, error(_))
            .Times(0);
        EXPECT_CALL(scanner, endOfFile(_))
            .WillOnce(Return(true));

        EXPECT_TRUE(scanner.parse());
    }

    MATCHER_P(NumEq, x, "Comparison of T_NUM token and a value")
    {
        *result_listener << "where the value is " << (x);
        return (arg.token == tToken::T_NUM) && arg.tok_value.toDouble() == x;
    }

    TEST(Scanner, NumericLiterals)
    {
        MockScanner scanner("1 +2 3.141 4e-6 2.0e3 2.0E+3 .5 +.5 -6 -.6");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, processToken(NumEq(1)))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(NumEq(2)))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(NumEq(3.141)))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(NumEq(4.0e-6)))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(NumEq(2.0e3)))
            .Times(2).WillRepeatedly(Return(true));
        EXPECT_CALL(scanner, processToken(NumEq(0.5)))
            .Times(2).WillRepeatedly(Return(true));
        EXPECT_CALL(scanner, processToken(NumEq(-6.0)))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(NumEq(-0.6)))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, error(_))
            .Times(0);
        EXPECT_CALL(scanner, endOfFile(_))
            .WillOnce(Return(true));

        EXPECT_TRUE(scanner.parse());
    }

    TEST(Scanner, StringLiterals1)
    {
        MockScanner scanner("\"aaa\"\"\"");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_STR, QStringLiteral(""))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_STR, QStringLiteral("aaa"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, error(_))
            .Times(0);
        EXPECT_CALL(scanner, endOfFile(_))
            .WillOnce(Return(true));

        EXPECT_TRUE(scanner.parse());
    }

    TEST(Scanner, StringLiterals2)
    {
        MockScanner scanner("\"\\\"quoted\\\" string\"");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_STR, QStringLiteral("\"quoted\" string"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, error(_))
            .Times(0);
        EXPECT_CALL(scanner, endOfFile(_))
            .WillOnce(Return(true));

        EXPECT_TRUE(scanner.parse());
    }

    TEST(Scanner, StringLiterals3)
    {
        MockScanner scanner("\"unicode \\u0059\\u0041\\u00A5\\u00C0\"");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_STR, QStringLiteral(u"unicode \u0059\u0041\u00A5\u00C0"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, error(_))
            .Times(0);
        EXPECT_CALL(scanner, endOfFile(_))
            .WillOnce(Return(true));

        EXPECT_TRUE(scanner.parse());
    }

    TEST(Scanner, StringLiterals4)
    {
        MockScanner scanner("\"back\\\\slash\"");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_STR, QStringLiteral("back\\slash"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, error(_))
            .Times(0);
        EXPECT_CALL(scanner, endOfFile(_))
            .WillOnce(Return(true));

        EXPECT_TRUE(scanner.parse());
    }

    TEST(Scanner, Operators)
    {
        MockScanner scanner(". + - * / ! < > = ^ % () [] {} , : ; ? ** // != <= <> >= ==");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("."))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("+"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("-"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("*"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("/"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("!"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("<"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral(">"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("="))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("^"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("%"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("("))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral(")"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("["))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("]"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("{"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("}"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral(","))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral(":"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral(";"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("?"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("**"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("//"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("!="))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("<="))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("<>"))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral(">="))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, processToken(CToken(tToken::T_OP, QStringLiteral("=="))))
            .WillOnce(Return(true));
        EXPECT_CALL(scanner, error(_))
            .Times(0);
        EXPECT_CALL(scanner, endOfFile(_))
            .WillOnce(Return(true));

        EXPECT_TRUE(scanner.parse());
    }

    TEST(Scanner, MalformedStrings1)
    {
        MockScanner scanner("\"aaa");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, error(_))
            .WillOnce(DoDefault());
        EXPECT_CALL(scanner, endOfFile(_))
            .Times(0);

        EXPECT_FALSE(scanner.parse());
    }

    TEST(Scanner, MalformedStrings2)
    {
        MockScanner scanner("\"aaa\nbbb\"");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, error(_))
            .WillOnce(DoDefault());
        EXPECT_CALL(scanner, endOfFile(_))
            .Times(0);

        EXPECT_FALSE(scanner.parse());
    }

    TEST(Scanner, MalformedNumericLiterals1)
    {
        MockScanner scanner("3E");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, error(_))
            .WillOnce(DoDefault());
        EXPECT_CALL(scanner, endOfFile(_))
            .Times(0);

        EXPECT_FALSE(scanner.parse());
    }

    TEST(Scanner, MalformedNumericLiterals2)
    {
        MockScanner scanner("3E+");

        EXPECT_CALL(scanner, processToken(_))
            .Times(0);
        EXPECT_CALL(scanner, error(_))
            .WillOnce(DoDefault());
        EXPECT_CALL(scanner, endOfFile(_))
            .Times(0);

        EXPECT_FALSE(scanner.parse());
    }
}
