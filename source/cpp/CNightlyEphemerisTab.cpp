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
void CNightlyEphemerisTab::loadState(const QDomElement& xml) 
{
	int date = loadXmlValueInt(xml, "Date");
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
	tonightCheck->setChecked(loadXmlValueBool(xml, "DateTonight"));
	tonightCheck->blockSignals(false);

	m_checkedCatalogs = loadXmlValueMap(xml, "Catalogs");

	timeCheck->blockSignals(true);
	timeCheck->setChecked(loadXmlValueBool(xml, "FilterTimeCheck"));
	timeCheck->blockSignals(false);

	timeFromEdit->blockSignals(true);
	timeFromEdit->setValue(loadXmlValueReal(xml, "FilterTimeFrom"));
	timeFromEdit->blockSignals(false);

	timeToEdit->blockSignals(true);
	timeToEdit->setValue(loadXmlValueReal(xml, "FilterTimeTo"));
	timeToEdit->blockSignals(false);

	nightCheck->blockSignals(true);
	nightCheck->setChecked(loadXmlValueReal(xml, "FilterTimeAuto"));
	nightCheck->blockSignals(false);

	altCheck->blockSignals(true); 
	altCheck->setChecked(loadXmlValueBool(xml, "FilterAltCheck"));
	altCheck->blockSignals(false);

	altFromEdit->blockSignals(true);
	altFromEdit->setValue(loadXmlValueInt(xml, "FilterAltFrom"));
	altFromEdit->blockSignals(false);

	altToEdit->blockSignals(true);
	altToEdit->setValue(loadXmlValueInt(xml, "FilterAltTo"));
	altToEdit->blockSignals(false);

	magCheck->blockSignals(true); 
	magCheck->setChecked(loadXmlValueBool(xml, "FilterMagCheck"));
	magCheck->blockSignals(false);

	magFromEdit->blockSignals(true);
	magFromEdit->setValue(loadXmlValueReal(xml, "FilterMagFrom"));
	magFromEdit->blockSignals(false);

	magToEdit->blockSignals(true);
	magToEdit->setValue(loadXmlValueReal(xml, "FilterMagTo"));
	magToEdit->blockSignals(false);

	ptsCheck->blockSignals(true);
	ptsCheck->setChecked(loadXmlValueBool(xml, "FilterPtsCheck"));
	ptsCheck->blockSignals(false);

	ptsFromEdit->blockSignals(true);
	ptsFromEdit->setValue(loadXmlValueInt(xml, "FilterPtsFrom"));
	ptsFromEdit->blockSignals(false);

	ptsToEdit->blockSignals(true);
	ptsToEdit->setValue(loadXmlValueInt(xml, "FilterPtsTo"));
	ptsToEdit->blockSignals(false);

	rascCheck->blockSignals(true);
	rascCheck->setChecked(loadXmlValueBool(xml, "FilterRaCheck"));
	rascCheck->blockSignals(false);

	rascFromEdit->blockSignals(true);
	rascFromEdit->setValue(loadXmlValueReal(xml, "FilterRaFrom"));
	rascFromEdit->blockSignals(false);

	rascToEdit->blockSignals(true);
	rascToEdit->setValue(loadXmlValueReal(xml, "FilterRaTo"));
	rascToEdit->blockSignals(false);

	decCheck->blockSignals(true);
	decCheck->setChecked(loadXmlValueBool(xml, "FilterDecCheck"));
	decCheck->blockSignals(false);

	decFromEdit->blockSignals(true);
	decFromEdit->setValue(loadXmlValueReal(xml, "FilterRaFrom"));
	decFromEdit->blockSignals(false);

	decToEdit->blockSignals(true);
	decToEdit->setValue(loadXmlValueReal(xml, "FilterDecTo"));
	decToEdit->blockSignals(false);

	consCheck->blockSignals(true);
	consCheck->setChecked(loadXmlValueBool(xml, "FilterConsCheck"));
	consCheck->blockSignals(false);

	m_constellationList = loadXmlValueList(xml, "FilterConsList");

	typesCheck->blockSignals(true);
	typesCheck->setChecked(loadXmlValueBool(xml, "FilterTypeCheck"));
	typesCheck->blockSignals(false);

	m_varTypesList = loadXmlValueList(xml, "FilterTypeList");

	aziCheck->blockSignals(true);
	aziCheck->setChecked(loadXmlValueBool(xml, "FilterAzCheck"));
	aziCheck->blockSignals(false);

	aziFromEdit->blockSignals(true);
	aziFromEdit->setValue(loadXmlValueInt(xml, "FilterAzFrom"));
	aziFromEdit->blockSignals(false);

	aziToEdit->blockSignals(true);
	aziToEdit->setValue(loadXmlValueInt(xml, "FilterAzTo"));
	aziToEdit->blockSignals(false);

	omdCheck->blockSignals(true);
	omdCheck->setChecked(loadXmlValueBool(xml, "FilterOMDCheck"));
	omdCheck->blockSignals(false);

	omdFromEdit->blockSignals(true);
	omdFromEdit->setValue(loadXmlValueInt(xml, "FilterOMDFrom"));
	omdFromEdit->blockSignals(false);

	updateCaption();
}


