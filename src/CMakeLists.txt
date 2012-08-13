CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include (src_list.cmake)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
if (UNIX OR MINGW)
    # se for o g++ para *nix ou o MinGW para Windows:
    add_definitions(-Wall -ansi -U_FORTIFY_SOURCE -msse2 -std=c++0x)
elseif (MSVC) 
    add_definitions(/D_CRT_SECURE_NO_WARNINGS /W4 /wd4100 /wd4127 /wd4201 /wd4211 /wd4250 /wd4706 /arch:SSE2 /fp:fast /MP)
endif ()

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )

add_executable(topdownshooter ${GAME_SRCS} ${GENERATED_SRC})
target_link_libraries(topdownshooter ${UGDK_EXTERNAL_LIBRARIES})
