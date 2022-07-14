/*!
*  \file      CAzAltCoordinates.h
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

#include "CAzimuth.h"
#include "CElevation.h"

/*!
* \brief Horizontal coordinates
*
* The CAzAltCoordinates class holds horizontal coordinates of a point on the celestial sphere - azimuth and
* elevation.
*
* \sa class CAzimuth, class CElevation
*/
class CAzAltCoordinates
{
public:
	/*!
	* \brief Constructor
	*
	* The constructor creates an object that represents an invalid or
	* unkown geographic coordinates.
	*/
	CAzAltCoordinates() {}

	/*!
	* \brief Constructor
	*
	* The constructor creates an object from azimuth and elevation
	* \param lon horizontal azimuth
	* \param lat horizontal elevation
	*/
	CAzAltCoordinates(const CAzimuth& az, const CElevation& alt) : m_azimuth(az), m_elevation(alt) {}

	/*! \brief True if the coordinates are valid */
	bool isValid(void) const { return m_azimuth.isValid() && m_elevation.isValid(); }

	/*!
	* \brief Set azimuth
	* \param az horizontal azimuth
	*/
	void setAzimuth(const CAzimuth& az) { m_azimuth = az; }

	/*! \brief Horizontal azimuth */
	const CAzimuth& azimuth(void) const { return m_azimuth; }

	/*! \brief Horizontal azimuth */
	CAzimuth& azimuth(void) { return m_azimuth; }

	/*!
	* \brief Set elevation
	* \param alt horizontal elevation
	*/
	void setElevation(const CElevation& alt) { m_elevation = alt; }

	/*! \brief Horizontal elevation */
	const CElevation& elevation(void) const { return m_elevation; }

	/*! \brief Horizontal elevation */
	CElevation& elevation(void) { return m_elevation; }

	/*! \brief comparison operator */
	inline bool operator==(const CAzAltCoordinates& other) const { return m_elevation == other.m_elevation && m_azimuth == other.m_azimuth; }

	/*! \brief comparison operator */
	inline bool operator!=(const CAzAltCoordinates& other) const { return !this->operator==(other); }

private:
	CAzimuth m_azimuth;
	CElevation m_elevation;
};
