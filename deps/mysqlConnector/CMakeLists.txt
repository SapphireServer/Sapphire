cmake_minimum_required(VERSION 3.2.0)
project(Sapphire)


file( GLOB UTILS_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*" )
file( GLOB UTILS_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*" )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( mysqlConnector ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} )

set_target_properties( mysqlConnector PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        )

target_include_directories( mysqlConnector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( mysqlConnector PUBLIC mysql )
#cotire(mysqlConnector)
