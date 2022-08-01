cmake_minimum_required (VERSION 3.19)

set(ui_sources
 "main.cpp"
 "main.qrc"
 "CMainWindow.cpp"
 "CMainWindow.h"
 "CNightlyEphemerisTab.h"
 "CNightlyEphemerisTab.cpp"
 "CNightlyEphemerisTab.ui"
 "CStarEphemerisTab.h"
 "CStarEphemerisTab.cpp"
 "CStarEphemerisTab.ui"
 "CSunDockWidget.h" 
 "CSunDockWidget.cpp"
 "CSunDockWidget.ui"
 "CMoonDockWidget.h"
 "CMoonDockWidget.cpp"
 "CMoonDockWidget.ui"
 "CPropertiesDockWidget.h" 
 "CPropertiesDockWidget.cpp"
 "CSetupDialog.h"
 "CSetupDialog.cpp"
 "CSetupDialog.ui"
 "CChartDockWidget.h"
 "CChartDockWidget.cpp"
 "CCheckListDialog.h"
 "CCheckListDialog.cpp"
 "CCheckListDialog.ui"
 "CAboutDialog.h"
 "CAboutDialog.cpp"
 "CAboutDialog.ui"
 "CSharedData.cpp"
 "CSharedData.h"
 "CJulianDateConverterDockWidget.cpp"
 "CJulianDateConverterDockWidget.h"
 "CJulianDateConverterDockWidget.ui"
 "CHeliocentricCorrectionDockWidget.cpp"
 "CHeliocentricCorrectionDockWidget.h"
 "CHeliocentricCorrectionDockWidget.ui"
 "CAirMassDockWidget.cpp"
 "CAirMassDockWidget.h"
 "CAirMassDockWidget.ui"
 "CSunWidget.cpp"
 "CSunWidget.h"
 "CMoonWidget.cpp"
 "CMoonWidget.h"
 "CMainTabWidget.cpp"
 "CMainTabWidget.h"
 "CMainDockWidget.cpp"
 "CMainDockWidget.h"
 "CSkyChartTab.cpp"
 "CSkyChartTab.h"
 "UtilsQt.cpp"
 "UtilsQt.h"
 "CConfigSupport.cpp"
 "CConfigSupport.h"
)

set(uiTargetName "ephemerides")
add_executable(${uiTargetName} WIN32 ${ui_sources})
target_compile_options(${uiTargetName} PRIVATE /W3 /WX)
#target_precompile_headers(${uiTargetName} PRIVATE PrecompiledHeader.h)
target_link_libraries(${uiTargetName} PRIVATE Qt6::Core Qt6::Xml Qt6::Gui Qt6::Widgets skychart)
target_compile_definitions(${uiTargetName} PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)

if(WIN32)
	configure_file(ephemerides.rc.in ephemerides.rc @ONLY)
	configure_file(Resources/ephemerides.ico ephemerides.ico COPYONLY)
	target_sources(${uiTargetName} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/ephemerides.rc)
endif(WIN32)


add_subdirectory(SkyChart)

