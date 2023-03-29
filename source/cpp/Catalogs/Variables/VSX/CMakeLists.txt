cmake_minimum_required (VERSION 3.19)

add_library(vsx_catalog STATIC "CVSXCatalog.h" "CVSXCatalog.cpp")
target_compile_options(vsx_catalog PRIVATE /W3 /WX)
target_link_libraries(vsx_catalog PUBLIC skychartcorelib catalogscorelib)
target_include_directories(vsx_catalog PUBLIC .)
