/*!
*  \file      elp82.h
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
#ifndef _EPHEMERIS_ELP82_H_INCLUDED
#define _EPHEMERIS_ELP82_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct tELP82_Rect {
		double X[6];
	} tELP82_Rect;

	/*
	* \brief Ephemeride Lunaire Parisienne
	*
	* \details The function finds a position of a Earth's moon
	* at specified time.
	* Rectangular coordinates in AU.
	* Heliocentric position.
	* Dynamic equinox and ecliptic J2000
	*
	* \param T julian date (time scale: dynamical time TDB)
	* \param[out] xyz rectangular heliocentric coordinates
	*/

	int elp82b(int ibody, double tjd, tELP82_Rect* xyz);

#ifdef __cplusplus
}
#endif

#endif
