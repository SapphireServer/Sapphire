
file( GLOB_RECURSE SOURCES
        *.cpp
  *.h
)

add_executable( server ${SOURCES} )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

set_target_properties( server PROPERTIES
                           ENABLE_EXPORTS ON
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries( server PUBLIC world )
target_include_directories( server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" )
