#pragma once

#include <string>
#include <list>
#include <map>

#include "CSkyObject.h"

class CBSC1991
{
public:
	struct CObject : public CSkyObject
	{
	public:
		CObject(int bs_num,
			const CEquCoordinates& pos, double mag) : m_bsnum(bs_num), m_pos(pos), m_mag(mag) {}
		CEquCoordinates pos(void) override { return m_pos; }
		int brightStarNumber(void) const { return m_bsnum; }
		double magnitude(void) const { return m_mag; }

	private:
		friend class CNGC2000;

		int m_bsnum;
		CEquCoordinates m_pos;
		double m_mag;
	};

public:
	CBSC1991() {}

	~CBSC1991();

	void clear();

	bool load(const char* dirPath);

	const std::list<CObject*>& data() const
	{
		return m_list;
	}

	CObject* find_bs(int bs_num) const;

	static double invalidMagnitude() { return -99; }

private:
	std::list<CObject*> m_list;
	std::map<int, CObject*> m_idmap;

	CBSC1991(const CBSC1991&) = delete;
	CBSC1991& operator=(const CBSC1991&) const = delete;
};
