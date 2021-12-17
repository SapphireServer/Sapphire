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

#include <datReaderPs3/DatCategories/bg/pcb.h>
#include <datReaderPs3/DatCategories/bg/lgb.h>
#include <datReaderPs3/DatCategories/bg/sgb.h>
#include "tex.h"
#include "tex_decode.h"

#include <datReaderPs3/GameData.h>
#include <datReaderPs3/File.h>
#include <datReaderPs3/DatCat.h>
#include <datReaderPs3/ExdData.h>
#include <datReaderPs3/ExdCat.h>
#include <datReaderPs3/Exd.h>
#include <datReaderPs3/DatCategories/bg/lvb.h>

#include "ExdData.h"
#include <Logging/Logger.h>

#include <algorithm>

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

using LayerSetToTerritoryIdMap = std::unordered_map< uint32_t, uint32_t >;
using LayerSetToGroupIdsMap = std::unordered_map< uint32_t, std::vector< std::tuple< uint32_t, std::string > > >;

// parsing shit
std::string gamePath( "E:\\\\XIV_Patches\\monitor\\USRDIR\\game\\sqpack" );

std::unordered_map< uint32_t, std::string > eobjNameMap;
std::unordered_map< uint16_t, ZoneInfo > zoneInfoMap;
std::unordered_map< uint16_t, std::vector< std::pair< uint16_t, std::string > > > zoneInstanceMap;
uint32_t zoneId;
std::string zoneName;

std::set< std::string > zoneDumpList;

xivps3::dat::GameData* gameData = nullptr;
xivps3::exd::ExdData* eData = nullptr;

Data::ExdData g_exdDataGen;

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
  gameData = gameData ? gameData : new xivps3::dat::GameData( gamePath );
  eData = eData ? eData : new xivps3::exd::ExdData( *gameData );
}

