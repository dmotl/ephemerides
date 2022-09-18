/*!
*  \file      CParser.cpp
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
#include "CParser.h"

#include "CDriver.h"

using namespace JSON::Parser;

//
// Create JSON from a string
//
JSON::CObject* CParser::parseFromString(const QString& instr, CLogger* logger)
{
	QString string = instr;
	string.detach();
	CDriver driver;
	QTextStream stream(&string);
	return driver.parse(&stream, QString(), logger);
}


//
// Create JSON from a file
//
JSON::CObject* CParser::parseFromFile(const QString& filePath, CLogger* logger)
{
	QFile f(filePath);
	if (f.open(QFile::ReadOnly)) {
		CDriver driver;
		QTextStream stream(&f);
		return driver.parse(&stream, filePath, logger);
	}
	return nullptr;
}
