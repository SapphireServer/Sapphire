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
      ZoneChannelPacket< FFXIVIpcEffect >( sourceId, targetId )
   {
      m_data.actionId = actionId;
      m_data.actionAnimationId = static_cast< uint16_t >( actionId );

      m_data.animationTargetId = targetId;
      m_data.effectTargetId = targetId;
      
      m_data.effectDisplayType = Common::ActionEffectDisplayType::ShowActionName;
   }

   void addEffect( const Server::EffectEntry& effect )
   {
      assert( m_data.effectCount <= 8 );

      std::memcpy( &m_data.effects[m_data.effectCount++], &effect, sizeof( Server::EffectEntry ) );
   }

   void setAnimationId( const uint16_t animationId )
   {
      m_data.actionAnimationId = animationId;
   }

   void setEffectFlags( const uint32_t effectFlags )
   {
      m_data.effectFlags = effectFlags;
   }

   void setRotation( const uint16_t rotation )
   {
      m_data.rotation = rotation;
   }

   void setTargetActor( const uint32_t targetId )
   {
      m_data.animationTargetId = targetId;
      m_data.effectTargetId = targetId;

      FFXIVPacketBase::setTargetActor( targetId );
   }
};

}
}
}
}

#endif //SAPPHIRE_EFFECTPACKET_H
