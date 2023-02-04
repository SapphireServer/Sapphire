#pragma once

#include "ForwardsZone.h"

#include <array>
#include <tuple>

namespace Sapphire::World::Manager
{
  class NaviMgr
  {
  public:
    NaviMgr() = default;
    virtual ~NaviMgr() = default;

    bool setupTerritory( const std::string& bgPath, uint32_t guid );
    Navi::NaviProviderPtr getNaviProvider( const std::string& bgPath, uint32_t guid );

  private:
    std::string getBgName( const std::string& bgPath );

    std::unordered_map< uint32_t, Navi::NaviProviderPtr > m_naviProviderTerritoryMap;
  };

}

