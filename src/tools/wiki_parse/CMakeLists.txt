file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*")

add_executable( wiki_parse ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

if (UNIX)
  target_link_libraries( wiki_parse common xivdat pthread mysql dl z stdc++fs )
else()
  target_link_libraries( wiki_parse common xivdat mysql zlib )
endif()
