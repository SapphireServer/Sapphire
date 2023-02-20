#pragma once

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief Packet sent to set a players state, this impacts which actions he can perform.
  */
  class ConditionPacket : public ZoneChannelPacket< FFXIVIpcCondition >
  {
  public:
    ConditionPacket( Entity::Player& player ) :
      ZoneChannelPacket< FFXIVIpcCondition >( player.getId(), player.getId() )
    {
      initialize( player.getStateFlags().data() );
    }

    ConditionPacket( Entity::Player& player, std::vector< Common::PlayerCondition > flags ) :
      ZoneChannelPacket< FFXIVIpcCondition >( player.getId(), player.getId() )
    {
      uint8_t newFlags[ 12 ];
      memset( newFlags, 0, 12 );

      for( auto& flag : flags )
      {
        int32_t iFlag = static_cast< uint32_t >( flag );
        uint8_t index = iFlag / 8;
        uint8_t bitIndex = iFlag % 8;

        uint8_t value = 1 << bitIndex;

        newFlags[ index ] |= value;
      }

      initialize( newFlags );
    }

  private:
    void initialize( const uint8_t* flags )
    {
      memcpy( m_data.flags, flags, 12 );
    };
  };

}
