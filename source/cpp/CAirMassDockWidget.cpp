/*!
*  \file      CAirMassDockWidget.cpp
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
#include "CAirMassDockWidget.h"

#include "CSharedData.h"
#include "CJulianDate.h"
#include "CPlanets.h"
#include "Utils.h"
#include "UtilsQt.h"

//
// Constructor
//
CAirMassDockWidget::CAirMassDockWidget(CSharedData* data, QWidget* parent) : QDockWidget(parent), m_sharedData(data)
{
	setupUi(this);
	setWindowTitle(tr("Air mass"));

	localButton->blockSignals(true);
	localButton->setChecked(true);
	localButton->blockSignals(false);
	on_localButton_toggled(true);

	reset();

	connect(m_sharedData, &CSharedData::dateTimeChanged, this, &CAirMassDockWidget::onDateTimeChanged);
	connect(m_sharedData, &CSharedData::geoLocationChanged, this, &CAirMassDockWidget::onGeoLocationChanged);
	connect(m_sharedData, &CSharedData::equLocationChanged, this, &CAirMassDockWidget::onEquLocationChanged);
}


//
// Time (shared data) changed
//
void CAirMassDockWidget::onDateTimeChanged()
{
	QDateTime dt = m_sharedData->getSelectedLocalDateTime();
	if (m_dateTimeLocal != dt) {
		m_dateTimeLocal = dt;
		updateDateTime();
		updateAzAltCoordinates();
		updateValues();
	}
}


//
// Time modified
//
void CAirMassDockWidget::on_dateEdit_dateTimeChanged(const QDateTime& dateTime)
{
	if (m_dateTimeLocal != dateTime) {
		m_dateTimeLocal = dateTime;
		updateDateTime();
		updateAzAltCoordinates();
		updateValues();
	}
}


//
// Julian date changed
//
void CAirMassDockWidget::on_jdEdit_textChanged(const QString& text)
{
	bool ok;
	QDateTime dateTime = jdToLocal(text.toDouble(&ok));
	if (dateTime.isValid() && dateTime != m_dateTimeLocal) {
		m_dateTimeLocal = dateTime;
		updateDateTime();
		updateAzAltCoordinates();
		updateValues();
	}
}



//
// Longitude modified
//
void CAirMassDockWidget::on_lonEdit_textChanged(const QString& text)
{
	CLongitude lon(text.toStdWString());
	if (lon.isValid() && lon != m_geoloc.longitude()) {
		m_geoloc.setLongitude(lon);
		updateAzAltCoordinates();
		updateValues();
	}
}


//
// Update displayed longitude value
//
void CAirMassDockWidget::on_lonEdit_editingFinished()
{
	updateObserverCoordinates();
}


//
// Latitude modified
//
void CAirMassDockWidget::on_latEdit_textChanged(const QString& text)
{
	CLatitude lat(text.toStdWString());
	if (lat.isValid() && lat != m_geoloc.latitude()) {
		m_geoloc.setLatitude(lat);
		updateAzAltCoordinates();
		updateValues();
	}
}


//
// Update displayed latitude value
//
void CAirMassDockWidget::on_latEdit_editingFinished()
{
	updateObserverCoordinates();
}


//
// Geographic location (shared data) changed
//
void CAirMassDockWidget::onGeoLocationChanged()
{
	CGeoCoordinates gl = m_sharedData->geoLocation();
	if (gl != m_geoloc) {
		m_geoloc = gl;
		updateObserverCoordinates();
		updateAzAltCoordinates();
		updateValues();
	}
}


//
// Right ascension changed
//
void CAirMassDockWidget::on_raEdit_textChanged(const QString& text)
{
	CRightAscension ra(text.toStdWString());
	if (ra.isValid() && ra != m_equloc.rightAscension()) {
		m_equloc.setRightAscension(ra);
		updateAzAltCoordinates();
		updateValues();
	}
}


//
// Update displayed right ascension
//
void CAirMassDockWidget::on_raEdit_editingFinished()
{
	updateObjectCoordinates();
}


//
// Right ascension changed
//
void CAirMassDockWidget::on_decEdit_textChanged(const QString& text)
{
	CDeclination dec(text.toStdWString());
	if (dec.isValid() && dec != m_equloc.declination()) {
		m_equloc.setDeclination(dec);
		updateAzAltCoordinates();
		updateValues();
	}
}


//
// Update displayed declination
//
void CAirMassDockWidget::on_decEdit_editingFinished()
{
	updateObjectCoordinates();
}


//
// Object coordinates changed
//
void CAirMassDockWidget::onEquLocationChanged()
{
	CEquCoordinates rd = m_sharedData->equLocation();
	if (m_equloc != rd) {
		m_equloc = rd;
		updateObjectCoordinates();
		updateAzAltCoordinates();
		updateValues();
	}
}


//
// Update date and time
//
void CAirMassDockWidget::on_jdEdit_editingFinished()
{
	updateDateTime();
	updateAzAltCoordinates();
	updateValues();
}


//
// Update displayed time
//
void CAirMassDockWidget::updateDateTime()
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
void CAirMassDockWidget::on_resetButton_clicked()
{
	reset();
}


//
// Reset time and location to value stored in the shared data
//
void CAirMassDockWidget::reset()
{
	m_dateTimeLocal = m_sharedData->getSelectedLocalDateTime();
	updateDateTime();
	m_equloc = m_sharedData->equLocation();
	updateObjectCoordinates();
	m_geoloc = m_sharedData->geoLocation();
	updateObserverCoordinates();
	updateAzAltCoordinates();
	updateValues();
}


//
// Update Julian date
//
void CAirMassDockWidget::updateValues()
{
	CJulianDate jd = localToJD(m_dateTimeLocal);
	if (!jd.isNull() && m_equloc.isValid() && m_geoloc.isValid()) {
		double x = jd.AirMass(m_equloc, m_geoloc);
		if (x >= 1)
			amEdit->setText(QString::number(x, 'f', 4));
		else 
			amEdit->setText(tr("N/A"));
	}
	else
		amEdit->setText(tr("Invalid input"));
}


//
// Update displayed location
//
void CAirMassDockWidget::updateObjectCoordinates()
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
// Update az-alt coordinates
//
void CAirMassDockWidget::updateAzAltCoordinates()
{
	CAzAltCoordinates azAlt = CJulianDate(localToJD(m_dateTimeLocal)).RaDeToAzAlt(m_equloc, m_geoloc);

	if (azAlt.azimuth().isValid()) {
		QString text = QString::fromStdWString(azAlt.azimuth().toString());
		text += QStringLiteral(" (%1)").arg(UtilsQt::compassPointName(azAlt.azimuth().toCompassPoint()));
		azEdit->setText(text);
	}
	else
		azEdit->setText(tr("Invalid input"));

	if (azAlt.elevation().isValid()) {
		QString text = QString::fromStdWString(azAlt.elevation().toString());
		if (azAlt.elevation().radians() > 0)
			text += QStringLiteral(" (%1)").arg(tr("above horizon"));
		else
			text += QStringLiteral(" (%1)").arg(tr("below horizon"));
		altEdit->setText(text);
	}
	else
		altEdit->setText(tr("Invalid input"));
}


//
// Update displayed location
//
void CAirMassDockWidget::updateObserverCoordinates()
{
	lonEdit->blockSignals(true);
	if (m_geoloc.longitude().isValid())
		lonEdit->setText(QString::fromStdWString(m_geoloc.longitude().toString()));
	else
		lonEdit->setText(QStringLiteral("***"));
	lonEdit->blockSignals(false);

	latEdit->blockSignals(true);
	if (m_geoloc.latitude().isValid())
		latEdit->setText(QString::fromStdWString(m_geoloc.latitude().toString()));
	else
		latEdit->setText(QStringLiteral("***"));
	latEdit->blockSignals(false);
}




//
// Show Universal time
//
void CAirMassDockWidget::on_utcButton_toggled(bool checked)
{
	if (checked) {
		dateLabel->setText(tr("Universal time"));
		updateDateTime();
	}
}


//
// Show local time
//
void CAirMassDockWidget::on_localButton_toggled(bool checked)
{
	if (checked) {
		dateLabel->setText(tr("Local time"));
		updateDateTime();
	}
}


//
// Show Julian date
//
void CAirMassDockWidget::on_jdButton_toggled(bool checked)
{
	if (checked) {
		dateLabel->setText(tr("Julian date (UTC)"));
		updateDateTime();
	}
}


//
// Local time to UTC time
//
QDateTime CAirMassDockWidget::localToUTC(const QDateTime& local)
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
QDateTime CAirMassDockWidget::utcToLocal(const QDateTime& utc)
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
double CAirMassDockWidget::localToJD(const QDateTime& local)
{
	return UtilsQt::toJulianDate(local);
}


//
// Julian date to local time
//
QDateTime CAirMassDockWidget::jdToLocal(double jd_utc)
{
	return UtilsQt::fromJulianDate(jd_utc);
}
