cmake_minimum_required (VERSION 3.19)

set(view_sources
 "CSkyChartView.cpp"
 "CSkyChartView.h"
)

add_library(skychartview STATIC ${view_sources})
target_include_directories(skychartview PUBLIC .)
target_compile_options(skychartview PRIVATE /W3 /WX)
target_link_libraries(skychartview PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets skychartcorelib skychartlayers)
target_compile_definitions(skychartview PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
