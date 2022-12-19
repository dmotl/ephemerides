cmake_minimum_required (VERSION 3.19)

set(layers_sources
 "Base/CSkyChartDataset.h"
 "Base/CSkyChartObject.h"
 "Grids/CEquGridDataset.h"
 "Grids/CEquGridDataset.cpp"
 "Stars/CBrightStarCatalogDataset.h"
 "Stars/CBrightStarCatalogDataset.cpp"
 "ConstBounds/CConstBoundsDataset.h" 
 "ConstBounds/CConstBoundsDataset.cpp"
 "ConstLines/CConstLinesDataset.cpp"
 "ConstLines/CConstLinesDataset.h"
)

add_library(skychartlayers STATIC ${layers_sources})
target_include_directories(skychartlayers 
	PUBLIC 
		.
		Base 
		ConstBounds
		ConstLines
		Grids
		Stars
)
target_compile_options(skychartlayers PRIVATE /W3 /WX)
target_link_libraries(skychartlayers PRIVATE constbnd constlines vsop87 elp82 Qt6::Core Qt6::Gui Qt6::Widgets skychartcorelib skychartprojections skycharttables solarsystem)
target_compile_definitions(skychartlayers PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
