cmake_minimum_required (VERSION 3.19)

set(ui_sources
 "main.cpp"
 "main.qrc"
 "CMainApp.cpp"
 "CMainApp.h"
 "CMainWindow.cpp"
 "CMainWindow.h"
 "Tabs/CNightlyEphemerisTab.h"
 "Tabs/CNightlyEphemerisTab.cpp"
 "Tabs/CNightlyEphemerisTab.ui"
 "Tabs/CStarEphemerisTab.h"
 "Tabs/CStarEphemerisTab.cpp"
 "Tabs/CStarEphemerisTab.ui"
 "DockWidgets/CSunDockWidget.h" 
 "DockWidgets/CSunDockWidget.cpp"
 "DockWidgets/CSunDockWidget.ui"
 "DockWidgets/CMoonDockWidget.h"
 "DockWidgets/CMoonDockWidget.cpp"
 "DockWidgets/CMoonDockWidget.ui"
 "DockWidgets/CPropertiesDockWidget.h" 
 "DockWidgets/CPropertiesDockWidget.cpp"
 "Dialogs/CSetupDialog.h"
 "Dialogs/CSetupDialog.cpp"
 "Dialogs/CSetupDialog.ui"
 "DockWidgets/CChartDockWidget.h"
 "DockWidgets/CChartDockWidget.cpp"
 "Dialogs/CCheckListDialog.h"
 "Dialogs/CCheckListDialog.cpp"
 "Dialogs/CCheckListDialog.ui"
 "Dialogs/CAboutDialog.h"
 "Dialogs/CAboutDialog.cpp"
 "Dialogs/CAboutDialog.ui"
 "DockWidgets/CJulianDateConverterDockWidget.cpp"
 "DockWidgets/CJulianDateConverterDockWidget.h"
 "DockWidgets/CJulianDateConverterDockWidget.ui"
 "DockWidgets/CHeliocentricCorrectionDockWidget.cpp"
 "DockWidgets/CHeliocentricCorrectionDockWidget.h"
 "DockWidgets/CHeliocentricCorrectionDockWidget.ui"
 "DockWidgets/CAirMassDockWidget.cpp"
 "DockWidgets/CAirMassDockWidget.h"
 "DockWidgets/CAirMassDockWidget.ui"
 "Widgets/CSunWidget.cpp"
 "Widgets/CSunWidget.h"
 "Widgets/CMoonWidget.cpp"
 "Widgets/CMoonWidget.h"
 "Tabs/CMainTabWidget.cpp"
 "Tabs/CMainTabWidget.h"
 "DockWidgets/CMainDockWidget.cpp"
 "DockWidgets/CMainDockWidget.h"
 "Tabs/CSkyChartTab.cpp"
 "Tabs/CSkyChartTab.h"
 )

set(uiTargetName "ephemerides")
add_executable(${uiTargetName} WIN32 ${ui_sources})
target_compile_options(${uiTargetName} PRIVATE /W3 /WX)
#target_precompile_headers(${uiTargetName} PRIVATE PrecompiledHeader.h)
target_link_libraries(${uiTargetName} PRIVATE Qt6::Core Qt6::Xml Qt6::Gui Qt6::Widgets skychart catalogs core vstars)
target_compile_definitions(${uiTargetName} PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
target_include_directories(${uiTargetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} Core Dialogs DockWidgets Tabs Widgets)

if(WIN32)
	configure_file(ephemerides.rc.in ephemerides.rc @ONLY)
	configure_file(Resources/ephemerides.ico ephemerides.ico COPYONLY)
	target_sources(${uiTargetName} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/ephemerides.rc)
endif(WIN32)

add_subdirectory(Catalogs)
add_subdirectory(Core)
#add_subdirectory(JSON)
add_subdirectory(Models)
add_subdirectory(SkyChart)
add_subdirectory(Variables)
