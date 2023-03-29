#pragma once

class CCatalogObject;

class CSource
{
public:
	CSource() {}

	virtual ~CSource() {}

	virtual const CCatalogObject* first() = 0;

	virtual const CCatalogObject* next() = 0;
};
