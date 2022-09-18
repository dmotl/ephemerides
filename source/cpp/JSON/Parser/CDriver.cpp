/*!
*  \file      CDriver.cpp
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
#include "CDriver.h"

#include "CIntParser.h"

using namespace JSON::Parser;

//
// Initialization before parsing the input
//
void CDriver::beginParse()
{
	delete m_object;
	m_object = nullptr;
}


//
// Parse input
//
JSON::CObject* CDriver::parse(QTextStream* stream, const QString& filePath, CLogger* logger)
{
	beginParse();
	return endParse(CIntParser(stream, filePath, this, logger).parse());
}


//
// Set contents
//
void CDriver::setContents(const tToken& tok, CObject* object)
{
    if (object != m_object) {
        delete m_object;
        m_object = object;
        m_endToken = tok;
    }
}


//
// Finalization after parsing the input
//
JSON::CObject* CDriver::endParse(bool success)
{ 
	if (success) {
		JSON::CObject* obj = m_object;
		m_object = nullptr;
		return obj;
	}
	else {
		delete m_object;
		m_object = nullptr;
		return nullptr;
	}
}
