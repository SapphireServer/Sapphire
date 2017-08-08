#ifndef _UPDATEHPMPTP_H
#define _UPDATEHPMPTP_H

#include <Server_Common/GamePacketNew.h>
#include "Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The Ping response packet.
*/
class UpdateHpMpTpPacket :
   public GamePacketNew< FFXIVIpcUpdateHpMpTp >
{
public:
   UpdateHpMpTpPacket( Entity::ActorPtr pActor ) :
      GamePacketNew< FFXIVIpcUpdateHpMpTp >( pActor->getId(), pActor->getId() )
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