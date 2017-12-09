cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
cmake_policy(SET CMP0014 OLD)

project(Sapphire_Zone)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

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

add_executable(server_zone ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES} )
add_dependencies(server_zone Common xivdat mysqlConnector )

set_target_properties(server_zone PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
)

if (UNIX)
  target_link_libraries ( server_zone Common xivdat pthread mysqlclient mysqlConnector dl z )
else()
  target_link_libraries ( server_zone Common xivdat libmysql zlib1 mysqlConnector )
endif()

target_link_libraries(server_zone ${Boost_LIBRARIES} )
