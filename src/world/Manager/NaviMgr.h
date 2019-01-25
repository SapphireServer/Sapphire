#ifndef SAPPHIRE_NAVIMGR_H
#define SAPPHIRE_NAVIMGR_H

#include "ForwardsZone.h"
#include "BaseManager.h"

#include <array>

namespace Sapphire::World::Manager
{
  class NaviMgr : public BaseManager
  {

  public:

    NaviMgr( FrameworkPtr pFw );
    virtual ~NaviMgr() = default;

    bool setupTerritory( const std::string& bgPath );
    Navi::NaviProviderPtr getNaviProvider( const std::string& bgPath );

  private:
    FrameworkPtr m_pFw;

    std::string getBgName( const std::string& bgPath );

    std::unordered_map< std::string, Navi::NaviProviderPtr > m_naviProviderTerritoryMap;
  };

}

#endif // SAPPHIRE_NAVIMGR_H
