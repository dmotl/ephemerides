function(add_constlines_cc target)
    set(outfile "${CMAKE_CURRENT_BINARY_DIR}/constlines_tables.h")

	add_custom_command(
	    OUTPUT ${outfile}
		COMMAND "${Python_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/constlines_conv.py" "${CMAKE_SOURCE_DIR}/share/clines/constellationship.fab" "${CMAKE_SOURCE_DIR}/share/hip93/hip2hd" "${outfile}"
		MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/share/clines/constellationship.fab" "${CMAKE_SOURCE_DIR}/share/hip93/hip2hd"
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/constlines_conv.py"
		COMMENT "Converting constellation lines..."
		VERBATIM
	)

	add_custom_target(constlines_tables DEPENDS ${outfile})
	add_dependencies(${target} constlines_tables)
endfunction(add_constlines_cc)
