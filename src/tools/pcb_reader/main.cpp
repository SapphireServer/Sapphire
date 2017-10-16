#include <stdio.h>
#include <cstdint>
#include <string>
#include <experimental/filesystem>

#include "pcb.h"
#include "lgb.h"

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

int parseBlockEntry( char* data, std::vector<PCB_BLOCK_ENTRY>& entries, int gOff, uint32_t& groupCount, LGB_BGPARTS_ENTRY& bgParts )
{
   int offset = 0;
   bool isgroup = true;
   while( isgroup )
   {
      groupCount++;
      PCB_BLOCK_ENTRY block_entry;
      memcpy( &block_entry.header, data + offset, sizeof( block_entry.header ) );
      isgroup = block_entry.header.type == 0x30 ? true : false;

      //printf( " BLOCKHEADER_%X: type: %i, group_size: %i\n", gOff + offset, block_entry.header.type, block_entry.header.group_size );

      if( isgroup )
      {
         parseBlockEntry( data + offset + 0x30, entries, gOff + offset, groupCount, bgParts );
         offset += block_entry.header.group_size;
      }
      else
      {
         //printf( "\tnum_v16: %i, num_indices: %i, num_vertices: %i\n\n",
         //        block_entry.header.num_v16, block_entry.header.num_indices, block_entry.header.num_vertices );
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
            int32_t size_indexbuffer = block_entry.header.num_indices * 6;
            memcpy( &block_entry.data.indices[0], data + doffset, size_indexbuffer );
            doffset += size_indexbuffer;
         }
         entries.push_back( block_entry );

         //printf( "Vertices: \n" );
         for( auto& entry1 : block_entry.data.vertices )
         {
         //   printf( "\t %f, %f, %f \n",
         //            entry1.x, entry1.y, entry1.z );
         }

         float x_base = abs( float( block_entry.header.x1 - block_entry.header.x ) );
         float y_base = abs( float( block_entry.header.y1 - block_entry.header.y ) );
         float z_base = abs( float( block_entry.header.z1 - block_entry.header.z ) );

         //printf( "Vertices I16: \n" );
         for( auto& entry1 : block_entry.data.vertices_i16 )
         {
            uint16_t var1 = entry1.x;
            uint16_t var2 = entry1.y;
            uint16_t var3 = entry1.z;
            float x = ( var1 );
            float y = ( var2 );
            float z = ( var3 );
            //printf( "\t%f, ", ( x / 0xFFFF ) * x_base + block_entry.header.x );
            //printf( "%f, ", ( y / 0xFFFF ) * y_base + block_entry.header.y );
            //printf( "%f ", ( z / 0xFFFF ) * z_base + block_entry.header.z );
            //printf( "\n" );

         }
      }
   }

   return 0;
}

int main()
{
   char *data;

   uint32_t offset = 0;
   //r1f1_b1_dor00.pcb
   PCB_LIST_FILE listFile;
   int groupsCount = 0;
   //auto list = loadDir("bg/ffxiv/roc_r1/collision");
   auto lgbFiles = getLgbFiles("bg/ffxiv/roc_r1/");

   std::cout << "Loaded " << lgbFiles.size() << " LGB files" << std::endl;

   uint64_t vertexCount = 0;
   std::map<std::string, uint32_t> groupCounts;
   for (const auto& pair : lgbFiles)
   {
      for (const auto& group : pair.second.groups)
      {
         uint32_t bgPartsCount = 0;
         std::cout << group.name << "\n";
         for (auto entry : group.entries)
         {
            if (dynamic_cast<LGB_BGPARTS_ENTRY*>(entry.get()))
               bgPartsCount++;
         }

         for (auto entry : group.entries)
         {
            auto bgParts = dynamic_cast<LGB_BGPARTS_ENTRY*>(entry.get());
            if (!bgParts)
               continue;

            const auto& filename = bgParts->collisionFileName;
            std::cout << filename << std::endl;
            //std::string filename( "f1h0_s_rof0003.pcb" );
            //std::string filename("tr0924.pcb");
            FILE *fp = nullptr;
            fp = fopen(filename.c_str(), "rb");
            if (fp == nullptr)
            {
               return 0;
            }

            fseek(fp, 0, SEEK_END);
            int32_t size = ftell(fp);
            data = new char[size];
            rewind(fp);
            fread(data, sizeof(char), size, fp);
            fclose(fp);

            PCB_FILE pcb_file;
            memcpy(&pcb_file.header, data, sizeof(pcb_file.header));
            auto offset = sizeof(pcb_file.header);
            try
            {
               parseBlockEntry(data + offset, pcb_file.entries, offset, groupCounts[filename], *bgParts);
            }
            catch(std::exception& e)
            {
               std::cout << filename << " " << e.what() << "\n";
            }
         }
      }
   }
   return 0;
}

