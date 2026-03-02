#ifndef SAPPHIRE_TILEDNAVMESHGENERATOR_H
#define SAPPHIRE_TILEDNAVMESHGENERATOR_H

#include <string>
#include <cassert>
#include <cmath>
#include <cstring>
#include <memory>

#include "ext/MeshLoaderObj.h"
#include "ext/ChunkyTriMesh.h"

#include "recastnavigation/Detour/Include/DetourNavMesh.h"
#include "recastnavigation/Detour/Include/DetourNavMeshQuery.h"
#include "recastnavigation/Recast/Include/Recast.h"
#include <DetourTileCache.h>
#include <DetourTileCacheBuilder.h>
#include <DetourMath.h>
#include <DetourCommon.h>
#include <DetourNavMeshBuilder.h>

#include "FastLZ/fastlz.h"
#include <recastnavigation/RecastDemo/Include/Sample.h>
#include <recastnavigation/RecastDemo/Include/InputGeom.h>

// todo: this no worky
struct PrintContext : rcContext {
  explicit PrintContext( bool state = true ) : rcContext( state ) {}
protected:
  void doLog( const rcLogCategory category, const char* msg, const int /*len*/ ) override
  {
    const char* catStr = "";
    switch( category )
    {
      case RC_LOG_PROGRESS: catStr = "PROGRESS"; break;
      case RC_LOG_WARNING:  catStr = "WARNING";  break;
      case RC_LOG_ERROR:    catStr = "ERROR";    break;
    }
    printf( "[Recast %s] %s\n", catStr, msg );
    fflush( stdout );
  }
};

struct FastLZCompressor : dtTileCacheCompressor {
  ~FastLZCompressor() override = default;

  int maxCompressedSize( const int bufferSize ) override { return static_cast< int >( static_cast< float >( bufferSize ) * 1.05f ); }

  dtStatus compress(
          const unsigned char* buffer,
          const int bufferSize,
          unsigned char* compressed,
          const int /*maxCompressedSize*/,
          int* compressedSize ) override
  {
    *compressedSize = fastlz_compress( buffer, bufferSize, compressed );
    return DT_SUCCESS;
  }

  dtStatus decompress(
          const unsigned char* compressed,
          const int compressedSize,
          unsigned char* buffer,
          const int maxBufferSize,
          int* bufferSize ) override
  {
    *bufferSize = fastlz_decompress( compressed, compressedSize, buffer, maxBufferSize );
    return *bufferSize < 0 ? DT_FAILURE : DT_SUCCESS;
  }
};

struct LinearAllocator : dtTileCacheAlloc {
  unsigned char* buffer = nullptr;
  size_t capacity = 0;
  size_t top = 0;
  size_t high = 0;

  explicit LinearAllocator( const size_t cap ) { resize( cap ); }

  ~LinearAllocator() override { dtFree( buffer ); }

  void resize( const size_t cap )
  {
    if( buffer )
    {
      dtFree( buffer );
    }
    buffer = static_cast< unsigned char* >( dtAlloc( cap, DT_ALLOC_PERM ) );
    capacity = cap;
  }

  void reset() override
  {
    high = dtMax( high, top );
    top = 0;
  }

  void* alloc( const size_t size ) override
  {
    if( !buffer )
    {
      return 0;
    }
    if( top + size > capacity )
    {
      return 0;
    }

    unsigned char* mem = &buffer[ top ];
    top += size;
    return mem;
  }

  void free( void* /*ptr*/ ) override {}
};

struct MeshProcess : dtTileCacheMeshProcess {
  ~MeshProcess() override = default;
  InputGeom* m_geom{ nullptr };
  void init( InputGeom* input ) { m_geom = input; }
  void process( dtNavMeshCreateParams* params, unsigned char* polyAreas, unsigned short* polyFlags ) override;
};

static const int EXPECTED_LAYERS_PER_TILE = 4;
static const int MAX_LAYERS = 32;

static const int TILECACHESET_MAGIC = 'T' << 24 | 'S' << 16 | 'E' << 8 | 'T';//'TSET';
static const int TILECACHESET_VERSION = 1;

struct TileCacheSetHeader
{
  int magic;
  int version;
  int numTiles;
  dtNavMeshParams meshParams;
  dtTileCacheParams cacheParams;
};

struct TileCacheData
{
  unsigned char* data;
  int dataSize;
};

struct TileCacheTileHeader
{
  dtCompressedTileRef tileRef;
  int dataSize;
};

struct RasterizationContext {
  rcHeightfield* solid = nullptr;
  unsigned char* triAreas = nullptr;
  rcHeightfieldLayerSet* lset = nullptr;
  rcCompactHeightfield* chf = nullptr;
  TileCacheData tiles[ MAX_LAYERS ]{};
  int ntiles = 0;

  RasterizationContext() { memset( tiles, 0, sizeof( TileCacheData ) * MAX_LAYERS ); }

  ~RasterizationContext()
  {
    rcFreeHeightField( solid );
    delete[] triAreas;
    rcFreeHeightfieldLayerSet( lset );
    rcFreeCompactHeightfield( chf );
    for( int i = 0; i < MAX_LAYERS; ++i )
    {
      dtFree( tiles[ i ].data );
      tiles[ i ].data = 0;
    }
  }
};

class TiledNavmeshGenerator
{
public:


  TiledNavmeshGenerator() = default;
  ~TiledNavmeshGenerator();

  bool init( const std::string& path );
  unsigned char* buildTileMesh( const int tx, const int ty, const float* bmin, const float* bmax, int& dataSize );
  bool buildNavmesh();
  bool buildTiledCache();
  int rasterizeTileLayers(
          const int tileX,
          const int tileY,
          const rcConfig& cfg,
          TileCacheData* tiles,
          const int maxTiles ) const;

  void saveNavmesh( const std::string& name );

private:
  rcConfig m_cfg;

  rcMeshLoaderObj* m_mesh;
  rcChunkyTriMesh* m_chunkyMesh;

  rcContext* m_ctx{ nullptr };
  dtTileCache* m_tileCache{ nullptr };
  LinearAllocator* m_tAllocator{ nullptr };
  FastLZCompressor* m_tCompressor{ nullptr };
  MeshProcess* m_tMeshProcess{ nullptr };

  dtNavMesh* m_navMesh{ nullptr };
  rcHeightfield* m_solid{ nullptr };
  rcContourSet* m_cset{ nullptr };
  rcPolyMesh* m_pmesh{ nullptr };
  rcPolyMeshDetail* m_dmesh{ nullptr };
  InputGeom* m_inputGeometry{ nullptr };
  rcCompactHeightfield* m_chf{ nullptr };

  InputGeom* m_geom{ 0 };

  unsigned char* m_triareas{ nullptr };

  int m_maxTiles = 0;
  int m_maxPolysPerTile = 0;

  int m_tileTriCount = 0;

  int m_partitionType = static_cast< int >( SamplePartitionType::WATERSHED );

  float m_meshBMin[ 3 ];
  float m_meshBMax[ 3 ];

  float m_lastBuiltTileBmin[ 3 ];
  float m_lastBuiltTileBmax[ 3 ];

  // options
  float m_tileSize = 64.f;
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
