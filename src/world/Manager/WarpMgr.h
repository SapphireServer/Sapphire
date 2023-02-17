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

    /// <summary>
    /// request to move a player to specified territorytype and position, with given WarpType
    /// </summary>
    /// <param name="player"></param>
    /// <param name="warpType"></param>
    /// <param name="targetTerritoryId"></param>
    /// <param name="targetPos"></param>
    /// <param name="targetRot"></param>
    void requestMoveTerritory( Entity::Player& player, Common::WarpType warpType, uint32_t targetTerritoryId, Common::FFXIVARR_POSITION3 targetPos, float targetRot );


    /// <summary>
    /// request to move a player to specified territorytype with given WarpType, position will be the same as before
    /// </summary>
    /// <param name="player"></param>
    /// <param name="warpType"></param>
    /// <param name="targetTerritoryId"></param>
    void requestMoveTerritory( Entity::Player& player, Common::WarpType warpType, uint32_t targetTerritoryId );

    /// <summary>
    /// handle player state pre-warp and tells client to warp player
    /// </summary>
    /// <param name="player"></param>
    /// <param name="warpType"></param>
    /// <param name="targetPos"></param>
    /// <param name="targetRot"></param>
    void requestWarp( Entity::Player& player, Common::WarpType warpType, Common::FFXIVARR_POSITION3 targetPos, float targetRot );

    /// <summary>
    /// handle player state post-warp after client is done loading
    /// </summary>
    /// <param name="player"></param>
    void finishWarp( Entity::Player& player );

    /// <summary>
    /// teleport a player to specified aetheryte and teleport type (teleport, return, etc)
    /// </summary>
    /// <param name="player"></param>
    /// <param name="aetheryteId"></param>
    /// <param name="teleportType"></param>
    void requestPlayerTeleport( Entity::Player& player, uint16_t aetheryteId, uint8_t teleportType );

  private:
    std::unordered_map< uint32_t, WarpInfo > m_entityIdToWarpInfoMap;

  };

}
