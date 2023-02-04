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
#include "LgbTypes.h"
#include "../../bparse.h"


// based on https://github.com/ufx/SaintCoinach/blob/master/SaintCoinach/Graphics/Lgb/
struct LGB_FILE;
struct LGB_FILE_HEADER;
struct LGB_GROUP;
struct LGB_GROUP_HEADER;

/* 253494 */
struct LayerSetReferenced
{
  uint32_t LayerSetID;
};

/* 253496 */
enum LayerSetReferencedType : int32_t
{
  All = 0x0,
  Include = 0x1,
  Exclude = 0x2,
  Undetermined = 0x3,
};

/* 253495 */
struct LayerSetReferencedList
{
  LayerSetReferencedType ReferencedType;
  int32_t LayerSets;
  int32_t LayerSet_Count;
};


class LgbEntry
{
public:
  char* m_buf;
  uint32_t m_offset;
  InstanceObject header;

  LgbEntry()
  {
    m_buf = nullptr;
    m_offset = 0;
    memset( &header, 0, sizeof( header ) );
  };

  LgbEntry( char* buf, uint32_t offset )
  {
    m_buf = buf;
    m_offset = offset;
    header = *reinterpret_cast< InstanceObject* >( buf + offset );
    header.instanceId = xivps3::utils::bparse::byteswap( header.instanceId );
    header.nameOffset = xivps3::utils::bparse::byteswap( header.nameOffset );
    header.type = xivps3::utils::bparse::byteswap( header.type );

    header.transform.translation.x = xivps3::utils::bparse::byteswap( header.transform.translation.x );
    header.transform.translation.y = xivps3::utils::bparse::byteswap( header.transform.translation.y );
    header.transform.translation.z = xivps3::utils::bparse::byteswap( header.transform.translation.z );

    header.transform.rotation.x = xivps3::utils::bparse::byteswap( header.transform.rotation.x );
    header.transform.rotation.y = xivps3::utils::bparse::byteswap( header.transform.rotation.y );
    header.transform.rotation.z = xivps3::utils::bparse::byteswap( header.transform.rotation.z );
  };

  const LgbEntryType getType() const
  {
    return header.type;
  };

  virtual ~LgbEntry()
  {
  };
};


class LGB_BGPARTS_ENTRY : public LgbEntry
{
public:
  BgPartsData data;
  std::string name;
  std::string modelFileName;
  std::string collisionFileName;

  LGB_BGPARTS_ENTRY()
  {
  };

  LGB_BGPARTS_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< BgPartsData* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
    modelFileName = std::string( buf + offset + data.modelFileOffset );
    collisionFileName = std::string( buf + offset + data.collisionFileOffset );
  };
};

class LGB_GIMMICK_ENTRY : public LgbEntry
{
public:
  GimmickData data;
  std::string name;
  std::string gimmickFileName;

  LGB_GIMMICK_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< GimmickData* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
    gimmickFileName = std::string( buf + offset + data.gimmickFileOffset );
  };
};

class LGB_ENPC_ENTRY : public LgbEntry
{
public:
  ENpcData data;
  std::string name;

  LGB_ENPC_ENTRY( char* buf, uint32_t offset ) :
    LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< ENpcData* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
  };
};

class LGB_BNPC_ENTRY : public LgbEntry
{
public:
  BNPCInstanceObject data;
  BNpcBaseData baseData;
  std::string name;

  LGB_BNPC_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< BNPCInstanceObject* >( buf + offset );
    data.BaseId = xivps3::utils::bparse::byteswap( data.BaseId );
    data.BNpcBaseData = xivps3::utils::bparse::byteswap( data.BNpcBaseData );
    data.BoundInstanceID = xivps3::utils::bparse::byteswap( data.BoundInstanceID );
    data.CustomizeID = xivps3::utils::bparse::byteswap( data.CustomizeID );
    data.DropItem = xivps3::utils::bparse::byteswap( data.DropItem );
    data.EquipmentID = xivps3::utils::bparse::byteswap( data.EquipmentID );
    data.EventGroup = xivps3::utils::bparse::byteswap( data.EventGroup );
    data.FateLayoutLabelId = xivps3::utils::bparse::byteswap( data.FateLayoutLabelId );
    data.HorizontalPopRange = xivps3::utils::bparse::byteswap( data.HorizontalPopRange );

    data.type = xivps3::utils::bparse::byteswap( data.type );
    data.instanceId = xivps3::utils::bparse::byteswap( data.instanceId );
    data.nameOffset = xivps3::utils::bparse::byteswap( data.nameOffset );

    data.transform.translation.x = xivps3::utils::bparse::byteswap( data.transform.translation.x );
    data.transform.translation.y = xivps3::utils::bparse::byteswap( data.transform.translation.y );
    data.transform.translation.z = xivps3::utils::bparse::byteswap( data.transform.translation.z );

