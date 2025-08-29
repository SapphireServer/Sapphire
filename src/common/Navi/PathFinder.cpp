#include <Common.h>
#include <Logging/Logger.h>
#include <Random/RNGMgr.h>
#include <Service.h>

#include "PathFinder.h"
#include "Common.h"
#include "Vector3.h"

#include <recastnavigation/Detour/Include/DetourNavMesh.h>
#include <recastnavigation/Detour/Include/DetourNavMeshQuery.h>
#include <DetourCommon.h>
#include <recastnavigation/Recast/Include/Recast.h>
#include <filesystem>

using namespace Sapphire;
using namespace Sapphire::Common::Navigation;

PathFinder::PathFinder( const std::string& zoneName ) :
  m_zoneName( zoneName ),
  m_naviMesh( nullptr ),
  m_naviMeshQuery( nullptr ),
  m_avoidanceDebug( nullptr ),
  m_obstacleAvoidanceQuality( 2 )
{
  // Set default pathfinding extents
  setPathfindingExtents();
}

PathFinder::~PathFinder()
{
  shutdown();
}

bool PathFinder::initialize( const std::string& meshPath )
{
  m_meshPath = meshPath;
  auto meshFolder = std::filesystem::path( meshPath ) / std::filesystem::path( m_zoneName );

  if( !std::filesystem::exists( meshFolder ) )
  {
    Logger::error( "PathFinder: Mesh folder does not exist: {}", meshFolder.string() );
    return false;
  }

  auto navMeshFile = meshFolder / std::filesystem::path( m_zoneName + ".nav" );

  if( !loadNavMesh( navMeshFile.string() ) )
  {
    Logger::error( "PathFinder: Failed to load navigation mesh for zone: {}", m_zoneName );
    return false;
  }

  initializeCrowd();
  initializeQuery();
  setupObstacleAvoidanceParams();

  Logger::info( "PathFinder: Successfully initialized for zone: {}", m_zoneName );
  return true;
}

void PathFinder::shutdown()
{
  if( m_avoidanceDebug )
  {
    dtFreeObstacleAvoidanceDebugData( m_avoidanceDebug );
    m_avoidanceDebug = nullptr;
  }

  if( m_naviMeshQuery )
  {
    dtFreeNavMeshQuery( m_naviMeshQuery );
    m_naviMeshQuery = nullptr;
  }

  if( m_naviMesh )
  {
    dtFreeNavMesh( m_naviMesh );
    m_naviMesh = nullptr;
  }

  m_crowd.reset();
  m_doors.clear();
  m_agentParams.clear();
}

PathfindingResponse PathFinder::findPath( const PathfindingRequest& request )
{
  PathfindingResponse response;

  if( !m_naviMesh || !m_naviMeshQuery )
  {
    response.result = PathfindingResult::NoMeshLoaded;
    response.errorMessage = "Navigation mesh not loaded";
    return response;
  }

  float startPos[ 3 ], endPos[ 3 ];
  toDetourCoords( request.start, startPos );
  toDetourCoords( request.end, endPos );

  dtQueryFilter filter;
  filter.setIncludeFlags( 0xffff );
  filter.setExcludeFlags( 0 );

  auto startPoly = findNearestPoly( request.start );
  auto endPoly = findNearestPoly( request.end );

  if( !startPoly.has_value() )
  {
    response.result = PathfindingResult::StartNotFound;
    response.errorMessage = "Could not find walkable area near start position";
    return response;
  }

  if( !endPoly.has_value() )
  {
    response.result = PathfindingResult::EndNotFound;
    response.errorMessage = "Could not find walkable area near end position";
    return response;
  }

  dtPolyRef polys[ MAX_POLYS ];
  int32_t numPolys = 0;

  auto status = m_naviMeshQuery->findPath( startPoly.value(), endPoly.value(), startPos, endPos,
                                           &filter, polys, &numPolys, MAX_POLYS );

  if( dtStatusFailed( status ) || numPolys == 0 )
  {
    response.result = PathfindingResult::NoPathFound;
    response.errorMessage = "Could not calculate path between positions";
    return response;
  }

  // Check for doors along the path
  if( request.allowDoors )
  {
    response.doorsUsed = findRequiredDoorsForPath( polys, numPolys );

    // Check door access if callback provided
    if( request.doorAccessCheck )
    {
      for( uint32_t doorId : response.doorsUsed )
      {
        if( !isDoorAccessible( doorId, request.doorAccessCheck ) )
        {
          response.result = PathfindingResult::DoorBlocked;
          response.errorMessage = "Path requires access to door " + std::to_string( doorId );
          return response;
        }
      }
    }
  }

  // Generate smooth path
  response.waypoints = findStraightPath( request.start, request.end );

  if( !response.waypoints.empty() )
  {
    response.result = PathfindingResult::Success;

    // Calculate total distance
    for( size_t i = 1; i < response.waypoints.size(); ++i )
    {
      response.totalDistance += calculateDistance( response.waypoints[ i - 1 ], response.waypoints[ i ] );
    }
  }
  else
  {
    response.result = PathfindingResult::NoPathFound;
    response.errorMessage = "Failed to generate smooth path";
  }

  return response;
}

