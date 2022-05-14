/*!
*  \file      CDeclination.h
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
* \brief Declination
*
* The CDeclination class holds one of the two equatorial coordinates that 
* defines a point on the celestial sphere. The declination is an angular
* distance of a point measured north or south of the celestial equator, 
* along the hour circle passing through the point in question. 
* 
* The value is stored internally in radians.
* Positive declinations are north of celestial equator and negative ones
* are south.
*/
class CDeclination
{
public:
	/*!
	* \brief Constructor
	*
	* The constructor creates an object that represents an invalid or unknown declination
	*/
	CDeclination() : m_radians(invalidDeclination()) {}

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a declination in radians. The value is clipped
	* to the range of -pi and pi.
	* \param radians declination in radians.
	*/
	CDeclination(double radians) { m_radians = cropAngle(radians); }

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a Unicode string. If the input string
	* is not a valid representation of declination, the constructor creates an invalid
	* object.
	*
	* \param str input string
	*/
	explicit CDeclination(const std::wstring& str);

	/*! \brief Check if the object holds a valid declination */
	bool isValid(void) const { return m_radians != invalidDeclination(); }

	/*!
	* \brief Set declination
	*
	* The value is clipped to the range of -pi and pi.
	* \param radians declination in radians.
	*/
	void setRadians(double radians) { m_radians = cropAngle(radians); }

	/*! \brief Declination in radians */
	double radians() const { return m_radians; }

	/*!
	* \brief Set declination
	*
	* The input value is converted to radians and clipped to the
	* range of -pi and pi.
	*/
	void setDegrees(double degrees) { setRadians(degToRad(degrees)); }

	/*! \brief Declination in degrees */
	double degrees() const { return radToDeg(m_radians); }

	/*! \brief String representation of the declination */
	std::wstring toString() const;

	/*! \brief A numeric value used as an invalid declination */
	static double invalidDeclination() { return DBL_MAX; }

	/*!
	* \brief Crop declination
	*
	* The input value specify a declination in radians. The function
	* clips the input value to the range of -pi..pi and returns
	* the clipped value.
	*/
	static double cropAngle(double rad);

	/*!
	* \brief Declination from angle in degrees
	*
	* The method creates a new CDeclination object from an angle specified
	* in degrees. Positive declinations are north of celestial equator and negative ones
    * are south.
	* \param degrees declination in degrees.
	*/
	static CDeclination fromDegrees(double degrees) { return CDeclination(degToRad(degrees)); }

	/*! \brief degrees-to-radians conversion */
	static double degToRad(double degrees);

	/*! \brief radians-to-degrees conversion */
	static double radToDeg(double radians);

	/*! \brief comparison operator */
	inline bool operator==(const CDeclination& other) const { return m_radians == other.m_radians; }

	/*! \brief comparison operator */
	inline bool operator!=(const CDeclination& other) const { return !this->operator==(other); }

private:
	// Declination in radians
	double m_radians;
};
