cmake_minimum_required(VERSION 3.2)
project(Sapphire_Script)

file(GLOB SCRIPT_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SCRIPT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

include_directories("../../src/servers/")
include_directories("../../src/servers/Server_Zone/")

if(MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yc${CMAKE_CURRENT_SOURCE_DIR}/ScriptObject.h /FI${CMAKE_CURRENT_SOURCE_DIR}/ScriptObject.h")
endif()

foreach(_sourcefile ${SCRIPT_FILES})
    get_filename_component(_file "${_sourcefile}" NAME_WE)
    add_library("${_file}" MODULE "${_sourcefile}" "${SCRIPT_INCLUDE_FILES}")

    target_link_libraries("${_file}" server_zone)

    if(MSVC)
        set_source_files_properties("${_file}" PROPERTIES
            COMPILE_FLAGS "/Yc${CMAKE_CURRENT_SOURCE_DIR}/ScriptObject.h"
        )
    endif()

    set_target_properties("${_file}" PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/compiledscripts/"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/compiledscripts/"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/compiledscripts/"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/compiledscripts/"
    )

    add_custom_command(TARGET "${_file}" POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/${_file}.exp"
        COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/${_file}.lib"
    )
endforeach(_sourcefile ${SCRIPT_FILES})