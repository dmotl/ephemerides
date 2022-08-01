/*!
*  \file      CMainTabWidget.h
*  \author    David Motl
*  \date      2022-01-31
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

#include <QtXml>

class CConfigSupport
{
public:
	CConfigSupport() = default;

	static void setXmlValue(QDomElement& xml, const char* elementName, int value);
	static void setXmlValue(QDomElement& xml, const char* elementName, const QString& value);
	static void setXmlValue(QDomElement& xml, const char* elementName, const QStringList& values);
	static void setXmlValue(QDomElement& xml, const char* elementName, const QMap<QString, bool>& value);

	static int loadXmlValueInt(const QDomElement& xml, const char* elementName, int defaultValue = 0);
	static bool loadXmlValueBool(const QDomElement& xml, const char* elementName, bool defaultValue = false);
	static double loadXmlValueReal(const QDomElement& xml, const char* elementName, double defaultValue = 0);
	static QMap<QString, bool> loadXmlValueMap(const QDomElement& xml, const char* elementName);
	static QStringList loadXmlValueList(const QDomElement& xml, const char* elementName);
};
