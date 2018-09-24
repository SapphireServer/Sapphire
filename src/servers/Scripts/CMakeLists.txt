cmake_minimum_required(VERSION 3.0)
project(Sapphire_Script)

file(GLOB SCRIPT_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

message("exec: ${EXECUTABLE_OUTPUT_DIRECTORY}")

set(SCRIPT_LIB_DIR "${EXECUTABLE_OUTPUT_DIRECTORY}/compiledscripts/" )
set(EXECUTABLE_OUTPUT_PATH "${SCRIPT_LIB_DIR}")
set(LIBRARY_OUTPUT_PATH "${SCRIPT_LIB_DIR}")
set(RUNTIME_OUTPUT_DIRECTORY "${SCRIPT_LIB_DIR}")


file(GLOB children "${CMAKE_CURRENT_SOURCE_DIR}/*" )
foreach(_scriptDir ${children})
    get_filename_component(_name "${_scriptDir}" NAME_WE)
    if(IS_DIRECTORY ${_scriptDir} AND NOT ${_name} MATCHES "CMakeFiles" AND NOT ${_name} MATCHES "\\.dir$")
        message("discovered plugin lib: ${_scriptDir} (${_name})")

        file(GLOB_RECURSE SCRIPT_BUILD_FILES "${_scriptDir}/*.cpp")
        file(GLOB_RECURSE SCRIPT_FILES RELATIVE "${_scriptDir}" "${_name}/*.cpp")

        # build file list
        foreach(_script ${SCRIPT_FILES})
            get_filename_component( _scriptname "${_script}" NAME_WE)

            if(NOT ${_scriptname} MATCHES "ScriptLoader")
                if(ScriptIncludes)
                    set(ScriptIncludes "${ScriptIncludes}\n#include \"${_script}\"")
                else()
                    set(ScriptIncludes "#include \"${_script}\"")
                endif()

                set(ScriptNames "${ScriptNames}   static_cast< ScriptObject* >( new ${_scriptname} ),\n")
            endif()
        endforeach()

        add_library("script_${_name}" MODULE ${SCRIPT_BUILD_FILES} "${SCRIPT_INCLUDE_FILES}" "${_scriptDir}/ScriptLoader.cpp")
        target_link_libraries( "script_${_name}" sapphire_zone )

        if(MSVC)
            #target_link_libraries( "script_${_name}" ${Boost_LIBRARIES})
            set_target_properties( "script_${_name}" PROPERTIES
                CXX_STANDARD 14
                CXX_STANDARD_REQUIRED ON
                CXX_EXTENSIONS ON
                LIBRARY_OUTPUT_DIRECTORY_DEBUG "${SCRIPT_LIB_DIR}"
                LIBRARY_OUTPUT_DIRECTORY_RELEASE "${SCRIPT_LIB_DIR}"
                LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${SCRIPT_LIB_DIR}"
                LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${SCRIPT_LIB_DIR}"
            )
        endif()
        target_include_directories("script_${_name}" PUBLIC "${CMAKE_SOURCE_DIR}/src/servers/sapphire_zone/")
        target_include_directories("script_${_name}" PUBLIC "${CMAKE_SOURCE_DIR}/src/servers/Script/Scripts")
        target_include_directories("script_${_name}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
        target_include_directories("script_${_name}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Scripts")

        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ScriptLoader.cpp.in" "${_scriptDir}/ScriptLoader.cpp")

        cotire("script_${_name}")

        if(MSVC)
            add_custom_command(TARGET "script_${_name}" POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E remove "${SCRIPT_LIB_DIR}/script_${_name}.exp"
                COMMAND ${CMAKE_COMMAND} -E remove "${SCRIPT_LIB_DIR}/script_${_name}.lib"
                COMMAND ${CMAKE_COMMAND} -E remove "${SCRIPT_LIB_DIR}/script_${_name}.ilk"
            )
        endif()

        unset(ScriptIncludes)
        unset(ScriptNames)
    endif()
endforeach()
