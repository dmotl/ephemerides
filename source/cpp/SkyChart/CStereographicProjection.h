/*!
*  \file      CStereographicProjection.h
*  \author    David Motl
*  \date      2022-06-10
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

#include "CProjection.h"

class CStereographicProjection : public CProjection
{
public:
	CStereographicProjection() {}

	void project(QVector3D& v) const override
	{
		double r = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		double h = 0.5 * (r - v[2]);
		if (h > 1e-6) {
			double f = 1. / h;
			v[0] *= f;
			v[1] *= f;
			v[2] = r;
		}
		else {
			v[0] = v[1] = FLT_MAX;
			v[2] = -FLT_MIN;
		}
	}
};
