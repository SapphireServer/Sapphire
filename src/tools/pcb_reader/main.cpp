#include <stdio.h>
#include <cstdint>
#include <string>
#include <experimental/filesystem>

#include "pcb.h"
#include "lgb.h"

#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

#include <iostream>
namespace fs = std::experimental::filesystem;

int parseBlockEntry( char* data, std::vector<PCB_BLOCK_ENTRY>& entries, int gOff )
{
   int offset = 0;
   bool isgroup = true;
   while( isgroup )
   {
      PCB_BLOCK_ENTRY block_entry;
      memcpy( &block_entry.header, data + offset, sizeof( block_entry.header ) );
      isgroup = block_entry.header.type == 0x30 ? true : false;

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
            memcpy( &block_entry.data.vertices[0], data + doffset, size_vertexbuffer * 4 );
            doffset += size_vertexbuffer * 4;
         }
         if( block_entry.header.num_v16 != 0 )
         {
            block_entry.data.vertices_i16.resize( block_entry.header.num_v16 );
            int32_t size_unknownbuffer = block_entry.header.num_v16 * 6;
            memcpy( &block_entry.data.vertices_i16[0], data + doffset, size_unknownbuffer );
            doffset += block_entry.header.num_v16 * 6;
         }
         if( block_entry.header.num_indices != 0 )
         {
            block_entry.data.indices.resize( block_entry.header.num_indices );
            int32_t size_indexbuffer = block_entry.header.num_indices * 12;
            memcpy( &block_entry.data.indices[0], data + doffset, size_indexbuffer );
            doffset += size_indexbuffer;
         }
         entries.push_back( block_entry );
      }
   }

   return 0;
}

void toFile(const std::string& fileName, const std::vector<vec3>& vertices, const std::vector<int>& indices)
{
   auto fp_out = fopen(fileName.c_str(), "w");
   if (fp_out)
   {
      fprintf(fp_out, "\n");
      fclose(fp_out);
   }
   fp_out = fopen(fileName.c_str(), "ab+");
   if (fp_out)
   {
      for (const auto& v : vertices)
      {
         fprintf(fp_out, "v %f %f %f\n", v.x, v.y, v.z);
      }
      for (auto i = 0; i < indices.size(); i += 3)
      {
         fprintf(fp_out, "f %i %i %i\n", indices[i] + 1, indices[i + 1] + 1, indices[i + 2] + 1);
      }
      fclose(fp_out);
   }
}

std::string zoneNameToPath( const std::string& name )
{
   char teri = name[0];
   char region = name[1];
   char type = name[2];
   char zone = name[3];
   static std::map<char, std::string> teriMap
   {
      { 'r', "roc" },
      { 'w', "wil" },
      { 'l', "lak" },
      { 'o', "ocn" },
      { 'f', "fst" },
      { 'a', "air" },
      { 's', "sea" },
      { 'z', "zon" }
   };

   static std::map<char, std::string> typeMap
   {
      { 'f', "fld" },
      { 't', "twn" },
      { 'd', "dun" },
      { 'b', "bah" },
      { 'i', "ind" },
      { 'e', "evt" },
   };
   std::string ret;
   const auto& teriRet = teriMap[teri];
   const auto& typeRet = typeMap[type];
   ret += teriRet + "_";
   ret += teri;
   ret += region;
   ret += "/" + typeRet + "/" + name;
   return ret;
}

