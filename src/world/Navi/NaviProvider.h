#ifndef _NAVIPROVIDER_H_
#define _NAVIPROVIDER_H_

#include <Common.h>
#include "ForwardsZone.h"
#include <recastnavigation/Detour/Include/DetourNavMesh.h>
#include <recastnavigation/Detour/Include/DetourNavMeshQuery.h>

namespace Sapphire
{

  class NaviProvider
  {

    static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
    static const int NAVMESHSET_VERSION = 1;

    struct NavMeshSetHeader
    {
      int magic;
      int version;
      int numTiles;
      dtNavMeshParams params;
    };

    struct NavMeshTileHeader
    {
      dtTileRef tileRef;
      int dataSize;
    };

    static const int MAX_POLYS = 256;
	  static const int MAX_SMOOTH = 2048;

  public:
    NaviProvider( const std::string internalName );

    bool init();
    void loadMesh( std::string path );
    void initQuery();

    void toDetourPos(const Common::FFXIVARR_POSITION3 position, float* out);
    Sapphire::Common::FFXIVARR_POSITION3 toGamePos( float* pos );

    std::vector< Sapphire::Common::FFXIVARR_POSITION3 > findFollowPath(Common::FFXIVARR_POSITION3 startPos, Common::FFXIVARR_POSITION3 endPos);

    bool hasNaviMesh() const;

  protected:
    std::string m_internalName;

    dtNavMesh* m_naviMesh;
    dtNavMeshQuery* m_naviMeshQuery;

    float m_polyFindRange[3];

  private:
    static int fixupCorridor( dtPolyRef* path, const int npath, const int maxPath,
                          const dtPolyRef* visited, const int nvisited );
    static int fixupShortcuts( dtPolyRef* path, int npath, dtNavMeshQuery* navQuery );
    inline static bool inRange( const float* v1, const float* v2, const float r, const float h );
    static bool getSteerTarget( dtNavMeshQuery* navQuery, const float* startPos, const float* endPos,
                            const float minTargetDist,
                            const dtPolyRef* path, const int pathSize,
                            float* steerPos, unsigned char& steerPosFlag, dtPolyRef& steerPosRef,
                            float* outPoints = 0, int* outPointCount = 0 );

  };

}

#endif
