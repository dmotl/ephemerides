/*!
*  \file      CParserError.h
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

#include <QtCore>

#include "CToken.h"
#include "CError.h"

namespace JSON::Parser
{
    class CIntParser;

    /// Parser error descriptor
    ///
    /// This is a base class for parser errors.
    /// 
    class CParserError : public JSON::Utils::CError
    {
    public:
        /// Preprocessing token
        using tToken = JSON::Scanner::CToken;

        /// Constructor
        ///
        /// \param sender parser
        /// \param token position in the input stream
        CParserError(CIntParser* sender, const tToken& token);

        /// Get error message
        QString toString() const override;

    protected:
        /// Path to the file (can be "")
        QString m_filePath;

        /// Line number
        int m_line;

        /// Column number
        int m_column;

        /// Error message
        QString m_msg;
    };

    /// Syntax error
    class CParserSyntaxError: public CParserError
    {
    public:
        /// Constructor
        /// \param sender object that generated the error
        /// \param token place in the script
        CParserSyntaxError(CIntParser* sender, const tToken& token);
    };

    /// Memory allocation error
    class CParserMemoryError : public CParserError
    {
    public:
        /// Constructor
        /// \param sender object that generated the error
        /// \param token place in the script
        CParserMemoryError(CIntParser* sender, const tToken& token);
    };
}
