cmake_minimum_required (VERSION 3.19)

set(vstars_sources 
 "CEphemerisBase.h" 
 "CEphemerisBase.cpp" 
 "CNightlyEphemeris.h" 
 "CNightlyEphemeris.cpp"
 "CVarEphemeris.h" 
 "CVarEphemeris.cpp"
)

add_library(vstars STATIC ${vstars_sources})
target_compile_options(vstars PRIVATE /W3 /WX)
target_link_libraries(vstars PUBLIC catalogscorelib skychartcorelib)
target_include_directories(vstars PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
