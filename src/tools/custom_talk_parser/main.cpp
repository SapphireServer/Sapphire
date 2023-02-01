#include <cstdint>
#include <fstream>
#include <iostream>
#include <locale>
#include <set>
#include <string>
#include <cstring>
#include <unordered_map>

#include <filesystem>

#include <Exd.h>
#include <ExdCat.h>
#include <ExdData.h>
#include <File.h>
#include <GameData.h>
#include <DatCat.h>

#include <Exd/ExdData.h>
#include <Logging/Logger.h>

#include <algorithm>

Sapphire::Data::ExdData g_exdDataGen;
namespace fs = std::filesystem;
using namespace Sapphire;

std::string javaPath("C:\\java.exe " );
std::string gamePath( "F:\\Client3.3\\game\\sqpack" );

const std::string onWithinRangeStr(
  "  void onWithinRange( World::Quest& quest, Entity::Player& player, uint64_t eRangeId, float x, float y, float z ) override\n"
  "  {\n"
  "  }\n\n"
);

const std::string onEmoteStr(
  "  void onEmote( World::Quest& quest, Entity::Player& player, uint64_t actorId, uint32_t emoteId ) override\n"
  "  {\n"
  "  }\n\n"
);

// https://stackoverflow.com/a/9745132
bool compareNat(const std::string& a, const std::string& b)
{
    if (a.empty())
        return true;
    if (b.empty())
        return false;
    if (std::isdigit(a[0]) && !std::isdigit(b[0]))
        return true;
    if (!std::isdigit(a[0]) && std::isdigit(b[0]))
        return false;
    if (!std::isdigit(a[0]) && !std::isdigit(b[0]))
    {
        if (std::toupper(a[0]) == std::toupper(b[0]))
            return compareNat(a.substr(1), b.substr(1));
        return (std::toupper(a[0]) < std::toupper(b[0]));
    }

    std::istringstream issa(a);
    std::istringstream issb(b);
    int ia, ib;
    issa >> ia;
    issb >> ib;
    if (ia != ib)
        return ia < ib;

    std::string anew, bnew;
    std::getline(issa, anew);
    std::getline(issb, bnew);
    return (compareNat(anew, bnew));
}

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

std::string titleCaseNoUnderscores( const std::string& str )
{
  std::string result = titleCase( str );

  result.erase( std::remove_if( result.begin(), result.end(), []( const char c ) {
    return c == '_';
  }), result.end());

  return result;
}

struct splito
{
  enum empties_t { empties_ok, no_empties };
};

template <typename Container>
Container& split(
        Container&                            result,
        const typename Container::value_type& s,
        const typename Container::value_type& delimiters,
        splito::empties_t                     empties = splito::empties_ok )
{
  result.clear();
  size_t current;
  size_t next = -1;
  do
  {
    if (empties == splito::no_empties)
    {
      next = s.find_first_not_of( delimiters, next + 1 );
      if (next == Container::value_type::npos) break;
      next -= 1;
    }
    current = next + 1;
    next = s.find_first_of( delimiters, current );
    result.push_back( s.substr( current, next - current ) );
  }
  while (next != Container::value_type::npos);
  return result;
}


const std::string& getItemNameFromExd( uint32_t id )
{
  static std::unordered_map< uint32_t, std::string > itemNames;
  static std::string invalid;

  if( itemNames.empty() )
  {
    auto nameIdList = g_exdDataGen.getIdList< Excel::Item >();
    for( auto id : nameIdList )
    {
      auto itemName = g_exdDataGen.getRow< Excel::Item >( id );
      if( itemName && !itemName->getString( itemName->data().Text.SGL ).empty() )
        itemNames[id] = itemName->getString( itemName->data().Text.SGL );
    }
  }
  if( auto name = itemNames.find( id ); name != itemNames.end() )
    return name->second;
  
  return invalid;
}

