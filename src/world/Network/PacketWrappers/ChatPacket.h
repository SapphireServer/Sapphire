#ifndef _CHATPACKET_H
#define _CHATPACKET_H

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"


namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The Chat packet.
  */
  class ChatPacket :  public ZoneChannelPacket< FFXIVIpcChat >
  {
  public:
    ChatPacket( Entity::Player& player, Common::ChatType chatType, const std::string& msg ) :
      ZoneChannelPacket< FFXIVIpcChat >( player.getId(), player.getId() )
    {
      initialize( player, chatType, msg );
    };

  private:
    void initialize( Entity::Player& player, Common::ChatType chatType, const std::string& msg )
    {
      m_data.chatType = chatType;
      strcpy( m_data.name, player.getName().c_str() );
      strcpy( m_data.msg, msg.c_str() );
    };
  };

}

#endif /*_CHATPACKET_H*/
