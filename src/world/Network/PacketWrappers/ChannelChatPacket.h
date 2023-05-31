#pragma once

#include "Forwards.h"
#include "Actor/Player.h"
#include <Network/GamePacket.h>
#include <Network/PacketDef/Chat/ServerChatDef.h>

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The Chat packet.
  */
  class ChannelChatPacket : public ChatChannelPacket< FFXIVIpcChannelChat >
  {
  public:
    ChannelChatPacket( Entity::Player& target,
                         Entity::Player& sender,
                         uint64_t channelId,
                         const std::string& msg ) :
      ChatChannelPacket< FFXIVIpcChannelChat >( target.getId(), target.getId() )
    {
      initialize( sender, channelId, msg );
    };

  private:
    void initialize( Entity::Player& sender, uint64_t channelId, const std::string& msg )
    {
      strcpy( m_data.message, msg.c_str() );
      strcpy( m_data.name, sender.getName().c_str() );

      m_data.channelId = channelId;

      m_data.contentId = sender.getContentId();
      m_data.charaId = sender.getId();

      m_data.type = 0;
    };
  };

}