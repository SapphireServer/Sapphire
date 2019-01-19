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

#include "pcb.h"
#include "lgb.h"
#include "sgb.h"
#include "tex.h"
#include "tex_decode.h"

#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

// garbage to ignore models
bool ignoreModels = false;

struct ZoneInfo
{
  uint16_t id;
  std::string name;
  std::string path;
};

// parsing shit
std::string gamePath( "C:\\Program Files (x86)\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
std::unordered_map< uint32_t, std::string > eobjNameMap;
std::unordered_map< uint16_t, ZoneInfo > zoneInfoMap;
std::unordered_map< uint16_t, std::vector< std::pair< uint16_t, std::string > > > zoneInstanceMap;
uint32_t zoneId;
std::string zoneName;

std::set< std::string > zoneDumpList;

xiv::dat::GameData* data1 = nullptr;
xiv::exd::ExdData* eData = nullptr;

void readFileToBuffer( const std::string& path, std::vector< char >& buf );


// discovery shit
struct vec2
{
  float x, y;
};

struct DiscoveryMap :
  std::enable_shared_from_this< DiscoveryMap >
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


enum class TerritoryTypeExdIndexes :
  size_t
{
  TerritoryType = 0,
  Path = 1
};

using namespace std::chrono_literals;

struct face
{
  int32_t f1, f2, f3;
};

// init
void initExd( const std::string& gamePath )
{
  data1 = data1 ? data1 : new xiv::dat::GameData( gamePath );
  eData = eData ? eData : new xiv::exd::ExdData( *data1 );
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
      zoneInfoMap[ row.first ] = info;

      if( !found && ( Sapphire::Util::toLowerCopy( name ) == Sapphire::Util::toLowerCopy( teriName ) ) )
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
      if( found = Sapphire::Util::toLowerCopy( name ) == Sapphire::Util::toLowerCopy( entry.second.name ) )
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

void writeEobjEntry( std::ofstream& out, LGB_ENTRY* pObj )
{
  static std::string mapRangeStr( "\"MapRange\", " );
  std::ofstream discoverySql( zoneName + "_poprange.txt", std::ios::app );
  uint32_t id;
  uint32_t unknown2 = 0, unknown2_1 = 0, unknown3 = 0;
  std::string name;
  std::string typeStr;
  uint32_t eobjlevelHierachyId = 0;
  static std::map< uint32_t, std::map< uint32_t, uint32_t > > exportedMapRange;

  auto pMapRange = reinterpret_cast< LGB_MAPRANGE_ENTRY* >( pObj );
  id = pMapRange->header.unknown;
  unknown2 = pMapRange->header.unknown2;
  unknown2_1 = pMapRange->header.unknown2_1;
  unknown3 = pMapRange->header.unknown3;
  typeStr = mapRangeStr;

  // discovery shit
  vec2 pos{ 0 };
  auto subArea = 0;
  auto mapId = -1;
  auto discoveryIndex = pMapRange->header.discoveryIndex;

  vec3 translation = pObj->header.translation;

  bool found = false;
  float scale = 100.f; //pMapRange->header.unknown2

  std::string outStr( pMapRange->name + " " + std::to_string( pMapRange->header.unknown ) + " " +
  std::to_string( pMapRange->header.translation.x ) + " " +
  std::to_string( pMapRange->header.translation.y ) + " " +
  std::to_string( pMapRange->header.translation.z ) + " " +
  std::to_string( pMapRange->header.rotation.y ) + "\n"
  );

    //std::to_string( pObj->header.translation.x ) + ", " + std::to_string( pObj->header.translation.y ) + ", " + std::to_string( pObj->header.translation.z ) +
    //", " + std::to_string( subArea ) + "" + "\n"
  //);
  discoverySql.write( outStr.c_str(), outStr.size() );
  //out.write( outStr.c_str(), outStr.size() );
}

void readFileToBuffer( const std::string& path, std::vector< char >& buf )
{
  auto inFile = std::ifstream( path, std::ios::binary );
  if( inFile.good() )
  {
    inFile.seekg( 0, inFile.end );
    int32_t fileSize = ( int32_t ) inFile.tellg();
    buf.resize( fileSize );
    inFile.seekg( 0, inFile.beg );
    inFile.read( &buf[ 0 ], fileSize );
    inFile.close();
  }
  else
  {
    throw std::runtime_error( "Unable to open " + path );
  }
}

bool isEx = false;

int main( int argc, char* argv[] )
{
  auto startTime = std::chrono::system_clock::now();
  auto entryStartTime = std::chrono::system_clock::now();

  std::vector< std::string > argVec( argv + 1, argv + argc );
  zoneName = "s1h1";

  bool dumpAll = ignoreModels = std::remove_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--dump-all"; } ) != argVec.end();
  dumpAll = true;
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

  initExd( gamePath );
  std::ofstream discoverySql( zoneName + "_poprange.txt", std::ios::trunc );
  discoverySql.close();

  if( dumpAll )
  {
    zoneNameToPath( "s1h1" );

    zoneDumpList.emplace( "s1h1" );
    zoneDumpList.emplace( "f1h1" );
    zoneDumpList.emplace( "w1h1" );
    zoneDumpList.emplace( "e1h1" );
  }
  else
  {
    zoneDumpList.emplace( zoneName );
  }

  LABEL_DUMP:
  entryStartTime = std::chrono::system_clock::now();
  zoneName = *zoneDumpList.begin();
  discoverySql.open( zoneName + "_poprange.txt", std::ios::trunc );
  discoverySql.write( ( zoneName + "\n" ).c_str() , zoneName.size() + 1 );
  try
  {
    const auto zonePath = zoneNameToPath( zoneName );

    std::string listPcbPath( zonePath + "/collision/list.pcb" );
    std::string bgLgbPath( zonePath + "/level/bg.lgb" );
    std::string planmapLgbPath( zonePath + "/level/planmap.lgb" );
    std::string collisionFilePath( zonePath + "/collision/" );

    isEx = bgLgbPath.find( "ex1" ) != -1 || bgLgbPath.find( "ex2" ) != -1;
    std::vector< char > section;
    std::vector< char > section1;
    std::vector< char > section2;

    auto test_file = data1->getFile( bgLgbPath );
    section = test_file->access_data_sections().at( 0 );

    auto planmap_file = data1->getFile( planmapLgbPath );
    section2 = planmap_file->access_data_sections().at( 0 );

    auto test_file1 = data1->getFile( listPcbPath );
    section1 = test_file1->access_data_sections().at( 0 );

    std::vector< std::string > stringList;

    uint32_t offset1 = 0x20;

    //loadEobjNames();
    //getMapExdEntries( zoneId );

    std::string eobjFileName( zoneName + "_eobj.csv" );
    std::ofstream eobjOut( eobjFileName, std::ios::trunc );
    if( !eobjOut.good() )
      throw std::string( "Unable to create " + zoneName +
                         "_eobj.csv for eobj entries. Run as admin or check there isnt already a handle on the file." ).c_str();

    eobjOut.close();
    eobjOut.open( eobjFileName, std::ios::app );

    if( !eobjOut.good() )
      throw std::string( "Unable to create " + zoneName +
                         "_eobj.csv for eobj entries. Run as admin or check there isnt already a handle on the file." ).c_str();

    if( 0 )
    {
      for( ;; )
      {

        uint16_t trId = *( uint16_t* ) &section1[ offset1 ];

        char someString[200];
        sprintf( someString, "%str%04d.pcb", collisionFilePath.c_str(), trId );
        stringList.push_back( std::string( someString ) );
        //std::cout << someString << "\n";
        offset1 += 0x20;

        if( offset1 >= section1.size() )
        {
          break;
        }
      }
    }
    LGB_FILE bgLgb( &section[ 0 ], "bg" );
    LGB_FILE planmapLgb( &section2[ 0 ], "planmap" );

    std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb };
    uint32_t max_index = 0;

    // dont bother if we cant write to a file
    FILE* fp_out = nullptr;
    //auto fp_out = ignoreModels ? ( FILE* )nullptr : fopen( ( zoneName + ".obj" ).c_str(), "w" );
    if( fp_out )
    {
      fprintf( fp_out, "\n" );
      fclose( fp_out );
    }
    else if( /*!ignoreModels*/ false )
    {
      std::string errorMessage( "Cannot create " + zoneName + ".obj\n" +
                                " Check no programs have a handle to file and run as admin.\n" );
      std::cout << errorMessage;
      throw std::runtime_error( errorMessage.c_str() );
      return 0;
    }


    {
      std::map< std::string, PCB_FILE > pcbFiles;

      std::cout << "[Info] " << ( ignoreModels ? "Dumping MapRange and EObj" : "Writing obj file " ) << "\n";
      uint32_t totalGroups = 0;
      uint32_t totalGroupEntries = 0;

      for( const auto& lgb : lgbList )
      {
        for( const auto& group : lgb.groups )
        {
          //std::cout << "\t" << group.name << " Size " << group.header.entryCount << "\n";
          totalGroups++;
          for( const auto& pEntry : group.entries )
          {
            if( pEntry->getType() == LgbEntryType::PopRange )
            {
              totalGroupEntries++;
              writeEobjEntry( eobjOut, pEntry.get() );
            }
          }
        }
      }
      std::cout << "[Info] " << "Loaded " << pcbFiles.size() << " PCB Files \n";
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
  if( discoverySql.good() )
    discoverySql.flush();

  LABEL_NEXT_ZONE_ENTRY:
  zoneDumpList.erase( zoneName );
  if( !zoneDumpList.empty() )
    goto LABEL_DUMP;


  std::cout << "\n\n\n[Success] Finished all tasks in " <<
            std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now() - startTime ).count()
            << " seconds\n";

  getchar();

  if( eData )
    delete eData;
  if( data1 )
    delete data1;
  return 0;
}
