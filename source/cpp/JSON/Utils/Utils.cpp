/*!
*  \file      CUtils.cpp
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
#include "Utils.h"

using namespace JSON::Utils;

//
// Replace quote with \" and backslash with two backslashes
//
QString JSON::Utils::encodeString(const QString& str)
{
    QString retval = QStringLiteral("\"");
    for (int i = 0; i < str.length(); i++) {
        const QChar& ch = str[i];
        if (ch == QLatin1Char('\"') || ch == QLatin1Char('\\'))
            retval.append(QLatin1Char('\\'));
        retval.append(ch);
    }
    return retval + QStringLiteral("\"");
}
