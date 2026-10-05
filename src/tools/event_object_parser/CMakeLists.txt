add_executable( event_object_parser main.cpp "vec3.h" "matrix4.h" )
target_link_libraries( event_object_parser PRIVATE common )

add_custom_command(
  TARGET event_object_parser POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/instance.tmpl"
          "${CMAKE_CURRENT_SOURCE_DIR}/questbattle.tmpl"
          "$<TARGET_FILE_DIR:event_object_parser>"
)
