/*!
*  \file      CSunDockWidget.cpp
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
#include "CSunDockWidget.h"

#include "CSharedData.h"
#include "CJulianDate.h"
#include "CPlanets.h"
#include "Utils.h"


//
// Constructor
//
CSunDockWidget::CSunDockWidget(CSharedData* data, QWidget* parent) : QDockWidget(parent), m_sharedData(data)
{
	setupUi(this);
	setWindowTitle(tr("Sun"));

	localTimeButton->blockSignals(true);
	localTimeButton->setChecked(true);
	localTimeButton->blockSignals(false);

	reset();

	connect(m_sharedData, &CSharedData::dateTimeChanged, this, &CSunDockWidget::onDateTimeChanged);
	connect(m_sharedData, &CSharedData::geoLocationChanged, this, &CSunDockWidget::onGeoLocationChanged);
}


//
// Time (shared data) changed
//
void CSunDockWidget::onDateTimeChanged()
{
	QDateTime dateTime = m_sharedData->getSelectedLocalDateTime();
	if (m_dateTime != dateTime) {
		m_dateTime = dateTime;
		updateDateTime();
		updateValues();
	}
}


//
// Time changed
//
void CSunDockWidget::on_dateTimeEdit_dateTimeChanged(const QDateTime& dateTime)
{
	if (m_dateTime != dateTime) {
		m_dateTime = dateTime;
		updateDateTime();
		updateValues();
	}
}


//
// Longitude modified
//
void CSunDockWidget::on_lonEdit_textChanged(const QString& text)
{
	CLongitude lon(text.toStdWString());
	if (lon.isValid() && lon != m_geoloc.longitude()) {
		m_geoloc.setLongitude(lon);
		updateValues();
	}
}


//
// Update displayed longitude value
//
void CSunDockWidget::on_lonEdit_editingFinished()
{
	updateGeoLocation();
}


//
// Latitude modified
//
void CSunDockWidget::on_latEdit_textChanged(const QString& text)
{
	CLatitude lat(text.toStdWString());
	if (lat.isValid() && lat != m_geoloc.latitude()) {
		m_geoloc.setLatitude(lat);
		updateValues();
	}
}


//
// Update displayed latitude value
//
void CSunDockWidget::on_latEdit_editingFinished()
{
	updateGeoLocation();
}



//
// Geographic location (shared data) changed
//
void CSunDockWidget::onGeoLocationChanged()
{
	CGeoCoordinates gl = m_sharedData->geoLocation();
	if (gl != m_geoloc) {
		m_geoloc = gl;
		updateGeoLocation();
		updateValues();
	}
}


//
// Update displayed time
//
void CSunDockWidget::updateDateTime()
{
	if (m_dateTime.isValid()) {
		dateTimeEdit->blockSignals(true);
		dateTimeEdit->setDateTime(m_dateTime);
		dateTimeEdit->blockSignals(false);
	}
}


//
// Update displayed location
//
void CSunDockWidget::updateGeoLocation()
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
// Compute sunrise and sunset
//
bool CSunDockWidget::computeSunRiseSet(QDateTime& rise, QDateTime& set) const
{
	static const double eps = HMS_TO_JD(0, 1, 0);

	QDateTime localTime = m_dateTime;
	if (localTime.time().hour() >= 12)
		localTime = localTime.addDays(1);
	CJulianDate jd0(localTime.date().toJulianDay() - 0.5);

	CJulianDate::tRiseSetResult res_1 = CJulianDate::rcOK;
	double jd_rise = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_rise, ra, de;
		CPlanets(jd_rise).Sun(&ra, &de);
		res_1 = jd0.RaDeToRise(CEquCoordinates(ra, de), m_geoloc, &jd_rise);
		if (res_1 != CJulianDate::rcOK || fabs(jd_rise - last_jd) < eps)
			break;
	}

	CJulianDate::tRiseSetResult res_2 = CJulianDate::rcOK;
	double jd_set = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_set, ra, de;
		CPlanets(jd_set).Sun(&ra, &de);
		res_2 = jd0.RaDeToSet(CEquCoordinates(ra, de), m_geoloc, &jd_set);
		if (res_2 != CJulianDate::rcOK || fabs(jd_set - last_jd) < eps)
			break;
	}
	if (res_1 == CJulianDate::rcOK && res_2 == CJulianDate::rcOK) {
		CDateTime dt_rise = CJulianDate(jd_rise).toDateTime();
		rise = QDateTime(QDate(dt_rise.year(), dt_rise.month(), dt_rise.day()), QTime(dt_rise.hour(), dt_rise.minute(), dt_rise.second()), Qt::UTC);
		if (localTimeButton->isChecked())
			rise = rise.toLocalTime();
		CDateTime dt_set = CJulianDate(jd_set).toDateTime();
		set = QDateTime(QDate(dt_set.year(), dt_set.month(), dt_set.day()), QTime(dt_set.hour(), dt_set.minute(), dt_set.second()), Qt::UTC);
		if (localTimeButton->isChecked())
			set = set.toLocalTime();
		return true;
	}
	else {
		rise = set = QDateTime();
		return false;
	}
}


//
// Compute twilight start and end
//
bool CSunDockWidget::computeTwilight(QDateTime& start, QDateTime& end) const
{
	static const double eps = HMS_TO_JD(0, 1, 0);
	double twel = -DEG_TO_RAD(m_sharedData->twilightElevation());

	QDateTime localTime = m_dateTime;
	if (localTime.time().hour() >= 12)
		localTime = localTime.addDays(1);
	CJulianDate jd0(localTime.date().toJulianDay() - 0.5);

	CJulianDate::tRiseSetResult res_1 = CJulianDate::rcOK;
	double jd_end = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_end, ra, de;
		CPlanets(jd_end).Sun(&ra, &de);
		res_1 = jd0.RaDeToRise(CEquCoordinates(ra, de), m_geoloc, &jd_end, twel);
		if (res_1 != CJulianDate::rcOK || fabs(jd_end - last_jd) < eps)
			break;
	}
	CJulianDate::tRiseSetResult res_2 = CJulianDate::rcOK;
	double ra, de, jd_start = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_start;
		CPlanets(jd_start).Sun(&ra, &de);
		res_2 = jd0.RaDeToSet(CEquCoordinates(ra, de), m_geoloc, &jd_start, twel);
		if (res_2 != CJulianDate::rcOK || fabs(jd_start - last_jd) < eps)
			break;
	}
	if (res_1 == CJulianDate::rcOK && res_2 == CJulianDate::rcOK) {
		CDateTime dt_end = CJulianDate(jd_end).toDateTime();
		end = QDateTime(QDate(dt_end.year(), dt_end.month(), dt_end.day()), QTime(dt_end.hour(), dt_end.minute(), dt_end.second()), Qt::UTC);
		if (localTimeButton->isChecked())
			end = end.toLocalTime();

		CDateTime dt_start = CJulianDate(jd_start).toDateTime();
		start = QDateTime(QDate(dt_start.year(), dt_start.month(), dt_start.day()), QTime(dt_start.hour(), dt_start.minute(), dt_start.second()), Qt::UTC);
		if (localTimeButton->isChecked())
			start = start.toLocalTime();
		return true;
	}
	else {
		start = end = QDateTime();
		return false;
	}
}


//
// Update displayed values
//
void CSunDockWidget::updateValues()
{
	if (!m_dateTime.isValid() || !m_geoloc.isValid()) {
		QString invalidInputStr = tr("Invalid input");
		sunrise->setText(invalidInputStr);
		sunset->setText(invalidInputStr);
		twilightEnd->setText(invalidInputStr);
		twilightStart->setText(invalidInputStr);
	}
	else {
		QDateTime rise, set;
		if (computeSunRiseSet(rise, set)) {
			sunrise->setText(rise.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
			sunset->setText(set.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
		}
		else {
			sunrise->setText(QStringLiteral("***"));
			sunset->setText(QStringLiteral("***"));
		}
		QDateTime start, end;
		if (computeTwilight(start, end)) {
			twilightStart->setText(start.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
			twilightEnd->setText(end.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
		}
		else {
			twilightStart->setText(QStringLiteral("***"));
			twilightEnd->setText(QStringLiteral("***"));
		}
	}

	if (!m_dateTime.isValid() || !m_geoloc.isValid()) {
		QString invalidInputStr = tr("Invalid input");
		rasc->setText(invalidInputStr);
		decl->setText(invalidInputStr);
	}
	else {
		QDateTime utc = m_dateTime.toUTC();
		double jd0 = utc.date().toJulianDay() + static_cast<double>(utc.time().msecsSinceStartOfDay()) / 86400000 - 0.5;

		double ra, dec;
		CPlanets(jd0).Sun(&ra, &dec);
		ra = ra * 12 / M_PI;
		if (ra < 0)
			ra = 24 + ra;
		rasc->setText(QString::number(ra, 'f', 4));
		dec = RAD_TO_DEG(dec);
		decl->setText(QString::number(dec, 'f', 4));
	}

}


//
// Reset time and location to value stored in the shared data
//
void CSunDockWidget::on_resetButton_clicked()
{
	reset();
}


//
// Reset time and location to value stored in the shared data
//
void CSunDockWidget::reset()
{
	m_dateTime = m_sharedData->getSelectedLocalDateTime();
	updateDateTime();
	m_geoloc = m_sharedData->geoLocation();
	updateGeoLocation();
	updateValues();
}


//
// Set mode to "Local time"
//
void CSunDockWidget::on_localTimeButton_toggled(bool checked)
{
	if (checked)
		updateValues();
}


//
// Set mode to "UTC"
//
void CSunDockWidget::on_universalTimeButton_toggled(bool checked)
{
	if (checked)
		updateValues();
}
