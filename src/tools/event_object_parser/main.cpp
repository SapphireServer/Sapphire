#include <stdio.h>
#include <cstdint>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include <set>
#include <variant>
#include <Util/Util.h>

#include <Exd/StructureDef/pcb.h>
#include <Exd/StructureDef/lgb.h>
#include <Exd/StructureDef/sgb.h>

#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>

#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

#include <experimental/filesystem>


#include <Util/CrashHandler.h>

Sapphire::Common::Util::CrashHandler crashHandler;

Sapphire::Data::ExdDataGenerated g_exdData;

using namespace Sapphire;

namespace fs = std::experimental::filesystem;

// garbage to ignore models
bool ignoreModels = false;
std::string gamePath( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );
//std::string gamePath( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
std::unordered_map< uint32_t, std::string > eobjNameMap;
std::unordered_map< uint16_t, std::vector< std::pair< uint16_t, std::string > > > zoneInstanceMap;
uint32_t zoneId;

struct instanceContent
{
  uint32_t id;
  std::string name;
  std::string zoneName;
  uint8_t type;
};

std::vector< instanceContent > contentList;

std::set< std::string > zoneDumpList;

xiv::dat::GameData* gameData = nullptr;
xiv::exd::ExdData* eData = nullptr;

using namespace std::chrono_literals;

void initExd( const std::string& gamePath )
{
  gameData = gameData ? gameData : new xiv::dat::GameData( gamePath );
  eData = eData ? eData : new xiv::exd::ExdData( *gameData );
}

int parseBlockEntry( char* data, std::vector< PCB_BLOCK_ENTRY >& entries, int gOff )
{
  int offset = 0;
  bool isgroup = true;
  while( isgroup )
  {
    PCB_BLOCK_ENTRY block_entry;
    memcpy( &block_entry.header, data + offset, sizeof( block_entry.header ) );
    isgroup = block_entry.header.type == 0x30;

    //printf( " BLOCKHEADER_%X: type: %i, group_size: %i\n", gOff + offset, block_entry.header.type, block_entry.header.group_size );

    if( isgroup )
    {
      parseBlockEntry( data + offset + 0x30, entries, gOff + offset );
      offset += block_entry.header.group_size;
    }
    else
    {
      /*   printf( "\tnum_v16: %i, num_indices: %i, num_vertices: %i\n\n",
                 block_entry.header.num_v16, block_entry.header.num_indices, block_entry.header.num_vertices );*/
      int doffset = sizeof( block_entry.header ) + offset;
      uint16_t block_size = sizeof( block_entry.header ) +
                            block_entry.header.num_vertices * 3 * 4 +
                            block_entry.header.num_v16 * 6 +
                            block_entry.header.num_indices * 6;

      if( block_entry.header.num_vertices != 0 )
      {
        block_entry.data.vertices.resize( block_entry.header.num_vertices );

        int32_t size_vertexbuffer = block_entry.header.num_vertices * 3;
        memcpy( &block_entry.data.vertices[ 0 ], data + doffset, size_vertexbuffer * 4 );
        doffset += size_vertexbuffer * 4;
      }
      if( block_entry.header.num_v16 != 0 )
      {
        block_entry.data.vertices_i16.resize( block_entry.header.num_v16 );
        int32_t size_unknownbuffer = block_entry.header.num_v16 * 6;
        memcpy( &block_entry.data.vertices_i16[ 0 ], data + doffset, size_unknownbuffer );
        doffset += block_entry.header.num_v16 * 6;
      }
      if( block_entry.header.num_indices != 0 )
      {
        block_entry.data.indices.resize( block_entry.header.num_indices );
        int32_t size_indexbuffer = block_entry.header.num_indices * 12;
        memcpy( &block_entry.data.indices[ 0 ], data + doffset, size_indexbuffer );
        doffset += size_indexbuffer;
      }
      entries.push_back( block_entry );
    }
  }

  return 0;
}

std::string zoneNameToPath( const std::string& name )
{
  std::string path;
  bool found = false;

  auto teriIdList = g_exdData.getTerritoryTypeIdList();
  for( auto teriId : teriIdList )
  {
    auto teri = g_exdData.get< Sapphire::Data::TerritoryType >( teriId );
    if( !teri )
      continue;
    
    auto teriName = teri->name;
    auto teriPath = teri->bg;
    
    if( teriName.empty() )
      continue;
    
    if( Sapphire::Util::toLowerCopy( name ) == Sapphire::Util::toLowerCopy( teriName ) )
    {
      path = teriPath;
      found = true;
      break;
    }
  }

  if( found )
  {
    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );
    Logger::debug( "Found path for {0}: {1}", name, path );
  }
  else
  {
    throw std::runtime_error( "Unable to find path for " + name );
  }

  return path;
}

