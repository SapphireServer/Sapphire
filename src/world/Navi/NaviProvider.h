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

  public:
    NaviProvider( const ZonePtr pZone, Sapphire::FrameworkPtr pFw );

    void init();
    void LoadMesh( std::string path );
    void InitQuery();

    bool HasNaviMesh() const;

  protected:
    FrameworkPtr m_pFw;
    ZonePtr m_pZone;

    dtNavMesh* m_naviMesh;
    dtNavMeshQuery* m_naviMeshQuery;
  };

}

#endif
