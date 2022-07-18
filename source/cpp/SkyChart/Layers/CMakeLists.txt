cmake_minimum_required (VERSION 3.19)

set(layers_sources
 "Base/CSkyChartDataset.h"
 "Base/CSkyChartObject.h"
 "Grids/CEquGridDataset.h"
 "Grids/CEquGridDataset.cpp"
 "Stars/CBrightStarCatalogDataset.h"
 "Stars/CBrightStarCatalogDataset.cpp"
 "Stars/CBSC1991.h"
 "Stars/CBSC1991.cpp"
 "ConstBounds/CBound.h" 
 "ConstBounds/CBound.cpp"
 "ConstBounds/CConstBoundsDataset.h" 
 "ConstBounds/CConstBoundsDataset.cpp"
 "DeepSky/CNGC2000.h"
 "DeepSky/CNGC2000.cpp"
 "SolarSystem/CPlanets.h"
 "SolarSystem/CPlanets.cpp"
)

add_library(skychartlayers STATIC ${layers_sources})
target_include_directories(skychartlayers 
	PUBLIC 
		.
		Base 
		SolarSystem 
		DeepSky 
		ConstBounds
		Grids
		Stars
)
target_compile_options(skychartlayers PRIVATE /W3 /WX)
target_link_libraries(skychartlayers PRIVATE constbnd vsop87 elp82 Qt6::Core Qt6::Gui Qt6::Widgets skychartcorelib skychartprojections)
target_compile_definitions(skychartlayers PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
