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
  class ChatToChannelPacket : public ChatChannelPacket< FFXIVChatToChannel >
  {
  public:
    ChatToChannelPacket( Entity::Player& target,
                         Entity::Player& sender,
                         uint64_t channelId,
                         const std::string& msg ) :
      ChatChannelPacket< FFXIVChatToChannel >( target.getId(), target.getId() )
    {
      initialize( sender, channelId, msg );
    };

  private:
    void initialize( Entity::Player& sender, uint64_t channelId, const std::string& msg )
    {
      strcpy( m_data.message, msg.c_str() );
      strcpy( m_data.speakerName, sender.getName().c_str() );

      m_data.channelID = channelId;

      m_data.speakerCharacterID = sender.getCharacterId();
      m_data.speakerEntityID = sender.getId();

      m_data.type = 0;
    };
  };

}