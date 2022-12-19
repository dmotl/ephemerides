add_subdirectory(ConstBounds)
add_subdirectory(ConstLines)
add_subdirectory(Stars)

set(tables_sources
 "Stars/CBSC1991.h"
 "Stars/CBSC1991.cpp"
 "ConstBounds/CBound.h"
 "ConstBounds/CBound.cpp"
 "ConstLines/CLines.h"
 "ConstLines/CLines.cpp"
 "DeepSky/CNGC2000.h"
 "DeepSky/CNGC2000.cpp"
)

add_library(skycharttables STATIC ${tables_sources})
target_include_directories(skycharttables 
	PUBLIC 
		.
		ConstBounds
		ConstLines
		DeepSky
		Stars
)
target_compile_options(skycharttables PRIVATE /W3 /WX)
target_link_libraries(skycharttables PRIVATE vsop87 elp82 bsc91 skychartcorelib constbnd constlines)