std::vector< Common::FFXIVARR_POSITION3 > PathFinder::findStraightPath(
  const Common::FFXIVARR_POSITION3& start,
  const Common::FFXIVARR_POSITION3& end )
{
  std::vector< Common::FFXIVARR_POSITION3 > waypoints;

  if( !m_naviMesh || !m_naviMeshQuery )
    return waypoints;

  float startPos[ 3 ], endPos[ 3 ];
  toDetourCoords( start, startPos );
  toDetourCoords( end, endPos );

  dtQueryFilter filter;
  filter.setIncludeFlags( 0xffff );
  filter.setExcludeFlags( 0 );

  auto startPoly = findNearestPoly( start );
  auto endPoly = findNearestPoly( end );

  if( !startPoly.has_value() || !endPoly.has_value() )
    return waypoints;

  dtPolyRef polys[ MAX_POLYS ];
  int32_t numPolys = 0;

  m_naviMeshQuery->findPath( startPoly.value(), endPoly.value(), startPos, endPos,
                             &filter, polys, &numPolys, MAX_POLYS );

  if( numPolys == 0 )
    return waypoints;

  // Generate smooth path using the algorithm from the original implementation
  memcpy( polys, polys, sizeof( dtPolyRef ) * numPolys );
  int32_t npolys = numPolys;

  float iterPos[ 3 ], targetPos[ 3 ];
  m_naviMeshQuery->closestPointOnPoly( startPoly.value(), startPos, iterPos, nullptr );
  m_naviMeshQuery->closestPointOnPoly( polys[ npolys - 1 ], endPos, targetPos, nullptr );

  const float STEP_SIZE = 0.5f;
  const float SLOP = 0.15f;

  int32_t numSmoothPath = 0;
  float smoothPath[ MAX_SMOOTH * 3 ];

  dtVcopy( &smoothPath[ numSmoothPath * 3 ], iterPos );
  numSmoothPath++;

  while( npolys && numSmoothPath < MAX_SMOOTH )
  {
    float steerPos[ 3 ];
    uint8_t steerPosFlag;
    dtPolyRef steerPosRef;

    if( !getSteerTarget( iterPos, targetPos, SLOP, polys, npolys, steerPos, steerPosFlag, steerPosRef ) )
      break;

    bool endOfPath = ( steerPosFlag & DT_STRAIGHTPATH_END ) ? true : false;
    bool offMeshConnection = ( steerPosFlag & DT_STRAIGHTPATH_OFFMESH_CONNECTION ) ? true : false;

    float delta[ 3 ], len;
    dtVsub( delta, steerPos, iterPos );
    len = dtMathSqrtf( dtVdot( delta, delta ) );

    if( ( endOfPath || offMeshConnection ) && len < STEP_SIZE )
      len = 1;
    else
      len = STEP_SIZE / len;

    float moveTgt[ 3 ];
    dtVmad( moveTgt, iterPos, delta, len );

    float result[ 3 ];
    dtPolyRef visited[ 16 ];
    int32_t nvisited = 0;
    m_naviMeshQuery->moveAlongSurface( polys[ 0 ], iterPos, moveTgt, &filter,
                                       result, visited, &nvisited, 16 );

    npolys = fixupCorridor( polys, npolys, MAX_POLYS, visited, nvisited );
    npolys = fixupShortcuts( polys, npolys );

    float h = 0;
    m_naviMeshQuery->getPolyHeight( polys[ 0 ], result, &h );
    result[ 1 ] = h;
    dtVcopy( iterPos, result );

    if( endOfPath && inRange( iterPos, steerPos, SLOP, 1.0f ) )
    {
      dtVcopy( iterPos, targetPos );
      if( numSmoothPath < MAX_SMOOTH )
      {
        dtVcopy( &smoothPath[ numSmoothPath * 3 ], iterPos );
        numSmoothPath++;
      }
      break;
    }
    else if( offMeshConnection && inRange( iterPos, steerPos, SLOP, 1.0f ) )
    {
      float startPosConn[ 3 ], endPosConn[ 3 ];
      dtPolyRef prevRef = 0, polyRef = polys[ 0 ];
      int32_t npos = 0;

      while( npos < npolys && polyRef != steerPosRef )
      {
        prevRef = polyRef;
        polyRef = polys[ npos ];
        npos++;
      }

      for( int32_t i = npos; i < npolys; ++i )
        polys[ i - npos ] = polys[ i ];
      npolys -= npos;

      dtStatus status = m_naviMesh->getOffMeshConnectionPolyEndPoints( prevRef, polyRef, startPosConn, endPosConn );
      if( dtStatusSucceed( status ) )
      {
        if( numSmoothPath < MAX_SMOOTH )
        {
          dtVcopy( &smoothPath[ numSmoothPath * 3 ], startPosConn );
          numSmoothPath++;

          if( numSmoothPath & 1 )
          {
            dtVcopy( &smoothPath[ numSmoothPath * 3 ], startPosConn );
            numSmoothPath++;
          }
        }

        dtVcopy( iterPos, endPosConn );
        float eh = 0.0f;
        m_naviMeshQuery->getPolyHeight( polys[ 0 ], iterPos, &eh );
        iterPos[ 1 ] = eh;
      }
    }

    if( numSmoothPath < MAX_SMOOTH )
    {
      dtVcopy( &smoothPath[ numSmoothPath * 3 ], iterPos );
      numSmoothPath++;
    }
  }

  // Convert to game coordinates
  for( int32_t i = 0; i < numSmoothPath; i += 3 )
  {
    waypoints.emplace_back( fromDetourCoords( &smoothPath[ i ] ) );
  }

  return waypoints;
}

