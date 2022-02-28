/*!
*  \file      CSunDockWidget.h
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

#include <QtWidgets>

#include "CGeoCoordinates.h"

#include "ui_CSunDockWidget.h"

class CSharedData;

/*!
* \brief The "Solar ephemeris" tool
*
* The CSunDockWidget class implements a dock widget that shows position
* of the Sun, time of sunrise and sunset and times of twilight start
* and twilight end.
*
* The time and geographic coordinates are specified in the shared data.
*/
class CSunDockWidget : public QDockWidget, private Ui::CSunDockWidget
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param data shared data container
	* \param parent parent widget
	*/
	CSunDockWidget(CSharedData* data, QWidget* parent);

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
	// Shared data
	CSharedData* m_sharedData;

	// Date 
	QDateTime m_dateTime;

	// Geographic coordinates
	CGeoCoordinates m_geoloc;

	// Reset time and position to values in shared data
	void reset();

	// Update shown date and time
	void updateDateTime();

	// Update displated localtion
	void updateGeoLocation();

	// Update computed values
	void updateValues();

	// Compute times of sunrise and sunset
	bool computeSunRiseSet(QDateTime& rise, QDateTime& set) const;
	
	// Compute times of twilight start and end
	bool computeTwilight(QDateTime& start, QDateTime& end) const;
};