/*
   for( uint16_t i = 0; i <= pcb_file.header.num_entries; i++ )
   {
      PCB_BLOCK_ENTRY block_entry;
      memcpy( &block_entry.header, data + offset, sizeof( block_entry.header ) );
      offset += sizeof( block_entry.header );

      uint16_t block_size = sizeof( block_entry.header ) +
         block_entry.header.num_vertices * 3 * 4 +
         block_entry.header.num_v16 * 6 +
         block_entry.header.num_indices * 6;

      if( block_entry.header.num_vertices != 0 )
      {
         block_entry.data.vertices.resize( block_entry.header.num_vertices );

         int32_t size_vertexbuffer = block_entry.header.num_vertices * 3;
         memcpy( &block_entry.data.vertices[0], data + offset, size_vertexbuffer * 4 );
         offset += size_vertexbuffer * 4;
      }
      if( block_entry.header.num_v16 != 0 )
      {
         block_entry.data.vertices_i16.resize( block_entry.header.num_v16 );
         int32_t size_unknownbuffer = block_entry.header.num_v16 * 6;
         memcpy( &block_entry.data.vertices_i16[0], data + offset, size_unknownbuffer );
         offset += block_entry.header.num_v16 * 6;
      }
      if( block_entry.header.num_indices != 0 )
      {
         block_entry.data.indices.resize( block_entry.header.num_indices );
         int32_t size_indexbuffer = block_entry.header.num_indices * 6;
         memcpy( &block_entry.data.indices[0], data + offset, size_indexbuffer );
         offset += size_indexbuffer;
      }

      // blocks always align to 16 bytes + 8 bytes padding till the next block
      int rest = ( offset % 16 );
      if( rest > 0 )
      {
         rest = 0x10 - rest;
      }
      offset += rest ;


      pcb_file.entries.push_back( block_entry );
   }

   FILE* fp_out1 = fopen( std::string( filename + ".plain" ).c_str(), "w" );
   fprintf( fp_out1, "");
   fclose( fp_out1 );

   FILE* fp_out = fopen( std::string( filename + ".plain" ).c_str(), "w+" );

   fprintf( fp_out, "HEADER: num_entries: %i, total_indices: %i, unknown_1: %i\n\n", pcb_file.header.num_entries, pcb_file.header.total_indices, pcb_file.header.unknown_1 );

   int block_cnt = 0;
   for( auto& entry : pcb_file.entries )
   {

      fprintf( fp_out, "BLOCKHEADER_%i: type: %i, group_size: %i\n ",
                       block_cnt, entry.header.type, entry.header.group_size );
      fprintf( fp_out, "\tAABB: x: %f, y: %f, z: %f\n ",
               entry.header.x, entry.header.y, entry.header.z );
      fprintf( fp_out, "\t\t  x1: %f, y1: %f, z1: %f\n ",
               entry.header.x1, entry.header.y1, entry.header.z1 );
      fprintf( fp_out, "\tnum_v16: %i, num_indices: %i, num_vertices: %i\n\n",
               entry.header.num_v16, entry.header.num_indices, entry.header.num_vertices );

      fprintf( fp_out, "Vertices: \n");
      for( auto& entry1 : entry.data.vertices )
      {
         fprintf( fp_out, "\t %f, %f, %f \n",
                  entry1.x, entry1.y, entry1.z );
      }

      float x_base = abs( float( entry.header.x1 - entry.header.x ) );
      float y_base = abs( float( entry.header.y1 - entry.header.y ) );
      float z_base = abs( float( entry.header.z1 - entry.header.z ) );

      fprintf( fp_out, "Vertices I16: \n" );
      for( auto& entry1 : entry.data.vertices_i16 )
      {
         uint16_t var1 = entry1.x;
         uint16_t var2 = entry1.y;
         uint16_t var3 = entry1.z;
         float x = ( var1 );
         float y = ( var2 );
         float z = ( var3 );
         fprintf( fp_out, "\t%f, ", (x / 0xFFFF) * x_base + entry.header.x );
         fprintf( fp_out, "%f, ", (y / 0xFFFF) * y_base + entry.header.y );
         fprintf( fp_out, "%f ", (z / 0xFFFF) * z_base + entry.header.z );
         fprintf( fp_out, "\n");

      }




      fprintf( fp_out, "Indices: \n" );
      for( auto& entry1 : entry.data.indices )
      {
         fprintf( fp_out, "\t %i, %i, %i - %x,%x,%x \n",
                  entry1.index[0], entry1.index[1], entry1.index[2], entry1.unknown[0], entry1.unknown[1], entry1.unknown[2] );
      }
      fprintf( fp_out, "\n" );
   }

   fclose( fp_out );
*/