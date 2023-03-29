/*!
*  \file      vsop87.c
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
#include "vsop87.h"

#include <math.h>

#include "vsop87a.mer.h"
#include "vsop87a.ven.h"
#include "vsop87a.ear.h"
#include "vsop87a.mar.h"
#include "vsop87a.jup.h"
#include "vsop87a.sat.h"
#include "vsop87a.ura.h"
#include "vsop87a.nep.h"

#include "vsop87c.mer.h"
#include "vsop87c.ven.h"
#include "vsop87c.ear.h"
#include "vsop87c.mar.h"
#include "vsop87c.jup.h"
#include "vsop87c.sat.h"
#include "vsop87c.ura.h"
#include "vsop87c.nep.h"

static const double t2000 = 2451545.0;
static const double a1000 = 365250;

//
// \param tab table of terms (A, B and C)
// \param nterm number of terms
// \param T1 T ** 1
// \param Talpha T ** alpha
// \param Talpha_m1_alpha (T ** (alpha-1)) * alpha
// \param[in, out] positional component
// \param[in, out] velocity component
//
static void _xyz(const tVSOP87Table* tab, int nterm, double T1, double Talpha, double* pos, double Talpha_m1_alpha, double *vel)
{
	const tVSOP87Table* t = tab;
	double sacu = 0, sacsu = 0;
	for (int i = 0; i < nterm; i++, t++) {
		sacu += t->A * cos(t->B + t->C * T1);
		sacsu += t->A * t->C * sin(t->B + t->C * T1);
	}
	*pos += sacu * Talpha;
	*vel += (Talpha_m1_alpha * sacu - Talpha * sacsu) / a1000;
}

#define TAB(iv, ib, ic, it) vsop87_ ## iv ## ib ## ic ## it

#define XYZN(iv, ib, ic, it) _xyz(TAB(iv, ib, ic, it), sizeof(TAB(iv, ib, ic, it)) / sizeof(tVSOP87Table), T[1], T[it], xyz->X + (ic - 1), dT[it], xyz->X + ((ic) + 3 - 1));
#define XYZ0(iv, ib, ic) XYZN(iv, ib, ic, 0)

int vsop87a(int ibody, double tjd, tVSOP87_Rect* xyz)
{
	double T[6], dT[6];
	T[0] = 1;
	T[1] = (tjd - t2000) / a1000;
	for (int i = 2; i < 6; i++)
		T[i] = pow(T[1], i);

	dT[0] = 0;
	dT[1] = 1;
	for (int i = 2; i < 6; i++)
		dT[i] = T[i - 1] * i;

	xyz->X[0] = xyz->X[1] = xyz->X[2] = xyz->X[3] = xyz->X[4] = xyz->X[5] = 0;

	switch (ibody)
	{
	case 1:
		/* Mercury */
		XYZ0(1, 1, 1);	XYZN(1, 1, 1, 1);	XYZN(1, 1, 1, 2);	XYZN(1, 1, 1, 3);	XYZN(1, 1, 1, 4);	XYZN(1, 1, 1, 5);
		XYZ0(1, 1, 2);	XYZN(1, 1, 2, 1);	XYZN(1, 1, 2, 2);	XYZN(1, 1, 2, 3);	XYZN(1, 1, 2, 4);	XYZN(1, 1, 2, 5);
		XYZ0(1, 1, 3);	XYZN(1, 1, 3, 1);	XYZN(1, 1, 3, 2);	XYZN(1, 1, 3, 3);	XYZN(1, 1, 3, 4);	XYZN(1, 1, 3, 5);
		return 0;

	case 2:
		/* Venus */
		XYZ0(1, 2, 1);	XYZN(1, 2, 1, 1);	XYZN(1, 2, 1, 2);	XYZN(1, 2, 1, 3);	XYZN(1, 2, 1, 4);	XYZN(1, 2, 1, 5);
		XYZ0(1, 2, 2);	XYZN(1, 2, 2, 1);	XYZN(1, 2, 2, 2);	XYZN(1, 2, 2, 3);	XYZN(1, 2, 2, 4);	XYZN(1, 2, 2, 5);
		XYZ0(1, 2, 3);	XYZN(1, 2, 3, 1);	XYZN(1, 2, 3, 2);	XYZN(1, 2, 3, 3);	XYZN(1, 2, 3, 4);	XYZN(1, 2, 3, 5);
		return 0;

	case 3:
		/* Earth */
		XYZ0(1, 3, 1);	XYZN(1, 3, 1, 1);	XYZN(1, 3, 1, 2);	XYZN(1, 3, 1, 3);	XYZN(1, 3, 1, 4);	XYZN(1, 3, 1, 5);
		XYZ0(1, 3, 2);	XYZN(1, 3, 2, 1);	XYZN(1, 3, 2, 2);	XYZN(1, 3, 2, 3);	XYZN(1, 3, 2, 4);	XYZN(1, 3, 2, 5);
		XYZ0(1, 3, 3);	XYZN(1, 3, 3, 1);	XYZN(1, 3, 3, 2);	XYZN(1, 3, 3, 3);	XYZN(1, 3, 3, 4);	XYZN(1, 3, 3, 5);
		return 0;

	case 4:
		/* Mars */
		XYZ0(1, 4, 1);	XYZN(1, 4, 1, 1);	XYZN(1, 4, 1, 2);	XYZN(1, 4, 1, 3);	XYZN(1, 4, 1, 4);	XYZN(1, 4, 1, 5);
		XYZ0(1, 4, 2);	XYZN(1, 4, 2, 1);	XYZN(1, 4, 2, 2);	XYZN(1, 4, 2, 3);	XYZN(1, 4, 2, 4);	XYZN(1, 4, 2, 5);
		XYZ0(1, 4, 3);	XYZN(1, 4, 3, 1);	XYZN(1, 4, 3, 2);	XYZN(1, 4, 3, 3);	XYZN(1, 4, 3, 4);	XYZN(1, 4, 3, 5);
		return 0;

	case 5:
		/* Jupiter */
		XYZ0(1, 5, 1);	XYZN(1, 5, 1, 1);	XYZN(1, 5, 1, 2);	XYZN(1, 5, 1, 3);	XYZN(1, 5, 1, 4);	XYZN(1, 5, 1, 5);
		XYZ0(1, 5, 2);	XYZN(1, 5, 2, 1);	XYZN(1, 5, 2, 2);	XYZN(1, 5, 2, 3);	XYZN(1, 5, 2, 4);	XYZN(1, 5, 2, 5);
		XYZ0(1, 5, 3);	XYZN(1, 5, 3, 1);	XYZN(1, 5, 3, 2);	XYZN(1, 5, 3, 3);	XYZN(1, 5, 3, 4);	XYZN(1, 5, 3, 5);
		return 0;

	case 6:
		/* Saturn */
		XYZ0(1, 6, 1);	XYZN(1, 6, 1, 1);	XYZN(1, 6, 1, 2);	XYZN(1, 6, 1, 3);	XYZN(1, 6, 1, 4);	XYZN(1, 6, 1, 5);
		XYZ0(1, 6, 2);	XYZN(1, 6, 2, 1);	XYZN(1, 6, 2, 2);	XYZN(1, 6, 2, 3);	XYZN(1, 6, 2, 4);	XYZN(1, 6, 2, 5);
		XYZ0(1, 6, 3);	XYZN(1, 6, 3, 1);	XYZN(1, 6, 3, 2);	XYZN(1, 6, 3, 3);	XYZN(1, 6, 3, 4);	XYZN(1, 6, 3, 5);
		return 0;

	case 7:
		/* Neptune */
		XYZ0(1, 7, 1);	XYZN(1, 7, 1, 1);	XYZN(1, 7, 1, 2);	XYZN(1, 7, 1, 3);	XYZN(1, 7, 1, 4);	
		XYZ0(1, 7, 2);	XYZN(1, 7, 2, 1);	XYZN(1, 7, 2, 2);	XYZN(1, 7, 2, 3);	XYZN(1, 7, 2, 4);	
		XYZ0(1, 7, 3);	XYZN(1, 7, 3, 1);	XYZN(1, 7, 3, 2);	XYZN(1, 7, 3, 3);	
		return 0;

	case 8:
		/* Uranus */
		XYZ0(1, 8, 1);	XYZN(1, 8, 1, 1);	XYZN(1, 8, 1, 2);	XYZN(1, 8, 1, 3);	XYZN(1, 8, 1, 4);	
		XYZ0(1, 8, 2);	XYZN(1, 8, 2, 1);	XYZN(1, 8, 2, 2);	XYZN(1, 8, 2, 3);	XYZN(1, 8, 2, 4);	
		XYZ0(1, 8, 3);	XYZN(1, 8, 3, 1);	XYZN(1, 8, 3, 2);	XYZN(1, 8, 3, 3);	
		return 0;
	}

	return 1;
}