Common::FFXIVARR_POSITION3 PathFinder::findNearestWalkablePosition( const Common::FFXIVARR_POSITION3& position,
                                                                    float searchRadius )
{
  if( !m_naviMesh || !m_naviMeshQuery )
    return {};

  float pos[ 3 ];
  toDetourCoords( position, pos );

  float extents[ 3 ] = { searchRadius, searchRadius * 2.0f, searchRadius };
  float nearest[ 3 ];

  dtQueryFilter filter;
  filter.setIncludeFlags( 0xffff );
  filter.setExcludeFlags( 0 );

  dtPolyRef nearestRef;
  dtStatus status = m_naviMeshQuery->findNearestPoly( pos, extents, &filter, &nearestRef, nearest );

  if( dtStatusFailed( status ) || nearestRef == 0 )
    return {};

  return fromDetourCoords( nearest );
}

Common::FFXIVARR_POSITION3 PathFinder::findRandomPositionInRadius( const Common::FFXIVARR_POSITION3& center,
                                                                   float radius )
{
  if( !m_naviMesh || !m_naviMeshQuery )
    return {};

  float centerPos[ 3 ];
  toDetourCoords( center, centerPos );

  dtQueryFilter filter;
  filter.setIncludeFlags( 0xffff );
  filter.setExcludeFlags( 0 );

  auto centerPoly = findNearestPoly( center );
  if( !centerPoly.has_value() )
    return {};

  float randomPoint[ 3 ];
  dtPolyRef randomRef;

  auto& rngMgr = Common::Service< Common::Random::RNGMgr >::ref();
  auto rng = rngMgr.getRandGenerator< float >( 0.0f, 1.0f );

  dtStatus status = m_naviMeshQuery->findRandomPointAroundCircle( centerPoly.value(), centerPos, radius,
                                                                  &filter, []()
                                                                  {
                                                                    return static_cast< float >( rand() ) / RAND_MAX;
                                                                  },
                                                                  &randomRef, randomPoint );

  if( dtStatusFailed( status ) )
    return {};

  return fromDetourCoords( randomPoint );
}

