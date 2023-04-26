#pragma once

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

  LgbEntry()
  {
    m_buf = nullptr;
    m_offset = 0;
    memset( &header, 0, sizeof( header ) );
  };

  LgbEntry( char* buf, size_t offset )
  {
    m_buf = buf;
    m_offset = static_cast< uint32_t >( offset );
    header = *reinterpret_cast< InstanceObject* >( buf + offset );
  };

  const LgbEntryType getType() const
  {
    return header.type;
  };

  virtual ~LgbEntry(){};
};

class LGB_BGPARTS_ENTRY : public LgbEntry
{
public:
  BgPartsData data;
  std::string_view name;
  std::string_view modelFileName;
  std::string_view collisionFileName;

  LGB_BGPARTS_ENTRY() = default;

  LGB_BGPARTS_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< BgPartsData* >( buf + offset );
    name = std::string_view( buf + offset + header.nameOffset );
    modelFileName = std::string_view( buf + offset + data.modelFileOffset );
    collisionFileName = std::string_view( buf + offset + data.collisionFileOffset );
  };
};

class LGB_GIMMICK_ENTRY : public LgbEntry
{
public:
  GimmickData data;
  std::string_view name;
  std::string_view gimmickFileName;

  LGB_GIMMICK_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< GimmickData* >( buf + offset );
    name = std::string_view( buf + offset + header.nameOffset );
    gimmickFileName = std::string_view( buf + offset + data.gimmickFileOffset );
  };
};

struct LGB_ENPC_ENTRY : public LgbEntry
{
public:
  ENpcData data;
  std::string_view name;

  LGB_ENPC_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< ENpcData* >( buf + offset );
    name = std::string_view( buf + offset + header.nameOffset );
  };
};

struct LGB_EOBJ_ENTRY : public LgbEntry
{
public:
  EObjData data;
  std::string_view name;

  LGB_EOBJ_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< EObjData* >( buf + offset );
    name = std::string_view( buf + offset + header.nameOffset );
  };
};

struct LGB_MAP_RANGE_ENTRY : public LgbEntry
{
public:
  MapRangeData data;
  std::string_view name;

  LGB_MAP_RANGE_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< MapRangeData* >( buf + offset );
    name = std::string_view( buf + offset + header.nameOffset );
  };
};

struct LGB_EXIT_RANGE_ENTRY : public LgbEntry
{
public:
  ExitRangeData data;
  std::string_view name;

  LGB_EXIT_RANGE_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< ExitRangeData* >( buf + offset );
    name = std::string_view( buf + offset + header.nameOffset );
  };
};

struct LGB_POP_RANGE_ENTRY : public LgbEntry
{
public:
  PopRangeData data;

  LGB_POP_RANGE_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< PopRangeData* >( buf + offset );
  };
};

struct LGB_EVENT_RANGE_ENTRY : public LgbEntry
{
public:
  EventRangeData data;

  LGB_EVENT_RANGE_ENTRY( char* buf, size_t offset ) : LgbEntry( buf, offset )
  {
    data = *reinterpret_cast< EventRangeData* >( buf + offset );
  };
};

enum LayerSetReferencedType
{
  All = 0x0,
  Include = 0x1,
  Exclude = 0x2,
  Undetermined = 0x3,
};

struct LayerSetReferenced
{
  uint32_t LayerSetID;
};

struct LayerSetReferencedList
{
  LayerSetReferencedType ReferencedType;
  int32_t LayerSets;
  int32_t LayerSetCount;
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
  std::string_view name;
  std::vector< std::shared_ptr< LgbEntry > > entries;
  std::vector< LayerSetReferenced > refs;

