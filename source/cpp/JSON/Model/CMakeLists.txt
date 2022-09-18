cmake_minimum_required (VERSION 3.19)
set(targetName "json_model")

add_library(${targetName} INTERFACE)
target_link_libraries(${targetName} INTERFACE json_utils)
target_include_directories(${targetName} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${targetName} INTERFACE
	"CArray.h"
	"CLogicValue.h"
	"CObject.h"
	"CNullObject.h"
	"CNumericValue.h"
	"CNode.h"
	"CTextValue.h"
	"CPrimitiveValue.h"
)
