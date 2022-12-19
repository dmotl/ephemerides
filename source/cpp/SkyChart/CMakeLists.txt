cmake_minimum_required (VERSION 3.19)

add_subdirectory(Core)
add_subdirectory(Layers)
add_subdirectory(Projections)
add_subdirectory(Tables)
add_subdirectory(Utils)
add_subdirectory(View)

set(skychart_sources
 "SkyChart.cpp"
)

add_library(skychart STATIC ${skychart_sources})
target_compile_options(skychart PRIVATE /W3 /WX)
target_link_libraries(skychart PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets skychartcorelib skychartlayers solarsystem skycharttables skychartprojections skychartutils skychartview constbnd)
target_compile_definitions(skychart PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)

add_subdirectory(Tests)
