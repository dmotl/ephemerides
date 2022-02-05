/*!
*  \file      utils.h
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

/*
* \brief Degrees to radians
* 
* The macro converts an angle in degrees to radians
* \param deg angle in degrees
* \return angle in radians
*/
#define DEG_TO_RAD(deg) ((deg) / 180 * M_PI)

/*
* \brief Radians to degrees
*
* The macro converts an angle in radians to degrees
* \param deg angle in radians
* \return angle in degrees
*/
#define RAD_TO_DEG(rad) ((rad) / M_PI * 180)

/*
* \brief Time to fractions of day
*
* The macro converts time specified as hour, minute and second
* to a fractional part of the day since midnight.
* \param h hour
* \param m minute
* \param s second
* \return fractional part of the day since midnight
* 
*/
#define HMS_TO_JD(h, m, s) (((h) + static_cast<double>(m) / 60 + static_cast<double>(s) / 3600) / 24)

namespace Utils
{
	/*
	* \brief Angular distance of two objects
	* 
	* The function computes angular distance an a unit sphere of two objects specified 
	* by polar coordinates in radians.
	* 
	* \param Ra1 first coordinate of the first object, in radians
	* \param Dec1 second coordinate of the first object, in radians
	* \param Ra2 first coordinate of the second object, in radians
	* \param Dec2 second coordinate of the second object, in radians
	* \return angular distance in radians
	*/
	double AngularDistance(double Ra1, double De1, double Ra2, double De2);
};
