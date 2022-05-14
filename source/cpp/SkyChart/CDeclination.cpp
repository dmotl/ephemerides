/*!
*  \file      CDeclination.cpp
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
#include "CDeclination.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <assert.h>
#include <sstream>

//
// Constructor from a Unicode string
//
CDeclination::CDeclination(const std::wstring& str) : m_radians(invalidDeclination())
{
	wchar_t* endptr;

	double val = std::wcstod(str.c_str(), &endptr);
	if (*endptr == '\0')
		m_radians = cropAngle(val / 180 * M_PI);
}


//
// Clipping to range -pi..pi
//
double CDeclination::cropAngle(double rad)
{
	if (rad > M_PI_2)
		return M_PI_2;
	else if (rad < -M_PI_2)
		return -M_PI_2;
	else
		return rad;
}


//
// Degrees to radians
//
double CDeclination::degToRad(double degrees)
{
	return degrees / 180 * M_PI;
}


//
// Radians to degrees
//
double CDeclination::radToDeg(double radians)
{
	return radians / M_PI * 180;
}


//
// Convert to string
//
std::wstring CDeclination::toString() const
{
	std::wostringstream strs;
	strs << degrees();
	return strs.str();
}
