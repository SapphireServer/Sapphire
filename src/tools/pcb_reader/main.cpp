#include <stdio.h>
#include <cstdint>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <regex>
#include <map>
#include <vector>

#include <queue>
#include <set>
#include <thread>
#include <variant>
#include <Util/Util.h>

#include "exporter.h"
#include "exportmgr.h"

#include "cache.h"
#include "pcb.h"
#include "lgb.h"
#include "sgb.h"

#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

// garbage to ignore models
bool noObj = false;

std::string gamePath( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
std::unordered_map< uint16_t, std::string > zoneNameMap;
std::map< std::string, std::string > exportedTeriMap;

uint32_t zoneId;


std::set< std::string > zoneDumpList;

std::shared_ptr< Cache > pCache;
std::map< uint32_t, uint16_t > eobjSgbPaths;

xiv::dat::GameData* gameData = nullptr;
xiv::exd::ExdData* eData = nullptr;


enum class TerritoryTypeExdIndexes :
  size_t
{
  TerritoryType = 0,
  Path = 1
};

using namespace std::chrono_literals;

void initExd( const std::string& gamePath )
{
  gameData = gameData ? gameData : new xiv::dat::GameData( gamePath );
  eData = eData ? eData : new xiv::exd::ExdData( *gameData );
  pCache = std::make_shared< Cache >( gameData );
}

void replaceAll( std::string& str, const std::string& from, const std::string& to ) {
  if( from.empty() )
    return;
  size_t start_pos = 0;
  while( ( start_pos = str.find( from, start_pos ) ) != std::string::npos ) {
    str.replace( start_pos, from.length(), to );
    start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
  }
}

std::string getEobjSgbPath( uint32_t eobjId )
{
  static std::map< uint16_t, std::string > exportedSgMap;

  if( !exportedSgMap.empty() )
    return exportedSgMap[ eobjSgbPaths[ eobjId ] ];

  auto& eobjCat = eData->get_category( "EObj" );
  auto eObjExd = static_cast< xiv::exd::Exd >( eobjCat.get_data_ln( xiv::exd::Language::none ) );

  auto& exportedSgCat = eData->get_category( "ExportedSG" );
  auto exportedSgExd = static_cast< xiv::exd::Exd >( exportedSgCat.get_data_ln( xiv::exd::Language::none ) );

  for( auto& row : exportedSgExd.get_rows() )
  {
    auto id = row.first;
    auto& fields = row.second;

    auto path = std::get< std::string >( fields.at( 0 ) );
    exportedSgMap[id] = path;
  }

  uint16_t exportedSgId{0};

  for( auto& row : eObjExd.get_rows() )
  {
    auto id = row.first;
    auto& fields = row.second;

    eobjSgbPaths[id] = std::get< uint16_t >( fields.at( 11 ) );
  }
  return exportedSgMap[exportedSgId];
}

std::string zoneNameToPath( const std::string& name )
{
  std::string path;
  bool found = false;

  auto& cat = eData->get_category( "TerritoryType" );
  auto exd = static_cast< xiv::exd::Exd >( cat.get_data_ln( xiv::exd::Language::none ) );
  for( auto& row : exd.get_rows() )
  {
    auto& fields = row.second;
    auto teriName = std::get< std::string >(
      fields.at( static_cast< size_t >( TerritoryTypeExdIndexes::TerritoryType ) ) );
    if( teriName.empty() )
      continue;
    auto teriPath = std::get< std::string >( fields.at( static_cast< size_t >( TerritoryTypeExdIndexes::Path ) ) );
    if( !found && ( Sapphire::Util::toLowerCopy( name ) == Sapphire::Util::toLowerCopy( teriName ) ) )
    {
      path = teriPath;
      found = true;
      zoneId = row.first;
    }
    zoneNameMap[ row.first ] = teriName;
  }

  if( found )
  {
    //path = path.substr( path.find_first_of( "/" ) + 1, path.size() - path.find_first_of( "/" ));
    //path = std::string( "ffxiv/" ) + path;
    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );
    printf( "[Info] Found path for %s\n", name.c_str() );
  }
  else
  {
    throw std::runtime_error( "Unable to find path for " + name +
                              ".\n\tPlease double check spelling." );
  }

  return path;
}

