cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project(Tool_pcb_reader2)

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.c*
        nav/*.c*
        nav/ext/*.c*)

add_executable(pcb_reader2 ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

if (UNIX)
    target_link_libraries( pcb_reader2 common xivdat pthread mysql dl z stdc++fs Recast Detour DetourTileCache )
else()
    target_link_libraries( pcb_reader2 common xivdat mysql zlib Recast Detour DetourTileCache )
endif()

target_include_directories( pcb_reader2
        PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/" )

