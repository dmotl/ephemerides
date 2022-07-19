/*!
*  \file      CPlanets.h
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

#include <SkyChartUtils.h>

/*!
* Model of positions of the planets, the Sun and the Moon
*
* The CPlanets class implements a mathematical model for computing
* position of the planets, the Sun and the Moon.
*
* Source:
* Pokorny Z.: Astronomicke algoritmy pro kalkulatory, Prague 1988
*
*/
class CPlanets
{
public:
	/*
	* \brief Constructor
	*
	* \param jd_utc time as Julian date in UTC
	*/
	explicit CPlanets(double jd_utc = 0);

	/*
	* Reinitialize the object for different time
	*
	* \param jd_utc time as Julian date in UTC
	*/
	void setJD(double jd_utc);

	/* Moon
	*
	* The function computes the ecliptical geocentric coordinates of the Moon
	*
	* The phase is expressed in radians:
	* - 0 for new moon
	* - pi/2 for first quarter
	* - pi for full moon
	* - 3pi/2 for last quarter
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad Earth-Moon distance in AU
	* \param phase phase in radians - see description
	*/
	CVector3d Moon() const;

	/* Sun
	*
	* The function computes the ecliptical geocentric coordinates of the Sun
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad Earth-Moon distance in AU
	*/
	CVector3d Sun() const;

	/* Mercury
	*
	* The function computes the ecliptical geocentric coordinates of Mercury
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	CVector3d Mercury() const { return _Planet(1); }

	/* Venus
	*
	* The function computes the ecliptical geocentric coordinates of Venus
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	CVector3d Venus() const { return _Planet(2); }

	/* Mars
	*
	* The function computes the ecliptical geocentric coordinates of Mars
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	CVector3d Mars() const { return _Planet(4); }

	/* Jupiter
	*
	* The function computes the ecliptical geocentric coordinates of Jupiter
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	CVector3d Jupiter() const { return _Planet(5); }

	/* Saturn
	*
	* The function computes the ecliptical geocentric coordinates of Saturn
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	CVector3d Saturn() const { return _Planet(6); }

	/* Uranus
	*
	* The function computes the ecliptical geocentric coordinates of Uranus
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	CVector3d Uranus() const { return _Planet(7); }

	/* Neptune
	*
	* The function computes the ecliptical geocentric coordinates of Neptune
	*
	* \param ra right ascention of ecliptical geocentric coordinates, in radians
	* \param dec declination of ecliptical geocentric coordinates, in radians
	* \param rad distance in AU
	* \param phase phase in radians
	*/
	CVector3d Neptune() const { return _Planet(8); }

private:
	// Julian date (UTC)
	double m_jd;

	// Rectangular ecliptical heliocentric coordinates (positions [AU])
	// 0 = Sun, 1 = Mercury, ...
	CVector3d m_eclipticPos[9];

	// Rectangular ecliptical heliocentric coordinates (velocities [AU/d])
	// 0 = Sun, 1 = Mercury, ...
	CVector3d m_eclipticVelocity[9];

	// Rectangular ecliptical geocentric coordinates (positions [AU])
	CVector3d m_moon;

	// Compute values for current JD
	void Init();

	// Ecliptical geocentric position [AU]
	CVector3d aberationPush(int ibody) const;

	// Ecliptical geocentric position [AU]
	CVector3d _Planet(int ibody) const;
};
