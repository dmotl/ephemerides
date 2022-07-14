cmake_minimum_required (VERSION 3.19)

set(lib_sources
 "CSkyObject.h"
 "CNGC2000.cpp"
 "CNGC2000.h"
 "CBSC1991.cpp"
 "CBSC1991.h"
 "CBound.cpp"
 "CBound.h"
 "CJulianDate.cpp"
 "CJulianDate.h"
 "CDateTime.cpp"
 "CDateTime.h"
 "CLatitude.cpp"
 "CLatitude.h"
 "CLongitude.cpp"
 "CLongitude.h"
 "CGeoCoordinates.h"
 "CDeclination.cpp"
 "CDeclination.h"
 "CEquCoordinates.h"
 "CEquCoordinates.cpp"
 "CAzimuth.cpp"
 "CAzimuth.h"
 "CElevation.cpp"
 "CElevation.h"
 "CAzAltCoordinates.h"
 "CPlanets.h" 
 "CPlanets.cpp"
 "CRightAscension.cpp"
 "CRightAscension.h"
 "CVector3.h"
 "CQuaternion.h"
 "SkyChartUtils.h"
 "SkyChartUtils.cpp"
 "Utils.cpp"
 "Utils.h"
)

set(ui_sources
 "CSkyChartView.cpp"
 "CSkyChartView.h"
 "CSkyChartDataset.h"
 "SkyChartUtilsQt.cpp"
 "SkyChartUtilsQt.h"
 "CEquGridDataset.h"
 "CEquGridDataset.cpp"
 "CBrightStarCatalogDataset.h"
 "CBrightStarCatalogDataset.cpp"
 "CConstBoundsDataset.h" "CConstBoundsDataset.cpp")

add_library(skychartcorelib STATIC ${lib_sources})
target_include_directories(skychartcorelib PUBLIC .)
target_link_libraries(skychartcorelib PUBLIC vsop87 elp82 constbnd Qt6::Core Qt6::Gui)

add_library(skychart STATIC ${ui_sources})
target_include_directories(skychart PUBLIC .)
target_compile_options(skychart PRIVATE /W3 /WX)
target_link_libraries(skychart PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets skychartcorelib)
target_compile_definitions(skychart PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
