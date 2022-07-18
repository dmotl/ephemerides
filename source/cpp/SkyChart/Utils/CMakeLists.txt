cmake_minimum_required (VERSION 3.19)

set(utils_sources
 "SkyChartUtilsQt.cpp"
 "SkyChartUtilsQt.h"
)

add_library(skychartutils STATIC ${utils_sources})
target_include_directories(skychartutils PUBLIC .)
target_compile_options(skychartutils PRIVATE /W3 /WX)

