cmake_minimum_required(VERSION 3.0.2)
cmake_policy(SET CMP0015 NEW)
project(Sapphire)

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*")


add_executable(sapphire_lobby ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

set_target_properties(sapphire_lobby PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
        )

target_link_libraries(sapphire_lobby PRIVATE common)

cotire( sapphire_lobby )
