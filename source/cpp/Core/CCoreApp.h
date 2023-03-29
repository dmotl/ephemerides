/*!
*  \file      CCoreApp.h
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

#include <QtWidgets>

class CCatalogList;

/*!
* \brief Core application
*
* The CCoreApp extends the QApplication class and provides an internal 
* environment for running the application, such as paths to shared 
* and user directories.
*
*/
class CCoreApp : public QApplication
{
public:
	CCoreApp(int argc, char* argv[]);

	~CCoreApp() override;

	CCatalogList& catalogs() { assert(m_catalogs != NULL); return *m_catalogs; }

	// Path to the directory with read-only architecture-independent data files
	QString dataDir() const{ return m_dataDir; }

	// Path to the file with host-specific read-only configuration
	QString sysConfigFilePath() const { return m_sysConfigFilePath; }

	// Path to the directory with shared architecture-independent data files which the programs modify while they run
	QString localStateDir() const { return m_localStateDir; }

	// Path to the directory with documentation, manual, ...
	QString docDir() const { return m_docDir; }

	// Path to the directory with translation tables 
	QString localeDir() const { return m_localeDir; }

	// Path to the directory with read-only architecture-independent data files
	QString dataHomeDir() const { return m_dataHomeDir; }

	// Path to the file with user-specific read-only configuration
	QString useConfigFilePath() const { return m_useConfigFilePath; }

	// Path to the directory with user-specific data files which the programs modify while they run
	QString stateHomeDir() const { return m_stateHomeDir; }

protected:
	CCatalogList *m_catalogs;

	// Path to the directory with read-only architecture-independent data files
	QString m_dataDir;

	// Path to the file with host-specific read-only configuration
	QString m_sysConfigFilePath;

	// Path to the directory with shared architecture-independent data files which the programs modify while they run
	QString m_localStateDir;

	// Path to the directory with documentation, manual, ...
	QString m_docDir;

	// Path to the directory with translation tables 
	QString m_localeDir;

	// Path to the directory with read-only architecture-independent data files
	QString m_dataHomeDir;

	// Path to the file with user-specific read-only configuration
	QString m_useConfigFilePath;

	// Path to the directory with user-specific data files which the programs modify while they run
	QString m_stateHomeDir;
};
