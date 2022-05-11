/*!
*  \file      SkyChartUtils.cpp
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
#include "SkyChartUtils.h"

using namespace Utils;

// Ecliptic obliquity of J2000.0, degrees
#define EPS_0 23.4392803055555555555556

// speed of light (m/sec)
#define SPEED_OF_LIGHT 299792458.0

// astronomical unit (m)
#define AU 149597870691.0


#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef M_PI_2
#define M_PI_2 (1.57079632679489661923)
#endif

CVector3d Utils::vsop87ToFK5(const CVector3d& in)
{
	static const double cos_eps = cos(EPS_0 * M_PI / 180);
	static const double sin_eps = -sin(EPS_0 * M_PI / 180);
	static const double cos_phi = cos(0.0000275 * M_PI / 180);
	static const double sin_phi = sin(0.0000275 * M_PI / 180);

	return CVector3d(
		cos_phi * in.x() + cos_eps * sin_phi * in.y() + sin_eps * sin_phi * in.z(),
		-sin_phi * in.x() + cos_eps * cos_phi * in.y() + sin_eps * cos_phi * in.z(),
		-sin_eps * in.y() + cos_eps * in.z()
		);
}

CEquCoordinates Utils::rectangularToSperical(const CVector3d& xyz)
{
	double rho = M_PI_2 - atan2(sqrt(xyz.x() * xyz.x() + xyz.y() * xyz.y()), xyz.z());
	double phi = atan2(xyz.y(), xyz.x());
	return CEquCoordinates(CRightAscension(phi), CDeclination(rho));
}

CVector3d Utils::aberrationPush(double planet_Earth_distance, CVector3d& earth_velocity)
{
	return earth_velocity * (planet_Earth_distance * AU / (SPEED_OF_LIGHT * 86400.0));
}
