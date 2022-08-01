/*!
*  \file      CMoonDockWidget.h
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
#pragma once

#include "CMainDockWidget.h"
#include "CGeoCoordinates.h"

#include "ui_CMoonDockWidget.h"

/*!
* \brief The "Lunar ephemeris" tool
*
* The CMoonDockWidget class implements a dock widget that shows position
* phase of the Moon and the Lunar ephemeris - date of new moon, first 
* quaret, full moon and last quarter. A simple show drawing shows an
* illumated part of the satellite. 
*
* The time and geographic coordinates are specified in the shared data.
*/
class CMoonDockWidget : public CMainDockWidget, private Ui::CMoonDockWidget
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param data shared data container
	* \param parent parent widget
	*/
	CMoonDockWidget(CSharedData* data, CMainWindow* mainWnd, QWidget* parent);

	static constexpr const char* type_id = "moon";

	static constexpr const char* caption = QT_TR_NOOP("Moon");

protected slots:
	void onDateTimeChanged();
	void onGeoLocationChanged();

	void on_dateTimeEdit_dateTimeChanged(const QDateTime& dateTime);
	void on_lonEdit_textChanged(const QString& text);
	void on_latEdit_textChanged(const QString& text);

	void on_lonEdit_editingFinished();
	void on_latEdit_editingFinished();

	void on_resetButton_clicked();
	void on_localTimeButton_toggled(bool checked);
	void on_universalTimeButton_toggled(bool checked);

private:
	QDateTime m_dateTime;
	CGeoCoordinates m_geoloc;

	QSize m_labelSize;

	void reset();
	void updateDateTime();
	void updateGeoLocation();
	void updateValues();

	bool computeMoonRiseSet(QDateTime& rise, QDateTime& set) const;
	bool computeMoonEphemerides(QDateTime& new_moon, QDateTime& first_quarter,
		QDateTime& full_moon, QDateTime& last_quarter);
};
