file( GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*" )
file( GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*" )

add_executable( dbm ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES} )

target_include_directories( dbm
                              PUBLIC
                                "${CMAKE_CURRENT_SOURCE_DIR}/"
                              PRIVATE
                                "${CMAKE_CURRENT_SOURCE_DIR}/../" )

target_link_libraries( dbm PRIVATE mysqlConnector common xivdat )
if (UNIX)
    target_link_libraries( dbm PRIVATE stdc++fs )
else()
    target_link_libraries( dbm PRIVATE mysql )
endif()

