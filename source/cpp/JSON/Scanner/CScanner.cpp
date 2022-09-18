/*!
*  \file      CScanner.cpp
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

#include "CLexer.h"

using namespace JSON::Scanner;

//
// Constructor
//
CScanner::CScanner(QTextStream* stream, const QString& filePath) : m_lexer(nullptr), m_stream(stream), m_sharedStream(true)
{
    m_lexer = new CLexer(this, filePath, m_stream);
}


//
// Constructor
//
CScanner::CScanner(const QString& string) : m_lexer(nullptr), m_string(string), m_stream(nullptr), m_sharedStream(false)
{
    m_string.detach();
    m_stream = new QTextStream(&m_string);
    m_lexer = new CLexer(this, QString(), m_stream);
}


//
// Destructor
//
CScanner::~CScanner(void)
{
    if (m_sharedStream)
        delete m_stream;
}


//
// Parse input
//
bool CScanner::parse(void)
{
    bool ok = true;
    while (true) {
        if (!push(&ok))
            return ok;
    }
}


//
// Get next token, return false to cancel further processing
// or true to continue. Value set to pOK is returned by parse()
//
bool CScanner::push(bool* pOk)
{
    // Get next token from the current file and process it
    CToken t;
    if (!m_lexer->GetSym(t)) {
        // Irrecoverable error occurred --> stop parsing
        if (pOk != NULL)
            *pOk = false;
        return false;
    }
    else if (t.token == tToken::T_END) {
        // End of input
        bool retval = endOfFile(t);
        if (!retval && pOk != NULL)
            *pOk = false;
        return false;
    }
    else {
        // Process token
        bool retval = processToken(t);
        if (!retval && pOk != NULL)
            *pOk = false;
        return retval;
    }
}
