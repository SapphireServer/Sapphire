#ifndef _SERVERNOTICEPACKET_H
#define _SERVERNOTICEPACKET_H

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The Ping response packet.
  */
  class ServerNoticePacket :
    public ZoneChannelPacket< FFXIVIpcServerNotice >
  {
  public:
    ServerNoticePacket( uint32_t playerId, const std::string& message ) :
      ZoneChannelPacket< FFXIVIpcServerNotice >( playerId, playerId )
    {
      initialize( message );
    };

  private:
    void initialize( const std::string& message )
    {
      strcpy( m_data.message, message.c_str() );
    };
  };

}

#endif /*_SERVERNOTICEPACKET_H*/
