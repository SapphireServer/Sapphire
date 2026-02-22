#pragma once

#include <Common.h>
#include "recastnavigation/Detour/Include/DetourNavMesh.h"
#include "recastnavigation/Detour/Include/DetourNavMeshQuery.h"
#include "recastnavigation/Detour/Include/DetourNavMeshBuilder.h"
#include "recastnavigation/DetourCrowd/Include/DetourCrowd.h"
#include "recastnavigation/DetourTileCache/Include/DetourTileCache.h"
#include "recastnavigation/DetourTileCache/Include/DetourTileCacheBuilder.h"
#include "recastnavigation/Recast/Include/Recast.h"

#include "FastLZ/fastlz.h"

namespace Sapphire::Common::Navi
{
  const int32_t MAX_POLYS = 32;
  const int32_t MAX_SMOOTH = 2048;

  const int32_t NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET'
  const int32_t NAVMESHSET_VERSION = 1;

  struct TileCacheSetHeader {
    int magic;
    int version;
    int numTiles;
    dtNavMeshParams meshParams;
    dtTileCacheParams cacheParams;
  };

  struct TileCacheData {
    unsigned char* data;
    int dataSize;
  };

  struct TileCacheTileHeader {
    dtCompressedTileRef tileRef;
    int dataSize;
  };

  /** 1. Memory Allocator for Tile Cache **/
  struct LinearAllocator : public dtTileCacheAlloc {
    unsigned char* buffer;
    size_t capacity, top;
    LinearAllocator( size_t cap ) : capacity( cap ), top( 0 ) { buffer = new unsigned char[ cap ]; }
    ~LinearAllocator() { delete[] buffer; }
    void reset() override { top = 0; }
    void* alloc( const size_t size ) override
    {
      if( top + size > capacity ) return nullptr;
      unsigned char* mem = &buffer[ top ];
      top += size;
      return mem;
    }
    void free( void* ) override {}
  };

  /** 2. FastLZ Compressor for Tiles **/
  struct FastLZCompressor : public dtTileCacheCompressor {
    int maxCompressedSize( const int bufferSize ) override { return ( int ) ( bufferSize * 1.05f ); }
    dtStatus compress( const unsigned char* buffer, const int bufferSize,
                       unsigned char* compressed, const int, int* compressedSize ) override
    {
      *compressedSize = fastlz_compress( buffer, bufferSize, compressed );
      return DT_SUCCESS;
    }
    dtStatus decompress( const unsigned char* compressed, const int compressedSize,
                         unsigned char* buffer, const int maxBufferSize, int* bufferSize ) override
    {
      *bufferSize = fastlz_decompress( compressed, compressedSize, buffer, maxBufferSize );
      return *bufferSize < 0 ? DT_FAILURE : DT_SUCCESS;
    }
  };

  /** 3. Mesh Processor (Assigns Area IDs and Flags) **/
  struct MeshProcess : public dtTileCacheMeshProcess {
    void process( struct dtNavMeshCreateParams* params, unsigned char* polyAreas, unsigned short* polyFlags ) override
    {
      for( int i = 0; i < params->polyCount; ++i )
      {
        if( polyAreas[ i ] == RC_WALKABLE_AREA )
        {
          polyAreas[ i ] = 0;   // Default Ground Area
          polyFlags[ i ] = 0x01;// Walkable Flag
        }
      }
    }
  };

  class NaviProvider
  {

    struct TileCacheSetHeader
    {
      int magic;
      int version;
      int numTiles;
      dtNavMeshParams meshParams;
      dtTileCacheParams cacheParams;
    };

    struct TileCacheData {
      unsigned char* data;
      int dataSize;
    };

    struct TileCacheTileHeader {
      dtCompressedTileRef tileRef;
      int dataSize;
    };

    static const int EXPECTED_LAYERS_PER_TILE = 4;
    static const int MAX_LAYERS = 32;

