
file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( world ${SOURCES} )

set_target_properties( world PROPERTIES
  ENABLE_EXPORTS ON
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries( world PUBLIC common )
target_include_directories( world PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )
