/*!
*  \file      CMainWindow.cpp
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
#include <QtWidgets>

#include "CMainWindow.h"
#include "CNightlyEphemerisTab.h"
#include "CStarEphemerisTab.h"
#include "CSharedData.h"

#include "CSunDockWidget.h"
#include "CMoonDockWidget.h"
#include "CPropertiesDockWidget.h"
#include "CChartDockWidget.h"

#include "CSetupDialog.h"
#include "CAboutDialog.h"

//
// Constructor
//
CMainWindow::CMainWindow() : m_dayTabWidget(NULL), m_dayTabIndex(-1), m_starTabWidget(NULL), m_starTabIndex(-1)
{
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);

    m_sharedData = new CSharedData(this);

    createTabs();
    createActions();
    createDockWindows();
    createStatusBar();

    setUnifiedTitleAndToolBarOnMac(true);
}


//
// Save settings and close the window
//
void CMainWindow::closeEvent(QCloseEvent *event)
{
    if (closeQuery()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


//
// Save settings
//
void CMainWindow::writeSettings() 
{
    if (m_sharedData)
        m_sharedData->Save();
}


//
// Create tools
//
void CMainWindow::createDockWindows()
{
    m_sunDockWidget = new CSunDockWidget(m_sharedData, this);
    addDockWidget(Qt::RightDockWidgetArea, m_sunDockWidget);

    m_moonDockWidget = new CMoonDockWidget(m_sharedData, this);
    addDockWidget(Qt::RightDockWidgetArea, m_moonDockWidget);

    m_propertiesDockWidget = new CPropertiesDockWidget(this, this);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesDockWidget);

    m_chartDockWidget = new CChartDockWidget(this, this);
    addDockWidget(Qt::RightDockWidgetArea, m_chartDockWidget);
}


//
// Create tabs
//
void CMainWindow::createTabs()
{
    m_dayTabWidget = new CNightlyEphemerisTab(this, m_tabWidget);
    m_dayTabIndex = m_tabWidget->addTab(m_dayTabWidget, m_dayTabWidget->caption());

    m_starTabWidget = new CStarEphemerisTab(this, m_tabWidget);
    m_starTabIndex = m_tabWidget->addTab(m_starTabWidget, m_starTabWidget->caption());
}


//
// Create menu actions
//
void CMainWindow::createActions()
{

    /*QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar* fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction* newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction* openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);
    ...
        QAction* aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));*/

}


//
// Create a status bar
void CMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
