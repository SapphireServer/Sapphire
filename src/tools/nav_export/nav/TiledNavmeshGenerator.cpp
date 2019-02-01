#include "TiledNavmeshGenerator.h"

#include <experimental/filesystem>
#include <cstring>

#include <recastnavigation/Detour/Include/DetourNavMeshBuilder.h>

namespace fs = std::experimental::filesystem;


inline unsigned int nextPow2( uint32_t v )
{
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

inline unsigned int ilog2( uint32_t v )
{
  uint32_t r;
  uint32_t shift;
  r = (v > 0xffff) << 4; v >>= r;
  shift = (v > 0xff) << 3; v >>= shift; r |= shift;
  shift = (v > 0xf) << 2; v >>= shift; r |= shift;
  shift = (v > 0x3) << 1; v >>= shift; r |= shift;
  r |= (v >> 1);
  return r;
}

bool TiledNavmeshGenerator::init( const std::string& path )
{
  if( !fs::exists( path ) )
    throw std::runtime_error( "what" );

  // ignore logging/bullshit/etc
  m_ctx = new rcContext( false );

  printf( "[Navmesh] loading obj: %s\n", path.substr( path.find( "pcb_export" ) - 1 ).c_str() );

  m_mesh = new rcMeshLoaderObj;
  assert( m_mesh );

  if( !m_mesh->load( path ) )
  {
    printf( "[Navmesh] Failed to allocate rcMeshLoaderObj\n" );
    return false;
  }

  rcCalcBounds( m_mesh->getVerts(), m_mesh->getVertCount(), m_meshBMin, m_meshBMax );

  m_chunkyMesh = new rcChunkyTriMesh;
  assert( m_chunkyMesh );

  if( !rcCreateChunkyTriMesh( m_mesh->getVerts(), m_mesh->getTris(), m_mesh->getTriCount(), 256, m_chunkyMesh ) )
  {
    printf( "[Navmesh] buildTiledNavigation: Failed to build chunky mesh.\n" );
    return false;
  }

  // todo: load some bullshit settings from exd

  int gw = 0, gh = 0;
  rcCalcGridSize( m_meshBMin, m_meshBMax, m_cellSize, &gw, &gh );

  auto ts = static_cast< uint32_t >( m_tileSize );
  const uint32_t tw = ( gw + ts - 1 ) / ts;
  const uint32_t th = ( gh + ts - 1 ) / ts;

  printf( "[Navmesh]  - Tiles %d x %d\n", tw, th );

  int tileBits = rcMin( ( int ) ilog2( nextPow2( tw * th ) ), 14 );
  if( tileBits > 14 )
    tileBits = 14;
  int polyBits = 22 - tileBits;
  m_maxTiles = 1 << tileBits;
  m_maxPolysPerTile = 1 << polyBits;

  printf( "[Navmesh]  - %.1fK verts, %.1fK tris\n", m_mesh->getVertCount() / 1000.0f, m_mesh->getTriCount() / 1000.0f );

  return true;
}

TiledNavmeshGenerator::~TiledNavmeshGenerator()
{
  delete m_mesh;
  delete m_chunkyMesh;

  if( m_triareas )
    delete[] m_triareas;
  delete m_ctx;

  rcFreeContourSet( m_cset );
  rcFreeHeightField( m_solid );
  rcFreeCompactHeightfield(m_chf);
  rcFreePolyMesh( m_pmesh );
  rcFreePolyMeshDetail( m_dmesh );
  dtFreeNavMesh( m_navMesh );
}

void TiledNavmeshGenerator::saveNavmesh( const std::string& name )
{
  assert( m_navMesh );

  // fuck this gay earth
  auto mesh = const_cast< const dtNavMesh* >( m_navMesh );

  auto dir = fs::current_path().string() + "/pcb_export/" + name + "/";
  auto fileName = dir + name + ".nav";

  fs::create_directories( dir );

  FILE* fp = fopen( fileName.c_str(), "wb" );
  if( !fp )
    return;

  // Store header.
  NavMeshSetHeader header;
  header.magic = NAVMESHSET_MAGIC;
  header.version = NAVMESHSET_VERSION;
  header.numTiles = 0;
  for( int i = 0; i < mesh->getMaxTiles(); ++i )
  {
    auto tile = mesh->getTile( i );
    if( !tile || !tile->header || !tile->dataSize )
      continue;

    header.numTiles++;
  }

  memcpy( &header.params, mesh->getParams(), sizeof( dtNavMeshParams ) );
  fwrite( &header, sizeof( NavMeshSetHeader ), 1, fp );

  // Store tiles.
  for( int i = 0; i < mesh->getMaxTiles(); ++i )
  {
    auto tile = mesh->getTile( i );
    if( !tile || !tile->header || !tile->dataSize )
      continue;

    NavMeshTileHeader tileHeader;
    tileHeader.tileRef = mesh->getTileRef( tile );
    tileHeader.dataSize = tile->dataSize;
    fwrite( &tileHeader, sizeof( tileHeader ), 1, fp );

    fwrite( tile->data, tile->dataSize, 1, fp );
  }

  fclose( fp );

  auto pos = fileName.find( "pcb_export" );
  fileName = fileName.substr( pos - 1 );

  printf( "[Navmesh] Saved navmesh to '%s'\n", fileName.c_str() );
}

bool TiledNavmeshGenerator::buildNavmesh()
{
  assert( m_mesh );

  m_navMesh = dtAllocNavMesh();
  if( !m_navMesh )
  {
    printf( "[Navmesh] buildTiledNavigation: Could not allocate navmesh.\n" );
    return false;
  }

  dtNavMeshParams params{};
  rcVcopy( params.orig, m_meshBMin );
  params.tileWidth = m_tileSize * m_cellSize;
  params.tileHeight = m_tileSize * m_cellSize;
  params.maxTiles = m_maxTiles;
  params.maxPolys = m_maxPolysPerTile;

  dtStatus status;

  status = m_navMesh->init( &params );
  if( dtStatusFailed( status ) )
  {
    printf( "[Navmesh] buildTiledNavigation: Could not init navmesh.\n" );
    return false;
  }

  // todo: duplicated from above, we can probably cache all this and only do it once
  int gw = 0, gh = 0;
  rcCalcGridSize( m_meshBMin, m_meshBMax, m_cellSize, &gw, &gh );
  auto ts = static_cast< uint32_t >( m_tileSize );
  const int tw = ( gw + ts - 1 ) / ts;
  const int th = ( gh + ts - 1 ) / ts;
  const float tcs = m_tileSize * m_cellSize;

  for( int y = 0; y < th; y++ )
  {
    for( int x = 0; x < tw; x++ )
    {
      m_lastBuiltTileBmin[ 0 ] = m_meshBMin[ 0 ] + x * tcs;
      m_lastBuiltTileBmin[ 1 ] = m_meshBMin[ 1 ];
      m_lastBuiltTileBmin[ 2 ] = m_meshBMin[ 2 ] + y * tcs;

      m_lastBuiltTileBmax[ 0 ] = m_meshBMin[ 0 ] + ( x + 1 ) * tcs;
      m_lastBuiltTileBmax[ 1 ] = m_meshBMax[ 1 ];
      m_lastBuiltTileBmax[ 2 ] = m_meshBMin[ 2 ] + ( y + 1 ) * tcs;

      int dataSize = 0;

      unsigned char* data = buildTileMesh( x, y, m_lastBuiltTileBmin, m_lastBuiltTileBmax, dataSize );
      if( data )
      {
        // Remove any previous data (navmesh owns and deletes the data).
        m_navMesh->removeTile( m_navMesh->getTileRefAt( x, y, 0 ), nullptr, nullptr );

        // Let the navmesh own the data.
        status = m_navMesh->addTile( data, dataSize, DT_TILE_FREE_DATA, 0, nullptr );

        if( dtStatusFailed( status ) )
        {
          dtFree( data );
        }
      }
    }
  }

  return true;
}


unsigned char* TiledNavmeshGenerator::buildTileMesh( const int tx, const int ty, const float* bmin, const float* bmax,
                                                     int& dataSize )
{
  const float* verts = m_mesh->getVerts();
  const int nverts = m_mesh->getVertCount();
  const int ntris = m_mesh->getTriCount();

  // Init build configuration from GUI
  memset( &m_cfg, 0, sizeof( m_cfg ) );
  m_cfg.cs = m_cellSize;
  m_cfg.ch = m_cellHeight;
  m_cfg.walkableSlopeAngle = m_agentMaxSlope;
  m_cfg.walkableHeight = static_cast< int >( ceilf( m_agentHeight / m_cfg.ch ) );
  m_cfg.walkableClimb = static_cast< int >( floorf( m_agentMaxClimb / m_cfg.ch ) );
  m_cfg.walkableRadius = static_cast< int >( ceilf( m_agentRadius / m_cfg.cs ) );
  m_cfg.maxEdgeLen = static_cast< int >( m_edgeMaxLen / m_cellSize );
  m_cfg.maxSimplificationError = m_edgeMaxError;
  m_cfg.minRegionArea = static_cast< int >( rcSqr( m_regionMinSize ) ); // Note: area = size*size
  m_cfg.mergeRegionArea = static_cast< int >( rcSqr( m_regionMergeSize ) ); // Note: area = size*size
  m_cfg.maxVertsPerPoly = static_cast< int >( m_vertsPerPoly );
  m_cfg.tileSize = static_cast< int >( m_tileSize );
  m_cfg.borderSize = m_cfg.walkableRadius + 3; // Reserve enough padding.
  m_cfg.width = m_cfg.tileSize + m_cfg.borderSize * 2;
  m_cfg.height = m_cfg.tileSize + m_cfg.borderSize * 2;
  m_cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
  m_cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;

  // Expand the heighfield bounding box by border size to find the extents of geometry we need to build this tile.
  //
  // This is done in order to make sure that the navmesh tiles connect correctly at the borders,
  // and the obstacles close to the border work correctly with the dilation process.
  // No polygons (or contours) will be created on the border area.
  //
  // IMPORTANT!
  //
  //   :''''''''':
  //   : +-----+ :
  //   : |     | :
  //   : |     |<--- tile to build
  //   : |     | :
  //   : +-----+ :<-- geometry needed
  //   :.........:
  //
  // You should use this bounding box to query your input geometry.
  //
  // For example if you build a navmesh for terrain, and want the navmesh tiles to match the terrain tile size
  // you will need to pass in data from neighbour terrain tiles too! In a simple case, just pass in all the 8 neighbours,
  // or use the bounding box below to only pass in a sliver of each of the 8 neighbours.
  rcVcopy( m_cfg.bmin, bmin );
  rcVcopy( m_cfg.bmax, bmax );
  m_cfg.bmin[ 0 ] -= m_cfg.borderSize * m_cfg.cs;
  m_cfg.bmin[ 2 ] -= m_cfg.borderSize * m_cfg.cs;
  m_cfg.bmax[ 0 ] += m_cfg.borderSize * m_cfg.cs;
  m_cfg.bmax[ 2 ] += m_cfg.borderSize * m_cfg.cs;

  m_solid = rcAllocHeightfield();
  if( !m_solid )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'solid'.\n" );
    return nullptr;
  }

  if( !rcCreateHeightfield( m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch ) )
  {
    printf( "[Navmesh] buildNavigation: Could not create solid heightfield.\n" );
    return nullptr;
  }

  // Allocate array that can hold triangle flags.
  // If you have multiple meshes you need to process, allocate
  // and array which can hold the max number of triangles you need to process.
  m_triareas = new unsigned char[ m_chunkyMesh->maxTrisPerChunk ];
  if( !m_triareas )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'm_triareas' (%d).\n", m_chunkyMesh->maxTrisPerChunk );
    return nullptr;
  }

  float tbmin[ 2 ];
  float tbmax[ 2 ];
  tbmin[ 0 ] = m_cfg.bmin[ 0 ];
  tbmin[ 1 ] = m_cfg.bmin[ 2 ];
  tbmax[ 0 ] = m_cfg.bmax[ 0 ];
  tbmax[ 1 ] = m_cfg.bmax[ 2 ];

  int cid[512];// TODO: Make grow when returning too many items.
  const int ncid = rcGetChunksOverlappingRect( m_chunkyMesh, tbmin, tbmax, cid, 512 );

  if( !ncid )
    return nullptr;

  m_tileTriCount = 0;

  for( int i = 0; i < ncid; ++i )
  {
    const rcChunkyTriMeshNode& node = m_chunkyMesh->nodes[ cid[ i ] ];
    const int* ctris = &m_chunkyMesh->tris[ node.i * 3 ];
    const int nctris = node.n;

    m_tileTriCount += nctris;

    memset( m_triareas, 0, nctris * sizeof( unsigned char ) );
    rcMarkWalkableTriangles( m_ctx, m_cfg.walkableSlopeAngle, verts, nverts, ctris, nctris, m_triareas );
    if( !rcRasterizeTriangles( m_ctx, verts, nverts, ctris, m_triareas, nctris, *m_solid, m_cfg.walkableClimb ) )
      return nullptr;
  }

  delete[] m_triareas;
  m_triareas = nullptr;

  // Once all geometry is rasterized, we do initial pass of filtering to
  // remove unwanted overhangs caused by the conservative rasterization
  // as well as filter spans where the character cannot possibly stand.
  rcFilterLowHangingWalkableObstacles( m_ctx, m_cfg.walkableClimb, *m_solid );
  rcFilterLedgeSpans( m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid );
  rcFilterWalkableLowHeightSpans( m_ctx, m_cfg.walkableHeight, *m_solid );

  // Compact the heightfield so that it is faster to handle from now on.
  // This will result more cache coherent data as well as the neighbours
  // between walkable cells will be calculated.
  m_chf = rcAllocCompactHeightfield();
  if( !m_chf )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'chf'." );
    return nullptr;
  }
  if( !rcBuildCompactHeightfield( m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf ) )
  {
    printf( "[Navmesh] buildNavigation: Could not build compact data." );
    return nullptr;
  }

  rcFreeHeightField( m_solid );
  m_solid = nullptr;

  // Erode the walkable area by agent radius.
  if( !rcErodeWalkableArea( m_ctx, m_cfg.walkableRadius, *m_chf ) )
  {
    printf( "[Navmesh] buildNavigation: Could not erode." );
    return nullptr;
  }

  // (Optional) Mark areas.
