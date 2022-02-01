/*!
*  \file      CLatitude.h
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
* \brief CLatitude
* 
* The CLatitude class holds a geograpic latitude as a double-precision 
* floating point number. The value is stored internally in radians.
* 
* Positive latitudes are for Northern hemisphere and negative ones are
* for Southern hemisphere.
*/
class CLatitude
{
public:
	/*! 
	* \brief Constructor
	*
	* The constructor creates an object that represents an invalid or unknown latitude
	*/
	CLatitude() : m_radians(invalidLatitude()) {}

	/*!
	* \brief Constructor
	* 
	* The constructor creates an object from a latitude in radians. The value is clipped
	* to the range of -pi and pi.
	* \param radians latitude in radians.
	*/
	explicit CLatitude(double radians) { m_radians = cropAngle(radians); }

	/*!
	* \brief Constructor
	* 
	* The constructor creates an object from a Unicode string. If the input string
	* is not a valid representation of latitude, the constructor creates an invalid
	* object.
	* 
	* \param str input string
	*/
	explicit CLatitude(const std::wstring& str);

	/*! \brief Check if the object holds a valid latitude */
	bool isValid(void) const { return m_radians != invalidLatitude(); }

	/*!
	* \brief Set latitude
	* 
	* The value is clipped to the range of -pi and pi.
	* \param radians latitude in radians.
	*/
	void setRadians(double radians) { m_radians = cropAngle(radians); }

	/*! \brief Latitude in radians */
	double radians() const { return m_radians; }

	/*!
	* \brief Set latitude
	* 
	* The input value is converted to radians and clipped to the
	* range of -pi and pi.
	*/
	void setDegrees(double degrees) { setRadians(degToRad(degrees)); }

	/*! \brief Latitude in degrees */
	double degrees() const { return radToDeg(m_radians); }

	/*! \brief String representation of the latitude */
	std::wstring toString() const;

	/*! \brief A numeric value used as an invalid latitude */
	static double invalidLatitude() { return DBL_MAX; }

	/*! 
	* \brief Crop latitude 
	* 
	* The input value specify a latitude in radians. The function
	* clips the input value to the range of -pi..pi and returns 
	* the clipped value.
	*/
	static double cropAngle(double rad);

	/*! 
	* \brief Latitude from angle in degrees
	* 
	* The method creates a new CLatitude object from an angle specified
	* in degrees. Positive values are for the Northern hemisphere and negative
	* ones are for Southern hemisphere.
	* \param degrees latitude in degrees.
	*/
	static CLatitude fromDegrees(double degrees) { return CLatitude(degToRad(degrees)); }

	/*! \brief degrees-to-radians conversion */
	static double degToRad(double degrees);

	/*! \brief radians-to-degrees conversion */
	static double radToDeg(double radians);

	/*! \brief comparison operator */
	inline bool operator==(const CLatitude& other) const { return m_radians == other.m_radians; }

	/*! \brief comparison operator */
	inline bool operator!=(const CLatitude& other) const { return !this->operator==(other); }

private:
	// Latitude in radians
	double m_radians;
};
