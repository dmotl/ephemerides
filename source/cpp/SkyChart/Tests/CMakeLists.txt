cmake_minimum_required (VERSION 3.19)

if(ephem_build_tests)
	set(targetName "tests_skychart")

	add_executable(${targetName} 
	"tests_main.cpp" 
	"CJulianDate_test.cpp" 
	"Utils_tests.cpp" 
	"CDateTime_test.cpp" 
	"CLongitude_test.cpp" 
	"CLatitude_test.cpp" 
	"CNGC2000_test.cpp" 
	"CBSC1991_test.cpp" 
	"CPoint_test.cpp" 
	"CVector3_test.cpp"
	"CTransform_test.cpp")

	target_link_libraries(${targetName} GTest::gtest vsop87 vsop87_tests elp82 skychartcorelib solarsystem skycharttables)
	target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
	gtest_discover_tests(${targetName})

	configure_file(tests_config.h.in tests_config.h)

endif(ephem_build_tests)
