#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include <Util/Util.h>
#include <unordered_map>

namespace Sapphire::World::Manager
{

  struct WarpInfo
  {
    uint32_t targetTerritoryId;
    Common::WarpType m_warpType;
  };

  class WarpMgr
  {
  public:
    WarpMgr() = default;

  private:
    std::unordered_map< uint32_t, std::shared_ptr< WarpInfo > > m_entityIdToWarpInfoMap;

  };

}
