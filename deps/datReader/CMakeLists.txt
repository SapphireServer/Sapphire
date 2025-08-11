include_directories( "../" )

file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_library( xivdat ${SOURCES} )
target_link_libraries( xivdat PUBLIC zlib )
target_include_directories( xivdat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
