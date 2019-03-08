#ifndef _DIRECTORPLAYSCENE_H
#define _DIRECTORPLAYSCENE_H

#include <Network/GamePacket.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The packet sent to play an event.
  */
  class DirectorPlayScenePacket : public ZoneChannelPacket< FFXIVIpcDirectorPlayScene >
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
      m_data.unknown[ 0 ] = 0x05;
      m_data.unknown[ 4 ] = 0x22;
      m_data.unknown[ 5 ] = 0xD6;
      m_data.unknown[ 6 ] = 0x62;
      m_data.unknown[ 7 ] = 0x59;
      m_data.unknown[ 0x14 ] = 0x08;
      m_data.unknown[ 0x15 ] = 0x02;

      // time remaining in sec
      m_data.unknown[ 0x18 ] = 0x19;
      m_data.unknown[ 0x19 ] = 0x14;

      m_data.unknown[ 0x1C ] = 0x23;
      m_data.unknown[ 0x20 ] = 0x40;
      m_data.unknown[ 0x24 ] = 0x80;
    };
  };

}

#endif /*_EVENTPLAY_H*/
