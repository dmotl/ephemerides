#pragma once

#include "CJulianDate.h"
#include "CCatalogObject.h"

class CFilter
{
public:
	CFilter() {}

	virtual ~CFilter() {}

	bool operator()(const CCatalogObject* obj, const CJulianDate& jd) const { return check(obj, jd); }

	virtual CFilter* makeCopy(void) const = 0;

protected:
	virtual bool check(const CCatalogObject* obj, const CJulianDate& jd) const = 0;
};
