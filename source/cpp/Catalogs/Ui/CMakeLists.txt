cmake_minimum_required (VERSION 3.19)

set(ui_sources
"CCatalogLoader.cpp"
"CCatalogLoader.h" 
"CCatalogLoaderDialog.cpp"
"CCatalogLoaderDialog.h" 
"CCatalogLoaderThread.cpp" 
"CCatalogLoaderThread.h" 
)

add_library(catalogs_ui STATIC ${ui_sources})
target_compile_options(catalogs_ui PRIVATE /W3 /WX)
target_link_libraries(catalogs_ui PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets skychartcorelib catalogscorelib)
target_compile_definitions(catalogs_ui PRIVATE QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
target_include_directories(catalogs_ui PUBLIC .)
