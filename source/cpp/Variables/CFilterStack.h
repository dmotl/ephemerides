#pragma once

#include <QtCore>

#include "CFilter.h"

class CFilterStack : public CFilter
{
public:
	CFilterStack() {}

	CFilterStack(const CFilterStack&);
	CFilterStack(CFilterStack&&) noexcept;

	CFilterStack& operator=(const CFilterStack&);
	CFilterStack& operator=(CFilterStack&&) noexcept;

	~CFilterStack() override { qDeleteAll(m_data); }

	CFilter* makeCopy(void) const override { return new CFilterStack(*this); }

protected:
	bool check(const CCatalogObject* obj, const CJulianDate& jd) const override;

private:
	QStack<CFilter*> m_data;
};
