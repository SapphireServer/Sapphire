#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Util/UtilMath.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Client UI Initialization packet. This must be sent to the client
  * once upon connection to configure the UI.
  */
  class MoveActorPacket : public ZoneChannelPacket< FFXIVIpcActorMove >
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

      m_data.dir = Common::Util::floatToUInt8Rot( actor.getRot() );
      m_data.dirBeforeSlip = headRotation;
      m_data.flag = animationType;
      m_data.flag2 = state;
      m_data.speed = static_cast< uint8_t >( animationSpeed );
      m_data.pos[0] = Common::Util::floatToUInt16( actor.getPos().x );
      m_data.pos[1] = Common::Util::floatToUInt16( actor.getPos().y );
      m_data.pos[2] = Common::Util::floatToUInt16( actor.getPos().z );

    };
  };
}