const std::string& getActorPosFromLevelExd( uint32_t id )
{
  static std::unordered_map< uint32_t, std::string > levelPositions;
  static std::string invalid;

  if( levelPositions.empty() )
  {
    auto levelIdList = g_exdDataGen.getIdList< Excel::Level >();
    for( auto id : levelIdList )
    {
      auto levelRow = g_exdDataGen.getRow< Excel::Level >( id );
      if( levelRow )
      {
        auto assetType = levelRow->data().eAssetType;
        // enpc, bnpc, eobj
        if( assetType != 8 && assetType != 9 && assetType != 45 )
          continue;
        std::string pos(" ( Pos: ");
        pos +=
          std::to_string( levelRow->data().TransX ) + " " +
          std::to_string( levelRow->data().TransY ) + " " +
          std::to_string( levelRow->data().TransZ ) + "  " +
          "Teri: " + std::to_string( levelRow->data().TerritoryType ) + " )";
        levelPositions.emplace( levelRow->data().BaseId, pos );
      }
    }
  }
  if( auto pos = levelPositions.find( id ); pos != levelPositions.end() )
    return pos->second;
  return invalid;
}

const std::string& getActorNameFromExd( uint32_t id )
{
  static std::unordered_map< uint32_t, std::string > bnpcNames, enpcNames, eobjNames;
  static std::string invalid;

  // bnpc
  if( id < 1000000 )
  {
    if( bnpcNames.empty() )
    {
      auto nameIdList = g_exdDataGen.getIdList< Excel::BNpcName >();
      for( auto id : nameIdList )
      {
        auto BNpcName = g_exdDataGen.getRow< Excel::BNpcName >( id );
        if( BNpcName && !BNpcName->getString( BNpcName->data().Text.SGL ).empty() )
          bnpcNames[id] = BNpcName->getString( BNpcName->data().Text.SGL );
      }
    }
    if( auto name = bnpcNames.find( id ); name != bnpcNames.end() )
      return name->second;
  }
  // enpcresident
  else if( id < 2000000 )
  {
    if( enpcNames.empty() )
    {
      auto nameIdList = g_exdDataGen.getIdList< Excel::ENpcResident >();
      for( auto id : nameIdList )
      {
        auto eNpcName = g_exdDataGen.getRow< Excel::ENpcResident >( id );
        if( eNpcName  && !eNpcName->getString( eNpcName->data().Text.SGL ).empty() )
          enpcNames[id] = eNpcName->getString( eNpcName->data().Text.SGL );
      }
    }
    if( auto name = enpcNames.find( id ); name != enpcNames.end() )
      return name->second;
  }
  // eobj
  else
  {
    if( eobjNames.empty() )
    {
      auto nameIdList = g_exdDataGen.getIdList< Excel::EObj >();
      for( auto id : nameIdList )
      {
        auto eObjName = g_exdDataGen.getRow< Excel::EObj >( id );
        if( eObjName && !eObjName->getString( eObjName->data().Text.SGL ).empty() )
          eobjNames[id] = eObjName->getString( eObjName->data().Text.SGL );
      }
    }
    if( auto name = eobjNames.find( id ); name != eobjNames.end() )
      return name->second;
  }
  return invalid;
}


