cmake_minimum_required( VERSION 3.0.2 )
cmake_policy( SET CMP0015 NEW )

project( world )

file( GLOB SERVER_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.c*
        Actor/*.c*
        Action/*.c*
        DebugCommand/*.c*
        Event/*.c*
        Inventory/*.c*
        Linkshell/*.c*
        Manager/*.c*
        Math/*.c*
        Network/*.c*
        Network/Handlers/*.c*
        Network/PacketWrappers/*.c*
        Script/*.c*
        StatusEffect/*.c*
        Territory/*.c*
        Territory/Housing/*.c*)

add_executable( world ${SERVER_SOURCE_FILES} )

set_target_properties( world PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        ENABLE_EXPORTS ON
        WINDOWS_EXPORT_ALL_SYMBOLS ON
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
)


target_link_libraries( world PUBLIC common )
target_include_directories( world PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )


if( UNIX )
    cotire( world )
    target_link_libraries( world PUBLIC stdc++fs )
else()
    target_link_libraries( world PUBLIC mysql )
endif()
