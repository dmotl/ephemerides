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
#include "UtilsQt.h"

//
// Constructor
//
CHeliocentricCorrectionDockWidget::CHeliocentricCorrectionDockWidget(CSharedData* data, QWidget* parent) : QDockWidget(parent), m_sharedData(data)
{
	setupUi(this);
	setWindowTitle(tr("Heliocentric correction"));

	localButton->blockSignals(true);
	localButton->setChecked(true);
	localButton->blockSignals(false);
	on_localButton_toggled(true);
	
	reset();

	connect(m_sharedData, &CSharedData::dateTimeChanged, this, &CHeliocentricCorrectionDockWidget::onDateTimeChanged);
	connect(m_sharedData, &CSharedData::equLocationChanged, this, &CHeliocentricCorrectionDockWidget::onEquLocationChanged);
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
// Object coordinates changed
//
void CHeliocentricCorrectionDockWidget::onEquLocationChanged()
{
	CEquCoordinates rd = m_sharedData->equLocation();
	if (m_equloc != rd) {
		m_equloc = rd;
		updateObjectCoordinates();
		updateValues();
	}
}


//
// Time modified
//
void CHeliocentricCorrectionDockWidget::on_dateEdit_dateTimeChanged(const QDateTime& dateTime)
{
	if (m_dateTimeLocal != dateTime) {
		m_dateTimeLocal = dateTime;
		updateDateTime();
		updateValues();
	}
}


//
// Julian date changed
//
void CHeliocentricCorrectionDockWidget::on_jdEdit_textChanged(const QString& text)
{
	bool ok;
	QDateTime dateTime = jdToLocal(text.toDouble(&ok));
	if (dateTime.isValid() && dateTime != m_dateTimeLocal) {
		m_dateTimeLocal = dateTime;
		updateDateTime();
		updateValues();
	}
}


//
// Right ascension changed
//
void CHeliocentricCorrectionDockWidget::on_raEdit_textChanged(const QString& text)
{
	CRightAscension ra(text.toStdWString());
	if (ra.isValid() && ra != m_equloc.rightAscension()) {
		m_equloc.setRightAscension(ra);
		updateValues();
	}
}


//
// Update displayed right ascension
//
void CHeliocentricCorrectionDockWidget::on_raEdit_editingFinished()
{
	updateObjectCoordinates();
}


//
// Right ascension changed
//
void CHeliocentricCorrectionDockWidget::on_decEdit_textChanged(const QString& text)
{
	CDeclination dec(text.toStdWString());
	if (dec.isValid() && dec != m_equloc.declination()) {
		m_equloc.setDeclination(dec);
		updateValues();
	}
}


//
// Update displayed declination
//
void CHeliocentricCorrectionDockWidget::on_decEdit_editingFinished()
{
	updateObjectCoordinates();
}


//
// Update date and time
//
void CHeliocentricCorrectionDockWidget::on_jdEdit_editingFinished()
{
	updateDateTime();
	updateValues();
}


//
// Update displayed time
//
void CHeliocentricCorrectionDockWidget::updateDateTime()
{
	if (m_dateTimeLocal.isValid()) {
		if (jdButton->isChecked()) {
			jdEdit->setVisible(true);
			jdEdit->blockSignals(true);
			jdEdit->setText(QString::number(localToJD(m_dateTimeLocal), 'f', 6));
			jdEdit->blockSignals(false);
			dateEdit->setVisible(false);
		}
		else if (utcButton->isChecked()) {
			dateEdit->setVisible(true);
			dateEdit->blockSignals(true);
			dateEdit->setDateTime(localToUTC(m_dateTimeLocal));
			dateEdit->blockSignals(false);
			jdEdit->setVisible(false);
		}
		else {
			dateEdit->setVisible(true);
			dateEdit->blockSignals(true);
			dateEdit->setDateTime(m_dateTimeLocal);
			dateEdit->blockSignals(false);
			jdEdit->setVisible(false);
		}
	}
	else {
		jdEdit->setVisible(true);
		jdEdit->blockSignals(true);
		jdEdit->setText(tr("Invalid input"));
		jdEdit->blockSignals(false);
		dateEdit->setVisible(false);
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
	m_equloc = m_sharedData->equLocation();
	updateObjectCoordinates();
	updateValues();
}

//
// Update Julian date
//
void CHeliocentricCorrectionDockWidget::updateValues()
{
	CJulianDate jd = localToJD(m_dateTimeLocal);
	if (!jd.isNull() && m_equloc.isValid()) 
		hcEdit->setText(QString::number(jd.HeliocentricCorrection(m_equloc), 'f', 6));
	else
		hcEdit->setText(tr("Invalid input"));
}


//
// Update displayed location
//
void CHeliocentricCorrectionDockWidget::updateObjectCoordinates()
{
	raEdit->blockSignals(true);
	if (m_equloc.rightAscension().isValid())
		raEdit->setText(QString::fromStdWString(m_equloc.rightAscension().toString()));
	else
		raEdit->setText(QStringLiteral("***"));
	raEdit->blockSignals(false);

	decEdit->blockSignals(true);
	if (m_equloc.declination().isValid())
		decEdit->setText(QString::fromStdWString(m_equloc.declination().toString()));
	else
		decEdit->setText(QStringLiteral("***"));
	decEdit->blockSignals(false);
}


//
// Show Universal time
//
void CHeliocentricCorrectionDockWidget::on_utcButton_toggled(bool checked)
{
	if (checked) {
		dateLabel->setText(tr("Universal time"));
		updateDateTime();
	}
}


//
// Show local time
//
void CHeliocentricCorrectionDockWidget::on_localButton_toggled(bool checked)
{
	if (checked) {
		dateLabel->setText(tr("Local time"));
		updateDateTime();
	}
}


//
// Show Julian date
//
void CHeliocentricCorrectionDockWidget::on_jdButton_toggled(bool checked)
{
	if (checked) {
		dateLabel->setText(tr("Julian date (UTC)"));
		updateDateTime();
	}
}


//
// Local time to UTC time
//
QDateTime CHeliocentricCorrectionDockWidget::localToUTC(const QDateTime& local)
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
QDateTime CHeliocentricCorrectionDockWidget::utcToLocal(const QDateTime& utc)
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
double CHeliocentricCorrectionDockWidget::localToJD(const QDateTime& local)
{
	return UtilsQt::toJulianDate(local);
}


//
// Julian date to local time
//
QDateTime CHeliocentricCorrectionDockWidget::jdToLocal(double jd_utc)
{
	return UtilsQt::fromJulianDate(jd_utc);
}
