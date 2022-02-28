/*!
*  \file      CElevation.h
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
* \brief Elevation
*
* The CElevation class holds a horizontal elevation of celestial coordinate
* system that defines a position of an object and uses the observer's
* horizont and meridian as the fundamental planes.
*
* The value is stored internally in radians.
* Positive elevations are above the horizon and negative ones are below.
*/
class CElevation
{
public:
	/*!
	* \brief Constructor
	*
	* The constructor creates an object that represents an invalid or unknown elevation
	*/
	CElevation() : m_radians(invalidElevation()) {}

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a elevation in radians. The value is clipped
	* to the range of -pi and pi.
	* \param radians elevation in radians.
	*/
	CElevation(double radians) { m_radians = cropAngle(radians); }

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a Unicode string. If the input string
	* is not a valid representation of elevation, the constructor creates an invalid
	* object.
	*
	* \param str input string
	*/
	explicit CElevation(const std::wstring& str);

	/*! \brief Check if the object holds a valid elevation */
	bool isValid(void) const { return m_radians != invalidElevation(); }

	/*!
	* \brief Set elevation
	*
	* The value is clipped to the range of -pi and pi.
	* \param radians elevation in radians.
	*/
	void setRadians(double radians) { m_radians = cropAngle(radians); }

	/*! \brief Elevation in radians */
	double radians() const { return m_radians; }

	/*!
	* \brief Set elevation
	*
	* The input value is converted to radians and clipped to the
	* range of -pi and pi.
	*/
	void setDegrees(double degrees) { setRadians(degToRad(degrees)); }

	/*! \brief Elevation in degrees */
	double degrees() const { return radToDeg(m_radians); }

	/*! \brief String representation of the elevation */
	std::wstring toString() const;

	/*! \brief A numeric value used as an invalid elevation */
	static double invalidElevation() { return DBL_MAX; }

	/*!
	* \brief Crop elevation
	*
	* The input value specify a elevation in radians. The function
	* clips the input value to the range of -pi..pi and returns
	* the clipped value.
	*/
	static double cropAngle(double rad);

	/*!
	* \brief Elevation from angle in degrees
	*
	* The method creates a new CElevation object from an angle specified
	* in degrees. Positive values are for the Northern hemisphere and negative
	* ones are for Southern hemisphere.
	* \param degrees elevation in degrees.
	*/
	static CElevation fromDegrees(double degrees) { return CElevation(degToRad(degrees)); }

	/*! \brief degrees-to-radians conversion */
	static double degToRad(double degrees);

	/*! \brief radians-to-degrees conversion */
	static double radToDeg(double radians);

	/*! \brief comparison operator */
	inline bool operator==(const CElevation& other) const { return m_radians == other.m_radians; }

	/*! \brief comparison operator */
	inline bool operator!=(const CElevation& other) const { return !this->operator==(other); }

private:
	// Elevation in radians
	double m_radians;
};
