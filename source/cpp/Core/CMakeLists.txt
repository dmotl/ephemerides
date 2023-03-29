cmake_minimum_required (VERSION 3.19)

set(core_sources 
 "CCoreApp.cpp" 
 "CCoreApp.h" 
 "CSharedData.cpp"
 "CSharedData.h"
 "CConfigSupport.cpp"
 "CConfigSupport.h"
 "UtilsQt.cpp"
 "UtilsQt.h"
)

add_library(core STATIC ${core_sources})
target_compile_options(core PRIVATE /W3 /WX)
target_link_libraries(core PUBLIC catalogscorelib catalogs_ui skycharttables constbnd)
target_include_directories(core PUBLIC .)
