add_executable( quest_parse main.cpp )
target_link_libraries( quest_parse PRIVATE common )

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/unluac_2015_06_13.jar
  ${EXECUTABLE_OUTPUT_PATH}/unluac_2015_06_13.jar
  COPYONLY
)