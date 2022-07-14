cmake_minimum_required (VERSION 3.19)

add_executable(tests 
"CPlanets_test.cpp" 
"test_main.cpp" 
"CJulianDate_test.cpp" 
"Utils_test.cpp" 
"CDateTime_test.cpp" 
"CLongitude_test.cpp" 
"CLatitude_test.cpp" 
"CNGC2000_test.cpp" 
"CBSC1991_test.cpp" 
"VSOP87_test.cpp" 
"ELP82_test.cpp"
"CPoint_test.cpp" 
"CVector3_test.cpp"
 "CTransform_test.cpp")

target_link_libraries(tests GTest::gtest vsop87 vsop87_tests elp82 skychartcorelib )
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
gtest_discover_tests(tests)

configure_file(test_config.h.in test_config.h)
