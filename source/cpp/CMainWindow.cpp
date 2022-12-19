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
#include "CJulianDateConverterDockWidget.h"
#include "CHeliocentricCorrectionDockWidget.h"
#include "CAirMassDockWidget.h"

#include "CSetupDialog.h"
#include "CAboutDialog.h"
#include "CSkyChartTab.h"
#include "UtilsQt.h"

#define SHOW_NIGHTLY_EPHEMERIS_TAB 1
#define SHOW_STAR_EPHEMERIS_TAB 0
#define SHOW_SKY_CHART_TAB 0

#define SHOW_SUN_DOCK_WIDGET 0
#define SHOW_MOON_DOCK_WIDGET 0
#define SHOW_SKY_CHART_DOCK_WIDGET 0
#define SHOW_PROPERTIES_DOCK_WIDGET 0
#define SHOW_JULIAN_DATE_DOCK_WIDGET 0
#define SHOW_HELIOCENTRIC_CORRECTION_DOWN_WIDGET 0
#define SHOW_AIR_MASS_DOCK_WIDGET 0

//
// Constructor
//
CMainWindow::CMainWindow(CMainApp* app, QWidget* parentWidget) : QMainWindow(parentWidget, Qt::Window), m_app(app)
{
    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setDocumentMode(true);

    setCentralWidget(m_tabWidget);
    setWindowTitle(qApp->applicationName());
    setWindowState(windowState() | Qt::WindowMaximized);
    
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
#if SHOW_SUN_DOCK_WIDGET
    m_sunDockWidget = new CSunDockWidget(m_sharedData, this);
    addDockWidget(Qt::LeftDockWidgetArea, m_sunDockWidget);
#endif

#if SHOW_MOON_DOCK_WIDGET
    m_moonDockWidget = new CMoonDockWidget(m_sharedData, this);
    addDockWidget(Qt::LeftDockWidgetArea, m_moonDockWidget);
#endif

#if SHOW_SKY_CHART_DOCK_WIDGET
    m_chartDockWidget = new CChartDockWidget(m_sharedData, this);
    addDockWidget(Qt::LeftDockWidgetArea, m_chartDockWidget);
#endif

#if SHOW_PROPERTIES_DOCK_WIDGET
    m_propertiesDockWidget = new CPropertiesDockWidget(m_sharedData, this);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesDockWidget);
#endif

#if SHOW_JULIAN_DATE_DOCK_WIDGET
    m_julianDateDockWidget = new CJulianDateConverterDockWidget(m_sharedData, this);
    addDockWidget(Qt::RightDockWidgetArea, m_julianDateDockWidget);
#endif

#if SHOW_HELIOCENTRIC_CORRECTION_DOWN_WIDGET
    m_heliocentricCorrectionDockWidget = new CHeliocentricCorrectionDockWidget(m_sharedData, this);
    addDockWidget(Qt::RightDockWidgetArea, m_heliocentricCorrectionDockWidget);
#endif

#if SHOW_AIR_MASS_DOCK_WIDGET
    m_airMassDockWidget = new CAirMassDockWidget(m_sharedData, this);
    addDockWidget(Qt::RightDockWidgetArea, m_airMassDockWidget);
#endif
}


//
// Create tabs
//
void CMainWindow::createTabs()
{
#if SHOW_NIGHTLY_EPHEMERIS_TAB
    new CNightlyEphemerisTab(m_sharedData, this, this);
#endif

#if SHOW_STAR_EPHEMERIS_TAB
    new CStarEphemerisTab(m_sharedData, this, this);
#endif

#if SHOW_SKY_CHART_TAB 
    new CSkyChartTab(m_sharedData, this, this);
#endif
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
//
void CMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


//
// Register a tab widget
//
QString CMainWindow::registerTabWidget(const char* typeId, CMainTabWidget* wnd)
{
    assert(wnd != nullptr);
   
    int lastSuffix = 0;
    foreach(const CMainTabWidget * tab, m_tabWidgetsByType.values(typeId)) {
        if (tab == wnd)
            return wnd->uniqueId();
        int suffix;
        if (UtilsQt::parseUniqueId(tab->uniqueId(), nullptr, &suffix) && suffix > lastSuffix)
            lastSuffix = suffix;
    }
    QString uniqueId = UtilsQt::createUniqueId(typeId, lastSuffix + 1);
    m_tabWidgets.append(wnd);
    m_tabWidgetsByType.insert(typeId, wnd);
    m_tabWidgetById.insert(uniqueId, wnd);
    m_tabWidget->addTab(wnd, QString::fromLatin1(typeId));
    return uniqueId;
}


//
// Register a dock widget
//
QString CMainWindow::registerDockWidget(const char* typeId, CMainDockWidget* wnd)
{
    assert(wnd != nullptr);

    int lastSuffix = 0;
    foreach(const CMainDockWidget * dock, m_dockWidgetsByType.values(typeId)) {
        if (dock == wnd)
            return wnd->uniqueId();
        int suffix;
        if (UtilsQt::parseUniqueId(dock->uniqueId(), nullptr, &suffix) && suffix > lastSuffix)
            lastSuffix = suffix;
    }
    QString uniqueId = UtilsQt::createUniqueId(typeId, lastSuffix + 1);
    m_dockWidgets.append(wnd);
    m_dockWidgetsByType.insert(typeId, wnd);
    m_dockWidgetById.insert(uniqueId, wnd);
    return uniqueId;
}
