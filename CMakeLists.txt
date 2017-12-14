cmake_policy(SET CMP0014 NEW)
cmake_minimum_required(VERSION 2.6)
project (Sapphire)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

##########################################################################
# Boost stuff

# set(Boost_DEBUG 1)

if(NOT SAPPHIRE_BOOST_VER)
    set(SAPPHIRE_BOOST_VER 1.60.0)
endif()
set(SAPPHIRE_BOOST_FOLDER_NAME boost_1_60_0)

##########################################################################
# Common and library path
set(SERVER_COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/servers/Server_Common")
set(LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/libraries")

##########################################################################
# Dependencies and compiler settings
include( "cmake/boost.cmake" )
include( "cmake/mysql.cmake" )
include( "cmake/compiler.cmake" )

##############################
#             Git            #
##############################
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(VERSION --tags --dirty=-d)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/servers/Server_Common/Version.cpp.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/servers/Server_Common/Version.cpp" @ONLY)

##########################################################################
# Common include folders
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/sapphire/datReader/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/sapphire/mysqlConnector/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

##########################################################################
# Common lib folders
link_directories(${MYSQLCONNECTORCPP_LIBRARIES})
link_directories(${SERVER_COMMON_DIR})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/sapphire/datReader)

add_subdirectory("src/servers")

add_subdirectory("src/libraries/sapphire/datReader")
add_subdirectory("src/libraries/sapphire/mysqlConnector")

add_subdirectory("src/tools/exd_common_gen")
add_subdirectory("src/tools/exd_struct_gen")
add_subdirectory("src/tools/exd_struct_test")
add_subdirectory("src/tools/quest_parser")
add_subdirectory("src/tools/pcb_reader")

add_subdirectory("scripts/native")
