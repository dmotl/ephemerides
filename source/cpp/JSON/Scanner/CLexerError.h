/*!
*  \file      CLexerError.h
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

#include "CError.h"

namespace JSON::Scanner
{
    using CError = JSON::Utils::CError;
    class CLexer;

    /// Lexer errors
    ///
    /// The CLexerError is a base class for all error events issued by
    /// a lexer. The class keeps location and context of an error.
    ///
    class CLexerError : public CError
    {
    public:
        /// Constructor
        /// \param sender lexer that issued the error
        explicit CLexerError(CLexer*sender);

        //// Get error message
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


    /// \brief Malformed Unicode escape sequence
    ///
    /// The CUnicodeError error is issued by a lexer if a malformed Unicode escape sequence
    /// occurs on the input. The correct for is `\UXXXX` or `\uXXXX` where `X`
    /// is a hexadecimal digit.
    ///
    class CUnicodeError : public CLexerError
    {
    public:
        /// Constructor
        /// \param sender lexer that issued the error
        /// \param ch a character that should not be part of the input
        CUnicodeError(CLexer* sender, const QChar &ch);
    };


    /// \brief Invalid numeric literal
    ///
    /// The CInvalidNumericLiteralError error is issued by a lexer if an unexpected character
    /// occurs inside a numeric literal.
    ///
    class CInvalidNumericLiteralError : public CLexerError
    {
    public:
        /// Constructor
        /// \param sender lexer that issued the error
        explicit CInvalidNumericLiteralError(CLexer* sender);
    };


    /// \brief New line in a string literal
    ///
    /// The CNewLineInStringLiteralError error is issued by a lexer if a string
    /// literal is not closed before end of a logic line.
    ///
    class CNewLineInStringLiteralError : public CLexerError
    {
    public:
        /// Constructor
        /// \param sender lexer that issued the error
        /// \param ch a character that should not be part of the input
        CNewLineInStringLiteralError(CLexer* sender, const QChar& ch);
    };


    /// \brief Invalid character in a string literal
    ///
    /// The CNewLineInStringLiteralError error is issued by a lexer if a string
    /// literal is not closed before end of a logic line.
    ///
    class CInvalidCharInStringLiteralError : public CLexerError
    {
    public:
        /// Constructor
        /// \param sender lexer that issued the error
        /// \param ch a character that should not be part of the input
        CInvalidCharInStringLiteralError(CLexer* sender, const QChar& ch);
    };


    /// \brief Invalid character escape sequence
    ///
    /// The CInvalidCharEscSequenceError error is issued if a lexer if an unexpected character
    /// follows a backslash in a string literal.
    ///
    class CInvalidCharEscSequenceError : public CLexerError
    {
    public:
        /// Constructor
        /// \param sender lexer that issued the error
        /// \param ch a character that should not be part of the input
        CInvalidCharEscSequenceError(CLexer* sender, const QChar& ch);
    };

    /// \brief Invalid state error
    ///
    /// The CInvalidStateError error is issued by a lexer if it happens to be in an
    /// invalid state. This should never happens and indicates
    /// a problem of the lexer's design.
    ///
    class CInvalidStateError : public CLexerError
    {
    public:
        /// Constructor
        /// \param sender lexer that issued the error
        /// \param state a lexer's state
        CInvalidStateError(CLexer* sender, int state);
    };
}
