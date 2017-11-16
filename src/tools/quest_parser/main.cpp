
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <iostream>
#include <set>
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Logging/Logger.h>

#include <fstream>


Core::Logger g_log;
Core::Data::ExdData g_exdData;


void createScript( boost::shared_ptr< Core::Data::QuestInfo > pQuestData, std::set< std::string > additionalList )
{
   std::string header(
      "// This is an automatically generated chai script template\n"
      "// Content needs to be added by hand to make it function\n"
      "// In order for this script to be loaded, change its extension to .chai\n"
      "// and move it to the correct folder in bin/scripts/chai/quest\n"
      "\n"
   );

   std::size_t splitPos = pQuestData->name_intern.find( "_" );
   std::string className = pQuestData->name_intern.substr( 0, splitPos );

   std::string sceneStr = "    //////////////////////////////////////////////////////////////////////\n    // Available Scenes in this quest, not necessarly all are used\n";
   std::string seqStr = "        // Steps in this quest ( 0 is before accepting, \n        // 1 is first, 255 means ready for turning it in\n";
   std::string questVarStr = "        // Quest vars / flags used\n";
   for( auto &entry : additionalList )
   {
      if( entry.find( "OnScene" ) != std::string::npos )
      {
         std::string sceneName = entry.substr( 2 );
         std::string sceneId = entry.substr( 7 );

         std::size_t numOff = sceneId.find_first_not_of( "0" );
         sceneId = numOff != std::string::npos ? sceneId.substr( numOff ) : "0";

         sceneStr += "    def " + sceneName + "( player )\n";
         sceneStr += "    {\n";  
         sceneStr += "        player.eventPlay( this.id, " + sceneId + ", NONE,\n";
         sceneStr += "            fun( player, eventId, param1, param2, param3 )\n";
         sceneStr += "            {} );\n";
         sceneStr += "    }\n\n";  
      }
      else if( entry.find( "Flag" ) != std::string::npos ||
               entry.find( "QuestUI" ) != std::string::npos )
      {
         questVarStr += "        // " + entry + "\n";
      }
      else if( entry.find( "SEQ" ) != std::string::npos )
      {
         if( entry.find( "SEQ_FINISH" ) != std::string::npos )
         {
            seqStr += "        this.SEQ_FINISH = 255;\n";
         }
         else if( entry.find( "SEQ_OFFER" ) != std::string::npos )
         {
         }
         else
         {
            std::string seqName = entry;
            std::string seqId = entry.substr( 4 );
            seqStr += "        this." + seqName + " = " + seqId + ";\n";
         }
      }


   }
   std::string rewards = "        // Quest rewards \n";
   rewards += ( pQuestData->reward_exp_factor != 0 ) ? "        this.RewardExpFactor = " + std::to_string( pQuestData->reward_exp_factor ) + ";\n" : "";
   rewards += ( pQuestData->reward_gil != 0 ) ? "        this.RewardGil = " + std::to_string( pQuestData->reward_gil ) + ";\n" : "";
   rewards += ( pQuestData->reward_emote != 0 ) ? "        this.RewardEmote = " + std::to_string( pQuestData->reward_emote ) + ";\n" : "";
   rewards += ( pQuestData->reward_action != 0 ) ? "        this.RewardAction = " + std::to_string( pQuestData->reward_action ) + ";\n" : "";
   rewards += ( pQuestData->reward_action_general1 != 0 ) ? "        this.RewardGeneralAction1 = " + std::to_string( pQuestData->reward_action_general1 ) + ";\n" : "";
   rewards += ( pQuestData->reward_action_general2 != 0 ) ? "        this.RewardGeneralAction2 = " + std::to_string( pQuestData->reward_action_general2 ) + ";\n" : "";
   rewards += ( pQuestData->reward_gc_seals != 0 ) ? "        this.RewardGCSeals = " + std::to_string( pQuestData->reward_gc_seals ) + ";\n" : "";
   rewards += ( pQuestData->reward_other != 0 ) ? "         this.RewardOther = " + std::to_string( pQuestData->reward_other ) + ";\n" : "";
   rewards += ( pQuestData->reward_reputation != 0 ) ? "        this.RewardReputation = " + std::to_string( pQuestData->reward_reputation ) + ";\n" : "";
   rewards += ( pQuestData->reward_tome_type != 0 ) ? "        this.RewardTomeType = " + std::to_string( pQuestData->reward_tome_type ) + ";\n" : "";
   rewards += ( pQuestData->reward_tome_count != 0 ) ? "        this.RewardTomeCount = " + std::to_string( pQuestData->reward_tome_count ) + ";\n" : "";
   rewards += ( pQuestData->instanced_content_unlock != 0 ) ? "        this.InstancedContentUnlock = " + std::to_string( pQuestData->instanced_content_unlock ) + ";\n" : "";

   if( pQuestData->reward_item.size() > 0 )
   {
      rewards += "        this.RewardItem = [";
      for( size_t ca = 0; ca < pQuestData->reward_item.size(); ca++ )
      {
         rewards += std::to_string( pQuestData->reward_item.at( ca ) );
         if( ca != pQuestData->reward_item.size() - 1 )
         {
            rewards += ", ";
         }
      }
      rewards += "];\n";
   }

   if( pQuestData->reward_item.size() > 0 )
   {
      rewards += "        this.RewardItemCount = [";
      for( size_t ca = 0; ca < pQuestData->reward_item_count.size(); ca++ )
      {
         rewards += std::to_string( pQuestData->reward_item_count.at( ca ) );
         if( ca != pQuestData->reward_item_count.size() - 1 )
         {
            rewards += ", ";
         }
      }
      rewards += "];\n";
   }

   if( pQuestData->reward_item_optional.size() > 0 )
   {
      rewards += "        this.RewardItemOptional = [";
      for( size_t ca = 0; ca < pQuestData->reward_item_optional.size(); ca++ )
      {
         rewards += std::to_string( pQuestData->reward_item_optional.at( ca ) );
         if( ca != pQuestData->reward_item_optional.size() - 1 )
         {
            rewards += ", ";
         }
      }
      rewards += "];\n";
   }

   if( pQuestData->reward_item_optional_count.size() > 0 )
   {
      rewards += "        this.RewardItemOptionalCount = [";
      for( size_t ca = 0; ca < pQuestData->reward_item_optional_count.size(); ca++ )
      {
         rewards += std::to_string( pQuestData->reward_item_optional_count.at( ca ) );
         if( ca != pQuestData->reward_item_optional_count.size() - 1 )
         {
            rewards += ", ";
         }
      }
      rewards += "];\n";
   }

   bool hasERange = false;
   bool hasEmote = false;
   bool hasEnemies = false;
   std::vector< uint32_t > enemy_ids;
   std::vector< std::string > script_entities;
   std::string sentities = "        // Entities found in the script data of the quest\n";
   
   for( size_t ca = 0; ca < pQuestData->script_entity.size(); ca ++ )
   {
     if( ( pQuestData->script_entity.at( ca ).find( "HOWTO" ) != std::string::npos ) || ( pQuestData->script_entity.at( ca ).find( "HOW_TO" ) != std::string::npos ) )
        continue;

     if( (pQuestData->script_entity.at( ca ).find( "EMOTENO" ) != std::string::npos ) || (pQuestData->script_entity.at( ca ).find( "EMOTEOK" ) != std::string::npos ) )
        hasEmote = true;

     if(pQuestData->script_entity.at(ca).find("ENEMY") != std::string::npos)
     {
        hasEnemies = true;
        enemy_ids.push_back(pQuestData->script_value.at(ca));
     }

     script_entities.push_back( pQuestData->script_entity.at( ca ) + " = " + std::to_string( pQuestData->script_value.at( ca ) ) ); 
   }
   std::sort( script_entities.begin(), script_entities.end() );
   
   for( auto& entity : script_entities )
   {
     sentities += "        this." + entity + ";\n";
   }

   std::string additional = "// Quest Script: " + pQuestData->name_intern + "\n";
   additional += "// Quest Name: " + pQuestData->name + "\n";
   additional += "// Quest ID: " + std::to_string( pQuestData->id ) + "\n";
   additional += "// Start NPC: " + std::to_string( pQuestData->enpc_resident_start ) + "\n";
   additional += "// End NPC: " + std::to_string( pQuestData->enpc_resident_end ) + "\n\n";

   std::string scriptEntry = "    //////////////////////////////////////////////////////////////////////\n";
   scriptEntry += "    // Event Handlers\n";
   scriptEntry += "    def onTalk( eventId, player, actorId )\n";
   scriptEntry += "    {\n";
   scriptEntry += "        var actor = mapActor( actorId );\n";
   scriptEntry += "    }\n\n";
   
   if( hasERange )
   {
     scriptEntry += "    def onWithinRange( eventId, player, eRangeId, x, y, z )\n";
     scriptEntry += "    {\n";
     scriptEntry += "    }\n\n";
   }
   
   if( hasEmote )
   {
     scriptEntry += "    def onEmote( eventId, player, actorId, emoteId )\n";
     scriptEntry += "    {\n";
     scriptEntry += "    }\n\n";
   }

   for( auto enemy : enemy_ids )
   {
      scriptEntry += "    def onMobKill_" + std::to_string(enemy) + "( player )\n";
      scriptEntry += "    {\n";
      scriptEntry += "    }\n\n";
   }
   
   std::string constructor;
   constructor += "    def " + className + "Def()\n";
   constructor += "    {\n";
   constructor += "        // Basic quest information \n";
   constructor += "        this.name = \"" + pQuestData->name + "\";\n";
   constructor += "        this.id = " + std::to_string( pQuestData->id ) + ";\n\n";
   constructor += questVarStr + "\n";
   constructor += seqStr + "\n";
   constructor += rewards + "\n";
   constructor += sentities + "\n";
   constructor += "    }\n";
   
   
   std::string classString(
      "class " + className + "Def \n"
      "{\n"
      + constructor +
      "\n"
      + sceneStr +
      scriptEntry +
      "};\n\n"
   );

   std::string objName = className;
   std::string initObj = "GLOBAL " + objName + " = " + className + "Def();\n";

   std::ofstream outputFile;
   outputFile.open( "generated/" + className + ".chai_generated" );
   outputFile << header << additional << classString << initObj;
   outputFile.close();
}