    data.transform.rotation.x = xivps3::utils::bparse::byteswap( data.transform.rotation.x );
    data.transform.rotation.y = xivps3::utils::bparse::byteswap( data.transform.rotation.y );
    data.transform.rotation.z = xivps3::utils::bparse::byteswap( data.transform.rotation.z );

    data.transform.scale.x = xivps3::utils::bparse::byteswap( data.transform.scale.x );
    data.transform.scale.y = xivps3::utils::bparse::byteswap( data.transform.scale.y );
    data.transform.scale.z = xivps3::utils::bparse::byteswap( data.transform.scale.z );

    data.PopWeather = xivps3::utils::bparse::byteswap( data.PopWeather );
    data.MoveAI = xivps3::utils::bparse::byteswap( data.MoveAI );
    data.Level = xivps3::utils::bparse::byteswap( data.Level );
    data.NormalAI = xivps3::utils::bparse::byteswap( data.NormalAI );
    data.SenseRangeRate = xivps3::utils::bparse::byteswap( data.SenseRangeRate );
    data.ServerPathId = xivps3::utils::bparse::byteswap( data.ServerPathId );
    data.TerritoryRange = xivps3::utils::bparse::byteswap( data.TerritoryRange );
    data.VerticalPopRange = xivps3::utils::bparse::byteswap( data.VerticalPopRange );
    data.NameId = xivps3::utils::bparse::byteswap( data.NameId );

    name = std::string( buf + offset + header.nameOffset );

    baseData = *reinterpret_cast< BNpcBaseData* >( buf + offset + data.BNpcBaseData );

    baseData.TerritoryRange = xivps3::utils::bparse::byteswap( baseData.TerritoryRange );

    std::cout << data.BNpcBaseData << "\n";

  };
};

struct LGB_EOBJ_ENTRY : public LgbEntry
{
public:
  EObjData data;
  std::string name;

  LGB_EOBJ_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< EObjData* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
  };
};

struct LGB_MAP_RANGE_ENTRY : public LgbEntry
{
public:
  MapRangeData data;
  std::string name;

  LGB_MAP_RANGE_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< MapRangeData* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
  };
};

struct LGB_EXIT_RANGE_ENTRY : public LgbEntry
{
public:
  ExitRangeData data;
  std::string name;

  LGB_EXIT_RANGE_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< ExitRangeData* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
  };
};

struct LGB_POP_RANGE_ENTRY : public LgbEntry
{
public:
  PopRangeData data;

  LGB_POP_RANGE_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< PopRangeData* >( buf + offset );
  };
};

struct LGB_GROUP_HEADER
{
  uint32_t id;
  int32_t groupNameOffset;
  int32_t entriesOffset;
  int32_t entryCount;
  int8_t ToolModeVisible;
  int8_t ToolModeReadOnly;
  int8_t IsBushLayer;
  int8_t PS3Visible;
  int32_t LayerSetRef;
  uint16_t FestivalID;
  uint16_t FestivalPhaseID;
  int8_t IsTemporary;
  int8_t IsHousing;
  uint16_t VersionMask;
  uint32_t Reserved;
  int32_t OBSetReferencedList;
  int32_t OBSetReferencedList_Count;
  int32_t OBSetEnableReferencedList;
  int32_t OBSetEnableReferencedList_Count;
};

struct LGB_GROUP
{
  LGB_FILE* parent;
  LGB_GROUP_HEADER header;
  LayerSetReferencedList layerSetReferencedList;

  std::string name;
  std::vector< std::shared_ptr< LgbEntry > > entries;
  std::vector< LayerSetReferenced > refs;

