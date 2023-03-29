/*!
*  \file      CCatalogList.cpp
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
#include "CCatalogList.h"

#include "CCatalog.h"
#include "CVSXCatalog.h"
#include "CBSC1991Catalog.h"
#include "CCoreApp.h"

#include <iostream>
#include <fstream>

//
// Constructor
//
int CCatalogList::open(tCancelledFn cbCancelled, tSetCaption cbSetCaption, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue)
{
	close();

	assert(m_app != nullptr);

	cbSetCaption("Loading catalogs...");
	cbSetProgressRange(0);

	QString sharedStateDir = m_app->localStateDir();
	if (!sharedStateDir.isEmpty()) {
		QString dir = QDir(sharedStateDir).filePath(QStringLiteral("catalogs"));
		if (!QFileInfo(dir).exists() && !QDir().mkpath(dir)) {
			qDebug() << QStringLiteral("CCatalogsList: Failed to create directory ") + QDir::toNativeSeparators(dir);
			return 1;
		}
		m_sharedCatalogsDir = dir;
	}

	if (!m_sharedCatalogsDir.isEmpty()) {
		m_sharedConfig = fromFile(QDir(m_sharedCatalogsDir).filePath("catalogs.json"));

		QString dir = QDir(QDir(sharedStateDir).filePath(QStringLiteral("cache"))).filePath("catalogs");
		if (!QFileInfo(dir).exists() && !QDir().mkpath(dir)) {
			qDebug() << QStringLiteral("CCatalogsList: Failed to create directory ") + QDir::toNativeSeparators(dir);
			return 1;
		}
		m_sharedCacheDir = dir;
	}

	QString userStateDir = m_app->stateHomeDir();
	if (!userStateDir.isEmpty()) {
		QString dir = QDir(userStateDir).filePath(QStringLiteral("catalogs"));
		if (!QFileInfo(dir).exists() && !QDir().mkpath(dir)) {
			qDebug() << QStringLiteral("CCatalogsList: Failed to create directory ") + QDir::toNativeSeparators(dir);
			return 1;
		}
		m_userCatalogsDir = dir;
	}

	if (!m_userCatalogsDir.isEmpty()) {
		m_userConfig = fromFile(QDir(m_userCatalogsDir).filePath("catalogs.json"));

		QString dir = QDir(QDir(sharedStateDir).filePath(QStringLiteral("cache"))).filePath("catalogs");
		if (!QFileInfo(dir).exists() && !QDir().mkpath(dir)) {
			qDebug() << QStringLiteral("CCatalogsList: Failed to create directory ") + QDir::toNativeSeparators(dir);
			return 1;
		}
		m_userCacheDir = dir;
	}

	int catalogCount = 2;
	cbSetProgressRange(catalogCount * 1000);
	if (!m_sharedCatalogsDir.isEmpty() && QFileInfo(m_sharedCatalogsDir).isDir()) {
		int catalogIndex = 0;
		QString vsxFilePath = QDir(QDir(QDir(m_sharedCatalogsDir).filePath(QStringLiteral("Variables"))).filePath(QStringLiteral("vsx"))).filePath(QStringLiteral("vsx.dat"));
		loadCatalog(catalogIndex++, new CVSXCatalog(vsxFilePath), cbCancelled, cbSetCaption, cbSetProgressRange, cbSetProgressValue);
		QString bscFilePath = QDir(QDir(QDir(m_sharedCatalogsDir).filePath(QStringLiteral("Stars"))).filePath(QStringLiteral("bsc91"))).filePath(QStringLiteral("catalog"));
		loadCatalog(catalogIndex++, new CBSC1991Catalog(bscFilePath), cbCancelled, cbSetCaption, cbSetProgressRange, cbSetProgressValue);
	}

	saveChanges();

	return 0;
}

void CCatalogList::saveChanges()
{
	if (m_userConfigModified && !m_userCatalogsDir.isEmpty()) {
		if (!m_userConfig.isEmpty())
			toFile(m_userConfig, QDir(m_userCatalogsDir).filePath("catalogs.json"));
		else
			QFile::remove(QDir(m_userCatalogsDir).filePath("catalogs.json"));
		m_userConfigModified = false;
	}
	if (m_sharedConfigModified && !m_sharedCatalogsDir.isEmpty()) {
		if (!m_sharedConfig.isEmpty())
			toFile(m_sharedConfig, QDir(m_sharedCatalogsDir).filePath("catalogs.json"));
		else
			QFile::remove(QDir(m_sharedCatalogsDir).filePath("catalogs.json"));
		m_sharedConfigModified = false;
	}
}

void CCatalogList::close()
{
	saveChanges();

	qDeleteAll(m_catalogs);
	m_catalogs.clear();
	m_sharedCatalogsDir.clear();
	m_userCatalogsDir.clear();
}

void CCatalogList::loadCatalog(int catalogIndex, CCatalog* catalog,
	tCancelledFn cbCancelled, tSetCaption cbSetCaption, tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue)
{
	cbSetCaption(QStringLiteral("Loading ") + catalog->name());

	try {
		bool cached = false;

		QString name = catalog->name();
		bool user = catalog->user();
		if (!name.isEmpty()) {
			QJsonArray cache;
			if (user)
				cache = m_userConfig["Catalogs"]["Cache"].toArray();
			else
				cache = m_sharedConfig["Catalogs"]["Cache"].toArray();
			auto begin = cache.cbegin(), end = cache.cend();
			while (begin != end) {
				const auto& item = *begin;
				if (item[QStringLiteral("name")].toString() == name) {
					QString file = item[QStringLiteral("file")].toString();
					if (!file.isEmpty() && item[QStringLiteral("sign")].toString() == catalog->getSignature()) {
						QString path = QDir((user ? m_userCacheDir : m_sharedCacheDir)).filePath(file + ".dat");
						QFile cache_file(path);
						if (cache_file.open(QIODeviceBase::ReadOnly)) {
							try {
								catalog->unpickle(&cache_file);
								m_catalogs.append(catalog);
								cached = true;
							}
							catch (std::runtime_error&) {
								// Not present in cache
							}
						}
					}
					break;
				}
				++begin;
			}
		}

		if (!cached) {
			long long catalogMax = 0;
			if (!catalog->open(cbCancelled,
				[&](long long max)
				{
					catalogMax = max;
				},
				[&](long long pos) {
					if (catalogMax > 0)
						cbSetProgressValue(catalogIndex * 1000 + static_cast<int>(static_cast<double>(pos) / catalogMax * 1000));
				}
					)) {
				qDebug() << QStringLiteral("CCatalogsList: Failed to load catalog ") + catalog->name();
				qDebug() << QStringLiteral("CCatalogsList: ") + catalog->errorMessage();
			}
			else {
				QString cacheDir = user ? m_userCacheDir : m_sharedCacheDir;
				if (!cacheDir.isEmpty() && QDir(cacheDir).exists()) {
					QJsonObject obj;
					obj.insert(QStringLiteral("name"), catalog->name());
					QByteArray buf;
					QBuffer stream(&buf);
					stream.open(QIODevice::WriteOnly);
					try {
						catalog->pickle(&stream);
						stream.close();
					}
					catch (std::runtime_error&) {
						stream.close();
						buf = QByteArray();
					}
					if (!buf.isEmpty()) {
						QString path = makeUniqueFile(cacheDir, ".dat");
						if (!path.isEmpty()) {
							QFile cache_file(path);
							if (cache_file.open(QIODeviceBase::WriteOnly | QIODeviceBase::Truncate)) {
								if (cache_file.write(buf) == buf.size()) {
									obj.insert(QStringLiteral("file"), QFileInfo(path).completeBaseName());
									obj.insert(QStringLiteral("sign"), catalog->getSignature());
								}
							}
						}
					}
					QJsonObject rootObj;
					if (user) {
						if (!m_userConfig.isObject())
							m_userConfig.setObject(QJsonObject());
						rootObj = m_userConfig.object();
					}
					else {
						if (!m_sharedConfig.isObject())
							m_sharedConfig.setObject(QJsonObject());
						rootObj = m_sharedConfig.object();
					}
					if (!rootObj["Catalogs"].isObject()) {
						rootObj.remove("Catalogs");
						rootObj.insert("Catalogs", QJsonObject());
					}
					QJsonObject catalogsObj = rootObj["Catalogs"].toObject();
					if (!catalogsObj["Cache"].isArray()) {
						catalogsObj.remove("Cache");
						catalogsObj.insert("Cache", QJsonArray());
					}
					QJsonArray old_cache = catalogsObj["Cache"].toArray();
					QJsonArray new_cache;
					auto begin = old_cache.cbegin(), end = old_cache.cend();
					bool found = false;
					while (begin != end) {
						const auto& item = *begin;
						if (item[QStringLiteral("name")].toString() == name) {
							if (!found) {
								new_cache.append(obj);
								found = true;
							}
						}
						else
							new_cache.append(item);
						++begin;
					}
					if (!found) 
						new_cache.append(obj);
					catalogsObj.remove("Cache");
					catalogsObj.insert("Cache", new_cache);
					rootObj.insert("Catalogs", catalogsObj);
					if (user) {
						m_userConfig.setObject(rootObj);
						m_userConfigModified = true;
					}
					else {
						m_sharedConfig.setObject(rootObj);
						m_sharedConfigModified = true;
					}
				}
			}
			m_catalogs.append(catalog);
		}
	}
	catch (std::bad_alloc&) {
		return;
	}
}

QString CCatalogList::makeUniqueFile(const QString& dirPath, const QString& suffix)
{
	static const char* chars = "0123456789abcdefghijklmnopqrstuvwxyz";
	static const int len = (int)strlen(chars);

	QDir dir(dirPath);
	if (dir.exists()) {
		while (true) {
			QString fileName;
			for (int i = 0; i < 16; i++) 
				fileName.append(QLatin1Char(chars[rand() % len]));
			fileName += suffix;
			if (!dir.exists(fileName))
				return dir.filePath(fileName);
		}
	}
	return QString();
}

CCatalog* CCatalogList::find(const QString& name) const
{
	for (int i = 0; i < m_catalogs.count(); i++) {
		CCatalog* c = m_catalogs[i];

		assert(c != nullptr);

		if (c->name() == name)
			return c;
	}
	return nullptr;
}
