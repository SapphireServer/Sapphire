sapphire_set_output_directories(
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tools"
)

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
add_subdirectory( "BattleNpcToJson" )

if( SAPPHIRE_BUILD_TOOLKIT )
  add_subdirectory( "Toolkit" )
  add_subdirectory( "ToolkitPs3" )
endif()
