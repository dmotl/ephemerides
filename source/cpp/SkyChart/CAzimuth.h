/*!
*  \file      CAzimuth.h
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
* \brief Azimuth
*
* The CAzimuth class holds a horizontal azimuth of celestial coordinate
* system that defines a position of an object and uses the observer's
* horizont and meridian as the fundamental planes. 
* 
* The value is stored internally in radians. 
* Positive azimuth values are east of the true north and negative ones
* are west.
*/
class CAzimuth
{
public:
	/* \breif Points on 16-point compass rose */
	enum tCompassPoint
	{
		N, NNE, NE, ENE, E, ESE, SE, SSE, S, SSW, SW, WSW, W, WNW, NW, NNW
	};

	/*!
	* \brief Constructor
	*
	* The constructor creates an object that represents an invalid or unknown azimuth
	*/
	CAzimuth() : m_radians(invalidAzimuth()) {}

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a azimuth in radians. The value is normalized
	* to the range of (0 and 2*pi>.
	* \param radians azimuth in radians.
	*/
	CAzimuth(double radians) { m_radians = normalizeAngle(radians); }

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a Unicode string. If the input string
	* is not a valid representation of azimuth, the constructor creates an invalid
	* object.
	*
	* \param str input string
	*/
	explicit CAzimuth(const std::wstring& str);

	/*! \brief Check if the object holds a valid azimuth */
	bool isValid(void) const { return m_radians != invalidAzimuth(); }

	/*!
	* \brief Set azimuth
	*
	* The value is normalized to the range of (0 and 2*pi>.
	* \param radians azimuth in radians.
	*/
	void setRadians(double radians) { m_radians = normalizeAngle(radians); }

	/*! \brief Azimuth in radians */
	double radians() const { return m_radians; }

	/*!
	* \brief Set azimuth
	*
	* The input value is converted to radians and normalized to the
	* range of (0 and 2*pi>.
	*/
	void setDegrees(double degrees) { setRadians(degToRad(degrees)); }

	/*! \brief Azimuth in degrees */
	double degrees() const { return radToDeg(m_radians); }

	/*! \brief String representation of the azimuth */
	std::wstring toString() const;

	/*! \brief Compass point abbreviation
	*
	* The function returns an abbreviation of the point on the 8-wind compass 
	* rose nearest to the azimuth. Examples are: N, NW, NNW, ...
	*
	*/
	tCompassPoint toCompassPoint(void) const { return toCompassPoint(m_radians); }

	/*! \brief Compass point abbreviation
	*
	* The function returns an abbreviation of the point on the 8-wind compass
	* rose nearest to the azimuth. Examples are: N, NW, NNW, ...
	*
	*  \param radians azimuth in radians
	*/
	static tCompassPoint toCompassPoint(double radians);

	/*! \brief A numeric value used as an invalid azimuth */
	static double invalidAzimuth() { return DBL_MAX; }

	/*!
	* \brief Normalize azimuth
	*
	* The input value specify a azimuth in radians. The function
	* normalizes the input value to the range of (0 and 2*pi> and returns
	* the normalized value. The function can return zero, the return
	* value is always less then 2*pi.
	*/
	static double normalizeAngle(double rad);

	/*!
	* \brief Azimuth from angle in degrees
	*
	* The method creates a new CAzimuth object from an angle specified
	* in degrees. Positive values are east of prime meridian and negative
	* ones are west.
	* \param degrees azimuth in degrees.
	*/
	static CAzimuth fromDegrees(double degrees) { return CAzimuth(degToRad(degrees)); }

	/*! \brief degrees-to-radians conversion */
	static double degToRad(double degrees);

	/*! \brief radians-to-degrees conversion */
	static double radToDeg(double radians);

	/*! \brief comparison operator */
	inline bool operator==(const CAzimuth& other) const { return m_radians == other.m_radians; }

	/*! \brief comparison operator */
	inline bool operator!=(const CAzimuth& other) const { return !this->operator==(other); }

private:
	// Azimuth in radians
	double m_radians;
};
