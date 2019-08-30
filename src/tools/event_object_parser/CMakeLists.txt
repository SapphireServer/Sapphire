cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project(Tool_event_object_parser)

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
add_executable(event_object_parser ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})


if (UNIX)
    target_link_libraries (event_object_parser common xivdat pthread mysql dl z stdc++fs)
else()
    target_link_libraries (event_object_parser common xivdat mysql zlib)
endif()


