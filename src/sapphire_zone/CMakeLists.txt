cmake_minimum_required(VERSION 3.0.2)
cmake_policy(SET CMP0015 NEW)
cmake_policy(SET CMP0014 OLD)

project( sapphire_zone )

file(GLOB SERVER_PUBLIC_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        /*.h
        )

file(GLOB SERVER_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.c*
        )

add_executable( sapphire_zone ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES} )

target_link_libraries( sapphire_zone common )

if (UNIX)
  target_link_libraries( sapphire_zone pthread )
  target_link_libraries( sapphire_zone dl )
endif()

target_include_directories( sapphire_zone PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )
