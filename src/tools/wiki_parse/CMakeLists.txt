file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( wiki_parse ${SOURCES} )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
target_link_libraries( wiki_parse PRIVATE common )