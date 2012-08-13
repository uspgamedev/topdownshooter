CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(topdownshooter CXX C)
set(topdownshooter_VERSION_MAJOR 1)
set(topdownshooter_VERSION_MINOR 1)
set(topdownshooter_VERSION_SUBMINOR 2)
SET(topdownshooter_FULL_VERSION "${topdownshooter_FULL_VERSION_VERSION_MAJOR}.${topdownshooter_FULL_VERSION_VERSION_MINOR}.${topdownshooter_FULL_VERSION_VERSION_SUBMINOR} Alpha")

MESSAGE("== Topdown Shooter -- version ${topdownshooter_FULL_VERSION} ==")

# TODO: document why we need this.
cmake_policy(SET CMP0015 NEW)

IF (UNIVERSAL)
  # Necessary for a Mac Universal Binary
  SET (CMAKE_OSX_ARCHITECTURES ppc;i386;x86_64)
  SET (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
  SET (MACOSX_DEPLOYMENT_TARGET 10.5)
ENDIF (UNIVERSAL)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND UNIVERSAL)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=10.5")
ENDIF()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# FindUGDK
find_package(UGDK REQUIRED)
include_directories(${UGDK_INCLUDE_DIRS})
set(UGDK_EXTERNAL_LIBRARIES ${UGDK_LIBRARIES})

add_subdirectory(src) # The game binary.
