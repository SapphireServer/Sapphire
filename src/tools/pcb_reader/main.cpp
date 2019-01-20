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

#include <condition_variable>

#include <recastnavigation/Recast/Include/Recast.h>
#include <recastnavigation/Recast/Include/RecastAlloc.h>


// garbage to ignore models
bool noObj = false;

std::string gamePath( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
std::unordered_map< uint16_t, std::string > zoneNameMap;
uint32_t zoneId;

std::set< std::string > zoneDumpList;

std::shared_ptr< Cache > pCache;

xiv::dat::GameData* data1 = nullptr;
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
  data1 = data1 ? data1 : new xiv::dat::GameData( gamePath );
  eData = eData ? eData : new xiv::exd::ExdData( *data1 );
  pCache = std::make_shared< Cache >( data1 );
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
    std::cout << "[Info] " << "Found path for " << name << ": " << path << std::endl;
  }
  else
  {
    throw std::runtime_error( "Unable to find path for " + name +
                              ".\n\tPlease double check spelling or open 0a0000.win32.index with FFXIV Explorer and extract territorytype.exh as CSV\n\tand copy territorytype.exh.csv into pcb_reader.exe directory if using standalone" );
  }

  return path;
}

int main( int argc, char* argv[] )
{
  auto startTime = std::chrono::high_resolution_clock::now();
  auto entryStartTime = std::chrono::high_resolution_clock::now();

  std::vector< std::string > argVec( argv + 1, argv + argc );
  std::string zoneName = "r2t2";

  noObj = std::remove_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--no-obj"; } ) != argVec.end();
  bool dumpAllZones = std::remove_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--dump-all"; } ) != argVec.end();
  bool generateNavmesh = std::remove_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--navmesh"; } ) != argVec.end();

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
  }
  catch( std::exception& e )
  {
    std::cout << "Unable to initialise EXD! Usage: pcb_reader <teri> \"path/to/FINAL FANTASY XIV - A REALM REBORN/game/sqpack\"" << std::endl;
    return -1;
  }
  ExportMgr exportMgr;
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

  for( const auto& zoneName : zoneDumpList )
  {
    try
    {
      ExportedZone exportedZone;
      exportedZone.name = zoneName;

      const auto& zonePath = zoneNameToPath( zoneName );

      std::string listPcbPath( zonePath + "/collision/list.pcb" );
      std::string bgLgbPath( zonePath + "/level/bg.lgb" );
      std::string planmapLgbPath( zonePath + "/level/planmap.lgb" );
      std::string collisionFilePath( zonePath + "/collision/" );
      std::vector< char > section;
      std::vector< char > section1;
      std::vector< char > section2;

      const xiv::dat::Cat& test = data1->getCategory( "bg" );

      auto test_file = data1->getFile( bgLgbPath );
      section = test_file->access_data_sections().at( 0 );

      auto planmap_file = data1->getFile( planmapLgbPath );
      section2 = planmap_file->access_data_sections().at( 0 );

      auto test_file1 = data1->getFile( listPcbPath );
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

      {

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

          uint32_t groupCount = 0;
          for( const auto& entry : pcb_file.entries )
          {
            ExportedMesh mesh;

            int verts = 0;
            int indices = 0;
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

            //fprintf( fp_out, "g %s_", (name2 + "_" + std::to_string( groupCount++ )).c_str() );
            for( const auto& index : entry.data.indices )
            {
              mesh.indices[ indices++ ] = index.index[ 0 ];
              mesh.indices[ indices++ ] = index.index[ 1 ];
              mesh.indices[ indices++ ] = index.index[ 2 ];
              // std::cout << std::to_string( index.unknown[0] )<< " " << std::to_string( index.unknown[1] )<< " " << std::to_string( index.unknown[2]) << std::endl;
            }
            max_index += entry.data.vertices.size() + entry.data.vertices_i16.size();
            model.meshes.push_back( mesh );
          }
          exportedGroup.models[model.name] = model;
        };
        ExportedGroup exportedTerrainGroup;
        exportedTerrainGroup.name = zoneName;
        for( const auto& fileName : stringList )
        {
          if( auto pPcbFile = pCache->getPcbFile( fileName ) )
            buildModelEntry( pPcbFile, exportedTerrainGroup, fileName, zoneName );
        }
        
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
              auto writeOutput = [&](const std::string& fileName, const vec3* scale, const vec3* rotation,
                const vec3* translation, const SGB_MODEL_ENTRY* pModel = nullptr)->bool
              {
                if( auto pPcbFile = pCache->getPcbFile( fileName ) )
                {
                  buildModelEntry( pPcbFile, exportedGroup, fileName, group.name, scale, rotation, translation, pModel );
                }
                return true;
              };

              switch( pEntry->getType() )
              {
                case LgbEntryType::BgParts:
                {
                  auto pBgParts = static_cast<LGB_BGPARTS_ENTRY*>(pEntry.get());
                  fileName = pBgParts->collisionFileName;
                  writeOutput( fileName, &pBgParts->header.scale, &pBgParts->header.rotation,
                    &pBgParts->header.translation );
                }
                break;

                // gimmick entry
                case LgbEntryType::Gimmick:
                {
                  auto pGimmick = static_cast<LGB_GIMMICK_ENTRY*>(pEntry.get());
                  if (auto pSgbFile = pCache->getSgbFile(pGimmick->gimmickFileName))
                  {
                    const auto& sgbFile = *pSgbFile;
                    for (const auto& group : sgbFile.entries)
                    {
                      for (const auto& pEntry : group.entries)
                      {
                        auto pModel = dynamic_cast<SGB_MODEL_ENTRY*>(pEntry.get());
                        fileName = pModel->collisionFileName;
                        writeOutput( fileName, &pGimmick->header.scale, &pGimmick->header.rotation,
                          &pGimmick->header.translation, pModel );
                      }
                    }
                  }
                }

                case LgbEntryType::EventObject:
                {
                  writeOutput( fileName, &pEntry->header.scale, &pEntry->header.rotation, &pEntry->header.translation );
                }
                break;
                default:
                  break;
              }
            }
            exportMgr.exportGroup( zoneName, exportedGroup, ( ExportFileType )exportFileType );
            //exportedZone.groups.emplace( group.name, exportedGroup );
          }
        }
        //exportMgr.exportZone( exportedZone, ( ExportFileType )exportFileType );
        //std::cout << "[Info] " << "Loaded " << pcbFiles.size() << " PCB Files \n";
        std::cout << "[Info] " << "Total Groups " << totalGroups << "\n";
      }

      std::cout << "[Success] " << "Exported " << zoneName << " in " <<
                std::chrono::duration_cast< std::chrono::seconds >(
                  std::chrono::high_resolution_clock::now() - entryStartTime ).count() << " seconds\n";
    }
    catch( std::exception& e )
    {
      std::cout << "[Error] " << e.what() << std::endl;
      std::cout << "[Error] "
                << "Unable to extract collision data.\n"
                << std::endl;
      std::cout << std::endl;
      std::cout << "[Info] " << "Usage: pcb_reader2 territory \"path/to/game/sqpack/ffxiv\" " << std::endl;
    }
  }
  exportMgr.waitForTasks();
  std::cout << "\n\n\n";

  std::cout << "\n\n\n[Success] Finished all tasks in " <<
            std::chrono::duration_cast< std::chrono::seconds >( std::chrono::high_resolution_clock::now() - startTime ).count()
            << " seconds\n";

  getchar();

  if( eData )
    delete eData;
  if( data1 )
    delete data1;
  return 0;
}
