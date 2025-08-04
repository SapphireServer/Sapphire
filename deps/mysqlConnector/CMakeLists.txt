file( GLOB UTILS_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*" )
file( GLOB UTILS_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*" )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( mysqlConnector ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} )

target_include_directories( mysqlConnector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( mysqlConnector PUBLIC mysql )
#cotire(mysqlConnector)
