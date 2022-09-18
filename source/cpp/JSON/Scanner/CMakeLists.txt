cmake_minimum_required (VERSION 3.19)
set(targetName "json_scanner")

add_library(${targetName} STATIC)
target_compile_options(${targetName} PRIVATE /W3 /WX)
target_include_directories(${targetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${targetName} PRIVATE

"CLexer.cpp"
"CLexer.h"
"CLexerError.cpp"
"CLexerError.h"
"CScanner.cpp"
"CToken.cpp"











"CScanner.h"
"CToken.h"
)

target_link_libraries(${targetName} PUBLIC json_utils Qt6::Core)

