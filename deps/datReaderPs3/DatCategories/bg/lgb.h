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
#include "datReader/DatCategories/InstanceObject.h"
#include "datReaderPs3/DatCategories/bg/LgbTypes.h"
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
    header.InstanceID = xivps3::utils::bparse::byteswap( header.InstanceID );
    header.Name = xivps3::utils::bparse::byteswap( header.Name );
    header.AssetType = xivps3::utils::bparse::byteswap( header.AssetType );

    header.Transformation.Translation.x = xivps3::utils::bparse::byteswap( header.Transformation.Translation.x );
    header.Transformation.Translation.y = xivps3::utils::bparse::byteswap( header.Transformation.Translation.y );
    header.Transformation.Translation.z = xivps3::utils::bparse::byteswap( header.Transformation.Translation.z );

    header.Transformation.Rotation.x = xivps3::utils::bparse::byteswap( header.Transformation.Rotation.x );
    header.Transformation.Rotation.y = xivps3::utils::bparse::byteswap( header.Transformation.Rotation.y );
    header.Transformation.Rotation.z = xivps3::utils::bparse::byteswap( header.Transformation.Rotation.z );
  };

  const LgbEntryType getType() const
  {
    return static_cast< LgbEntryType >( header.AssetType );
  };

  virtual ~LgbEntry()
  {
  };
};


class LGB_BGPARTS_ENTRY : public LgbEntry
{
public:
  BgData data;
  std::string name;
  std::string modelFileName;
  std::string collisionFileName;

  LGB_BGPARTS_ENTRY()
  {
  };

  LGB_BGPARTS_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< BgData* >( buf + offset );
    data.CollisionAssetPath = xivps3::utils::bparse::byteswap( data.CollisionAssetPath );
    data.AssetPath = xivps3::utils::bparse::byteswap( data.AssetPath );
    data.Name = xivps3::utils::bparse::byteswap( data.Name );
    name = std::string( buf + offset + header.Name );
    modelFileName = std::string( buf + offset + data.AssetPath );
    collisionFileName = std::string( buf + offset + data.CollisionAssetPath );
  };
};

class LGB_SERVERPATH_ENTRY : public LgbEntry
{
public:
  ServerPathData data;
  std::vector< PathControlPoint > points;
  std::string name;

  LGB_SERVERPATH_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< ServerPathData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
    data.ControlPoint_Count = xivps3::utils::bparse::byteswap( data.ControlPoint_Count );
    data.ControlPoints = xivps3::utils::bparse::byteswap( data.ControlPoints );
    data.Reserved1 = xivps3::utils::bparse::byteswap( data.Reserved1 );
    data.Reserved2 = xivps3::utils::bparse::byteswap( data.Reserved2 );

    int innerOff = offset + data.ControlPoints;
    for( int i = 0; i < data.ControlPoint_Count; ++i )
    {
      PathControlPoint point;
      point = *reinterpret_cast< PathControlPoint* >( buf + innerOff );

      point.PointID = xivps3::utils::bparse::byteswap( point.PointID );
      point.Translation.x = xivps3::utils::bparse::byteswap( point.Translation.x );
      point.Translation.y = xivps3::utils::bparse::byteswap( point.Translation.y );
      point.Translation.z = xivps3::utils::bparse::byteswap( point.Translation.z );
      points.push_back( point );
      innerOff += sizeof( PathControlPoint );

    }

  };
};

class LGB_SG_ENTRY : public LgbEntry
{
public:
  SGData data;
  std::string name;
  std::string gimmickFileName;

  LGB_SG_ENTRY( char* buf, uint32_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< SGData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
    gimmickFileName = std::string( buf + offset + xivps3::utils::bparse::byteswap( data.AssetPath ) );


  };
};


class LGB_ENPC_ENTRY : public LgbEntry
{
public:
  ENPCData data;
  std::string name;

  LGB_ENPC_ENTRY( char* buf, uint32_t offset ) :
    LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< ENPCData* >( buf + offset );
    name = std::string( buf + offset +  header.Name );
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

    data.AssetType = xivps3::utils::bparse::byteswap( data.AssetType );
    data.InstanceID = xivps3::utils::bparse::byteswap( data.InstanceID );
    data.Name = xivps3::utils::bparse::byteswap( data.Name );

