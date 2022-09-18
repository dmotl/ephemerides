/*!
*  \file      CParserError.cpp
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
#include "CParserError.h"

using namespace JSON::Parser;

//
// Constructor
//
CParserError::CParserError(CIntParser* sender, const tToken& token) : m_filePath(token.fpath),
m_line(token.line), m_column(token.column)
{
}


//
// Get error message
//
QString CParserError::toString() const
{
    QString prefix;
    if (!m_filePath.isEmpty()) {
        if (m_line > 0 && m_column > 0)
            prefix = QDir::toNativeSeparators(m_filePath) + QStringLiteral(" (line %1, column %2):\n").arg(m_line).arg(m_column);
        else
            prefix = QDir::toNativeSeparators(m_filePath) + QStringLiteral(":\n");
    }
    else {
        if (m_line > 0 && m_column > 0)
            prefix = QStringLiteral("Line %1, column %2: ").arg(m_line).arg(m_column);
    }
    return prefix + m_msg;
}


//
// Syntax error
//
CParserSyntaxError::CParserSyntaxError(CIntParser* sender, const tToken& token) : CParserError(sender, token)
{
    m_msg = QStringLiteral("Syntax error");
}


//
// Memory allocation error
//
CParserMemoryError::CParserMemoryError(CIntParser* sender, const tToken& token) : CParserError(sender, token)
{
    m_msg = QStringLiteral("Memory allocation error");
}
