/*!
*  \file      CEphemerisUpdater.cpp
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
#include "CEphemerisUpdater.h"

#include "CEphemerisUpdaterDialog.h"
#include "CEphemerisUpdaterThread.h"
#include "CEphemerisBase.h"

CEphemerisUpdater::CEphemerisUpdater(CEphemerisBase* ephemeris, QWidget* parent) :QObject(parent), m_ephemeris(ephemeris),
m_retval(0), m_cancelled(false), m_dialog(NULL), m_thread(NULL)
{
	m_dialog = new CEphemerisUpdaterDialog(this, parent);
	connect(this, SIGNAL(setCancelEnabled(bool)), m_dialog, SLOT(setCancelEnabled(bool)));
	connect(this, SIGNAL(setLabelText(const QString&)), m_dialog, SLOT(onSetLabelText(const QString&)));
	connect(this, SIGNAL(setRange(int, int)), m_dialog, SLOT(onSetRange(int, int)));
	connect(this, SIGNAL(setValue(int)), m_dialog, SLOT(onSetValue(int)));
}

int CEphemerisUpdater::exec(const CJulianDate& start, const CJulianDate& end)
{
	assert(!m_thread);

	setCancelEnabled(true);
	m_start = start;
	m_end = end;
	m_retval = 0;
	m_cancelled = false;
	m_dialog->exec();
	return m_retval;
}

void CEphemerisUpdater::onThreadFinished()
{
	if (m_thread) {
		m_thread->wait();
		delete m_thread;
		m_thread = NULL;
		m_dialog->close();
	}
}

void CEphemerisUpdater::onCancelClicked()
{
	m_cancelled = true;
}

int CEphemerisUpdater::run()
{
	m_ephemeris->update(m_start, m_end, [&] { return m_cancelled; },
		[&](const QString& str) { this->setLabelText(str); },
		[&](int maxValue) { this->setRange(0, maxValue); },
		[&](int currentValue) { this->setValue(currentValue); }
	);
	return 1;
}
