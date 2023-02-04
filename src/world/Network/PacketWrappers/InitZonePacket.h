#pragma once

#include <Network/GamePacket.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Ping response packet.
  */
  class InitZonePacket : public ZoneChannelPacket< FFXIVIpcInitZone >
  {
  public:
    InitZonePacket( Entity::Player& player, Territory& territory ) : ZoneChannelPacket< FFXIVIpcInitZone >( player.getId(), player.getId() )
    {
      initialize( player, territory );
    };

  private:
    void initialize( Entity::Player& player, Territory& territory )
    {
      m_data.ZoneId = territory.getTerritoryTypeId();
      m_data.TerritoryType = territory.getTerritoryTypeId();
      m_data.TerritoryIndex = 0;
      m_data.WeatherId = static_cast< uint8_t >( territory.getCurrentWeather() );
      m_data.Flag = 1;
      m_data.FestivalEid0 = territory.getCurrentFestival().first;
      m_data.FestivalPid0 = territory.getCurrentFestival().second;
      //m_data.LayoutId = 85915;
      //m_data.LayerSetId = 115133;
      m_data.Pos[ 0 ] = player.getPos().x;
      m_data.Pos[ 1 ] = player.getPos().y;
      m_data.Pos[ 2 ] = player.getPos().z;
    };
  };
  template< typename... Args >
  std::shared_ptr< InitZonePacket > makeInitZone( Args... args )
  {
    return std::make_shared< InitZonePacket >( args... );
  }
}