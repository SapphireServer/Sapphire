#include "TiledNavmeshGenerator.h"

#include <filesystem>
#include <cstring>

#include <recastnavigation/Detour/Include/DetourNavMeshBuilder.h>
#include <recastnavigation/RecastDemo/Source/InputGeom.cpp>
#include <recastnavigation/DebugUtils/Source/DebugDraw.cpp>

namespace fs = std::filesystem;


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

void MeshProcess::process( struct dtNavMeshCreateParams* params,
                      unsigned char* polyAreas, unsigned short* polyFlags )
{
  // Update poly flags from areas.
  for( int i = 0; i < params->polyCount; ++i )
  {
    if( polyAreas[ i ] == DT_TILECACHE_WALKABLE_AREA )
      polyAreas[ i ] = SAMPLE_POLYAREA_GROUND;

    if( polyAreas[ i ] == SAMPLE_POLYAREA_GROUND ||
        polyAreas[ i ] == SAMPLE_POLYAREA_GRASS ||
        polyAreas[ i ] == SAMPLE_POLYAREA_ROAD )
    {
      polyFlags[ i ] = SAMPLE_POLYFLAGS_WALK;
    }
    else if( polyAreas[ i ] == SAMPLE_POLYAREA_WATER )
    {
      polyFlags[ i ] = SAMPLE_POLYFLAGS_SWIM;
    }
    else if( polyAreas[ i ] == SAMPLE_POLYAREA_DOOR )
    {
      polyFlags[ i ] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
    }
  }

  // Pass in off-mesh connections.
  if( m_geom )
  {
    params->offMeshConVerts = m_geom->getOffMeshConnectionVerts();
    params->offMeshConRad = m_geom->getOffMeshConnectionRads();
    params->offMeshConDir = m_geom->getOffMeshConnectionDirs();
    params->offMeshConAreas = m_geom->getOffMeshConnectionAreas();
    params->offMeshConFlags = m_geom->getOffMeshConnectionFlags();
    params->offMeshConUserID = m_geom->getOffMeshConnectionId();
    params->offMeshConCount = m_geom->getOffMeshConnectionCount();
  }
}

bool TiledNavmeshGenerator::init( const std::string& path )
{
  if( !fs::exists( path ) )
    throw std::runtime_error( "what" );

  // ignore logging/bullshit/etc
  m_ctx = new rcContext( false );

  printf( "[Navmesh] loading obj: %s\n", path.substr( path.find( "navi" ) ).c_str() );

  m_geom = new InputGeom();
  if( !m_geom || !m_geom->load( m_ctx, path ) )
  {
    printf( "[Navmesh] Failed to allocate InputGeom\n" );
    return false;
  }

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

 // printf( "[Navmesh]  - Tiles %d x %d\n", tw, th );

  int tileBits = rcMin( ( int ) ilog2( nextPow2( tw * th ) ), 14 );
  if( tileBits > 14 )
    tileBits = 14;
  int polyBits = 22 - tileBits;
  m_maxTiles = 1 << tileBits;
  m_maxPolysPerTile = 1 << polyBits;

  m_tAllocator = new LinearAllocator( 32000 );
  m_tCompressor = new FastLZCompressor();
  m_tMeshProcess = new MeshProcess();

  //  printf( "[Navmesh]  - %.1fK verts, %.1fK tris\n", m_mesh->getVertCount() / 1000.0f, m_mesh->getTriCount() / 1000.0f );

  return true;
}

TiledNavmeshGenerator::~TiledNavmeshGenerator()
{
  if( m_mesh )
    delete m_mesh;

  if( m_chunkyMesh)
    delete m_chunkyMesh;

  if( m_triareas )
    delete[] m_triareas;
  if( m_ctx )
    delete m_ctx;

  if( m_tAllocator )
    delete m_tAllocator;
  if( m_tCompressor )
    delete m_tCompressor;
  if( m_tMeshProcess )
    delete m_tMeshProcess;
  if( m_geom )
    delete m_geom;

  if( m_cset )
    rcFreeContourSet( m_cset );
  if( m_solid )
    rcFreeHeightField( m_solid );
  if( m_chf )
    rcFreeCompactHeightfield(m_chf);
  if( m_pmesh )
    rcFreePolyMesh( m_pmesh );
  if( m_dmesh )
    rcFreePolyMeshDetail( m_dmesh );
  if( m_navMesh )
    dtFreeNavMesh( m_navMesh );
  if( m_tileCache )
    dtFreeTileCache( m_tileCache );
}

