cmake_minimum_required (VERSION 3.19)

add_library(bsc1991_catalog STATIC "CBSC1991Catalog.h" "CBSC1991Catalog.cpp")
target_compile_options(bsc1991_catalog PRIVATE /W3 /WX)
target_link_libraries(bsc1991_catalog PUBLIC skychartcorelib catalogscorelib)
target_include_directories(bsc1991_catalog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
