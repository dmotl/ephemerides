/*!
*  \file      CCoreApp.cpp
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
#include "CCoreApp.h"

#include "CCatalogLoader.h"
#include "CCatalogList.h"

#include "config.h"

#include "Shlobj.h"

//
// Get path to a standard folder
//
static QString getStandardPath(REFKNOWNFOLDERID rfid, bool create = false)
{
	QString retval;
	wchar_t* path = nullptr;
	HRESULT hRes = SHGetKnownFolderPath(rfid, (create ? KF_FLAG_CREATE : KF_FLAG_DEFAULT), 0, &path);
	if (SUCCEEDED(hRes))
		retval = QString::fromWCharArray(path);
	CoTaskMemFree(path);
	return retval;
}

//-----------------------------------------------------------

CCoreApp::CCoreApp(int argc, char* argv[]) : QApplication(argc, argv)
{
	// Set default encoding to utf-8
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	// Taskbar icon
	setWindowIcon(QIcon(QStringLiteral(":/Resources/ephemerides.ico")));

	// Version
	setApplicationName(QLatin1String(APPLICATION_NAME));
	setApplicationVersion(QLatin1String(VERSION_STRING));

	// System configuration 
	QString sysConfigDir = QDir::toNativeSeparators(QStringLiteral(SYS_CONFIG_DIR));

	// Shared data
	QString dataRootDir = QDir::toNativeSeparators(QStringLiteral(DATA_ROOT_DIR));
	if (dataRootDir.isEmpty()) {
		dataRootDir = getStandardPath(FOLDERID_ProgramData, false);
		if (!dataRootDir.isEmpty())
			dataRootDir = QDir(dataRootDir).filePath(QStringLiteral(APPLICATION_NAME));
	}
	if (!dataRootDir.isEmpty()) {
		// Configuration/state templates
		m_dataDir = dataRootDir;
		// Standard catalogs
		m_localStateDir = QDir(dataRootDir).filePath(QStringLiteral("var"));
		// Documentation and manual
		m_docDir = QDir(dataRootDir).filePath(QStringLiteral("doc"));
		// Translation files
		m_localeDir = QDir(dataRootDir).filePath(QStringLiteral("locale"));
	}

	// User data
	QString userDataDir = QDir::toNativeSeparators(QStringLiteral(DATA_HOME_DIR));
	if (userDataDir.isEmpty()) {
		userDataDir = getStandardPath(FOLDERID_RoamingAppData, false);
		if (!userDataDir.isEmpty())
			userDataDir = QDir(userDataDir).filePath(QStringLiteral(APPLICATION_NAME));
	}
	if (!userDataDir.isEmpty()) {
		// User catalogs
		m_dataHomeDir = userDataDir;
		// User state
		m_stateHomeDir = QDir(userDataDir).filePath(QStringLiteral("state"));
	}

	m_catalogs = new CCatalogList(this);
}

CCoreApp::~CCoreApp()
{
	delete m_catalogs; 
}
