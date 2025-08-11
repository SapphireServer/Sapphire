file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( dbm ${SOURCES} )
target_link_libraries( dbm PRIVATE common )
