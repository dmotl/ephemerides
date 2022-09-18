cmake_minimum_required (VERSION 3.19)
set(targetName "json_parser")

bison_target(json_bison_target json.yy ${CMAKE_CURRENT_BINARY_DIR}/json_bison_output.cpp
    COMPILE_FLAGS "-v -Wall -p json_"
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/json_bison_output.h
    VERBOSE REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/json_bison_output.output
)

add_library(${targetName} STATIC)
target_compile_options(${targetName} PRIVATE /W3 /WX)
target_include_directories(${targetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_sources(${targetName} PRIVATE ${BISON_json_bison_target_OUTPUTS})
target_link_libraries(${targetName} PUBLIC json_scanner json_utils json_model)

target_sources(${targetName} PRIVATE
"CDriver.h"
"CDriver.cpp"



"CIntParser.cpp"
"CIntParser.h"
"CParserError.cpp"
"CParserError.h"
"CParser.cpp" 
"CParser.h"
 "CLogger.h")

target_link_libraries(${targetName} PUBLIC Qt6::Core)
