/*!
*  \file      CVarEphemeris.h
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

#include "CEphemerisBase.h"
#include "CFilterStack.h"

class CSource;

/*
* \brief Variable star ephemeris
*
* The CVarEphemeris implements the computation
* of ephemeris of variable stars and range of dates.
*
*/
class CVarEphemeris: public CEphemerisBase
{
public:
	// Constructor
	CVarEphemeris(const CGeoCoordinates& location, CSource* source, const CFilterStack& filter) : m_loc(location), m_source(source), m_filter(filter) {}

	// Update ephemeris
	void update(CJulianDate start, CJulianDate end, tCancelledFn cbCancelled, tSetCaption cbSetCaption, tSetProgressMaxFn 
		cbSetProgressRange, tSetProgressValueFn cbSetProgressValue) override;

protected:
	CGeoCoordinates m_loc;
	CSource* m_source;
	CFilterStack m_filter;
};
