/*!
*  \file      CLexerError.cpp
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
#include "CLexerError.h"

#include "CLexer.h"

using namespace JSON::Scanner;

//
// Constructor
//
CLexerError::CLexerError(CLexer* sender) : m_filePath(sender->filePath()), m_line(0), m_column(0)
{
    sender->GetPos(m_line, m_column);
}


//
// Get error message
//
QString CLexerError::toString() const
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
// Error in Unicode sequence
//
CUnicodeError::CUnicodeError(CLexer* sender, const QChar &ch) : CLexerError(sender)
{
    m_msg = QStringLiteral("%1: \\U%2").arg(QStringLiteral("Unexpected universal character name")).arg(ch.unicode(), 4, 16, QLatin1Char('0'));
}


//
// EOF, newline or a control charater in a string literal
//
CNewLineInStringLiteralError::CNewLineInStringLiteralError(CLexer* sender, const QChar& ch) : CLexerError(sender)
{
    // Null character indicates end of input stream (file)
    if (ch.isNull())
        m_msg = QStringLiteral("Unexpected end of file in a string literal");
    else
        m_msg = QStringLiteral("Unexpected end of line in a string literal");
}


//
// Invalid character in a string literal
//
CInvalidCharInStringLiteralError::CInvalidCharInStringLiteralError(CLexer* sender, const QChar& ch) : CLexerError(sender)
{
    if (ch >= QChar(0x21) && ch <= QChar(0x7E)) {
        // Printable, non-space ASCII characters: exclamation mark (0x21) - tilde (0x7E)
        m_msg = QStringLiteral("%1: '%2'").arg(QStringLiteral("Invalid character in a string literal")).arg(ch);
    }
    else if (ch >= QChar(0x80) && !ch.isNonCharacter()) {
        // Non-ASCII characters
        m_msg = QStringLiteral("%1: '%2' (\\U%3)").arg(QStringLiteral("Invalid character in a string literal")).arg(ch).arg(ch.unicode(), 4, 16, QLatin1Char('0'));
    }
    else {
        // Control characters (0x01 - 0x19, 0x7F), Unicode non-characters
        m_msg = QStringLiteral("%1: \\U%2").arg(QStringLiteral("Invalid character in a string literal")).arg(ch.unicode(), 4, 16, QLatin1Char('0'));
    }
}


//
// Error in numeric literal
//
CInvalidNumericLiteralError::CInvalidNumericLiteralError(CLexer* sender) : CLexerError(sender)
{
    m_msg = QStringLiteral("Invalid numeric literal");
}


//
// Constructor
//
CInvalidCharEscSequenceError::CInvalidCharEscSequenceError(CLexer* sender, const QChar& ch) : CLexerError(sender)
{
    if (ch >= QChar(0x21) && ch <= QChar(0x7E)) {
        // Printable, non-space ASCII characters: exclamation mark (0x21) - tilde (0x7E)
        m_msg = QStringLiteral("%1: '%2'").arg(QStringLiteral("Invalid character escape sequence")).arg(ch);
    }
    else if (ch >= QChar(0x80) && !ch.isNonCharacter()) {
        // Non-ASCII characters
        m_msg = QStringLiteral("%1: '%2' (\\U%3)").arg(QStringLiteral("Invalid character escape sequence")).arg(ch).arg(ch.unicode(), 4, 16, QLatin1Char('0'));
    }
    else {
        // Control characters (0x01 - 0x19, 0x7F), Unicode non-characters
        m_msg = QStringLiteral("%1: \\U%2").arg(QStringLiteral("Invalid character escape sequence")).arg(ch.unicode(), 4, 16, QLatin1Char('0'));
    }
}


//
// Constructor
//
CInvalidStateError::CInvalidStateError(CLexer* sender, int state) : CLexerError(sender)
{
    m_msg = QStringLiteral("%1: %2").arg(QStringLiteral("Undefined state of lexical analyzer")).arg(state);
}
