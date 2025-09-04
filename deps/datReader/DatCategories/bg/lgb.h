#ifndef _LGB_H
#define _LGB_H

#include <cstring>
#include <memory>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "matrix4.h"
#include "vec3.h"
#include "sgb.h"
#include "DatCategories/bg/LgbTypes.h"
#include "DatCategories/Layer.h"

// based on https://github.com/ufx/SaintCoinach/blob/master/SaintCoinach/Graphics/Lgb/
struct LGB_FILE;
struct LGB_FILE_HEADER;
struct LGB_GROUP;
struct LGB_GROUP_HEADER;

class LgbEntry
{
public:
  char* m_buf;
  uint32_t m_offset;
  InstanceObject header;
  std::string name;
  LgbEntry()
  {
    m_buf = nullptr;
    m_offset = 0;
    header = {};
  };

  LgbEntry( char* buf, size_t offset )
  {
    m_buf = buf;
    m_offset = static_cast< uint32_t >( offset );
    header = *reinterpret_cast< InstanceObject* >( buf + offset );
  };

  const eAssetType getType() const
  {
    return static_cast< eAssetType >( header.AssetType );
  };

  virtual ~LgbEntry()
  {
  };
};


class LGB_BGPARTS_ENTRY : public LgbEntry
{
public:
  BgPartsData data;
  std::string modelFileName;
  std::string collisionFileName;

  LGB_BGPARTS_ENTRY() = default;

  LGB_BGPARTS_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< BgPartsData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
    modelFileName = std::string( buf + offset + data.AssetPath );
    collisionFileName = std::string( buf + offset + data.CollisionAssetPath );
  };
};






struct LGB_GROUP
{
  LGB_FILE* parent;
  Layer header;
  LayerSetReferencedList layerSetReferencedList;
  std::string name;
  std::vector< std::shared_ptr< InstanceObjectEntry > > entries;
  std::vector< LayerSetReferenced > refs;

  LGB_GROUP( char* buf, LGB_FILE* parentStruct, size_t offset )
  {
    parent = parentStruct;
    header = *reinterpret_cast< Layer* >( buf + offset );
    name = std::string( buf + offset + header.Name );

    //std::cout << name << " groups: " << header.InstanceObject_Count << " " << header.InstanceObjects << std::endl;

    layerSetReferencedList = *reinterpret_cast< LayerSetReferencedList* >( buf + offset + header.LayerSetRef );

    if( layerSetReferencedList.LayerSetCount > 0 )
    {
      refs.resize( layerSetReferencedList.LayerSetCount );
      memcpy( (char*)&refs[0], buf + offset + header.LayerSetRef + layerSetReferencedList.LayerSets, layerSetReferencedList.LayerSetCount * sizeof( LayerSetReferenced ) );
    }

    entries.reserve( header.InstanceObject_Count );

    const auto entriesOffset = offset + header.InstanceObjects;

    for( auto i = 0; i < header.InstanceObject_Count; ++i )
    {
      const auto entryOffset = entriesOffset + *reinterpret_cast< int32_t* >( buf + ( entriesOffset + i * 4 ) );

      try
      {
        const auto type = *reinterpret_cast< eAssetType* >( buf + entryOffset );
        switch( type )
        {
          case eAssetType::BG:
          {
            entries.emplace_back( std::make_shared< BGEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::SharedGroup:
          {
            entries.emplace_back( std::make_shared< SharedGroupEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::EventNPC:
          {
            entries.emplace_back( std::make_shared< EventNPCEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::EventObject:
          {
            entries.emplace_back( std::make_shared< EventObjectEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::ExitRange:
          {
            entries.emplace_back( std::make_shared< ExitRangeEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::EventRange:
          {
            entries.emplace_back( std::make_shared< EventRangeEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::PopRange:
          {
            entries.emplace_back( std::make_shared< PopRangeEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::MapRange:
          {
            entries.emplace_back( std::make_shared< MapRangeEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::BattleNPC:
          {
            entries.emplace_back( std::make_shared< BattleNPCEntry >( buf, entryOffset ) );
            break;
          }
          case eAssetType::CollisionBox:
          {
            entries.emplace_back( std::make_shared< CollisionBoxEntry >( buf, entryOffset ) );
            break;
          }
          default:
          {
            entries.emplace_back( std::make_shared< InstanceObjectEntry >( buf, entryOffset ) );
            break;
          }
        }
      }
      catch( std::exception& e )
      {
        std::cout << name << " " << e.what() << std::endl;
      }
    }
  };
};

struct LGB_FILE_HEADER
{
  char magic[4]; // LGB 1
  uint32_t fileSize;
  uint32_t totalChunkCount;
  char magic2[4]; // LGP1
  uint32_t chunkSize;
  uint32_t layerGroupId;
  uint32_t nameOff;
  uint32_t groups;
  int32_t groupCount;
};

struct LGB_FILE
{
  LGB_FILE_HEADER header;
  std::vector< LGB_GROUP > groups;
  std::string m_name;

  LGB_FILE( char* buf, const std::string& name ) : LGB_FILE( buf )
  {
    m_name = std::string( buf + 20 + header.nameOff );
  }

  LGB_FILE( char* buf )
  {
    header = *reinterpret_cast< LGB_FILE_HEADER* >( buf );
    m_name = std::string( buf + 20 +  header.nameOff );
    if( strncmp( &header.magic[ 0 ], "LGB1", 4 ) != 0 || strncmp( &header.magic2[ 0 ], "LGP1", 4 ) != 0 )
      throw std::runtime_error( "Invalid LGB file!" );

    constexpr auto baseOffset = sizeof( header );
    for( size_t i = 0; i < header.groupCount; ++i )
    {
      const auto groupOffset = baseOffset + *reinterpret_cast< int32_t* >( buf + ( baseOffset + i * 4 ) );
      const auto group = LGB_GROUP( buf, this, groupOffset );
      groups.push_back( group );
    }
  };
};

/*
#if __cplusplus >= 201703L
#include <experimental/filesystem>
std::map<std::string, LGB_FILE> getLgbFiles( const std::string& dir )
{
   namespace fs = std::experimental::filesystem;
   std::map<std::string, LGB_FILE> fileMap;
   for( const auto& path : fs::recursive_directory_iterator( dir ) )
   {
      if( path.path().extension() == ".lgb" )
      {
         const auto& strPath = path.path().string();
         auto f = fopen( strPath.c_str(), "rb" );
         fseek( f, 0, SEEK_END );
         const auto size = ftell( f );
         std::vector<char> bytes( size );
         rewind( f );
         fread( bytes.data(), 1, size, f );
         fclose( f );
         try
         {
            LGB_FILE lgbFile( bytes.data() );
            fileMap.insert( std::make_pair( strPath, lgbFile ) );
         }
         catch( std::exception& e )
         {
            std::cout << "Unable to load " << strPath << std::endl;
         }
      }
   }
   return fileMap;
}
#endif
*/
#endif
