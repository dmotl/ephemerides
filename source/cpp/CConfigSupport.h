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

#include "CObject.h"

class CConfigSupport
{
public:
	CConfigSupport() = default;

	static void configSetValue(JSON::CObject& obj, const char* elementName, int value);
	static void configSetValue(JSON::CObject& obj, const char* elementName, const QString& value);
	static void configSetValue(JSON::CObject& obj, const char* elementName, const QStringList& values);
	static void configSetValue(JSON::CObject& obj, const char* elementName, const QMap<QString, bool>& value);

	static int configGetValueInt(const JSON::CObject& obj, const char* elementName, int defaultValue = 0);
	static bool configGetValueBool(const JSON::CObject& obj, const char* elementName, bool defaultValue = false);
	static double configGetValueReal(const JSON::CObject& obj, const char* elementName, double defaultValue = 0);
	static QMap<QString, bool> configGetValueMap(const JSON::CObject& obj, const char* elementName);
	static QStringList configGetValueList(const JSON::CObject& obj, const char* elementName);
};