bool PathFinder::isPositionWalkable( const Common::FFXIVARR_POSITION3& position, float tolerance )
{
  return findNearestPoly( position ).has_value();
}

float PathFinder::calculateDistance( const Common::FFXIVARR_POSITION3& start, const Common::FFXIVARR_POSITION3& end ) const
{
  float dx = end.x - start.x;
  float dy = end.y - start.y;
  float dz = end.z - start.z;
  return std::sqrt( dx * dx + dy * dy + dz * dz );
}

int32_t PathFinder::createAgent( const Common::FFXIVARR_POSITION3& position, const AgentParameters& params )
{
  if( !m_crowd )
    return -1;

  dtCrowdAgentParams crowdParams{};
  std::memset( &crowdParams, 0, sizeof( crowdParams ) );

  crowdParams.height = params.height;
  crowdParams.maxAcceleration = params.maxAcceleration;
  crowdParams.maxSpeed = params.maxSpeed * ( params.isRunning ? 2.0f : 1.0f );
  crowdParams.radius = params.radius * 0.75f;
  crowdParams.collisionQueryRange = crowdParams.radius * 12.0f;
  crowdParams.pathOptimizationRange = crowdParams.radius * 20.0f;
  crowdParams.updateFlags = params.crowdFlags;
  crowdParams.updateFlags |= DT_CROWD_ANTICIPATE_TURNS;
  crowdParams.obstacleAvoidanceType = m_obstacleAvoidanceQuality;

  float pos[ 3 ];
  toDetourCoords( position, pos );

  int32_t agentId = m_crowd->addAgent( pos, &crowdParams );
  if( agentId != -1 )
  {
    m_agentParams[ agentId ] = params;
  }

  return agentId;
}

bool PathFinder::removeAgent( int32_t agentId )
{
  if( !m_crowd || !isValidAgentId( agentId ) )
    return false;

  m_crowd->removeAgent( agentId );
  m_agentParams.erase( agentId );
  return true;
}

bool PathFinder::setAgentDestination( int32_t agentId, const Common::FFXIVARR_POSITION3& destination )
{
  if( !m_crowd || !isValidAgentId( agentId ) )
    return false;

  float pos[ 3 ];
  toDetourCoords( destination, pos );

  const dtQueryFilter *filter = m_crowd->getFilter( 0 );
  const float *halfExtents = m_crowd->getQueryExtents();

  dtPolyRef targetRef;
  dtStatus status = m_naviMeshQuery->findNearestPoly( pos, halfExtents, filter, &targetRef, nullptr );

  if( dtStatusFailed( status ) || targetRef == 0 )
  {
    Logger::error( "PathFinder: Failed to find nearest poly for agent {} destination", agentId );
    return false;
  }

  const dtCrowdAgent *agent = m_crowd->getAgent( agentId );
  if( agent && agent->active )
  {
    m_crowd->requestMoveTarget( agentId, targetRef, pos );
    return true;
  }

  return false;
}

