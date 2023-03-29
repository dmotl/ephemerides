/*!
*  \file      CMainWindow.h
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

#include "CConfigSupport.h"

#include <QtWidgets>

class CMainApp;
class CSharedData;
class CMainTabWidget;
class CMainDockWidget;

/*!
* \brief Main application window
* 
* The CMainWindow class implements the main application window.
* The window comprises of a tab widget with main sections that
* represents two work modes - nightly ephemeris and star ephemeris.
* 
* The auxilliaty tools are usually dock widgets.
*/
class CMainWindow : public QMainWindow, CConfigSupport
{
    Q_OBJECT

public:
    /*! \brief Constructor */
    explicit CMainWindow(CMainApp* app, QWidget* parentWidget = nullptr);

protected:
    /*! \brief Save settings and close the window */
    void closeEvent(QCloseEvent *event) override;

    /*! \brief Check if we can close the application */
    bool closeQuery(void) { return true; }

    /*! \brief Save settings */
    void writeSettings();

private:
    friend class CMainTabWidget;
    friend class CMainDockWidget;

    // Application's global data
    CMainApp* m_app;

    // Main configuration file
    QJsonDocument m_mainConfig;

    // Data shared with tools and windows
    CSharedData* m_sharedData;

    // Main tab container
    QTabWidget* m_tabWidget;

    // Tab widgets
    QList<CMainTabWidget*> m_tabWidgets;

    // Map of tab widgets (unique id --> pointer)
    QMap<QString, CMainTabWidget*> m_tabWidgetById;

    // Map of tab widgets by type
    QMultiMap<const char*, CMainTabWidget*> m_tabWidgetsByType;

    // List of dock widget
    QList<CMainDockWidget*> m_dockWidgets;

    // Dock widgets
    QMap<QString, CMainDockWidget*> m_dockWidgetById;

    // Dock widgets
    QMultiMap<const char*, CMainDockWidget*> m_dockWidgetsByType;

    // Register a tab widget
    QString registerTabWidget(const char* typeId, CMainTabWidget* wnd);

    // Register a dock widget
    QString registerDockWidget(const char* typeId, CMainDockWidget* wnd);

    // Get list of dock widgets by type
    QList<CMainDockWidget*> dockWidgetsByType(const char* typeId) const { return m_dockWidgetsByType.values(typeId); }

    // Create sections (tabs)
    void createTabs();

    // Create menu actions
    void createActions();

    // Create a status bar
    void createStatusBar();

    // Create tools
    void createDockWindows();

    // Add main tab
    void addMainTab(CMainTabWidget* tab);
};