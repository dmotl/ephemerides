/*!
*  \file      CAzimuth.cpp
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
#include "CAzimuth.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <assert.h>
#include <sstream>

//
// Constructor from a Unicode string
//
CAzimuth::CAzimuth(const std::wstring& str) : m_radians(invalidAzimuth())
{
	wchar_t* endptr;

	double val = std::wcstod(str.c_str(), &endptr);
	if (*endptr == '\0')
		m_radians = normalizeAngle(val / 180 * M_PI);
}


//
// Normalization of the angle
//
double CAzimuth::normalizeAngle(double rad)
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
// Degrees to radians
//
double CAzimuth::degToRad(double degrees)
{
	return (degrees / 180 * M_PI);
}


//
// Radians to degrees
//
double CAzimuth::radToDeg(double radians)
{
	return (radians / M_PI * 180);
}


//
// Conversion to a string
//
std::wstring CAzimuth::toString() const
{
	std::wostringstream strs;
	strs << degrees();
	return strs.str();
}


//
// Nearest point on 16-point compass rose
//
CAzimuth::tCompassPoint CAzimuth::toCompassPoint(double radians)
{
	radians = normalizeAngle(radians);
	if (radians < 0) {
		switch ((int)(radians * 8 / M_PI - 0.5))
		{
		case -8:
			return N;
		case -7:
			return NNE;
		case -6:
			return NE;
		case -5:
			return ENE;
		case -4:
			return E;
		case -3:
			return ESE;
		case -2:
			return SE;
		case -1:
			return SSE;
		default:
			return S;
		}
	}
	else {
		switch ((int)(radians * 8 / M_PI + 0.5))
		{
		case 0:
			return S;
		case 1:
			return SSW;
		case 2:
			return SW;
		case 3:
			return WSW;
		case 4:
			return W;
		case 5:
			return WNW;
		case 6:
			return NW;
		case 7:
			return NNW;
		default:
			return N;
		}
	}
}
