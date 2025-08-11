file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable(discovery_parser ${SOURCES} )
target_link_libraries( discovery_parser PRIVATE common )
