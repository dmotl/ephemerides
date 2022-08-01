/*!
*  \file      CAirMassDockWidget.h
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

#include "ui_CAirMassDockWidget.h"

#include "CMainDockWidget.h"
#include "CJulianDate.h"
#include "CDateTime.h"

/*!
* \brief The "Air mass" tool
*
* The CAirMassDockWidget class implements a dock widget that converts
* common date and time to Julian date and vice versa.
*
* The time is specified in the shared data and can be modified 
* in the tool.
*/
class CAirMassDockWidget : public CMainDockWidget, private Ui::CAirMassDockWidget
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param data shared data container
	* \param parent parent widget
	*/
	CAirMassDockWidget(CSharedData* data, CMainWindow* mainWnd, QWidget* parent);

	static constexpr const char* type_id = "airmass";

	static constexpr const char* caption = QT_TR_NOOP("Air mass");

protected slots:
	void onDateTimeChanged();
	void onEquLocationChanged();
	void onGeoLocationChanged();

	void on_dateEdit_dateTimeChanged(const QDateTime& dateTime);
	void on_jdEdit_textChanged(const QString& text);

	void on_raEdit_textChanged(const QString& text);
	void on_decEdit_textChanged(const QString& text);
	void on_lonEdit_textChanged(const QString& text);
	void on_latEdit_textChanged(const QString& text);

	void on_jdEdit_editingFinished();
	void on_lonEdit_editingFinished();
	void on_latEdit_editingFinished();
	void on_raEdit_editingFinished();
	void on_decEdit_editingFinished();

	void on_resetButton_clicked();

	void on_utcButton_toggled(bool checked);
	void on_localButton_toggled(bool checked);
	void on_jdButton_toggled(bool checked);

private:
	QDateTime m_dateTimeLocal;
	CEquCoordinates m_equloc;
	CGeoCoordinates m_geoloc;

	void reset();
	void updateDateTime();
	void updateValues();
	void updateObjectCoordinates();
	void updateAzAltCoordinates();
	void updateObserverCoordinates();

	static double localToJD(const QDateTime& local);
	static QDateTime jdToLocal(double jd_utc);

	static QDateTime localToUTC(const QDateTime& local);
	static QDateTime utcToLocal(const QDateTime& utc);
};
