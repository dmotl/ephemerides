/*!
*  \file      CSkyChartTab.h
*  \author    David Motl
*  \date      2022-03-24
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

#include "ui_CSkyChartTab.h"

class CMainWindow;
class CSkyChartView;

/*!
* \brief The "Nightly ephemeris" tab
*
* The CNightlyEphemerisTab class implements one of the main sections of the
* application. The widgets is used to show ephemeris of variable stars
* for a selected night.
*/
class CSkyChartTab : public CMainTabWidget, private Ui::CSkyChartTab
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param mainWnd main window
	* \param parent parent widget
	*/
	CSkyChartTab(CSharedData* data, CMainWindow* mainWnd, QWidget* parent);

private:
	QToolBar* m_toolBar;

	QToolButton* m_toolsBtn;

	QMenu* m_toolsMenu;

	QSignalMapper* m_toolsActionMapper;

	QAction* m_helpAction, * m_toolsAction;

	// Create toolbar and actions
	void createToolBar(void);

private slots:
	void onToolsAction(int dockWidgetId);

	void on_view_viewChanged(void);

	void on_raSpinBox_valueChanged(double value);
	void on_decSpinBox_valueChanged(double value);

	void on_btnCopyE_clicked(void);
	void on_btnPasteE_clicked(void);
};
