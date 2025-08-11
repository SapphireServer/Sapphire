file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_library( common ${SOURCES} )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

find_package( Threads REQUIRED )

target_link_libraries( common PUBLIC
  xivdat
  mysqlConnector
  mysql
  Threads::Threads
  DetourCrowd
)

target_include_directories( common PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
  # NOTE: This is for #include <datReader/xxx>
  "${CMAKE_CURRENT_SOURCE_DIR}/../../deps"
)

# Add asio and spdlog as system includes to suppress pointless warnings
target_include_directories( common SYSTEM PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/asio/asio/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/spdlog/include"
)