int main( int argc, char* argv[] )
{
  auto startTime = std::chrono::high_resolution_clock::now();
  auto entryStartTime = std::chrono::high_resolution_clock::now();

  std::vector< std::string > argVec( argv + 1, argv + argc );
  std::string zoneName = "r2t2";

  noObj = std::find_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--no-obj"; } ) != argVec.end();
  bool dumpAllZones = std::find_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--dump-all"; } ) != argVec.end();
  bool generateNavmesh = std::find_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--navmesh"; } ) != argVec.end();
  bool splitByGroup = std::find_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--split-by-group"; }) != argVec.end();
  bool splitByZone = std::find_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--split-by-zone"; }) != argVec.end();
  int nJobs = std::thread::hardware_concurrency();
  if( auto it = std::find_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--jobs"; }); it != argVec.end() )
  {

    try
    {
      auto it2 = ( it + 1 );
      nJobs =  std::stoi( *it2 );
      if( nJobs < 0 )
        throw std::runtime_error( "Number of jobs < 0\n" );
    }
    catch( std::exception& e )
    {
      std::cout << e.what() << "\n";
      std::cout << "Invalid number of jobs " << nJobs << "\n";
      std::cout << "--jobs <numberOfJobs>\n";
      return -1;
    }
  }
  int exportFileType = 0;
  if( !noObj )
    exportFileType |= ExportFileType::WavefrontObj;
  if( generateNavmesh )
    exportFileType |= ExportFileType::Navmesh;

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

  try
  {
    initExd( gamePath );
    getEobjSgbPath( 0 );
  }
  catch( std::exception& e )
  {
    printf( "Unable to initialise EXD!\n Usage: pcb_reader <teri> \"path/to/FINAL FANTASY XIV - A REALM REBORN/game/sqpack\" [--no-obj, --dump-all, --navmesh, --jobs #]\n" );
    return -1;
  }
  ExportMgr exportMgr( nJobs );
  zoneNameToPath( zoneName );

  if( dumpAllZones )
  {
    for( const auto& zone : zoneNameMap )
      zoneDumpList.emplace( zone.second );
  }
  else
  {
    zoneDumpList.emplace( zoneName );
  }

  int zoneCount = 0;
  for( auto zoneName : zoneDumpList )
  {
    try
    {
      const auto& zonePath = zoneNameToPath( zoneName );
      if( exportedTeriMap.find( zonePath ) != exportedTeriMap.end() )
        continue;

      zoneName = zonePath.substr( zonePath.find_last_of( '/' ) );

      ExportedZone exportedZone;
      exportedZone.name = zoneName;
      exportedTeriMap[ zonePath ] = zoneName;

      std::string listPcbPath( zonePath + "/collision/list.pcb" );
      std::string bgLgbPath( zonePath + "/level/bg.lgb" );
      std::string planmapLgbPath( zonePath + "/level/planmap.lgb" );
      std::string collisionFilePath( zonePath + "/collision/" );
      std::vector< char > section;
      std::vector< char > section1;
      std::vector< char > section2;

      const xiv::dat::Cat& test = gameData->getCategory( "bg" );

      auto test_file = gameData->getFile( bgLgbPath );
      section = test_file->access_data_sections().at( 0 );

      auto planmap_file = gameData->getFile( planmapLgbPath );
      section2 = planmap_file->access_data_sections().at( 0 );

      auto test_file1 = gameData->getFile( listPcbPath );
      section1 = test_file1->access_data_sections().at( 0 );

      std::vector< std::string > stringList;

      int totalGroups = 0;
      int totalEntries = 0;

      uint32_t offset1 = 0x20;

      {
        for( ;; )
        {
          if( offset1 >= section1.size() )
          {
            break;
          }
          uint16_t trId = *( uint16_t* ) &section1[ offset1 ];

          char someString[200];
          sprintf( someString, "%str%04d.pcb", collisionFilePath.c_str(), trId );
          stringList.push_back( std::string( someString ) );
          //std::cout << someString << "\n";
          offset1 += 0x20;


        }
      }
      LGB_FILE bgLgb( &section[ 0 ] );
      LGB_FILE planmapLgb( &section2[ 0 ] );

      std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb };
      uint32_t max_index = 0;
      int totalModels = 0;

      

      auto buildModelEntry = [ & ]( std::shared_ptr< PCB_FILE > pPcbFile, ExportedGroup& exportedGroup,
                              const std::string& name, const std::string& groupName,
                              const vec3* scale = nullptr,
                              const vec3* rotation = nullptr,
                              const vec3* translation = nullptr,
                              const SGB_MODEL_ENTRY* pSgbEntry = nullptr )
      {
        
        auto& pcb_file = *pPcbFile.get();

        ExportedModel model;
        model.name = name + "_" + std::to_string( totalModels++ );
        model.meshes.resize( pcb_file.entries.size() );

        uint32_t meshCount = 0;
        for( const auto& entry : pcb_file.entries )
        {
          ExportedMesh mesh;

          mesh.verts.resize( ( entry.header.num_vertices + entry.header.num_v16 ) * 3 );
          mesh.indices.resize( entry.header.num_indices * 3 );

          float x_base = abs( float( entry.header.x1 - entry.header.x ) );
          float y_base = abs( float( entry.header.y1 - entry.header.y ) );
          float z_base = abs( float( entry.header.z1 - entry.header.z ) );

          auto makeTranslation = [ & ]( vec3& v )
          {
            if( pSgbEntry )
            {
              v.x *= pSgbEntry->header.scale.x;
              v.y *= pSgbEntry->header.scale.y;
              v.z *= pSgbEntry->header.scale.z;

              v = v * matrix4::rotateX( pSgbEntry->header.rotation.x );
              v = v * matrix4::rotateY( pSgbEntry->header.rotation.y );
              v = v * matrix4::rotateZ( pSgbEntry->header.rotation.z );

              v.x += pSgbEntry->header.translation.x;
              v.y += pSgbEntry->header.translation.y;
              v.z += pSgbEntry->header.translation.z;
            }

            if( scale )
            {
              v.x *= scale->x;
              v.y *= scale->y;
              v.z *= scale->z;

              v = v * matrix4::rotateX( rotation->x );
              v = v * matrix4::rotateY( rotation->y );
              v = v * matrix4::rotateZ( rotation->z );

              v.x += translation->x;
              v.y += translation->y;
              v.z += translation->z;
            }

          };
          int verts = 0;
          int indices = 0;

          for( auto& vertex : entry.data.vertices )
          {
            vec3 v( vertex.x, vertex.y, vertex.z );
            makeTranslation( v );

            mesh.verts[ verts++ ] = v.x;
            mesh.verts[ verts++ ] = v.y;
            mesh.verts[ verts++ ] = v.z;
          }

          for( const auto& link : entry.data.vertices_i16 )
          {
            vec3 v( float( link.x ) / 0xFFFF, float( link.y ) / 0xFFFF, float( link.z ) / 0xFFFF );

            v.x = v.x * x_base + entry.header.x;
            v.y = v.y * y_base + entry.header.y;
            v.z = v.z * z_base + entry.header.z;

            makeTranslation( v );

            mesh.verts[ verts++ ] = v.x;
            mesh.verts[ verts++ ] = v.y;
            mesh.verts[ verts++ ] = v.z;
          }

          for( const auto& index : entry.data.indices )
          {
            mesh.indices[ indices++ ] = index.index[ 0 ];
            mesh.indices[ indices++ ] = index.index[ 1 ];
            mesh.indices[ indices++ ] = index.index[ 2 ];
            // std::cout << std::to_string( index.unknown[0] )<< " " << std::to_string( index.unknown[1] )<< " " << std::to_string( index.unknown[2]) << std::endl;
          }
          max_index += entry.data.vertices.size() + entry.data.vertices_i16.size();
          model.meshes[ meshCount++ ] = mesh;
        }
        exportedGroup.models[model.name] = model;
      };
      ExportedGroup exportedTerrainGroup;
      exportedTerrainGroup.name = zoneName + "_terrain";
      for( const auto& fileName : stringList )
      {
        if( auto pPcbFile = pCache->getPcbFile( fileName ) )
          buildModelEntry( pPcbFile, exportedTerrainGroup, fileName, zoneName );
      }
      exportedZone.groups.emplace( exportedTerrainGroup.name, exportedTerrainGroup );
      
      for( const auto& lgb : lgbList )
      {
        for( const auto& group : lgb.groups )
        {
          ExportedGroup exportedGroup;
          exportedGroup.name = group.name;

          max_index = 0;

          //std::cout << "\t" << group.name << " Size " << group.header.entryCount << "\n";
          for( const auto& pEntry : group.entries )
          {
            std::string fileName( "" );
            fileName.resize( 256 );

            // write files
            auto pcbTransformModel = [&]( const std::string& fileName, const vec3* scale, const vec3* rotation,
              const vec3* translation, const SGB_MODEL_ENTRY* pModel = nullptr )-> bool
            {
              if( auto pPcbFile = pCache->getPcbFile( fileName ) )
              {
                buildModelEntry( pPcbFile, exportedGroup, fileName, group.name, scale, rotation, translation, pModel );
              }
              return true;
            };
            auto exportSgbModel = [&]( const std::string& sgbFilePath, LGB_ENTRY* pGimmick, bool isEobj = false  )
            {
              if( auto pSgbFile = pCache->getSgbFile( sgbFilePath ) )
              {
                const auto& sgbFile = *pSgbFile;
                for( const auto& group : sgbFile.entries )
                {
                  for( const auto& pSgbEntry : group.entries )
                  {
                    auto pModel = dynamic_cast< SGB_MODEL_ENTRY* >( pSgbEntry.get() );
                    fileName = pModel->collisionFileName;
                    if( pModel->type == SgbGroupEntryType::Gimmick )
                    {
                      if( auto pSubSgbFile = pCache->getSgbFile( pModel->modelFileName ) )
                      {
                        for( const auto& subGroup : pSubSgbFile->entries )
                        {
                          for( const auto& pSubEntry : subGroup.entries )
                          {
                            auto pSubModel = dynamic_cast< SGB_MODEL_ENTRY* >( pSubEntry.get() );
                            std::string subModelFile = pSubModel->modelFileName;
                            //"bg/ex1/02_dra_d2/alx/common/bgparts/d2a0_a7_btog2.mdl"
                            //"bg/ex1/02_dra_d2/alx/common/collision/d2a0_a1_twl01.pcb"
                           replaceAll( subModelFile, "/bgparts/", "/collision/" );
                           replaceAll( subModelFile, ".mdl", ".pcb ");

                            if( pSubModel && pSubModel->type == SgbGroupEntryType::Model )
                              pcbTransformModel( subModelFile, &pGimmick->header.scale, &pGimmick->header.rotation,
                                &pGimmick->header.translation, pSubModel );
                          }
                        }
                      }
                    }
                    pcbTransformModel( fileName, &pGimmick->header.scale, &pGimmick->header.rotation,
                      &pGimmick->header.translation, pModel );

                  }
                }
              }
            };
            switch( pEntry->getType() )
            {
              case LgbEntryType::BgParts:
              {
                auto pBgParts = static_cast< LGB_BGPARTS_ENTRY* >( pEntry.get() );
                fileName = pBgParts->collisionFileName;
                pcbTransformModel( fileName, &pBgParts->header.scale, &pBgParts->header.rotation,
                  &pBgParts->header.translation );
              }
              break;

              // gimmick entry
              case LgbEntryType::Gimmick:
              {
                auto pGimmick = static_cast< LGB_GIMMICK_ENTRY* >( pEntry.get() );

                exportSgbModel( pGimmick->gimmickFileName, pGimmick );
              }
              break;

              case LgbEntryType::EventObject:
              {
                auto pEobj = static_cast< LGB_EOBJ_ENTRY* >( pEntry.get() );
                pcbTransformModel( fileName, &pEntry->header.scale, &pEntry->header.rotation, &pEntry->header.translation );

                auto sgbPath = getEobjSgbPath( pEobj->header.eobjId );
                if ( !sgbPath.empty() )
                {
                  exportSgbModel( sgbPath, pEobj, true );

                  if( auto pGimmick = pCache->getSgbFile( sgbPath ) )
                  {
                    for( const auto& offset1cFile : pGimmick->stateEntries )
                      exportSgbModel( offset1cFile, pEobj, true );
                  }
                }
                
              }
              break;
              default:
                break;
            }
          }
          if( splitByGroup )
            exportMgr.exportGroup( zoneName, exportedGroup, ( ExportFileType )exportFileType );
          exportedZone.groups.emplace( group.name, exportedGroup );
        }
      }
      exportMgr.exportZone( exportedZone, static_cast< ExportFileType >( exportFileType ) );

      printf( "Built export struct for %s in %lu seconds \n",
        zoneName.c_str(),
        std::chrono::duration_cast< std::chrono::seconds >( std::chrono::high_resolution_clock::now() - entryStartTime ).count() );
      if( zoneCount++ % nJobs == 0 )
      {
        exportMgr.restart();
        pCache->purge();
      }
    }
    catch( std::exception& e )
    {
      printf( "%s", ( std::string( e.what() ) + "\n" ).c_str() );
      printf( "Unable to extract collision data.\n" );
      printf( "Usage: pcb_reader2 territory \"path/to/game/sqpack/ffxiv\"\n" );
    }
  }
  pCache->purge();
  exportMgr.waitForTasks();
  std::cout << "\n\n\n";

  printf( "Finished all tasks in %lu seconds\n",
            std::chrono::duration_cast< std::chrono::seconds >( std::chrono::high_resolution_clock::now() - startTime ).count() );

  delete eData;
  delete gameData;
  
  return 0;
}
