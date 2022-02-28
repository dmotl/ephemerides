/*!
*  \file      CJulianDateConverterDockWidget.h
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

#include "ui_CHeliocentricCorrectionDockWidget.h"

#include "CJulianDate.h"

class CSharedData;

/*!
* \brief The "Julian date" tool
*
* The CJulianDateConverterDockWidget class implements a dock widget that converts
* common date and time to Julian date and vice versa.
*
* The time is specified in the shared data and can be modified 
* in the tool.
*/
class CHeliocentricCorrectionDockWidget : public QDockWidget, private Ui::CHeliocentricCorrectionDockWidget
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param data shared data container
	* \param parent parent widget
	*/
	CHeliocentricCorrectionDockWidget(CSharedData* data, QWidget* parent);

protected slots:
	void onDateTimeChanged();
	void onEquLocationChanged();

	void on_dateEdit_dateTimeChanged(const QDateTime& dateTime);
	void on_jdEdit_textChanged(const QString& text);
	void on_raEdit_textChanged(const QString& text);
	void on_decEdit_textChanged(const QString& text);

	void on_jdEdit_editingFinished();
	void on_raEdit_editingFinished();
	void on_decEdit_editingFinished();

	void on_resetButton_clicked();

	void on_utcButton_toggled(bool checked);
	void on_localButton_toggled(bool checked);
	void on_jdButton_toggled(bool checked);

private:
	CSharedData* m_sharedData;
	QDateTime m_dateTimeLocal;
	CEquCoordinates m_equloc;

	void reset();

	void updateDateTime();
	void updateObjectCoordinates();
	void updateValues();

	static double localToJD(const QDateTime& local);
	static QDateTime jdToLocal(double jd_utc);

	static QDateTime localToUTC(const QDateTime& local);
	static QDateTime utcToLocal(const QDateTime& utc);
};
