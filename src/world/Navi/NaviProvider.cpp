#include <Common.h>
#include <CommonGen.h>

#include "Framework.h"
#include "NaviProvider.h"
#include <recastnavigation/Detour/Include/DetourNavMesh.h>
#include <recastnavigation/Detour/Include/DetourNavMeshQuery.h>
#include <experimental/filesystem>
#include <filesystem>

#include "../Territory/Zone.h"
#include <Logging/Logger.h>

Sapphire::NaviProvider::NaviProvider( Sapphire::ZonePtr pZone, Sapphire::FrameworkPtr pFw ) :
  m_pFw( pFw ),
  m_pZone( pZone ),
  m_naviMesh( nullptr ),
  m_naviMeshQuery( nullptr )
{
}

void Sapphire::NaviProvider::init()
{
  auto meshesFolder = std::filesystem::path( "navi" );
  auto meshFolder = meshesFolder / std::filesystem::path( m_pZone->getInternalName() );

  if( std::filesystem::exists( meshFolder ) )
  {
    auto baseMesh = meshFolder / std::filesystem::path( m_pZone->getInternalName() + ".nav" );

    //m_naviMesh = LoadMesh( baseMesh.string() );

    // Load all meshes for testing
    for( const auto & entry : std::filesystem::directory_iterator( meshFolder ) )
    {
      if( entry.path().extension().string() == ".nav" )
      {
        Logger::debug( "Loading " + entry.path().string() );
        LoadMesh( entry.path().string() );
      }
    }

    InitQuery();
  }
}

bool Sapphire::NaviProvider::HasNaviMesh() const
{
  return m_naviMesh != nullptr;
}

void Sapphire::NaviProvider::InitQuery()
{
  if(m_naviMeshQuery != nullptr)
    dtFreeNavMeshQuery( m_naviMeshQuery );

  m_naviMeshQuery = dtAllocNavMeshQuery();
  m_naviMeshQuery->init( m_naviMesh, 2048 );
}

void Sapphire::NaviProvider::LoadMesh( std::string path )
{
  FILE* fp = fopen( path.c_str(), "rb" );
  if( !fp )
    throw std::exception( "Could open navimesh file" );

  // Read header.
  NavMeshSetHeader header;

  size_t readLen = fread( &header, sizeof( NavMeshSetHeader ), 1, fp );
  if( readLen != 1 )
  {
    fclose( fp );
    throw std::exception( "Could not read NavMeshSetHeader" );
  }

  if( header.magic != NAVMESHSET_MAGIC )
  {
    fclose( fp );
    throw std::exception( "Not a NavMeshSet" );
  }

  if( header.version != NAVMESHSET_VERSION )
  {
    fclose( fp );
    throw std::exception( "Invalid NavMeshSet version" );
  }

  if( !m_naviMesh )
  {
    m_naviMesh = dtAllocNavMesh();
    if( !m_naviMesh )
    {
      fclose( fp );
      throw std::exception( "Could not allocate dtNavMesh" );
    }

    dtStatus status = m_naviMesh->init( &header.params );
    if( dtStatusFailed( status ) )
    {
      fclose( fp );
      throw std::exception( "Could not initialize dtNavMesh" );
    }
  }

  // Read tiles.
  for( int i = 0; i < header.numTiles; ++i )
  {
    NavMeshTileHeader tileHeader;
    readLen = fread( &tileHeader, sizeof( tileHeader ), 1, fp );
    if( readLen != 1 )
    {
      fclose( fp );
      throw std::exception( "Could not read NavMeshTileHeader" );
    }

    if( !tileHeader.tileRef || !tileHeader.dataSize )
      break;

    unsigned char* data = (unsigned char*)dtAlloc( tileHeader.dataSize, DT_ALLOC_PERM );
    if( !data ) break;
    memset( data, 0, tileHeader.dataSize );
    readLen = fread( data, tileHeader.dataSize, 1, fp );
    if( readLen != 1 )
    {
      dtFree( data );
      fclose( fp );
      throw std::exception( "Could not read tile data" );
    }

    m_naviMesh->addTile( data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0 );
  }
  
  fclose( fp );
}