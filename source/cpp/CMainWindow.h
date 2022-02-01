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

#include <QtWidgets>

class CSharedData;
class CStarEphemerisTab;
class CNightlyEphemerisTab;
class CSunDockWidget;
class CMoonDockWidget;
class CPropertiesDockWidget;
class CChartDockWidget;

/*!
* \brief Main application window
* 
* The CMainWindow class implements the main application window.
* The window comprises of a tab widget with main sections that
* represents two work modes - nightly ephemeris and star ephemeris.
* 
* The auxilliaty tools are usually dock widgets.
*/

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*! \brief Constructor */
    CMainWindow();

protected:
    /*! \brief Save settings and close the window */
    void closeEvent(QCloseEvent *event) override;

    /*! \brief Check if we can close the application */
    bool closeQuery(void) { return true; }

    /*! \brief Save settings */
    void writeSettings();

private:
    // Main tab container
    QTabWidget* m_tabWidget;

    // The "Nightly epehemeris" section
    CNightlyEphemerisTab* m_dayTabWidget;

    // Tab index for the "Nightly epehemeris" section
    int m_dayTabIndex;

    // The "Star ephemeris" section
    CStarEphemerisTab* m_starTabWidget;

    // Tab index for the "Star ephemeris" section
    int m_starTabIndex;

    // Data shared with tools and windows
    CSharedData* m_sharedData;

    // The "Sun ephemeris" tool
    CSunDockWidget* m_sunDockWidget;

    // The "Lunar ephemeris" tool
    CMoonDockWidget* m_moonDockWidget;

    // The "Properties" tool
    CPropertiesDockWidget* m_propertiesDockWidget;

    // The "SKy chart" tool
    CChartDockWidget* m_chartDockWidget;

    // Create sections (tabs)
    void createTabs();

    // Create menu actions
    void createActions();

    // Create a status bar
    void createStatusBar();

    // Create tools
    void createDockWindows();
};