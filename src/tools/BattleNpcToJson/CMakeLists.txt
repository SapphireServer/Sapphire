file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable(bnpc_to_json ${SOURCES} )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
target_link_libraries ( bnpc_to_json PRIVATE common xivdatps3 )
