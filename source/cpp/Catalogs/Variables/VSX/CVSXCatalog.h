/*!
*  \file      CVSXCatalogObject.h
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

#include "CCatalogObject.h"
#include "CCatalogFile.h"

/*!
* \brief Variable Star Index 
*
* The CVSXCatalogObject class implements reading and querying the catalog
* of variable stars. The VSX is used to compute ephemeris of variable
* stars.
*
*/
class CVSXCatalogObject : public CVariableStar
{
public:
	CVSXCatalogObject(int oid) : m_oid(oid), m_minmag(-99), m_period(0), m_epoch(0) {}

	const std::string& variableName(void) const { return m_varName; }

	CEquCoordinates coords(void) const { return m_coords; }

	double minimumMag() const { return m_minmag; }

	int rating() const { return 1; }

	const std::string& type() const { return m_varType; }

	double period() const { return m_period; }

	double epoch() const { return m_epoch; }

	double vmag() const override { return m_minmag; }

protected:
	friend class CVSXCatalog;

	int m_oid;

	std::string m_varName, m_varType;

	CEquCoordinates m_coords;

	double m_minmag, m_period, m_epoch;
};

class CVSXCatalog : public CCatalogFile
{
public:
	explicit CVSXCatalog(const QString& filePath) : CCatalogFile(filePath) {}

	bool open(tCancelledFn cbCancelled, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue) override;

	QString errorMessage() const noexcept override { return m_errorMessage; }

	QString name() const override { return QStringLiteral("VSX"); }

	size_t count() const override { return m_objects.size(); }

	const CCatalogObject* at(int index) const override { return m_objects.at(index).ptr; }

	void pickle(QIODevice*) override;

	void unpickle(QIODevice*) override;

protected:
	struct tObject;

	class CVSXCatalogObject : public CCatalogObject
	{
	public:
		CVSXCatalogObject(CCatalog* _p, const tObject* _q) : CCatalogObject(_p), q(_q) {}

	private:
		friend struct tObject;

		const tObject* q;
	};

	struct tObject
	{
		size_t offset, length;
		int OID;
		CEquCoordinates coords;
		double epoch, period;

		CVSXCatalogObject* ptr;

		QString varName, varType;

		tObject() : offset(0), length(0), OID(0), epoch(0), period(0), ptr(nullptr) {}

		tObject(const tObject& other) : offset(other.offset), length(other.length), OID(other.OID), varName(other.varName), varType(other.varType), coords(other.coords), 
			epoch(other.epoch), period(other.period), ptr(nullptr) 
		{ 
			if (other.ptr)
				ptr = new CVSXCatalogObject(other.ptr->catalog(), this);
		}

		tObject(tObject&& other): offset(other.offset), length(other.length), OID(other.OID), varName(other.varName), varType(other.varType), coords(other.coords),
			epoch(other.epoch), period(other.period), ptr(nullptr)
		{
			std::swap(ptr, other.ptr);
			if (ptr) 
				ptr->q = this;
		}

		tObject& operator=(const tObject& other)
		{
			if (this != &other) {
				offset = other.offset;
				length = other.length;
				OID = other.OID;
				varName = other.varName;
				varType = other.varType;
				coords = other.coords;
				epoch = other.epoch;
				period = other.period;
				delete ptr;
				if (other.ptr)
					ptr = new CVSXCatalogObject(other.ptr->catalog(), this);
				else
					ptr = nullptr;

			}
			return *this;
		}

		tObject& operator=(tObject&& other) noexcept
		{
			if (this != &other) {
				offset = other.offset;
				length = other.length;
				OID = other.OID;
				varName = other.varName;
				varType = other.varType;
				coords = other.coords;
				epoch = other.epoch;
				period = other.period;
				delete ptr;
				ptr = nullptr;
				std::swap(ptr, other.ptr);
				if (ptr)
					ptr->q = this;
			}
			return *this;
		}

		~tObject() { delete ptr; }
	};

	QByteArray m_data;
	QString m_errorMessage;
	QList<tObject> m_objects;

	void reset();
};
