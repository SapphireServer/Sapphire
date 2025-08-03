file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*")

add_executable(exd_struct_test ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

if (UNIX)
  target_link_libraries (exd_struct_test common xivdat pthread mysql dl z stdc++fs )
else()
  target_link_libraries (exd_struct_test common xivdat mysql zlib)
endif()

