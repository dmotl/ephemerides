cmake_minimum_required (VERSION 3.19)

include(cmake/bsc91.cmake)

add_library(bsc91 INTERFACE)
target_include_directories(bsc91 INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
add_bsc91_cc(bsc91)
