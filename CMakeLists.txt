cmake_policy( SET CMP0014 NEW )
cmake_minimum_required( VERSION 3.0.2 )
project( Sapphire )

set( CMAKE_MODULE_PATH
       ${CMAKE_MODULE_PATH}
       ${CMAKE_SOURCE_DIR}/cmake )

#####################################
# Copy needed files to build-folder #
#####################################
add_custom_target( copy_runtime_files ALL
                     COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config ${CMAKE_BINARY_DIR}/bin/config
                     COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/sql ${CMAKE_BINARY_DIR}/bin/sql
                     COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/web ${CMAKE_BINARY_DIR}/bin/web
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/sql_import.sh ${CMAKE_BINARY_DIR}/bin/sql_import.sh )

######################################
# Dependencies and compiler settings #
######################################
include( "cmake/paths.cmake" )
#include( "cmake/mysql.cmake" )
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
#           Mysql            #
##############################
find_package( MySQL )

##############################
#        Dependencies        #
##############################
add_subdirectory( "deps/zlib" )
add_subdirectory( "deps/MySQL" )
add_subdirectory( "deps/datReader" )
add_subdirectory( "deps/mysqlConnector" )

##############################
#  Main Sapphire Components  #
##############################
add_subdirectory( "src/common" )
add_subdirectory( "src/api" )
add_subdirectory( "src/lobby" )
add_subdirectory( "src/world" )
add_subdirectory( "src/scripts" )
add_subdirectory( "src/dbm" )

##############################
#           Tools            #
##############################
add_subdirectory( "src/tools" )
