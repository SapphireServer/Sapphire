#ifndef _UPDATEHPMPTP_H
#define _UPDATEHPMPTP_H

#include <Network/GamePacketNew.h>
#include <Actor/Chara.h>
#include "Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The Ping response packet.
*/
class UpdateHpMpTpPacket :
   public ZoneChannelPacket< FFXIVIpcUpdateHpMpTp >
{
public:
   UpdateHpMpTpPacket( Entity::Chara& actor ) :
      ZoneChannelPacket< FFXIVIpcUpdateHpMpTp >( actor.getId(), actor.getId() )
   {
      initialize( actor );
   };

private:
   void initialize( Entity::Chara& actor )
   {
      m_data.hp = actor.getHp();
      m_data.mp = actor.getMp();
      m_data.tp = actor.getTp();
   };
};

}
}
}
}

#endif /*_UPDATEHPMPTP_H*/