bool PathFinder::resetAgentDestination( int32_t agentId )
{
  if( !m_crowd || !isValidAgentId( agentId ) )
    return false;

  m_crowd->resetMoveTarget( agentId );
  return true;
}

Common::FFXIVARR_POSITION3 PathFinder::getAgentPosition( int32_t agentId )
{
  if( !m_crowd || !isValidAgentId( agentId ) )
    return {};

  const dtCrowdAgent *agent = m_crowd->getAgent( agentId );
  if( !agent )
    return {};

  return fromDetourCoords( agent->npos );
}

bool PathFinder::isAgentActive( int32_t agentId ) const
{
  if( !m_crowd )
    return false;

  const dtCrowdAgent *agent = m_crowd->getAgent( agentId );
  return agent && agent->active;
}

bool PathFinder::hasAgentReachedDestination( int32_t agentId ) const
{
  if( !m_crowd )
    return false;

  const dtCrowdAgent *agent = m_crowd->getAgent( agentId );
  return agent && agent->targetState != DT_CROWDAGENT_TARGET_NONE;
}

bool PathFinder::updateAgentParameters( int32_t agentId, const AgentParameters& params )
{
  if( !m_crowd || !isValidAgentId( agentId ) )
    return false;

  dtCrowdAgentParams crowdParams{};
  std::memset( &crowdParams, 0, sizeof( crowdParams ) );

  crowdParams.height = params.height;
  crowdParams.maxAcceleration = params.maxAcceleration;
  crowdParams.maxSpeed = params.maxSpeed * ( params.isRunning ? 2.0f : 1.0f );
  crowdParams.radius = params.radius * 0.75f;
  crowdParams.collisionQueryRange = crowdParams.radius * 12.0f;
  crowdParams.pathOptimizationRange = crowdParams.radius * 20.0f;
  crowdParams.updateFlags = params.crowdFlags;
  crowdParams.obstacleAvoidanceType = m_obstacleAvoidanceQuality;

  m_crowd->updateAgentParameters( agentId, &crowdParams );
  m_agentParams[ agentId ] = params;
  return true;
}

void PathFinder::updateCrowdSimulation( float deltaTime )
{
  if( !m_crowd )
    return;

  dtCrowdAgentDebugInfo info{};
  info.idx = -1;
  info.vod = m_avoidanceDebug;
  m_crowd->update( deltaTime, &info );
}

void PathFinder::registerDoor( uint32_t doorId, const Common::FFXIVARR_POSITION3& position,
                               const std::vector< dtPolyRef >& connectedPolys )
{
  DoorInfo& door = m_doors[ doorId ];
  door.doorId = doorId;
  door.position = position;
  door.connectedPolys = connectedPolys;
  door.state = DoorState::Closed;
}

void PathFinder::setDoorState( uint32_t doorId, DoorState state )
{
  auto it = m_doors.find( doorId );
  if( it != m_doors.end() )
  {
    it->second.state = state;
  }
}

DoorState PathFinder::getDoorState( uint32_t doorId ) const
{
  auto it = m_doors.find( doorId );
  return it != m_doors.end() ? it->second.state : DoorState::Locked;
}

std::vector< uint32_t > PathFinder::getDoorsNearPosition( const Common::FFXIVARR_POSITION3& position,
                                                          float radius ) const
{
  std::vector< uint32_t > nearbyDoors;

  for( const auto& [ doorId, door ] : m_doors )
  {
    if( calculateDistance( position, door.position ) <= radius )
    {
      nearbyDoors.push_back( doorId );
    }
  }

  return nearbyDoors;
}

void PathFinder::clearAllDoors()
{
  m_doors.clear();
}

void PathFinder::setPathfindingExtents( float x, float y, float z )
{
  m_pathfindingExtents[ 0 ] = x;
  m_pathfindingExtents[ 1 ] = y;
  m_pathfindingExtents[ 2 ] = z;
}

