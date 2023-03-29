set(targetName constellations)

set(constellations_sources
 "CConstellation.h"
 "CConstellation.cpp"
)

add_library(${targetName} STATIC ${constellations_sources})
target_include_directories(${targetName} PUBLIC .)
target_compile_options(${targetName} PRIVATE /W3 /WX)
target_link_libraries(${targetName} PRIVATE skychartcorelib PUBLIC Qt6::Core constellation_names)
target_compile_definitions(${targetName} PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
