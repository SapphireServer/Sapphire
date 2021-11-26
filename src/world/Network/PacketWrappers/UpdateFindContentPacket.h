#pragma once

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief Packet to display a quest specific info message.
  */
  class UpdateFindContentPacket : public ZoneChannelPacket< FFXIVIpcUpdateFindContent >
  {
  public:
    UpdateFindContentPacket( uint32_t playerId, uint16_t terriId, uint32_t kind, uint32_t value1 = 0, uint32_t value2 = 0, uint32_t value3 = 0, uint32_t value4 = 0 ) :
      ZoneChannelPacket< FFXIVIpcUpdateFindContent >( playerId, playerId )
    {
      initialize( terriId, kind, value1, value2, value3, value4 );
    };

  private:
    void initialize( uint16_t terriId, uint32_t kind, uint32_t value1, uint32_t value2, uint32_t value3, uint32_t value4 )
    {
      m_data.territoryType = terriId;
      m_data.kind = kind;
      m_data.value1 = value1;
      m_data.value2 = value2;
      m_data.value3 = value3;
      m_data.value4 = value4;
    };
  };

  template< typename... Args >
  std::shared_ptr< UpdateFindContentPacket > makeUpdateFindContent( Args... args )
  {
    return std::make_shared< UpdateFindContentPacket >( args... );
  }
}