void loadEobjNames()
{
  auto& cat = eData->get_category( "EObjName" );
  auto exd = static_cast< xiv::exd::Exd >( cat.get_data_ln( xiv::exd::Language::en ) );
  for( auto& row : exd.get_rows() )
  {
    auto id = row.first;
    auto& fields = row.second;
    auto name = std::get< std::string >( fields.at( 0 ) );

    if( !name.empty() )
      eobjNameMap[ id ] = name;
  }
}

void writeEobjEntry( std::ofstream& out, LGB_ENTRY* pObj )
{
  static std::string mapRangeStr( "\"MapRange\", " );
  static std::string eobjStr( "\"EObj\", " );

  uint32_t id;
  uint32_t unknown = 0, unknown2 = 0;
  std::string name;
  std::string typeStr;
  uint32_t eobjlevelHierachyId = 0;

  if( pObj->getType() == LgbEntryType::EventObject )
  {
    auto pEobj = reinterpret_cast< LGB_EOBJ_ENTRY* >( pObj );
    id = pEobj->header.eobjId;
    unknown = pEobj->header.unknown;
    name = eobjNameMap[ id ];
    typeStr = eobjStr;
    eobjlevelHierachyId = pEobj->header.levelHierachyId;
  }
  else if( pObj->getType() == LgbEntryType::MapRange )
  {
    auto pMapRange = reinterpret_cast< LGB_MAPRANGE_ENTRY* >( pObj );
    id = pMapRange->header.unknown;
    unknown = pMapRange->header.unknown2;
    unknown2 = pMapRange->header.unknown3;
    typeStr = mapRangeStr;
  }

  std::string outStr(
    std::to_string( id ) + ", " + typeStr + "\"" + name + "\", " +
    std::to_string( pObj->header.translation.x ) + ", " + std::to_string( pObj->header.translation.y ) + ", " +
    std::to_string( pObj->header.translation.z ) +
    ", " + std::to_string( eobjlevelHierachyId ) + "\n"
  );
  out.write( outStr.c_str(), outStr.size() );
}

void loadAllInstanceContentEntries()
{
  auto cfcIdList = g_exdData.getContentFinderConditionIdList();
  for( auto cfcId : cfcIdList )
  {
    auto cfc = g_exdData.get< Sapphire::Data::ContentFinderCondition >( cfcId );
    if( !cfc )
      continue;
    
    uint16_t teriId = cfc->territoryType;
    auto tt = g_exdData.get< Sapphire::Data::TerritoryType >( teriId );
    if( !tt )
      continue;
    uint16_t contentId = cfc->content;
    uint8_t type;
    std::string name;
    
    if( cfc->contentLinkType == 1 )
    {
      auto ic = g_exdData.get< Sapphire::Data::InstanceContent >( cfc->content );
      if( !ic )
        continue;
      type = ic->instanceContentType;
      name = ic->name;
    }
    else if( cfc->contentLinkType == 5 )
    { 
      auto qb = g_exdData.get< Sapphire::Data::QuestBattle >( cfc->content );
      if( !qb )
        continue;
      auto q = g_exdData.get< Sapphire::Data::Quest >( qb->quest );
      if( !q )
        continue;
      type = 7;
      name = q->name;
    }
    else
      continue;
    
    if( name.empty() )
      continue;
    
    auto i = 0;
    while( ( i = name.find( ' ' ) ) != std::string::npos )
      name = name.replace( name.begin() + i, name.begin() + i + 1, { '_' } );
    
    zoneDumpList.emplace( tt->name );

    std::string remove = ",★_ '()[]-\xae\x1a\x1\x2\x1f\x1\x3.:";
    Sapphire::Util::eraseAllIn( name, remove );
    name[ 0 ] = toupper( name[ 0 ] );
    contentList.push_back( { contentId, name, tt->name, type } );
  }
}

