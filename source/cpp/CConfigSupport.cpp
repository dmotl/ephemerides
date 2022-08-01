/*!
*  \file      CConfigSupport.cpp
*  \author    David Motl
*  \date      2022-07-26
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
#include "CConfigSupport.h"

void CConfigSupport::setXmlValue(QDomElement& xml, const char* elementName, int value)
{

}

void CConfigSupport::setXmlValue(QDomElement& xml, const char* elementName, const QString& value)
{

}

void CConfigSupport::setXmlValue(QDomElement& xml, const char* elementName, const QStringList& values)
{

}

void CConfigSupport::setXmlValue(QDomElement& xml, const char* elementName, const QMap<QString, bool>& value)
{

}

int CConfigSupport::loadXmlValueInt(const QDomElement& xml, const char* elementName, int defaultValue)
{
	return defaultValue;
}

bool CConfigSupport::loadXmlValueBool(const QDomElement& xml, const char* elementName, bool defaultValue)
{
	return defaultValue;
}

double CConfigSupport::loadXmlValueReal(const QDomElement& xml, const char* elementName, double defaultValue)
{
	return defaultValue;
}

QMap<QString, bool> CConfigSupport::loadXmlValueMap(const QDomElement& xml, const char* elementName)
{
	return QMap<QString, bool>();
}

QStringList CConfigSupport::loadXmlValueList(const QDomElement& xml, const char* elementName)
{
	return QStringList();
}