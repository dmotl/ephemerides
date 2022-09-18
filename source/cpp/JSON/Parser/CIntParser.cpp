/*!
*  \file      CIntParser.cpp
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
#include "CIntParser.h"

#include "CDriver.h"
#include "json_bison_output.h"
#include "CParserError.h"
#include "CLogger.h"

// Set to 1 to print the tokens
#if !NDEBUG
#define JSON_PARSER_DEBUG_OUTPUT 0
#else
#undef JSON_PARSER_DEBUG_OUTPUT
#endif

using namespace JSON::Parser;

//
// Constructor
//
CIntParser::CIntParser(QTextStream* stream, const QString& filePath, CDriver* driver, CLogger* logger) : 
    CScanner(stream, filePath), m_driver(driver), m_logger(logger)
{
    m_ps = json_pstate_new();
}


//
// Destructor
//
CIntParser::~CIntParser()
{
    json_pstate_delete(m_ps);
}


//
// Process incoming preprocessor tokens
//
bool CIntParser::processToken(const tToken& what) 
{
    YYSTYPE pp_value;
    int pp_token = toParserToken(what, &pp_value);
    if (pp_token < 0) {
        // Invalid preprocessor token
        return syntaxError(what);
    }
    else if (pp_token > 0) {
#if JSON_PARSER_DEBUG_OUTPUT
        qDebug() << tokenName(pp_token) << what.tok_value << " file: " << QDir::toNativeSeparators(what.fpath) << " line: " << what.line << " column: " << what.column;
#endif
        int status = json_push_parse(m_ps, pp_token, &pp_value, what, this, m_driver, m_logger);
        if (status == 1) {
            // Syntax error in an expression
            return syntaxError(what);
        }
        if (status == 2) {
            // Memory allocation error
            memoryError(what);
            return false;
        }
    }
    return true;
}


//
// End of input
//
bool CIntParser::endOfFile(const tToken& token) 
{
    // End of directive, push terminating token to the parser to signal end the sentence
    int status = json_push_parse(m_ps, 0, NULL, token, this, m_driver, m_logger);
    if (status == 1) {
        // Syntax error in an expression
        return syntaxError(token);
    }
    if (status == 2) {
        // Memory allocation error
        memoryError(token);
        return false;
    }
    return (status == 0);
}


//
// Parser syntax error
//
bool CIntParser::syntaxError(const tToken& where)
{
    if (m_logger)
        m_logger->log(CParserSyntaxError(this, where));
    return true;
}


//
// Memory allocation error
//
void CIntParser::memoryError(const tToken& where)
{
    if (m_logger)
        m_logger->log(CParserMemoryError(this, where));
}


//
// Convert token to an input for expression parser
//
int CIntParser::toParserToken(const tToken& what, YYSTYPE* pp_value)
{
    pp_value->qstr = NULL;

    switch (what.token)
    {
    case JSON::Scanner::tToken::T_ID:
    {
        Token tmp = keywordToken(what.tok_value);
        if (tmp != 0) {
            // keyword
            return tmp;
        }
        // Unknown identifier
        return -1;
    }

    case JSON::Scanner::tToken::T_OP:
    {
        Token tmp = operatorToken(what.tok_value);
        if (tmp != 0)
            return tmp;
        // Unknown operator --> syntax error
        return -1;
    }

    case JSON::Scanner::tToken::T_NUM:
        // Numeric literal
        pp_value->qstr = new QString(what.tok_value);
        return T_NUM;

    case JSON::Scanner::tToken::T_STR:
        // String literal
        pp_value->qstr = new QString(what.tok_value);
        return T_STR;

    case JSON::Scanner::tToken::T_WS:
    case JSON::Scanner::tToken::T_END:
        // Ignore whitespaces
        return 0;

    default:
        // Other tokens --> Syntax error
        return -1;
    }
}


//
// Operator tokens
//
Token CIntParser::operatorToken(const QString& str)
{
    if (str == QStringLiteral(","))
        return T_COMMA;
    if (str == QStringLiteral(":"))
        return T_COLON;
    if (str == QStringLiteral("["))
        return T_BEGIN_LIST;
    if (str == QStringLiteral("]"))
        return T_END_LIST;
    if (str == QStringLiteral("{"))
        return T_BEGIN_OBJ;
    if (str == QStringLiteral("}"))
        return T_END_OBJ;
    return 0;
}


//
// Keywords
//
Token CIntParser::keywordToken(const QString& str)
{
    if (str.compare(QStringLiteral("true")) == 0)
        return T_TRUE;
    else if (str.compare(QStringLiteral("false")) == 0)
        return T_FALSE;
    else if (str.compare(QStringLiteral("null")) == 0)
        return T_NULL;
    return 0;
}


//
// Get next token (debug variant that calls _GetSym and print the symbol)
//
const char* CIntParser::tokenName(Token t)
{
    switch (t)
    {
    case T_NUM:			return "T_NUM";
    case T_STR:			return "T_STR";
    case T_COMMA:		return "T_COMMA";
    case T_COLON:		return "T_COLON";
    case T_FALSE:       return "T_FALSE";
    case T_TRUE:        return "T_TRUE";
    case T_NULL:        return "T_NULL";
    case T_BEGIN_LIST:  return "T_BEGIN_LIST";
    case T_END_LIST:    return "T_END_LIST";
    case T_BEGIN_OBJ:   return "T_BEGIN_OBJ";
    case T_END_OBJ:     return "T_END_OBJ";
    default:            return NULL;
    }
}


//
// Process error messages
//
bool CIntParser::error(const JSON::Scanner::CError& error)
{
    if (m_logger)
        m_logger->log(error);
    return true;
}
