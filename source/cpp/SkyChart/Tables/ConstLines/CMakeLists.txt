cmake_minimum_required (VERSION 3.19)

include(cmake/constlines.cmake)

add_library(constlines INTERFACE)
target_include_directories(constlines INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
add_constlines_cc(constlines)


