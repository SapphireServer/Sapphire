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
    uint32_t m_targetTerritoryId;
    Common::WarpType m_warpType;
    Common::FFXIVARR_POSITION3 m_targetPos;
    float m_targetRot;
  };

  class WarpMgr
  {
  public:
    WarpMgr() = default;
    void requestMoveTerritory( Entity::Player& player, Common::WarpType warpType, uint32_t targetTerritoryId, Common::FFXIVARR_POSITION3 targetPos, float targetRot );
    void requestWarp( Entity::Player& player, Common::WarpType warpType, Common::FFXIVARR_POSITION3 targetPos, float targetRot );
    void finishWarp( Entity::Player& player );

  private:
    std::unordered_map< uint32_t, WarpInfo > m_entityIdToWarpInfoMap;

  };

}
