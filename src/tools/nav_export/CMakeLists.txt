file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( nav_export ${SOURCES} )

target_link_libraries( nav_export PRIVATE common Recast DetourTileCache )

# NOTE: This is for #include <datReader/xxx>
target_include_directories( nav_export PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../deps" )
