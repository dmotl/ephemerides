/*!
*  \file      CToken.cpp
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
#include "CToken.h"

using namespace JSON::Scanner;

//
// Preprocessor token names (for debug output)
//
const char* JSON::Scanner::tokenName(tToken t)
{
    switch (t) {
    case tToken::T_ID:
        return "ID";
    case tToken::T_STR:
        return "STR";
    case tToken::T_NUM:
        return "NUM";
    case tToken::T_OP:
        return "OP";
    case tToken::T_WS:
        return "WS";
    case tToken::T_END:
        return "END";
    default:
        return NULL;
    }
}


//
// Convert token event to a string (for debuggin)
//
QString CToken::toString(void) const
{
    QString prefix;
    if (!fpath.isEmpty()) {
        if (line > 0 && column > 0)
            prefix = QDir::toNativeSeparators(fpath) + QStringLiteral(" (line %1, column %2):\n").arg(line).arg(column);
        else
            prefix = QDir::toNativeSeparators(fpath) + QStringLiteral(":\n");
    }
    else {
        if (line > 0 && column > 0)
            prefix = QStringLiteral("Line %1, column %2: ").arg(line).arg(column);
    }
    return prefix + QLatin1String(tokenName(token)) + QStringLiteral(" ") + tok_value;
}
