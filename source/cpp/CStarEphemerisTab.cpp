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

// Constructor
CStarEphemerisTab::CStarEphemerisTab(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : CMainTabWidget(sharedData, mainWnd, parent)
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
