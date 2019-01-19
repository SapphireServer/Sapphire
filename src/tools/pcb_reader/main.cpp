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
bool ignoreModels = false;

std::string gamePath( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
std::unordered_map< uint16_t, std::string > zoneNameMap;
uint32_t zoneId;

std::set< std::string > zoneDumpList;

xiv::dat::GameData* data1 = nullptr;
xiv::exd::ExdData* eData = nullptr;

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

void initExd( const std::string& gamePath )
{
  data1 = data1 ? data1 : new xiv::dat::GameData( gamePath );
  eData = eData ? eData : new xiv::exd::ExdData( *data1 );
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

int main( int argc, char* argv[] )
{
  auto startTime = std::chrono::system_clock::now();
  auto entryStartTime = std::chrono::system_clock::now();

  std::vector< std::string > argVec( argv + 1, argv + argc );
  std::string zoneName = "r2t2";
  bool dumpAllZones = std::remove_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--dump-all"; } ) != argVec.end();
  bool generateNavmesh = std::remove_if( argVec.begin(), argVec.end(), []( auto arg )
  { return arg == "--navmesh"; } ) != argVec.end();
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

  std::mutex navmeshMutex;
  std::queue< std::string > exportedGroups;

  std::string exportArg( "RecastDemo.exe --type tileMesh --obj " );
  std::thread navmeshThread( [&navmeshMutex, &exportedGroups, &exportArg, &generateNavmesh]()
  {
    while( generateNavmesh )
    {
      std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
      std::lock_guard< std::mutex > lock( navmeshMutex );
      {
        if( !exportedGroups.empty() )
        {
          auto& currFile = exportedGroups.front();
          std::cout << "\nGenerating navmesh for " << currFile << std::endl;
          system( ( exportArg + currFile ).c_str() );
          std::cout << "\nFinished generating navmesh for " << currFile << std::endl;
          exportedGroups.pop();
        }
      }
    }
  });
  navmeshThread.detach();

  LABEL_DUMP:
  entryStartTime = std::chrono::system_clock::now();
  zoneName = *zoneDumpList.begin();
  try
  {
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
    LGB_FILE bgLgb( &section[ 0 ], "bg" );
    LGB_FILE planmapLgb( &section2[ 0 ], "planmap" );

    std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb };
    uint32_t max_index = 0;

    // dont bother if we cant write to a file
    auto fp_out = ignoreModels ? ( FILE* ) nullptr : fopen( ( zoneName + ".obj" ).c_str(), "w" );
    if( fp_out )
    {
      fprintf( fp_out, "\n" );
      fclose( fp_out );
    }
    else if( !ignoreModels )
    {
      std::string errorMessage( "Cannot create " + zoneName + ".obj\n" +
                                " Check no programs have a handle to file and run as admin.\n" );
      std::cout << errorMessage;
      throw std::runtime_error( errorMessage.c_str() );
      return 0;
    }

    if( ignoreModels || ( fp_out = fopen( ( zoneName + ".obj" ).c_str(), "ab+" ) ) )
    {
      std::map< std::string, PCB_FILE > pcbFiles;
      std::map< std::string, SGB_FILE > sgbFiles;
      std::map< std::string, uint32_t > objCount;
      auto loadPcbFile = [ & ]( const std::string& fileName )->bool
      {
        if( ignoreModels )
          return false;
        try
        {
          if( fileName.find( '.' ) == std::string::npos )
            return false;
          else if( fileName.substr( fileName.find_last_of( '.' ) ) != ".pcb" )
            throw std::runtime_error( "Not a PCB file." );

          char* dataSection = nullptr;
          //std::cout << fileName << " ";
          auto file = data1->getFile( fileName );
          auto sections = file->get_data_sections();
          dataSection = &sections.at( 0 )[ 0 ];
          //std::cout << sections.size() << "\n";

          uint32_t offset = 0;
          PCB_FILE pcb_file;
          memcpy( &pcb_file.header, &dataSection[ 0 ], sizeof( pcb_file.header ) );
          offset += sizeof( pcb_file.header );
          pcb_file.entries.resize( pcb_file.header.num_entries );
          bool isgroup = true;
          while( isgroup )
          {
            PCB_BLOCK_ENTRY block_entry;
            memcpy( &block_entry.header, &dataSection[ 0 ] + offset, sizeof( block_entry.header ) );
            isgroup = block_entry.header.type == 0x30;

            //printf( "BLOCKHEADER_%X: type: %i, group_size: %i\n", offset, block_entry.header.type, block_entry.header.group_size );
            //
            if( isgroup )
            {
              parseBlockEntry( &dataSection[ 0 ] + offset + 0x30, pcb_file.entries, offset );
              offset += block_entry.header.group_size;
            }
            else
            {
              parseBlockEntry( &dataSection[ 0 ] + offset, pcb_file.entries, offset );
            }
          }
          pcbFiles.insert( std::make_pair( fileName, pcb_file ) );
          return true;
        }
        catch( std::exception& e )
        {
          std::cout << "[Error] " << "Unable to load collision mesh " << fileName << "\n\tError:\n\t" << e.what()
                    << "\n";
          return false;
        }
      };

      auto loadSgbFile = [ & ]( const std::string& fileName )->bool
      {
        SGB_FILE sgbFile;
        try
        {
          char* dataSection = nullptr;
          //std::cout << fileName << " ";

          auto file = data1->getFile( fileName );
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
      auto writeToFile = [ & ]( const PCB_FILE& pcb_file, const std::string& name, const std::string& groupName,
                              const vec3* scale = nullptr,
                              const vec3* rotation = nullptr,
                              const vec3* translation = nullptr,
                              const SGB_MODEL_ENTRY* pSgbEntry = nullptr )
      {
        char name2[0x100];
        memset( name2, 0, 0x100 );
        sprintf( &name2[ 0 ], "%s_%u", &name[ 0 ], objCount[ name ]++ );
        fprintf( fp_out, "o %s\n", &name2[ 0 ] );

        uint32_t groupCount = 0;
        for( const auto& entry : pcb_file.entries )
        {
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
            fprintf( fp_out, "v %f %f %f\n", v.x, v.y, v.z );
          }

          for( const auto& link : entry.data.vertices_i16 )
          {
            vec3 v( float( link.x ) / 0xFFFF, float( link.y ) / 0xFFFF, float( link.z ) / 0xFFFF );

            v.x = v.x * x_base + entry.header.x;
            v.y = v.y * y_base + entry.header.y;
            v.z = v.z * z_base + entry.header.z;

            makeTranslation( v );
            fprintf( fp_out, "v %f %f %f\n", v.x, v.y, v.z );
          }

          //fprintf( fp_out, "g %s_", (name2 + "_" + std::to_string( groupCount++ )).c_str() );
          for( const auto& index : entry.data.indices )
          {
            fprintf( fp_out, "f %i %i %i\n",
                     index.index[ 0 ] + max_index + 1,
                     index.index[ 1 ] + max_index + 1,
                     index.index[ 2 ] + max_index + 1 );
            // std::cout << std::to_string( index.unknown[0] )<< " " << std::to_string( index.unknown[1] )<< " " << std::to_string( index.unknown[2]) << std::endl;
          }
          max_index += entry.data.vertices.size() + entry.data.vertices_i16.size();
        }
      };

      for( const auto& fileName : stringList )
      {
        loadPcbFile( fileName );
        writeToFile( pcbFiles[ fileName ], fileName, zoneName );
      }

      std::cout << "[Info] " << "Writing obj file " << "\n";
      uint32_t totalGroups = 0;
      uint32_t totalGroupEntries = 0;

      for( const auto& lgb : lgbList )
      {
        for( const auto& group : lgb.groups )
        {
          max_index = 0;
          std::string outfile_name( zoneName + "_" + group.name + ".obj" );

          fp_out = fopen( outfile_name.c_str(), "w" );
          if( fp_out )
          {
            fprintf( fp_out, "" );
            fclose( fp_out );
            fp_out = fopen( outfile_name.c_str(), "ab+" );
          }
          //std::cout << "\t" << group.name << " Size " << group.header.entryCount << "\n";
          totalGroups++;
          for( const auto& pEntry : group.entries )
          {
            auto pGimmick = dynamic_cast< LGB_GIMMICK_ENTRY* >( pEntry.get() );
            auto pBgParts = dynamic_cast< LGB_BGPARTS_ENTRY* >( pEntry.get() );

            std::string fileName( "" );
            fileName.resize( 256 );
            totalGroupEntries++;

            // write files
            auto writeOutput = [ & ]( const std::string& fileName, const vec3* scale, const vec3* rotation,
                                      const vec3* translation, const SGB_MODEL_ENTRY* pModel = nullptr )->bool
            {
              {
                const auto& it = pcbFiles.find( fileName );
                if( it == pcbFiles.end() )
                {
                  if( fileName.empty() || !loadPcbFile( fileName ) )
                    return false;
                  //std::cout << "\t\tLoaded PCB File " << pBgParts->collisionFileName << "\n";
                }
              }
              const auto& it = pcbFiles.find( fileName );
              if( it != pcbFiles.end() )
              {
                const auto& pcb_file = it->second;
                writeToFile( pcb_file, fileName, group.name, scale, rotation, translation, pModel );
              }
              return true;
            };

            if( pBgParts )
            {
              fileName = pBgParts->collisionFileName;
              writeOutput( fileName, &pBgParts->header.scale, &pBgParts->header.rotation,
                           &pBgParts->header.translation );
            }

            // gimmick entry
            if( pGimmick )
            {
              {
                const auto& it = sgbFiles.find( pGimmick->gimmickFileName );
                if( it == sgbFiles.end() )
                {
                  // std::cout << "\tGIMMICK:\n\t\t" << pGimmick->gimmickFileName << "\n";
                  loadSgbFile( pGimmick->gimmickFileName );
                }
              }
              const auto& it = sgbFiles.find( pGimmick->gimmickFileName );
              if( it != sgbFiles.end() )
              {
                const auto& sgbFile = it->second;
                for( const auto& group : sgbFile.entries )
                {
                  for( const auto& pEntry : group.entries )
                  {
                    auto pModel = dynamic_cast< SGB_MODEL_ENTRY* >( pEntry.get() );
                    fileName = pModel->collisionFileName;
                    writeOutput( fileName, &pGimmick->header.scale, &pGimmick->header.rotation,
                                 &pGimmick->header.translation, pModel );
                  }
                }
              }
            }

            if( pEntry->getType() == LgbEntryType::EventObject )
            {
              writeOutput( fileName, &pEntry->header.scale, &pEntry->header.rotation, &pEntry->header.translation );
            }
          }
          if( fp_out )
            fclose( fp_out );
          std::lock_guard< std::mutex > lock( navmeshMutex );
          exportedGroups.push( outfile_name );
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
              << "Unable to extract collision data.\n"
              << std::endl;
    std::cout << std::endl;
    std::cout << "[Info] " << "Usage: pcb_reader2 territory \"path/to/game/sqpack/ffxiv\" " << std::endl;
  }
  std::cout << "\n\n\n";
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
