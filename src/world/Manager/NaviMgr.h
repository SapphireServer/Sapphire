#ifndef SAPPHIRE_NAVIMGR_H
#define SAPPHIRE_NAVIMGR_H

#include "Forwards.h"
#include "BaseManager.h"

#include <array>
#include <Navi/NaviProvider.h>

namespace Sapphire::World::Manager
{
  class NaviMgr : public BaseManager
  {

  public:

    NaviMgr( FrameworkPtr pFw );
    virtual ~NaviMgr() = default;

    bool setupTerritory( std::string internalName );
    NaviProvider* getNaviProvider( std::string internalName );

  private:
    FrameworkPtr m_pFw;

    std::unordered_map<std::string, NaviProvider*> m_naviProviderTerritoryMap;
  };

}

#endif // SAPPHIRE_NAVIMGR_H
