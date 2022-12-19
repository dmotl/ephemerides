cmake_minimum_required (VERSION 3.19)

set(catalogs_sources "Catalogs.cpp")

add_library(catalogs STATIC ${catalogs_sources})
target_compile_options(catalogs PRIVATE /W3 /WX)
target_link_libraries(catalogs PUBLIC catalogscorelib catalogs_ui vsx_catalog bsc1991_catalog)

add_subdirectory(Core)
add_subdirectory(Variables/VSX)
add_subdirectory(Stars/BSC)
add_subdirectory(Ui)
