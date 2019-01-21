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
    NaviProvider( const ZonePtr pZone, Sapphire::FrameworkPtr pFw );

    void init();
    void loadMesh( std::string path );
    void initQuery();

    void toDetourPos(const Common::FFXIVARR_POSITION3 position, float* out);

    std::vector< Sapphire::Common::FFXIVARR_POSITION3 > findFollowPath(Common::FFXIVARR_POSITION3 startPos, Common::FFXIVARR_POSITION3 endPos);

    bool hasNaviMesh() const;

  protected:
    FrameworkPtr m_pFw;
    ZonePtr m_pZone;

    dtNavMesh* m_naviMesh;
    dtNavMeshQuery* m_naviMeshQuery;

    float m_polyFindRange[3];
  };

}

#endif
