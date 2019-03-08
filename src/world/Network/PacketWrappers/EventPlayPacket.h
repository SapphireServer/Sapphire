#ifndef _EVENTPLAY_H
#define _EVENTPLAY_H

#include <Network/GamePacket.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The packet sent to play an event.
  */
  class EventPlayPacket : public ZoneChannelPacket< FFXIVIpcEventPlay >
  {
  public:
    EventPlayPacket( uint32_t playerId,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t scene,
                     uint32_t flags,
                     uint8_t param3,
                     uint32_t param4 = 0,
                     uint32_t param5 = 0 ) :
      ZoneChannelPacket< FFXIVIpcEventPlay >( playerId, playerId )
    {
      initialize( actorId, eventId, scene, flags, param3, param4, param5 );
    };

  private:
    void initialize( uint64_t actorId,
                     uint32_t eventId,
                     uint16_t scene,
                     uint32_t flags,
                     uint8_t param3,
                     uint32_t param4,
                     uint32_t param5 )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = scene;
      m_data.flags = flags;
      m_data.param3 = param3;
      m_data.param4 = param4;
      m_data.param5 = param5;
    };
  };

}

#endif /*_EVENTPLAY_H*/
