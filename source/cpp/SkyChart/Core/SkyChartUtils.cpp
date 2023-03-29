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

#include <math.h>
#include <float.h>

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

CMatrix3<double> Utils::vsop87ToFK5(void)
{
	static const double cos_eps = cos(EPS_0 * M_PI / 180);
	static const double sin_eps = -sin(EPS_0 * M_PI / 180);
	static const double cos_phi = cos(0.0000275 * M_PI / 180);
	static const double sin_phi = sin(0.0000275 * M_PI / 180);

	CMatrix3<double> t;
	t(0, 0) = cos_phi;
	t(1, 0) = cos_eps * sin_phi;
	t(2, 0) = sin_eps * sin_phi;

	t(0, 1) = -sin_phi;
	t(1, 1) = cos_eps * cos_phi;
	t(2, 1) = sin_eps * cos_phi;

	t(0, 2) = 0;
	t(1, 2) = -sin_eps;
	t(2, 2) = cos_eps;

	return t;
}

void Utils::rectangularToSperical(const CVector3d& xyz, double* lng, double* lat)
{
	if (lat)
		*lat = M_PI_2 - atan2(sqrt(xyz.x() * xyz.x() + xyz.y() * xyz.y()), xyz.z());
	if (lng)
		*lng = atan2(xyz.y(), xyz.x());
}

CVector3d Utils::sphericalToRectangular(double lng, double lat)
{
	return CVector3d(cos(lng) * cos(lat), sin(lng) * cos(lat), sin(lat));
}

CVector3d Utils::aberrationPush(double planet_Earth_distance, const CVector3d& earth_velocity)
{
	return earth_velocity * (planet_Earth_distance * AU / (SPEED_OF_LIGHT * 86400.0));
}

//
// Angular distance of two objects
//
double Utils::AngularDistance(double ra1, double de1, double ra2, double de2)
{
	return acos(sin(de1) * sin(de2) + cos(de1) * cos(de2) * cos(ra1 - ra2));
}


/* Hegret precession */
CVector3d Utils::HegretPrecession(double epoch_from, double epoch_to, const CVector3d& pos)
{
	static const double CDR = 0.017453292519943;

	// SET UP ROTATION MATRIX(R)
	double CSR = CDR / 3600.0;
	double T = 0.001 * (epoch_to - epoch_from);
	double ST = 0.001 * (epoch_from - 1900.0);
	double A = CSR * T * (23042.53 + ST * (139.75 + 0.06 * ST) + T * (30.23 - 0.27 * ST + 18.0 * T));
	double B = CSR * T * T * (79.27 + 0.66 * ST + 0.32 * T) + A;
	double C = CSR * T * (20046.85 - ST * (85.33 + 0.37 * ST) + T * (-42.67 - 0.37 * ST - 41.8 * T));
	double SINA = sin(A), SINB = sin(B), SINC = sin(C), COSA = cos(A), COSB = cos(B), COSC = cos(C);

	return CVector3d(
		(COSA * COSB * COSC - SINA * SINB) * pos.x() - (COSA * SINB + SINA * COSB * COSC) * pos.y() - COSB * SINC * pos.z(),
		(SINA * COSB + COSA * SINB * COSC) * pos.x() + (COSA * COSB - SINA * SINB * COSC) * pos.y() - SINB * SINC * pos.z(),
		COSA * SINC * pos.x() - SINA * SINC * pos.y() + COSC * pos.z()
	);
}

CMatrix3d Utils::HegretPrecession(double epoch_from, double epoch_to)
{
	static const double CDR = 0.017453292519943;

	// SET UP ROTATION MATRIX(R)
	double CSR = CDR / 3600.0;
	double T = 0.001 * (epoch_to - epoch_from);
	double ST = 0.001 * (epoch_from - 1900.0);
	double A = CSR * T * (23042.53 + ST * (139.75 + 0.06 * ST) + T * (30.23 - 0.27 * ST + 18.0 * T));
	double B = CSR * T * T * (79.27 + 0.66 * ST + 0.32 * T) + A;
	double C = CSR * T * (20046.85 - ST * (85.33 + 0.37 * ST) + T * (-42.67 - 0.37 * ST - 41.8 * T));
	double SINA = sin(A), SINB = sin(B), SINC = sin(C), COSA = cos(A), COSB = cos(B), COSC = cos(C);

	CMatrix3d t;
	t(0, 0) = COSA * COSB * COSC - SINA * SINB;
	t(1, 0) = -COSA * SINB - SINA * COSB * COSC;
	t(2, 0) = -COSB * SINC;

	t(0, 1) = (SINA * COSB + COSA * SINB * COSC);
	t(1, 1) = (COSA * COSB - SINA * SINB * COSC);
	t(2, 1) = -SINB * SINC;

	t(0, 2) = COSA * SINC;
	t(1, 2) = -SINA * SINC;
	t(2, 2) = COSC;

	return t;
}

void Utils::cubic(CVector3d point[], const CVector3d& p_start, const CVector3d& p_end)
{
	CVector3d start = p_start, end = p_end;

	double z = DBL_MAX;
	if (start[2] == end[2]) {
		// Horizontal line
		z = start[2];
		start[2] = end[2] = 0;
	}

	double AplusBlength = CVector3d(start + end).length();
	double AminusBlength = CVector3d(start - end).length();
	double radius = start.length();
	assert(radius > 0 && AplusBlength > 0 && AminusBlength > 0);

	double beta = 0.5 * AminusBlength, alphaSq = radius * radius - beta * beta;
	assert(beta > 0 && alphaSq >= 0);

	double alpha = sqrt(alphaSq);

	CVector3d P1 = (4 * radius - alpha) / (3.0 * AplusBlength) * (start + end) + (radius - alpha) * (3.0 * radius - alpha) / (3.0 * beta * AminusBlength) * (start - end);
	CVector3d P2 = (4 * radius - alpha) / (3.0 * AplusBlength) * (start + end) - (radius - alpha) * (3.0 * radius - alpha) / (3.0 * beta * AminusBlength) * (start - end);

	if (z != DBL_MAX)
		start[2] = end[2] = P1[2] = P2[2] = z;

	point[0] = start;
	point[1] = P1;
	point[2] = P2;
	point[3] = end;
}
