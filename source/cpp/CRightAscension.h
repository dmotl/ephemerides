/*!
*  \file      CRightAscension.h
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
* \brief CRightAscension
*
* The CRightAscension class holds one of the two equatorial coordinates that 
* defines a point on the celestial sphere. The right ascension is an angular
* distance of a point measured eastward along the celestial equator.
* 
* The value is stored internally in radians.
*
*/
class CRightAscension
{
public:
	/*!
	* \brief Constructor
	*
	* The constructor creates an object that represents an invalid or unknown right ascension
	*/
	CRightAscension() : m_radians(invalidRightAscension()) {}

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a right ascension in radians. The value is normalized
	* to the range of (0 and 2*pi>.
	* \param radians right ascension in radians.
	*/
	CRightAscension(double radians) { m_radians = normalizeAngle(radians); }

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a Unicode string. If the input string
	* is not a valid representation of right ascension, the constructor creates an invalid
	* object.
	*
	* \param str input string
	*/
	explicit CRightAscension(const std::wstring& str);

	/*! \brief Check if the object holds a valid right ascension */
	bool isValid(void) const { return m_radians != invalidRightAscension(); }

	/*!
	* \brief Set right ascension
	*
	* The value is normalized to the range of (0 and 2*pi>.
	* \param radians right ascension in radians.
	*/
	void setRadians(double radians) { m_radians = normalizeAngle(radians); }

	/*! \brief Right ascension in radians */
	double radians() const { return m_radians; }

	/*!
	* \brief Set right ascension
	*
	* The input value is converted to radians and normalized to the
	* range of (0 and 2*pi>.
	*/
	void setHours(double hours) { setRadians(hoursToRad(hours)); }

	/*! \brief Right ascension in degrees */
	double hours() const { return radToHours(m_radians); }

	/*! \brief String representation of the right ascension */
	std::wstring toString() const;

	/*! \brief A numeric value used as an invalid right ascension */
	static double invalidRightAscension() { return DBL_MAX; }

	/*!
	* \brief Normalize right ascension
	*
	* The input value specify a right ascension in radians. The function
	* normalizes the input value to the range of (0 and 2*pi> and returns
	* the normalized value. The function can return zero, the return
	* value is always less then 2*pi.
	*/
	static double normalizeAngle(double rad);

	/*!
	* \brief Right ascension from angle in degrees
	*
	* The method creates a new CRightAscension object from an angle specified
	* in degrees. Positive values are east of prime meridian and negative
	* ones are west.
	* \param degrees right ascension in hours 
	*/
	static CRightAscension fromHours(double hours) { return CRightAscension(hoursToRad(hours)); }

	/*! \brief hours-to-radians conversion */
	static double hoursToRad(double hours);

	/*! \brief radians-to-degrees conversion */
	static double radToHours(double radians);

	/*! \brief comparison operator */
	inline bool operator==(const CRightAscension& other) const { return m_radians == other.m_radians; }

	/*! \brief comparison operator */
	inline bool operator!=(const CRightAscension& other) const { return !this->operator==(other); }

private:
	// Right ascension in radians
	double m_radians;
};
