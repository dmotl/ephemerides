/*!
*  \file      CCatalogObject.h
*  \author    David Motl
*  \date      2022-12-19
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

#include "CEquCoordinates.h"

class CCatalog;

/*!
* \brief Base class for catalog objects
*
* The CCatalogObject class provides a common interface for all members
* of catalogs.
*/
class CCatalogObject
{
public:
	explicit CCatalogObject(CCatalog* catalog = nullptr) : m_catalog(catalog) {}

	virtual ~CCatalogObject() {}

	CCatalog* catalog() const { return m_catalog; }

protected:
	CCatalog* m_catalog;

	CCatalogObject(const CCatalogObject&) = delete;
	CCatalogObject& operator=(const CCatalogObject&) = delete;
};


/*!
* \brief Base class for stellar objects
*
* The CStellarObject class extends the CCatalogObject by introducing
* interface commmon to all stellar objects, such as equatorial coordinates
* and magnitude.
* 
*/
class CStellarObject : public CCatalogObject
{
public:
	/* Constructor */
	explicit CStellarObject(CCatalog* catalog = nullptr) : CCatalogObject(catalog) {}

	/* Equatorial J2000 coordinates */
	virtual CEquCoordinates coords(void) const = 0;

	/* Visual magnitude */
	virtual double vmag(void) const = 0;
};


/*!
* \brief Base class for variable stars
*
* The CVariableStar class extends the CStellarObject by introducing
* interface commmon to all variable stars, such as variable designation,
* minimum magnitude, period and epoch.
*
*/
class CVariableStar : public CStellarObject
{
public:
	explicit CVariableStar(CCatalog* catalog = nullptr) : CStellarObject(catalog) {}

	virtual const std::string& variableName(void) const = 0;

	virtual int rating() const = 0;

	virtual double minimumMag() const = 0;

	virtual double period() const = 0;

	virtual double epoch() const = 0;
};
