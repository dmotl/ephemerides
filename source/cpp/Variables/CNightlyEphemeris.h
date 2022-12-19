/*!
*  \file      CNightlyEphemeris.h
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

/*
* \brief Nightly ephemeris 
*
* The CNightlyEphemeris implements the computation 
* of ephemeris of variable stars for the given date (night).
*
*/
class CNightlyEphemeris : CEphemerisBase
{
public:
	// Constructor
	CNightlyEphemeris() {}

	// Update ephemerides
	void update();
};
