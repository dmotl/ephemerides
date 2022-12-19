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
#include "UtilsQt.h"
#include "CMainWindow.h"

//
// Constructor
//
CJulianDateConverterDockWidget::CJulianDateConverterDockWidget(CSharedData* data, CMainWindow* mainWnd, QWidget* parent) : CMainDockWidget(data, mainWnd, parent)
{
	registerDockWidget(type_id);

	setupUi(this);

	toJDButton->blockSignals(true);
	toJDButton->setChecked(true);
	toJDButton->blockSignals(false);
	stackedWidget->setCurrentWidget(pageIn);

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
		updateLocal(stackedWidget->currentWidget() == pageIn);
		updateUTC(stackedWidget->currentWidget() == pageIn);
		updateJD(stackedWidget->currentWidget() != pageIn);
	}
}


//
// Time modified
//
void CJulianDateConverterDockWidget::on_utcEditIn_dateTimeChanged(const QDateTime& dateTime)
{
	QDateTime local_time = utcToLocal(dateTime);
	if (m_dateTimeLocal != local_time) {
		m_dateTimeLocal = local_time;
		updateLocal(true);
		updateJD(false);
	}
}


//
// Time modified
//
void CJulianDateConverterDockWidget::on_localEditIn_dateTimeChanged(const QDateTime& dateTime)
{
	if (m_dateTimeLocal != dateTime) {
		m_dateTimeLocal = dateTime;
		updateUTC(true);
		updateJD(false);
	}
}


//
// Update displayed time
//
void CJulianDateConverterDockWidget::updateUTC(bool in)
{
	QDateTime dt = localToUTC(m_dateTimeLocal);
	if (in) {
		if (m_dateTimeLocal.isValid()) {
			utcEditIn->blockSignals(true);
			utcEditIn->setDateTime(dt);
			utcEditIn->blockSignals(false);
		}
	}
	else {
		if (dt.isValid()) 
			utcEditOut->setText(dt.toString(QStringLiteral("yyyy-MM-dd hh:mm:ss")));
		else 
			utcEditOut->setText(tr("Invalid input"));
	}
}


//
// Update displayed time
//
void CJulianDateConverterDockWidget::updateLocal(bool in)
{
	if (in) {
		if (m_dateTimeLocal.isValid()) {
			localEditIn->blockSignals(true);
			localEditIn->setDateTime(m_dateTimeLocal);
			localEditIn->blockSignals(false);
		}
	}
	else {
		if (m_dateTimeLocal.isValid()) 
			localEditOut->setText(m_dateTimeLocal.toString(QStringLiteral("yyyy-MM-dd hh:mm:ss")));
		else 
			localEditOut->setText(tr("Invalid input"));
	}
}


//
// Reset time and location to value stored in the shared data
//
void CJulianDateConverterDockWidget::reset()
{
	m_dateTimeLocal = m_sharedData->getSelectedLocalDateTime();
	updateLocal(stackedWidget->currentWidget() == pageIn);
	updateUTC(stackedWidget->currentWidget() == pageIn);
	updateJD(stackedWidget->currentWidget() != pageIn);
}


//
// Update Julian date
//
void CJulianDateConverterDockWidget::updateJD(bool in)
{
	if (in) {
		if (m_dateTimeLocal.isValid()) {
			jdEditIn->blockSignals(true);
			jdEditIn->setText(QString::number(localToJD(m_dateTimeLocal), 'f', 6));
			jdEditIn->blockSignals(false);
		}
	}
	else {
		if (m_dateTimeLocal.isValid()) 
			jdEditOut->setText(QString::number(localToJD(m_dateTimeLocal), 'f', 6));
		else
			jdEditOut->setText(tr("Invalid input"));
	}
}


//
// Longitude modified
//
void CJulianDateConverterDockWidget::on_jdEditIn_textChanged(const QString& text)
{
	QDateTime dateTime = jdToLocal(text.toDouble());
	if (dateTime != m_dateTimeLocal) {
		m_dateTimeLocal = dateTime;
		updateLocal(false);
		updateUTC(false);
	}
}


//
// Update displayed longitude value
//
void CJulianDateConverterDockWidget::on_jdEditIn_editingFinished()
{
	updateJD(true);

}


//
// Local time to UTC time
//
QDateTime CJulianDateConverterDockWidget::localToUTC(const QDateTime& local)
{
	if (local.isValid()) {
		QDateTime utc_time = local.toUTC();
		return QDateTime(
			QDate::fromJulianDay(utc_time.date().toJulianDay()),
			QTime::fromMSecsSinceStartOfDay(utc_time.time().msecsSinceStartOfDay())
		);
	}
	return QDateTime();
}


//
// UTC to local time
//
QDateTime CJulianDateConverterDockWidget::utcToLocal(const QDateTime& utc)
{
	if (utc.isValid()) {
		return QDateTime(
			QDate::fromJulianDay(utc.date().toJulianDay()),
			QTime::fromMSecsSinceStartOfDay(utc.time().msecsSinceStartOfDay()), Qt::UTC).toLocalTime();
	}
	return QDateTime();
}


//
// Local time to Julian date
//
double CJulianDateConverterDockWidget::localToJD(const QDateTime& local)
{
	return UtilsQt::toJulianDate(local);
}


//
// Julian date to local time
//
QDateTime CJulianDateConverterDockWidget::jdToLocal(double jd_utc)
{
	return UtilsQt::fromJulianDate(jd_utc);
}


//
// Set direction to "Local time --> Julian date"
//
void CJulianDateConverterDockWidget::on_toJDButton_toggled(bool checked)
{
	if (checked) {
		stackedWidget->setCurrentWidget(pageIn);
		updateLocal(true);
		updateUTC(true);
		updateJD(false);
	}
}


//
// Set direction to "Julian date --> Locale time"
//
void CJulianDateConverterDockWidget::on_fromJDButton_toggled(bool checked)
{
	if (checked) {
		stackedWidget->setCurrentWidget(pageOut);
		updateLocal(false);
		updateUTC(false);
		updateJD(true);
	}
}
