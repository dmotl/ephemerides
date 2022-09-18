/*!
*  \file      CScanner.h
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

#include "CToken.h"
#include "CError.h"

namespace JSON::Scanner
{
    class CLexer;

    using CError = JSON::Utils::CError;

    /// \brief Preprocessor public API
    ///
    /// The Scanner class encapsulates a functionality similar to a C preprocessor. It
    /// reads an input from a string (see parseString()) or a file (see parseFile()),
    /// breaks it into preprocessor tokens, replaces macros, recurse into include files
    /// and skip parts based on conditions. Unlike C, preprocessor commands starts with '!'.
    /// The caller shall create a descendant class and override the method that process
    /// events:
    /// - _processToken(t)_ - handle a preprocessor token _t_ (except T_END)
    /// - _error(e)_ - handle an error event _e_
    /// - _endOfFile(t) - handle a special token T_END issued at the end of input
    ///
    class CScanner
    {
    public:
        // Constructor
        explicit CScanner(QTextStream* stream, const QString& filePath = QString());

        // Constructor
        explicit CScanner(const QString& string);

        // Destructor
        virtual ~CScanner(void);

        /// Process an input
        bool parse(void);

        /// Override this function to handle error events
        /// \param error error event
        /// \return Return _true_ to continue parsing, return _false_ to abort parsing and return with false
        virtual bool error(const CError& error) { return true; }

        /// Override this function to handle tokens
        /// \param token token descriptor, includes type, value and location
        /// \return Return _true_ to continue parsing, return _false_ to abort parsing and return with false
        virtual bool processToken(const CToken &token) { return true; }

        /// Override this function to make checks on the end of the input
        /// \param token T_END token with location
        /// \return Return value is passed out of the parseXXX method.
        virtual bool endOfFile(const CToken& token) { return true; }

    protected:
        /// Source stream of characters
        QTextStream* m_stream;

        /// Lexer (tokenizer)
        CLexer* m_lexer;

        // Copy of input string
        QString m_string;

        // True if the desctructor must not delete the QTextStream
        bool m_sharedStream;

        /// Get next token and process it
        bool push(bool* pOk);
    };
}
