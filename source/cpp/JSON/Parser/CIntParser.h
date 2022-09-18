/*!
*  \file      CIntParser.h
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
#pragma once

#include "CScanner.h"

union YYSTYPE;
struct json_pstate;

/// Input to the parser
typedef int Token;

namespace JSON
{
    class CArray;
    class CObject;
    class CTextValue;
    class CNumericValue;
    class CLogicValue;
    class CNullObject;
}

namespace JSON::Parser
{
    class CDriver;
    class CLogger;

    /// Convert tokens into a JSON tree
    ///
    /// The CIntParser class receives a linear stream of tokens from the scanner
    /// and send them to a push-parser generated from the syntax rules by _bison_. 
    /// The parser calls _driver_'s methods to generate object model of content 
    /// of a script. At the end of the input, the parser calls driver's setContent
    /// method.
    ///
    class CIntParser : public JSON::Scanner::CScanner
    {
    public:
        /// Preprocessing token
        using tToken = JSON::Scanner::CToken;

        /// Constructor
        /// \param driver object that handles events from the parser
        /// \param logger message handling object
        CIntParser(QTextStream* stream, const QString& filePath, CDriver* driver, CLogger* logger);

        /// Destructor
        virtual ~CIntParser();

    private:
        /// Last token
        tToken m_lastToken;

        /// Object that handles output of the parser
        CDriver* m_driver;

        /// Object that handles error messsages
        CLogger* m_logger;

        /// Expression parser state
        json_pstate* m_ps;

        /// Parser syntax error
        /// \param where preprocessing token
        /// \return Return _true_ to continue parsing, return _false_ to abort parsing and return with false
        bool syntaxError(const tToken& where);

        /// Memory allocation error
        /// \param where preprocessing token
        void memoryError(const tToken& where);

        /// Converts a token to the input for the expression parser
        /// \param token preprocessing token
        /// \param[out] pp_value token value
        /// \return Returns an integer value passed to the expression parser
        static int toParserToken(const tToken& token, YYSTYPE* pp_value);

        /// Check if given string is a keyword.
        ///
        /// If the function returns zero, the identifier is not a keyword and the parser
        /// shall report it as an identifier.
        /// \param str string 
        /// \return Return corresponding T_xxx value for valid keyword.
        static Token keywordToken(const QString& str);

        /// Check if given string is an operator.
        ///
        /// If the function returns zero, the string is not an operator. The parser shall
        /// report this as an error.
        /// \param str string
        /// \return Return corresponding T_xxx value for valid operators.
        static Token operatorToken(const QString& str);

        /// Get a string representation for a token.
        ///
        /// This is used to print debugging 
        /// symbols as they are found in the source stream. Provide a text representation for each T_xxx value.
        static const char* tokenName(Token t);

        // Overridables:
        // -------------

        // Send errors to a driver
        bool error(const JSON::Scanner::CError& error) override;

        // Send tokens to a parser
        bool processToken(const tToken& token) override;

        // Send EOF to a parser
        bool endOfFile(const tToken& token) override;
    };
}