  LGB_GROUP( char* buf, LGB_FILE* parentStruct, uint32_t offset )
  {
    parent = parentStruct;
    header = *reinterpret_cast< LGB_GROUP_HEADER* >( buf + offset );
    header.entriesOffset = xivps3::utils::bparse::byteswap( header.entriesOffset );
    header.entryCount = xivps3::utils::bparse::byteswap( header.entryCount );
    header.groupNameOffset = xivps3::utils::bparse::byteswap( header.groupNameOffset );
    header.LayerSetRef = xivps3::utils::bparse::byteswap( header.LayerSetRef );
    header.id = xivps3::utils::bparse::byteswap( header.id );
    name = std::string( buf + offset + header.groupNameOffset );

    layerSetReferencedList = *reinterpret_cast< LayerSetReferencedList* >( buf + offset + header.LayerSetRef );
    layerSetReferencedList.LayerSet_Count = xivps3::utils::bparse::byteswap( layerSetReferencedList.LayerSet_Count );
    layerSetReferencedList.LayerSets = xivps3::utils::bparse::byteswap( layerSetReferencedList.LayerSets );
    layerSetReferencedList.ReferencedType = xivps3::utils::bparse::byteswap( layerSetReferencedList.ReferencedType );

    if( layerSetReferencedList.LayerSet_Count > 0 )
    {
      refs.resize( layerSetReferencedList.LayerSet_Count );
      memcpy( (char*)&refs[0], buf + offset + header.LayerSetRef + layerSetReferencedList.LayerSets, layerSetReferencedList.LayerSet_Count * sizeof( LayerSetReferenced ) );

      for( auto& ref : refs )
      {
        ref = xivps3::utils::bparse::byteswap( ref );
      }
    }
    const auto entriesOffset = offset + header.entriesOffset;
    for( auto i = 0; i < header.entryCount; ++i )
    {

      const auto entryOffset = entriesOffset + xivps3::utils::bparse::byteswap( *reinterpret_cast< int32_t* >( buf + ( entriesOffset + i * 4 ) ) );

      try
      {
        const auto type =  xivps3::utils::bparse::byteswap( *reinterpret_cast< LgbEntryType* >( buf + entryOffset ) );
        if( type == LgbEntryType::BgParts )
        {
        //  entries.push_back( std::make_shared< LGB_BGPARTS_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::Gimmick )
        {
        //  entries.push_back( std::make_shared< LGB_GIMMICK_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::EventNpc )
        {
        //  entries.push_back( std::make_shared< LGB_ENPC_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::EventObject )
        {
        //  entries.push_back( std::make_shared< LGB_EOBJ_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::ExitRange )
        {
        //  entries.push_back( std::make_shared< LGB_EXIT_RANGE_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::MapRange )
        {
        //  entries.push_back( std::make_shared< LGB_MAP_RANGE_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::BattleNpc )
        {
          entries.push_back( std::make_shared< LGB_BNPC_ENTRY >( buf, entryOffset ) );
        }
        else
        {
       //   entries.push_back( std::make_shared< LgbEntry >( buf, entryOffset ) );
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
  uint32_t unknown;
  char magic2[4]; // LGP1
  uint32_t dataOffset;
  uint32_t unknown3;
  uint32_t unknown4;
  uint32_t unknown5;
  int32_t groupCount;
};

struct LGB_FILE
{
  LGB_FILE_HEADER header;
  std::vector< LGB_GROUP > groups;
  std::string m_name;

  LGB_FILE( char* buf, const std::string& name ) : LGB_FILE( buf )
  {
    m_name = name;
  }

  LGB_FILE( char* buf )
  {
    header = *reinterpret_cast< LGB_FILE_HEADER* >( buf );

    header.fileSize = xivps3::utils::bparse::byteswap( header.fileSize );


 /*   header.unknown = xivps3::utils::bparse::byteswap( header.unknown );
    header.unknown2 = xivps3::utils::bparse::byteswap( header.unknown2 );
    header.unknown3 = xivps3::utils::bparse::byteswap( header.unknown3 );
    header.unknown4 = xivps3::utils::bparse::byteswap( header.unknown4 );
    header.unknown5 = xivps3::utils::bparse::byteswap( header.unknown5 );*/


    auto baseOffset = sizeof( header );

    header.dataOffset = xivps3::utils::bparse::byteswap( header.dataOffset );

    if( strncmp( &header.magic[ 0 ], "LGB1", 4 ) != 0 )
      throw std::runtime_error( "Invalid LGB file!" );

   if( strncmp( &header.magic2[ 0 ], "LGP1", 4 ) != 0  )
    {
      throw std::runtime_error( "Invalid LGB file, LGP section not found!" );
      /*     if( strncmp( &header.magic2[ 0 ] + 0x14 , "LGP1", 4 ) == 0 )
          {
            memcpy( &header.magic2[ 0 ], buf + 0x20, 24 );
            baseOffset = 0x44;

            header.dataOffset = *reinterpret_cast< int32_t* >( buf + 0x24 );
            header.dataOffset = xivps3::utils::bparse::byteswap( header.dataOffset );
            header.groupCount = *reinterpret_cast< int32_t* >( buf + 0x20 + header.dataOffset );
          }
          else
            throw std::runtime_error( "Invalid LGB file, LGP section not found!" );

    */
    }

    header.groupCount = xivps3::utils::bparse::byteswap( header.groupCount );

    for( auto i = 0; i < header.groupCount; ++i )
    {
      auto groupOffset = *reinterpret_cast< int32_t* >( buf + ( baseOffset + i * 4 ) );
      groupOffset = baseOffset + xivps3::utils::bparse::byteswap( groupOffset );
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