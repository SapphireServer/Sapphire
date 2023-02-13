#pragma once

#include <Network/GamePacket.h>
#include <StatusEffect/StatusEffect.h>
#include <Util/Util.h>
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

      auto statusMap = player.getStatusEffectMap();

      int i = 0;
      for( const auto& [ key, val ] : statusMap )
      {
        m_data.effect[ i ].Id = val->getId();
        m_data.effect[ i ].Source = val->getSrcActorId();
        m_data.effect[ i ].SystemParam = val->getParam();
        m_data.effect[ i ].Time = ( val->getDuration() - ( Common::Util::getTimeMs() - val->getStartTimeMs() ) ) / 1000.f;

        i++;
      }
    };
  };
  template< typename... Args >
  std::shared_ptr< HudParamPacket > makeHudParam( Args... args )
  {
    return std::make_shared< HudParamPacket >( args... );
  }
}