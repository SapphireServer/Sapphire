file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)
add_executable( api ${SOURCES} )

target_link_libraries( api PRIVATE common )
