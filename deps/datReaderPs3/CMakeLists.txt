file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_library( xivdatps3 ${SOURCES} )
target_link_libraries( xivdatps3 PUBLIC zlib )
target_include_directories( xivdatps3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
