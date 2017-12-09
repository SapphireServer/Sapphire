project(Sapphire_Script)

file(GLOB SCRIPT_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

file(GLOB_RECURSE SCRIPT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(_sourcefile "${SCRIPT_FILES}")
    get_filename_component(_file "${_sourcefile}" NAME_WE)
    add_library("${_file}" MODULE "${_sourcefile}" "${SCRIPT_INCLUDE_FILES}")

    add_dependencies("${_file}" server_zone)
    target_link_libraries("${_file}" server_zone)

    set_target_properties("${_file}" PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS ON
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/compiledscripts/"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/compiledscripts/"
            RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/compiledscripts/"
            RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/compiledscripts/"
            )
endforeach(_sourcefile "${SCRIPT_FILES}")