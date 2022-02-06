#include <cstdio>
#include <cstdint>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include <set>
#include <memory>
#include <variant>

#include <Util/Util.h>

#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>
#include "tex.h"
#include "tex_decode.h"

#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

using namespace Sapphire;

// garbage to ignore models
bool ignoreModels = false;

struct ZoneInfo
{
  uint16_t id;
  std::string name;
  std::string path;
  uint16_t mapId;
};

// parsing shit
std::string gamePath( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
std::unordered_map< uint32_t, std::string > eobjNameMap;
std::unordered_map< uint16_t, ZoneInfo > zoneInfoMap;
std::unordered_map< uint16_t, std::vector< std::pair< uint16_t, std::string > > > zoneInstanceMap;
uint32_t zoneId;
std::string zoneName;

std::set< std::string > zoneDumpList;

xiv::dat::GameData* gameData = nullptr;
xiv::exd::ExdData* eData = nullptr;

void readFileToBuffer( const std::string& path, std::vector< char >& buf );


// discovery shit
struct vec2
{
  float x, y;
};

struct DiscoveryMap : std::enable_shared_from_this< DiscoveryMap >
{
  std::string path;
  Image img;
  uint16_t mapScale;
  int16_t mapOffsetX, mapOffsetY;
  int mapId;
  constexpr static int discoveryMapRows = 3;
  constexpr static int discoveryMapCols = 4;
  constexpr static int tileWidth = 128;
  constexpr static int tiles = discoveryMapCols * discoveryMapRows;

  uint32_t getColour( uint8_t mapIndex, float x, float y, float scale )
  {
    auto ogX = x, ogY = y;
    int col = ( mapIndex % ( int ) ( ( float ) img.width / ( float ) tileWidth ) );
    int row = ( mapIndex / ( ( float ) img.width / ( float ) tileWidth ) );
    x = ( x / 2048.f ) * ( float ) tileWidth;
    y = ( y / 2048.f ) * ( float ) tileWidth;
    int tileX = ( col * ( float ) tileWidth ) + x;
    int tileY = ( row * ( float ) tileWidth ) + y;

    if( tileX < 0 || tileY < 0 || tileY > img.data.size() - 1 || tileX > img.data[ 0 ].size() - 1 )
    {
      std::cout << "Unable to find tile coord for " << x << " " << y << " mapIndex " << std::to_string( mapIndex )
                << "\n";
      return 0;
    }

    //std::cout << "getColour col " << col << " row " << row << " tileX " << tileX << " tileY " << tileY << " tile index " << std::to_string( unkFlag2 ) << "\n";
    auto colour = img.data[ tileY ][ tileX ];

    return colour;
  }

  vec3 get3dPosFrom2d( float x, float y )
  {
    vec3 ret;
    float scale2 = ( float ) mapScale / 100.0f;
    ret.x = ( x * scale2 ) + ( ( float ) img.height * 2.f ); //( x / scale2 ) - mapOffsetX;
    ret.z = ( y * scale2 ) + ( ( float ) img.height * 2.f ); //( y / scale2 ) - mapOffsetY;

    return ret;
  }

  vec2 get2dPosFrom3d( float x, float y, float scale )
  {
    vec2 ret;
    float scale2 = ( float ) ( ( float ) mapScale / 100.f );
    ret.x = ( ( x * scale2 ) + 1024.f );
    ret.y = ( ( y * scale2 ) + 1024.f );

    return ret;
  }
};

std::map< uint16_t, std::map< uint16_t, std::map< uint16_t, std::shared_ptr< DiscoveryMap > > > > discoveryMaps;


enum class TerritoryTypeExdIndexes : size_t
{
  TerritoryType = 0,
  Path = 1,
  Map = 6
};

using namespace std::chrono_literals;

struct face
{
  int32_t f1, f2, f3;
};

// init
void initExd( const std::string& gamePath )
{
  gameData = gameData ? gameData : new xiv::dat::GameData( gamePath );
  eData = eData ? eData : new xiv::exd::ExdData( *gameData );
}

std::string zoneNameToPath( const std::string& name )
{
  std::string path;
  bool found = false;

  static auto& cat = eData->get_category( "TerritoryType" );
  static auto exd = static_cast< xiv::exd::Exd >( cat.get_data_ln( xiv::exd::Language::none ) );
  static auto& rows = exd.get_rows();

  if( zoneInfoMap.size() == 0 )
  {
    for( auto& row : rows )
    {
      auto& fields = row.second;
      auto teriName = std::get< std::string >(
        fields.at( static_cast< size_t >( TerritoryTypeExdIndexes::TerritoryType ) ) );
      if( teriName.empty() )
        continue;
      auto teriPath = std::get< std::string >(
        fields.at( static_cast< size_t >( TerritoryTypeExdIndexes::Path ) ) );
      ZoneInfo info;
      info.id = row.first;
      info.path = teriPath;
      info.name = teriName;
      info.mapId = std::get< uint16_t >(
        fields.at( static_cast< size_t >( TerritoryTypeExdIndexes::Map ) ) );
      zoneInfoMap[ row.first ] = info;

      if( !found && ( Common::Util::toLowerCopy( name ) == Common::Util::toLowerCopy( teriName ) ) )
      {
        found = true;
        path = teriPath;
        zoneId = info.id;
      }
    }
  }
  else
  {
    for( const auto& entry : zoneInfoMap )
    {
      if( found = Common::Util::toLowerCopy( name ) == Common::Util::toLowerCopy( entry.second.name ) )
      {
        path = entry.second.path;
        zoneId = entry.second.id;
        break;
      }
    }
  }

  if( found )
  {
    //path = path.substr( path.find_first_of( "/" ) + 1, path.size() - path.find_first_of( "/" ));
    //path = std::string( "ffxiv/" ) + path;
    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );
    std::cout << "[Info] " << "Found path for " << name << ": " << path << std::endl;
  }
  else
  {
    throw std::runtime_error( "Unable to find path for " + name +
                              ".\n\tPlease double check spelling or open 0a0000.win32.index with FFXIV Explorer and extract territorytype.exh as CSV\n\tand copy territorytype.exh.csv into pcb_reader.exe directory if using standalone" );
  }

  return path;
}

