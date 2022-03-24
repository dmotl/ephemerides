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
