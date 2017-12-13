cmake_minimum_required(VERSION 3.0)
project(Sapphire_Script)

file(GLOB SCRIPT_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SCRIPT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/src/servers/")
include_directories("${CMAKE_SOURCE_DIR}/src/servers/Server_Zone/")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yc${CMAKE_CURRENT_SOURCE_DIR}/ScriptObject.h /FI${CMAKE_CURRENT_SOURCE_DIR}/ScriptObject.h")
endif()

message( "exec: ${EXECUTABLE_OUTPUT_DIRECTORY}" )

set( SCRIPT_LIB_DIR "${EXECUTABLE_OUTPUT_DIRECTORY}/compiledscripts/" )
set( EXECUTABLE_OUTPUT_PATH "${SCRIPT_LIB_DIR}")
set( LIBRARY_OUTPUT_PATH "${SCRIPT_LIB_DIR}")
set( RUNTIME_OUTPUT_DIRECTORY "${SCRIPT_LIB_DIR}")

foreach(_sourcefile ${SCRIPT_FILES})
    get_filename_component(_file "${_sourcefile}" NAME_WE)
    add_library("${_file}" MODULE "${_sourcefile}" "${SCRIPT_INCLUDE_FILES}")

    if(MSVC)
        set_source_files_properties("${_file}" PROPERTIES
            COMPILE_FLAGS "/Yc${CMAKE_CURRENT_SOURCE_DIR}/ScriptObject.h"
        )
        set_target_properties(${_file} PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS ON
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${SCRIPT_LIB_DIR}"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${SCRIPT_LIB_DIR}"
            LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${SCRIPT_LIB_DIR}"
            LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${SCRIPT_LIB_DIR}"
        )
    endif()

    target_link_libraries("${_file}" server_zone)

    add_custom_command(TARGET "${_file}" POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove "${SCRIPT_LIB_DIR}/${_file}.exp"
        COMMAND ${CMAKE_COMMAND} -E remove "${SCRIPT_LIB_DIR}/${_file}.lib"
        COMMAND ${CMAKE_COMMAND} -E remove "${SCRIPT_LIB_DIR}/${_file}.ilk"
    )
endforeach(_sourcefile ${SCRIPT_FILES})