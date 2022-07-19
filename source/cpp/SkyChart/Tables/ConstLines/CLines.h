/*!
*  \file      CLines.h
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

#include <list>

#include "CEquCoordinates.h"
#include "constellation_names.h"
#include "CBSC1991.h"

#include <vector>

class CLines
{
public:
	class CLine
	{
	public:
		CLine(const CEquCoordinates& start, const CEquCoordinates& end, tConstellation cons) : m_start(start), m_end(end), m_cons(cons) {}

		const CEquCoordinates& startJ2000(void) const { return m_start; }
		const CEquCoordinates& end2000(void) const { return m_end; }
		tConstellation constellation(void) const { return m_cons; }

	private:
		CEquCoordinates m_start, m_end;
		tConstellation m_cons;
	};

	explicit CLines(const CBSC1991& bsc);

	const std::vector<CLine>& data() const { return m_list; }

private:
	std::vector<CLine> m_list;

	static double invalidRightAscension() { return 1e99; }
	static double invalidDeclination() { return -99; }

	CLines(const CLines&) = delete;
	CLines& operator=(const CLines&) const = delete;
};
