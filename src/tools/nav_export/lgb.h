#ifndef _LGB_H
#define _LGB_H

#include <cstring>
#include <memory>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <iostream>
#include <sstream>
#include <iomanip>

#include "matrix4.h"
#include "vec3.h"
#include "sgb.h"

// garbage to skip model loading
extern bool noObj;

// all credit to
// https://github.com/ufx/SaintCoinach/blob/master/SaintCoinach/Graphics/Lgb/
// this is simply their work ported to c++ since we dont c#
struct LGB_FILE;
struct LGB_FILE_HEADER;
struct LGB_GROUP;
struct LGB_GROUP_HEADER;

enum class LgbEntryType :
  uint32_t
{
  BgParts = 1,
  Light = 3,
  Vfx = 4,
  PositionMarker = 5,
  Gimmick = 6,
  SharedGroup6 = 6,// secondary variable is set to 2
  Sound = 7,
  EventNpc = 8,
  BattleNpc = 9,
  Aetheryte = 12,
  EnvSpace = 13,
  Gathering = 14,
  SharedGroup15 = 15,// secondary variable is set to 13
  Treasure = 16,
  Weapon = 39,
  PopRange = 40,
  ExitRange = 41,
  MapRange = 43,
  NaviMeshRange = 44,
  EventObject = 45,
  EnvLocation = 47,
  EventRange = 49,
  QuestMarker = 51,
  CollisionBox = 57,
  DoorRange = 58,
  LineVfx = 59,
  ClientPath = 65,
  ServerPath = 66,
  GimmickRange = 67,
  TargetMarker = 68,
  ChairMarker = 69,
  ClickableRange = 70,
  PrefetchRange = 71,
  FateRange = 72,
  SphereCastRange = 75,
};

struct LGB_ENTRY_HEADER
{
  LgbEntryType type;
  uint32_t unknown;
  uint32_t nameOffset;
  vec3 translation;
  vec3 rotation;
  vec3 scale;
};

class LGB_ENTRY
{
public:
  char* m_buf;
  uint32_t m_offset;
  LGB_ENTRY_HEADER header;

  LGB_ENTRY()
  {
    m_buf = nullptr;
    m_offset = 0;
    memset( &header, 0, sizeof( header ) );
  };

  LGB_ENTRY( char* buf, uint32_t offset )
  {
    m_buf = buf;
    m_offset = offset;
    header = *reinterpret_cast< LGB_ENTRY_HEADER* >( buf + offset );
  };

  const LgbEntryType getType() const
  {
    return header.type;
  };

  virtual ~LGB_ENTRY()
  {
  };
};


struct LGB_BGPARTS_HEADER :
  public LGB_ENTRY_HEADER
{
  uint32_t modelFileOffset;
  uint32_t collisionFileOffset;
  uint32_t unknown4;
  uint32_t unknown5;
  uint32_t unknown6;
  uint32_t unknown7;
  uint32_t unknown8;
  uint32_t unknown9;
};