void PathFinder::setObstacleAvoidanceQuality( uint8_t quality )
{
  m_obstacleAvoidanceQuality = std::clamp( quality, static_cast< uint8_t >( 0 ), static_cast< uint8_t >( 3 ) );
}

size_t PathFinder::getActiveAgentCount() const
{
  return m_agentParams.size();
}

// Private methods implementation

bool PathFinder::loadNavMesh( const std::string& path )
{
  FILE *fp = fopen( path.c_str(), "rb" );
  if( !fp )
  {
    Logger::error( "PathFinder: Couldn't open navigation mesh file: {}", path );
    return false;
  }

  NavMeshSetHeader header;
  size_t readLen = fread( &header, sizeof( NavMeshSetHeader ), 1, fp );
  if( readLen != 1 )
  {
    fclose( fp );
    Logger::error( "PathFinder: Couldn't read NavMeshSetHeader for {}", path );
    return false;
  }

  if( header.magic != NAVMESHSET_MAGIC )
  {
    fclose( fp );
    Logger::error( "PathFinder: '{}' has an incorrect NavMeshSet header", path );
    return false;
  }

  if( header.version != NAVMESHSET_VERSION )
  {
    fclose( fp );
    Logger::error( "PathFinder: '{}' has incorrect version. Expected {}, got {}",
                   path, NAVMESHSET_VERSION, header.version );
    return false;
  }

  m_naviMesh = dtAllocNavMesh();
  if( !m_naviMesh )
  {
    fclose( fp );
    Logger::error( "PathFinder: Couldn't allocate dtNavMesh" );
    return false;
  }

  dtStatus status = m_naviMesh->init( &header.params );
  if( dtStatusFailed( status ) )
  {
    fclose( fp );
    Logger::error( "PathFinder: Couldn't initialize dtNavMesh" );
    return false;
  }

  for( int32_t i = 0; i < header.numTiles; ++i )
  {
    NavMeshTileHeader tileHeader;
    readLen = fread( &tileHeader, sizeof( tileHeader ), 1, fp );
    if( readLen != 1 )
    {
      fclose( fp );
      Logger::error( "PathFinder: Couldn't read NavMeshTileHeader from '{}'", path );
      return false;
    }

    if( !tileHeader.tileRef || !tileHeader.dataSize )
      break;

    auto data = reinterpret_cast< uint8_t * >( dtAlloc( tileHeader.dataSize, DT_ALLOC_PERM ) );
    if( !data )
      break;

    memset( data, 0, tileHeader.dataSize );
    readLen = fread( data, tileHeader.dataSize, 1, fp );
    if( readLen != 1 )
    {
      dtFree( data );
      fclose( fp );
      Logger::error( "PathFinder: Couldn't read tile data from '{}'", path );
      return false;
    }

    m_naviMesh->addTile( data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0 );
  }

  fclose( fp );
  return true;
}

void PathFinder::initializeQuery()
{
  if( m_naviMeshQuery )
    dtFreeNavMeshQuery( m_naviMeshQuery );

  m_naviMeshQuery = dtAllocNavMeshQuery();
  m_naviMeshQuery->init( m_naviMesh, 2048 );
}

void PathFinder::initializeCrowd()
{
  m_crowd = std::make_unique< dtCrowd >();

  if( !m_crowd->init( 1000, 10.0f, m_naviMesh ) )
  {
    Logger::error( "PathFinder: Failed to initialize crowd simulation" );
    m_crowd.reset();
    return;
  }

  m_avoidanceDebug = dtAllocObstacleAvoidanceDebugData();
  m_avoidanceDebug->init( 2048 );
}

