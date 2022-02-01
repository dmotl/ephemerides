cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

option(ephem_build_tests "Build the tests." ON)

project(ephemerides
LANGUAGES CXX 
VERSION 2.0.0 
HOMEPAGE_URL https://github.com/dmotl/ephemerides
DESCRIPTION "Ephemerides for variable stars"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(GNUInstallDirs)

# Needed to include config.h
include_directories(${CMAKE_BINARY_DIR})

# Qt5 stuff
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Xml)
set(CMAKE_AUTOGEN_PARALLEL 1)	
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# GUI
# ------------
add_subdirectory(source/cpp)


# TESTS
# -----

if(ephem_build_tests)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)
    add_subdirectory(test)
endif()


# CONFIGURATION FILES
# -------------------

# Needed to include config.h
include_directories(${CMAKE_BINARY_DIR})

configure_file(config.h.in config.h)