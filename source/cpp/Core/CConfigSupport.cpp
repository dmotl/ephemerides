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

QJsonDocument CConfigSupport::fromFile(const QString& filePath, QString* error_msg)
{
	QFile file(filePath);
	if (file.open(QIODeviceBase::ReadOnly)) {
		QJsonParseError json_error;
		QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &json_error);
		if (json_error.error) {
			if (error_msg)
				*error_msg = json_error.errorString();
			return QJsonDocument();
		}
		return doc;
	}
	else {
		if (error_msg)
			*error_msg = QStringLiteral("Failed to open the file: ") + QDir(filePath).toNativeSeparators(filePath);
		return QJsonDocument();
	}
}

bool CConfigSupport::toFile(const QJsonDocument& json, const QString& filePath, QString* error_msg)
{
	QFile file(filePath);
	if (file.open(QIODeviceBase::WriteOnly)) {
		file.write(json.toJson());
		file.close();
		return true;
	}
	else {
		if (error_msg)
			*error_msg = QStringLiteral("Failed to create the file: ") + QDir(filePath).toNativeSeparators(filePath);
		return false;
	}
}
