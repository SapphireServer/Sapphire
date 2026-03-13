#include "NavMeshCacheIO.h"

#include <DetourAlloc.h>

#include <fstream>
#include <limits>

namespace Sapphire
{
  namespace Common
  {
    namespace Navi
    {
      std::filesystem::path getNavMeshCachePath( const std::filesystem::path& navPath )
      {
        auto cachePath = navPath;
        cachePath.replace_extension( ".navmesh_cache" );
        return cachePath;
      }

      bool isNavMeshCacheFresh( const std::filesystem::path& navPath, const std::filesystem::path& cachePath )
      {
        std::error_code ec;
        if( !std::filesystem::exists( cachePath, ec ) || ec )
          return false;

        std::error_code navTimeEc;
        std::error_code cacheTimeEc;
        const auto navTime = std::filesystem::last_write_time( navPath, navTimeEc );
        const auto cacheTime = std::filesystem::last_write_time( cachePath, cacheTimeEc );

        if( navTimeEc || cacheTimeEc )
          return false;

        return cacheTime >= navTime;
      }

      bool loadNavMeshCache( const std::filesystem::path& cachePath, dtNavMesh* navMesh, std::string* errorMessage )
      {
        if( !navMesh )
        {
          if( errorMessage )
            *errorMessage = "navmesh is null";

          return false;
        }

        std::ifstream cacheStream( cachePath, std::ios::binary );
        if( !cacheStream.is_open() )
        {
          if( errorMessage )
            *errorMessage = "unable to open cache file";

          return false;
        }

        NavMeshCacheHeader header{};
        cacheStream.read( reinterpret_cast< char* >( &header ), sizeof( NavMeshCacheHeader ) );
        if( !cacheStream )
        {
          if( errorMessage )
            *errorMessage = "unable to read cache header";

          return false;
        }

        if( header.magic != NAVMESH_CACHE_MAGIC )
        {
          if( errorMessage )
            *errorMessage = "invalid cache magic";

          return false;
        }

        if( header.version != NAVMESH_CACHE_VERSION )
        {
          if( errorMessage )
            *errorMessage = "unsupported cache version";

          return false;
        }

        if( header.numTiles > static_cast< uint32_t >( navMesh->getMaxTiles() ) )
        {
          if( errorMessage )
            *errorMessage = "invalid cache tile count";

          return false;
        }

        uint64_t totalTileBytes = 0;
        for( uint32_t i = 0; i < header.numTiles; ++i )
        {
          uint32_t tileSize = 0;
          cacheStream.read( reinterpret_cast< char* >( &tileSize ), sizeof( uint32_t ) );
          if( !cacheStream )
          {
            if( errorMessage )
              *errorMessage = "truncated tile-size data";

            return false;
          }

          if( tileSize == 0 || tileSize > NAVMESH_CACHE_MAX_TILE_BYTES )
          {
            if( errorMessage )
              *errorMessage = "invalid tile size";

            return false;
          }

          totalTileBytes += tileSize;
          if( totalTileBytes > NAVMESH_CACHE_MAX_TOTAL_BYTES )
          {
            if( errorMessage )
              *errorMessage = "cache exceeds total size budget";

            return false;
          }

          if( tileSize > static_cast< uint32_t >( std::numeric_limits< int32_t >::max() ) )
          {
            if( errorMessage )
              *errorMessage = "tile size exceeds detour limit";

            return false;
          }

          const int32_t tileSizeInt = static_cast< int32_t >( tileSize );
          auto* data = static_cast< unsigned char* >( dtAlloc( tileSizeInt, DT_ALLOC_PERM ) );
          if( !data )
          {
            if( errorMessage )
              *errorMessage = "allocation failure while loading tile";

            return false;
          }

          cacheStream.read( reinterpret_cast< char* >( data ), static_cast< std::streamsize >( tileSizeInt ) );
          if( !cacheStream )
          {
            dtFree( data );
            if( errorMessage )
              *errorMessage = "truncated tile payload";

            return false;
          }

          dtStatus status = navMesh->addTile( data, tileSizeInt, DT_TILE_FREE_DATA, 0, nullptr );
          if( dtStatusFailed( status ) )
          {
            dtFree( data );
            if( errorMessage )
              *errorMessage = "detour addTile failed";

            return false;
          }
        }

        return true;
      }
      
