#ifndef _UPDATEHPMPTP_H
#define _UPDATEHPMPTP_H

#include <Network/GamePacket.h>
#include <Actor/Chara.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The Ping response packet.
  */
  class UpdateHpMpTpPacket : public WorldChannelPacket< FFXIVIpcUpdateHpMpTp >
  {
  public:
    UpdateHpMpTpPacket( Entity::Chara& actor ) :
      WorldChannelPacket< FFXIVIpcUpdateHpMpTp >( actor.getId(), actor.getId() )
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

#endif /*_UPDATEHPMPTP_H*/
