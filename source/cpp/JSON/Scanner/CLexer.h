/*!
*  \file      CLexer.h
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
    using CError = JSON::Utils::CError;
    class CScanner;

    /// Lexel (tokenizer)
    ///
    /// The CLexer class decomposes an input stream into tokens:
    ///  - Identifiers (includes keywords)
    ///  - Numeric literals
    ///  - String literals
    ///  - Operators and punctuation
    ///  - White-space character sequences (`\\n`, `\\t`, `' '`, `\\f`, `\\v`)
    ///  - Other non-whitespace characters
    ///
    class CLexer
    {
    public:
        /// Constructor
        /// 
        /// \param driver
        /// \param filePath path of a parsed file ("" when parsing a string)
        /// \param input input character stream
        CLexer(CScanner* driver, const QString &filePath, QTextStream* input);

        /// Destructor
        ~CLexer(void) {}

        /// Get next token
        ///
        /// The GetSym method retrieve character from the input stream and group them
        /// into a preprocessing token. If a preprocessing token has been received,
        /// the token is stored to the token parameter and the method returns true.
        /// If an irecoverable error occurs on input or an end of the input has been
        /// reached, the function returns false.
        ///
        /// \param state context (some directives requires special processing of the input)
        /// \param token token found
        /// \return Returns _true_ if a token was found or _false_ if an end of input was reached
        bool GetSym(CToken &token);

        /// Get path to the parsed file
        QString filePath(void) const { return m_filePath; }

        /// Get position of the character returns by the last call of GetChar().
        /// This is used to indicate a position of an error in the input stream.
        /// \param line line number (starting with 1)
        /// \param column column number (starting with 1)
        void GetPos(int& line, int& column) const {
            line = m_LastLine; column = m_LastColumn;
        }

    private:
        // File path
        QString         m_filePath;

        // File handle
        QTextStream     *m_Stream;				

        // Unicode character
        QChar           m_Chr;

        // Actual parser's reading position
        // This is not the position of the character
        // returned by last call to the GetChar() method.
        int			    m_Line, m_Column;		

        // Position of the last character
        // This is the position of the character
        // returned by last call to the GetChar() method.
        int             m_LastLine, m_LastColumn;

        // Starting position of the current
        // preprocessing-token.
        // This is reported as the position of the token.
        int             m_StartPosLine, m_StartPosColumn;

        // There is a character pushed back
        bool            m_BackChar;             

        // Character pushed back
        QChar		    m_BackCh;				

        // Callback for handling error messages
        CScanner*       m_scanner;

        // Last input character
        QChar           m_storedChar;

        // Status code
        int             m_state;

        // Get next token
        bool _GetSym(CToken& token);

        // Get next character from the input
        QChar GetChar();

        // Push back a character. Next GetChar will return it.
        void UngetChar(const QChar &ch);

        // Print error message through the classifier
        bool sendError(const CError &error) const;

        // Create a token
        CToken tok(tToken tok_type, const QString& tok_value = QString()) const;
    };
}
