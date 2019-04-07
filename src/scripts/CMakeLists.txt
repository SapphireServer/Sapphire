cmake_minimum_required(VERSION 3.0)
project(Script)

file(GLOB SCRIPT_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

message("exec: ${EXECUTABLE_OUTPUT_PATH}")

set(SCRIPT_LIB_DIR "${EXECUTABLE_OUTPUT_PATH}/compiledscripts/" )
set(EXECUTABLE_OUTPUT_PATH "${SCRIPT_LIB_DIR}")
set(LIBRARY_OUTPUT_PATH "${SCRIPT_LIB_DIR}")
set(RUNTIME_OUTPUT_DIRECTORY "${SCRIPT_LIB_DIR}")

if( WIN32 )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${SCRIPT_LIB_DIR}" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${SCRIPT_LIB_DIR}" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${SCRIPT_LIB_DIR}" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${SCRIPT_LIB_DIR}" )
endif()

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
                    set(ScriptIncludes "${ScriptIncludes}\nextern Sapphire::ScriptAPI::ScriptObject* makeScript${_scriptname}();")
                else()
                    set(ScriptIncludes "extern Sapphire::ScriptAPI::ScriptObject* makeScript${_scriptname}();")
                endif()

                set(ScriptNames "${ScriptNames}   makeScript${_scriptname}(),\n")
            endif()
        endforeach()

        add_library( "script_${_name}"
                       MODULE 
                         ${SCRIPT_BUILD_FILES} 
                         "${SCRIPT_INCLUDE_FILES}"
                         "${_scriptDir}/ScriptLoader.cpp" )

        target_link_libraries( "script_${_name}" world )

        target_include_directories("script_${_name}" PUBLIC "${CMAKE_SOURCE_DIR}/src/scripts")
        target_include_directories("script_${_name}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
        target_include_directories("script_${_name}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Scripts")

        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ScriptLoader.cpp.in" "${_scriptDir}/ScriptLoader.cpp")

        if( UNIX )
            cotire("script_${_name}")
        endif()

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