    static const int TILECACHESET_MAGIC = 'T' << 24 | 'S' << 16 | 'E' << 8 | 'T';//'TSET';
    static const int TILECACHESET_VERSION = 1;

  public:
    explicit NaviProvider( const std::string& internalName );

    bool init( const std::string& naviPath );
    bool loadMesh( const std::string& path );
    void initQuery();

    void toDetourPos( const Common::FFXIVARR_POSITION3& position, float* out );
    Common::FFXIVARR_POSITION3 toGamePos( float* pos );

    std::vector< Common::FFXIVARR_POSITION3 > findFollowPath( const Common::FFXIVARR_POSITION3& startPos,
                                                              const Common::FFXIVARR_POSITION3& endPos );
    Common::FFXIVARR_POSITION3 findRandomPositionInCircle( const Common::FFXIVARR_POSITION3& startPos,
                                                           float maxRadius );

    Common::FFXIVARR_POSITION3 findNearestPosition( float x, float z );

    bool hasNaviMesh() const;

    int32_t addAgent( const Common::FFXIVARR_POSITION3& pos, float radius, float speed = 1.0f );

    void removeAgent( int32_t naviAgentId );

    void update( float timeInSeconds );

    static void calcVel( float* vel, const float* pos, const float* tgt, const float speed );

    void setMoveTarget( int32_t naviAgentId, const Common::FFXIVARR_POSITION3& endPos );
    void resetMoveTarget( int32_t naviAgentId );

    Common::FFXIVARR_POSITION3 getAgentPos( int32_t naviAgentId );
    float getAgentSpeed( int32_t naviAgentId );

    bool isAgentActive( int32_t naviAgentId ) const;
    bool hasTargetState( int32_t naviAgentId ) const;

    int32_t updateAgentPosition( int32_t naviAgentId, const Common::FFXIVARR_POSITION3& pos, float radius, float speed );

    void addAgentUpdateFlag( int32_t naviAgentId, uint8_t flags );
    void removeAgentUpdateFlag( int32_t naviAgentId, uint8_t flags );

    void updateAgentParameters( int32_t naviAgentId, float radius, bool isRunning, float speed );
    const dtNavMesh* getNavMesh() const { return m_naviMesh; }

    std::string getNaviPath() const { return m_naviPath; }

    // halfExtents: { width, height, depth } 
    void toggleDoor( dtObstacleRef& doorRef, const Common::FFXIVARR_POSITION3& pos, const Common::FFXIVARR_POSITION3& halfExtents, float rot, bool closed );
    void toggleObstacle( dtObstacleRef& obstacleRef, const Common::FFXIVARR_POSITION3& pos, float radius, float height, bool closed );

  protected:
    std::string m_internalName;
    std::string m_naviPath;

    dtNavMesh* m_naviMesh;
    dtTileCache* m_tileCache;
    LinearAllocator* m_talloc;
    FastLZCompressor* m_tcomp;
    MeshProcess* m_tmproc;

    dtNavMeshQuery* m_naviMeshQuery;
    dtObstacleAvoidanceDebugData* m_vod;
    std::unique_ptr< dtCrowd > m_pCrowd;

    float m_polyFindRange[ 3 ];

  private:
    int32_t fixupCorridor( dtPolyRef* path, int32_t npath, int32_t maxPath, const dtPolyRef* visited, int32_t nvisited );
    int32_t fixupShortcuts( dtPolyRef* path, int32_t npath, dtNavMeshQuery* navQuery );
    inline bool inRange( const float* v1, const float* v2, const float r, const float h );
    bool getSteerTarget( dtNavMeshQuery* navQuery, const float* startPos, const float* endPos, const float minTargetDist,
		                     const dtPolyRef* path, const int32_t pathSize, float* steerPos, uint8_t& steerPosFlag,
			       	           dtPolyRef& steerPosRef, float* outPoints = 0, int32_t* outPointCount = 0 );



  };

}