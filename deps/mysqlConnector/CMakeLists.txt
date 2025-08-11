file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_library( mysqlConnector ${SOURCES} )

target_include_directories( mysqlConnector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( mysqlConnector PUBLIC mysql )
