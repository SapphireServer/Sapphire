#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"
#include <string>
#include <cstring>
#include <cassert>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  class EffectPacket : public ZoneChannelPacket< FFXIVIpcActionResult >
  {
  public:
    EffectPacket( uint64_t sourceId, uint32_t actionId ) :
      ZoneChannelPacket< FFXIVIpcActionResult >( static_cast< uint32_t >( sourceId ) )
    {
      m_data.Flag = 0;
      m_data.ActionKey = actionId;
      m_data.Action = static_cast< uint16_t >( actionId );
      m_data.ActionKind = 1;

      m_data.MainTarget = Common::INVALID_GAME_OBJECT_ID;
      m_data.BallistaEntityId = Common::INVALID_GAME_OBJECT_ID;

      m_data.LockTime = 0.6f;

      m_data.TargetCount = 0;

      std::memset( m_data.CalcResult, 0, sizeof( Common::CalcResult ) * 16 );
    }

    void addTargetEffect( const Common::CalcResultParam& effect, uint64_t targetId = Common::INVALID_GAME_OBJECT_ID64 )
    {
      std::memcpy( &m_data.CalcResult[ m_data.TargetCount ].CalcResultTg[ m_targetEffectCount++ ], &effect, sizeof( Common::CalcResultParam ) );

      // iterate and see if we already have this target added
      bool targetAlreadyAdded = false;
      for( int i = 0; i < sizeof( m_data.Target ) / sizeof( uint64_t ); ++i )
      {
        if( m_data.Target[ i ] == targetId )
        {
          targetAlreadyAdded = true;
          break;
        }
      }

      m_data.Target[ m_data.TargetCount ] = targetId;

      if( !targetAlreadyAdded )
        m_data.TargetCount++;
    }

    void addSourceEffect( const Common::CalcResultParam& effect )
    {
      // we associate the source effect with the current target index set
      std::memcpy( &m_data.CalcResult[ m_data.TargetCount - 1 ].CalcResultCt[ m_sourceEffectCount++ ], &effect, sizeof( Common::CalcResultParam ) );
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
  private:
    uint8_t m_targetEffectCount{ 0 };
    uint8_t m_sourceEffectCount{ 0 };
  };

}