/*!
*  \file      CHeliocentricCorrectionDockWidget.cpp
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
#include "CHeliocentricCorrectionDockWidget.h"

#include "CSharedData.h"
#include "CJulianDate.h"
#include "CPlanets.h"
#include "Utils.h"

//
// Constructor
//
CHeliocentricCorrectionDockWidget::CHeliocentricCorrectionDockWidget(CSharedData* data, QWidget* parent) : QDockWidget(parent), m_sharedData(data)
{
	setupUi(this);
	setWindowTitle(tr("Heliocentric correction"));

	reset();

	connect(m_sharedData, &CSharedData::dateTimeChanged, this, &CHeliocentricCorrectionDockWidget::onDateTimeChanged);
}


//
// Time (shared data) changed
//
void CHeliocentricCorrectionDockWidget::onDateTimeChanged()
{
	QDateTime dt = m_sharedData->getSelectedLocalDateTime();
	if (m_dateTimeLocal != dt) {
		m_dateTimeLocal = dt;
		updateDateTime();
		updateValues();
	}
}


//
// Time modified
//
void CHeliocentricCorrectionDockWidget::on_dateTimeEdit_dateTimeChanged(const QDateTime& dateTime)
{
	if (m_dateTimeLocal != dateTime) {
		m_dateTimeLocal = dateTime;
		updateDateTime();
		updateValues();
	}
}


//
// Update displayed time
//
void CHeliocentricCorrectionDockWidget::updateDateTime()
{
	if (m_dateTimeLocal.isValid()) {
		dateTimeEdit->blockSignals(true);
		dateTimeEdit->setDateTime(m_dateTimeLocal);
		dateTimeEdit->blockSignals(false);
	}
}


//
// Reset time and location to value stored in the shared data
//
void CHeliocentricCorrectionDockWidget::on_resetButton_clicked()
{
	reset();
}


//
// Reset time and location to value stored in the shared data
//
void CHeliocentricCorrectionDockWidget::reset()
{
	m_dateTimeLocal = m_sharedData->getSelectedLocalDateTime();
	updateDateTime();
	updateValues();
}

//
// Update Julian date
//
void CHeliocentricCorrectionDockWidget::updateValues()
{
	if (!m_jd.isNull())
		jdEdit->setText(QString::number(m_jd.jd_utc(), 'f', 6));
	else
		jdEdit->setText(tr("Invalid input"));
}
