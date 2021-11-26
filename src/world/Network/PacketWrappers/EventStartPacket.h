#ifndef _EVENTSTART_H
#define _EVENTSTART_H

#include <Network/GamePacket.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The packet sent to start an event.
  */
  class EventStartPacket : public ZoneChannelPacket< FFXIVIpcEventStart >
  {
  public:
    EventStartPacket( uint32_t playerId,
                      uint64_t targetId,
                      uint32_t eventId,
                      uint8_t param1 = 0,
                      uint8_t param2 = 0,
                      uint32_t param3 = 0 ) :
      ZoneChannelPacket< FFXIVIpcEventStart >( playerId, playerId )
    {
      initialize( targetId, eventId, param1, param2, param3 );
    };

  private:
    void initialize( uint64_t actorId,
                     uint32_t eventId,
                     uint8_t param1,
                     uint8_t param2,
                     uint32_t param3 )
    {
      m_data.targetId = actorId;
      m_data.handlerId = eventId;
      m_data.event = param1;
      m_data.flags = param2;
      m_data.eventArg = param3;

    };
  };

}
#endif /*_EVENTSTART_H*/
