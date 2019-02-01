#ifndef SAPPHIRE_TILEDNAVMESHGENERATOR_H
#define SAPPHIRE_TILEDNAVMESHGENERATOR_H

#include <string>
#include <cassert>
#include <cmath>

#include "ext/MeshLoaderObj.h"
#include "ext/ChunkyTriMesh.h"

#include "recastnavigation/Detour/Include/DetourNavMesh.h"
#include "recastnavigation/Detour/Include/DetourNavMeshQuery.h"
#include "recastnavigation/Recast/Include/Recast.h"

class TiledNavmeshGenerator
{
public:
  enum SamplePartitionType
  {
    SAMPLE_PARTITION_WATERSHED,
    SAMPLE_PARTITION_MONOTONE,
    SAMPLE_PARTITION_LAYERS,
  };

  enum SamplePolyAreas
  {
    SAMPLE_POLYAREA_GROUND,
    SAMPLE_POLYAREA_WATER,
    SAMPLE_POLYAREA_ROAD,
    SAMPLE_POLYAREA_DOOR,
    SAMPLE_POLYAREA_GRASS,
    SAMPLE_POLYAREA_JUMP,
  };
  enum SamplePolyFlags
  {
    SAMPLE_POLYFLAGS_WALK		= 0x01,		// Ability to walk (ground, grass, road)
    SAMPLE_POLYFLAGS_SWIM		= 0x02,		// Ability to swim (water).
    SAMPLE_POLYFLAGS_DOOR		= 0x04,		// Ability to move through doors.
    SAMPLE_POLYFLAGS_JUMP		= 0x08,		// Ability to jump.
    SAMPLE_POLYFLAGS_DISABLED	= 0x10,		// Disabled polygon
    SAMPLE_POLYFLAGS_ALL		= 0xffff	// All abilities.
  };

  static const int NAVMESHSET_MAGIC = 'M'<<24 | 'S'<<16 | 'E'<<8 | 'T'; //'MSET';
  static const int NAVMESHSET_VERSION = 1;

  struct NavMeshSetHeader
  {
    int magic;
    int version;
    int numTiles;
    dtNavMeshParams params;
  };

  struct NavMeshTileHeader
  {
    dtTileRef tileRef;
    int dataSize;
  };


  TiledNavmeshGenerator() = default;
  ~TiledNavmeshGenerator();

  bool init( const std::string& path );
  unsigned char* buildTileMesh( const int tx, const int ty, const float* bmin, const float* bmax, int& dataSize );
  bool buildNavmesh();
  void saveNavmesh( const std::string& name );

private:
  rcConfig m_cfg;

  rcMeshLoaderObj* m_mesh;
  rcChunkyTriMesh* m_chunkyMesh;

  rcContext* m_ctx;
  dtNavMesh* m_navMesh;
  rcHeightfield* m_solid;
  rcContourSet* m_cset;
  rcPolyMesh* m_pmesh;
  rcPolyMeshDetail* m_dmesh;

  rcCompactHeightfield* m_chf;

  unsigned char* m_triareas;

  int m_maxTiles = 0;
  int m_maxPolysPerTile = 0;

  int m_tileTriCount = 0;

  int m_partitionType = SamplePartitionType::SAMPLE_PARTITION_WATERSHED;

  float m_meshBMin[ 3 ];
  float m_meshBMax[ 3 ];

  float m_lastBuiltTileBmin[ 3 ];
  float m_lastBuiltTileBmax[ 3 ];

  // options
  float m_tileSize = 160.f;
  float m_cellSize = 0.2f;
  float m_cellHeight = 0.2f;

  float m_agentMaxSlope = 56.f;
  float m_agentHeight = 2.f;
  float m_agentMaxClimb = 0.6f;
  float m_agentRadius = 0.5f;

  float m_regionMinSize = 8.f;
  float m_regionMergeSize = 20.f;

  float m_edgeMaxLen = 12.f;
  float m_edgeMaxError = 1.4f;
  float m_vertsPerPoly = 6.f;

  float m_detailSampleDist = 6.f;
  float m_detailSampleMaxError = 1.f;

};


#endif //SAPPHIRE_TILEDNAVMESHGENERATOR_H
