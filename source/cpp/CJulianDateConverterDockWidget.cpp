/*!
*  \file      CJulianDateConverterDockWidget.cpp
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
#include "CJulianDateConverterDockWidget.h"

#include "CSharedData.h"
#include "CJulianDate.h"
#include "CPlanets.h"
#include "Utils.h"

//
// Constructor
//
CJulianDateConverterDockWidget::CJulianDateConverterDockWidget(CSharedData* data, QWidget* parent) : QDockWidget(parent), m_sharedData(data)
{
	setupUi(this);
	setWindowTitle(tr("Julian date converter"));

	localTimeButton->blockSignals(true);
	localTimeButton->setChecked(true);
	localTimeButton->blockSignals(false);

	reset();

	connect(m_sharedData, &CSharedData::dateTimeChanged, this, &CJulianDateConverterDockWidget::onDateTimeChanged);
}


//
// Time (shared data) changed
//
void CJulianDateConverterDockWidget::onDateTimeChanged()
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
void CJulianDateConverterDockWidget::on_dateTimeEdit_dateTimeChanged(const QDateTime& dateTime)
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
void CJulianDateConverterDockWidget::updateDateTime()
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
void CJulianDateConverterDockWidget::on_resetButton_clicked()
{
	reset();
}


//
// Reset time and location to value stored in the shared data
//
void CJulianDateConverterDockWidget::reset()
{
	m_dateTimeLocal = m_sharedData->getSelectedLocalDateTime();
	updateDateTime();
	updateValues();
}


//
// Set mode to "Local time"
//
void CJulianDateConverterDockWidget::on_localTimeButton_toggled(bool checked)
{
	if (checked)
		updateValues();
}


//
// Set mode to "UTC"
//
void CJulianDateConverterDockWidget::on_universalTimeButton_toggled(bool checked)
{
	if (checked)
		updateValues();
}


//
// Update Julian date
//
void CJulianDateConverterDockWidget::updateValues()
{
	if (!m_jd.isNull())
		jdEdit->setText(QString::number(m_jd.jd_utc(), 'f', 6));
	else
		jdEdit->setText(tr("Invalid input"));
}
