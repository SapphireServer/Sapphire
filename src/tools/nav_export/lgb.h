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

#include "InstanceObject.h"
#include "matrix4.h"
#include "vec3.h"
#include "sgb.h"
#include "Layer.h"
#include "DatCommon.h"

#include "InstanceObjectParser.h"
// garbage to skip model loading
extern bool noObj;

// all credit to
// https://github.com/ufx/SaintCoinach/blob/master/SaintCoinach/Graphics/Lgb/
// this is simply their work ported to c++ since we dont c#
struct LGB_FILE;
struct LGB_FILE_HEADER;
struct LGB_GROUP;
struct LGB_GROUP_HEADER;




struct ENpcData :
  public InstanceObject
{
  uint32_t enpcId;
  uint8_t unknown1[0x24];
};

class LGB_ENPC_ENTRY :
  public InstanceObjectEntry
{
public:
  ENpcData header;
  std::string name;

  LGB_ENPC_ENTRY( char* buf, uint32_t offset ) :
          InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< ENpcData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
    //std::cout << "\t ENpc " << header.enpcId << " " << name << "\n";
  };
};

struct LGB_EOBJ_ENTRY : public InstanceObjectEntry
{
public:
  EObjData header;
  std::string name;

  LGB_EOBJ_ENTRY( char* buf, uint32_t offset ) :
          InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< EObjData* >( buf + offset );
    //std::cout << "\t " << header.eobjId << " " << name << " unknown: " << header.unknown << "\n";
    name = std::string( buf + offset + header.Name );
  };
};


struct LGB_MAP_RANGE_ENTRY :  public InstanceObjectEntry
{
public:
  MapRangeData header;
  std::string name;

  LGB_MAP_RANGE_ENTRY( char* buf, uint32_t offset ) :
          InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< MapRangeData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};

struct LGB_COLLISION_BOX_ENTRY :
  public InstanceObjectEntry
{
  CollisionBoxData header;
  std::string name;

  LGB_COLLISION_BOX_ENTRY( char* buf, uint32_t offset ) :
          InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< CollisionBoxData* >( buf + offset );
    header.AssetType = eAssetType::CollisionBox;
    name = std::string( buf + offset + header.Name );
    std::stringstream ss;
    ss << "\nName: " << name << "Id: " << header.InstanceID << "\n";
    ss << "Pos: " << header.Transformation.Translation.x << " " << header.Transformation.Translation.y << " " << header.Transformation.Translation.z << "\n";
    ss << "Rot?: " << header.Transformation.Rotation.x << " " << header.Transformation.Rotation.y << " " << header.Transformation.Rotation.z << "\n";
    ss << "Scale?: " << header.Transformation.Scale.x << " " << header.Transformation.Scale.y << " " << header.Transformation.Scale.z << "\n";
    ss << "00 01 02 03 04 05 06 07 | 08 09 0A 0B 0C 0D 0E 0F\n";
    ss << "-------------------------------------------------\n";
    ss << std::hex;
    ss << std::setw( 2 );
    ss << std::setfill( '0' );

  /*  for( auto i = 1; i < sizeof( header. ); ++i )
      if( i % 16 == 0 )
        ss << std::setw(2) << (int)header.unk[i - 1] << "\n";
      else if( i % 8 == 0 )
        ss << std::setw(2) << (int)header.unk[i - 1] << " | ";
      else
        ss << std::setw(2) << (int)header.unk[i - 1] << " ";
    ss << "\n";
    std::cout << ss.str();*/
  }
};




struct LGB_GROUP
{
  LGB_FILE* parent;
  Layer header;
  std::string name;
  std::vector< std::shared_ptr< InstanceObjectEntry > > entries;

  LGB_GROUP( char* buf, LGB_FILE* parentStruct, uint32_t offset )
  {
    parent = parentStruct;
    header = *reinterpret_cast< Layer* >( buf + offset );
    name = std::string( buf + offset + header.Name );
    //entries.resize( header.entryCount );
    //std::cout << name << "\n\t unknown: " << header.unknown << "\n";
    const auto entriesOffset = offset + header.InstanceObjects;
    for( auto i = 0; i < header.InstanceObject_Count; ++i )
    {
      const auto entryOffset = entriesOffset + *reinterpret_cast< int32_t* >( buf + ( entriesOffset + i * 4 ) );

      try
      {
        const auto type = *reinterpret_cast<eAssetType*>( buf + entryOffset );
        // garbage to skip model loading
        switch( type )
        {
          case eAssetType::BG:
            entries.push_back( std::make_shared< BGEntry >( buf, entryOffset ) );
            break;
          case eAssetType::SharedGroup:
            entries.push_back( std::make_shared< SharedGroupEntry >( buf, entryOffset ) );
            break;
          case eAssetType::EventObject:
            entries.push_back( std::make_shared< LGB_EOBJ_ENTRY >( buf, entryOffset ) );
            break;
          case eAssetType::CollisionBox:
          //case LgbEntryType::NaviMeshRange:
            //std::cout << "\t\tUnknown SGB entry! Group: " << name << " type: " << ( int )type << " index: " << i << " entryOffset: " << entryOffset << "\n";
            //entries.push_back( std::make_shared< LGB_COLLISION_BOX_ENTRY >( buf, entryOffset ) );
            break;
          default:
         //   std::cout << "\t\tUnknown SGB entry! Group: " << name << " type: " << ( int )type << " index: " << i << " entryOffset: " << entryOffset << "\n";
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