void PathFinder::setupObstacleAvoidanceParams()
{
  if( !m_crowd )
    return;

  dtObstacleAvoidanceParams params;

  // Low quality (0)
  memcpy( &params, m_crowd->getObstacleAvoidanceParams( 0 ), sizeof( dtObstacleAvoidanceParams ) );
  params.velBias = 0.5f;
  params.adaptiveDivs = 5;
  params.adaptiveRings = 2;
  params.adaptiveDepth = 1;
  m_crowd->setObstacleAvoidanceParams( 0, &params );

  // Medium quality (1)
  params.adaptiveDepth = 2;
  m_crowd->setObstacleAvoidanceParams( 1, &params );

  // High quality (2)
  params.adaptiveDivs = 7;
  params.adaptiveDepth = 3;
  m_crowd->setObstacleAvoidanceParams( 2, &params );

  // Ultra quality (3)
  params.adaptiveRings = 3;
  m_crowd->setObstacleAvoidanceParams( 3, &params );
}

std::optional< dtPolyRef > PathFinder::findNearestPoly( const Common::FFXIVARR_POSITION3& position,
                                                        const float *extents )
{
  if( !m_naviMeshQuery )
    return std::nullopt;

  float pos[ 3 ];
  toDetourCoords( position, pos );

  const float *searchExtents = extents ? extents : m_pathfindingExtents;

  dtQueryFilter filter;
  filter.setIncludeFlags( 0xffff );
  filter.setExcludeFlags( 0 );

  dtPolyRef nearestRef;
  dtStatus status = m_naviMeshQuery->findNearestPoly( pos, searchExtents, &filter, &nearestRef, nullptr );

  if( dtStatusFailed( status ) || nearestRef == 0 )
    return std::nullopt;

  return nearestRef;
}

bool PathFinder::getSteerTarget( const float *startPos, const float *endPos, const float minTargetDist,
                                 const dtPolyRef *path, int32_t pathSize, float *steerPos,
                                 uint8_t& steerPosFlag, dtPolyRef& steerPosRef )
{
  const int32_t MAX_STEER_POINTS = 3;
  float steerPath[ MAX_STEER_POINTS * 3 ];
  uint8_t steerPathFlags[ MAX_STEER_POINTS ];
  dtPolyRef steerPathPolys[ MAX_STEER_POINTS ];
  int32_t nsteerPath = 0;

  m_naviMeshQuery->findStraightPath( startPos, endPos, path, pathSize,
                                     steerPath, steerPathFlags, steerPathPolys, &nsteerPath, MAX_STEER_POINTS );

  if( !nsteerPath )
    return false;

  int32_t ns = 0;
  while( ns < nsteerPath )
  {
    if( ( steerPathFlags[ ns ] & DT_STRAIGHTPATH_OFFMESH_CONNECTION ) ||
        !inRange( &steerPath[ ns * 3 ], startPos, minTargetDist, 1000.0f ) )
      break;
    ns++;
  }

  if( ns >= nsteerPath )
    return false;

  dtVcopy( steerPos, &steerPath[ ns * 3 ] );
  steerPos[ 1 ] = startPos[ 1 ];
  steerPosFlag = steerPathFlags[ ns ];
  steerPosRef = steerPathPolys[ ns ];

  return true;
}

int32_t PathFinder::fixupCorridor( dtPolyRef *path, int32_t npath, int32_t maxPath,
                                   const dtPolyRef *visited, int32_t nvisited )
{
  int32_t furthestPath = -1;
  int32_t furthestVisited = -1;

  for( int32_t i = npath - 1; i >= 0; --i )
  {
    bool found = false;
    for( int32_t j = nvisited - 1; j >= 0; --j )
    {
      if( path[ i ] == visited[ j ] )
      {
        furthestPath = i;
        furthestVisited = j;
        found = true;
      }
    }
    if( found )
      break;
  }

  if( furthestPath == -1 || furthestVisited == -1 )
    return npath;

  const int32_t req = nvisited - furthestVisited;
  const int32_t orig = rcMin( furthestPath + 1, npath );
  int32_t size = rcMax( 0, npath - orig );

  if( req + size > maxPath )
    size = maxPath - req;

  if( size )
    memmove( path + req, path + orig, size * sizeof( dtPolyRef ) );

  for( int32_t i = 0; i < req; ++i )
    path[ i ] = visited[ ( nvisited - 1 ) - i ];

  return req + size;
}

