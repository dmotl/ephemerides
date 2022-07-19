function(add_bsc91_cc target)
    set(outfile "${CMAKE_CURRENT_BINARY_DIR}/bsc91_tables.h")

	add_custom_command(
	    OUTPUT ${outfile}
		COMMAND "${Python_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/bsc91_conv.py" "${CMAKE_SOURCE_DIR}/share/bsc91/catalog" "${outfile}"
		MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/share/bsc91/catalog"
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/bsc91_conv.py"
		COMMENT "Converting Bright Star Catalog..."
		VERBATIM
	)

	add_custom_target(bsc91_tables DEPENDS ${outfile})
	add_dependencies(${target} bsc91_tables)
endfunction(add_bsc91_cc)
