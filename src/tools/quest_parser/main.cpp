#include <cstdint>
#include <fstream>
#include <iostream>
#include <locale>
#include <set>
#include <string>
#include <cstring>

#include <experimental/filesystem>

#include <Exd.h>
#include <ExdCat.h>
#include <ExdData.h>
#include <File.h>
#include <GameData.h>
#include <DatCat.h>

#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>

#include <algorithm>

Sapphire::Data::ExdDataGenerated g_exdDataGen;
namespace fs = std::experimental::filesystem;
using namespace Sapphire;

const std::string onTalkStr(
  "  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override\n"
  "  {\n"
  "    auto actor = Event::mapEventActorToRealActor( actorId );\n"
  "  }\n\n"
);

const std::string onWithinRangeStr(
  "  void onWithinRange( uint32_t eventId, Entity::Player& player, uint64_t eRangeId, float x, float y, float z ) override\n"
  "  {\n"
  "  }\n\n"
);

const std::string onEmoteStr(
  "  void onEmote( uint32_t eventId, Entity::Player& player, uint64_t actorId, uint32_t emoteId ) override\n"
  "  {\n"
  "  }\n\n"
);

std::string titleCase( const std::string& str )
{
  if( str.empty() )
    return str;

  std::string retStr( str );
  std::transform( str.begin(), str.end(), retStr.begin(), ::tolower );
  std::locale loc;
  retStr[ 0 ] = std::toupper( str[ 0 ], loc );
  for( size_t i = 1; i < str.size(); ++i )
  {
    if( str[ i - 1 ] == ' ' || str[ i - 1 ] == '_' ||
        ( std::isdigit( str[ i - 1 ], loc ) && !std::isdigit( str[ i ], loc ) ) )
      retStr[ i ] = std::toupper( str[ i ], loc );
  }
  return retStr;
}