int main()
{

   g_log.init();

  // std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
   std::string datLocation( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack\\ffxiv" );

   g_log.info( "Setting up EXD data" );
   if( !g_exdData.init( datLocation  ) )
   {
      g_log.fatal( "Error setting up EXD data " );
      return 0;
   }

   xiv::dat::GameData data( datLocation );
   xiv::exd::ExdData eData( data );

   auto QuestDat = g_exdData.setupDatAccess( "Quest", xiv::exd::Language::en );
   auto rows = QuestDat.get_rows();

   for( auto row : rows )
   {
      
      auto questInfo = g_exdData.getQuestInfo( row.first );

      if( questInfo->name.empty() || questInfo->name_intern.empty() )
      {
         continue;
      }

      size_t pos_seperator = questInfo->name_intern.find_first_of( "_" );

      std::string folder;

      if( pos_seperator != std::string::npos )
      {
         folder = questInfo->name_intern.substr( pos_seperator + 1, 3 );
      }
      else
      {
         return 0;
      }



      const xiv::dat::Cat& test = data.get_category( "game_script" );

      const std::string questPath = "game_script/quest/" + folder + "/" + questInfo->name_intern + ".luab";

      const auto &test_file = data.get_file( questPath );
      auto &section = test_file->access_data_sections().at( 0 );
      int32_t size = *( uint32_t* ) &section[4];

      std::set<std::string> stringList;

      uint32_t offset = 0;

      std::ofstream outputFile1;
      outputFile1.open("generated/" + questInfo->name_intern + ".luab", std::ios::binary);
      outputFile1.write(&section[0], section.size());
      outputFile1.close();
      std::string command= std::string("java -jar unluac_2015_06_13.jar ") + "generated/" + questInfo->name_intern + ".luab" + ">> " + "generated/" + questInfo->name_intern + ".lua";
      if ( system( command.c_str() ) == -1 )
      {
         g_log.error( "Error executing java command:\n" + command + "\nerrno: " + std::strerror( errno ) );
         return errno;
      }
      for( ; ; )
      {
         
         std::string entry( &section[offset] );
         offset += entry.size() + 1;
    
         if( entry.size() > 3 
             &&  entry.find_first_not_of( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_" ) == std::string::npos )
         {
            if( entry.find( "SEQ" ) != std::string::npos
                || entry.find( "QuestUI" ) != std::string::npos
                || entry.find( "OnScene" ) != std::string::npos
                || entry.find( "Flag" ) != std::string::npos
                || entry.find( "ACTOR" ) != std::string::npos
                && entry.find( "_ACTOR" ) == std::string::npos )
               if( entry.find( "HOWTO" ) == std::string::npos )
                   stringList.insert( entry );
         }

         if( offset >= section.size() )
            break;
      }


      createScript( questInfo, stringList );
//break;
   }

   return 0;
}
