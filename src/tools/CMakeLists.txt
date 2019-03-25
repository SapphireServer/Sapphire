cmake_policy( SET CMP0014 NEW )
cmake_minimum_required( VERSION 3.0.2 )
project( Sapphire )

set( EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/tools )
set( LIBRARY_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH}/tools )

if( WIN32 )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/tools" )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/tools" )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO}/tools" )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL}/tools" )
  set( VS_DEBUGGER_WORKING_DIRECTORY "${VS_DEBUGGER_WORKING_DIRECTORY}/tools" )
endif()

##############################
#           Tools            #
##############################
add_subdirectory( "exd_common_gen" )
add_subdirectory( "exd_struct_gen" )
add_subdirectory( "exd_struct_test" )
add_subdirectory( "quest_parser" )
add_subdirectory( "discovery_parser" )
add_subdirectory( "mob_parse" )
add_subdirectory( "pcb_reader" )
add_subdirectory( "nav_export" )
add_subdirectory( "event_object_parser" )
add_subdirectory( "action_parse" )
