/*!
*  \file      CBound.cpp
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
#include "CBound.h"

#include "constbnd_tables.h"

CBound::CBound()
{
	int length = sizeof(constbnd) / sizeof(tConstBoundariesTable);
	for (int i = 0; i < length; i++) {
		const tConstBoundariesTable* src = constbnd + i;

		CEquCoordinates equ(CRightAscension::fromHours((double)src->ra / 3600.0), CDeclination::fromDegrees((double)src->dec / 3600.0));
		m_list.push_back(CPoint(tPointType::ORIGIN, equ, (tConstellation)src->cons));
	}
}
