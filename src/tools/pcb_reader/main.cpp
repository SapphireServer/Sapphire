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

std::vector<std::string> loadDir(const std::string& dir)
{
    std::vector<std::string> files;

    auto fsDir = fs::current_path().append(fs::path(dir));
    std::cout << fsDir.string() << "\n";
    if (fs::exists(fsDir))
    {
        for (const auto& entry : fs::directory_iterator(fsDir))
        {
            auto filename = entry.path().filename();
            if (filename.string().find("~") == -1)
                files.push_back(entry.path().string());
            if (filename.string().find("list") != std::string::npos)
                std::cout << filename.string() << "\n";
        }
    }
    return files;
}

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
         //if( indices[i]!= 0 || indices[i + 1] != 0 || indices[i+ 2] != 0)
         fprintf(fp_out, "f %i %i %i\n", indices[i] + 1, indices[i + 1] + 1, indices[i + 2] + 1);
      }
      fclose(fp_out);
   }
}

int main()
{

   xiv::dat::GameData data1( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack\\ffxiv" );
   xiv::exd::ExdData eData( data1 );

   const xiv::dat::Cat& test = data1.get_category( "bg" );

   auto &test_file = data1.get_file( "bg/ffxiv/sea_s1/fld/s1f5/level/bg.lgb" );
   auto &section = test_file->access_data_sections().at( 0 );
   int32_t list_offset = *( uint32_t* ) &section[0x18];
   int32_t size = *( uint32_t* ) &section[4];

   std::vector<std::string> stringList;

   uint32_t offset = list_offset + 0x14;

   for( ; ; )
   {
      std::string entry( &section[offset] );
      offset += entry.size() + 1;
      if( entry.find( "bgcommon" ) == std::string::npos && entry.find( ".mdl" ) == std::string::npos && entry.find( ".pcb" ) != std::string::npos )
      {
         //stringList.push_back( entry );
      }

      if( offset >= size )
      {
         break;
      }
   }

   auto &test_file1 = data1.get_file( "bg/ffxiv/roc_r1/fld/r1f1/collision/list.pcb" );
   auto &section1 = test_file1->access_data_sections().at( 0 );
   std::string path = "bg/ffxiv/roc_r1/fld/r1f1/collision/";
   int offset1 = 0x20;
   for( ; ; )
   {

      uint16_t trId = *( uint16_t* ) &section1[offset1];

      char someString[200];
      sprintf( someString, "%str%04d.pcb", path.c_str(), trId );
      stringList.push_back( std::string( someString ) );
      std::cout << someString << "\n";
      offset1 += 0x20;

      if( offset1 >= section1.size() )
      {
         break;
      }
   }

   int total_vertices = 0;
   int total_indices = 0;
   int max_index = 0;

   std::vector<vec3> vertices;
   std::vector<int> indices;

   char *data;
   int counter = 0;
   for( auto fileName : stringList )
   {
      std::cout << fileName << " ";
      auto file = data1.get_file( fileName );
      auto sections = file->get_data_sections();

      auto dataSection = sections[0];

      std::cout << sections.size() << "\n";


      /*if( fileName != "collision1\\s1fa_t1_hasi1.pcb" )
      {
         std::cout << fileName;
         continue;
      }*/

      uint32_t offset = 0;

      PCB_FILE pcb_file;
      memcpy( &pcb_file.header, &dataSection[0], sizeof( pcb_file.header ) );
      offset += sizeof( pcb_file.header );

      std::vector<PCB_BLOCK_ENTRY> entries;

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

      }


      for( auto &entry : pcb_file.entries )
      {
         total_vertices += entry.header.num_vertices;
         total_vertices += entry.header.num_v16;

         total_indices += entry.header.num_indices;

         for( auto &vertex_list : entry.data.vertices )
         {
            vec3 v;
            v.x = vertex_list.x;
            v.y = vertex_list.y;
            v.z = vertex_list.z;
            vertices.push_back( v );
         }

         float x_base = abs( float( entry.header.x1 - entry.header.x ) );
         float y_base = abs( float( entry.header.y1 - entry.header.y ) );
         float z_base = abs( float( entry.header.z1 - entry.header.z ) );

         for( const auto &link : entry.data.vertices_i16 )
         {
            vec3 v(float( link.x ) / 0xFFFF, float( link.y ) / 0xFFFF, float( link.z ) / 0xFFFF);

            float x = float( link.x );
            float y = float( link.y );
            float z = float( link.z );
            v.x = ( x / 0xFFFF ) * x_base + entry.header.x;
            v.y = ( y / 0xFFFF ) * y_base + entry.header.y;
            v.z = ( z / 0xFFFF ) * z_base + entry.header.z;
            vertices.push_back( v );
         }


         for( const auto &index : entry.data.indices )
         {
            //if( index.index[0] != 0 || index.index[1] != 0 || index.index[2] != 0 )
            {
               indices.push_back(int(index.index[0]) + max_index );
               indices.push_back(int(index.index[1]) + max_index );
               indices.push_back(int(index.index[2]) + max_index );
            }
            //std::cout << std::to_string( index.unknown[0] )<< " " << std::to_string( index.unknown[1] )<< " " << std::to_string( index.unknown[2]) << std::endl;
         }
         max_index = vertices.size();
      }
      //for( auto block : pcb_file.entries )
      //{
      //   auto pMesh3 = createBoundMeshFromPcbBlock( block );
      //   if( pMesh3 )
      //      m_pMeshList3.push_back( pMesh3 );
      //}

   }
   toFile("test.obj", vertices, indices);
 /*  char *data;

   uint32_t offset = 0;
   //r1f1_b1_dor00.pcb
   PCB_LIST_FILE listFile;
   int groupsCount = 0;
   //auto list = loadDir("bg/ffxiv/roc_r1/collision");
   auto lgbFiles = getLgbFiles("bg/ffxiv/roc_r1/");

   std::cout << "Loaded " << lgbFiles.size() << " LGB files" << std::endl;

   std::map<std::string, uint32_t> groupCounts;
   std::map<std::string, PCB_FILE> pcbFiles;

   int total_vertices = 0;
   int total_indices = 0;
   int max_index = 0;

   std::vector<vec3> vertices;
   std::vector<int> indices;

   for (const auto& pair : lgbFiles)
   {
      std::cout << "FILE " << pair.first << "\n";
      for (const auto& group : pair.second.groups)
      {
         uint32_t groupEntryCount = 0;
         uint32_t bgPartsCount = 0;
         //std::cout << "GROUP " << group.name << "\n";
         for (auto entry : group.entries)
         {
            if (dynamic_cast<LGB_BGPARTS_ENTRY*>(entry.get()))
               bgPartsCount++;
         }

         for (auto pEntry : group.entries)
         {
            if (!pEntry)
               continue;

            auto pBgParts = dynamic_cast<LGB_BGPARTS_ENTRY*>(pEntry.get());

            if (!pBgParts || pBgParts->collisionFileName.empty())
               continue;

            auto filename = pBgParts->collisionFileName;
            if(!groupCounts[filename])
               std::cout << "GROUP " << group.name << " " << pBgParts->collisionFileName << "\n";

            PCB_FILE pcb_file = PCB_FILE();
            if(pcbFiles.find(filename) == pcbFiles.end())
            {
               FILE *fp = nullptr;
               fp = fopen(filename.c_str(), "rb");
               if (fp == nullptr)
                  return 0;

               fseek(fp, 0, SEEK_END);
               int32_t size = ftell(fp);
               data = new char[size];
               rewind(fp);
               fread(data, 1, size, fp);
               fclose(fp);

               memcpy(&pcb_file.header, data, sizeof(pcb_file.header));
               auto offset = sizeof(pcb_file.header);
               try
               {
                  bool isgroup = true;
                  while( isgroup )
                  {
                     PCB_BLOCK_ENTRY block_entry;
                     memcpy(&block_entry.header, data + offset, sizeof(block_entry.header));
                     isgroup = block_entry.header.type == 0x30 ? true : false;

                     //printf( "BLOCKHEADER_%X: type: %i, group_size: %i\n", offset, block_entry.header.type, block_entry.header.group_size );
                     //
                     if( isgroup )
                     {
                        std::cout << "ISGROUP" << "\n";
                        parseBlockEntry(data + offset + 0x30, pcb_file.entries, offset);
                        offset += block_entry.header.group_size;
                     }
                     else
                     {
                        parseBlockEntry(data + offset, pcb_file.entries, offset);
                     }
                  }
               }
               catch(std::exception& e)
               {
                  std::cout << "Unable to parse " << filename << " " << e.what() << "\n";
               }


            }
            else
            {
               pcb_file = pcbFiles[filename];
            }

            for( auto &entry : pcb_file.entries )
            {
               total_vertices += entry.header.num_vertices;
               total_vertices += entry.header.num_v16;

               total_indices += entry.header.num_indices;

               for( auto &vertex_list : entry.data.vertices )
               {
                  vec3 v;
                  v.x = vertex_list.x;
                  v.y = vertex_list.y;
                  v.z = vertex_list.z;
                  vertices.push_back( v );
               }

               float x_base = abs( float( entry.header.x1 - entry.header.x ) );
               float y_base = abs( float( entry.header.y1 - entry.header.y ) );
               float z_base = abs( float( entry.header.z1 - entry.header.z ) );

               for( const auto &link : entry.data.vertices_i16 )
               {
                  vec3 v(float( link.x ) / 0xFFFF, float( link.y ) / 0xFFFF, float( link.z ) / 0xFFFF);

                  float x = float( link.x );
                  float y = float( link.y );
                  float z = float( link.z );
                  v.x = ( x / 0xFFFF ) * x_base + entry.header.x;
                  v.y = ( y / 0xFFFF ) * y_base + entry.header.y;
                  v.z = ( z / 0xFFFF ) * z_base + entry.header.z;
                  vertices.push_back( v );
               }


               for( const auto &index : entry.data.indices )
               {
                  indices.push_back( int( index.index[0] ) + max_index );
                  indices.push_back( int( index.index[1] ) + max_index );
                  indices.push_back( int( index.index[2] ) + max_index );
                  //std::cout << std::to_string( index.unknown[0] )<< " " << std::to_string( index.unknown[1] )<< " " << std::to_string( index.unknown[2]) << std::endl;
               }
               max_index = vertices.size();
            }
            //toFile("test.obj", vertices, indices);
            //break;
         }
      }
   }
   toFile("test.obj", vertices, indices);
   std::cout << "vertices " << vertices.size() << " indices " << indices.size() / 3 << " expected indices " << vertices.size() << " total " << total_indices << "\n";*/
   return 0;
}