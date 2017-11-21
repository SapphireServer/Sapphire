#ifndef _PLAYERSTATE_H
#define _PLAYERSTATE_H

#include <src/servers/Server_Common/Network/GamePacketNew.h>
#include "src/servers/Server_Zone/Actor/Player.h"
#include "src/servers/Server_Zone/Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief Packet sent to set a players state, this impacts which actions he can perform.
*/
class PlayerStateFlagsPacket :
   public ZoneChannelPacket< FFXIVIpcPlayerStateFlags >
{
public:
   PlayerStateFlagsPacket( Entity::PlayerPtr pActor ) :
      ZoneChannelPacket< FFXIVIpcPlayerStateFlags >( pActor->getId(), pActor->getId() )
   {
      initialize( pActor->getStateFlags() );
   }

   PlayerStateFlagsPacket( Entity::PlayerPtr pActor, std::vector< Common::PlayerStateFlag > flags ) :
      ZoneChannelPacket< FFXIVIpcPlayerStateFlags >( pActor->getId(), pActor->getId() )
   {
      uint8_t newFlags[7];
      memset( newFlags, 0, 7 );

      for( auto& flag : flags )
      {
         int32_t iFlag = static_cast< uint32_t >( flag );
         uint8_t index = iFlag / 8;
         uint8_t bitIndex = iFlag % 8;

         uint8_t value = 1 << bitIndex;

         newFlags[index] |= value;
      }

      initialize( newFlags );
   }

private:
   void initialize( const uint8_t* flags )
   {
      memcpy( m_data.flags, flags, 7 );
   };
};

}
}
}
}

#endif /*_PLAYERSTATE_H*/