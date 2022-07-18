cmake_minimum_required (VERSION 3.19)

set(lib_sources
 "CProjection.h"
 "COrthographicProjection.h"
 "CStereographicProjection.h"
)

add_library(skychartprojections INTERFACE ${lib_sources})
target_include_directories(skychartprojections INTERFACE .)
