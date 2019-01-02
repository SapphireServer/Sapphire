cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project(Tool_discovery_parser)

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_BINARY_DIR}/bin/tools")

file(GLOB SERVER_PUBLIC_INCLUDE_FILES 
  "${CMAKE_CURRENT_SOURCE_DIR}/*"
  "${CMAKE_CURRENT_SOURCE_DIR}/BMP-DDS_Converter/*"
)
file(GLOB SERVER_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}*.c*"
  "${CMAKE_CURRENT_SOURCE_DIR}/BMP-DDS_Converter/*.c*"
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
add_executable(discovery_parser ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

#set_target_properties(discovery_parser PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
#    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
#    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
#    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
#)

if (UNIX)
    target_link_libraries (discovery_parser common xivdat pthread mysqlclient dl z stdc++fs)
else()
    target_link_libraries (discovery_parser common xivdat mysql zlib)
endif()



