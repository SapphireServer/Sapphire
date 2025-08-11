#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Util/UtilMath.h>
#include "Forwards.h"
#include <string>
#include <cstring>
#include <cassert>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  class EffectPacket : public ZoneChannelPacket< FFXIVIpcActionResult >
  {
  public:
    EffectPacket( uint64_t sourceId, uint32_t mainTarget, uint32_t actionId ) :
      ZoneChannelPacket< FFXIVIpcActionResult >( static_cast< uint32_t >( sourceId ), mainTarget )
    {
      m_data.Flag = 0;
      m_data.ActionKey = actionId;
      m_data.Action = static_cast< uint16_t >( actionId );
      m_data.ActionKind = 1;

      m_data.MainTarget = static_cast< uint64_t >( mainTarget );
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

    void setActionId( uint16_t actionId )
    {
      m_data.Action = actionId;
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

    void setRequestId( uint16_t requestId )
    {
      m_data.RequestId = static_cast< uint32_t >( requestId );
    }

    void setResultId( uint32_t resultId )
    {
      m_data.ResultId = static_cast< uint32_t >( resultId );
    }

    void setTargetPosition( Common::FFXIVARR_POSITION3& pos )
    {
      m_data.TargetPos[ 0 ] = Common::Util::floatToUInt16( pos.x );
      m_data.TargetPos[ 1 ] = Common::Util::floatToUInt16( pos.y );
      m_data.TargetPos[ 2 ] = Common::Util::floatToUInt16( pos.z );
    }
  private:
    uint8_t m_targetEffectCount{ 0 };
    uint8_t m_sourceEffectCount{ 0 };
  };

  template< typename... Args >
  std::shared_ptr< EffectPacket > makeEffectPacket( Args... args )
  {
    return std::make_shared< EffectPacket >( args... );
  }

}