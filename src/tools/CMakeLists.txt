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
# These currently do not build, needs work
#add_subdirectory( "exd_common_gen" )
#add_subdirectory( "exd_struct_gen" )
#add_subdirectory( "exd_struct_test" )
#add_subdirectory( "mob_parse" )
#add_subdirectory( "questbattle_bruteforce" )

add_subdirectory( "quest_parser" )
add_subdirectory( "custom_talk_parser" )
add_subdirectory( "discovery_parser" )
add_subdirectory( "nav_export" )
add_subdirectory( "nav_convert" )
add_subdirectory( "BattleNpcParserPs3" )
add_subdirectory( "event_object_parser" )
add_subdirectory( "action_parse" )
add_subdirectory( "wiki_parse" )

if( SAPPHIRE_BUILD_TOOLKIT )
  add_subdirectory( "Toolkit" )
endif()
