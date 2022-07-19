add_subdirectory(SolarSystem/vsop87)
add_subdirectory(SolarSystem/elp82)

set(models_sources
 "SolarSystem/CPlanets.h"
 "SolarSystem/CPlanets.cpp"
)

add_library(skychartmodels STATIC ${models_sources})
target_include_directories(skychartmodels 
	PUBLIC 
		.
		SolarSystem 
)
target_compile_options(skychartmodels PRIVATE /W3 /WX)
target_link_libraries(skychartmodels PRIVATE vsop87 elp82 skychartcorelib)
target_compile_definitions(skychartmodels PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
