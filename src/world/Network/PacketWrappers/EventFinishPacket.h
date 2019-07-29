#ifndef _EVENTFINISH_H
#define _EVENTFINISH_H

#include <Network/GamePacket.h>

namespace Sapphire::Network::Packets::Server
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
      m_data.eventId = eventId;
      m_data.param1 = param1;
      m_data.param2 = 1;
      m_data.param3 = param3;

    };
  };

}

#endif /*_EVENTFINISH_H*/