//
// Save settings
//
void CNightlyEphemerisTab::saveState(QDomElement& xml) 
{
	setXmlValue(xml, "Date", dateEdit->date().toJulianDay());
	setXmlValue(xml, "DateTonight", tonightCheck->isChecked());

	setXmlValue(xml, "Catalogs", m_checkedCatalogs);

	setXmlValue(xml, "FilterTimeCheck", timeCheck->isChecked());
	setXmlValue(xml, "FilterTimeFrom", QString::number(timeFromEdit->value(), 'f', 1));
	setXmlValue(xml, "FilterTimeTo", QString::number(timeToEdit->value(), 'f', 1));
	setXmlValue(xml, "FilterTimeAuto", nightCheck->isChecked());

	setXmlValue(xml, "FilterAltCheck", altCheck->isChecked());
	setXmlValue(xml, "FilterAltFrom", altFromEdit->value());
	setXmlValue(xml, "FilterAltTo", altToEdit->value());

	setXmlValue(xml, "FilterMagCheck", magCheck->isChecked());
	setXmlValue(xml, "FilterMagFrom", QString::number(magFromEdit->value(), 'f', 1));
	setXmlValue(xml, "FilterMagTo", QString::number(magToEdit->value(), 'f', 1));

	setXmlValue(xml, "FilterPtsCheck", ptsCheck->isChecked());
	setXmlValue(xml, "FilterPtsFrom", ptsFromEdit->value());
	setXmlValue(xml, "FilterPtsTo", ptsToEdit->value());

	setXmlValue(xml, "FilterRaCheck", rascCheck->isChecked());
	setXmlValue(xml, "FilterRaFrom", QString::number(rascFromEdit->value(), 'f', 1));
	setXmlValue(xml, "FilterRaTo", QString::number(rascToEdit->value(), 'f', 1));

	setXmlValue(xml, "FilterDecCheck", decCheck->isChecked());
	setXmlValue(xml, "FilterDecFrom", decFromEdit->value());
	setXmlValue(xml, "FilterDecTo", decToEdit->value());

	setXmlValue(xml, "FilterConsCheck", consCheck->isChecked());
	setXmlValue(xml, "FilterConsList", m_constellationList);

	setXmlValue(xml, "FilterTypeCheck", typesCheck->isChecked());
	setXmlValue(xml, "FilterTypeList", m_varTypesList);

	setXmlValue(xml, "FilterAzCheck", aziCheck->isChecked());
	setXmlValue(xml, "FilterAzFrom", aziFromEdit->value());
	setXmlValue(xml, "FilterAzTo", aziToEdit->value());

	setXmlValue(xml, "FilterOMDCheck", omdCheck->isChecked());
	setXmlValue(xml, "FilterOMDFrom", omdFromEdit->value());
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
