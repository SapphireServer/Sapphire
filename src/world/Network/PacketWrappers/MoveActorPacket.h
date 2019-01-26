#ifndef _MOVEACTORPACKET_H
#define _MOVEACTORPACKET_H

#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Util/UtilMath.h>
#include "Actor/Player.h"
#include "Forwards.h"


namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The Client UI Initialization packet. This must be sent to the client
  * once upon connection to configure the UI.
  */
  class MoveActorPacket :
    public ZoneChannelPacket< FFXIVIpcActorMove >
  {
  public:
    MoveActorPacket( Entity::Chara& actor, uint8_t unk1, uint8_t animationType, uint8_t unk3, uint16_t unk4 ) :
      ZoneChannelPacket< FFXIVIpcActorMove >( actor.getId(), actor.getId() )
    {
      initialize( actor, unk1, animationType, unk3, unk4 );
    };

  private:
    void initialize( Entity::Chara& actor, uint8_t unk1, uint8_t animationType, uint8_t unk3, uint16_t unk4 )
    {

      m_data.rotation = Util::floatToUInt8Rot( actor.getRot() );
      m_data.unknown_1 = unk1;
      m_data.animationType = animationType;
      m_data.unknown_3 = unk3;
      m_data.unknown_4 = unk4;
      m_data.posX = Util::floatToUInt16( actor.getPos().x );
      m_data.posY = Util::floatToUInt16( actor.getPos().y );
      m_data.posZ = Util::floatToUInt16( actor.getPos().z );

    };
  };

}

#endif /*_MOVEACTORPACKET_H*/
