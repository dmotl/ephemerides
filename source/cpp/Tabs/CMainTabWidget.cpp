/*!
*  \file      CMainTabWidget.cpp
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
#include "CMainTabWidget.h"

#include "CMainWindow.h"
#include "CMainDockWidget.h"

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
CMainTabWidget::CMainTabWidget(CMainApp* app, CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : QWidget(parent), 
	m_app(app), m_mainWnd(mainWnd), m_sharedData(sharedData), m_toolsAction(nullptr), m_setupAction(nullptr), m_helpAction(nullptr),
	m_toolBar(nullptr), m_toolsMenu(nullptr), m_toolsBtn(nullptr)
{
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	m_toolsActionMapper = new QSignalMapper(this);
	connect(m_toolsActionMapper, &QSignalMapper::mappedString, this, &CMainTabWidget::onToolsAction);

	m_helpAction = new QAction(this);
	m_helpAction->setText(tr("Help"));

	m_setupAction = new QAction(this);
	m_setupAction->setText(tr("Options"));

	CREATE_DOCK_WIDGET_TOOL(CSunDockWidget);
	CREATE_DOCK_WIDGET_TOOL(CMoonDockWidget);
	CREATE_DOCK_WIDGET_TOOL(CChartDockWidget);
	CREATE_DOCK_WIDGET_TOOL(CJulianDateConverterDockWidget);
	CREATE_DOCK_WIDGET_TOOL(CHeliocentricCorrectionDockWidget);
	CREATE_DOCK_WIDGET_TOOL(CAirMassDockWidget);
}

// Create popup menu for the "Tools" button
void CMainTabWidget::createToolsMenu(void)
{
	if (!m_toolsMenu) {
		m_toolsMenu = new QMenu(this);
		ADD_DOCK_WIDGET_ACTION(CSunDockWidget);
		ADD_DOCK_WIDGET_ACTION(CMoonDockWidget);
		ADD_DOCK_WIDGET_ACTION(CChartDockWidget);
		m_toolsMenu->addSeparator();
		ADD_DOCK_WIDGET_ACTION(CJulianDateConverterDockWidget);
		ADD_DOCK_WIDGET_ACTION(CHeliocentricCorrectionDockWidget);
		ADD_DOCK_WIDGET_ACTION(CAirMassDockWidget);
		m_toolsMenu->addSeparator();
		m_toolsMenu->addAction(m_setupAction);
		m_toolsMenu->addSeparator();
		m_toolsMenu->addAction(m_helpAction);
	}
}

void CMainTabWidget::createToolBar(QWidget* mainFrame)
{
	createToolsMenu();

	if (!m_toolsBtn) {
		m_toolsBtn = new QToolButton(this);
		m_toolsBtn->setText(tr("Tools"));
		m_toolsBtn->setPopupMode(QToolButton::InstantPopup);
		if (m_toolsMenu)
			m_toolsBtn->setMenu(m_toolsMenu);
	}

	if (!m_toolBar) {
		m_toolBar = new QToolBar(this);
		static_cast<QVBoxLayout*>(mainFrame->layout())->insertWidget(0, m_toolBar);
		m_toolBar->setFloatable(false);
		m_toolBar->setMovable(false);
		if (m_toolsBtn)
			m_toolsAction = m_toolBar->addWidget(m_toolsBtn);
	}
}


//
// Register a tab widget
//
void CMainTabWidget::registerTabWidget(const char* typeId)
{
	assert(typeId != nullptr && m_mainWnd != nullptr);
	m_uniqueId = m_mainWnd->registerTabWidget(typeId, this);
}


//
// Set tab caption
//
void CMainTabWidget::setText(const QString& text) 
{ 
	if (m_text != text) {
		m_text = text;
		emit captionChanged();
	}
}


//
// Get pointer to a dock widget
//
CMainDockWidget* CMainTabWidget::dockWidget(const char* typeId) const
{
	assert(m_mainWnd != NULL);

	QList<CMainDockWidget*> widgets = m_mainWnd->dockWidgetsByType(typeId);
	if (!widgets.isEmpty())
		return widgets.first();
	return nullptr;
}

CMainDockWidget* CMainTabWidget::dockWidget(const QString& typeId) const
{
	return dockWidget(typeId.toLatin1().constData());
}

void CMainTabWidget::onToolsAction(const QString& dockTypeId)
{
	CMainDockWidget* dw = dockWidget(dockTypeId);
	if (dw) {
		if (dw->isVisible()) {
			if (dw->isFloating()) {
				dw->activateWindow();
				dw->raise();
			}
		}
		else {
			dw->showNormal();
		}
		QAction* action_var = m_toolsActionList.value(dockTypeId);
		if (action_var)
			action_var->setChecked(dw->isVisible());
	}
}


//
// Initialize tools menu
//
void CMainTabWidget::onTabEnter(CMainTabWidget* previousTab)
{
	foreach(const QString& dockTypeId, m_toolsActionList.keys()) {
		QAction* action_var = m_toolsActionList.value(dockTypeId);
		if (action_var) {
			CMainDockWidget* dw = dockWidget(dockTypeId);
			if (dw) {
				action_var->setEnabled(true);
				action_var->setChecked(dw->isVisible());
			}
			else {
				action_var->setEnabled(false);
				action_var->setChecked(false);
			}
		}
	}
}
