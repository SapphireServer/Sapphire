#pragma once

#include <Common.h>
#include "recastnavigation/Detour/Include/DetourNavMesh.h"
#include "recastnavigation/Detour/Include/DetourNavMeshQuery.h"
#include "recastnavigation/DetourCrowd/Include/DetourCrowd.h"

namespace Sapphire::Common::Navi
{
  const int32_t MAX_POLYS = 32;
  const int32_t MAX_SMOOTH = 2048;

  const int32_t NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET'
  const int32_t NAVMESHSET_VERSION = 1;

  class NaviProvider
  {
    struct NavMeshSetHeader
    {
      int32_t magic;
      int32_t version;
      int32_t numTiles;
      dtNavMeshParams params;
    };

    struct NavMeshTileHeader
    {
      dtTileRef tileRef;
      int32_t dataSize;
    };

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

    int32_t addAgent( const Common::FFXIVARR_POSITION3& pos, float radius );

    void removeAgent( int32_t naviAgentId );

    void updateCrowd( float timeInSeconds );

    static void calcVel( float* vel, const float* pos, const float* tgt, const float speed );

    void setMoveTarget( int32_t naviAgentId, const Common::FFXIVARR_POSITION3& endPos );
    void resetMoveTarget( int32_t naviAgentId );

    Common::FFXIVARR_POSITION3 getMovePos( int32_t naviAgentId );

    bool isAgentActive( int32_t naviAgentId ) const;
    bool hasTargetState( int32_t naviAgentId ) const;

    int32_t updateAgentPosition( int32_t naviAgentId, const Common::FFXIVARR_POSITION3& pos, float radius );

    void addAgentUpdateFlag( int32_t naviAgentId, uint8_t flags );
    void removeAgentUpdateFlag( int32_t naviAgentId, uint8_t flags );

    void updateAgentParameters( int32_t naviAgentId, float radius, bool isRunning );

  protected:
    std::string m_internalName;

    dtNavMesh* m_naviMesh;
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