cmake_minimum_required (VERSION 3.19)

add_executable(tests "CPlanets_test.cpp" "test_main.cpp" "CJulianDate_test.cpp" "Utils_test.cpp" "CDateTime_test.cpp" "CLongitude_test.cpp" "CLatitude_test.cpp")
target_link_libraries(tests GTest::gtest ephem_lib)
gtest_discover_tests(tests)
