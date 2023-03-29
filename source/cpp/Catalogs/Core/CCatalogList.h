/*!
*  \file      CCatalogList.h
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

#include "CConfigSupport.h"

class CCoreApp;
class CCatalog;

/*!
* \brief Contatainer for catalogs
*
* The CCatalogsList class holds multitude catalogs of objects.
* 
*/
class CCatalogList : public QObject, CConfigSupport
{
public:
	using tCancelledFn = std::function<bool()>;
	using tSetCaption = std::function<void(const QString&)>;
	using tSetProgressMaxFn = std::function<void(int)>;
	using tSetProgressValueFn = std::function<void(int)>;

	// Constructor
	explicit CCatalogList(CCoreApp* app, QObject* parent = nullptr) : QObject(parent), m_app(app), m_userConfigModified(false), m_sharedConfigModified(false) {}

	~CCatalogList() override { close(); }
	
	int open(tCancelledFn cbCancelled, tSetCaption cbSetCaption, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue);

	void close();

	// Add a catalog
	void insert(CCatalog* catalog);

	// Remove a catalog
	void remove(CCatalog* catalog);

	// Number of catalogs
	int count() const { return m_catalogs.size(); }

	// Get catalog by index
	CCatalog* at(int index) const { return m_catalogs.at(index); }

	CCatalog* find(const QString& name) const;

private:
	CCoreApp* m_app;

	QString m_sharedCatalogsDir;
	QString m_userCatalogsDir;
	QString m_sharedCacheDir;
	QString m_userCacheDir;

	QList<CCatalog*> m_catalogs;

	QJsonDocument m_userConfig, m_sharedConfig;

	bool m_userConfigModified, m_sharedConfigModified;

	void loadCatalog(int catalogIndex, CCatalog* catalog,
		tCancelledFn cbCancelled, tSetCaption cbSetCaption,
		tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue
	);

	void saveChanges();

	static QString makeUniqueFile(const QString& dir, const QString& suffix);
};