  LGB_GROUP( char* buf, LGB_FILE* parentStruct, size_t offset )
  {
    parent = parentStruct;
    header = *reinterpret_cast< LGB_GROUP_HEADER* >( buf + offset );
    name = std::string_view( buf + offset + header.groupNameOffset );

    // Initialize the layerSetReferencedList from the buffer and offset
    layerSetReferencedList = *reinterpret_cast< LayerSetReferencedList* >( buf + offset + header.LayerSetRef );

    // Check if there are any layer set references to initialize
    if( layerSetReferencedList.LayerSetCount > 0 )
    {
      // Reserve memory for layer set references
      refs.reserve( layerSetReferencedList.LayerSetCount );

      // Iterate through each layer set reference and construct LayerSetReferenced objects from the buffer
      for( size_t i = 0; i < layerSetReferencedList.LayerSetCount; ++i )
      {
        LayerSetReferenced ref = *reinterpret_cast< LayerSetReferenced* >( buf + offset + header.LayerSetRef + layerSetReferencedList.LayerSets + i * sizeof( LayerSetReferenced ) );
        refs.emplace_back( ref );
      }
    }

    // Reserve memory for entries
    entries.reserve( header.entryCount );

    // Calculate the offset for entries
    const auto entriesOffset = offset + header.entriesOffset;

    // Iterate through each entry and construct the appropriate objects (not shown in the code snippet)
    for( auto i = 0; i < header.entryCount; ++i )
    {
      const auto entryOffset = entriesOffset + *reinterpret_cast< int32_t* >( buf + ( entriesOffset + i * 4 ) );

      try
      {
        const auto type = *reinterpret_cast< LgbEntryType* >( buf + entryOffset );
        switch( type )
        {
          case LgbEntryType::BgParts:
          {
            entries.emplace_back( std::make_shared< LGB_BGPARTS_ENTRY >( buf, entryOffset ) );
            break;
          }
          case LgbEntryType::Gimmick:
          {
            entries.emplace_back( std::make_shared< LGB_GIMMICK_ENTRY >( buf, entryOffset ) );
            break;
          }
          case LgbEntryType::EventNpc:
          {
            entries.emplace_back( std::make_shared< LGB_ENPC_ENTRY >( buf, entryOffset ) );
            break;
          }
          case LgbEntryType::EventObject:
          {
            entries.emplace_back( std::make_shared< LGB_EOBJ_ENTRY >( buf, entryOffset ) );
            break;
          }
          case LgbEntryType::ExitRange:
          {
            entries.emplace_back( std::make_shared< LGB_EXIT_RANGE_ENTRY >( buf, entryOffset ) );
            break;
          }
          case LgbEntryType::EventRange:
          {
            entries.emplace_back( std::make_shared< LGB_EVENT_RANGE_ENTRY >( buf, entryOffset ) );
            break;
          }
          case LgbEntryType::PopRange:
          {
            entries.emplace_back( std::make_shared< LGB_POP_RANGE_ENTRY >( buf, entryOffset ) );
            break;
          }
          case LgbEntryType::MapRange:
          {
            entries.emplace_back( std::make_shared< LGB_MAP_RANGE_ENTRY >( buf, entryOffset ) );
            break;
          }
          default:
          {
            entries.emplace_back( std::make_shared< LgbEntry >( buf, entryOffset ) );
            break;
          }
        }
      }
      catch( std::exception& e )
      {
        throw e;
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
  uint32_t unknown2;
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

  // Constructor that initializes an LGB_FILE object from a buffer and a name
  LGB_FILE( char* buf, const std::string& name ) : LGB_FILE( buf )
  {
    m_name = name;
  }

  // Constructor that initializes an LGB_FILE object from a buffer
  LGB_FILE( char* buf )
  {
    // Reinterpret the buffer as an LGB_FILE_HEADER pointer and dereference it
    header = *reinterpret_cast< LGB_FILE_HEADER* >( buf );

    // Check for a valid file header
    if( strncmp( &header.magic[ 0 ], "LGB1", 4 ) != 0 || strncmp( &header.magic2[ 0 ], "LGP1", 4 ) != 0 )
    {
      throw std::runtime_error( "Invalid LGB file!" );
    }

    constexpr auto baseOffset = sizeof( header );
    groups.reserve( header.groupCount );// Reserve memory for the groups

    // Iterate through each group and construct LGB_GROUP objects from the buffer
    for( size_t i = 0; i < header.groupCount; ++i )
    {
      const auto groupOffset = baseOffset + *reinterpret_cast< int32_t* >( buf + ( baseOffset + i * 4 ) );
      groups.emplace_back( buf, this, groupOffset );
    }
  }
};
