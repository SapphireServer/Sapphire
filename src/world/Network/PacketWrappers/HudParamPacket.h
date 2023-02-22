#pragma once

#include <Network/GamePacket.h>
#include <StatusEffect/StatusEffect.h>
#include <Util/Util.h>
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief HUD stats packet.
  */
  class HudParamPacket : public ZoneChannelPacket< FFXIVIpcHudParam >
  {
  public:
    HudParamPacket( Entity::Player& player ) : ZoneChannelPacket< FFXIVIpcHudParam >( player.getId(), player.getId() )
    {
      initialize( player );
    };

    HudParamPacket( Entity::BNpc& bnpc ) : ZoneChannelPacket< FFXIVIpcHudParam >( bnpc.getId(), bnpc.getId() )
    {
      initialize( bnpc );
    };

  private:
    void initialize( Entity::Player& player )
    {
      m_data.ClassJob = static_cast< uint8_t >( player.getClass() );
      m_data.Lv = player.getLevel();
      m_data.OrgLv = player.getLevel();
      m_data.LvSync = 0; //player.getLevelSync();
      m_data.Hp = player.getHp();
      m_data.Mp = player.getMp();
      m_data.Tp = player.getTp();
      m_data.HpMax = player.getMaxHp();
      m_data.MpMax = player.getMaxMp();

      for( int i = 0; i < 30; ++i )
        m_data.effect[ i ] = { 0, 0, 0.0f, 0 };

      auto statusMap = player.getStatusEffectMap();

      int i = 0;
      for( const auto& [ key, val ] : statusMap )
      {
        auto timeLeft = static_cast< int32_t >( val->getDuration() - ( Common::Util::getTimeMs() - val->getStartTimeMs() ) );
        m_data.effect[ i ].Id = val->getId();
        m_data.effect[ i ].Source = val->getSrcActorId();
        m_data.effect[ i ].SystemParam = val->getParam();
        if( timeLeft <= 0 )
          m_data.effect[ i ].Time = 0.f;
        else
          m_data.effect[ i ].Time = timeLeft / 1000.f;

        i++;
      }
    }
    void initialize( Entity::BNpc& bnpc )
    {
      m_data.ClassJob = static_cast< uint8_t >( bnpc.getClass() );
      m_data.Lv = bnpc.getLevel();
      m_data.OrgLv = bnpc.getLevel();
      m_data.LvSync = 0;
      m_data.Hp = bnpc.getHp();
      m_data.Mp = bnpc.getMp();
      m_data.Tp = bnpc.getTp();
      m_data.HpMax = bnpc.getMaxHp();
      m_data.MpMax = bnpc.getMaxMp();

      for( int i = 0; i < 30; ++i )
        m_data.effect[ i ] = { 0, 0, 0.0f, 0 };

      auto statusMap = bnpc.getStatusEffectMap();

      int i = 0;
      for( const auto& [ key, val ] : statusMap )
      {
        auto timeLeft = static_cast< int32_t >( val->getDuration() - ( Common::Util::getTimeMs() - val->getStartTimeMs() ) );
        m_data.effect[ i ].Id = val->getId();
        m_data.effect[ i ].Source = val->getSrcActorId();
        m_data.effect[ i ].SystemParam = val->getParam();
        if( timeLeft <= 0 )
          m_data.effect[ i ].Time = 0.f;
        else
          m_data.effect[ i ].Time = timeLeft / 1000.f;

        i++;
      }
    }
  };
  template< typename... Args >
  std::shared_ptr< HudParamPacket > makeHudParam( Args... args )
  {
    return std::make_shared< HudParamPacket >( args... );
  }
}