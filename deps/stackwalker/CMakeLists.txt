cmake_minimum_required(VERSION 3.0.2)
project(Sapphire)

if( WIN32 )

  file( GLOB STACKWALKER_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h*" )
  file( GLOB STACKWALKER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c*" )

  add_library( stackwalker ${STACKWALKER_INCLUDE_FILES} ${STACKWALKER_SOURCE_FILES} )

endif()