int32_t PathFinder::fixupShortcuts( dtPolyRef *path, int32_t npath )
{
  if( npath < 3 )
    return npath;

  const int32_t maxNeis = 16;
  dtPolyRef neis[ maxNeis ];
  int32_t nneis = 0;

  const dtMeshTile *tile = nullptr;
  const dtPoly *poly = nullptr;

  if( dtStatusFailed( m_naviMeshQuery->getAttachedNavMesh()->getTileAndPolyByRef( path[ 0 ], &tile, &poly ) ) )
    return npath;

  for( uint32_t k = poly->firstLink; k != DT_NULL_LINK; k = tile->links[ k ].next )
  {
    const dtLink *link = &tile->links[ k ];
    if( link->ref != 0 && nneis < maxNeis )
      neis[ nneis++ ] = link->ref;
  }

  const int32_t maxLookAhead = 6;
  int32_t cut = 0;

  for( int32_t i = dtMin( maxLookAhead, npath ) - 1; i > 1 && cut == 0; i-- )
  {
    for( int32_t j = 0; j < nneis; j++ )
    {
      if( path[ i ] == neis[ j ] )
      {
        cut = i;
        break;
      }
    }
  }

  if( cut > 1 )
  {
    int32_t offset = cut - 1;
    npath -= offset;
    for( int32_t i = 1; i < npath; i++ )
      path[ i ] = path[ i + offset ];
  }

  return npath;
}

bool PathFinder::inRange( const float *v1, const float *v2, float r, float h ) const
{
  const float dx = v2[ 0 ] - v1[ 0 ];
  const float dy = v2[ 1 ] - v1[ 1 ];
  const float dz = v2[ 2 ] - v1[ 2 ];
  return ( dx * dx + dz * dz ) < r * r && fabsf( dy ) < h;
}

bool PathFinder::isDoorAccessible( uint32_t doorId, const std::function< bool( uint32_t ) >& accessCheck ) const
{
  auto it = m_doors.find( doorId );
  if( it == m_doors.end() )
    return false;

  const DoorInfo& door = it->second;

  // Check door state
  if( door.state == DoorState::Locked )
    return false;
  if( door.state == DoorState::Open )
    return true;

  // If door is closed, check if player has access
  return accessCheck ? accessCheck( doorId ) : false;
}

std::vector< uint32_t > PathFinder::findRequiredDoorsForPath( const dtPolyRef *polys, int32_t polyCount ) const
{
  std::vector< uint32_t > requiredDoors;

  // Check each polygon in the path against registered doors
  for( int32_t i = 0; i < polyCount; ++i )
  {
    for( const auto& [ doorId, door ] : m_doors )
    {
      // Check if this polygon is connected to a door
      for( dtPolyRef connectedPoly : door.connectedPolys )
      {
        if( polys[ i ] == connectedPoly )
        {
          // Add door if not already in list
          if( std::find( requiredDoors.begin(), requiredDoors.end(), doorId ) == requiredDoors.end() )
          {
            requiredDoors.push_back( doorId );
          }
          break;
        }
      }
    }
  }

  return requiredDoors;
}

void PathFinder::toDetourCoords( const Common::FFXIVARR_POSITION3& position, float *out ) const
{
  out[ 0 ] = position.x;
  out[ 1 ] = position.y;
  out[ 2 ] = position.z;
}

Common::FFXIVARR_POSITION3 PathFinder::fromDetourCoords( const float *coords ) const
{
  return { coords[ 0 ], coords[ 1 ], coords[ 2 ] };
}

bool PathFinder::isValidAgentId( int32_t agentId ) const
{
  return m_agentParams.find( agentId ) != m_agentParams.end();
}
