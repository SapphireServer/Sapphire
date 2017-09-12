cmake_policy(SET CMP0014 NEW)
cmake_minimum_required(VERSION 2.6)
project (Sapphire)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
# boost stuff
# set(Boost_DEBUG 1)

if(NOT SAPPHIRE_BOOST_VER)
    set(SAPPHIRE_BOOST_VER 1.60.0)
endif()
set(SAPPHIRE_BOOST_FOLDER_NAME boost_1_60_0)

include( "boost.cmake" )
include( "compiler.cmake" )

FIND_PACKAGE(MySQLConnectorCPP)

message(${MYSQLCONNECTORCPP_INCLUDE_DIR})
message(${MYSQLCONNECTORCPP_LIBRARIES})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/ChaiScript-6.0.0/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/sapphire/datReader/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/MySQLpp/include/")
include_directories("src")

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory("src/servers")
add_subdirectory("src/libraries/sapphire/datReader")
