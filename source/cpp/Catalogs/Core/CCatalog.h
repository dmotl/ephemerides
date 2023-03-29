/*!
*  \file      CCatalog.h
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

#include <QtCore>

#include "CSource.h"

#include <functional>

class CCatalogObject;

/*!
* \brief The base class for catalogs
*
* The CCatalog class provides a common interface for 
* loading, caching and querying catalogs of objects, 
* such as variable stars, stars, deep-sky objects, etc.
*/
class CCatalog : public CSource
{
public:
	using tCancelledFn = std::function<bool()>;
	using tSetProgressMaxFn = std::function<void(long long)>;
	using tSetProgressValueFn = std::function<void(long long)>;

	CCatalog() {}

	virtual ~CCatalog() {}

	virtual bool open(tCancelledFn cbCancelled, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue) = 0;

	virtual bool user() const { return false; }

	virtual QString getSignature() const noexcept = 0;

	virtual QString errorMessage() const noexcept = 0;

	virtual void pickle(QIODevice*) = 0;

	virtual void unpickle(QIODevice*) = 0;

	virtual QString name() const = 0;

	virtual size_t count() const = 0;

	virtual const CCatalogObject* at(int index) const = 0;

	const CCatalogObject* operator[](int index) const { return at(index); }
};
