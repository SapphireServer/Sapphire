cmake_minimum_required(VERSION 2.6)
project (Sapphire)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(${PROJECT_SOURCE_DIR}/sapphire_lobby)
add_subdirectory(${PROJECT_SOURCE_DIR}/sapphire_api)
add_subdirectory(${PROJECT_SOURCE_DIR}/sapphire_zone)
add_subdirectory(${PROJECT_SOURCE_DIR}/Scripts)