    data.Transformation.Translation.x = xivps3::utils::bparse::byteswap( data.Transformation.Translation.x );
    data.Transformation.Translation.y = xivps3::utils::bparse::byteswap( data.Transformation.Translation.y );
    data.Transformation.Translation.z = xivps3::utils::bparse::byteswap( data.Transformation.Translation.z );

    data.Transformation.Rotation.x = xivps3::utils::bparse::byteswap( data.Transformation.Rotation.x );
    data.Transformation.Rotation.y = xivps3::utils::bparse::byteswap( data.Transformation.Rotation.y );
    data.Transformation.Rotation.z = xivps3::utils::bparse::byteswap( data.Transformation.Rotation.z );

    data.Transformation.Scale.x = xivps3::utils::bparse::byteswap( data.Transformation.Scale.x );
    data.Transformation.Scale.y = xivps3::utils::bparse::byteswap( data.Transformation.Scale.y );
    data.Transformation.Scale.z = xivps3::utils::bparse::byteswap( data.Transformation.Scale.z );

    data.PopWeather = xivps3::utils::bparse::byteswap( data.PopWeather );
    data.MoveAI = xivps3::utils::bparse::byteswap( data.MoveAI );
    data.Level = xivps3::utils::bparse::byteswap( data.Level );
    data.NormalAI = xivps3::utils::bparse::byteswap( data.NormalAI );
    data.SenseRangeRate = xivps3::utils::bparse::byteswap( data.SenseRangeRate );
    data.ServerPathId = xivps3::utils::bparse::byteswap( data.ServerPathId );
    data.TerritoryRange = xivps3::utils::bparse::byteswap( data.TerritoryRange );
    data.VerticalPopRange = xivps3::utils::bparse::byteswap( data.VerticalPopRange );
    data.NameId = xivps3::utils::bparse::byteswap( data.NameId );

    name = std::string( buf + offset + header.Name );

    baseData = *reinterpret_cast< BNpcBaseData* >( buf + offset + data.BNpcBaseData );
    baseData.TerritoryRange = xivps3::utils::bparse::byteswap( baseData.TerritoryRange );

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
    name = std::string( buf + offset + header.Name );
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
    name = std::string( buf + offset + header.Name );
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
    name = std::string( buf + offset + header.Name );
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
          entries.push_back( std::make_shared< LGB_BGPARTS_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::SharedGroup )
        {
          entries.push_back( std::make_shared< LGB_SG_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::EventNpc )
        {
          entries.push_back( std::make_shared< LGB_ENPC_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::EventObject )
        {
          entries.push_back( std::make_shared< LGB_EOBJ_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::ExitRange )
        {
          entries.push_back( std::make_shared< LGB_EXIT_RANGE_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::MapRange )
        {
          entries.push_back( std::make_shared< LGB_MAP_RANGE_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::BattleNpc )
        {
          entries.push_back( std::make_shared< LGB_BNPC_ENTRY >( buf, entryOffset ) );
        }
        else if( type == LgbEntryType::ServerPath )
        {
          entries.push_back( std::make_shared< LGB_SERVERPATH_ENTRY >( buf, entryOffset ) );
        }
        else
        {
          entries.push_back( std::make_shared< LgbEntry >( buf, entryOffset ) );
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
    header = *reinterpret_cast< LGB_FILE_HEADER* >( buf );
    m_name = std::string( buf + 20 + xivps3::utils::bparse::byteswap( header.nameOff ) );
  }

  LGB_FILE( char* buf )
  {
    header = *reinterpret_cast< LGB_FILE_HEADER* >( buf );
    m_name = std::string( buf + 20 + xivps3::utils::bparse::byteswap( header.nameOff ) );
    header.fileSize = xivps3::utils::bparse::byteswap( header.fileSize );


 /*   header.unknown = xivps3::utils::bparse::byteswap( header.unknown );
    header.unknown2 = xivps3::utils::bparse::byteswap( header.unknown2 );
    header.unknown3 = xivps3::utils::bparse::byteswap( header.unknown3 );
    header.unknown4 = xivps3::utils::bparse::byteswap( header.unknown4 );
    header.unknown5 = xivps3::utils::bparse::byteswap( header.unknown5 );*/


    auto baseOffset = sizeof( header );

    header.chunkSize = xivps3::utils::bparse::byteswap( header.chunkSize );

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