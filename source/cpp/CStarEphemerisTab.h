/*!
*  \file      CStarEphemerisTab.h
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

#include "CMainTabWidget.h"

#include "ui_CStarEphemerisTab.h"

class CMainWindow;

/*!
* \brief The "Star ephemeris" tab
*
* The CStarEphemerisTab class implements one of the main sections of the
* application. The widgets is used to show ephemeris of a selected
* variable star for a range between two dates.
*/
class CStarEphemerisTab : public CMainTabWidget, private Ui::CStarEphemerisTab
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param mainWnd main window
	* \param parent parent widget
	*/
	CStarEphemerisTab(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent);

	void onTabEnter(CMainTabWidget* previousTab) override;

private:
	QToolBar* m_toolBar;

	QToolButton* m_toolsBtn;

	QMenu* m_toolsMenu;

	QAction* m_updateAction, * m_sortAction, * m_deleteAction, * m_findAction;
	QAction* m_printAction, * m_exportAction, * m_copyAction;
	QAction* m_toolsAction, * m_sunAction, * m_moonAction, * m_chartAction;
	QAction* m_jdConvAction, * m_helCorrAction, * m_airMassAction;
	QAction* m_setupAction, * m_helpAction;

	QSignalMapper* m_toolsActionMapper;

	void createToolBar();

private slots:
	void onToolsAction(int dockWidgetId);
};