//  const ConvexVolume* vols = m_mesh->getConvexVolumes();
//  for (int i  = 0; i < m_geom->getConvexVolumeCount(); ++i)
//    rcMarkConvexPolyArea(m_ctx, vols[i].verts, vols[i].nverts, vols[i].hmin, vols[i].hmax, (unsigned char)vols[i].area, *m_chf);

  // Partition the heightfield so that we can use simple algorithm later to triangulate the walkable areas.
  // There are 3 martitioning methods, each with some pros and cons:
  // 1) Watershed partitioning
  //   - the classic Recast partitioning
  //   - creates the nicest tessellation
  //   - usually slowest
  //   - partitions the heightfield into nice regions without holes or overlaps
  //   - the are some corner cases where this method creates produces holes and overlaps
  //      - holes may appear when a small obstacles is close to large open area (triangulation can handle this)
  //      - overlaps may occur if you have narrow spiral corridors (i.e stairs), this make triangulation to fail
  //   * generally the best choice if you precompute the nacmesh, use this if you have large open areas
  // 2) Monotone partioning
  //   - fastest
  //   - partitions the heightfield into regions without holes and overlaps (guaranteed)
  //   - creates long thin polygons, which sometimes causes paths with detours
  //   * use this if you want fast navmesh generation
  // 3) Layer partitoining
  //   - quite fast
  //   - partitions the heighfield into non-overlapping regions
  //   - relies on the triangulation code to cope with holes (thus slower than monotone partitioning)
  //   - produces better triangles than monotone partitioning
  //   - does not have the corner cases of watershed partitioning
  //   - can be slow and create a bit ugly tessellation (still better than monotone)
  //     if you have large open areas with small obstacles (not a problem if you use tiles)
  //   * good choice to use for tiled navmesh with medium and small sized tiles

  if( m_partitionType == SAMPLE_PARTITION_WATERSHED )
  {
    // Prepare for region partitioning, by calculating distance field along the walkable surface.
    if( !rcBuildDistanceField( m_ctx, *m_chf ) )
    {
      printf( "[Navmesh] buildNavigation: Could not build distance field." );
      return nullptr;
    }

    // Partition the walkable surface into simple regions without holes.
    if( !rcBuildRegions( m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea ) )
    {
      printf( "[Navmesh] buildNavigation: Could not build watershed regions." );
      return nullptr;
    }
  }
  else if( m_partitionType == SAMPLE_PARTITION_MONOTONE )
  {
    // Partition the walkable surface into simple regions without holes.
    // Monotone partitioning does not need distancefield.
    if( !rcBuildRegionsMonotone( m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea ) )
    {
      printf( "[Navmesh] buildNavigation: Could not build monotone regions." );
      return nullptr;
    }
  }
  else // SAMPLE_PARTITION_LAYERS
  {
    // Partition the walkable surface into simple regions without holes.
    if( !rcBuildLayerRegions( m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea ) )
    {
      printf( "[Navmesh] buildNavigation: Could not build layer regions." );
      return nullptr;
    }
  }

  // Create contours.
  m_cset = rcAllocContourSet();
  if( !m_cset )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'cset'." );
    return nullptr;
  }
  if( !rcBuildContours( m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset ) )
  {
    printf( "[Navmesh] buildNavigation: Could not create contours." );
    return nullptr;
  }

  if( m_cset->nconts == 0 )
  {
    return nullptr;
  }

  // Build polygon navmesh from the contours.
  m_pmesh = rcAllocPolyMesh();
  if( !m_pmesh )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'pmesh'." );
    return nullptr;
  }
  if( !rcBuildPolyMesh( m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh ) )
  {
    printf( "[Navmesh] buildNavigation: Could not triangulate contours." );
    return nullptr;
  }

  // Build detail mesh.
  m_dmesh = rcAllocPolyMeshDetail();
  if( !m_dmesh )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'dmesh'." );
    return nullptr;
  }

  if( !rcBuildPolyMeshDetail( m_ctx, *m_pmesh, *m_chf,
                              m_cfg.detailSampleDist, m_cfg.detailSampleMaxError,
                              *m_dmesh ) )
  {
    printf( "[Navmesh] buildNavigation: Could build polymesh detail." );
    return nullptr;
  }

  rcFreeCompactHeightfield( m_chf );
  rcFreeContourSet( m_cset );
  m_chf = nullptr;
  m_cset = nullptr;

  unsigned char* navData = 0;
  int navDataSize = 0;
  if( m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON )
  {
    if( m_pmesh->nverts >= 0xffff )
    {
      // The vertex indices are ushorts, and cannot point to more than 0xffff vertices.
      printf( "[Navmesh] Too many vertices per tile %d (max: %d).", m_pmesh->nverts, 0xffff );
      return nullptr;
    }

    // Update poly flags from areas.
    for( int i = 0; i < m_pmesh->npolys; ++i )
    {
      if( m_pmesh->areas[ i ] == RC_WALKABLE_AREA )
        m_pmesh->areas[ i ] = SAMPLE_POLYAREA_GROUND;

      if( m_pmesh->areas[ i ] == SAMPLE_POLYAREA_GROUND ||
          m_pmesh->areas[ i ] == SAMPLE_POLYAREA_GRASS ||
          m_pmesh->areas[ i ] == SAMPLE_POLYAREA_ROAD )
      {
        m_pmesh->flags[ i ] = SAMPLE_POLYFLAGS_WALK;
      }
      else if( m_pmesh->areas[ i ] == SAMPLE_POLYAREA_WATER )
      {
        m_pmesh->flags[ i ] = SAMPLE_POLYFLAGS_SWIM;
      }
      else if( m_pmesh->areas[ i ] == SAMPLE_POLYAREA_DOOR )
      {
        m_pmesh->flags[ i ] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
      }
    }

    dtNavMeshCreateParams params;
    memset( &params, 0, sizeof( params ) );
    params.verts = m_pmesh->verts;
    params.vertCount = m_pmesh->nverts;
    params.polys = m_pmesh->polys;
    params.polyAreas = m_pmesh->areas;
    params.polyFlags = m_pmesh->flags;
    params.polyCount = m_pmesh->npolys;
    params.nvp = m_pmesh->nvp;
    params.detailMeshes = m_dmesh->meshes;
    params.detailVerts = m_dmesh->verts;
    params.detailVertsCount = m_dmesh->nverts;
    params.detailTris = m_dmesh->tris;
    params.detailTriCount = m_dmesh->ntris;

    params.offMeshConVerts = nullptr;
    params.offMeshConRad = nullptr;
    params.offMeshConDir = nullptr;
    params.offMeshConAreas = nullptr;
    params.offMeshConFlags = nullptr;
    params.offMeshConUserID = nullptr;
    params.offMeshConCount = 0;

    params.walkableHeight = m_agentHeight;
    params.walkableRadius = m_agentRadius;
    params.walkableClimb = m_agentMaxClimb;
    params.tileX = tx;
    params.tileY = ty;
    params.tileLayer = 0;
    rcVcopy( params.bmin, m_pmesh->bmin );
    rcVcopy( params.bmax, m_pmesh->bmax );
    params.cs = m_cfg.cs;
    params.ch = m_cfg.ch;
    params.buildBvTree = true;

    if( !dtCreateNavMeshData( &params, &navData, &navDataSize ) )
    {
      printf( "[Navmesh] Could not build Detour navmesh." );
      return nullptr;
    }
  }

  rcFreePolyMesh( m_pmesh );
  rcFreePolyMeshDetail( m_dmesh );
  m_pmesh = nullptr;
  m_dmesh = nullptr;

  dataSize = navDataSize;
  return navData;
}
