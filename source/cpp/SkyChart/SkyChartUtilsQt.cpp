/*!
*  \file      SkyChartUtilsQt.cpp
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
#include "SkyChartUtilsQt.h"

static QMatrix4x4 matVSOP87ToJ2000;
static bool initialized = false;

void vsop87ToFK5(const QVector4D& in, QVector4D& out)
{
	if (!initialized) {




		QMatrix4x4 mat;
		mat.rotate((float)( - 23.4392803055555555556 * M_PI / 180), 1, 0);
		mat.rotate((float)(0.0000275 * M_PI / 180), 0, 0, 1);
		matVSOP87ToJ2000 = mat.transposed();
		initialized = true;
	}
	out = matVSOP87ToJ2000 * in;
}
