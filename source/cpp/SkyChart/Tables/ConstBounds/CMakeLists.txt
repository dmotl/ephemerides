cmake_minimum_required (VERSION 3.19)

include(cmake/constbnd.cmake)

add_library(constbnd INTERFACE)
target_include_directories(constbnd INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
add_constbnd_cc(constbnd)
add_constellation_names_cc(constbnd)

