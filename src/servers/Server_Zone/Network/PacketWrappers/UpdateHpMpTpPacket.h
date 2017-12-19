#ifndef _UPDATEHPMPTP_H
#define _UPDATEHPMPTP_H

#include <Server_Common/Network/GamePacketNew.h>
#include <Actor/Actor.h>
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
   UpdateHpMpTpPacket( Entity::ActorPtr pActor ) :
      ZoneChannelPacket< FFXIVIpcUpdateHpMpTp >( pActor->getId(), pActor->getId() )
   {
      initialize( pActor );
   };

private:
   void initialize( Entity::ActorPtr pActor )
   {
      m_data.hp = pActor->getHp();
      m_data.mp = pActor->getMp();
      m_data.tp = pActor->getTp();
   };
};

}
}
}
}

#endif /*_UPDATEHPMPTP_H*/