void TiledNavmeshGenerator::saveNavmesh( const std::string& name )
{
  assert( m_navMesh );

  // fuck this gay earth
  auto mesh = const_cast< const dtNavMesh* >( m_navMesh );
  auto tileCache = const_cast< const dtTileCache* >( m_tileCache );

  auto dir = fs::current_path() / "navi" / name;
  auto fileName = dir / ( name + ".nav" );

  fs::create_directories( dir );

  FILE* fp = fopen( fileName.string().c_str(), "wb" );
  if( !fp )
    return;

	// Store header.
  TileCacheSetHeader header;
  header.magic = TILECACHESET_MAGIC;
  header.version = TILECACHESET_VERSION;
  header.numTiles = 0;
  for( int i = 0; i < m_tileCache->getTileCount(); ++i )
  {
    const dtCompressedTile* tile = m_tileCache->getTile( i );
    if( !tile || !tile->header || !tile->dataSize ) continue;
    header.numTiles++;
  }

  memcpy( &header.cacheParams, m_tileCache->getParams(), sizeof( dtTileCacheParams ) );
  memcpy( &header.meshParams, m_navMesh->getParams(), sizeof( dtNavMeshParams ) );
  fwrite( &header, sizeof( TileCacheSetHeader ), 1, fp );

  // Store tiles.
  for( int i = 0; i < m_tileCache->getTileCount(); ++i )
  {
    const dtCompressedTile* tile = m_tileCache->getTile( i );
    if( !tile || !tile->header || !tile->dataSize ) continue;

    TileCacheTileHeader tileHeader;
    tileHeader.tileRef = m_tileCache->getTileRef( tile );
    tileHeader.dataSize = tile->dataSize;
    fwrite( &tileHeader, sizeof( tileHeader ), 1, fp );

    fwrite( tile->data, tile->dataSize, 1, fp );
  }

  fclose( fp );
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

int TiledNavmeshGenerator::rasterizeTileLayers(
        const int tx, const int ty,
        const rcConfig& cfg,
        TileCacheData* tiles,
        const int maxTiles )
{
  if( !m_geom )
  {
    printf( "[Navmesh] buildTile: Input mesh is not specified." );
    return 0;
  }

  FastLZCompressor comp;
  RasterizationContext rc;

  const float* verts = m_geom->getMesh()->getVerts();
  const int nverts = m_geom->getMesh()->getVertCount();
  const rcChunkyTriMesh* chunkyMesh = m_geom->getChunkyMesh();
  
  // Tile bounds.
  const float tcs = cfg.tileSize * cfg.cs;

  rcConfig tcfg;
  memcpy( &tcfg, &cfg, sizeof( tcfg ) );

  tcfg.bmin[ 0 ] = cfg.bmin[ 0 ] + tx * tcs;
  tcfg.bmin[ 1 ] = cfg.bmin[ 1 ];
  tcfg.bmin[ 2 ] = cfg.bmin[ 2 ] + ty * tcs;
  tcfg.bmax[ 0 ] = cfg.bmin[ 0 ] + ( tx + 1 ) * tcs;
  tcfg.bmax[ 1 ] = cfg.bmax[ 1 ];
  tcfg.bmax[ 2 ] = cfg.bmin[ 2 ] + ( ty + 1 ) * tcs;
  tcfg.bmin[ 0 ] -= tcfg.borderSize * tcfg.cs;
  tcfg.bmin[ 2 ] -= tcfg.borderSize * tcfg.cs;
  tcfg.bmax[ 0 ] += tcfg.borderSize * tcfg.cs;
  tcfg.bmax[ 2 ] += tcfg.borderSize * tcfg.cs;

  // Allocate voxel heightfield where we rasterize our input data to.
  rc.solid = rcAllocHeightfield();
  if( !rc.solid )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'solid'." );
    return 0;
  }
  if( !rcCreateHeightfield( m_ctx, *rc.solid, tcfg.width, tcfg.height, tcfg.bmin, tcfg.bmax, tcfg.cs, tcfg.ch ) )
  {
    printf( "[Navmesh] buildNavigation: Could not create solid heightfield." );
    return 0;
  }

  // Allocate array that can hold triangle flags.
  // If you have multiple meshes you need to process, allocate
  // and array which can hold the max number of triangles you need to process.
  rc.triAreas = new unsigned char[ chunkyMesh->maxTrisPerChunk ];
  if( !rc.triAreas )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'm_triareas' (%d).", chunkyMesh->maxTrisPerChunk );
    return 0;
  }

  float tbmin[ 2 ], tbmax[ 2 ];
  tbmin[ 0 ] = tcfg.bmin[ 0 ];
  tbmin[ 1 ] = tcfg.bmin[ 2 ];
  tbmax[ 0 ] = tcfg.bmax[ 0 ];
  tbmax[ 1 ] = tcfg.bmax[ 2 ];
  int cid[ 512 ];// TODO: Make grow when returning too many items.
  const int ncid = rcGetChunksOverlappingRect( chunkyMesh, tbmin, tbmax, cid, 512 );
  if( !ncid )
  {
    return 0;// empty
  }

  for( int i = 0; i < ncid; ++i )
  {
    const rcChunkyTriMeshNode& node = chunkyMesh->nodes[ cid[ i ] ];
    const int* tris = &chunkyMesh->tris[ node.i * 3 ];
    const int ntris = node.n;

    memset( rc.triAreas, 0, ntris * sizeof( unsigned char ) );
    rcMarkWalkableTriangles( m_ctx, tcfg.walkableSlopeAngle,
                             verts, nverts, tris, ntris, rc.triAreas );

    if( !rcRasterizeTriangles( m_ctx, verts, nverts, tris, rc.triAreas, ntris, *rc.solid, tcfg.walkableClimb ) )
      return 0;
  }

  // Once all geometry is rasterized, we do initial pass of filtering to
  // remove unwanted overhangs caused by the conservative rasterization
  // as well as filter spans where the character cannot possibly stand.
  //if( m_filterLowHangingObstacles )
    rcFilterLowHangingWalkableObstacles( m_ctx, tcfg.walkableClimb, *rc.solid );
  //if( m_filterLedgeSpans )
    rcFilterLedgeSpans( m_ctx, tcfg.walkableHeight, tcfg.walkableClimb, *rc.solid );
  //if( m_filterWalkableLowHeightSpans )
    rcFilterWalkableLowHeightSpans( m_ctx, tcfg.walkableHeight, *rc.solid );


  rc.chf = rcAllocCompactHeightfield();
  if( !rc.chf )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'chf'.\n" );
    return 0;
  }
  if( !rcBuildCompactHeightfield( m_ctx, tcfg.walkableHeight, tcfg.walkableClimb, *rc.solid, *rc.chf ) )
  {
    printf( "[Navmesh] buildNavigation: Could not build compact data.\n" );
    return 0;
  }

  // Erode the walkable area by agent radius.
  if( !rcErodeWalkableArea( m_ctx, tcfg.walkableRadius, *rc.chf ) )
  {
    printf( "[Navmesh] buildNavigation: Could not erode.\n" );
    return 0;
  }

  // (Optional) Mark areas.
  const ConvexVolume* vols = m_geom->getConvexVolumes();
  for( int i = 0; i < m_geom->getConvexVolumeCount(); ++i )
  {
    rcMarkConvexPolyArea( m_ctx, vols[ i ].verts, vols[ i ].nverts,
                          vols[ i ].hmin, vols[ i ].hmax,
                          ( unsigned char ) vols[ i ].area, *rc.chf );
  }

  if( !rcBuildRegionsMonotone( m_ctx, *rc.chf, cfg.borderSize, cfg.minRegionArea, cfg.mergeRegionArea ) )
  {
    printf( "[Navmesh] buildNavigation: Could not build monotone regions.\n" );
    return 0;
  }

  rc.lset = rcAllocHeightfieldLayerSet();
  if( !rc.lset )
  {
    printf( "[Navmesh] buildNavigation: Out of memory 'lset'.\n" );
    return 0;
  }
  if( !rcBuildHeightfieldLayers( m_ctx, *rc.chf, tcfg.borderSize, tcfg.walkableHeight, *rc.lset ) )
  {
    printf( "[Navmesh] buildNavigation: Could not build heightfield layers.\n" );
    return 0;
  }

  rc.ntiles = 0;
  for( int i = 0; i < rcMin( rc.lset->nlayers, MAX_LAYERS ); ++i )
  {
    TileCacheData* tile = &rc.tiles[ rc.ntiles++ ];
    const rcHeightfieldLayer* layer = &rc.lset->layers[ i ];

    // Store header
    dtTileCacheLayerHeader header;
    header.magic = DT_TILECACHE_MAGIC;
    header.version = DT_TILECACHE_VERSION;

    // Tile layer location in the navmesh.
    header.tx = tx;
    header.ty = ty;
    header.tlayer = i;
    dtVcopy( header.bmin, layer->bmin );
    dtVcopy( header.bmax, layer->bmax );

    // Tile info.
    header.width = ( unsigned char ) layer->width;
    header.height = ( unsigned char ) layer->height;
    header.minx = ( unsigned char ) layer->minx;
    header.maxx = ( unsigned char ) layer->maxx;
    header.miny = ( unsigned char ) layer->miny;
    header.maxy = ( unsigned char ) layer->maxy;
    header.hmin = ( unsigned short ) layer->hmin;
    header.hmax = ( unsigned short ) layer->hmax;

    dtStatus status = dtBuildTileCacheLayer( &comp, &header, layer->heights, layer->areas, layer->cons,
                                             &tile->data, &tile->dataSize );
    if( dtStatusFailed( status ) )
    {
      return 0;
    }
  }

  // Transfer ownsership of tile data from build context to the caller.
  int n = 0;
  for( int i = 0; i < rcMin( rc.ntiles, maxTiles ); ++i )
  {
    tiles[ n++ ] = rc.tiles[ i ];
    rc.tiles[ i ].data = 0;
    rc.tiles[ i ].dataSize = 0;
  }

  return n;
}

