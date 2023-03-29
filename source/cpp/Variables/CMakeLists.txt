cmake_minimum_required (VERSION 3.19)

set(vstars_sources 
 "CEphemerisBase.h" 
 "CEphemerisBase.cpp" 
 "CVarEphemeris.h" 
 "CVarEphemeris.cpp"
 "CFilter.h" 
 "CFilterStack.h" 
 "CEVNightlyEphemerisSource.cpp"
 "CEVNightlyEphemerisSource.h"
 "CFilterStack.cpp")

add_library(vstars STATIC ${vstars_sources})
target_compile_options(vstars PRIVATE /W3 /WX)
target_link_libraries(vstars PUBLIC catalogscorelib skychartcorelib constellations)
target_include_directories(vstars PUBLIC .)
