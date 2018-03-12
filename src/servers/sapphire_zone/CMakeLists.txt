cmake_minimum_required(VERSION 3.0.2)
cmake_policy(SET CMP0015 NEW)
cmake_policy(SET CMP0014 OLD)

project(sapphire_zone)

file(GLOB SERVER_PUBLIC_INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        /*.h
        Actor/*.h
        Action/*.h
        DebugCommand/*.h
        Event/*.h
        Inventory/*.h
        Linkshell/*.h
        Math/*.h
        Network/*.h
        Network/Handlers/*.h
        Network/PacketWrappers/*.h
        Script/*.h
        StatusEffect/*.h
        Zone/*.h)

file(GLOB SERVER_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.c*
        Actor/*.c*
        Action/*.c*
        DebugCommand/*.c*
        Event/*.c*
        Inventory/*.c*
        Linkshell/*.c*
        Math/*.c*
        Network/*.c*
        Network/Handlers/*.c*
        Network/PacketWrappers/*.c*
        Script/*.c*
        StatusEffect/*.c*
        Zone/*.c*)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/")

add_executable(sapphire_zone ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES} )

set_target_properties(sapphire_zone PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    ENABLE_EXPORTS ON
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
)

target_link_libraries( sapphire_zone common )

if (UNIX)
  target_link_libraries( sapphire_zone pthread )
  target_link_libraries( sapphire_zone dl )
  target_link_libraries( sapphire_zone z )
else()
  target_link_libraries( sapphire_zone zlib1 )
endif()

target_link_libraries( sapphire_zone ${Boost_LIBRARIES} )
target_include_directories( sapphire_zone PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )
target_include_directories( sapphire_zone PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Script" )
target_include_directories( sapphire_zone PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external" )
if (UNIX)
  cotire( sapphire_zone )
endif()
