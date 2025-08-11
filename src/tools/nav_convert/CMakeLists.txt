file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( nav_convert ${SOURCES} )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
target_link_libraries( nav_convert PRIVATE common Recast DetourTileCache )
