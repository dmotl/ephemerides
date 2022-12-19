/*!
*  \file      CNightlyEphemeris.cpp
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
#include "CNightlyEphemerisTab.h"

#include "UtilsQt.h"

#include "CSunDockWidget.h"
#include "CMoonDockWidget.h"
#include "CChartDockWidget.h"
#include "CJulianDateConverterDockWidget.h"
#include "CHeliocentricCorrectionDockWidget.h"
#include "CAirMassDockWidget.h"

//
// Constructor
//
CNightlyEphemerisTab::CNightlyEphemerisTab(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : CMainTabWidget(sharedData, mainWnd, parent), 
m_initialized(false)
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


//
// Restore settings
//
void CNightlyEphemerisTab::loadState(const QJsonObject& obj)
{
	int date = configGetValueInt(obj, "Date");
	if (date > 0) {
		dateEdit->blockSignals(true);
		dateEdit->setDate(QDate::fromJulianDay(date));
		dateEdit->blockSignals(false);
	}
	else {
		dateEdit->blockSignals(true);
		dateEdit->setDate(QDate::currentDate());
		dateEdit->blockSignals(false);
	}

	tonightCheck->blockSignals(true);
	tonightCheck->setChecked(configGetValueBool(obj, "DateTonight"));
	tonightCheck->blockSignals(false);

	m_checkedCatalogs = configGetValueMap(obj, "Catalogs");

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

	altCheck->blockSignals(true); 
	altCheck->setChecked(configGetValueBool(obj, "FilterAltCheck"));
	altCheck->blockSignals(false);

	altFromEdit->blockSignals(true);
	altFromEdit->setValue(configGetValueInt(obj, "FilterAltFrom"));
	altFromEdit->blockSignals(false);

	altToEdit->blockSignals(true);
	altToEdit->setValue(configGetValueInt(obj, "FilterAltTo"));
	altToEdit->blockSignals(false);

	magCheck->blockSignals(true); 
	magCheck->setChecked(configGetValueBool(obj, "FilterMagCheck"));
	magCheck->blockSignals(false);

	magFromEdit->blockSignals(true);
	magFromEdit->setValue(configGetValueReal(obj, "FilterMagFrom"));
	magFromEdit->blockSignals(false);

	magToEdit->blockSignals(true);
	magToEdit->setValue(configGetValueReal(obj, "FilterMagTo"));
	magToEdit->blockSignals(false);

	ptsCheck->blockSignals(true);
	ptsCheck->setChecked(configGetValueBool(obj, "FilterPtsCheck"));
	ptsCheck->blockSignals(false);

	ptsFromEdit->blockSignals(true);
	ptsFromEdit->setValue(configGetValueInt(obj, "FilterPtsFrom"));
	ptsFromEdit->blockSignals(false);

	ptsToEdit->blockSignals(true);
	ptsToEdit->setValue(configGetValueInt(obj, "FilterPtsTo"));
	ptsToEdit->blockSignals(false);

	rascCheck->blockSignals(true);
	rascCheck->setChecked(configGetValueBool(obj, "FilterRaCheck"));
	rascCheck->blockSignals(false);

	rascFromEdit->blockSignals(true);
	rascFromEdit->setValue(configGetValueReal(obj, "FilterRaFrom"));
	rascFromEdit->blockSignals(false);

	rascToEdit->blockSignals(true);
	rascToEdit->setValue(configGetValueReal(obj, "FilterRaTo"));
	rascToEdit->blockSignals(false);

	decCheck->blockSignals(true);
	decCheck->setChecked(configGetValueBool(obj, "FilterDecCheck"));
	decCheck->blockSignals(false);

	decFromEdit->blockSignals(true);
	decFromEdit->setValue(configGetValueReal(obj, "FilterRaFrom"));
	decFromEdit->blockSignals(false);

	decToEdit->blockSignals(true);
	decToEdit->setValue(configGetValueReal(obj, "FilterDecTo"));
	decToEdit->blockSignals(false);

	consCheck->blockSignals(true);
	consCheck->setChecked(configGetValueBool(obj, "FilterConsCheck"));
	consCheck->blockSignals(false);

	m_constellationList = configGetValueList(obj, "FilterConsList");

	typesCheck->blockSignals(true);
	typesCheck->setChecked(configGetValueBool(obj, "FilterTypeCheck"));
	typesCheck->blockSignals(false);

	m_varTypesList = configGetValueList(obj, "FilterTypeList");

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
void CNightlyEphemerisTab::saveState(QJsonObject& obj)
{
	configSetValue(obj, "Date", dateEdit->date().toJulianDay());
	configSetValue(obj, "DateTonight", tonightCheck->isChecked());

	configSetValue(obj, "Catalogs", m_checkedCatalogs);

	configSetValue(obj, "FilterTimeCheck", timeCheck->isChecked());
	configSetValue(obj, "FilterTimeFrom", QString::number(timeFromEdit->value(), 'f', 1));
	configSetValue(obj, "FilterTimeTo", QString::number(timeToEdit->value(), 'f', 1));
	configSetValue(obj, "FilterTimeAuto", nightCheck->isChecked());

	configSetValue(obj, "FilterAltCheck", altCheck->isChecked());
	configSetValue(obj, "FilterAltFrom", altFromEdit->value());
	configSetValue(obj, "FilterAltTo", altToEdit->value());

	configSetValue(obj, "FilterMagCheck", magCheck->isChecked());
	configSetValue(obj, "FilterMagFrom", QString::number(magFromEdit->value(), 'f', 1));
	configSetValue(obj, "FilterMagTo", QString::number(magToEdit->value(), 'f', 1));

	configSetValue(obj, "FilterPtsCheck", ptsCheck->isChecked());
	configSetValue(obj, "FilterPtsFrom", ptsFromEdit->value());
	configSetValue(obj, "FilterPtsTo", ptsToEdit->value());

	configSetValue(obj, "FilterRaCheck", rascCheck->isChecked());
	configSetValue(obj, "FilterRaFrom", QString::number(rascFromEdit->value(), 'f', 1));
	configSetValue(obj, "FilterRaTo", QString::number(rascToEdit->value(), 'f', 1));

	configSetValue(obj, "FilterDecCheck", decCheck->isChecked());
	configSetValue(obj, "FilterDecFrom", decFromEdit->value());
	configSetValue(obj, "FilterDecTo", decToEdit->value());

	configSetValue(obj, "FilterConsCheck", consCheck->isChecked());
	configSetValue(obj, "FilterConsList", m_constellationList);

	configSetValue(obj, "FilterTypeCheck", typesCheck->isChecked());
	configSetValue(obj, "FilterTypeList", m_varTypesList);

	configSetValue(obj, "FilterAzCheck", aziCheck->isChecked());
	configSetValue(obj, "FilterAzFrom", aziFromEdit->value());
	configSetValue(obj, "FilterAzTo", aziToEdit->value());

	configSetValue(obj, "FilterOMDCheck", omdCheck->isChecked());
	configSetValue(obj, "FilterOMDFrom", omdFromEdit->value());
}


//
// Create toolbar and actions
//
void CNightlyEphemerisTab::addCustomToolBarActions()
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

void CNightlyEphemerisTab::updateCaption()
{
	QDate date = dateEdit->date();
	setText(date.toString());
}
