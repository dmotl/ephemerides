cmake_minimum_required (VERSION 3.19)

include(cmake/vsop87.cmake)

add_library(vsop87_tables INTERFACE)
target_include_directories(vsop87_tables INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(bodies mer ven ear mar jup sat ura nep)
set(tables a c)

foreach(b IN LISTS bodies)
   foreach(t IN LISTS tables)
	   add_vsop87_cc(vsop87_tables ${t} ${b})
   endforeach(t)
endforeach(b)

add_library(vsop87 STATIC vsop87.c vsop87.h)
target_link_libraries(vsop87 PUBLIC vsop87_tables)
target_include_directories(vsop87 PUBLIC .)

add_vsop87_test_cc(vsop87_tests chk)
