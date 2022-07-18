/*!
*  \file      SkyChartUtils.h
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
#pragma once

#include "Utils.h"
#include "CVector3d.h"
#include "CMatrix3d.h"

namespace Utils
{
	/* Converts VSOP87 ecliptical rectangular coordinates to the
	 * equatorial frame FK5 J2000. This should be used
	 * for VSOP87A and VSOP87E.
	 *
	 * \param in VSOP87 coordinates
	 * \param out FK5 J2000 coordinates
	 */
	CVector3d vsop87ToFK5(const CVector3d& in);

	CMatrix3<double> vsop87ToFK5();

	/*
	* \brief Angular distance of two objects
	*
	* The function computes angular distance an a unit sphere of two objects specified
	* by polar coordinates in radians.
	*
	* \param Ra1 first coordinate of the first object, in radians
	* \param Dec1 second coordinate of the first object, in radians
	* \param Ra2 first coordinate of the second object, in radians
	* \param Dec2 second coordinate of the second object, in radians
	* \return angular distance in radians
	*/
	double AngularDistance(double Ra1, double De1, double Ra2, double De2);

	//
	// Hegret precession 
	//
	CVector3d HegretPrecession(double epoch_from, double epoch_to, const CVector3d& pos);

	//
	// Hegret precession 
	//
	CMatrix3d HegretPrecession(double epoch_from, double epoch_to);

	/* Convert equatorial rectangular coordinates to spherical ones.
	* 
	* \param xyz FK5 J2000 equatorial coordinates
	* \return equatorial spherical coordinates
	 */
	void rectangularToSperical(const CVector3d& xyz, double *lng, double *lat);

	/* Convert equatorial rectangular coordinates to spherical ones.
	*
	* \param FK5 J2000 equatorial coordinates (in radians)
	* \param[out] xyz coordinates (normalized)
	 */
	CVector3d sphericalToRectangular(double lng, double lat);

	/* Compute aberration shift to position of a planet
	 *
	 * \param planet_distance distance between the observer and the planet [AU]
	 * \param earth_velocity ecliptic velocity of the observer [AU/d]
	 * \return aberration shift [AU]
	 */
	CVector3d aberrationPush(double planet_distance, const CVector3d& earth_velocity);


	void cubic(CVector3d out[], const CVector3d& start, const CVector3d& end);
}
