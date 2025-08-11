add_executable( custom_talk_parse main.cpp )
target_link_libraries( custom_talk_parse PRIVATE common )

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/unluac_2015_06_13.jar
  ${EXECUTABLE_OUTPUT_PATH}/unluac_2015_06_13.jar
  COPYONLY
)
