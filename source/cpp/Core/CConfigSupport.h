/*!
*  \file      CConfigSupport.h
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

#include <QtCore>

class CConfigSupport
{
public:
	CConfigSupport() = default;

	static QJsonDocument fromFile(const QString& filePath, QString* error_msg = nullptr);

	static bool toFile(const QJsonDocument& json, const QString& filePath, QString* error_msg = nullptr);

	static inline void configSetValue(QJsonObject& obj, const char* elementName, int value)
	{
		obj.insert(QLatin1String(elementName), value);
	}

	static inline void configSetValue(QJsonObject& obj, const char* elementName, const QString& value)
	{
		obj.insert(QLatin1String(elementName), value);
	}

	static inline void configSetValue(QJsonObject& obj, const char* elementName, const QStringList& values)
	{
		QJsonArray ja;
		for (const QString & str: values)
			ja.append(str);
		obj.insert(QLatin1String(elementName), ja);
	}

	static inline void configSetValue(QJsonObject& obj, const char* elementName, const QMap<QString, bool>& value)
	{
		QJsonObject jo;
		for (const QString& key: value.keys())
			jo.insert(key, value[key]);
		obj.insert(QLatin1String(elementName), jo);
	}

	static inline int configGetValueInt(const QJsonObject& obj, const char* elementName, int defaultValue = 0)
	{
		return obj[QLatin1String(elementName)].toInt(defaultValue);
	}

	static inline bool configGetValueBool(const QJsonObject& obj, const char* elementName, bool defaultValue = false)
	{
		return obj[QLatin1String(elementName)].toBool(defaultValue);
	}
	static inline double configGetValueReal(const QJsonObject& obj, const char* elementName, double defaultValue = 0)
	{
		return obj[QLatin1String(elementName)].toDouble(defaultValue);
	}
	static QString configGetValueString(const QJsonObject& obj, const char* elementName, const QString& defaultValue = QString())
	{
		return obj[QLatin1String(elementName)].toString(defaultValue);
	}
	static QMap<QString, bool> configGetValueMap(const QJsonObject& obj, const char* elementName)
	{
		QMap<QString, bool> retval;

		auto jo = obj[QLatin1String(elementName)].toObject();
		auto cbegin = jo.constBegin(), cend = jo.constEnd();
		while (cbegin != cend) {
			QString key = cbegin.key();
			if (cbegin->isBool()) 
				retval.insert(key, cbegin.value().toBool(false));
			++cbegin;
		}
		return retval;
	}
	static QStringList configGetValueList(const QJsonObject& obj, const char* elementName, bool skipEmptyItems = true)
	{
		QList<QString> retval;

		auto ja = obj[QLatin1String(elementName)].toArray();
		auto cbegin = ja.constBegin(), cend = ja.constEnd();
		while (cbegin != cend) {
			QString value = cbegin->toString();
			if (!skipEmptyItems || !value.isEmpty())
				retval.append(value);
			++cbegin;
		}
		return retval;
	}
};
