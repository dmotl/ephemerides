/*!
*  \file      CBSC1991Catalog.h
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
* \brief Bright Star Catalog (BSC) 1991
*
* The CBSC1991Catalog class implements reading and querying the catalog
* of stellar objects. The BSC 1991 is used to draw overview sky charts.
* 
*/
class CBSC1991Catalog : public CCatalogFile
{
public:
	explicit CBSC1991Catalog(const QString& filePath) : CCatalogFile(filePath), m_index(-1) {}

	bool open(tCancelledFn cbCancelled, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue) override;

	QString errorMessage() const noexcept override { return m_errorMessage; }

	QString name() const override { return QStringLiteral("BSC 1991"); }

	size_t count() const override { return m_objects.size(); }

	const CCatalogObject* at(int index) const override;

	void pickle(QIODevice*) override;

	void unpickle(QIODevice*) override;

	const CCatalogObject* first() override;

	const CCatalogObject* next() override;

protected:
	struct tObject;
	class CBSCCatalogObject;

	struct tObject
	{
		size_t offset, length;
		int bs_num, hd_num;
		CEquCoordinates coords;
		double mag;

		CBSCCatalogObject* ptr;

		tObject() : offset(0), length(0), bs_num(0), hd_num(0), mag(-99.9), ptr(nullptr) {}

		tObject(const tObject& other) : offset(other.offset), length(other.length), bs_num(other.bs_num), hd_num(other.hd_num), coords(other.coords),
			mag(other.mag), ptr(nullptr)
		{
			if (other.ptr)
				ptr = new CBSCCatalogObject(other.ptr->catalog(), this);
		}

		tObject(tObject&& other) noexcept : offset(other.offset), length(other.length), bs_num(other.bs_num), hd_num(other.hd_num), coords(other.coords),
			mag(other.mag), ptr(nullptr)
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
				bs_num = other.bs_num;
				hd_num = other.hd_num;
				coords = other.coords;
				mag = other.mag;
				delete ptr;
				if (other.ptr)
					ptr = new CBSCCatalogObject(other.ptr->catalog(), this);
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
				bs_num = other.bs_num;
				hd_num = other.hd_num;
				coords = other.coords;
				mag = other.mag;
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

	class CBSCCatalogObject : public CStellarObject
	{
	public:
		CBSCCatalogObject(CCatalog* _p, const tObject* _q) : CStellarObject(_p), q(_q) {}

		tObjectType objectType(void) const override { return tObjectType::STAR; }
		CEquCoordinates coords(void) const override { return q->coords; }
		double vmag(void) const override { return q->mag; }

	private:
		friend struct tObject;

		const tObject* q;
	};

	QByteArray m_data;
	QList<tObject> m_objects;
	QString m_errorMessage;

	int m_index;

	void reset() { m_objects.clear(); m_index = -1; }

	const CCatalogObject* find() const;
};

inline const CCatalogObject* CBSC1991Catalog::at(int index) const 
{ 
	return m_objects.at(index).ptr; 
}
