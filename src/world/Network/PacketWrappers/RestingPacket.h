#pragma once

#include <Network/GamePacket.h>
#include <Actor/Chara.h>
#include "Forwards.h"

#include <Network/PacketDef/Zone/ServerZoneDef.h>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Ping response packet.
  */
  class RestingPacket : public ZoneChannelPacket< FFXIVIpcResting >
  {
  public:
    RestingPacket( Entity::Chara& actor ) : ZoneChannelPacket< FFXIVIpcResting >( actor.getId(), actor.getId() )
    {
      initialize( actor );
    };

  private:
    void initialize( Entity::Chara& actor )
    {
      m_data.Hp = actor.getHp();
      m_data.Mp = actor.getMp();
      m_data.Tp = actor.getTp();
    };
  };

}