void
createScript( std::shared_ptr< Excel::ExcelStruct< Excel::CustomTalk > >& pQuestData, std::set< std::string >& additionalList, int questId, std::vector< std::string >& functions )
{
  std::string header(
    "// This is an automatically generated C++ script template\n"
    "// Content needs to be added by hand to make it function\n"
    "// In order for this script to be loaded, move it to the correct folder in <root>/scripts/\n"
    "\n"
    "#include <Actor/Player.h>\n"
    "#include \"Manager/EventMgr.h\"\n"
    "#include <ScriptObject.h>\n"
    "#include <Service.h>\n\n"
  );

  for( size_t ca = 0; ca < 30; ca++ )
  {
    auto name = pQuestData->getString( pQuestData->data().Define[ ca ].Name );

  }

  std::vector< std::string > scenes;
  std::vector< std::string > sequences;
  std::vector< std::string > vars;
  bool hasEventItem = false;

  for( const auto& function : functions )
  {
    if( function.find( "GetEventItems" ) != std::string::npos )
    {
      hasEventItem = true;
    }
  }
  for( auto& entry : additionalList )
  {
    if( entry.find( "OnScene" ) != std::string::npos )
    {
      scenes.push_back( entry );
    }
    else if( entry.find( "SEQ" ) != std::string::npos )
    {
      if( entry.find( "SEQ_OFFER" ) == std::string::npos )
        sequences.push_back( entry );
    }
    else if( entry.find( "Flag" ) != std::string::npos ||
             entry.find( "QuestUI" ) != std::string::npos )
    {
      vars.push_back( entry.substr( std::string( "GetQuest" ).length() ) );
    }
  }

  std::size_t splitPos( pQuestData->getString( pQuestData->data().Script ).find( '_' ) );
  std::string className( pQuestData->getString( pQuestData->data().Script ).substr( 0, splitPos ) );

  std::string todoInfo;
  for( int i = 0; i < 23; ++i )
  {
  //  if( pQuestData->data().QuestTodo[ i ].CountableNum == 0 && pQuestData->data().QuestTodo[ i ].TodoSequence == 0 )
  //    break;
  //  todoInfo += std::string( "    /// Countable Num: " + std::to_string( pQuestData->data().QuestTodo[ i ].CountableNum ) + " Seq: " +
  //  std::to_string( pQuestData->data().QuestTodo[ i ].TodoSequence ) + " Event: " + std::to_string( pQuestData->data().EventListener[i].Event ) +
  //  " Listener: " + std::to_string( pQuestData->data().EventListener[i].Listener ) + "\n" );
  }

  //className = "Quest" + className;
  std::string sceneStr( "  //////////////////////////////////////////////////////////////////////\n"
                        "  // Available Scenes in this event, not necessarly all are used\n" );


  for( auto& scene : scenes )
  {
    if( scene.find( "OnScene" ) != std::string::npos )
    {
      std::string sceneName = scene.substr( 2 );
      std::string sceneId = scene.substr( 7 );

      std::size_t numOff = sceneId.find_first_not_of( "0" );
      sceneId = numOff != std::string::npos ? sceneId.substr( numOff ) : "0";

      std::string sceneFlags = "NONE";
      bool questOffer = false;
      bool questReward = false;

      for( const auto& function : functions )
      {
        if( function.find( sceneName ) != std::string::npos )
        {
          /// SCENE FLAGS
          if( function.find( "CutScene" ) != std::string::npos || function.find( "Cutscene" ) != std::string::npos )
          {
            sceneFlags = "FADE_OUT | CONDITION_CUTSCENE | HIDE_UI";
          }
          else if( function.find( "FadeIn" ) != std::string::npos )
          {
            sceneFlags = "FADE_OUT | HIDE_UI";
          }
          else
          {
            sceneFlags = "NONE";
          }
          /// SCENE CONTENT
          if( function.find( "QuestOffer" ) != std::string::npos )
          {
            questOffer = true;
          }
          if( function.find( "QuestReward" ) != std::string::npos )
          {
            questReward = true;
          }
          break;
        }
      }

      sceneStr += std::string(
              "  //////////////////////////////////////////////////////////////////////\n\n"
              "  void " + sceneName + "( Entity::Player& player )\n"
                                      "  {\n"
                                      "    eventMgr().playScene( player, getId(), " + sceneId + ", " + sceneFlags + ", bindSceneReturn( &" + className + "::" + sceneName +
              "Return ) );\n"
              "  }\n\n"
              "  void " + sceneName + "Return( Entity::Player& player, const Event::SceneResult& result )\n" +
              "  {\n"
              "  }\n\n"
      );
    }
  }

  std::string seqStr;
  seqStr.reserve( 0xFFF );
  seqStr += todoInfo;

  bool hasERange = false;
  bool hasEmote = false;
  bool hasEnemies = false;
  bool hasActions = false;
  std::vector< uint32_t > enemy_ids;
  std::vector< std::string > action_names;
  std::vector< uint32_t > action_ids;
  std::vector< std::string > script_entities;
  std::string sentities = "    // Entities found in the script data of the event\n";
  std::vector< std::string > enemy_strings;
  std::vector< std::string > actorList;
  for( size_t ca = 0; ca < 30; ca++ )
  {
    auto name = pQuestData->getString( pQuestData->data().Define[ ca ].Name );

    if( ( name.find( "HOWTO" ) != std::string::npos ) ||
        ( name.find( "HOW_TO" ) != std::string::npos ) ||
        ( name.find( "LOC_MARK" ) != std::string::npos ) ||
        ( name.find( "LocMark" ) != std::string::npos ) )
      continue;

    if( ( name.find( "EMOTENO" ) != std::string::npos ) ||
        ( name.find( "EMOTEOK" ) != std::string::npos ) )
      hasEmote = true;

    if( name.find( "ENEMY" ) != std::string::npos )
    {
      hasEnemies = true;
      enemy_ids.push_back( pQuestData->data().Define[ ca ].Value );
      enemy_strings.push_back( name );
    }

    if( ( ( name.find( "ACTION0" ) != std::string::npos ) ||
          ( name.find( "ACTION1" ) != std::string::npos ) ||
          ( name.find( "ACTION2" ) != std::string::npos ) ) &&
            name.find( "_ACTION" ) == std::string::npos && name.find( "EVENT" ) == std::string::npos )
    {
      hasActions = true;
      action_ids.push_back( pQuestData->data().Define[ ca ].Value );
      action_names.push_back( name );
    }

    if( !name.empty() )
    {
      auto nameStripped = titleCaseNoUnderscores( name );
      if( nameStripped.substr( 0, 5 ) == "Actor" )
        actorList.push_back( titleCaseNoUnderscores( name ) );

      std::transform( nameStripped.begin(), nameStripped.end(), nameStripped.begin(), ::tolower);
      // comment actor names and positions if possible
      if( nameStripped.find( "acto" ) != std::string::npos || nameStripped.find( "enemy" ) != std::string::npos
        || nameStripped.find( "eobj" ) != std::string::npos || nameStripped.find( "npc" ) != std::string::npos )
      { 
        script_entities.push_back( name + " = " + std::to_string( pQuestData->data().Define[ ca ].Value ) );
        //
        // + "; // " +
        //  getActorNameFromExd( pQuestData->data().Define[ca].Value ) /*+ getActorPosFromLevelExd( pQuestData->data().Define[ca].Value ) */);
      }
      // comment item names
      else if( nameStripped.find( "ritem" ) != std::string::npos )
      { 
        script_entities.push_back( name + " = " + std::to_string( pQuestData->data().Define[ ca ].Value ) + "; // " + getItemNameFromExd( pQuestData->data().Define[ca].Value ) );
      }
      else
        script_entities.push_back(
              name + " = " + std::to_string( pQuestData->data().Define[ ca ].Value ) + ";");
    }
  }


  std::sort( script_entities.begin(), script_entities.end(), compareNat );
  for( auto& entity : script_entities )
  {
    auto name = titleCaseNoUnderscores( entity );
    sentities += "    static constexpr auto " + name + "\n";

  }

  std::string additional = "// Script: " + pQuestData->getString( pQuestData->data().Script ) + "\n";
  additional += "// Event Name: " + pQuestData->getString( pQuestData->data().Text.Name ) + "\n";
  additional += "// Event ID: " + std::to_string( questId ) + "\n";
 // additional += "// Start NPC: " + std::to_string( pQuestData->data(). ) + " (" + getActorNameFromExd( pQuestData->data().Client ) + ")\n";
 // additional += "// End NPC: " + std::to_string( pQuestData->data().Finish ) + " (" + getActorNameFromExd( pQuestData->data().Finish ) + ")\n\n";

  additional += "using namespace Sapphire;\n\n";

  std::string actionEntry;
  std::string scriptEntry;
  scriptEntry.reserve( 0xFFFF );
  scriptEntry += "  //////////////////////////////////////////////////////////////////////\n  // Event Handlers\n";

  scriptEntry +=
  "  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override\n"
  "  {\n" ;
  if( !actorList.empty() )
  {
    scriptEntry += "    switch( actorId )\n";
    scriptEntry += "    {\n";
    for( auto &actor: actorList )
    {
      scriptEntry += "      case " + actor +":\n";
      scriptEntry += "      {\n";
      scriptEntry += "        break;\n";
      scriptEntry += "      }\n";
    }
    scriptEntry += "    }\n";
  }

  scriptEntry += "  }\n\n";


  if( hasERange )
  {
    scriptEntry += onWithinRangeStr;
  }

  if( hasEmote )
  {
    scriptEntry += onEmoteStr;
  }

  if( hasEventItem )
  {
    scriptEntry +=  "  void onEventItem( Entity::Player& player, uint64_t actorId ) override\n"
            "  {\n"
            "  }\n\n" ;
  }

  if( !enemy_ids.empty() )
    scriptEntry += std::string(
      "  void onBNpcKill( Entity::BNpc& bnpc, Entity::Player& player ) override\n"
      "  {\n" 
      "    switch( bnpc->getBNpcNameId() )\n"
      "    {\n" );

  for( auto enemy : enemy_strings )
  { 
    scriptEntry += "      case " + titleCaseNoUnderscores( enemy ) + ": { break; }\n";
  }

  if( !enemy_ids.empty() )
    scriptEntry += std::string( "    }\n"
                                "  }\n" );

  if( !action_ids.empty() )
    actionEntry += std::string(
      "  void onEObjHit( uint32_t npcId, Entity::Player& player, uint32_t actionId )\n"
      "  {\n" 
      "    switch( actionId )\n"
      "    {\n" );

  for( auto action : action_names )
  { 
    actionEntry += "      case " + titleCaseNoUnderscores( action ) + ": { break; }\n";
  }

  if( !action_ids.empty() )
    actionEntry += std::string( "    }\n"
                                "  }\n" );
  std::string constructor;
  constructor += std::string(
    "  private:\n"
    "    // Basic event information \n" );
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

void parseIf( std::ifstream& t, std::string& functionBlock, std::string& line )
{
  if( line.find( " if " ) != std::string::npos )
  {
    while( true )
    {
      std::getline(t, line );
      functionBlock.append( line );
      if( line.find( " end" ) != std::string::npos )
        break;

      parseIf( t, functionBlock, line );
    }
  }
}

int main( int argc, char** argv )
{

  Logger::init( "custom_talk_parser" );

  bool unluac = false;

  if( argc > 1 )
    gamePath = std::string( argv[ 1 ] );
  if( argc > 2 )
    unluac = ( bool ) atoi( argv[ 2 ] );
  if( argc > 3)
    javaPath = std::string( argv[ 3 ] );

  unluac = true;

  Logger::info( "Setting up generated EXD data" );
  if( !g_exdDataGen.init( gamePath ) )
  {
    std::cout << gamePath << "\n";
    Logger::fatal( "Error setting up EXD data " );
    std::cout << "Usage: quest_parser \"path/to/ffxiv/game/sqpack\" <1/0 unluac export toggle>\n";
    return 0;
  }

  xiv::dat::GameData data( gamePath );

  auto rows = g_exdDataGen.getIdList< Excel::CustomTalk >();

  if( !fs::exists( "./generated" ) )
    fs::create_directory( "./generated" );

  Logger::info( "Export in progress" );

  auto updateInterval = rows.size() / 20;
  uint32_t i = 0;
  for( const auto& row : rows )
  {
    Logger::info( "Generating {0}", row );
    auto questInfo = g_exdDataGen.getRow< Excel::CustomTalk >( row );

    if( questInfo->getString( questInfo->data().Script ).empty() )
    {
      continue;
    }

    size_t pos_seperator = questInfo->getString( questInfo->data().Script ).find_first_of( "_" );

    std::string folder;

    if( pos_seperator != std::string::npos )
    {
      folder = questInfo->getString( questInfo->data().Script ).substr( pos_seperator + 1, 3 );
    }
    else
    {
      return 0;
    }


    const xiv::dat::Cat& test = data.getCategory( "game_script" );

    const std::string questPath = "game_script/custom/" + folder + "/" + questInfo->getString( questInfo->data().Script ) + ".luab";

    try
    {
      const auto& test_file = data.getFile( questPath );
    }
    catch( std::exception& e)
    {
      Logger::error( "Skipping {}", questPath );
      continue;
    }
    const auto& test_file = data.getFile( questPath );
    auto& section = test_file->access_data_sections().at( 0 );
    int32_t size = *( uint32_t* ) &section[ 4 ];

    std::set< std::string > stringList;

    uint32_t offset = 0;

    std::ofstream outputFile1;
    outputFile1.open( "generated/" + questInfo->getString( questInfo->data().Script ) + ".luab", std::ios::binary );
    outputFile1.write( &section[ 0 ], section.size() );
    outputFile1.close();
    std::vector< std::string > functions;
    if( unluac )
    {
      std::string command =
        javaPath + " -jar unluac_2015_06_13.jar " + "generated/" + questInfo->getString( questInfo->data().Script ) + ".luab" + ">> " +
        "generated/" + questInfo->getString( questInfo->data().Script ) + ".lua";
      if( system( command.c_str() ) == -1 )
      {
        Logger::error( "Error executing java command:\n {0}\nerrno: {1}", command, std::strerror( errno ) );
        return errno;
      }
     // std::ifstream t("generated/" + questInfo->getString( questInfo->data().Script ) + ".lua" );
    //  std::stringstream buffer;
    //  buffer << t.rdbuf();
    //  std::string contents = buffer.str();





      std::ifstream t;
      t.open("generated/" + questInfo->getString( questInfo->data().Script ) + ".lua" );
      std::string buffer;
      std::string line;
      std::getline(t, line );
      while( t )
      {
        std::getline(t, line );
        std::string functionBlock;
        if( line.find( "function" ) != std::string::npos )
        {
          functionBlock.append( line );
          while( true )
          {
            std::getline(t, line);
            functionBlock.append( line );
            if( line.find( "end" ) != std::string::npos )
            {
              functions.push_back( functionBlock );
              break;
            }
            parseIf( t, functionBlock, line );
          }
        }
      }
      t.close();

      //split( functions, contents, "function" );

    }
    for( ;; )
    {

      std::string entry( &section[ offset ] );
      offset += static_cast< uint32_t >( entry.size() + 1 );

      if( entry.size() > 3
          && entry.find_first_not_of( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-" ) ==
             std::string::npos )
      {
        if( entry.find( "SEQ" ) != std::string::npos
            || entry.find( "QuestUI" ) != std::string::npos
            || entry.find( "OnScene" ) != std::string::npos
            || entry.find( "Flag" ) != std::string::npos
            || entry.find( "ACTOR" ) != std::string::npos && entry.find( "_ACTOR" ) == std::string::npos )
          if( entry.find( "HOWTO" ) == std::string::npos )
            stringList.insert( entry );
      }

      if( offset >= section.size() )
        break;
    }


    createScript( questInfo, stringList, row, functions );
    ++i;
    if( i % updateInterval == 0 )
      std::cout << ".";
//break;
  }
  std::cout << "\nDone!";
  return 0;
}
