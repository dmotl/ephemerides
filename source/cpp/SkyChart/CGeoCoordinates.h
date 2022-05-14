/*!
*  \file      CGeoCoordinates.h
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

#include "CLatitude.h"
#include "CLongitude.h"

/*!
* \brief Geographic coordinates
* 
* The CGeoCoordinates class holds geographic coordinates of a point of the Earth - longitude and 
* latitude. The object is used to specify a geographic location of an observer.
* 
* \sa class CLongitude, class CLatitude
*/
class CGeoCoordinates
{
public:
	/*! 
	* \brief Constructor
	* 
	* The constructor creates an object that represents an invalid or 
	* unkown geographic coordinates.
	*/
	CGeoCoordinates() {}

	/*! 
	* \brief Constructor
	* 
	* The constructor creates an object from longitude and latitude
	* \param lon geographic longitude
	* \param lat geographic latitude
	*/
	CGeoCoordinates(const CLongitude& lon, const CLatitude& lat) : m_longitude(lon), m_latitude(lat) {}

	/*! \brief True if the coordinates are valid */
	bool isValid(void) const { return m_longitude.isValid() && m_latitude.isValid(); }

	/*! 
	* \brief Set longitude
	* \param lon geographic longitude
	*/
	void setLongitude(const CLongitude& lon) { m_longitude = lon; }

	/*! \brief longitude */
	const CLongitude& longitude(void) const { return m_longitude; }

	/*! \brief longitude */
	CLongitude& longitude(void) { return m_longitude; }

	/*! 
	* \brief Set latitude 
	* \param lat geographic latitude
	*/
	void setLatitude(const CLatitude& lat) { m_latitude = lat; }

	/*! \brief latitude */
	const CLatitude& latitude(void) const { return m_latitude; }

	/*! \brief latitude */
	CLatitude& latitude(void) { return m_latitude; }

	/*! \brief comparison operator */
	inline bool operator==(const CGeoCoordinates& other) const { return m_latitude == other.m_latitude && m_longitude == other.m_longitude; }

	/*! \brief comparison operator */
	inline bool operator!=(const CGeoCoordinates& other) const { return !this->operator==(other); }

private:
	CLongitude m_longitude;
	CLatitude m_latitude;
};
