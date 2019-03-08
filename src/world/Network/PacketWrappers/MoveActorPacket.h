#ifndef _MOVEACTORPACKET_H
#define _MOVEACTORPACKET_H

#include <Network/GamePacket.h>
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
    MoveActorPacket( Entity::Chara& actor, uint8_t headRotation, uint8_t animationType, uint8_t state, uint16_t animationSpeed, uint8_t unknownRotation = 0 ) :
      ZoneChannelPacket< FFXIVIpcActorMove >( actor.getId(), actor.getId() )
    {
      initialize( actor, headRotation, animationType, state, animationSpeed, unknownRotation );
    };

  private:
    void initialize( Entity::Chara& actor, uint8_t headRotation, uint8_t animationType, uint8_t state, uint16_t animationSpeed, uint8_t unknownRotation )
    {

      m_data.rotation = Util::floatToUInt8Rot( actor.getRot() );
      m_data.headRotation = headRotation;
      m_data.animationType = animationType;
      m_data.animationState = state;
      m_data.animationSpeed = animationSpeed;
      m_data.unknownRotation = unknownRotation;
      m_data.posX = Util::floatToUInt16( actor.getPos().x );
      m_data.posY = Util::floatToUInt16( actor.getPos().y );
      m_data.posZ = Util::floatToUInt16( actor.getPos().z );

    };
  };

}

#endif /*_MOVEACTORPACKET_H*/