      // todo: probably enum this errormessage instead lol
      bool writeNavMeshCache( const std::filesystem::path& cachePath, const dtNavMesh* navMesh, std::string* errorMessage )
      {
        if( !navMesh )
        {
          if( errorMessage )
            *errorMessage = "navmesh is null";

          return false;
        }

        uint32_t numTiles = 0;
        const int maxTiles = navMesh->getMaxTiles();
        for( int i = 0; i < maxTiles; ++i )
        {
          const dtMeshTile* tile = navMesh->getTile( i );
          if( tile && tile->header )
          {
            if( numTiles == std::numeric_limits< uint32_t >::max() )
            {
              if( errorMessage )
                *errorMessage = "tile count overflow";

              return false;
            }

            numTiles++;
          }
        }

        auto tempCachePath = cachePath;
        tempCachePath += ".tmp";

        std::ofstream cacheStream( tempCachePath, std::ios::binary | std::ios::trunc );
        if( !cacheStream.is_open() )
        {
          if( errorMessage )
            *errorMessage = "unable to open temp cache for writing";

          return false;
        }

        NavMeshCacheHeader header{ NAVMESH_CACHE_MAGIC, NAVMESH_CACHE_VERSION, numTiles };
        cacheStream.write( reinterpret_cast< const char* >( &header ), sizeof( NavMeshCacheHeader ) );
        if( !cacheStream )
        {
          if( errorMessage )
            *errorMessage = "failed writing cache header";

          cacheStream.close();
          std::error_code cleanupEc;
          std::filesystem::remove( tempCachePath, cleanupEc );
          return false;
        }

        for( int i = 0; i < maxTiles; ++i )
        {
          const dtMeshTile* tile = navMesh->getTile( i );
          if( !tile || !tile->header )
            continue;

          if( tile->dataSize <= 0 || tile->dataSize > static_cast< int >( NAVMESH_CACHE_MAX_TILE_BYTES ) )
          {
            if( errorMessage )
              *errorMessage = "invalid tile size while writing";

            cacheStream.close();
            std::error_code cleanupEc;
            std::filesystem::remove( tempCachePath, cleanupEc );
            return false;
          }

          const uint32_t tileSize = static_cast< uint32_t >( tile->dataSize );
          cacheStream.write( reinterpret_cast< const char* >( &tileSize ), sizeof( uint32_t ) );
          if( !cacheStream )
          {
            if( errorMessage )
              *errorMessage = "failed writing tile size";

            cacheStream.close();
            std::error_code cleanupEc;
            std::filesystem::remove( tempCachePath, cleanupEc );
            return false;
          }

          cacheStream.write( reinterpret_cast< const char* >( tile->data ), static_cast< std::streamsize >( tileSize ) );
          if( !cacheStream )
          {
            if( errorMessage )
              *errorMessage = "failed writing tile payload";

            cacheStream.close();
            std::error_code cleanupEc;
            std::filesystem::remove( tempCachePath, cleanupEc );
            return false;
          }
        }

        cacheStream.close();

        std::error_code removeEc;
        std::filesystem::remove( cachePath, removeEc );

        std::error_code renameEc;
        std::filesystem::rename( tempCachePath, cachePath, renameEc );
        if( renameEc )
        {
          if( errorMessage )
            *errorMessage = "failed to finalize cache file";

          std::error_code cleanupEc;
          std::filesystem::remove( tempCachePath, cleanupEc );
          return false;
        }

        return true;
      }
    }
  }
}
