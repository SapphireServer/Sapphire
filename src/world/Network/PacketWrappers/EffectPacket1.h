#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"
#include <string>
#include <cstring>
#include <cassert>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  class EffectPacket1 : public ZoneChannelPacket< FFXIVIpcActionResult1 >
  {
  public:
    EffectPacket1( uint64_t sourceId, uint32_t targetId, uint32_t actionId ) :
      ZoneChannelPacket< FFXIVIpcActionResult1 >( static_cast< uint32_t >( sourceId ), targetId )
    {
      m_data.Flag = 0;
      m_data.ActionKey = actionId;
      m_data.Action = static_cast< uint16_t >( actionId );
      m_data.ActionKind = 1;

      m_data.LockTime = 0.6f;
      m_data.MainTarget = static_cast< uint64_t >( targetId );
      m_data.Target = targetId;

      //m_data.ActionArg = Common::ActionEffectDisplayType::ShowActionName;
      m_data.BallistaEntityId = Common::INVALID_GAME_OBJECT_ID;

      std::memset( &m_data.CalcResult, 0, sizeof( Common::CalcResult ) );
    }

    void addEffect( const Common::CalcResultParam& effect, uint64_t targetId = Common::INVALID_GAME_OBJECT_ID64 )
    {
      std::memcpy( &m_data.CalcResult.CalcResultTg, &effect, sizeof( Common::CalcResultParam ) );
    }

    void setAnimationId( uint16_t animationId )
    {
      m_data.Action = animationId;
    }

    void setDisplayType( Common::ActionEffectDisplayType displayType )
    {
      m_data.ActionArg = displayType;
    }

    void setEffectFlags( uint32_t effectFlags )
    {
      m_data.Flag = effectFlags;
    }

    void setRotation( uint16_t rotation )
    {
      m_data.DirTarget = rotation;
    }

    void setTargetActor( const uint32_t targetId )
    {
      m_data.MainTarget = static_cast< uint64_t >( targetId );

      FFXIVPacketBase::setTargetActor( targetId );
    }

    void setSequence( uint32_t sequence, uint16_t sourceSequence = 0 )
    {
      m_data.RequestId = static_cast< uint32_t >( sourceSequence );
      m_data.ResultId = static_cast< uint32_t>( sequence );
    }
  };

}

