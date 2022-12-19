/*!
*  \file      CLines.cpp
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
#include "CLines.h"

#include "constlines_tables.h"

CLines::CLines(const CBSC1991_Embedded& bsc)
{
	int length = sizeof(constlines) / sizeof(tConstLinesTable);
	for (int i = 0; i < length; i++) {
		const tConstLinesTable* src = constlines + i;

		auto obj_start = bsc.find_hd(src->hd_start), obj_end = bsc.find_hd(src->hd_end);
		if (obj_start && obj_end)
			m_list.push_back(CLine(obj_start->equatorialJ2000(), obj_end->equatorialJ2000(), (tConstellation)src->cons));
	}
}
