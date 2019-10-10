#ifndef SAPPHIRE_EFFECTPACKET_H
#define SAPPHIRE_EFFECTPACKET_H

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"
#include <string>
#include <cstring>
#include <cassert>

namespace Sapphire::Network::Packets::Server
{

  class EffectPacket : public ZoneChannelPacket< FFXIVIpcEffect >
  {
  public:
    EffectPacket( uint64_t sourceId, uint32_t targetId, uint32_t actionId ) :
      ZoneChannelPacket< FFXIVIpcEffect >( static_cast< uint32_t >( sourceId ), targetId )
    {
      m_data.effectCount = 0;
      m_data.actionId = actionId;
      m_data.actionAnimationId = static_cast< uint16_t >( actionId );

      m_data.animationTargetId = targetId;
      m_data.effectTargetId = targetId;

      m_data.effectDisplayType = Common::ActionEffectDisplayType::ShowActionName;
    }

    void addEffect( const Common::EffectEntry& effect )
    {
      assert( m_data.effectCount <= 8 );

      std::memset( m_data.effects, 0, sizeof( Common::EffectEntry ) * 8 );
      std::memcpy( &m_data.effects[ m_data.effectCount * 8 ], &effect, sizeof( Common::EffectEntry ) );
      m_data.effectCount++;
    }

    void setAnimationId( uint16_t animationId )
    {
      m_data.actionAnimationId = animationId;
    }

    void setDisplayType( Common::ActionEffectDisplayType displayType )
    {
      m_data.effectDisplayType = displayType;
    }

    void setEffectFlags( uint32_t effectFlags )
    {
      m_data.effectFlags = effectFlags;
    }

    void setRotation( uint16_t rotation )
    {
      m_data.rotation = rotation;
    }

    void setTargetActor( const uint32_t targetId )
    {
      m_data.animationTargetId = targetId;
      m_data.effectTargetId = targetId;

      FFXIVPacketBase::setTargetActor( targetId );
    }

    void setSequence( uint32_t sequence, uint16_t sourceSequence = 0 )
    {
      m_data.sequence = sequence;
      m_data.sourceSequence = sourceSequence;
    }
  };

}

#endif //SAPPHIRE_EFFECTPACKET_H
