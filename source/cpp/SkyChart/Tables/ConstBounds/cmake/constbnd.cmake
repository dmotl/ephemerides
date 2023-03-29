function(add_constbnd_cc target)
    set(outfile "${CMAKE_CURRENT_BINARY_DIR}/constbnd_tables.h")

	add_custom_command(
	    OUTPUT ${outfile}
		COMMAND "${Python_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/constbnd_conv.py" "${CMAKE_SOURCE_DIR}/share/Catalogs/Constellations/cbound89/constbnd.dat" "${CMAKE_SOURCE_DIR}/share/Catalogs/Constellations/constellation_names.dat" "${outfile}"
		MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/share/Catalogs/Constellations/cbound89/constbnd.dat"
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/constbnd_conv.py" "${CMAKE_SOURCE_DIR}/share/Catalogs/Constellations/constellation_names.dat"
		COMMENT "Converting constellation boundaries..."
		VERBATIM
	)

	add_custom_target(constbnd_tables DEPENDS ${outfile})
	add_dependencies(${target} constbnd_tables)
endfunction(add_constbnd_cc)

function(add_constellation_names_cc target)
    set(outfile_h "${CMAKE_CURRENT_BINARY_DIR}/constellation_names.h")
	set(outfile_c "${CMAKE_CURRENT_BINARY_DIR}/constellation_names.c")

	add_custom_command(
	    OUTPUT ${outfile_h} ${outfile_c}
		COMMAND "${Python_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/constellation_names.py" "${CMAKE_SOURCE_DIR}/share/Catalogs/Constellations/constellation_names.dat" "${outfile_h}"
		MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/share/Catalogs/Constellations/constellation_names.dat"
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/constellation_names.py" "${CMAKE_SOURCE_DIR}/share/Catalogs/Constellations/constellation_names.dat"
		COMMENT "Converting constellation names..."
		VERBATIM
	)

	add_library(constellation_names OBJECT ${outfile_h} ${outfile_c})
	target_include_directories(constellation_names PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
	add_dependencies(${target} constellation_names)
endfunction(add_constellation_names_cc)