class LGB_BGPARTS_ENTRY :
  public LGB_ENTRY
{
public:
  LGB_BGPARTS_HEADER header;
  std::string name;
  std::string modelFileName;
  std::string collisionFileName;

  LGB_BGPARTS_ENTRY()
  {
  };

  LGB_BGPARTS_ENTRY( char* buf, uint32_t offset ) :
    LGB_ENTRY( buf, offset )
  {
    header = *reinterpret_cast<LGB_BGPARTS_HEADER*>( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
    modelFileName = std::string( buf + offset + header.modelFileOffset );
    collisionFileName = std::string( buf + offset + header.collisionFileOffset );
  };
};

struct LGB_GIMMICK_HEADER :
  public LGB_ENTRY_HEADER
{
  uint32_t gimmickFileOffset;
  char unknownBytes[100];
};

class LGB_GIMMICK_ENTRY :
  public LGB_ENTRY
{
public:
  LGB_GIMMICK_HEADER header;
  std::string name;
  std::string gimmickFileName;

  LGB_GIMMICK_ENTRY( char* buf, uint32_t offset ) :
    LGB_ENTRY( buf, offset )
  {
    header = *reinterpret_cast<LGB_GIMMICK_HEADER*>( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
    gimmickFileName = std::string( buf + offset + header.gimmickFileOffset );
    //std::cout << "\t " << gimmickFileName << " unknown: " << header.unknown << "\n";
  };
};

struct LGB_ENPC_HEADER :
  public LGB_ENTRY_HEADER
{
  uint32_t enpcId;
  uint8_t unknown1[0x24];
};

class LGB_ENPC_ENTRY :
  public LGB_ENTRY
{
public:
  LGB_ENPC_HEADER header;
  std::string name;

  LGB_ENPC_ENTRY( char* buf, uint32_t offset ) :
    LGB_ENTRY( buf, offset )
  {
    header = *reinterpret_cast< LGB_ENPC_HEADER* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
    //std::cout << "\t ENpc " << header.enpcId << " " << name << "\n";
  };
};

struct LGB_EOBJ_HEADER :
  public LGB_ENTRY_HEADER
{
  uint32_t eobjId;
  uint32_t levelHierachyId;
  uint8_t unknown1[0xC];
};

class LGB_EOBJ_ENTRY :
  public LGB_ENTRY
{
public:
  LGB_EOBJ_HEADER header;
  std::string name;

  LGB_EOBJ_ENTRY( char* buf, uint32_t offset ) :
    LGB_ENTRY( buf, offset )
  {
    header = *reinterpret_cast< LGB_EOBJ_HEADER* >( buf + offset );
    //std::cout << "\t " << header.eobjId << " " << name << " unknown: " << header.unknown << "\n";
    name = std::string( buf + offset + header.nameOffset );
  };
};

struct LGB_MAPRANGE_HEADER :
  public LGB_ENTRY_HEADER
{
  uint32_t type;
  uint16_t unknown2;
  uint16_t unknown3;
  uint8_t unknown4[0x10];
};

struct LGB_MAPRANGE_ENTRY :
  public LGB_ENTRY
{
public:
  LGB_MAPRANGE_HEADER header;
  std::string name;

  LGB_MAPRANGE_ENTRY( char* buf, uint32_t offset ) :
    LGB_ENTRY( buf, offset )
  {
    header = *reinterpret_cast< LGB_MAPRANGE_HEADER* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
  };
};

struct LGB_COLLISION_BOX_HEADER :
  public LGB_ENTRY_HEADER
{
  uint8_t unk[100];
};

struct LGB_COLLISION_BOX_ENTRY :
  public LGB_ENTRY
{
  LGB_COLLISION_BOX_HEADER header;
  std::string name;

  LGB_COLLISION_BOX_ENTRY( char* buf, uint32_t offset ) :
    LGB_ENTRY( buf, offset )
  {
    header = *reinterpret_cast< LGB_COLLISION_BOX_HEADER* >( buf + offset );
    header.type = LgbEntryType::CollisionBox;
    name = std::string( buf + offset + header.nameOffset );
    std::stringstream ss;
    ss << "\nName: " << name << "Id: " << header.unknown << "\n";
    ss << "Pos: " << header.translation.x << " " << header.translation.y << " " << header.translation.z << "\n";
    ss << "Rot?: " << header.rotation.x << " " << header.rotation.y << " " << header.rotation.z << "\n";
    ss << "Scale?: " << header.scale.x << " " << header.scale.y << " " << header.scale.z << "\n";
    ss << "00 01 02 03 04 05 06 07 | 08 09 0A 0B 0C 0D 0E 0F\n";
    ss << "-------------------------------------------------\n";
    ss << std::hex;
    ss << std::setw( 2 );
    ss << std::setfill( '0' );

    for( auto i = 1; i < sizeof( header.unk ); ++i )
      if( i % 16 == 0 )
        ss << std::setw(2) << (int)header.unk[i - 1] << "\n";
      else if( i % 8 == 0 )
        ss << std::setw(2) << (int)header.unk[i - 1] << " | ";
      else
        ss << std::setw(2) << (int)header.unk[i - 1] << " ";
    ss << "\n";
    std::cout << ss.str();
  }
};

struct LGB_GROUP_HEADER
{
  uint32_t unknown;
  int32_t groupNameOffset;
  int32_t entriesOffset;
  int32_t entryCount;
  uint32_t unknown2;
  uint32_t unknown3;
  uint32_t unknown4;
  uint32_t unknown5;
  uint32_t unknown6;
  uint32_t unknown7;
  uint32_t unknown8;
  uint32_t unknown9;
  uint32_t unknown10;
};

struct LGB_GROUP
{
  LGB_FILE* parent;
  LGB_GROUP_HEADER header;
  std::string name;
  std::vector< std::shared_ptr< LGB_ENTRY > > entries;

  LGB_GROUP( char* buf, LGB_FILE* parentStruct, uint32_t offset )
  {
    parent = parentStruct;
    header = *reinterpret_cast< LGB_GROUP_HEADER* >( buf + offset );
    name = std::string( buf + offset + header.groupNameOffset );
    //entries.resize( header.entryCount );
    //std::cout << name << "\n\t unknown: " << header.unknown << "\n";
    const auto entriesOffset = offset + header.entriesOffset;
    for( auto i = 0; i < header.entryCount; ++i )
    {
      const auto entryOffset = entriesOffset + *reinterpret_cast< int32_t* >( buf + ( entriesOffset + i * 4 ) );

      try
      {
        const auto type = *reinterpret_cast<LgbEntryType*>( buf + entryOffset );
        // garbage to skip model loading
        switch( type )
        {
          case LgbEntryType::BgParts:
            entries.push_back( std::make_shared< LGB_BGPARTS_ENTRY >( buf, entryOffset ) );
            break;
          case LgbEntryType::Gimmick:
            entries.push_back( std::make_shared< LGB_GIMMICK_ENTRY >( buf, entryOffset ) );
            break;
          case LgbEntryType::EventObject:
            entries.push_back( std::make_shared< LGB_EOBJ_ENTRY >( buf, entryOffset ) );
            break;
          case LgbEntryType::CollisionBox:
            //entries.push_back( std::make_shared< LGB_COLLISION_BOX_ENTRY >( buf, entryOffset ) );
            break;
          default:
            //std::cout << "\t\tUnknown SGB entry! Group: " << name << " type: " << ( int )type << " index: " << i << " entryOffset: " << entryOffset << "\n";
            break;
        }
      }
      catch( std::exception& e )
      {
        std::cout << ( name + " " + e.what() + "\n" );
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
  
  LGB_FILE( char* buf )
  {
    header = *reinterpret_cast< LGB_FILE_HEADER* >( buf );
    if( strncmp( &header.magic[ 0 ], "LGB1", 4 ) != 0 || strncmp( &header.magic2[ 0 ], "LGP1", 4 ) != 0 )
      throw std::runtime_error( "Invalid LGB file!" );

    //groups.resize(header.groupCount);

    constexpr auto baseOffset = sizeof( header );
    for( auto i = 0; i < header.groupCount; ++i )
    {
      const auto groupOffset = baseOffset + *reinterpret_cast< int32_t* >( buf + ( baseOffset + i * 4 ) );
      const auto group = LGB_GROUP( buf, this, groupOffset );
      groups.push_back( group );
    }
  };
};

#endif