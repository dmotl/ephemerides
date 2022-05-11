cmake_minimum_required (VERSION 3.19)

add_library(elp82_tables INTERFACE)
target_include_directories(elp82_tables INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_library(elp82 STATIC elp82.c elp82.h)
target_link_libraries(elp82 PUBLIC elp82_tables)
target_include_directories(elp82 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

