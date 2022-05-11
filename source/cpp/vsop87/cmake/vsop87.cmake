function(add_vsop87_cc target verid fileext)
    set(outfile "${CMAKE_CURRENT_BINARY_DIR}/vsop87${verid}.${fileext}.h")
	add_custom_command(
	    OUTPUT ${outfile}
		COMMAND "${Python_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/vsop87_conv.py" "${CMAKE_SOURCE_DIR}/share/vsop87/VSOP87${verid}.${fileext}" "vsop87${verid}.${fileext}.h"
		MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/share/vsop87/VSOP87${verid}.${fileext}"
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/vsop87_conv.py"
		COMMENT "Converting VSOP87${verid}.${fileext}..."
		VERBATIM
	)
	add_custom_target(vsop87${verid}.${fileext} DEPENDS ${outfile})
	add_dependencies(${target} vsop87${verid}.${fileext})
endfunction(add_vsop87_cc)

function(add_vsop87_test_cc target fileext)
	set(outfile "${CMAKE_CURRENT_BINARY_DIR}/vsop87.${fileext}.h")
	add_custom_command(
		OUTPUT ${outfile}
		COMMAND "${Python_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/tests_conv.py" "${CMAKE_SOURCE_DIR}/share/vsop87/VSOP87.${fileext}" "vsop87.${fileext}.h"
		MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/share/vsop87/VSOP87.${fileext}" 
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests_conv.py"
		COMMENT "Converting VSOP87.${fileext}..."
		VERBATIM
	)
	add_custom_target(${target}_tables DEPENDS ${outfile})
	add_library(${target} INTERFACE)
	target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
	add_dependencies(${target} ${target}_tables)
endfunction(add_vsop87_test_cc)
