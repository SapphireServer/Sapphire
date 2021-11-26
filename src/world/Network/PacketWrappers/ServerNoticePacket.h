#ifndef _SERVERNOTICEPACKET_H
#define _SERVERNOTICEPACKET_H

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Ping response packet.
  */
  class ServerNoticePacket : public ZoneChannelPacket< FFXIVIpcSendSystemMessage >
  {
  public:
    ServerNoticePacket( uint32_t playerId, const std::string& message ) :
      ZoneChannelPacket< FFXIVIpcSendSystemMessage >( playerId, playerId )
    {
      initialize( message );
    };

  private:
    void initialize( const std::string& message )
    {
      strcpy( m_data.Message, message.c_str() );
    };
  };

}

#endif /*_SERVERNOTICEPACKET_H*/
