/*!
*  \file      CLexer.cpp
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
#include "CLexer.h"

#include "CLexerError.h"
#include "CScanner.h"

// Set to 1 to print the tokens
#if !NDEBUG
#define JSON_SCANNER_DEBUG_OUTPUT 0
#else
#undef JSON_SCANNER_DEBUG_OUTPUT
#endif

static const QString forbiddenChars = QStringLiteral("\\/:*?\"<>|");

//----------------------------   LEXICAL ANALYZER   -------------------------------------------

using namespace JSON::Scanner;

//
// Create a lexical analyser for a file
//
CLexer::CLexer(CScanner* scanner, const QString &filePath, QTextStream* input) : m_filePath(filePath),
    m_Stream(input), m_BackChar(false), m_Line(1), m_Column(1), m_LastLine(0), m_LastColumn(0),
    m_scanner(scanner), m_state(0), m_StartPosLine(0), m_StartPosColumn(0)
{
}

#if JSON_SCANNER_DEBUG_OUTPUT

//
// Get next token (debug variant that calls _GetSym and print the symbol)
//
bool CLexer::GetSym(CToken& token)
{
    bool retval = _GetSym(token);
    if (retval)
        qDebug() << token.toString();
    return retval;
}

#else

bool CLexer::GetSym(CToken& token) 
{ 
    return _GetSym(token); 
}

#endif


//
// Get next token
//
bool CLexer::_GetSym(CToken& token)
{
    QString value;
    int state = 0;

    while (true) {
        QChar ch = GetChar();
        switch (state)
        {
        case 0:
            // First character of a token (keep the character's position and report it as the position of the token)
            GetPos(m_StartPosLine, m_StartPosColumn);
            if (ch.isLetter() || ch == QLatin1Char('_') || ch.unicode() >= 128) {
                value = ch;
                state = 1;
            }
            else if (ch == QLatin1Char('-')) {
                value = ch;
                state = 2;
            }
            else if (ch == QLatin1Char('0')) {
                value = ch;
                state = 21;
            }
            else if (ch.isDigit()) {
                value = ch;
                state = 22;
            }
            else if (ch == QLatin1Char('"')) {
                value.clear();
                state = 3;
            }
            else if (ch == QLatin1Char('[') || ch == QLatin1Char(']') || ch == QLatin1Char('{') || ch == QLatin1Char('}') || ch == QLatin1Char(',') || ch == QLatin1Char(':')) {
                // Single character operators and punctuation
                value = ch;
                token = tok(tToken::T_OP, ch);
                return true;
            }
            else if (ch == QLatin1Char('\t') || ch == QLatin1Char(' ') || ch == QLatin1Char('\n') || ch == QLatin1Char('\r') || ch == QLatin1Char('\f') || ch == QLatin1Char('\v')) {
                // White space sequence
                value = ch;
                state = 5;
            }
            else if (ch.isNull()) {
                // End of stream
                token = tok(tToken::T_END);
                return true;
            }
            else {
                // Unexpected character
                value = ch;
                token = tok(tToken::T_OTHER, value);
                return true;
            }
            break;

        case 1:
            // Identifiers
            if (ch.isLetter() || ch.isDigit() || ch == QLatin1Char('_') || ch.unicode() >= 128) {
                // Letters, digits and underscore
                value.append(ch);
            }
            else {
                // End of identifier
                UngetChar(ch);
                token = tok(tToken::T_ID, value);
                return true;
            }
            break;

        case 2:
            // Numeric literal starting with `-`
            if (ch == QLatin1Char('0')) {
                value.append(ch);
                state = 21;
            }
            else if (ch.isDigit()) {
                value.append(ch);
                state = 22;
            }
            else {
                // Invalid numeric literal
                UngetChar(ch);
                if (!sendError(CInvalidNumericLiteralError(this)))
                    return false;
                state = 0;
            }
            break;

        case 21:
            // Numeric literals after `0`
            if (ch == QLatin1Char('.')) {
                // Period after a digit
                value.append(ch);
                state = 23;
            }
            else if (ch == QLatin1Char('E') || ch == QLatin1Char('e')) {
                // Exponent indicator
                value.append(ch);
                state = 25;
            }
            else {
                // End of numeric literal
                UngetChar(ch);
                token = tok(tToken::T_NUM, value);
                return true;
            }
            break;

        case 22:
            // Numeric literals, after `1` - '9`
            if (ch.isDigit()) {
                value.append(ch);
                state = 22;
            }
            else if (ch == QLatin1Char('.')) {
                value.append(ch);
                state = 23;
            }
            else if (ch == QLatin1Char('E') || ch == QLatin1Char('e')) {
                // Exponent indicator
                value.append(ch);
                state = 25;
            }
            else {
                // End of numeric literal
                UngetChar(ch);
                token = tok(tToken::T_NUM, value);
                return true;
            }
            break;

        case 23:
            // Numeric literal, after a period
            if (ch.isDigit()) {
                // Digits     
                value.append(ch);
                state = 24;
            }
            else {
                // Invalid numeric literal
                UngetChar(ch);
                if (!sendError(CInvalidNumericLiteralError(this)))
                    return false;
                state = 0;
            }
            break;

        case 24:
            // Numeric literal, fractional part
            if (ch.isDigit()) {
                // Digits     
                value.append(ch);
                state = 24;
            }
            else if (ch == QLatin1Char('E') || ch == QLatin1Char('e')) {
                // Exponent indicator
                value.append(ch);
                state = 25;
            }
            else {
                // End of numeric literal
                UngetChar(ch);
                token = tok(tToken::T_NUM, value);
                return true;
            }
            break;

        case 25:
            // Exponent part of numeric integral
            if (ch == QLatin1Char('+') || ch == QLatin1Char('-')) {
                // Sign
                value.append(ch);
                state = 26;
            }
            else if (ch.isDigit()) {
                // Digits
                value.append(ch);
                state = 27;
            }
            else {
                // Invalid numeric literal
                UngetChar(ch);
                if (!sendError(CInvalidNumericLiteralError(this)))
                    return false;
                state = 0;
            }
            break;

        case 26:
            // Exponent part of numeric integral
            if (ch.isDigit()) {
                // Digits
                value.append(ch);
                state = 27;
            }
            else {
                // Invalid numeric literal
                UngetChar(ch);
                if (!sendError(CInvalidNumericLiteralError(this)))
                    return false;
                state = 0;
            }
            break;

        case 27:
            // Exponent part of numeric integral
            if (ch.isDigit()) {
                // Digits
                value.append(ch);
                state = 27;
            }
            else {
                // End of numeric literal
                UngetChar(ch);
                token = tok(tToken::T_NUM, value);
                return true;
            }
            break;

        case 3:
            // String literal 
            if (ch == QLatin1Char('\\')) {
                // Start of escape sequence
                state = 41;
            }
            else if (ch == QLatin1Char('\"')) {
                // End of string literal
                token = tok(tToken::T_STR, value);
                return true;
            }
            else if (ch.isNull() || ch == QLatin1Char('\n') || ch == QLatin1Char('\r') || ch == QLatin1Char('\f') || ch == QLatin1Char('\v')) {
                // End of file or line in a string literal
                UngetChar(ch);
                if (!sendError(CNewLineInStringLiteralError(this, ch)))
                    return false;
                state = 0;
            }
            else if (ch < QLatin1Char(' ') || ch.isNonCharacter()) {
                // Unexpected character
                UngetChar(ch);
                sendError(CInvalidCharInStringLiteralError(this, ch));
                return false;
            }
            else {
                // String literal continues
                value.append(ch);
            }
            break;

        case 41:
            // Escaping in a string literal - backslash, quote or universal character name
            if (ch == QLatin1Char('\\') || ch == QLatin1Char('\"')) {
                // Simple escape sequences - backslash or quote
                value.append(ch);
                state = 4;
            }
            else if (ch == QLatin1Char('U') || ch == QLatin1Char('u')) {
                // Uncode escape sequences
                m_Chr = QChar();
                state = 42;
            }
            else {
                // Invalid escape sequence
                UngetChar(ch);
                if (!sendError(CInvalidCharEscSequenceError(this, ch)))
                    return false;
                state = 4;
            }
            break;

        case 42:
        case 43:
        case 44:
        case 45:
            // Universal character name (always 4 hex digits)
            if ((ch >= QLatin1Char('0') && ch <= QLatin1Char('9')) || (ch >= QLatin1Char('A') && ch <= QLatin1Char('F')) || (ch >= QLatin1Char('a') && ch <= QLatin1Char('f'))) {
                if (ch >= QLatin1Char('0') && ch <= QLatin1Char('9'))
                    m_Chr = QChar(m_Chr.unicode() * 16 + (ch.unicode() - '0'));
                if (ch >= QLatin1Char('A') && ch <= QLatin1Char('F'))
                    m_Chr = QChar(m_Chr.unicode() * 16 + (ch.unicode() - 'A' + 10));
                if (ch >= QLatin1Char('a') && ch <= QLatin1Char('f'))
                    m_Chr = QChar(m_Chr.unicode() * 16 + (ch.unicode() - 'a' + 10));
                if (state == 45) {
                    // Four digits received
                    if (m_Chr.isNonCharacter() || m_Chr.isNull() || m_Chr.unicode() < ' ') {
                        // Invalid Unicode character
                        UngetChar(ch);
                        if (!sendError(CUnicodeError(this, m_Chr)))
                            return false;
                        state = 0;
                    }
                    else {
                        // Correct Unicode character
                        value += m_Chr;
                        m_Chr = QChar();
                        state = 4;
                    }
                }
                else {
                    // Wait for next digit
                    state++;
                }
            }
            else {
                UngetChar(ch);
                state = 0;
            }
            break;

        case 5:
            // Sequence of white-space characters 
            if (ch == QLatin1Char('\t') || ch == QLatin1Char(' ') || ch == QLatin1Char('\n') || ch == QLatin1Char('\r') || ch == QLatin1Char('\f') || ch == QLatin1Char('\v')) {
                // Whitespace characters
                value += ch;
            }
            else {
                // End of whitespaces
                UngetChar(ch);
                token = tok(tToken::T_WS, (value.contains(QLatin1Char('\n')) ? QStringLiteral("\n") : QStringLiteral(" ")));
                return true;
            }
            break;

        default:
            sendError(CInvalidStateError(this, state));
            return false;
        }
    }
    return false;
}


//
// Get next character from the input
//
QChar CLexer::GetChar(void)
{
    if (m_BackChar) {
        // Character pushed back
        QChar ch = m_BackCh;
        m_BackCh = QChar();
        m_BackChar = false;
        return ch;
    }

    // Save current position
    m_LastLine = m_Line;
    m_LastColumn = m_Column;

    while (true) {
        if (m_state == 0) {
            if (m_Stream->atEnd()) {
                // End of stream, send new line and stop reading
                m_state = 3;
                return QLatin1Char('\n');
            }
            QChar ch;
            (*m_Stream) >> ch;
            if (ch == QLatin1Char('\n')) {
                m_Line++;
                m_Column = 1;
                return ch;
            }
            if (ch == QLatin1Char('\\')) {
                // Backslash character, go to state "1" and continue
                m_Column++;
                m_state = 1;
                continue;
            }
            else {
                // Any other character --> send ch
                m_Column++;
                return ch;
            }
        }
        else if (m_state == 1) {
            if (m_Stream->atEnd()) {
                // Backslash before end of stream
                m_state = 0;
                return QLatin1Char('\\');
            }
            QChar ch;
            (*m_Stream) >> ch;
            if (ch == QLatin1Char('\n')) {
                // New line --> ignore and get a next character
                m_Line++;
                m_Column = 1;
                m_state = 0;
                continue;
            }
            else {
                // Backslash followed by ch --> store ch and return backslash
                m_storedChar = ch;
                m_state = 2;
                return QLatin1Char('\\');
            }
        }
        else if (m_state == 2) {
            // Send stored character, and return to state 0
            QChar ch = m_storedChar;
            m_storedChar = QChar();
            m_state = 0;
            return ch;
        }
        else {
            // Any other state --> send the 'null' character
            // that indicates and end of stream
            return QChar();
        }
    }
}


//
// Push back a character.
//
void CLexer::UngetChar(const QChar& ch)
{
    m_BackChar = true;
    m_BackCh = ch;
}


//
// Print error message
//
bool CLexer::sendError(const CError &error) const
{
    if (m_scanner)
        return m_scanner->error(error);
    return true;
}


//
// Create a token
//
CToken CLexer::tok(tToken tok_type, const QString& tok_value) const
{
    return CToken(tok_type, tok_value, filePath(), m_StartPosLine, m_StartPosColumn);
}
