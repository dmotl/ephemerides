cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

option(ephem_build_tests "Build the tests." ON)

project(ephemerides
LANGUAGES C CXX 
VERSION 2.0.0 
HOMEPAGE_URL https://github.com/dmotl/ephemerides
DESCRIPTION "Ephemerides for variable stars"
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if(MSVC)
    set(gtest_force_shared_crt ON)
    add_compile_options (/permissive-)
    add_compile_definitions(_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
endif(MSVC)

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

if (MSVC)
    set(VSINSTALLDIR $ENV{VSINSTALLDIR} CACHE INTERNAL "")
    set(VCINSTALLDIR $ENV{VCINSTALLDIR} CACHE INTERNAL "")
endif(MSVC)

include(GNUInstallDirs)

# Needed to include config.h
include_directories(${CMAKE_BINARY_DIR})

# Bison
find_package(BISON 3 REQUIRED)

# Qt5 stuff
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Xml)
set(CMAKE_AUTOGEN_PARALLEL 1)	
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Needed python
find_package(Python)


# TESTS
# -----

if(ephem_build_tests)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)
endif()


# CONFIGURATION FILES
# -------------------

configure_file(${PROJECT_SOURCE_DIR}/cmake/config.h.in config.h)


# BUILD
# -----
add_subdirectory(source/cpp)


# VERSION INFO
# ------------

file(WRITE ${CMAKE_BINARY_DIR}/VERSION ${CMAKE_PROJECT_VERSION})
install(FILES ${CMAKE_BINARY_DIR}/VERSION DESTINATION "${CMAKE_INSTALL_DATADIR}")


# LICENCES
# --------

#install(FILES COPYING DESTINATION "${CMAKE_INSTALL_DATADIR}")

# PACKAGING
# ---------

#configure_file(${PROJECT_SOURCE_DIR}/cmake/NSISConfig.nsh.in NSISConfig.nsh @ONLY)

set(CPACK_PACKAGE_VENDOR "David Motl")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-x64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/source/cpp/Resources/Ephem.ico")
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
#set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README")
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_MONOLITHIC_INSTALL ON)
set(CPACK_STRIP_FILES ON)

set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-source")
set(CPACK_SOURCE_IGNORE_FILES "/.git/" "/.vs/" "/out/")

if(WIN32)
  set(CPACK_GENERATOR "NSIS")
  set(CPACK_SOURCE_GENERATOR "ZIP")
endif(WIN32)

include(CPack)
