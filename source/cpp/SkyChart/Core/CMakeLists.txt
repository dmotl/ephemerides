cmake_minimum_required (VERSION 3.19)

set(lib_sources
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
 "CRightAscension.cpp"
 "CRightAscension.h"
 "CPoint.h"
 "CPointd.h"
 "CVector3.h"
 "CVector3d.h"
 "CMatrix3.h"
 "CMatrix3d.h"
 "CQuaternion.h"
 "CQuaterniond.h"
 "SkyChartUtils.h"
 "SkyChartUtils.cpp"
 "Utils.cpp"
 "Utils.h"
)

add_library(skychartcorelib STATIC ${lib_sources})
target_include_directories(skychartcorelib PUBLIC .)
