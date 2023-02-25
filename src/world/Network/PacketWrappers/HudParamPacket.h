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

    HudParamPacket( Entity::Chara& chara ) : ZoneChannelPacket< FFXIVIpcHudParam >( chara.getId(), chara.getId() )
    {
      initialize( chara );
    };

  private:
    void initialize( Entity::Chara& chara )
    {
      m_data.ClassJob = static_cast< uint8_t >( chara.getClass() );
      m_data.Lv = chara.getLevel();
      m_data.OrgLv = chara.getLevel();
      m_data.LvSync = 0; //player.getLevelSync();
      m_data.Hp = chara.getHp();
      m_data.Mp = chara.getMp();
      m_data.Tp = chara.getTp();
      m_data.HpMax = chara.getMaxHp();
      m_data.MpMax = chara.getMaxMp();

      for( int i = 0; i < 30; ++i )
        m_data.effect[ i ] = { 0, 0, 0.0f, 0 };

      auto statusMap = chara.getStatusEffectMap();

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