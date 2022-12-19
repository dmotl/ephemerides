cmake_minimum_required (VERSION 3.19)

if(ephem_build_tests)
	set(targetName "tests_models")

	add_executable(${targetName} 
	"CPlanets_test.cpp" 
	"tests_main.cpp" 
	"VSOP87_test.cpp" 
	"ELP82_test.cpp"
	)

	target_link_libraries(${targetName} GTest::gtest vsop87 vsop87_tests elp82 skychartcorelib solarsystem)
	target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
	gtest_discover_tests(${targetName})
	
endif(ephem_build_tests)
