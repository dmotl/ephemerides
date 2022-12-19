add_subdirectory(vsop87)
add_subdirectory(elp82)

set(solarsystem_sources
 "CPlanets.h"
 "CPlanets.cpp"
)

add_library(solarsystem STATIC ${solarsystem_sources})
target_include_directories(solarsystem PUBLIC .)
target_compile_options(solarsystem PRIVATE /W3 /WX)
target_link_libraries(solarsystem PRIVATE vsop87 elp82 skychartcorelib)
