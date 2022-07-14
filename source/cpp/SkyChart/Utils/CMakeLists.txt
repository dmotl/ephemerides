cmake_minimum_required (VERSION 3.19)

set(utils_sources
 "SkyChartUtilsQt.cpp"
 "SkyChartUtilsQt.h"
)

add_library(skychartutils STATIC ${utils_sources})
target_include_directories(skychartutils PUBLIC .)
target_compile_options(skychartutils PRIVATE /W3 /WX)
target_link_libraries(skychartutils PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets skychartcorelib skychartlayers skychartview)
target_compile_definitions(skychartutils PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
