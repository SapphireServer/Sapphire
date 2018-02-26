#ifndef _SGB_H
#define _SGB_H

#include <cstring>
#include <memory>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "vec3.h"

// garbage to skip model loading
extern bool ignoreModels;

//
// ported from https://github.com/ufx/SaintCoinach/blob/master/SaintCoinach/Graphics/Sgb/SgbDataType.cs

struct SGB_FILE;
struct SGB_HEADER;
struct SGB_MODEL_ENTRY;
struct SGB_MODEL_HEADER;
struct SGB_GROUP;
struct SGB_GROUP_HEADER;


enum SgbDataType : uint32_t
{
   Unknown0008 = 0x0008,
   Group = 0x0100,
};

enum SgbGroupEntryType : uint32_t
{
   Model = 0x01,
};

struct SGB_GROUP_HEADER
{
   SgbDataType type;
   int32_t nameOffset;
   uint32_t unknown08;
   uint32_t unknown0C;

   uint32_t unknown10;
   uint32_t unknown14;
   uint32_t unknown18;
   uint32_t unknown1C;

   int32_t entryCount;
   uint32_t unknown24;
   uint32_t unknown28;
   uint32_t unknown2C;

   uint32_t unknown30;
   uint32_t unknown34;
   uint32_t unknown38;
   uint32_t unknown3C;

   uint32_t unknown40;
   uint32_t unknown44;
};

struct SGB_GROUP_ENTRY
{
public:
   char* m_buf;
   uint32_t m_offset;

   SGB_GROUP_ENTRY()
   {
      m_buf = nullptr;
      m_offset = 0;
   };
   SGB_GROUP_ENTRY( char* buf, uint32_t offset )
   {
      m_buf = buf;
      m_offset = offset;
   };
   virtual ~SGB_GROUP_ENTRY() {};
};

struct SGB_ENTRY_HEADER
{
   SgbGroupEntryType type;
   uint32_t unknown2;
   int32_t nameOffset;
   vec3 translation;
   vec3 rotation;
   vec3 scale;
};

struct SGB_MODEL_HEADER : public SGB_ENTRY_HEADER
{
   int32_t modelFileOffset;
   int32_t collisionFileOffset;
};

struct SGB_MODEL_ENTRY : public SGB_GROUP_ENTRY
{
   SGB_MODEL_HEADER header;
   SgbGroupEntryType type;
   std::string name;
   std::string modelFileName;
   std::string collisionFileName;

   SGB_MODEL_ENTRY( char* buf, uint32_t offset )
   {
      header = *reinterpret_cast< SGB_MODEL_HEADER* >( buf + offset );
      name = std::string( buf + offset + header.nameOffset );
      modelFileName = std::string( buf + offset + header.modelFileOffset );
      collisionFileName = std::string( buf + offset + header.collisionFileOffset );
   }
};

struct SGB_GROUP
{
   SGB_GROUP_HEADER header;
   std::string name;
   SGB_FILE* parent;
   std::vector< std::shared_ptr< SGB_GROUP_ENTRY > > entries;

   SGB_GROUP( char* buf, SGB_FILE* file, uint32_t fileSize, uint32_t offset )
   {
      parent = file;
      header = *reinterpret_cast< SGB_GROUP_HEADER* >( buf + offset );
      name = std::string( buf + offset + header.nameOffset );

      auto entriesOffset = offset + sizeof( header );

      for( auto i = 0; i < header.entryCount; ++i )
      {
         auto entryOffset = entriesOffset + *reinterpret_cast< uint32_t* >( buf + ( entriesOffset + ( i * 4 ) ) );
         if( entryOffset > fileSize )
            throw std::runtime_error( "SGB_GROUP entry offset was larger than SGB file size!" );
         auto type = *reinterpret_cast< uint32_t* >( buf + entryOffset );
         if( type == SgbGroupEntryType::Model && !ignoreModels )
         {
            entries.push_back( std::make_shared< SGB_MODEL_ENTRY >( buf, entryOffset ) );
         }
         else
         {
            // std::cout << "\t\tUnknown SGB entry! Group: " << name << " type: " << type << " index: " << i << " entryOffset: " << entryOffset << "\n";
         }
      }
   }
};

struct SGB_HEADER
{
   char magic[4];     // SGB1
   uint32_t fileSize;
   uint32_t unknown1;
   char magic2[4];    // SCN1

   uint32_t unknown10;
   int32_t sharedOffset;
   uint32_t unknown18;
   int32_t offset1C;

   uint32_t unknown20;
   uint32_t unknown24;
   uint32_t unknown28;
   uint32_t unknown2C;

   uint32_t unknown30;
   uint32_t unknown34;
   uint32_t unknown38;
   uint32_t unknown3C;

   uint32_t unknown40;
   uint32_t unknown44;
   uint32_t unknown48;
   uint32_t unknown4C;

   uint32_t unknown50;
   uint32_t unknown54;
};

struct SGB_FILE
{
   SGB_HEADER header;
   std::vector<SGB_GROUP> entries;

   SGB_FILE()
   {
      memset( &header, 0, sizeof( header ) );
   }
   SGB_FILE( char* buf )
   {
      constexpr int baseOffset = 0x14;
      header = *reinterpret_cast< SGB_HEADER* >( buf );

      if( strncmp( &header.magic[0], "SGB1", 4 ) != 0 || strncmp( &header.magic2[0], "SCN1", 4 ) != 0 )
         throw std::runtime_error( "Unable to load SGB File!" );

      try
      {
         auto group = SGB_GROUP( buf, this, header.fileSize, baseOffset + header.sharedOffset );
         entries.push_back( group );
         auto group2 = SGB_GROUP( buf, this, header.fileSize, baseOffset + header.offset1C );
         entries.push_back( group2 );
      }
      catch( std::exception& e )
      {
         std::cout << e.what() << "\n";
      }
   };
};


#endif // !_SGB_H
