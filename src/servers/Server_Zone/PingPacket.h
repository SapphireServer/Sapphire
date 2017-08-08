#ifndef _CORE_NETWORK_PACKETS_PINGPACKET_H
#define _CORE_NETWORK_PACKETS_PINGPACKET_H

#include <Server_Common/GamePacketNew.h>

#include "Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The Ping response packet.
*/
class PingPacket :
   public GamePacketNew<FFXIVIpcPing>
{
public:
   PingPacket( Entity::PlayerPtr player, int32_t inVal ) :
      GamePacketNew<FFXIVIpcPing>( player->getId(), player->getId() )
   {
      initialize( player, inVal );
   };

private:
   void initialize( Entity::PlayerPtr player, int32_t inVal )
   {
      m_data.timeInMilliseconds = 0x000014D00000000 + inVal;
   };
};

}
}
}
}

#endif /*_CORE_NETWORK_PACKETS_CPINGPACKET_H*/