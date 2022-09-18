cmake_minimum_required (VERSION 3.19)
set(targetName "json_utils")

add_library(${targetName} STATIC)
target_compile_options(${targetName} PRIVATE /W3 /WX)
target_include_directories(${targetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${targetName} PRIVATE "Utils.cpp" "Utils.h" "CError.h")

target_link_libraries(${targetName} PUBLIC Qt6::Core)

