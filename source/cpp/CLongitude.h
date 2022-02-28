/*!
*  \file      CLongitude.h
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

#include <float.h>
#include <string>

/*
* \brief Longitude
*
* The CLongitude class holds a geograpic longitude as a double-precision
* floating point number. The value is stored internally in radians.
*
* Positive longitudes are east of the prime meridian and negative ones
* are west.
*/
class CLongitude
{
public:
	/*!
	* \brief Constructor
	*
	* The constructor creates an object that represents an invalid or unknown longitude
	*/
	CLongitude() : m_radians(invalidLongitude()) {}

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a longitude in radians. The value is normalized
	* to the range of (0 and 2*pi>.
	* \param radians longitude in radians.
	*/
	CLongitude(double radians) { m_radians = normalizeAngle(radians); }

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a Unicode string. If the input string
	* is not a valid representation of longitude, the constructor creates an invalid
	* object.
	*
	* \param str input string
	*/
	explicit CLongitude(const std::wstring& str);

	/*! \brief Check if the object holds a valid longitude */
	bool isValid(void) const { return m_radians != invalidLongitude(); }

	/*!
	* \brief Set longitude
	*
	* The value is normalized to the range of (0 and 2*pi>.
	* \param radians longitude in radians.
	*/
	void setRadians(double radians) { m_radians = normalizeAngle(radians); }

	/*! \brief Longitude in radians */
	double radians() const { return m_radians; }

	/*!
	* \brief Set longitude
	*
	* The input value is converted to radians and normalized to the
	* range of (0 and 2*pi>.
	*/
	void setDegrees(double degrees) { setRadians(degToRad(degrees)); }

	/*! \brief Longitude in degrees */
	double degrees() const { return radToDeg(m_radians); }

	/*! \brief String representation of the longitude */
	std::wstring toString() const;

	/*! \brief A numeric value used as an invalid longitude */
	static double invalidLongitude() { return DBL_MAX; }

	/*!
	* \brief Normalize longitude
	*
	* The input value specify a longitude in radians. The function
	* normalizes the input value to the range of (0 and 2*pi> and returns
	* the normalized value. The function can return zero, the return
	* value is always less then 2*pi.
	*/
	static double normalizeAngle(double rad);

	/*!
	* \brief Longitude from angle in degrees
	*
	* The method creates a new CLongitude object from an angle specified
	* in degrees. Positive values are east of prime meridian and negative
	* ones are west.
	* \param degrees longitude in degrees.
	*/
	static CLongitude fromDegrees(double degrees) { return CLongitude(degToRad(degrees)); }

	/*! \brief degrees-to-radians conversion */
	static double degToRad(double degrees);

	/*! \brief radians-to-degrees conversion */
	static double radToDeg(double radians);

	/*! \brief comparison operator */
	inline bool operator==(const CLongitude& other) const { return m_radians == other.m_radians; }

	/*! \brief comparison operator */
	inline bool operator!=(const CLongitude& other) const { return !this->operator==(other); }

private:
	// Longitude in radians
	double m_radians;
};
