cmake_minimum_required(VERSION 2.6)
project (Sapphire)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# boost stuff
if("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xMSVC")
    set(Boost_COMPILER "-vc140")
endif()

if(NOT SAPPHIRE_BOOST_VER)
    set(SAPPHIRE_BOOST_VER 1.60.0)
endif()
set(SAPPHIRE_BOOST_FOLDER_NAME boost_1_60_0)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
 
add_subdirectory("src/servers")
add_subdirectory("src/libraries/sapphire/datReader")
