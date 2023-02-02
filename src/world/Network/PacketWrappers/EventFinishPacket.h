#pragma once

#include <Network/GamePacket.h>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The packet sent to finish an event.
  */
  class EventFinishPacket : public ZoneChannelPacket< FFXIVIpcEventFinish >
  {
  public:
    EventFinishPacket( uint32_t playerId,
                       uint32_t eventId,
                       uint8_t param1,
                       uint32_t param3 ) :
      ZoneChannelPacket< FFXIVIpcEventFinish >( playerId, playerId )
    {
      initialize( eventId, param1, param3 );
    };

  private:
    void initialize( uint32_t eventId,
                     uint8_t param1,
                     uint32_t param3 )
    {
      m_data.handlerId = eventId;
      m_data.event = param1;
      m_data.result = 1;
      m_data.eventArg = param3;

    };
  };

}