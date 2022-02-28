/*!
*  \file      CRightAscension.cpp
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
#include "CRightAscension.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <assert.h>
#include <sstream>

//
// Constructor from a Unicode string
//
CRightAscension::CRightAscension(const std::wstring& str) : m_radians(invalidRightAscension())
{
	wchar_t* endptr;

	double val = std::wcstod(str.c_str(), &endptr);
	if (*endptr == '\0')
		m_radians = normalizeAngle(val / 180 * M_PI);
}


//
// Normalization of the angle
//
double CRightAscension::normalizeAngle(double rad)
{
	double i;

	if (rad > M_PI) {
		rad = modf((rad + M_PI) / (2 * M_PI), &i);
		rad = rad * (2 * M_PI) - M_PI;
	}
	else if (rad < -M_PI) {
		rad = modf((M_PI - rad) / (2 * M_PI), &i);
		rad = (1 - rad) * (2 * M_PI) - M_PI;
	}
	if (rad == -M_PI)
		return M_PI;
	return rad;
}


//
// Hours to radians
//
double CRightAscension::hoursToRad(double hours)
{
	return (hours / 12 * M_PI);
}


//
// Radians to hours
//
double CRightAscension::radToHours(double radians)
{
	return (radians / M_PI * 12);
}


//
// Conversion to a string
//
std::wstring CRightAscension::toString() const
{
	std::wostringstream strs;
	strs << hours();
	return strs.str();
}
