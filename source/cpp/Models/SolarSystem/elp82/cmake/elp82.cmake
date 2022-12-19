function(add_elp82_cc target verid fileext)
    set(outfile "${CMAKE_CURRENT_BINARY_DIR}/elp82_${verid}.h")
	add_custom_command(
	    OUTPUT ${outfile}
		COMMAND "${Python_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/elp82_conv.py" "${CMAKE_SOURCE_DIR}/share/Catalogs/SolarSystem/elp82/ELP${verid}.${fileext}" "elp82_${verid}.h"
		MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/share/Catalogs/SolarSystem/elp82/ELP${verid}.${fileext}"
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/elp82_conv.py"
		COMMENT "Converting ELP${verid}.${fileext}..."
		VERBATIM
	)
	add_custom_target(elp82_${verid} DEPENDS ${outfile})
	add_dependencies(${target} elp82_${verid})
endfunction(add_elp82_cc)
