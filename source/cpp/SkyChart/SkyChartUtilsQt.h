/*!
*  \file      SkyChartUtilsQt.h
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

#include <QtGui>

#include "SkyChartUtils.h"

namespace Utils
{
	inline QVector4D vec3dToVec4d(const CVector3d& in)
	{
		return QVector4D(in.x(), in.y(), in.z(), 1.0);
	}

	inline CVector3d vec4dToVec3d(const QVector4D& in)
	{
		return CVector3d(in.x(), in.y(), in.z());
	}
}