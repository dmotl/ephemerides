#pragma once

#include "CEquCoordinates.h"

class CSkyObject
{
public:
	CSkyObject() {}

	virtual ~CSkyObject() {}

	virtual CEquCoordinates pos() = 0;
};