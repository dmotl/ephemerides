/*!
*  \file      CToken.h
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

namespace JSON::Scanner
{
    // Constants
    // ---------

    /// \brief Preprocessor token types
    enum class tToken
    {
        /// Identifiers and keywords
        T_ID,

        /// String literals
        T_STR,

        /// Numerical literals
        T_NUM,

        /// Operators and punctuation
        T_OP,

        /// White space character sequences (internal use only)
        T_WS,

        /// Other non-whitespace characters (internal use only)
        T_OTHER,

        // End of file or input string (never passed to processToken)
        T_END
    };

    // Functions
    // ---------

    /// \brief Get a string representation for a token.
    ///
    /// The tokenName function is used to print debugging symbols as they are found in
    /// the source stream. Provide a text representation for each T_xxx value.
    /// \param t token type
    /// \return pointer to a null-terminated string with a name represeting given token type
    const char* tokenName(tToken t);

    // Classes
    // -------

    /// \brief Token event descriptor
    ///
    /// The Token class keep holds data (type, value) and context (location)
    /// of a preprocessing token.
    struct CToken
    {
        /// Token type
        tToken token;

        /// Token value
        QString tok_value;

        /// Path to the file where the token was found
        QString fpath;

        /// Line (starting from 1) of position of the
        /// beginning of the token in the file specified by fpath.
        int line;

        /// Line (starting from 1) of position of the
        /// beginning of the token in the file specified by fpath.
        int column;

        /// Default constructor
        CToken() : token(tToken::T_OTHER), line(0), column(0) {}

        /// Constructor
        /// \param t token type
        /// \param v token value
        /// \param p file path (optional)
        /// \param l line number (optional)
        /// \param c column number (optional)
        CToken(tToken t, const QString& v, const QString& p = QString(), int l = 0, int c = 0) : token(t), tok_value(v), fpath(p), line(l), column(c) {}

        /// Dump token descriptor to a string. Includes position, type and value.
        QString toString(void) const;
    };
}
