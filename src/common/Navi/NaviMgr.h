#pragma once

#include <Forwards.h>

#include <string>
#include <unordered_map>

namespace Sapphire::Common::Navi
{
  class NaviMgr
  {
  public:
    NaviMgr() = default;
    virtual ~NaviMgr() = default;

    bool setupTerritory( const std::string& naviPath, const std::string& bgPath, uint32_t guid );
    NaviProviderPtr getNaviProvider( const std::string& bgPath, uint32_t guid );

  private:
    std::string getBgName( const std::string& bgPath );

    std::unordered_map< uint32_t, NaviProviderPtr > m_naviProviderTerritoryMap;
  };

}