void loadEobjNames()
{
  static auto& cat = eData->get_category( "EObjName" );
  static auto exd = static_cast< xiv::exd::Exd >( cat.get_data_ln( xiv::exd::Language::en ) );
  for( auto& row : exd.get_rows() )
  {
    auto id = row.first;
    auto& fields = row.second;
    auto name = std::get< std::string >( fields.at( 0 ) );
    eobjNameMap[ id ] = name;
  }
}

void writeMapRangeEntry( std::ofstream& out, LgbEntry* pObj )
{
  auto pMapRange = reinterpret_cast< LGB_MAP_RANGE_ENTRY* >( pObj );
  if( !pMapRange->data.discoveryEnabled )
    return;

  auto subArea = 0;
  auto mapId = -1;
  auto discoveryIndex = pMapRange->data.discoveryIndex;

  vec3 translation = pObj->header.transform.translation;

  std::string outStr( pMapRange->name + " " + std::to_string( pMapRange->header.instanceId ) + " " +
                      std::to_string( pMapRange->header.transform.translation.x ) + " " +
                      std::to_string( pMapRange->header.transform.translation.y ) + " " +
                      std::to_string( pMapRange->header.transform.translation.z ) + " " +
                      std::to_string( pMapRange->header.transform.rotation.y ) + " " +
                      std::to_string( pMapRange->data.mapId ) + " " +
                      std::to_string( pMapRange->data.discoveryIndex ) + "\n"
  );

  out.write( outStr.c_str(), outStr.size() );

}

int main( int argc, char* argv[] )
{
  auto startTime = std::chrono::system_clock::now();
  auto entryStartTime = std::chrono::system_clock::now();

  std::vector< std::string > argVec( argv + 1, argv + argc );
  zoneName = "s1h1";

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

  initExd( gamePath );
  std::ofstream discoverySql( "maprange_export.txt", std::ios::trunc );

  zoneNameToPath( "f1f1" );
  zoneDumpList.emplace( "f1f1" );
  zoneDumpList.emplace( "f1f2" );

  for( const auto& zoneName : zoneDumpList )
  {
    entryStartTime = std::chrono::system_clock::now();
    discoverySql.write( ( zoneName + "\n" ).c_str(), zoneName.size() + 1 );
    try
    {
      const auto zonePath = zoneNameToPath( zoneName );

      std::string bgLgbPath( zonePath + "/level/bg.lgb" );
      std::string planmapLgbPath( zonePath + "/level/planmap.lgb" );
      std::vector< char > section;
      std::vector< char > section2;

      auto test_file = gameData->getFile( bgLgbPath );
      section = test_file->access_data_sections().at( 0 );

      auto planmap_file = gameData->getFile( planmapLgbPath );
      section2 = planmap_file->access_data_sections().at( 0 );

      std::vector< std::string > stringList;

      uint32_t offset1 = 0x20;

      LGB_FILE bgLgb( &section[ 0 ], "bg" );
      LGB_FILE planmapLgb( &section2[ 0 ], "planmap" );

      std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb };
      uint32_t max_index = 0;

      std::cout << "[Info] " << "Dumping MapRange and EObj" << "\n";
      uint32_t totalGroups = 0;
      uint32_t totalGroupEntries = 0;

      for( const auto& lgb : lgbList )
      {
        for( const auto& group : lgb.groups )
        {
          totalGroups++;
          for( const auto& pEntry : group.entries )
          {
            if( pEntry->getType() == LgbEntryType::MapRange )
            {
              totalGroupEntries++;
              writeMapRangeEntry( discoverySql, pEntry.get() );
            }
            else if( pEntry->getType() == LgbEntryType::ExitRange )
            {
              auto pExitRange = reinterpret_cast< LGB_EXIT_RANGE_ENTRY* >( pEntry.get() );

            }
          }
        }
      }
      std::cout << "[Info] " << "Total Groups " << totalGroups << " Total entries " << totalGroupEntries << "\n";

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
    std::cout << "\n";
    if( discoverySql.good() )
      discoverySql.flush();
  }
  std::cout << "\n[Success] Finished all tasks in " <<
            std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now() - startTime ).count()
            << " seconds\n";

  std::cout << "Press any key to exit...";
  getchar();

  if( eData )
    delete eData;
  if( gameData )
    delete gameData;
  return 0;
}
