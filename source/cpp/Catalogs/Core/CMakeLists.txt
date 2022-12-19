cmake_minimum_required (VERSION 3.19)

set(core_sources
"CCatalogList.cpp"
"CCatalogList.h"
"CCatalog.h" 
"CCatalog.cpp" 
"CCatalogFile.h" 
"CCatalogFile.cpp" 
"CCatalogObject.h"
)

add_library(catalogscorelib STATIC ${core_sources})
target_compile_options(catalogscorelib PRIVATE /W3 /WX)
target_link_libraries(catalogscorelib PUBLIC skychartcorelib core vsx_catalog bsc1991_catalog)
target_include_directories(catalogscorelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
