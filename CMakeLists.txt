cmake_policy(SET CMP0014 NEW)
cmake_minimum_required(VERSION 2.6)
project (Sapphire)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
# boost stuff
# set(Boost_DEBUG 1)

if(NOT SAPPHIRE_BOOST_VER)
    set(SAPPHIRE_BOOST_VER 1.60.0)
endif()
set(SAPPHIRE_BOOST_FOLDER_NAME boost_1_60_0)
set(SERVER_COMMON_DIR ${CMAKE_SOURCE_DIR}/src/servers/Server_Common)

include( "cmake/boost.cmake" )
include( "cmake/compiler.cmake" )


if(UNIX)
    include_directories("/usr/include/mysql/")
else()
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/MySQL/")
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # 32 bit link
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/MySQL/x86)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/zlib/x86)
    else()
        # 64 bit link
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/MySQL/x64)
        link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/zlib/x64)
    endif()
endif()

FIND_PACKAGE(MySQLConnectorCPP)

if( MYSQLCONNECTORCPP_FOUND )
    message( "Found Mysql C++ Connector at ${MYSQLCONNECTORCPP_INCLUDE_DIR}" )
else()
    message( FATAL_ERROR "Missing Mysql C++ Connector 1.1" )
endif()



include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/ChaiScript-6.0.0/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/sapphire/datReader/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories("${MYSQLCONNECTORCPP_INCLUDE_DIR}")

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

link_directories(${MYSQLCONNECTORCPP_LIBRARIES})
link_directories(${SERVER_COMMON_DIR})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/sapphire/datReader)

add_subdirectory("src/servers")
add_subdirectory("src/libraries/sapphire/datReader")
