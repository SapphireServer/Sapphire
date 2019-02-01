#ifndef _PCB_H
#define _PCB_H

#include <stdint.h>
#include <vector>

struct PCB_HEADER
{
  uint32_t unknown_1;
  uint32_t unknown_2;
  uint32_t num_entries; // count starts at 0
  uint32_t total_indices;
  uint64_t padding;
};

struct PCB_BLOCK_HEADER
{
  uint32_t type; // 0 for entry, 0x30 for group
  uint32_t group_size; // when group size in bytes for the group block
  // bounding box
  float x;
  float y;
  float z;
  float x1;
  float y1;
  float z1;
  // number of vertices packed into 16 bit
  uint16_t num_v16;
  // number of indices
  uint16_t num_indices;
  // number of normal floar vertices
  uint32_t num_vertices;
};

struct PCB_VERTEXDATA
{
  float x;
  float y;
  float z;
};

struct PCB_INDEXDATA
{
  uint8_t index[3];
  uint8_t unknown[3];
  uint8_t unknown1[6];
};

struct PCB_VERTEXDATAI16
{
  uint16_t x;
  uint16_t y;
  uint16_t z;
};

struct PCB_BLOCK_DATA
{
  std::vector< PCB_VERTEXDATA > vertices;
  std::vector< PCB_VERTEXDATAI16 > vertices_i16;
  std::vector< PCB_INDEXDATA > indices;
};

struct PCB_BLOCK_ENTRY
{
  PCB_BLOCK_HEADER header;
  PCB_BLOCK_DATA data;
};

struct PCB_FILE
{
  PCB_HEADER header;
  std::vector< PCB_BLOCK_ENTRY > entries;

  PCB_FILE( char* buf )
  {
    uint32_t offset = 0;
    memcpy( &header, buf, sizeof( header ));
    offset += sizeof( header );
    entries.resize( header.num_entries );
    bool isgroup = true;
    while( isgroup )
    {
      PCB_BLOCK_ENTRY block_entry;
      memcpy( &block_entry.header, buf + offset, sizeof( block_entry.header ) );
      isgroup = block_entry.header.type == 0x30;

      //printf( "BLOCKHEADER_%X: type: %i, group_size: %i\n", offset, block_entry.header.type, block_entry.header.group_size );
      //
      if( isgroup )
      {
        parseBlockEntry( buf + offset + 0x30, entries, offset);
        offset += block_entry.header.group_size;
      }
      else
      {
        parseBlockEntry( buf + offset, entries, offset );
      }
    }
  }
  
  int parseBlockEntry( char* data, std::vector< PCB_BLOCK_ENTRY >& entries, int gOff )
  {
    int offset = 0;
    bool isgroup = true;
    while( isgroup )
    {
      PCB_BLOCK_ENTRY block_entry;
      memcpy( &block_entry.header, data + offset, sizeof( block_entry.header ) );
      isgroup = block_entry.header.type == 0x30;
  
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
          memcpy( &block_entry.data.vertices[ 0 ], data + doffset, size_vertexbuffer * 4 );
          doffset += size_vertexbuffer * 4;
        }
        if( block_entry.header.num_v16 != 0 )
        {
          block_entry.data.vertices_i16.resize( block_entry.header.num_v16 );
          int32_t size_unknownbuffer = block_entry.header.num_v16 * 6;
          memcpy( &block_entry.data.vertices_i16[ 0 ], data + doffset, size_unknownbuffer );
          doffset += block_entry.header.num_v16 * 6;
        }
        if( block_entry.header.num_indices != 0 )
        {
          block_entry.data.indices.resize( block_entry.header.num_indices );
          int32_t size_indexbuffer = block_entry.header.num_indices * 12;
          memcpy( &block_entry.data.indices[ 0 ], data + doffset, size_indexbuffer );
          doffset += size_indexbuffer;
        }
        entries.push_back( block_entry );
      }
    }
  
    return 0;
  }

};

struct PCB_LIST_ENTRY
{
  uint32_t id;
  float x, y, z, x2, y2, z2, rot;
};

struct PCB_LIST_BASE_ENTRY
{
  float x, y, z, x2, y2, z2, rot;
};

struct PCB_LIST_FILE
{
  uint32_t count;
  PCB_LIST_BASE_ENTRY entry;
  std::vector< PCB_LIST_ENTRY > entries;
};
#endif