/*!
*  \file      CEquCoordinates.h
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

#include "SkyChartUtils.h"
#include "CDeclination.h"
#include "CRightAscension.h"

/*!
* \brief Equatorial coordinates
*
* The CEquCoordinates class holds an equatorial coordinates of a point on the celestial sphere - 
* right ascension and declination. The object is used to specify a position of a celestial object,
* such as a star or a planet.
*
* \sa class CRightAscension, class CDeclination
*/
class CEquCoordinates
{
public:
	/*!
	* \brief Constructor
	*
	* The constructor creates an object that represents an invalid or
	* unkown celestial coordinates
	*/
	CEquCoordinates() {}

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from right ascension and declination
	* \param ra right ascension
	* \param d declination
	*/
	CEquCoordinates(const CRightAscension& ra, const CDeclination& d) : m_rightAscension(ra), m_declination(d) {}

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from a equatorial rectangular coordinates
	*/
	CEquCoordinates(const CVector3d& rect);

	/*! \brief True if the coordinates are valid */
	bool isValid(void) const { return m_rightAscension.isValid() && m_declination.isValid(); }

	/*!
	* \brief Set right ascension
	* \param ra right ascension
	*/
	void setRightAscension(const CRightAscension& ra) { m_rightAscension = ra; }

	/*! \brief right ascension */
	const CRightAscension& rightAscension(void) const { return m_rightAscension; }

	/*! \brief right ascension */
	CRightAscension& rightAscension(void) { return m_rightAscension; }

	/*!
	* \brief Set declination
	* \param d declination
	*/
	void setDeclination(const CDeclination& d) { m_declination = d; }

	/*! \brief declination */
	const CDeclination& declination(void) const { return m_declination; }

	/*! \brief declination */
	CDeclination& declination(void) { return m_declination; }

	/*! \brief comparison operator */
	inline bool operator==(const CEquCoordinates& other) const { return m_declination == other.m_declination && m_rightAscension == other.m_rightAscension; }

	/*! \brief comparison operator */
	inline bool operator!=(const CEquCoordinates& other) const { return !this->operator==(other); }

	/*! \brief convert to rectangular coordinates */
	CVector3d toXYZ(void) const { return Utils::sphericalToRectangular(m_rightAscension.radians(), m_declination.radians()); }

	/*! 
	* \brief Angular distance 
	* 
	* The function returns an angular distance in radians to another point
	* on the celestial sphere. The angular distance is defined as length of shortest arc on 
	* the celestial sphere that connects this point and given point.
	* 
	* \param other other point
	* \return angular distance in radians (0..pi)
	*/
	double distanceTo(const CEquCoordinates& other) const { return distanceBetween(*this, other); }

	/*! 
	* \brief Angular distance
	*
	* The function returns an angular distance in radians between two given points 
	* on the celestial sphere. The angular distance is defined as length of shortest arc on 
	* the celestial sphere that connects the two given points.
	* 
	* \param first first point
	* \param second second point
	* \return angular distance in radians (0..pi)
	*/
	static double distanceBetween(const CEquCoordinates& first, const CEquCoordinates& second)
	{
		return Utils::AngularDistance(first.m_rightAscension.radians(), first.m_declination.radians(),
			second.m_rightAscension.radians(), second.declination().radians());
	}

private:
	CRightAscension m_rightAscension;
	CDeclination m_declination;
};
