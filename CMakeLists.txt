CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(topdownshooter CXX C)

IF(MSVC AND (CMAKE_SIZEOF_VOID_P EQUAL 8))
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
ENDIF()

set(topdownshooter_VERSION_MAJOR 1)
set(topdownshooter_VERSION_MINOR 1)
set(topdownshooter_VERSION_SUBMINOR 2)
SET(topdownshooter_FULL_VERSION "${topdownshooter_FULL_VERSION_VERSION_MAJOR}.${topdownshooter_FULL_VERSION_VERSION_MINOR}.${topdownshooter_FULL_VERSION_VERSION_SUBMINOR} Alpha")

MESSAGE("== Topdown Shooter -- version ${topdownshooter_FULL_VERSION} ==")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# UGDK
add_subdirectory(externals/ugdk EXCLUDE_FROM_ALL)
set(UGDK_EXTERNAL_LIBRARIES libugdk)

add_subdirectory(src) # The game binary.
