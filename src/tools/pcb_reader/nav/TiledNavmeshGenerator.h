#ifndef SAPPHIRE_TILEDNAVMESHGENERATOR_H
#define SAPPHIRE_TILEDNAVMESHGENERATOR_H

#include <string>
#include <cassert>
#include <experimental/filesystem>

#include "ext/MeshLoaderObj.h"
#include "ext/ChunkyTriMesh.h"

#include "recastnavigation/Detour/Include/DetourNavMesh.h"
#include "recastnavigation/Detour/Include/DetourNavMeshQuery.h"
#include "recastnavigation/Recast/Include/Recast.h"

namespace fs = std::experimental::filesystem;

class TiledNavmeshGenerator
{
private:
  rcMeshLoaderObj* m_mesh;
  rcChunkyTriMesh* m_chunkyMesh;

  dtNavMesh* m_navMesh;
  dtNavMeshQuery* m_navQuery;


  float m_meshBMin[ 3 ];
  float m_meshBMax[ 3 ];

  float m_tileSize = 160.f;
  float m_cellSize = 0.2f;

  int m_maxTiles = 0;
  int m_maxPolysPerTile = 0;

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


public:
  explicit TiledNavmeshGenerator( const std::string& path )
  {
    if( !fs::exists( path ) )
      throw std::runtime_error( "what" );

    printf( "[Navmesh] loading obj: %s\n", path.c_str() );

    m_mesh = new rcMeshLoaderObj;
    assert( m_mesh );

    if( !m_mesh->load( path ) )
    {
      printf( "[Navmesh] Failed to allocate rcMeshLoaderObj\n" );
      return;
    }

    rcCalcBounds( m_mesh->getVerts(), m_mesh->getVertCount(), m_meshBMin, m_meshBMax );

    m_chunkyMesh = new rcChunkyTriMesh;
    assert( m_chunkyMesh );

    if( !rcCreateChunkyTriMesh( m_mesh->getVerts(), m_mesh->getTris(), m_mesh->getTriCount(), 256, m_chunkyMesh ) )
    {
      printf( "[Navmesh] buildTiledNavigation: Failed to build chunky mesh.\n" );
      return;
    }

    printf( "[Navmesh] loaded obj, verts: %i tris: %i\n", m_mesh->getVertCount(), m_mesh->getTriCount() );

    // todo: load some bullshit settings from exd

    int gw = 0, gh = 0;
    rcCalcGridSize( m_meshBMin, m_meshBMax, m_cellSize, &gw, &gh );

    auto ts = static_cast< uint32_t >( m_tileSize );
    const uint32_t tw = (gw + ts-1) / ts;
    const uint32_t th = (gh + ts-1) / ts;

    printf( "[Navmesh] Tiles %d x %d\n", tw, th );

    int tileBits = rcMin((int)ilog2(nextPow2(tw*th)), 14);
    if (tileBits > 14) tileBits = 14;
    int polyBits = 22 - tileBits;
    m_maxTiles = 1 << tileBits;
    m_maxPolysPerTile = 1 << polyBits;

    printf( "[Navmesh] Max Tiles: %d\tMax Polys: %d\n", m_maxTiles, m_maxPolysPerTile );
  }

  bool buildNavmesh()
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
      printf( "[Navigation] buildTiledNavigation: Could not init navmesh.\n" );
      return false;
    }

    m_navQuery = dtAllocNavMeshQuery();
    assert( m_navQuery );

    status = m_navQuery->init( m_navMesh, 2048 );
    if( dtStatusFailed( status ) )
    {
      printf( "[Navigation] buildTiledNavigation: Could not init Detour navmesh query\n" );
      return false;
    }

  }

  ~TiledNavmeshGenerator()
  {
    delete m_mesh;
    delete m_chunkyMesh;
  }

};


#endif //SAPPHIRE_TILEDNAVMESHGENERATOR_H
