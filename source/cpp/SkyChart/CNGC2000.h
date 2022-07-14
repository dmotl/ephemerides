/*!
*  \file      CNGC2000.h
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

class CNGC2000
{
public:
	enum class tObjectType
	{
		UNKNOWN,
		GALAXY,
		OPEN_CLUSTER,
		GLOB_CLUSTER,
		NEBULA,
		PLAN_NEBULA,
		TRIPPLE_STAR,
		DOUBLE_STAR,
		STAR,
		UNCERTAIN,
		CL_AND_NB,
		ASTERISM,
		KNOT,
		NON_EXISTENT,
		DEFECT,
		SUPERNOVA,
	};

	enum class tCatalog 
	{ 
		UNDEFINED,
		IC, 
		NGC 
	};

	class CObjectDesignation
	{
	public:

		tCatalog cat;
		int number;

		CObjectDesignation() : cat(tCatalog::UNDEFINED), number(0) {}
		CObjectDesignation(tCatalog c, int num) : cat(c), number(num) {}
		CObjectDesignation(const std::string&);

		bool operator==(const CObjectDesignation&) const;
		bool operator!=(const CObjectDesignation& other) const { return !this->operator==(other); }
		bool operator<(const CObjectDesignation&) const;
		bool operator>=(const CObjectDesignation& other) const { return !this->operator<(other); }
		bool operator>(const CObjectDesignation& other) const { return other.operator<(*this); }
		bool operator<=(const CObjectDesignation& other) const { return !other.operator<(*this); }
	};

	struct CObject : public CSkyObject
	{
	public:
		CObject(const CObjectDesignation&id,
			tObjectType type, const CEquCoordinates& pos, std::string& con, double mag) : m_id(id), m_type(type), m_pos(pos), m_mag(mag), m_messier(0) {}
		tObjectType type(void) const { return m_type; }
		CEquCoordinates equatorialJ2000(void) override { return m_pos; }
		const CObjectDesignation& designation(void) const { return m_id; }
		double magnitude(void) const { return m_mag; }

		int messier(void) const { return m_messier; }

	private:
		friend class CNGC2000;

		CObjectDesignation m_id;
		tObjectType m_type;
		CEquCoordinates m_pos;
		double m_mag;
		int m_messier;
	};

	CNGC2000() {}

	~CNGC2000();

	void clear();

	bool load(const char* dirPath);

	const std::vector<CObject*>& data() const
	{
		return m_list;
	}

	CObject* find_ngc(int ngc_num) const;
	CObject* find_ic(int ic_num) const;
	CObject* find_messier(int m_num) const;

	static double invalidMagnitude() { return -99; }

private:
	std::vector<CObject*> m_list;
	std::map<int, CObject*> m_ngc, m_ic, m_messier;

	CNGC2000(const CNGC2000&) = delete;
	CNGC2000& operator=(const CNGC2000&) const = delete;
};