std::string zoneNameToPath( const std::string& name )
{
  std::string path;
  bool found = false;

  static auto& cat = eData->get_category( "TerritoryType" );
  static auto exd = static_cast< xivps3::exd::Exd >( cat.get_data_ln( xivps3::exd::Language::none ) );
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
  static auto exd = static_cast< xivps3::exd::Exd >( cat.get_data_ln( xivps3::exd::Language::en ) );
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


void writeBNPCEntry( std::string& name, std::ofstream& out, LgbEntry* pObj, const LGB_GROUP& group, LayerSetToGroupIdsMap& layerSetMap )
{
  auto pBNpc = reinterpret_cast< LGB_BNPC_ENTRY* >( pObj );

  auto subArea = 0;
  auto mapId = -1;
  //auto discoveryIndex = pBNpc->data.discoveryIndex;

  vec3 translation = pObj->header.transform.translation;
  for( auto ref : group.refs )
  {
    auto& groupList = layerSetMap[ ref.LayerSetID ];

    auto it = std::find_if( groupList.begin(), groupList.end(), [ &group ]( const auto& item )
    {
      return std::get< 0 >( item ) == group.header.id;
    } );

    if( it == groupList.end() )
    {
      groupList.emplace_back( group.header.id, group.name );
    }
  }


  std::string outStr( std::to_string( group.header.id ) + ", " +
//                      layers + ", " +
                      group.name + ", " +
                      name + ", " +
                      pBNpc->name + ", " +
                      std::to_string( pBNpc->header.instanceId ) + ", " +
                      std::to_string( pBNpc->header.transform.translation.x ) + ", " +
                      std::to_string( pBNpc->header.transform.translation.y ) + ", " +
                      std::to_string( pBNpc->header.transform.translation.z ) + ", " +
                      std::to_string( pBNpc->data.transform.rotation.y ) + ", " +
                      std::to_string( pBNpc->data.BaseId ) + ", " +
                      std::to_string( pBNpc->data.PopWeather ) + ", " +
                        std::to_string( pBNpc->data.PopTimeStart ) + ", " +
                        std::to_string( pBNpc->data.PopTimeEnd ) + ", " +
                        std::to_string( pBNpc->data.MoveAI ) + ", " +
                        std::to_string( pBNpc->data.WanderingRange ) + ", " +
                        std::to_string( pBNpc->data.Route ) + ", " +
                        std::to_string( pBNpc->data.EventGroup ) + ", " +
                        std::to_string( pBNpc->data.NameId ) + ", " +
                        std::to_string( pBNpc->data.DropItem ) + ", " +
                        std::to_string( pBNpc->data.SenseRangeRate ) + ", " +
                        std::to_string( pBNpc->data.Level ) + ", " +
                        std::to_string( pBNpc->data.ActiveType ) + ", " +
                        std::to_string( pBNpc->data.PopInterval ) + ", " +
                        std::to_string( pBNpc->data.PopRate ) + ", " +
                        std::to_string( pBNpc->data.PopEvent ) + ", " +
                        std::to_string( pBNpc->data.LinkGroup ) + ", " +
                        std::to_string( pBNpc->data.LinkFamily ) + ", " +
                        std::to_string( pBNpc->data.LinkRange ) + ", " +
                        std::to_string( pBNpc->data.LinkCountLimit ) + ", " +
                        std::to_string( pBNpc->data.NonpopInitZone ) + ", " +
                        std::to_string( pBNpc->data.InvalidRepop ) + ", " +
                        std::to_string( pBNpc->data.LinkParent ) + ", " +
                        std::to_string( pBNpc->data.LinkOverride ) + ", " +
                        std::to_string( pBNpc->data.LinkReply ) + ", " +
                        std::to_string( pBNpc->data.Nonpop ) + ", " +
                        std::to_string( pBNpc->data.HorizontalPopRange ) + ", " +
                        std::to_string( pBNpc->data.VerticalPopRange ) + ", " +
                        std::to_string( pBNpc->data.BNpcBaseData ) + ", " +
                        std::to_string( pBNpc->data.RepopId ) + ", " +
                        std::to_string( pBNpc->data.BNPCRankId ) + ", " +
                        std::to_string( pBNpc->data.TerritoryRange ) + ", " +
                        std::to_string( pBNpc->data.BoundInstanceID ) + ", " +
                        std::to_string( pBNpc->data.FateLayoutLabelId ) + ", " +
                        std::to_string( pBNpc->data.NormalAI ) + ", " +
                        std::to_string( pBNpc->data.ServerPathId ) + ", " +
                        std::to_string( pBNpc->data.EquipmentID ) + ", " +
                        std::to_string( pBNpc->data.CustomizeID ) + " " +
                      "\n" );

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
  std::ofstream discoverySql( "maprange_export.csv", std::ios::trunc );

  LayerSetToGroupIdsMap layerMap;
  LayerSetToTerritoryIdMap layerSetToTerritoryIdMap;

  zoneNameToPath( "f1f1" );
  zoneDumpList.emplace( "f1d1" );
  zoneDumpList.emplace( "f1f2" );

  if ( !g_exdDataGen.init( gamePath ) )
  {
    
  }

  auto teriIdList = g_exdDataGen.getIdList< Component::Excel::Ps3::TerritoryType >();


  std::string data = std::string("GroupId, GroupName, TerritoryName, name, instanceId, x, y, z, Rotation, BaseId, PopWeather, PopTimeStart, PopTimeEnd, MoveAI, WanderingRange, Route, ") +
                     std::string("EventGroup, NameId, DropItem, SenseRangeRate, Level, ActiveType, PopInterval,PopRate, PopEvent, LinkGroup, ") +
                     std::string("LinkFamily, LinkRange, LinkCountLimit, NonpopInitZone, InvalidRepop, LinkParent, LinkOverride, LinkReply, Nonpop, ") +
                     std::string("HorizontalPopRange, VerticalPopRange, BNpcBaseData, RepopId, BNPCRankId, TerritoryRange, BoundInstanceID, ") +
                     std::string("FateLayoutLabelId, NormalAI, ServerPathId, EquipmentID, CustomizeID \n");

  discoverySql.write( data.c_str(), data.size() );


  std::set< std::string > zoneNames;
  for( const auto& id : teriIdList )
  {
    auto row = g_exdDataGen.getRow< Component::Excel::Ps3::TerritoryType >( id );
    if( !row )
      continue;
    std::string zonePath = row->getString( row->data().LVB );

    if( zonePath.empty() )
      continue;

    auto pos = zonePath.find_last_of( "/" );
    if( pos != std::string::npos )
    {
      zonePath = zonePath.substr( pos + 1 );
    }

    zoneNames.insert( zonePath );

  }
  for( const auto& name : zoneNames )
  {
   // auto row = g_exdDataGen.getRow< Component::Excel::TerritoryType >( id );
   // if( !row )
   //   continue;

   if( name.empty() )
     continue;

    auto zoneName = name;
    entryStartTime = std::chrono::system_clock::now();

    try
    {
      const auto zonePath = zoneNameToPath( name );

      auto exportBnpcEntries = [ & ]( const std::string& path )
      {
        std::vector< char > data_section;

        try
        {
          auto bg_file = gameData->getFile( path );
          data_section = bg_file->access_data_sections().at( 0 );
        }
        catch( ... )
        {
          return;
        }



        std::vector< std::string > stringList;

        uint32_t offset1 = 0x20;

        LGB_FILE bgLgb( &data_section[ 0 ], "bg" );

        std::vector< LGB_FILE > lgbList{ bgLgb };
        uint32_t max_index = 0;

        std::cout << "[Info] " << "Dumping BNPC data" << "\n";
        uint32_t totalGroups = 0;
        uint32_t totalGroupEntries = 0;

        for( const auto& lgb : lgbList )
        {
          for( const auto& group : lgb.groups )
          {
            totalGroups++;
            for( const auto& pEntry : group.entries )
            {
              if( pEntry->getType() == LgbEntryType::BattleNpc )
              {
                totalGroupEntries++;
                writeBNPCEntry( zoneName, discoverySql, pEntry.get(), group, layerMap );
              }
              else if( pEntry->getType() == LgbEntryType::ClientPath )
              {
                totalGroupEntries++;
                totalGroupEntries--;
              }
            }
          }
        }
        std::cout << fmt::format(
          "[Info] file: {} total groups: {} total entries: {}",
          path, totalGroups, totalGroupEntries ) << std::endl;
      };

      std::cout << zonePath + "/level/" + zoneName + ".lvb\n";

      auto file = gameData->getFile( zonePath + "/level/" + zoneName + ".lvb" );
      auto data_section = file->access_data_sections().at( 0 );
      LVB_FILE lvb( &data_section[ 0 ], zoneName );

      std::ofstream lvbRawFile("./lvb/" + zoneName + ".lvb", std::ios::trunc );
      lvbRawFile.write( &data_section[ 0 ], data_section.size() );
      if( lvbRawFile.good() )
        lvbRawFile.close();

      int nameIndex = 0;
      for( const auto& layer : lvb.layers )
      {
//        std::cout << layer.LayerSetID << " " << layer.TerritoryTypeID << " " << lvb.layerNames[ nameIndex++ ] << "\n";

//        std::string layerOut = std::to_string( layer.TerritoryTypeID ) + ", " + std::to_string( layer.LayerSetID ) + ", " + lvb.layerNames[ nameIndex++ ] + "\n";
//        mapSql.write( layerOut.c_str(), layerOut.size() );

        layerMap[ layer.LayerSetID ] = {};
        layerSetToTerritoryIdMap[ layer.LayerSetID ] = layer.TerritoryTypeID;
      }


      exportBnpcEntries( zonePath + "/level/bg.lgb" );
      exportBnpcEntries( zonePath + "/level/planmap.lgb" );
      exportBnpcEntries( zonePath + "/level/planevent.lgb" );
      exportBnpcEntries( zonePath + "/level/planner.lgb" );
      exportBnpcEntries( zonePath + "/level/planlive.lgb" );

      std::cout << "[Success] " << "Exported " << zoneName << " in " <<
                std::chrono::duration_cast< std::chrono::seconds >(
                  std::chrono::system_clock::now() - entryStartTime ).count() << " seconds\n";
    }
    catch( std::exception& e )
    {
      std::cout << "[Error] " << e.what() << std::endl;

      std::cout << std::endl;
      std::cout << "[Info] " << "Usage: bnpc_parser \"path/to/game/sqpack/ffxiv\" " << std::endl;
    }
    std::cout << "\n";
    if( discoverySql.good() )
      discoverySql.flush();
  }
  std::cout << "\n[Success] Finished all tasks in " <<
            std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now() - startTime ).count()
            << " seconds\n";

  std::cout << "dumping layerset -> lgb group" << std::endl;

  std::ofstream mapSql( "maprange_territories.csv", std::ios::trunc );

  std::string lvbColumns = "TerritoryTypeId, LayerSetId, LayerGroupId, LayerGroupName\n";
  mapSql.write( lvbColumns.c_str(), lvbColumns.size() );

  for( const auto& entry : layerMap )
  {
    auto layerSetId = entry.first;
    auto groupIds = entry.second;

    if( groupIds.empty() )
    {
      continue;
    }

    auto territoryId = layerSetToTerritoryIdMap[ layerSetId ];
    //std::cout << "LayerSetID: " << layerSetId << " territory: " << territoryId << std::endl;


    for( const auto& groupInfo : groupIds )
    {
      std::string output = std::to_string( territoryId ) + "," +
        std::to_string( layerSetId ) + "," +
        std::to_string( std::get< 0 >( groupInfo ) ) + "," +
        std::get< 1 >( groupInfo ) + "\n";

      mapSql.write( output.c_str(), output.size() );

//      std::cout << " - " << std::get< 0 >( groupInfo ) << " " << std::get< 1 >( groupInfo ) << std::endl;
    }

//    std::cout << std::endl;
  }

  if( mapSql.good() )
    mapSql.flush();

  mapSql.close();

  std::cout << "Press any key to exit...";
  getchar();

  if( eData )
    delete eData;
  if( gameData )
    delete gameData;
  return 0;
}
