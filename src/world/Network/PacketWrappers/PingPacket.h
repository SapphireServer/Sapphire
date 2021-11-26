#ifndef _CORE_NETWORK_PACKETS_PINGPACKET_H
#define _CORE_NETWORK_PACKETS_PINGPACKET_H

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
      m_data.timeInMilliseconds = 0x000014D00000000 + inVal;
    };
  };

}

#endif /*_CORE_NETWORK_PACKETS_CPINGPACKET_H*/
