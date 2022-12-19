/*!
*  \file      CEphemerisBase.h
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
#pragma once

#include "CGeoCoordinates.h"
#include "CJulianDate.h"

class CCatalogObject;
class CCatalog;

#include <vector>

/*
* \brief Ephemeris (base class)
*
* The CEphemerisBase provides a common interface for 
* objects that compute ephemeris.
*
*/
class CEphemerisBase
{
public:
	struct tEphemeris
	{
		CJulianDate jd;
		const CCatalogObject* object;
		tEphemeris() : object(nullptr) {}
	};

	CEphemerisBase() {}

	virtual ~CEphemerisBase() {}

	// Set geographic location
	void setObserverLocation(const CGeoCoordinates& loc);

	// Add catalogs
	void addCatalog(CCatalog* catalog);

	// Delete all records
	void clear()
	{
		m_rec.clear();
	}

	// Number of records
	size_t size() const
	{
		return m_rec.size();
	}

	// True if there are no records
	bool empty() const
	{
		return m_rec.empty();
	}

	// Get records by index
	const tEphemeris& at(int index) const
	{
		return m_rec[index];
	}

	// Get records by index
	const tEphemeris& operator[](int index) const
	{
		return at(index);
	}

	// Iterator
	std::vector<tEphemeris>::const_iterator cbegin() const
	{
		return m_rec.cbegin();
	}

	// Iterator
	std::vector<tEphemeris>::const_iterator cend() const
	{
		return m_rec.cend();
	}

public:
	CGeoCoordinates m_loc;

	std::vector<tEphemeris> m_rec;
};
