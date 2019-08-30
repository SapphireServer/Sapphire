cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project(Tool_ExdCommonGen)

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*")

add_executable(exd_common_gen ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

if (UNIX)
    target_link_libraries (exd_common_gen common xivdat pthread mysql dl z stdc++fs)
else()
    target_link_libraries (exd_common_gen common xivdat mysql zlib)
endif()



