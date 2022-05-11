/*!
*  \file      CBound.h
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

#include "CSkyObject.h"

class CBound
{
public:
	enum class tPointType { ORIGIN, INTERPOLATED };

	class CPoint
	{
	public:
		CPoint(tPointType type, const CEquCoordinates& origin, std::string con, int csuffix): m_type(type), m_origin(origin), m_con(con), m_csuffix(csuffix) {}

		tPointType type(void) const { return m_type; }

		const CEquCoordinates& origin(void) { return m_origin; }

	private:
		tPointType m_type;
		CEquCoordinates m_origin;
		std::string m_con;
		int m_csuffix;
	};

	CBound() {}

	~CBound();

	void clear();

	bool load(const char* dirPath);

private:
	std::list<CPoint*> m_list;

	static double invalidRightAscension() { return 1e99; }
	static double invalidDeclination() { return -99; }

	CBound(const CBound&) = delete;
	CBound& operator=(const CBound&) const = delete;
};
