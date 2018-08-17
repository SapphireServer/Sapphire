cmake_policy(SET CMP0014 NEW)
cmake_minimum_required(VERSION 3.0.2)
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

if( NOT SAPPHIRE_BOOST_VER )
    set( SAPPHIRE_BOOST_VER 1.63.0 )
endif()
set( SAPPHIRE_BOOST_FOLDER_NAME boost_1_63_0 )

##########################################################################
# Common and library path
set( LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/libraries" )

##########################################################################
# Dependencies and compiler settings
include( "cmake/boost.cmake" )
include( "cmake/mysql.cmake" )
include( "cmake/compiler.cmake" )
include( "cmake/cotire.cmake" )
##############################
#             Git            #
##############################
include( GetGitRevisionDescription )
get_git_head_revision( GIT_REFSPEC GIT_SHA1 )
git_describe( VERSION --all --dirty=-d )
configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/src/common/Version.cpp.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/common/Version.cpp" @ONLY )

##########################################################################
add_subdirectory( "src/libraries/sapphire/datReader" )
add_subdirectory( "src/libraries/sapphire/mysqlConnector" )
add_subdirectory( "src/common" )

add_subdirectory( "src/servers" )

add_subdirectory( "src/tools/exd_common_gen" )
add_subdirectory( "src/tools/exd_struct_gen" )
add_subdirectory( "src/tools/exd_struct_test" )
add_subdirectory( "src/tools/quest_parser" )
add_subdirectory( "src/tools/discovery_parser" )
#add_subdirectory("src/tools/pcb_reader")
#add_subdirectory("src/tools/event_object_parser")