void
createScript( std::shared_ptr< Sapphire::Data::Quest >& pQuestData, std::set< std::string >& additionalList, int questId )
{
  std::string header(
    "// This is an automatically generated C++ script template\n"
    "// Content needs to be added by hand to make it function\n"
    "// In order for this script to be loaded, move it to the correct folder in <root>/scripts/\n"
    "\n"
    "#include <ScriptObject.h>\n\n"
  );

  std::size_t splitPos( pQuestData->id.find( "_" ) );
  std::string className( pQuestData->id.substr( 0, splitPos ) );
  //className = "Quest" + className;
  std::string sceneStr(
    "  //////////////////////////////////////////////////////////////////////\n  // Available Scenes in this quest, not necessarly all are used\n" );
  std::string seqStr;
  seqStr.reserve( 0xFFF );
  seqStr += ( "    // Steps in this quest ( 0 is before accepting, \n    // 1 is first, 255 means ready for turning it in\n" );
  std::string questVarStr( "    // Quest vars / flags used\n" );

  seqStr += "    enum Sequence : uint8_t\n    {\n";
  for( auto& entry : additionalList )
  {
    if( entry.find( "OnScene" ) != std::string::npos )
    {
      std::string sceneName = entry.substr( 2 );
      std::string sceneId = entry.substr( 7 );

      std::size_t numOff = sceneId.find_first_not_of( "0" );
      sceneId = numOff != std::string::npos ? sceneId.substr( numOff ) : "0";

      sceneStr += std::string(
        "  void " +
        sceneName +
        "( Entity::Player& player )\n"
        "  {\n"
        "    player.playScene( getId(), " +
        sceneId +
        ", 0,\n"
        "      [ & ]( Entity::Player& player, const Event::SceneResult& result )\n"
        "      {\n"
        "      });\n"
        "  }\n\n"
      );
    }
    else if( entry.find( "Flag" ) != std::string::npos ||
             entry.find( "QuestUI" ) != std::string::npos )
    {
      questVarStr += "    // " + entry + "\n";
    }
    else if( entry.find( "SEQ" ) != std::string::npos )
    {
      if( entry.find( "SEQ_FINISH" ) != std::string::npos )
      {
        seqStr += "      SeqFinish = 255,\n";
      }
      else if( entry.find( "SEQ_OFFER" ) != std::string::npos )
      {
      }
      else
      {
        std::string seqName = titleCase( entry );

        seqName.erase( std::remove_if( seqName.begin(), seqName.end(), []( const char c ) {
          return c == '_';
        }), seqName.end());

        std::string seqId = entry.substr( 4 );
        seqStr += "      " + seqName + " = " + seqId + ",\n";
      }
    }
  }
  seqStr += "    };\n";
  std::string rewards;
  rewards.reserve( 0xFFF );
  rewards += "    // Quest rewards \n";
  rewards += ( pQuestData->expFactor != 0 ) ? "    static constexpr auto RewardExpFactor = " +
                                              std::to_string( pQuestData->expFactor ) + ";\n" : "";
  rewards += ( pQuestData->gilReward != 0 ) ? "    static constexpr auto RewardGil = " +
                                              std::to_string( pQuestData->gilReward ) + ";\n" : "";
  rewards += ( pQuestData->emoteReward != 0 ) ? "    static constexpr auto RewardEmote = " +
                                                std::to_string( pQuestData->emoteReward ) + ";\n" : "";
  rewards += ( pQuestData->actionReward != 0 ) ? "    static constexpr auto RewardAction = " +
                                                 std::to_string( pQuestData->actionReward ) + ";\n" : "";
  rewards += ( pQuestData->generalActionReward[ 0 ] != 0 ) ? "    static constexpr auto RewardGeneralAction1 = " +
                                                             std::to_string( pQuestData->generalActionReward[ 0 ] ) +
                                                             ";\n" : "";
  rewards += ( pQuestData->generalActionReward[ 1 ] != 0 ) ? "    static constexpr auto RewardGeneralAction2 = " +
                                                             std::to_string( pQuestData->generalActionReward[ 1 ] ) +
                                                             ";\n" : "";
  rewards += ( pQuestData->gCSeals != 0 ) ? "    static constexpr auto RewardGCSeals = " +
                                            std::to_string( pQuestData->gCSeals ) + ";\n" : "";
  rewards += ( pQuestData->otherReward != 0 ) ? "     static constexpr auto RewardOther = " +
                                                std::to_string( pQuestData->otherReward ) + ";\n" : "";
  rewards += ( pQuestData->reputationReward != 0 ) ? "    static constexpr auto RewardReputation = " +
                                                     std::to_string( pQuestData->reputationReward ) + ";\n" : "";
  rewards += ( pQuestData->tomestoneReward != 0 ) ? "    static constexpr auto RewardTomeType = " +
                                                    std::to_string( pQuestData->tomestoneReward ) + ";\n" : "";
  rewards += ( pQuestData->tomestoneCountReward != 0 ) ? "    static constexpr auto RewardTomeCount = " +
                                                         std::to_string( pQuestData->tomestoneCountReward ) + ";\n"
                                                       : "";
  rewards += ( pQuestData->instanceContentUnlock != 0 ) ? "    static constexpr auto InstancedContentUnlock = " +
                                                          std::to_string( pQuestData->instanceContentUnlock ) + ";\n"
                                                        : "";

  if( !pQuestData->itemReward0.empty() )
  {
    rewards += "    static constexpr auto RewardItem = { ";
    for( size_t ca = 0; ca < pQuestData->itemReward0.size(); ca++ )
    {
      rewards += std::to_string( pQuestData->itemReward0.at( ca ) );
      if( ca != pQuestData->itemReward0.size() - 1 )
      {
        rewards += ", ";
      }
    }
    rewards += " };\n";
  }

  if( !pQuestData->itemReward0.empty() )
  {
    rewards += "    static constexpr auto RewardItemCount = { ";
    for( size_t ca = 0; ca < pQuestData->itemCountReward0.size(); ca++ )
    {
      rewards += std::to_string( pQuestData->itemCountReward0.at( ca ) );
      if( ca != pQuestData->itemCountReward0.size() - 1 )
      {
        rewards += ", ";
      }
    }
    rewards += " };\n";
  }

  if( !pQuestData->itemReward1.empty() )
  {
    rewards += "    static constexpr auto RewardItemOptional = { ";
    for( size_t ca = 0; ca < pQuestData->itemReward1.size(); ca++ )
    {
      rewards += std::to_string( pQuestData->itemReward1.at( ca ) );
      if( ca != pQuestData->itemReward1.size() - 1 )
      {
        rewards += ", ";
      }
    }
    rewards += " };\n";
  }

  if( !pQuestData->itemCountReward1.empty() )
  {
    rewards += "    static constexpr auto RewardItemOptionalCount = { ";
    for( size_t ca = 0; ca < pQuestData->itemCountReward1.size(); ca++ )
    {
      rewards += std::to_string( pQuestData->itemCountReward1.at( ca ) );
      if( ca != pQuestData->itemCountReward1.size() - 1 )
      {
        rewards += ", ";
      }
    }
    rewards += " };\n";
  }

  bool hasERange = false;
  bool hasEmote = false;
  bool hasEnemies = false;
  bool hasActions = false;
  std::vector< uint32_t > enemy_ids;
  std::vector< std::string > action_names;
  std::vector< uint32_t > action_ids;
  std::vector< std::string > script_entities;
  std::string sentities = "    // Entities found in the script data of the quest\n";
  std::vector< std::string > enemy_strings;

  for( size_t ca = 0; ca < pQuestData->scriptInstruction.size(); ca++ )
  {
    if( ( pQuestData->scriptInstruction.at( ca ).find( "HOWTO" ) != std::string::npos ) ||
        ( pQuestData->scriptInstruction.at( ca ).find( "HOW_TO" ) != std::string::npos ) )
      continue;

    if( ( pQuestData->scriptInstruction.at( ca ).find( "EMOTENO" ) != std::string::npos ) ||
        ( pQuestData->scriptInstruction.at( ca ).find( "EMOTEOK" ) != std::string::npos ) )
      hasEmote = true;

    if( pQuestData->scriptInstruction.at( ca ).find( "ENEMY" ) != std::string::npos )
    {
      hasEnemies = true;
      enemy_ids.push_back( pQuestData->scriptArg.at( ca ) );
      enemy_strings.push_back( pQuestData->scriptInstruction.at( ca ) );
    }

    if( ( ( pQuestData->scriptInstruction.at( ca ).find( "ACTION0" ) != std::string::npos ) ||
        ( pQuestData->scriptInstruction.at( ca ).find( "ACTION1" ) != std::string::npos ) ||
        ( pQuestData->scriptInstruction.at( ca ).find( "ACTION2" ) != std::string::npos ) ) &&
          pQuestData->scriptInstruction.at( ca ).find( "_ACTION" ) == std::string::npos && 
	  pQuestData->scriptInstruction.at( ca ).find( "EVENT" ) == std::string::npos )
    {
      hasActions = true;
      action_ids.push_back( pQuestData->scriptArg.at( ca ) );
      action_names.push_back( pQuestData->scriptInstruction.at( ca ) );
    }


    if( !pQuestData->scriptInstruction.at( ca ).empty() )
      script_entities.push_back(
        pQuestData->scriptInstruction.at( ca ) + " = " + std::to_string( pQuestData->scriptArg.at( ca ) ) );
  }
  std::sort( script_entities.begin(), script_entities.end() );
  for( auto& entity : script_entities )
  {
    auto name = titleCase( entity );

    name.erase( std::remove_if( name.begin(), name.end(), []( const char c ) {
      return c == '_';
    }), name.end());

    sentities += "    static constexpr auto " + name + ";\n";
  }

  std::string additional = "// Quest Script: " + pQuestData->id + "\n";
  additional += "// Quest Name: " + pQuestData->name + "\n";
  additional += "// Quest ID: " + std::to_string( questId ) + "\n";
  additional += "// Start NPC: " + std::to_string( pQuestData->eNpcResidentStart ) + "\n";
  additional += "// End NPC: " + std::to_string( pQuestData->eNpcResidentEnd ) + "\n\n";

  std::string actionEntry;
  std::string scriptEntry;
  scriptEntry.reserve( 0xFFFF );
  scriptEntry += "  //////////////////////////////////////////////////////////////////////\n  // Event Handlers\n";

  scriptEntry += onTalkStr;

  if( hasERange )
  {
    scriptEntry += onWithinRangeStr;
  }

  if( hasEmote )
  {
    scriptEntry += onEmoteStr;
  }


  if( !enemy_ids.empty() )
    scriptEntry += std::string(
      "  void onBNpcKill( uint32_t npcId, Entity::Player& player )\n"
      "  {\n" 
      "    switch( npcId )\n"
      "    {\n" );

  for( auto enemy : enemy_strings )
  { 
    scriptEntry += "      case " + enemy + ": { break; }\n"; 
  }

  if( !enemy_ids.empty() )
    scriptEntry += std::string( "    }\n"
                                "  }\n" );

  if( !action_ids.empty() )
    actionEntry += std::string(
      "  void onEObjHit( uint32_t npcId, Entity::Player& player, uin32_t actionId )\n"
      "  {\n" 
      "    switch( actionId )\n"
      "    {\n" );

  for( auto action : action_names )
  { 
    actionEntry += "      case " + action + ": { break; }\n"; 
  }

  if( !action_ids.empty() )
    actionEntry += std::string( "    }\n"
                                "  }\n" );
  std::string constructor;
  constructor += std::string(
    "  private:\n"
    "    // Basic quest information \n" );
  constructor += questVarStr + "\n";
  constructor += seqStr + "\n";
  constructor += rewards + "\n";
  constructor += sentities + "\n";
  constructor += "  public:\n";
  constructor += "    " + className + "() : Sapphire::ScriptAPI::EventScript" + "( " + std::to_string( questId ) + " ){}; \n";
  constructor += "    ~" + className + "() = default; \n";

  std::string classString(
    "class " + className + " : public Sapphire::ScriptAPI::EventScript\n"
                           "{\n" +
    constructor +
    "\n" +
    scriptEntry +
    "\n" +
    actionEntry +
    "  private:\n" +
    sceneStr +
    "};\n\nEXPOSE_SCRIPT( " + className + " );"
  );

  std::ofstream outputFile;

  outputFile.open( "generated/" + className + ".cpp" );
  outputFile << header << additional << classString;
  outputFile.close();
}

