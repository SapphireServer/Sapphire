# Required for: https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html
cmake_policy( SET CMP0091 NEW )

# CMake 3.22 ships with Ubuntu 22.04 LTS
# See: https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-1.html
cmake_minimum_required( VERSION 3.22 )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Prevent common user error
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-tree builds are not supported. Run CMake from a separate directory: cmake -B build")
endif()

# Enable folder support
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

option( SAPPHIRE_BUILD_TOOLKIT "Build the Sapphire Toolkit" ON )

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
if( NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/FastLZ/fastlz.c" )
  find_package( Git QUIET )
  if( GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git" )
    message( STATUS "FastLZ not found. Initializing deps/FastLZ submodule..." )
    execute_process(
      COMMAND "${GIT_EXECUTABLE}" submodule update --init --recursive -- deps/FastLZ
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      RESULT_VARIABLE FASTLZ_SUBMODULE_RESULT
    )

    if( NOT FASTLZ_SUBMODULE_RESULT EQUAL 0 )
      message( WARNING "Failed to initialize deps/FastLZ submodule automatically." )
    endif()
  endif()
endif()

if( NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/FastLZ/fastlz.c" )
  message( FATAL_ERROR "FastLZ source is missing. Run: git submodule update --init --recursive -- deps/FastLZ" )
endif()

set( CMAKE_FOLDER "deps" )
add_library( fastlz STATIC "deps/FastLZ/fastlz.c" )
target_include_directories( fastlz PUBLIC "${CMAKE_SOURCE_DIR}/deps" )
add_subdirectory( "deps/zlib" )
add_subdirectory( "deps/MySQL" )
add_subdirectory( "deps/datReader" )
add_subdirectory( "deps/datReaderPs3" )
add_subdirectory( "deps/mysqlConnector" )
set(RECASTNAVIGATION_DT_POLYREF64 ON CACHE BOOL "Use 64bit polyrefs instead of 32bit for Detour" FORCE)
add_subdirectory( "deps/recastnavigation" )

if( SAPPHIRE_BUILD_TOOLKIT )
  # Build GLM as a static library
  set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )
  add_subdirectory( "deps/glm" )
  # Only build GLFW as a static library
  set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
  set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
  set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
  set( GLFW_INSTALL OFF CACHE BOOL "" FORCE )
  option( GLFW_USE_WAYLAND "Use Wayland for window creation" OFF )
  add_subdirectory( "deps/glfw" )
  # Only build GLEW as a static library
  set( ONLY_LIBS ON CACHE BOOL "" FORCE )
  set( glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE )
  add_subdirectory( "deps/glew" )
endif()

##############################
#  Main Sapphire Components  #
##############################
set( CMAKE_FOLDER "" )
add_subdirectory( "src/common" )
add_subdirectory( "src/api" )
add_subdirectory( "src/lobby" )
add_subdirectory( "src/world" )
add_subdirectory( "src/server_console" )
add_subdirectory( "src/server_gui" )
add_subdirectory( "src/dbm" )

set( CMAKE_FOLDER "scripts" )
add_subdirectory( "src/scripts" )

##############################
#           Tools            #
##############################
set( CMAKE_FOLDER "tools" )
add_subdirectory( "src/tools" )
