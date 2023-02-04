#pragma once

#include <Network/GamePacket.h>

#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Ping response packet.
  */
  class PingPacket : public ZoneChannelPacket< FFXIVIpcSync >
  {
  public:
    PingPacket( Entity::Player& player, int32_t inVal ) :
      ZoneChannelPacket< FFXIVIpcSync >( player.getId(), player.getId() )
    {
      initialize( player, inVal );
    };

  private:
    void initialize( Entity::Player& player, int32_t inVal )
    {
      m_data.clientTimeValue = inVal;
      m_data.transmissionInterval = 333;
    };
  };

}