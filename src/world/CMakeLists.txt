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
        Territory/Housing/*.c*
        Navi/*.c*)

add_executable( world ${SERVER_SOURCE_FILES} )

set_target_properties( world
                         PROPERTIES
                           ENABLE_EXPORTS ON
                           WINDOWS_EXPORT_ALL_SYMBOLS ON )

target_link_libraries( world
                         PUBLIC
                           common 
                            Detour)
target_include_directories( world
                              PUBLIC
                                "${CMAKE_CURRENT_SOURCE_DIR}"
                                    Detour )


if( UNIX )
    cotire( world )
endif()
