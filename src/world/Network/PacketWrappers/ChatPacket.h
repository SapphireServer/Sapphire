#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"


namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Chat packet.
  */
  class ChatPacket : public ZoneChannelPacket< FFXIVIpcChat >
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
      m_data.type = static_cast< uint16_t >( chatType );
      m_data.characterId = player.getCharacterId();
      m_data.entityId = player.getId();
      strcpy( reinterpret_cast< char* >( m_data.speakerName ), player.getName().c_str() );
      strcpy( reinterpret_cast< char* >( m_data.message ), msg.c_str() );
    };
  };

}