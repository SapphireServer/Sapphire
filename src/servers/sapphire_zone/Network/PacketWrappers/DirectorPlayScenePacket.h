#ifndef _DIRECTORPLAYSCENE_H
#define _DIRECTORPLAYSCENE_H

#include <common/Network/GamePacketNew.h>
#include "Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The packet sent to play an event.
*/
class DirectorPlayScenePacket :  public ZoneChannelPacket< FFXIVIpcDirectorPlayScene >
{
public:
   DirectorPlayScenePacket( uint32_t playerId,
                    uint64_t actorId,
                    uint32_t eventId,
                    uint16_t scene,
                    uint32_t flags,
                    uint8_t param3,
                    uint32_t param4 = 0,
                    uint32_t param5 = 0 ) :
           ZoneChannelPacket< FFXIVIpcDirectorPlayScene >( playerId, playerId )
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
}
}
}

#endif /*_EVENTPLAY_H*/
