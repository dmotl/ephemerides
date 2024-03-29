/*!
*  \file      CBSC1991.h
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

#include <string>
#include <list>
#include <map>
#include <vector>

#include "CEquCoordinates.h"

class CBSC1991_Embedded
{
public:
	struct CObject
	{
	public:
		CObject(int hd_num, int bs_num, const CEquCoordinates& pos, double mag) : m_hdnum(hd_num), m_bsnum(bs_num), m_pos(pos), m_mag(mag) {}
		CEquCoordinates equatorialJ2000(void) { return m_pos; }
		int brightStarNumber(void) const { return m_bsnum; }
		double magnitude(void) const { return m_mag; }

	private:
		friend class CNGC2000;

		int m_hdnum, m_bsnum;
		CEquCoordinates m_pos;
		double m_mag;
	};

public:
	CBSC1991_Embedded();

	~CBSC1991_Embedded();

	const std::vector<CObject*>& data() const
	{
		return m_list;
	}

	CObject* find_bs(int bs_num) const;
	CObject* find_hd(int hd_num) const;

	static double invalidMagnitude() { return -99; }

private:
	std::vector<CObject*> m_list;
	std::map<int, CObject*> m_bs_id_map, m_hd_id_map;

	CBSC1991_Embedded(const CBSC1991_Embedded&) = delete;
	CBSC1991_Embedded& operator=(const CBSC1991_Embedded&) const = delete;
};