int main( int argc, char* argv[] )
{
  auto startTime = std::chrono::system_clock::now();
  auto entryStartTime = std::chrono::system_clock::now();

  Logger::init( "Event Object Parser" );

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( gamePath ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }

  std::vector< std::string > argVec( argv + 1, argv + argc );
  // todo: support expansions
  std::string zoneName = "r2t2";
  ignoreModels = true;
  if( argc > 1 )
  {
    zoneName = argv[ 1 ];
    if( argc > 2 )
    {
      std::string tmpPath( argv[ 2 ] );
      if( !tmpPath.empty() )
        gamePath = argv[ 2 ];
    }
  }

  std::map< uint8_t, std::string > instanceContentTypeMap;
  instanceContentTypeMap[ 0 ] = "";
  instanceContentTypeMap[ 1 ] = "raids";
  instanceContentTypeMap[ 2 ] = "dungeons";
  instanceContentTypeMap[ 3 ] = "guildhests";
  instanceContentTypeMap[ 4 ] = "trials";
  instanceContentTypeMap[ 5 ] = "pvp/thefeast";
  instanceContentTypeMap[ 6 ] = "pvp";
  instanceContentTypeMap[ 7 ] = "questbattles";
  instanceContentTypeMap[ 8 ] = "hallofthenovice";
  instanceContentTypeMap[ 9 ] = "deepdungeon";
  instanceContentTypeMap[ 10 ] = "treasurehunt";
  instanceContentTypeMap[ 11 ] = "events";
  instanceContentTypeMap[ 12 ] = "pvp/rivalwings";
  instanceContentTypeMap[ 13 ] = "maskedcarnivale"; // todo: better name?
  instanceContentTypeMap[ 14 ] = "goldsaucer/mahjong";
  instanceContentTypeMap[ 15 ] = "goldsaucer";

  if( !fs::exists( "instance.tmpl" ) )
    throw std::runtime_error( "instance.tmpl is missing in working directory" );

  try
  {
    initExd( gamePath );
  }
  catch( std::runtime_error error )
  {
    std::cout << error.what();
  }
  
  loadAllInstanceContentEntries();

  auto& catQuestBattle = eData->get_category( "QuestBattle" );
  auto questBattleData = static_cast< xiv::exd::Exd >( catQuestBattle.get_data_ln( xiv::exd::Language::none ) );

  for( auto entry : contentList )
  {
    std::string eobjects = "";
    entryStartTime = std::chrono::system_clock::now();
    zoneName = entry.zoneName;
    try
    {
      const auto& zonePath = zoneNameToPath( zoneName );

      std::string listPcbPath( zonePath + "/collision/list.pcb" );
      std::string bgLgbPath( zonePath + "/level/bg.lgb" );
      std::string planmapLgbPath( zonePath + "/level/planmap.lgb" );
      std::string planeventLgbPath( zonePath + "/level/planevent.lgb" );
      std::string collisionFilePath( zonePath + "/collision/" );
      std::string plannerFilePath( zonePath + "/level/planner.lgb" );
      std::string lcbFilePath( zonePath + "/level/" + zoneName + ".lcb" );
      std::string svbFilePath( zonePath + "/level/" + zoneName + ".svb" );
      std::vector< char > section;
      std::vector< char > section1;
      std::vector< char > section2;
      std::vector< char > section3;

      const xiv::dat::Cat& test = gameData->getCategory( "bg" );

      auto test_file = gameData->getFile( bgLgbPath );
      section = test_file->access_data_sections().at( 0 );

      auto planmap_file = gameData->getFile( planmapLgbPath );
      section2 = planmap_file->access_data_sections().at( 0 );

      auto planeventFile = gameData->getFile( planeventLgbPath );
      section3 = planeventFile->access_data_sections().at( 0 );

      auto exportFile = [&]( const std::string& path )
      {
        try
        {
          auto file = gameData->getFile( path );

          if( !file )
          {
            return;
          }
          auto p = fs::path( path );
          fs::create_directories( p.parent_path() );
          file->exportToFile( p );
        }
        catch( const std::exception& ex ) {}
      };

      exportFile( planeventLgbPath );
      exportFile( plannerFilePath );
      exportFile( lcbFilePath );
      exportFile( svbFilePath );

      std::vector< std::string > stringList;

      uint32_t offset1 = 0x20;

      loadEobjNames();

      LGB_FILE bgLgb( &section[ 0 ], "bg" );
      LGB_FILE planmapLgb( &section2[ 0 ], "planmap" );
      LGB_FILE planeventLgb( &section3[ 0 ], "planevent" );

      std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb, planeventLgb };
      uint32_t max_index = 0;

      //if( ignoreModels )
      {
        std::map< std::string, SGB_FILE > sgbFiles;

        auto loadSgbFile = [ & ]( const std::string& fileName )->bool
        {
          SGB_FILE sgbFile;
          try
          {
            char* dataSection = nullptr;
            //std::cout << fileName << " ";
            auto file = gameData->getFile( fileName );
            auto sections = file->get_data_sections();
            dataSection = &sections.at( 0 )[ 0 ];
            sgbFile = SGB_FILE( &dataSection[ 0 ] );
            sgbFiles.insert( std::make_pair( fileName, sgbFile ) );
            return true;
          }
          catch( std::exception& e )
          {
            std::cout << "[Error] " << "Unable to load SGB " << fileName << "\n\tError:\n\t" << e.what() << "\n";
            sgbFiles.insert( std::make_pair( fileName, sgbFile ) );
          }
          return false;
        };

        std::cout << "[Info] " << ( ignoreModels ? "Dumping MapRange and EObj" : "Writing obj file " ) << "\n";
        uint32_t totalGroups = 0;
        uint32_t totalGroupEntries = 0;
        std::cout << zoneName << "\n";
        uint32_t count = 0;
        for( const auto& lgb : lgbList )
        {
          std::map< std::string, uint32_t > nameMap;
          for( const auto& group : lgb.groups )
          {
            //std::cout << "\t" << group.name << " Size " << group.header.entryCount << "\n";
            totalGroups++;
            for( const auto& pEntry : group.entries )
            {
              auto pGimmick = dynamic_cast< LGB_GIMMICK_ENTRY* >( pEntry.get() );
              auto pBgParts = dynamic_cast< LGB_BGPARTS_ENTRY* >( pEntry.get() );

              std::string fileName( "" );
              fileName.resize( 256 );
              totalGroupEntries++;

              if( pEntry->getType() == LgbEntryType::EventObject )
              {
                auto pObj = pEntry.get();
                static std::string eobjStr( "\"EObj\", " );

                uint32_t id;
                uint32_t unknown = 0, unknown2 = 0;
                std::string name;
                std::string typeStr;
                uint32_t eobjlevelHierachyId = 0;

                auto pEobj = reinterpret_cast< LGB_EOBJ_ENTRY* >( pObj );
                id = pEobj->header.eobjId;
                unknown = pEobj->header.unknown;


                typeStr = eobjStr;
                eobjlevelHierachyId = pEobj->header.levelHierachyId;

                std::string states = "";
                std::string gimmickName = "";
                for( const auto& pEntry1 : group.entries )
                {
                  auto pGObj = pEntry1.get();
                  if( pGObj->getType() == LgbEntryType::Gimmick )
                  {
                    if( pGObj->header.unknown == pEobj->header.levelHierachyId )
                    {
                      auto pGObjR = reinterpret_cast< LGB_GIMMICK_ENTRY* >( pGObj );
                      char* dataSection = nullptr;
                      //std::cout << fileName << " ";

                      auto file = gameData->getFile( pGObjR->gimmickFileName );
                      auto sections = file->get_data_sections();
                      dataSection = &sections.at( 0 )[ 0 ];
                      auto sgbFile = SGB_FILE( &dataSection[ 0 ] );

                      auto pos = pGObjR->gimmickFileName.find_last_of( "/" );

                      if( pos != std::string::npos )
                      {
                        name = pGObjR->gimmickFileName.substr( pos + 1 );
                        name = name.substr( 0, name.length() - 4 );
                        gimmickName = name;
                      }

                      if( sgbFile.stateEntries.size() > 0 )
                      {
                        states = "    // States -> ";
                        for( auto entries1 : sgbFile.stateEntries )
                        {
                          states += entries1.name + " (id: " + std::to_string( entries1.header.id ) + ") ";
                        }
                        states += "\n";
                      }

                      break;

                    }
                  }
                }
                int state = 4;

                if( eobjNameMap.find( id ) != eobjNameMap.end() )
                {
                  name = eobjNameMap[ id ];
                  std::string remove = "\",★_ '()[]-\xae\x1a\x1\x2\x1f\x1\x3.:";
                  Sapphire::Util::eraseAllIn( name, remove );

                  name[ 0 ] = toupper( name[ 0 ] );
                }
                if( name.empty() )
                  name = "unknown_" + std::to_string( count++ );

                if( id == 2000182 || gimmickName == "sgvf_w_lvd_b0095" )
                {
                  state = 5;
                  name = "Entrance";
                }

                auto count1 = 0;
                if( nameMap.find( name ) == nameMap.end() )
                {
                  nameMap[ name ] = 0;
                }
                else
                {
                  nameMap[ name ] = ++nameMap[ name ];
                  count1 = nameMap[ name ];
                }

                if( count1 > 0 )
                  name = name + "_" + std::to_string( count1 );

                eobjects += "    instance.registerEObj( \"" + name + "\", " + std::to_string( id ) +
                            ", " + std::to_string( eobjlevelHierachyId ) + ", " + std::to_string( state ) +
                            ", " +
                            "{ " + std::to_string( pObj->header.translation.x ) + "f, "
                            + std::to_string( pObj->header.translation.y ) + "f, "
                            + std::to_string( pObj->header.translation.z ) + "f }, " +
                            std::to_string( pObj->header.scale.x ) + "f, " +

                            // for whatever reason, the rotation inside the sgbs is the inverse of what the game uses
                            std::to_string( pObj->header.rotation.y * -1.f ) + "f ); \n" + states;


                std::string outStr(
                  std::to_string( id ) + ", " + typeStr + "\"" + name + "\", " +
                  std::to_string( pObj->header.translation.x ) + ", " +
                  std::to_string( pObj->header.translation.y ) + ", " +
                  std::to_string( pObj->header.translation.z ) + ", " +
                  std::to_string( eobjlevelHierachyId ) + "\n"
                );
                //eobjOut.write( outStr.c_str(), outStr.size() );
              }
            }
          }
        }
        std::cout << "[Info] " << "Total Groups " << totalGroups << " Total entries " << totalGroupEntries << "\n";
      }
      std::cout << "[Success] " << "Exported " << zoneName << " in " <<
                std::chrono::duration_cast< std::chrono::seconds >(
                  std::chrono::system_clock::now() - entryStartTime ).count() << " seconds\n";
    }
    catch( std::exception& e )
    {
      std::cout << "[Error] " << e.what() << std::endl;
      std::cout << "[Error] "
                << "Unable to extract collision data.\n\tIf using standalone ensure your working directory folder layout is \n\tbg/[ffxiv|ex1|ex2]/teri/type/zone/[level|collision]"
                << std::endl;
      std::cout << std::endl;
      std::cout << "[Info] " << "Usage: pcb_reader2 territory \"path/to/game/sqpack/ffxiv\" " << std::endl;
    }
    std::cout << "\n\n\n";

    std::ifstream t;
    if( entry.type == 7 )
    {
      t = std::ifstream ( "questbattle.tmpl" );
    }
    else
      t = std::ifstream ( "instance.tmpl" );

    std::string instanceTpl( ( std::istreambuf_iterator< char >( t ) ),
                             std::istreambuf_iterator< char >() );

    auto result = std::regex_replace( instanceTpl, std::regex( "\\INSTANCE_NAME" ), entry.name );
    result = std::regex_replace( result, std::regex( "\\INSTANCE_ID" ), std::to_string( entry.id ) );
    result = std::regex_replace( result, std::regex( "\\EOBJ_INIT" ), eobjects );

    if( entry.type == 7 )
    {
      if( entry.id > 200 )
        continue;

      std::string instruction;
      auto row = questBattleData.get_row( entry.id );
      for( int i = 0; i < 149; ++i )
      {
        if( std::get< std::string >( row.at( 4 + i ) ).empty() )
          continue;
        instruction += "  static constexpr auto " + std::get< std::string >( row.at( 4 + i ) ) + " = " +
                       std::to_string( std::get< uint32_t >( row.at( 154 + i ) ) )+ ";\n";
      }

      result = std::regex_replace( result, std::regex( "\\SCRIPT_INSTRUCTIONS" ), instruction );
    }


    std::string subdir = "";

    auto subdirIt = instanceContentTypeMap.find( entry.type );
    if( subdirIt != instanceContentTypeMap.end() )
      subdir = subdirIt->second + "/";

    fs::path outDir( "instances/" + subdir );
    fs::create_directories( outDir );

    std::ofstream outH( outDir.string() + entry.name + ".cpp" );
    outH << result;
    outH.close();

  }


  std::cout << "\n\n\n[Success] Finished all tasks in " <<
            std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now() - startTime ).count()
            << " seconds\n";

//  getchar();

  if( eData )
    delete eData;
  if( gameData )
    delete gameData;
  return 0;
}
