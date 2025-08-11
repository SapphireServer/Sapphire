file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable(bnpc_parserps3 ${SOURCES} )
target_link_libraries ( bnpc_parserps3 PRIVATE common xivdatps3 )
