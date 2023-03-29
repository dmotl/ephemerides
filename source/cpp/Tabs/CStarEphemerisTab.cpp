/*!
*  \file      CStarEphemerisTab.cpp
*  \author    David Motl
*  \date      2022-05-11
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
#include "CStarEphemerisTab.h"

#include "UtilsQt.h"

#include "CSunDockWidget.h"
#include "CMoonDockWidget.h"
#include "CChartDockWidget.h"
#include "CJulianDateConverterDockWidget.h"
#include "CHeliocentricCorrectionDockWidget.h"
#include "CAirMassDockWidget.h"
#include "CVarEphemeris.h"

// Constructor
CStarEphemerisTab::CStarEphemerisTab(CMainApp* app, CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : CMainTabWidget(app, sharedData, mainWnd, parent),
	m_data(nullptr), m_model(nullptr)
{
	registerTabWidget(type_id);

	setupUi(this);

	layout()->setContentsMargins(0, 0, 0, 0);
	toolBox->layout()->setContentsMargins(9, 9, 9, 9);

	m_updateAction = new QAction(this);
	m_updateAction->setText(tr("Update"));

	m_sortAction = new QAction(this);
	m_sortAction->setText(tr("Sort"));

	m_deleteAction = new QAction(this);
	m_deleteAction->setText(tr("Delete"));

	m_findAction = new QAction(this);
	m_findAction->setText(tr("Find"));

	m_printAction = new QAction(this);
	m_printAction->setText(tr("Print"));

	m_exportAction = new QAction(this);
	m_exportAction->setText(tr("Export"));

	m_copyAction = new QAction(this);
	m_copyAction->setText(tr("Copy"));

	createToolBar(mainFrame);
	addCustomToolBarActions();
}

CStarEphemerisTab::~CStarEphemerisTab()
{
	delete m_data;
}

void CStarEphemerisTab::addCustomToolBarActions()
{
	if (m_toolBar) {
		m_toolBar->insertAction(m_toolsAction, m_updateAction);

		m_toolBar->insertSeparator(m_toolsAction);

		m_toolBar->insertAction(m_toolsAction, m_sortAction);
		m_toolBar->insertAction(m_toolsAction, m_deleteAction);
		m_toolBar->insertAction(m_toolsAction, m_findAction);

		m_toolBar->insertSeparator(m_toolsAction);

		m_toolBar->insertAction(m_toolsAction, m_printAction);
		m_toolBar->insertAction(m_toolsAction, m_exportAction);
		m_toolBar->insertAction(m_toolsAction, m_copyAction);

		m_toolBar->insertSeparator(m_toolsAction);

		m_toolBar->insertAction(m_toolsAction, DOCK_WIDGET_ACTION(CSunDockWidget));
		m_toolBar->insertAction(m_toolsAction, DOCK_WIDGET_ACTION(CMoonDockWidget));
		m_toolBar->insertAction(m_toolsAction, DOCK_WIDGET_ACTION(CChartDockWidget));

		m_toolBar->insertSeparator(m_toolsAction);
	}
}


//
// Restore settings
//
void CStarEphemerisTab::loadState(const QJsonObject& obj)
{
	m_catalogName = configGetValueString(obj, "Catalogue");
	m_constellationName = configGetValueString(obj, "Constellation");
	m_variableName = configGetValueString(obj, "Variable");

	int y1 = configGetValueInt(obj, "StartDate_Year");
	int m1 = configGetValueInt(obj, "StartDate_Month");
	int d1 = configGetValueInt(obj, "StartDate_Day");
	int y2 = configGetValueInt(obj, "EndDate_Year");
	int m2 = configGetValueInt(obj, "EndDate_Year");
	int d2 = configGetValueInt(obj, "EndDate_Day");
	if (QDate(y1, m1, d1).isValid() && QDate(y2, m2, d2).isValid() && QDate(y1, m1, d1) <= QDate(y2, m2, d2)) {
		dateFromEdit->blockSignals(true);
		dateFromEdit->setDate(QDate(y1, m1, d1));
		dateFromEdit->blockSignals(false);

		dateToEdit->blockSignals(true);
		dateToEdit->setDate(QDate(y2, m2, d2));
		dateToEdit->blockSignals(false);
	}
	else {
		QDate startDate = QDate::currentDate();

		dateFromEdit->blockSignals(true);
		dateFromEdit->setDate(startDate);
		dateFromEdit->blockSignals(false);

		dateToEdit->blockSignals(true);
		dateToEdit->setDate(startDate.addDays(7 * 13));
		dateToEdit->blockSignals(false);
	}

	timeCheck->blockSignals(true);
	timeCheck->setChecked(configGetValueBool(obj, "FilterTimeCheck"));
	timeCheck->blockSignals(false);

	timeFromEdit->blockSignals(true);
	timeFromEdit->setValue(configGetValueReal(obj, "FilterTimeFrom"));
	timeFromEdit->blockSignals(false);

	timeToEdit->blockSignals(true);
	timeToEdit->setValue(configGetValueReal(obj, "FilterTimeTo"));
	timeToEdit->blockSignals(false);

	nightCheck->blockSignals(true);
	nightCheck->setChecked(configGetValueReal(obj, "FilterTimeAuto"));
	nightCheck->blockSignals(false);

	dowCheck->blockSignals(true);
	dowCheck->setChecked(configGetValueBool(obj, "FilterDOW"));
	dowCheck->blockSignals(false);

	dowMondayCheck->blockSignals(true);
	dowMondayCheck->setChecked(configGetValueBool(obj, "FilterDOWMonday"));
	dowMondayCheck->blockSignals(false);

	dowTuesdayCheck->blockSignals(true);
	dowTuesdayCheck->setChecked(configGetValueBool(obj, "FilterDOWTuesday"));
	dowTuesdayCheck->blockSignals(false);

	dowWednesdayCheck->blockSignals(true);
	dowWednesdayCheck->setChecked(configGetValueBool(obj, "FilterDOWWednesday"));
	dowWednesdayCheck->blockSignals(false);

	dowThursdayCheck->blockSignals(true);
	dowThursdayCheck->setChecked(configGetValueBool(obj, "FilterDOWThursday"));
	dowThursdayCheck->blockSignals(false);

	dowFridayCheck->blockSignals(true);
	dowFridayCheck->setChecked(configGetValueBool(obj, "FilterDOWFriday"));
	dowFridayCheck->blockSignals(false);

	dowSaturdayCheck->blockSignals(true);
	dowSaturdayCheck->setChecked(configGetValueBool(obj, "FilterDOWSaturday"));
	dowSaturdayCheck->blockSignals(false);

	dowSundayCheck->blockSignals(true);
	dowSundayCheck->setChecked(configGetValueBool(obj, "FilterDOWSunday"));
	dowSundayCheck->blockSignals(false);

	altCheck->blockSignals(true);
	altCheck->setChecked(configGetValueBool(obj, "FilterAltCheck"));
	altCheck->blockSignals(false);

	altFromEdit->blockSignals(true);
	altFromEdit->setValue(configGetValueInt(obj, "FilterAltFrom"));
	altFromEdit->blockSignals(false);

	altToEdit->blockSignals(true);
	altToEdit->setValue(configGetValueInt(obj, "FilterAltTo"));
	altToEdit->blockSignals(false);

	aziCheck->blockSignals(true);
	aziCheck->setChecked(configGetValueBool(obj, "FilterAzCheck"));
	aziCheck->blockSignals(false);

	aziFromEdit->blockSignals(true);
	aziFromEdit->setValue(configGetValueInt(obj, "FilterAzFrom"));
	aziFromEdit->blockSignals(false);

	aziToEdit->blockSignals(true);
	aziToEdit->setValue(configGetValueInt(obj, "FilterAzTo"));
	aziToEdit->blockSignals(false);

	omdCheck->blockSignals(true);
	omdCheck->setChecked(configGetValueBool(obj, "FilterOMDCheck"));
	omdCheck->blockSignals(false);

	omdFromEdit->blockSignals(true);
	omdFromEdit->setValue(configGetValueInt(obj, "FilterOMDFrom"));
	omdFromEdit->blockSignals(false);

	updateCaption();
}

//
// Save settings
//
void CStarEphemerisTab::saveState(QJsonObject& obj)
{
	configSetValue(obj, "Catalogue", m_catalogName);
	configSetValue(obj, "Constellation", m_constellationName);
	configSetValue(obj, "Variable", m_variableName);

	QDate dateStart = dateFromEdit->date();
	configSetValue(obj, "StartDate_Year", dateStart.year());
	configSetValue(obj, "StartDate_Month", dateStart.month());
	configSetValue(obj, "StartDate_Day", dateStart.day());

	QDate dateEnd = dateToEdit->date();
	configSetValue(obj, "StartDate_Year", dateEnd.year());
	configSetValue(obj, "StartDate_Month", dateEnd.month());
	configSetValue(obj, "StartDate_Day", dateEnd.day());

	configSetValue(obj, "FilterTimeCheck", timeCheck->isChecked());
	configSetValue(obj, "FilterTimeFrom", QString::number(timeFromEdit->value(), 'f', 1));
	configSetValue(obj, "FilterTimeTo", QString::number(timeToEdit->value(), 'f', 1));
	configSetValue(obj, "FilterTimeAuto", nightCheck->isChecked());

	configSetValue(obj, "FilterAltCheck", altCheck->isChecked());
	configSetValue(obj, "FilterAltFrom", altFromEdit->value());
	configSetValue(obj, "FilterAltTo", altToEdit->value());

	configSetValue(obj, "FilterAzCheck", aziCheck->isChecked());
	configSetValue(obj, "FilterAzFrom", aziFromEdit->value());
	configSetValue(obj, "FilterAzTo", aziToEdit->value());

	configSetValue(obj, "FilterOMDCheck", omdCheck->isChecked());
	configSetValue(obj, "FilterOMDFrom", omdFromEdit->value());
}


void CStarEphemerisTab::updateCaption()
{
	if (!m_variableName.isEmpty())
		setText(m_variableName);
	else
		setText(tr("Variable ephemeris"));
}
