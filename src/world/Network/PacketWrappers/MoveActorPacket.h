#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Util/UtilMath.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The MoveActor packet for updating an actor's position.
  */
  class MoveActorPacket : public ZoneChannelPacket< FFXIVIpcActorMove >
  {
  public:
    MoveActorPacket( Entity::Chara& actor, uint8_t dirBeforeSlip, uint8_t animationType, uint8_t state, uint16_t animationSpeed, uint8_t unknownRotation = 0 ) :
      ZoneChannelPacket< FFXIVIpcActorMove >( actor.getId(), actor.getId() )
    {
      initialize( actor, dirBeforeSlip, animationType, state, animationSpeed, unknownRotation );
    };

  private:
    void initialize( Entity::Chara& actor, uint8_t dirBeforeSlip, uint8_t animationType, uint8_t state, uint16_t animationSpeed, uint8_t unknownRotation )
    {

      m_data.dir = actor.getRotUInt8();
      m_data.dirBeforeSlip = dirBeforeSlip;
      m_data.flag = animationType;
      m_data.flag2 = state;
      m_data.speed = static_cast< uint8_t >( animationSpeed );
      m_data.pos[0] = Common::Util::floatToUInt16( actor.getPos().x );
      m_data.pos[1] = Common::Util::floatToUInt16( actor.getPos().y );
      m_data.pos[2] = Common::Util::floatToUInt16( actor.getPos().z );

    };
  };
}