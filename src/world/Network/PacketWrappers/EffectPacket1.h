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

    void addTargetEffect( const Common::CalcResultParam& effect )
    {
      std::memcpy( &m_data.CalcResult.CalcResultTg[ m_targetEffectCount++ ], &effect, sizeof( Common::CalcResultParam ) );
    }

    void addSourceEffect( const Common::CalcResultParam& effect )
    {
      std::memcpy( &m_data.CalcResult.CalcResultCt[ m_sourceEffectCount++ ], &effect, sizeof( Common::CalcResultParam ) );
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

    void setTargetActor( const uint32_t targetId )
    {
      m_data.MainTarget = static_cast< uint64_t >( targetId );

      FFXIVPacketBase::setTargetActor( targetId );
    }

    void setRequestId( uint16_t requestId )
    {
      m_data.RequestId = static_cast< uint32_t >( requestId );
    }

    void setResultId( uint32_t resultId )
    {
      m_data.ResultId = resultId;
    }

  private:
    uint8_t m_targetEffectCount{ 0 };
    uint8_t m_sourceEffectCount{ 0 };
  };

}

