#pragma once

#include <Common.h>
#include "recastnavigation/Detour/Include/DetourNavMesh.h"
#include "recastnavigation/Detour/Include/DetourNavMeshQuery.h"
#include "recastnavigation/DetourCrowd/Include/DetourCrowd.h"
#include <unordered_map>
#include <functional>
#include <optional>

namespace Sapphire::Common::Navigation
{
  const int32_t MAX_POLYS = 32;
  const int32_t MAX_SMOOTH = 2048;

  const int32_t NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET'
  const int32_t NAVMESHSET_VERSION = 1;

  enum class PathfindingResult : uint8_t
  {
    Success,
    NoMeshLoaded,
    StartNotFound,
    EndNotFound,
    NoPathFound,
    InvalidAgent,
    DoorBlocked
  };

  enum class DoorState : uint8_t
  {
    Open,
    Closed,
    Locked
  };

  struct PathfindingRequest
  {
    Common::FFXIVARR_POSITION3 start;
    Common::FFXIVARR_POSITION3 end;
    float agentRadius = 1.0f;
    bool allowDoors = true;
    std::function< bool( uint32_t ) > doorAccessCheck = nullptr; // Callback for door permission checks
  };

  struct PathfindingResponse
  {
    PathfindingResult result;
    std::vector< Common::FFXIVARR_POSITION3 > waypoints;
    std::vector< uint32_t > doorsUsed; // Door IDs that need to be opened for this path
    float totalDistance = 0.0f;
    std::string errorMessage;
  };

  struct AgentParameters
  {
    float radius = 1.0f;
    float height = 3.0f;
    float maxSpeed = 5.0f;
    float maxAcceleration = 25.0f;
    bool isRunning = false;
    uint8_t crowdFlags = 0;
  };

  struct DoorInfo
  {
    uint32_t doorId;
    Common::FFXIVARR_POSITION3 position;
    DoorState state = DoorState::Closed;
    std::vector< dtPolyRef > connectedPolys; // Polygons this door connects
    float interactionRange = 2.0f;
  };

  class PathFinder
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
    explicit PathFinder( const std::string& zoneName );

    ~PathFinder();

    // Core initialization
    bool initialize( const std::string& meshPath );

    bool isInitialized() const { return m_naviMesh != nullptr; }

    void shutdown();

    // Pathfinding methods
    PathfindingResponse findPath( const PathfindingRequest& request );

    std::vector< Common::FFXIVARR_POSITION3 > findStraightPath(
      const Common::FFXIVARR_POSITION3& start,
      const Common::FFXIVARR_POSITION3& end
    );

    // Utility methods
    Common::FFXIVARR_POSITION3 findNearestWalkablePosition( const Common::FFXIVARR_POSITION3& position,
                                                            float searchRadius = 5.0f );

    Common::FFXIVARR_POSITION3 findRandomPositionInRadius( const Common::FFXIVARR_POSITION3& center, float radius );

    bool isPositionWalkable( const Common::FFXIVARR_POSITION3& position, float tolerance = 1.0f );

    float calculateDistance( const Common::FFXIVARR_POSITION3& start, const Common::FFXIVARR_POSITION3& end ) const;

    // Agent management (for crowd simulation)
    int32_t createAgent( const Common::FFXIVARR_POSITION3& position, const AgentParameters& params = {} );

    bool removeAgent( int32_t agentId );

    bool setAgentDestination( int32_t agentId, const Common::FFXIVARR_POSITION3& destination );

    bool resetAgentDestination( int32_t agentId );

    Common::FFXIVARR_POSITION3 getAgentPosition( int32_t agentId );

    bool isAgentActive( int32_t agentId ) const;

    bool hasAgentReachedDestination( int32_t agentId ) const;

    bool updateAgentParameters( int32_t agentId, const AgentParameters& params );

    // Crowd simulation update
    void updateCrowdSimulation( float deltaTime );

    // Door system (for future expansion)
    void registerDoor( uint32_t doorId, const Common::FFXIVARR_POSITION3& position,
                       const std::vector< dtPolyRef >& connectedPolys );

    void setDoorState( uint32_t doorId, DoorState state );

    DoorState getDoorState( uint32_t doorId ) const;

    std::vector< uint32_t > getDoorsNearPosition( const Common::FFXIVARR_POSITION3& position,
                                                  float radius = 10.0f ) const;

    void clearAllDoors();

    // Configuration
    void setPathfindingExtents( float x = 20.0f, float y = 20.0f, float z = 20.0f );

    void setObstacleAvoidanceQuality( uint8_t quality ); // 0-3, higher is better but slower

    // Debug/Info methods
    std::string getZoneName() const { return m_zoneName; }
    std::string getMeshPath() const { return m_meshPath; }
    const dtNavMesh *getNavMesh() const { return m_naviMesh; }

    size_t getActiveAgentCount() const;

  private:
    // Core pathfinding internals
    bool loadNavMesh( const std::string& path );

    void initializeQuery();

    void initializeCrowd();

    void setupObstacleAvoidanceParams();

    // Pathfinding utilities
    std::optional< dtPolyRef > findNearestPoly( const Common::FFXIVARR_POSITION3& position,
                                                const float *extents = nullptr );

    bool getSteerTarget( const float *startPos, const float *endPos, const float minTargetDist,
                         const dtPolyRef *path, int32_t pathSize, float *steerPos,
                         uint8_t& steerPosFlag, dtPolyRef& steerPosRef );

    int32_t fixupCorridor( dtPolyRef *path, int32_t npath, int32_t maxPath,
                           const dtPolyRef *visited, int32_t nvisited );

    int32_t fixupShortcuts( dtPolyRef *path, int32_t npath );

    bool inRange( const float *v1, const float *v2, float r, float h ) const;

    // Door pathfinding integration
    bool isDoorAccessible( uint32_t doorId, const std::function< bool( uint32_t ) >& accessCheck ) const;

    std::vector< uint32_t > findRequiredDoorsForPath( const dtPolyRef *polys, int32_t polyCount ) const;

    // Coordinate conversion
    void toDetourCoords( const Common::FFXIVARR_POSITION3& position, float *out ) const;

    Common::FFXIVARR_POSITION3 fromDetourCoords( const float *coords ) const;

    // Agent validation
    bool isValidAgentId( int32_t agentId ) const;

    // Member variables
    std::string m_zoneName;
    std::string m_meshPath;

    // Detour/Recast objects
    dtNavMesh *m_naviMesh;
    dtNavMeshQuery *m_naviMeshQuery;
    std::unique_ptr< dtCrowd > m_crowd;
    dtObstacleAvoidanceDebugData *m_avoidanceDebug;

    // Configuration
    float m_pathfindingExtents[ 3 ];
    uint8_t m_obstacleAvoidanceQuality;

    // Door system
    std::unordered_map< uint32_t, DoorInfo > m_doors;

    // Agent tracking
    std::unordered_map< int32_t, AgentParameters > m_agentParams;
  };
}
