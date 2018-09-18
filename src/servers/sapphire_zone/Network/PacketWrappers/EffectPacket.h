#ifndef SAPPHIRE_EFFECTPACKET_H
#define SAPPHIRE_EFFECTPACKET_H

#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

class EffectPacket :
  public ZoneChannelPacket< FFXIVIpcEffect >
{
public:
  EffectPacket( uint64_t sourceId, uint32_t targetId, uint32_t actionId ) :
    ZoneChannelPacket< FFXIVIpcEffect >( static_cast< uint32_t >( sourceId ), targetId )
  {
    m_data.header.actionId = actionId;
    m_data.header.actionAnimationId = static_cast< uint16_t >( actionId );

    m_data.header.animationTargetId = targetId;
    m_data.effectTargetId = targetId;

    m_data.header.effectDisplayType = Common::ActionEffectDisplayType::ShowActionName;
  }

  void addEffect( const Server::EffectEntry& effect )
  {
    assert( m_data.header.effectCount <= 8 );

    std::memcpy( &m_data.effects[ m_data.header.effectCount++ ], &effect, sizeof( Server::EffectEntry ) );
  }

  void setAnimationId( uint16_t animationId )
  {
    m_data.header.actionAnimationId = animationId;
  }

  void setEffectFlags( uint32_t effectFlags )
  {
    m_data.effectFlags = effectFlags;
  }

  void setRotation( uint16_t rotation )
  {
    m_data.header.rotation = rotation;
  }

  void setTargetActor( const uint32_t targetId )
  {
    m_data.header.animationTargetId = targetId;
    m_data.effectTargetId = targetId;

    FFXIVPacketBase::setTargetActor( targetId );
  }
};

}
}
}
}

#endif //SAPPHIRE_EFFECTPACKET_H
