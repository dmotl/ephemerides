cmake_minimum_required (VERSION 3.19)
set(targetName "tests_json")

add_executable(${targetName})

target_sources(${targetName} PRIVATE
"main.cpp"
"test_Scanner.cpp"
)

target_compile_options(${targetName} PRIVATE /W3 /WX)
target_include_directories(${targetName} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${targetName} PRIVATE json_scanner GTest::gtest GTest::gmock)
gtest_discover_tests(${targetName} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${targetName} PRIVATE TESTS_DIR_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test_data")
