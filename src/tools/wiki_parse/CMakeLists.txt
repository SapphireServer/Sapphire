file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( wiki_parse ${SOURCES} )
target_link_libraries( wiki_parse PRIVATE common )