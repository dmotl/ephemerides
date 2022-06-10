/*!
*  \file      Utils.cpp
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
#include "Utils.h"

#define _USE_MATH_DEFINES

#include <math.h>

//
// Angular distance of two objects
//
double Utils::AngularDistance(double ra1, double de1, double ra2, double de2)
{
	return acos(sin(de1) * sin(de2) + cos(de1) * cos(de2) * cos(ra1 - ra2));
}


/* Hegret precession */
void Utils::HegretPrecession(double epoch_from, double epoch_to, CVector3d& pos)
{
	double CDR = 0.17453292519943E-1;
	double ep1 = 0, ep2 = 0;

	double x11 = pos[0], x12 = pos[1], x13 = pos[2];

	// SET UP ROTATION MATRIX(R)
	double CSR = CDR / 3600.0;
	double T = 0.001 * (epoch_to - epoch_from);
	double ST = 0.001 * (epoch_from - 1900.0);
	double A = CSR * T * (23042.53 + ST * (139.75 + 0.06 * ST) + T * (30.23 - 0.27 * ST + 18.0 * T));
	double B = CSR * T * T * (79.27 + 0.66 * ST + 0.32 * T) + A;
	double C = CSR * T * (20046.85 - ST * (85.33 + 0.37 * ST) + T * (-42.67 - 0.37 * ST - 41.8 * T));
	double SINA = sin(A), SINB = sin(B), SINC = sin(C), COSA = cos(A), COSB = cos(B), COSC = cos(C);
	double r11 = COSA * COSB * COSC - SINA * SINB;
	double r12 = -COSA * SINB - SINA * COSB * COSC;
	double r13 = -COSB * SINC;
	double r21 = SINA * COSB + COSA * SINB * COSC;
	double r22 = COSA * COSB - SINA * SINB * COSC;
	double r23 = -SINB * SINC;
	double r31 = COSA * SINC;
	double r32 = -SINA * SINC;
	double r33 = COSC;
	// PERFORM THE ROTATION TO GET THE DIRECTION COSINES AT EPOCH2
	double x21 = 0, x22 = 0, x23 = 0;
	x21 += r11 * x11;
	x22 += r21 * x11;
	x23 += r31 * x11;

	x21 += r11 * x12;
	x22 += r21 * x12;
	x23 += r31 * x12;

	x21 += r11 * x13;
	x22 += r21 * x13;
	x23 += r31 * x13;

	pos[0] = x21;
	pos[1] = x22;
	pos[2] = x23;
}
