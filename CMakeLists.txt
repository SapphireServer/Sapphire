cmake_policy( SET CMP0014 NEW )
cmake_minimum_required( VERSION 3.0.2 )
project( Sapphire )

set( CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )
set( EXECUTABLE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

set( CMAKE_MODULE_PATH
       ${CMAKE_MODULE_PATH}
       ${CMAKE_SOURCE_DIR}/cmake )

######################################
# Dependencies and compiler settings #
######################################
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

##############################
#             Mysql          #
##############################
find_package( MySQL )

##########################################################################
add_subdirectory( "deps/zlib" )
add_subdirectory( "deps/MySQL" )
add_subdirectory( "deps/datReader" )
add_subdirectory( "deps/mysqlConnector" )
add_subdirectory( "src/common" )

add_subdirectory( "src/api" )
add_subdirectory( "src/lobby" )
add_subdirectory( "src/world" )
add_subdirectory( "src/dbm" )
add_subdirectory( "src/scripts" )

add_subdirectory( "src/tools/exd_common_gen" )
add_subdirectory( "src/tools/exd_struct_gen" )
add_subdirectory( "src/tools/exd_struct_test" )
add_subdirectory( "src/tools/quest_parser" )
add_subdirectory( "src/tools/discovery_parser" )
add_subdirectory( "src/tools/mob_parse" )
add_subdirectory( "src/tools/pcb_reader" )
add_subdirectory( "src/tools/event_object_parser" )