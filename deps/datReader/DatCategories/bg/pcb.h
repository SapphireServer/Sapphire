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