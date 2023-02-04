#pragma once

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  class NotifyFindContentStatusPacket : public ZoneChannelPacket< FFXIVIpcNotifyFindContentStatus >
  {
  public:
    NotifyFindContentStatusPacket( uint32_t playerId, uint16_t terriId, uint8_t status, uint8_t dpsRoleCount,
                                   uint8_t healerRoleCount, uint8_t tankRoleCount, uint8_t matchingTime ) :
      ZoneChannelPacket< FFXIVIpcNotifyFindContentStatus >( playerId, playerId )
    {
      initialize( terriId, status, dpsRoleCount, healerRoleCount, tankRoleCount, matchingTime );
    };

  private:
    void initialize( uint16_t terriId, uint8_t status, uint8_t dpsRoleCount, uint8_t healerRoleCount, uint8_t tankRoleCount, uint8_t matchingTime )
    {
      m_data.territoryType = terriId;
      m_data.status = status;
      m_data.dpsRoleCount = dpsRoleCount;
      m_data.healerRoleCount = healerRoleCount;
      m_data.tankRoleCount = tankRoleCount;
      m_data.matchingTime = matchingTime;

    };
  };

  template< typename... Args >
  std::shared_ptr< NotifyFindContentStatusPacket > makeNotifyFindContentStatus( Args... args )
  {
    return std::make_shared< NotifyFindContentStatusPacket >( args... );
  }
}