int main( int argc, char** argv )
{

  Logger::init( "quest_parser" );

  bool unluac = false;
  // std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
  //std::string datLocation( "C:/Program Files (x86)/SquareEnix/FINAL FANTASY XIV - A Realm Reborn/game/sqpack" );
  //std::string datLocation( "C:/SquareEnix/FINAL FANTASY XIV - A Realm Reborn/game/sqpack" );
  
   std::string datLocation( "/home/mordred/sqpack" );
  if( argc > 1 )
    datLocation = std::string( argv[ 1 ] );
  if( argc > 2 )
    unluac = ( bool ) atoi( argv[ 2 ] );

  unluac = true;

  Logger::info( "Setting up generated EXD data" );
  if( !g_exdDataGen.init( datLocation ) )
  {
    std::cout << datLocation << "\n";
    Logger::fatal( "Error setting up EXD data " );
    std::cout << "Usage: quest_parser \"path/to/ffxiv/game/sqpack\" <1/0 unluac export toggle>\n";
    return 0;
  }

  xiv::dat::GameData data( datLocation );

  auto rows = g_exdDataGen.getQuestIdList();

  if( !fs::exists( "./generated" ) )
    fs::create_directory( "./generated" );

  Logger::info( "Export in progress" );

  uint32_t updateInterval = rows.size() / 20;
  uint32_t i = 0;
  for( const auto& row : rows )
  {
    Logger::info( "Generating {0}", row );
    auto questInfo = g_exdDataGen.get< Sapphire::Data::Quest >( row );

    if( questInfo->name.empty() || questInfo->id.empty() )
    {
      continue;
    }

    size_t pos_seperator = questInfo->id.find_first_of( "_" );

    std::string folder;

    if( pos_seperator != std::string::npos )
    {
      folder = questInfo->id.substr( pos_seperator + 1, 3 );
    }
    else
    {
      return 0;
    }


    const xiv::dat::Cat& test = data.getCategory( "game_script" );

    const std::string questPath = "game_script/quest/" + folder + "/" + questInfo->id + ".luab";

    const auto& test_file = data.getFile( questPath );
    auto& section = test_file->access_data_sections().at( 0 );
    int32_t size = *( uint32_t* ) &section[ 4 ];

    std::set< std::string > stringList;

    uint32_t offset = 0;

    std::ofstream outputFile1;
    outputFile1.open( "generated/" + questInfo->id + ".luab", std::ios::binary );
    outputFile1.write( &section[ 0 ], section.size() );
    outputFile1.close();
    if( unluac )
    {
      std::string command =
        std::string( "java -jar unluac_2015_06_13.jar " ) + "generated/" + questInfo->id + ".luab" + ">> " +
        "generated/" + questInfo->id + ".lua";
      if( system( command.c_str() ) == -1 )
      {
        Logger::error( "Error executing java command:\n {0}\nerrno: {1}", command, std::strerror( errno ) );
        return errno;
      }
    }
    for( ;; )
    {

      std::string entry( &section[ offset ] );
      offset += entry.size() + 1;

      if( entry.size() > 3
          && entry.find_first_not_of( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_-" ) ==
             std::string::npos )
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


    createScript( questInfo, stringList, row );
    ++i;
    if( i % updateInterval == 0 )
      std::cout << ".";
//break;
  }
  std::cout << "\nDone!";
  return 0;
}
