#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

#include <recastnavigation/Detour/Include/DetourNavMesh.h>

namespace Sapphire
{
  namespace Common
  {
    namespace Navi
    {
      struct NavMeshCacheHeader
      {
        uint32_t magic;
        uint32_t version;
        uint32_t numTiles;
      };

      // breaking changes to navmesh format should increment this and cause old caches to be regenerated
      constexpr uint32_t NAVMESH_CACHE_MAGIC = 0xFF14DEAD;
      constexpr uint32_t NAVMESH_CACHE_VERSION = 1;
      constexpr uint32_t NAVMESH_CACHE_MAX_TILE_BYTES = 32 * 1024 * 1024;

      std::filesystem::path getNavMeshCachePath( const std::filesystem::path& navPath );
      bool isNavMeshCacheFresh( const std::filesystem::path& navPath, const std::filesystem::path& cachePath );

      bool loadNavMeshCache( const std::filesystem::path& cachePath, dtNavMesh* navMesh, std::string* errorMessage );
      bool writeNavMeshCache( const std::filesystem::path& cachePath, const dtNavMesh* navMesh, std::string* errorMessage );
    }
  }
}
