cmake_minimum_required(VERSION 3.0.2)
project(Sapphire)


file( GLOB UTILS_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*" )
file( GLOB UTILS_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*" )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( mysqlConnector ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} )
target_include_directories( mysqlConnector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
if(UNIX)
  target_include_directories( mysqlConnector PUBLIC "/usr/include/mysql/" )
  
else()
  target_include_directories( mysqlConnector PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../external/MySQL/" )
endif()
cotire(mysqlConnector)
