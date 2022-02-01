cmake_minimum_required (VERSION 3.19)

set(lib_sources
 "CPlanets.cpp"
 "CPlanets.h"
 "CJulianDate.cpp"
 "CJulianDate.h"
 "CDateTime.cpp"
 "CDateTime.h"
 "CLatitude.cpp"
 "CLatitude.h"
 "CLongitude.cpp"
 "CLongitude.h"
 "CGeoLocation.h"
 "Utils.cpp"
 "Utils.h"
)

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
)

set(libTargetName "ephem_lib")
add_library(${libTargetName} ${lib_sources})
target_compile_options(${libTargetName} PRIVATE /W3 /WX)
target_include_directories(${libTargetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(uiTargetName "ephemerides")
add_executable(${uiTargetName} WIN32 ${ui_sources})
target_compile_options(${uiTargetName} PRIVATE /W3 /WX)
#target_precompile_headers(${uiTargetName} PRIVATE PrecompiledHeader.h)
target_link_libraries(${uiTargetName} PRIVATE Qt6::Core Qt6::Xml Qt6::Gui Qt6::Widgets ${libTargetName})
target_compile_definitions(${uiTargetName} PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
