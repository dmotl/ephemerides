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

#include "ui_CJulianDateConverterDockWidget.h"

#include "CMainDockWidget.h"
#include "CJulianDate.h"
#include "CDateTime.h"

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
class CJulianDateConverterDockWidget : public CMainDockWidget, private Ui::CJulianDateConverterDockWidget
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param data shared data container
	* \param parent parent widget
	*/
	CJulianDateConverterDockWidget(CSharedData* data, CMainWindow* mainWnd, QWidget* parent);

	// Type identifier
	static constexpr const char *type_id = "jdate";

	static constexpr const char* caption = QT_TR_NOOP("Julian date converter");


protected slots:
	void onDateTimeChanged();

	void on_utcEditIn_dateTimeChanged(const QDateTime& dateTime);
	void on_localEditIn_dateTimeChanged(const QDateTime& dateTime);
	void on_jdEditIn_textChanged(const QString& text);

	void on_jdEditIn_editingFinished();

	void on_resetButton_clicked() { reset(); }

	void on_toJDButton_toggled(bool checked);
	void on_fromJDButton_toggled(bool checked);

private:
	QDateTime m_dateTimeLocal;

	void reset();
	void updateUTC(bool in);
	void updateLocal(bool in);
	void updateJD(bool in);

	static double localToJD(const QDateTime& local);
	static QDateTime jdToLocal(double jd_utc);

	static QDateTime localToUTC(const QDateTime& local);
	static QDateTime utcToLocal(const QDateTime& utc);
};
