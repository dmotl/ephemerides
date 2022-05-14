/*!
*  \file      CMoonDockWidget.cpp
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
#include "CMoonDockWidget.h"

#include "CSharedData.h"
#include "CJulianDate.h"
#include "CPlanets.h"
#include "Utils.h"

//
// Constructor
//
CMoonDockWidget::CMoonDockWidget(CSharedData* data, QWidget* parent) : QDockWidget(parent), m_sharedData(data)
{
	setupUi(this);
	setWindowTitle(tr("Moon"));

	localTimeButton->blockSignals(true);
	localTimeButton->setChecked(true);
	localTimeButton->blockSignals(false);

	reset();

	connect(m_sharedData, &CSharedData::dateTimeChanged, this, &CMoonDockWidget::onDateTimeChanged);
	connect(m_sharedData, &CSharedData::geoLocationChanged, this, &CMoonDockWidget::onGeoLocationChanged);
}


//
// Time (shared data) changed
//
void CMoonDockWidget::onDateTimeChanged()
{
	QDateTime dt = m_sharedData->getSelectedLocalDateTime();
	if (m_dateTime != dt) {
		m_dateTime = dt;
		updateDateTime();
		updateValues();
	}
}


//
// Time modified
//
void CMoonDockWidget::on_dateTimeEdit_dateTimeChanged(const QDateTime& dateTime)
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
void CMoonDockWidget::on_lonEdit_textChanged(const QString& text)
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
void CMoonDockWidget::on_lonEdit_editingFinished()
{
	updateGeoLocation();
}


//
// Latitude modified
//
void CMoonDockWidget::on_latEdit_textChanged(const QString& text)
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
void CMoonDockWidget::on_latEdit_editingFinished()
{
	updateGeoLocation();
}


//
// Geographic location (shared data) changed
//
void CMoonDockWidget::onGeoLocationChanged()
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
void CMoonDockWidget::updateDateTime()
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
void CMoonDockWidget::updateGeoLocation()
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
// Compute Moon rise and set
//
bool CMoonDockWidget::computeMoonRiseSet(QDateTime& rise, QDateTime& set) const
{
	static const double eps = HMS_TO_JD(0, 1, 0);

	QDateTime localTime = m_dateTime;
	if (localTime.time().hour() >= 12)
		localTime = localTime.addDays(1);
	CJulianDate jd0(localTime.date().toJulianDay() - 0.5);

	CJulianDate::tRiseSetResult res_1 = CJulianDate::rcOK;
	double jd_rise = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_rise;
		res_1 = CJulianDate(jd_rise).RaDeToRise(CEquCoordinates(Utils::vsop87ToFK5(CPlanets(jd_rise).Moon())), m_geoloc, &jd_rise, 0, CJulianDate::rtNearest);
		if (res_1 != CJulianDate::rcOK || fabs(jd_rise - last_jd) < eps)
			break;
	}

	CJulianDate::tRiseSetResult res_2 = CJulianDate::rcOK;
	double jd_set = jd0.jd_utc();
	for (int i = 0; i < 10; i++) {
		double last_jd = jd_set;
		res_2 = CJulianDate(jd_set).RaDeToSet(CEquCoordinates(Utils::vsop87ToFK5(CPlanets(jd_set).Moon())), m_geoloc, &jd_set, 0, CJulianDate::rtNearest);
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
// Compute times for Lunar phases
//
bool CMoonDockWidget::computeMoonEphemerides(QDateTime& new_moon, QDateTime& first_quarter,
	QDateTime& full_moon, QDateTime& last_quarter)
{
	QDateTime localTime = m_dateTime;
	if (localTime.time().hour() >= 12)
		localTime = localTime.addDays(1);
	CJulianDate jd0(localTime.date().toJulianDay() - 0.5);

	double jd_phase[4] = { 0, 0, 0, 0 }, diff_min = 99;
	int i_min = -1;
	for (int i = 0; i < 4; i++) {
		double jd1 = jd0, jd_current = CJulianDate(jd1).MoonPhase(i == 0, i == 1, i == 2, i == 3), jd_prev;
		jd_phase[i] = jd_current;
		do {
			double diff_curr = fabs(jd_current - jd0);
			if (diff_curr < diff_min) {
				i_min = i;
				diff_min = diff_curr;
				jd_phase[i] = jd_current;
			}
			jd_prev = jd_current;
			jd1 = jd1 + (jd_current < jd0 ? 28 : -28);
			jd_current = CJulianDate(jd1).MoonPhase(i == 0, i == 1, i == 2, i == 3);
		} while ((jd_current < jd0 && jd_prev < jd0) || (jd_current > jd0 && jd_prev > jd0));
	}
	if (i_min < 0)
		return false;

	for (int i = 0; i < 4; i++) {
		if (i != i_min) {
			double jd1 = jd0, jd_current = CJulianDate(jd1).MoonPhase(i == 0, i == 1, i == 2, i == 3), jd_prev;
			do {
				jd_prev = jd_current;
				jd1 = jd1 + (jd_current < jd0 ? 28 : -28);
				jd_current = CJulianDate(jd1).MoonPhase(i == 0, i == 1, i == 2, i == 3);
				if (jd_current >= jd0)
					jd_phase[i] = jd_current;
			} while ((jd_current < jd0 && jd_prev < jd0) || (jd_current > jd0 && jd_prev > jd0));
		}
	}

	CDateTime dt_set = CJulianDate(jd_phase[0]).toDateTime();
	new_moon = QDateTime(QDate(dt_set.year(), dt_set.month(), dt_set.day()), QTime(dt_set.hour(), dt_set.minute(), dt_set.second()), Qt::UTC);
	if (localTimeButton->isChecked())
		new_moon = new_moon.toLocalTime();

	dt_set = CJulianDate(jd_phase[1]).toDateTime();
	first_quarter = QDateTime(QDate(dt_set.year(), dt_set.month(), dt_set.day()), QTime(dt_set.hour(), dt_set.minute(), dt_set.second()), Qt::UTC);
	if (localTimeButton->isChecked())
		first_quarter = first_quarter.toLocalTime();

	dt_set = CJulianDate(jd_phase[2]).toDateTime();
	full_moon = QDateTime(QDate(dt_set.year(), dt_set.month(), dt_set.day()), QTime(dt_set.hour(), dt_set.minute(), dt_set.second()), Qt::UTC);
	if (localTimeButton->isChecked())
		full_moon = full_moon.toLocalTime();

	dt_set = CJulianDate(jd_phase[3]).toDateTime();
	last_quarter = QDateTime(QDate(dt_set.year(), dt_set.month(), dt_set.day()), QTime(dt_set.hour(), dt_set.minute(), dt_set.second()), Qt::UTC);
	if (localTimeButton->isChecked())
		last_quarter = last_quarter.toLocalTime();

	return true;
}


//
// Update displayed values
//
void CMoonDockWidget::updateValues()
{
	if (!m_dateTime.isValid() || !m_geoloc.isValid()) {
		rises->setText(tr("Invalid input"));
		sets->setText(tr("Invalid input"));
	}
	else {
		QDateTime rise, set;
		if (computeMoonRiseSet(rise, set)) {
			rises->setText(rise.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
			sets->setText(set.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
		}
		else {
			rises->setText(QStringLiteral("***"));
			sets->setText(QStringLiteral("***"));
		}
	}

	if (!m_dateTime.isValid()) {
		newMoonDate->setText(tr("Invalid input"));
		firstQDate->setText(tr("Invalid input"));
		fullMoonDate->setText(tr("Invalid input"));
		lastQDate->setText(tr("Invalid input"));
	}
	else {
		QDateTime dtNewMoon, dtFirstQuarter, dtFullMoon, dtThirdQuarter;
		if (computeMoonEphemerides(dtNewMoon, dtFirstQuarter, dtFullMoon, dtThirdQuarter)) {
			newMoonDate->setText(dtNewMoon.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
			firstQDate->setText(dtFirstQuarter.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
			fullMoonDate->setText(dtFullMoon.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
			lastQDate->setText(dtThirdQuarter.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
		}
		else {
			newMoonDate->setText(QStringLiteral("***"));
			firstQDate->setText(QStringLiteral("***"));
			fullMoonDate->setText(QStringLiteral("***"));
			lastQDate->setText(QStringLiteral("***"));
		}
	}

	if (!m_dateTime.isValid()) {
		rasc->setText(tr("Invalid input"));
		decl->setText(tr("Invalid input"));
		phase->setText(tr("Invalid input"));
		illum->setText(tr("Invalid input"));
	}
	else {
		QDateTime utc = m_dateTime.toUTC();
		double jd0 = utc.date().toJulianDay() + static_cast<double>(utc.time().msecsSinceStartOfDay()) / 86400000 - 0.5;
		CEquCoordinates equ(Utils::vsop87ToFK5(CPlanets(jd0).Moon()));
		double ra = equ.rightAscension().hours();
		if (ra < 0)
			ra = 24 + ra;
		rasc->setText(QString::number(ra, 'f', 4));
		double dec = equ.declination().degrees();
		decl->setText(QString::number(dec, 'f', 4));

		static double period = 29.53059;

		double phase_age = fmod(jd0 - 1721088.5 + 0.25 * period, period);

		moonWidget->setPhase(phase_age / period * 2 * M_PI);

		int Phase = phase_age / period * 360;
		int phase_days = qRound(phase_age);
		QString Result = QString(tr("%1 day(s)", "", phase_days)).arg(phase_days);
		if (Phase < 18 || Phase > 360.0 - 18.0) {
			Result += QStringLiteral(" (%1)").arg(tr("new moon"));
		}
		else if (Phase < 90.0 - 12.0) {
			Result += QStringLiteral(" (%1)").arg(tr("waxing crescent"));
		}
		else if (Phase < 90.0 + 12.0) {
			Result += QStringLiteral(" (%1)").arg(tr("first quarter"));
		}
		else if (Phase < 180.0 - 18.0) {
			Result += QStringLiteral(" (%1)").arg(tr("waxing gibbous"));
		}
		else if (Phase < 180.0 + 18.0) {
			Result += QStringLiteral(" (%1)").arg(tr("full moon"));
		}
		else if (Phase < 270.0 - 12.0) {
			Result += QStringLiteral(" (%1)").arg(tr("waning gibbous"));
		}
		else if (Phase < 270.0 + 12.0) {
			Result += QStringLiteral(" (%1)").arg(tr("third quarter"));
		}
		else {
			Result += QStringLiteral(" (%1)").arg(tr("waning crescent"));
		}
		phase->setText(Result);

		double illum_pct = 0.5 * (1.0 - cos(phase_age / period * 2 * M_PI)) * 100.0;
		if (Phase < 180.0)
			Result = QStringLiteral("%1 %").arg(illum_pct, 0, 'f', 0) + QStringLiteral(" (%1)").arg(tr("increasing"));
		else
			Result = QStringLiteral("%1 %").arg(illum_pct, 0, 'f', 0) + QStringLiteral(" (%1)").arg(tr("decreasing"));
		illum->setText(Result);
	}
}


//
// Reset time and location to value stored in the shared data
//
void CMoonDockWidget::on_resetButton_clicked()
{
	reset();
}


//
// Reset time and location to value stored in the shared data
//
void CMoonDockWidget::reset()
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
void CMoonDockWidget::on_localTimeButton_toggled(bool checked)
{
	if (checked)
		updateValues();
}


//
// Set mode to "UTC"
//
void CMoonDockWidget::on_universalTimeButton_toggled(bool checked)
{
	if (checked)
		updateValues();
}
