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

	QString variableName(void) const override { return m_varName; }

	CEquCoordinates coords(void) const override { return m_coords; }

	double minimumMag() const override { return m_minmag; }

	int rating() const override { return 1; }

	QString type() const { return m_varType; }

	double period() const override { return m_period; }

	double epoch() const override { return m_epoch; }

	double vmag() const override { return m_minmag; }

protected:
	friend class CVSXCatalog;

	int m_oid;

	QString m_varName, m_varType;

	CEquCoordinates m_coords;

	double m_minmag, m_period, m_epoch;
};

class CVSXCatalog : public CCatalogFile
{
public:
	explicit CVSXCatalog(const QString& filePath) : CCatalogFile(filePath), m_index(-1) {}

	bool open(tCancelledFn cbCancelled, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue) override;

	QString errorMessage() const noexcept override { return m_errorMessage; }

	QString name() const override { return QStringLiteral("VSX"); }

	size_t count() const override { return m_objects.size(); }

	const CCatalogObject* at(int index) const override { return m_objects.at(index).ptr; }

	void pickle(QIODevice*) override;

	void unpickle(QIODevice*) override;

	const CCatalogObject* first() override;

	const CCatalogObject* next() override;

protected:
	struct tObject;
	class CVSXCatalogObject;

	struct tObject
	{
		// Values of the variables below are pickled

		size_t offset, length;
		int OID;
		CEquCoordinates coords;
		double epoch, period;

		// Members below are not stored in pickle

		CVSXCatalogObject* ptr;

		QString varName, varType;

		tObject() : offset(0), length(0), OID(0), epoch(0), period(0), ptr(nullptr) {}

		tObject(const tObject& other) : offset(other.offset), length(other.length), OID(other.OID), coords(other.coords), 
			epoch(other.epoch), period(other.period), ptr(nullptr), varName(other.varName), varType(other.varType) 
		{ 
			if (other.ptr)
				ptr = new CVSXCatalogObject(other.ptr->catalog(), this);
		}

		tObject(tObject&& other) noexcept: offset(other.offset), length(other.length), OID(other.OID), coords(other.coords),
			epoch(other.epoch), period(other.period), ptr(nullptr), varName(other.varName), varType(other.varType)
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

	class CVSXCatalogObject : public CVariableStar
	{
	public:
		CVSXCatalogObject(CCatalog* _p, const tObject* _q) : CVariableStar(_p), q(_q) {}

		CEquCoordinates coords(void) const override { return q->coords; }
		double vmag(void) const override { return 0; }
		QString variableName(void) const override { return q->varName; }
		int rating() const override { return 0; }
		double minimumMag() const override { return INVALID_MAG; }
		double maximumMag() const override { return INVALID_MAG; }
		double period() const override { return q->period; }
		double epoch() const override { return q->epoch; }
		QString varTypeString(void) const override { return QString(); }

	private:
		friend struct tObject;

		const tObject* q;
	};

	QByteArray m_data;
	QString m_errorMessage;
	QList<tObject> m_objects;

	int m_index;

	void reset();

	const CCatalogObject* find() const;

};