int vsop87c(int ibody, double tjd, tVSOP87_Rect *xyz)
{
	double T[6], dT[6];
	T[0] = 1;
	T[1] = (tjd - t2000) / a1000;
	for (int i = 2; i < 6; i++)
		T[i] = T[i - 1] * T[1];

	dT[0] = 0;
	dT[1] = 1;
	for (int i = 2; i < 6; i++)
		dT[i] = T[i - 1] * i;

	xyz->X[0] = xyz->X[1] = xyz->X[2] = xyz->X[3] = xyz->X[4] = xyz->X[5] = 0;

	switch (ibody)
	{
	case 1:
		/* Mercury */
		XYZ0(3, 1, 1);	XYZN(3, 1, 1, 1);	XYZN(3, 1, 1, 2);	XYZN(3, 1, 1, 3);	XYZN(3, 1, 1, 4);	XYZN(3, 1, 1, 5);
		XYZ0(3, 1, 2);	XYZN(3, 1, 2, 1);	XYZN(3, 1, 2, 2);	XYZN(3, 1, 2, 3);	XYZN(3, 1, 2, 4);	XYZN(3, 1, 2, 5);
		XYZ0(3, 1, 3);	XYZN(3, 1, 3, 1);	XYZN(3, 1, 3, 2);	XYZN(3, 1, 3, 3);	XYZN(3, 1, 3, 4);	XYZN(3, 1, 3, 5);
		return 0;

	case 2:
		/* Venus */
		XYZ0(3, 2, 1);	XYZN(3, 2, 1, 1);	XYZN(3, 2, 1, 2);	XYZN(3, 2, 1, 3);	XYZN(3, 2, 1, 4);	XYZN(3, 2, 1, 5);
		XYZ0(3, 2, 2);	XYZN(3, 2, 2, 1);	XYZN(3, 2, 2, 2);	XYZN(3, 2, 2, 3);	XYZN(3, 2, 2, 4);	XYZN(3, 2, 2, 5);
		XYZ0(3, 2, 3);	XYZN(3, 2, 3, 1);	XYZN(3, 2, 3, 2);	XYZN(3, 2, 3, 3);	XYZN(3, 2, 3, 4);	XYZN(3, 2, 3, 5);
		return 0;

	case 3:
		/* Earth */
		XYZ0(3, 3, 1);	XYZN(3, 3, 1, 1);	XYZN(3, 3, 1, 2);	XYZN(3, 3, 1, 3);	XYZN(3, 3, 1, 4);	XYZN(3, 3, 1, 5);
		XYZ0(3, 3, 2);	XYZN(3, 3, 2, 1);	XYZN(3, 3, 2, 2);	XYZN(3, 3, 2, 3);	XYZN(3, 3, 2, 4);	XYZN(3, 3, 2, 5);
		XYZ0(3, 3, 3);	XYZN(3, 3, 3, 1);	XYZN(3, 3, 3, 2);	XYZN(3, 3, 3, 3);	XYZN(3, 3, 3, 4);	
		return 0;

	case 4:
		/* Mars */
		XYZ0(3, 4, 1);	XYZN(3, 4, 1, 1);	XYZN(3, 4, 1, 2);	XYZN(3, 4, 1, 3);	XYZN(3, 4, 1, 4);	XYZN(3, 4, 1, 5);
		XYZ0(3, 4, 2);	XYZN(3, 4, 2, 1);	XYZN(3, 4, 2, 2);	XYZN(3, 4, 2, 3);	XYZN(3, 4, 2, 4);	XYZN(3, 4, 2, 5);
		XYZ0(3, 4, 3);	XYZN(3, 4, 3, 1);	XYZN(3, 4, 3, 2);	XYZN(3, 4, 3, 3);	XYZN(3, 4, 3, 4);	XYZN(3, 4, 3, 5);
		return 0;

	case 5:
		/* Jupiter */
		XYZ0(3, 5, 1);	XYZN(3, 5, 1, 1);	XYZN(3, 5, 1, 2);	XYZN(3, 5, 1, 3);	XYZN(3, 5, 1, 4);	XYZN(3, 5, 1, 5);
		XYZ0(3, 5, 2);	XYZN(3, 5, 2, 1);	XYZN(3, 5, 2, 2);	XYZN(3, 5, 2, 3);	XYZN(3, 5, 2, 4);	XYZN(3, 5, 2, 5);
		XYZ0(3, 5, 3);	XYZN(3, 5, 3, 1);	XYZN(3, 5, 3, 2);	XYZN(3, 5, 3, 3);	XYZN(3, 5, 3, 4);	XYZN(3, 5, 3, 5);
		return 0;

	case 6:
		/* Saturn */
		XYZ0(3, 6, 1);	XYZN(3, 6, 1, 1);	XYZN(3, 6, 1, 2);	XYZN(3, 6, 1, 3);	XYZN(3, 6, 1, 4);	XYZN(3, 6, 1, 5);
		XYZ0(3, 6, 2);	XYZN(3, 6, 2, 1);	XYZN(3, 6, 2, 2);	XYZN(3, 6, 2, 3);	XYZN(3, 6, 2, 4);	XYZN(3, 6, 2, 5);
		XYZ0(3, 6, 3);	XYZN(3, 6, 3, 1);	XYZN(3, 6, 3, 2);	XYZN(3, 6, 3, 3);	XYZN(3, 6, 3, 4);	XYZN(3, 6, 3, 5);
		return 0;

	case 7:
		/* Neptune */
		XYZ0(3, 7, 1);	XYZN(3, 7, 1, 1);	XYZN(3, 7, 1, 2);	XYZN(3, 7, 1, 3);	XYZN(3, 7, 1, 4);	XYZN(3, 7, 1, 5);
		XYZ0(3, 7, 2);	XYZN(3, 7, 2, 1);	XYZN(3, 7, 2, 2);	XYZN(3, 7, 2, 3);	XYZN(3, 7, 2, 4);	XYZN(3, 7, 2, 4);
		XYZ0(3, 7, 3);	XYZN(3, 7, 3, 1);	XYZN(3, 7, 3, 2);	XYZN(3, 7, 3, 3);	XYZN(3, 7, 3, 3);	XYZN(3, 7, 3, 3);
		return 0;

	case 8:
		/* Uranus */
		XYZ0(3, 8, 1);	XYZN(3, 8, 1, 1);	XYZN(3, 8, 1, 2);	XYZN(3, 8, 1, 3);	XYZN(3, 8, 1, 4);	XYZN(3, 8, 1, 4);
		XYZ0(3, 8, 2);	XYZN(3, 8, 2, 1);	XYZN(3, 8, 2, 2);	XYZN(3, 8, 2, 3);	XYZN(3, 8, 2, 4);	XYZN(3, 8, 2, 4);
		XYZ0(3, 8, 3);	XYZN(3, 8, 3, 1);	XYZN(3, 8, 3, 2);	XYZN(3, 8, 3, 3);	XYZN(3, 8, 3, 3);	XYZN(3, 8, 3, 3);
		return 0;
	}

	return 1;
}
