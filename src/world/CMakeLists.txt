cmake_minimum_required( VERSION 3.0.2 )
cmake_policy( SET CMP0015 NEW )

project( world )

file( GLOB SERVER_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.cpp
        Actor/*.cpp
        Action/*.cpp
        Action/Job/*.cpp
        ContentFinder/*.cpp
        DebugCommand/*.cpp
        Event/*.cpp
        FreeCompany/*.cpp
        Inventory/*.cpp
        Linkshell/*.cpp
        Manager/*.cpp
        Math/*.cpp
        Network/*.cpp
        Network/Util/*.cpp
        Network/Handlers/*.cpp
        Network/PacketWrappers/*.cpp
        Script/*.cpp
        StatusEffect/*.cpp
        Territory/*.cpp
        Territory/Housing/*.cpp
        Util/*.cpp
        Navi/*.cpp
        Task/*.cpp
        Quest/*.cpp )

add_executable( world ${SERVER_SOURCE_FILES} )

set_target_properties( world
                         PROPERTIES
                           ENABLE_EXPORTS ON
                           WINDOWS_EXPORT_ALL_SYMBOLS ON )

target_link_libraries( world
                         PUBLIC
                           common 
                            Detour
                            DetourCrowd )
target_include_directories( world
                              PUBLIC
                                "${CMAKE_CURRENT_SOURCE_DIR}"
                                    Detour )


