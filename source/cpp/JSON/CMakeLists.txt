cmake_minimum_required (VERSION 3.19)
set(targetName "json")

add_subdirectory(Model)
add_subdirectory(Scanner)
add_subdirectory(Parser)
add_subdirectory(Tests)
add_subdirectory(Utils)

add_library(${targetName} STATIC "json.h" "json.cpp") 
target_link_libraries(${targetName} PUBLIC json_scanner json_parser json_model json_utils)
