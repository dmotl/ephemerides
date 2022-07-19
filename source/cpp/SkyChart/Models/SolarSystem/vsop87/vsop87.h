/*!
*  \file      vsop87.h
*  \author    David Motl
*  \date      2022-05-11
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
#ifndef _EPHEMERIS_VSOP87_H_INCLUDED
#define _EPHEMERIS_VSOP87_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct tVSOP87_Rect {
		double X[6];
	} tVSOP87_Rect;

	/*
	* \brief Find position of a body
	* 
	* \details The function finds a position of a specified body
	* at specified time. 
	* Rectangular coordinates in AU. 
	* Heliocentric position.
	* Dynamic equinox and ecliptic J2000
	* 
	* Body index:
	* - 0: Sun 
	* - 1: Mercury
	* - 2: Vebus
	* - 3: Earth
	* - 4: Mars
	* - 5: Jupiter
	* - 6: Saturn
	* - 7: Uranus
	* - 8: Neptune
	* - 9: Earth-Moon barycenter
	* 
	* \param body 
	* \param T julian date (time scale: dynamical time TDB)
	* \param[out] xyz rectangular heliocentric coordinates
	*/

	int vsop87a(int ibody, double tjd, tVSOP87_Rect* xyz);

	/*
	* \brief Find position of a body
	*
	* \details The function finds a position of a specified body
	* at specified time.
	* Rectangular coordinates in AU.
	* Barycenter positions
	* Dynamic equinox and ecliptic J2000
	*
	* Body index:
	* - 0: Sun
	* - 1: Mercury
	* - 2: Vebus
	* - 3: Earth
	* - 4: Mars
	* - 5: Jupiter
	* - 6: Saturn
	* - 7: Uranus
	* - 8: Neptune
	* - 9: Earth-Moon barycenter
	*
	* \param body
	* \param T julian date expressed in dynamical time (TAI+32.184s)
	* \param[out] xyz rectangular heliocentric coordinates
	*/

	int vsop87c(int ibody, double tjd, tVSOP87_Rect* xyz);

#ifdef __cplusplus
}
#endif

#endif