bool TiledNavmeshGenerator::buildTiledCache()
{
  dtStatus status;

  if( !m_geom || !m_geom->getMesh() )
  {
    printf( "[Navmesh] buildTiledNavigation: No vertices and triangles." );
    return false;
  }

  m_tMeshProcess->init( m_geom );

  // Init cache
  const float* bmin = m_geom->getNavMeshBoundsMin();
  const float* bmax = m_geom->getNavMeshBoundsMax();
  int gw = 0, gh = 0;
  rcCalcGridSize( bmin, bmax, m_cellSize, &gw, &gh );
  const int ts = ( int ) m_tileSize;
  const int tw = ( gw + ts - 1 ) / ts;
  const int th = ( gh + ts - 1 ) / ts;

  // Generation params.
  rcConfig cfg;
  memset( &cfg, 0, sizeof( cfg ) );
  cfg.cs = m_cellSize;
  cfg.ch = m_cellHeight;
  cfg.walkableSlopeAngle = m_agentMaxSlope;
  cfg.walkableHeight = ( int ) ceilf( m_agentHeight / cfg.ch );
  cfg.walkableClimb = ( int ) floorf( m_agentMaxClimb / cfg.ch );
  cfg.walkableRadius = 8.0;// ( int ) ceilf( m_agentRadius / cfg.cs );
  cfg.maxEdgeLen = ( int ) ( m_edgeMaxLen / m_cellSize );
  cfg.maxSimplificationError = m_edgeMaxError;
  cfg.minRegionArea = ( int ) rcSqr( m_regionMinSize );    // Note: area = size*size
  cfg.mergeRegionArea = ( int ) rcSqr( m_regionMergeSize );// Note: area = size*size
  cfg.maxVertsPerPoly = ( int ) m_vertsPerPoly;
  cfg.tileSize = ( int ) m_tileSize;
  cfg.borderSize = cfg.walkableRadius + 3;// Reserve enough padding.
  cfg.width = cfg.tileSize + cfg.borderSize * 2;
  cfg.height = cfg.tileSize + cfg.borderSize * 2;
  cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
  cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;
  rcVcopy( cfg.bmin, bmin );
  rcVcopy( cfg.bmax, bmax );

  // Tile cache params.
  dtTileCacheParams tcparams;
  memset( &tcparams, 0, sizeof( tcparams ) );
  rcVcopy( tcparams.orig, bmin );
  tcparams.cs = m_cellSize;
  tcparams.ch = m_cellHeight;
  tcparams.width = ( int ) m_tileSize;
  tcparams.height = ( int ) m_tileSize;
  tcparams.walkableHeight = m_agentHeight;
  tcparams.walkableRadius = m_agentRadius;
  tcparams.walkableClimb = m_agentMaxClimb;
  tcparams.maxSimplificationError = m_edgeMaxError;
  tcparams.maxTiles = tw * th * EXPECTED_LAYERS_PER_TILE;
  tcparams.maxObstacles = 128;

  dtFreeTileCache( m_tileCache );

  m_tileCache = dtAllocTileCache();
  if( !m_tileCache )
  {
    printf( "[Navmesh] buildTiledNavigation: Could not allocate tile cache." );
    return false;
  }
  status = m_tileCache->init( &tcparams, m_tAllocator, m_tCompressor, m_tMeshProcess );
  if( dtStatusFailed( status ) )
  {
    printf( "[Navmesh] buildTiledNavigation: Could not init tile cache." );
    return false;
  }

  dtFreeNavMesh( m_navMesh );

  m_navMesh = dtAllocNavMesh();
  if( !m_navMesh )
  {
    printf( "[Navmesh] buildTiledNavigation: Could not allocate navmesh." );
    return false;
  }

  dtNavMeshParams params;
  memset( &params, 0, sizeof( params ) );
  rcVcopy( params.orig, bmin );
  params.tileWidth = m_tileSize * m_cellSize;
  params.tileHeight = m_tileSize * m_cellSize;
  params.maxTiles = m_maxTiles;
  params.maxPolys = m_maxPolysPerTile;

  status = m_navMesh->init( &params );
  if( dtStatusFailed( status ) )
  {
    printf( "[Navmesh] buildTiledNavigation: Could not init navmesh." );
    return false;
  }

  // Preprocess tiles.

  m_ctx->resetTimers();

  for( int y = 0; y < th; ++y )
  {
    for( int x = 0; x < tw; ++x )
    {
      TileCacheData tiles[ MAX_LAYERS ];
      memset( tiles, 0, sizeof( tiles ) );
      int ntiles = rasterizeTileLayers( x, y, cfg, tiles, MAX_LAYERS );

      for( int i = 0; i < ntiles; ++i )
      {
        TileCacheData* tile = &tiles[ i ];
        status = m_tileCache->addTile( tile->data, tile->dataSize, DT_COMPRESSEDTILE_FREE_DATA, 0 );
        if( dtStatusFailed( status ) )
        {
          dtFree( tile->data );
          tile->data = 0;
          continue;
        }
      }
    }
  }

  // Build initial meshes
  m_ctx->startTimer( RC_TIMER_TOTAL );
  for( int y = 0; y < th; ++y )
    for( int x = 0; x < tw; ++x )
      m_tileCache->buildNavMeshTilesAt( x, y, m_navMesh );
  m_ctx->stopTimer( RC_TIMER_TOTAL );
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
  {
    rcFreeHeightField( m_solid );
    m_solid = nullptr;
    delete[] m_triareas;
    m_triareas = nullptr;
    return nullptr;
  }

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
    rcFreeCompactHeightfield( m_chf );
    rcFreeContourSet( m_cset );
    m_chf = nullptr;
    m_cset = nullptr;
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
