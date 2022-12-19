/*!
*  \file      CCatalogLoader.cpp
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
#include "CCatalogLoader.h"

#include "CCatalogLoaderDialog.h"
#include "CCatalogLoaderThread.h"
#include "CCatalogList.h"

CCatalogLoader::CCatalogLoader(CCatalogsList* catalogs, QWidget* parent) :QObject(parent), m_catalogs(catalogs), 
	m_cancelled(false), m_dialog(NULL), m_thread(NULL), m_retval(0)
{
	m_dialog = new CCatalogLoaderDialog(this, parent);
	connect(this, SIGNAL(setCancelEnabled(bool)), m_dialog, SLOT(setCancelEnabled(bool)));
	connect(this, SIGNAL(setLabelText(const QString&)), m_dialog, SLOT(onSetLabelText(const QString&)));
	connect(this, SIGNAL(setRange(int, int)), m_dialog, SLOT(onSetRange(int, int)));
	connect(this, SIGNAL(setValue(int)), m_dialog, SLOT(onSetValue(int)));
}

int CCatalogLoader::exec()
{
	assert(!m_thread);

	setCancelEnabled(true);
	m_retval = 0;
	m_cancelled = false;
	m_dialog->exec();
	return m_retval;
}

void CCatalogLoader::onThreadFinished()
{
	if (m_thread) {
		m_thread->wait();
		delete m_thread;
		m_thread = NULL;
		m_dialog->close();
	}
}

void CCatalogLoader::onCancelClicked()
{
	m_cancelled = true;
}

int CCatalogLoader::run()
{
	return m_catalogs->open([&] { return m_cancelled; },
		[&](const QString& str) { this->setLabelText(str); },
		[&](int maxValue) { this->setRange(0, maxValue); },
		[&](int currentValue) { this->setValue(currentValue); }
	);
}
