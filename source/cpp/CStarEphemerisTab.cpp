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

// Constructor
CStarEphemerisTab::CStarEphemerisTab(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : CMainTabWidget(sharedData, mainWnd, parent), m_toolBar(NULL)
{
	setupUi(this);
	setText(tr("Star ephemeris"));
	layout()->setContentsMargins(0, 0, 0, 0);
	toolBox->layout()->setContentsMargins(9, 9, 9, 9);

	m_toolsActionMapper = new QSignalMapper(this);
	connect(m_toolsActionMapper, &QSignalMapper::mappedInt, this, &CStarEphemerisTab::onToolsAction);

	createToolBar();
}

//
// Initialize tools menu
//
void CStarEphemerisTab::onTabEnter(CMainTabWidget* previousTab)
{
	INIT_DOCK_WIDGET_ACTION(m_sunAction);
	INIT_DOCK_WIDGET_ACTION(m_moonAction);
	INIT_DOCK_WIDGET_ACTION(m_chartAction);
	INIT_DOCK_WIDGET_ACTION(m_jdConvAction);
	INIT_DOCK_WIDGET_ACTION(m_helCorrAction);
	INIT_DOCK_WIDGET_ACTION(m_airMassAction);
}

void CStarEphemerisTab::createToolBar()
{
	m_toolBar = new QToolBar(this);
	static_cast<QVBoxLayout*>(mainFrame->layout())->insertWidget(0, m_toolBar);
	m_toolBar->setFloatable(false);
	m_toolBar->setMovable(false);

	m_updateAction = m_toolBar->addAction(tr("Update"));
	m_toolBar->addSeparator();
	m_sortAction = m_toolBar->addAction(tr("Sort"));
	m_deleteAction = m_toolBar->addAction(tr("Delete"));
	m_findAction = m_toolBar->addAction(tr("Find"));
	m_toolBar->addSeparator();
	m_printAction = m_toolBar->addAction(tr("Print"));
	m_exportAction = m_toolBar->addAction(tr("Export"));
	m_copyAction = m_toolBar->addAction(tr("Copy"));
	m_toolBar->addSeparator();
	m_sunAction = m_toolBar->addAction(tr("Sun"));
	m_moonAction = m_toolBar->addAction(tr("Moon"));
	m_chartAction = m_toolBar->addAction(tr("Chart"));
	m_toolBar->addSeparator();

	m_toolsMenu = new QMenu(this);
	CREATE_DOCK_WIDGET_TOOL(m_sunAction, SUN_DOCK_WIDGET, tr("Sun"));
	CREATE_DOCK_WIDGET_TOOL(m_moonAction, MOON_DOCK_WIDGET, tr("Moon"));
	CREATE_DOCK_WIDGET_TOOL(m_chartAction, SKY_CHART_DOCK_WIDGET, tr("Sky chart"));
	m_toolsMenu->addSeparator();
	CREATE_DOCK_WIDGET_TOOL(m_jdConvAction, JD_CONVERTER_DOCK_WIDGET, tr("Julian date converter"));
	CREATE_DOCK_WIDGET_TOOL(m_helCorrAction, HELIOC_CORRECTION_DOCK_WIDGET, tr("Heliocentric correction"));
	CREATE_DOCK_WIDGET_TOOL(m_airMassAction, AIR_MASS_DOCK_WIDGET, tr("Air mass"));
	m_toolsMenu->addSeparator();
	m_setupAction = m_toolsMenu->addAction(tr("Options"));

	m_toolsBtn = new QToolButton(this);
	m_toolsBtn->setText(tr("Tools"));
	m_toolsBtn->setPopupMode(QToolButton::InstantPopup);
	m_toolsBtn->setMenu(m_toolsMenu);
	m_toolsAction = m_toolBar->addWidget(m_toolsBtn);

	m_helpAction = m_toolsMenu->addAction(tr("Help"));
}

void CStarEphemerisTab::onToolsAction(int dockWidgetId)
{
	DOCK_WIDGET_ACTION_TRIGGERED(dockWidgetId);
}