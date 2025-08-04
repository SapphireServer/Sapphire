cmake_policy( SET CMP0014 NEW )
cmake_minimum_required( VERSION 3.10 )
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

file( COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/bin )

######################################
# Dependencies and compiler settings #
######################################
include( "cmake/paths.cmake" )
include( "cmake/compiler.cmake" )

include_directories(
        "deps/glew-1.9.0/include"
        "deps/glfw-3.2.1/include"
        "deps/glm"
        "deps/freetype/include"
        "deps/"
)

##############################
#             Git            #
##############################
include( GetGitRevisionDescription )
get_git_head_revision( GIT_REFSPEC GIT_SHA1 )
git_describe( VERSION --all --dirty=-d )
configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/src/common/Version.cpp.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/common/Version.cpp" @ONLY )

link_directories(
        "${CMAKE_SOURCE_DIR}/deps/glew-1.9.0/lib/Release/x64"
        "${CMAKE_SOURCE_DIR}/deps/glfw-3.2.1/lib-vc2015"
        "${CMAKE_BUILD_PATH}"
        "${CMAKE_BUILD_PATH}/../")


set( FREETYPE_LIBRARY "${CMAKE_SOURCE_DIR}/lib/freetype.lib" )
set( FREETYPE_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/deps/freetype/include" )

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
add_subdirectory( "deps/datReaderPs3" )
add_subdirectory( "deps/mysqlConnector" )
add_subdirectory( "deps/recastnavigation" )
add_subdirectory( "deps/glm" )
add_subdirectory( "deps/freetype" )

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