int main( int argc, char* argv[] )
{
   std::string gamePath = "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack\\ffxiv";
   std::string zoneName = "r1f1";

   if( argc > 1 )
   {
      gamePath = argv[1];
      if( argc > 2 )
      {
         zoneName = argv[2];
      }
   }
   const auto& zonePath = zoneNameToPath( zoneName );

   xiv::dat::GameData data1( gamePath );
   xiv::exd::ExdData eData( data1 );

   const xiv::dat::Cat& test = data1.get_category( "bg" );

   auto &test_file = data1.get_file( "bg/ffxiv/" + zonePath + "/level/bg.lgb" );
   auto &section = test_file->access_data_sections().at( 0 );
   int32_t list_offset = *( uint32_t* ) &section[0x18];
   int32_t size = *( uint32_t* ) &section[4];

   std::vector<std::string> stringList;
   std::vector<std::string> stringList2;

   auto &test_file1 = data1.get_file( "bg/ffxiv/" + zonePath + "/collision/list.pcb" );
   auto &section1 = test_file1->access_data_sections().at( 0 );
   std::string path = "bg/ffxiv/roc_r1/fld/r1f1/collision/";
   int offset1 = 0x20;
   for( ; ; )
   {

      uint16_t trId = *( uint16_t* ) &section1[offset1];

      char someString[200];
      sprintf( someString, "%str%04d.pcb", path.c_str(), trId );
      stringList.push_back( std::string( someString ) );
      //std::cout << someString << "\n";
      offset1 += 0x20;

      if( offset1 >= section1.size() )
      {
         break;
      }
   }
   LGB_FILE bgLgb(&section[0]);

   int total_vertices = 0;
   int total_indices = 0;
   int max_index = 0;

   std::vector<vec3> vertices;
   std::vector<int> indices;

   char *data;
   int counter = 0;


   std::map<std::string, PCB_FILE> pcbFiles;

   auto loadPcbFile = [&]( const std::string& fileName)
   {
      try
      {
         //std::cout << fileName << " ";
         auto file = data1.get_file( fileName );
         auto sections = file->get_data_sections();
         auto dataSection = &sections.at( 0 )[0];

         //std::cout << sections.size() << "\n";

         uint32_t offset = 0;
         uint32_t groupCount = 0;
         PCB_FILE pcb_file;
         memcpy( &pcb_file.header, &dataSection[0], sizeof( pcb_file.header ) );
         offset += sizeof( pcb_file.header );

         bool isgroup = true;
         while( isgroup )
         {
            PCB_BLOCK_ENTRY block_entry;
            memcpy( &block_entry.header, &dataSection[0] + offset, sizeof( block_entry.header ) );
            isgroup = block_entry.header.type == 0x30 ? true : false;

            //printf( "BLOCKHEADER_%X: type: %i, group_size: %i\n", offset, block_entry.header.type, block_entry.header.group_size );
            //
            if( isgroup )
            {
               parseBlockEntry( &dataSection[0] + offset + 0x30, pcb_file.entries, offset );
               offset += block_entry.header.group_size;
            }
            else
            {
               parseBlockEntry( &dataSection[0] + offset, pcb_file.entries, offset );
            }
            groupCount++;
         }
         pcbFiles.insert( std::make_pair( fileName, pcb_file ) );
      }
      catch( std::exception& e )
      {
         std::cout << "Unable to load collision mesh " << fileName << "\n\tError:\n\t" << e.what() << "\n";
      }
   };
   auto pushVerts = [&]( const PCB_FILE& pcb_file, const vec3* scale = nullptr, const vec3* rotation = nullptr, const vec3* translation = nullptr)
   {
      for( auto &entry : pcb_file.entries )
      {
         total_vertices += entry.header.num_vertices;
         total_vertices += entry.header.num_v16;

         total_indices += entry.header.num_indices;
         float x_base = abs( float( entry.header.x1 - entry.header.x ) );
         float y_base = abs( float( entry.header.y1 - entry.header.y ) );
         float z_base = abs( float( entry.header.z1 - entry.header.z ) );

         auto makeTranslation = [&]( vec3& v )
         {
            if( scale )
            {
               v.x *= scale->x;
               v.y *= scale->y;
               v.z *= scale->z;
            }
            if( rotation )
            {
               v = v * matrix4::rotateX( rotation->x );
               v = v * matrix4::rotateY( rotation->y );
               v = v * matrix4::rotateZ( rotation->z );
            }
            if( translation )
            {
               v.x += translation->x;
               v.y += translation->y;
               v.z += translation->z;
            }
         };

         for( auto &vertex_list : entry.data.vertices )
         {
            vec3 v;
            v.x = vertex_list.x;
            v.y = vertex_list.y;
            v.z = vertex_list.z;
            makeTranslation( v );
            vertices.push_back( v );
         }

         for( const auto &link : entry.data.vertices_i16 )
         {
            vec3 v( float( link.x ) / 0xFFFF, float( link.y ) / 0xFFFF, float( link.z ) / 0xFFFF );

            float x = float( link.x );
            float y = float( link.y );
            float z = float( link.z );
            v.x = (x / 0xFFFF) * x_base + entry.header.x;
            v.y = (y / 0xFFFF) * y_base + entry.header.y;
            v.z = (z / 0xFFFF) * z_base + entry.header.z;

            makeTranslation( v );
            vertices.push_back( v );
         }

         for( const auto &index : entry.data.indices )
         {
            //if( index.index[0] != 0 || index.index[1] != 0 || index.index[2] != 0 )
            {
               indices.push_back( int( index.index[0] ) + max_index );
               indices.push_back( int( index.index[1] ) + max_index );
               indices.push_back( int( index.index[2] ) + max_index );
            }
            //std::cout << std::to_string( index.unknown[0] )<< " " << std::to_string( index.unknown[1] )<< " " << std::to_string( index.unknown[2]) << std::endl;
         }
         max_index = vertices.size();
      }
   };

   for( const auto& fileName : stringList )
   {
      loadPcbFile( fileName );
      pushVerts( pcbFiles[fileName] );
   }
   std::cout << "Writing obj file " << "\n";
   std::cout << bgLgb.groups.size() << " entries " << "\n";
   for( const auto& group : bgLgb.groups )
   {
      for( const auto pEntry : group.entries )
      {
         if( !pEntry )
            continue;

         auto pBgParts = dynamic_cast<LGB_BGPARTS_ENTRY*>( pEntry.get() );
         if( !pBgParts || pBgParts->collisionFileName.empty()
            || std::find(stringList.begin(), stringList.end(), pBgParts->collisionFileName) != stringList.end())
            continue;
         auto it = pcbFiles.find( pBgParts->collisionFileName );
         if( it == pcbFiles.end() )
         {
            loadPcbFile( pBgParts->collisionFileName );
         }
         if( it != pcbFiles.end() )
         {
            //std::cout << pBgParts->collisionFileName << "\n";

            const auto* scale = &pBgParts->header.scale;
            const auto* rotation = &pBgParts->header.rotation;
            const auto* translation = &pBgParts->header.translation;

            const auto& pcb_file = it->second;
            pushVerts( pcb_file, scale, rotation, translation );
         }
      }
   }
   toFile("test.obj", vertices, indices);
   return 0;
}