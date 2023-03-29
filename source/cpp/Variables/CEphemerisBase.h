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

#include <QtCore>

#include "CJulianDate.h"

class CCatalogObject;

/*
* \brief Ephemeris (base class)
*
* The CEphemerisBase provides a common interface for 
* objects that compute ephemeris.
*
*/
class CEphemerisBase : public QObject
{
public:
	using tCancelledFn = std::function<bool()>;
	using tSetCaption = std::function<void(const QString&)>;
	using tSetProgressMaxFn = std::function<void(int)>;
	using tSetProgressValueFn = std::function<void(int)>;

	struct tEphemeris
	{
		CJulianDate jd;
		const CCatalogObject* object;
		tEventType evtype;
		tEphemeris() : object(nullptr), evtype(tEventType::Unknown) {}
	};

	explicit CEphemerisBase(QObject* parent = nullptr) : QObject(parent) {}

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

	// List of records
	QList<tEphemeris> list() const
	{
		return m_rec;
	}

	// Update ephemeris
	virtual void update(CJulianDate start, CJulianDate end, tCancelledFn cbCancelled, tSetCaption cbSetCaption, 
		tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue) = 0;

public:
	QList<tEphemeris> m_rec;
};
