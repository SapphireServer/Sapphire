#pragma once

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{
  class InviteUpdatePacket : public ZoneChannelPacket< FFXIVIpcInviteUpdate >
  {
  public:
    InviteUpdatePacket( Entity::Player& player, uint32_t inviteTime, uint8_t authType, uint8_t inviteCount, uint8_t result ) :
      ZoneChannelPacket< FFXIVIpcInviteUpdate >( player.getId(), player.getId() )
    {
      initialize( player, inviteTime, authType, inviteCount, result );
    };

  private:
    void initialize( Entity::Player& player, uint32_t inviteTime, uint8_t authType, uint8_t inviteCount, uint8_t result )
    {
      m_data.InviteCharacterID = player.getCharacterId();
      m_data.InviteTime = inviteTime;
      m_data.AuthType = authType;
      m_data.InviteCount = inviteCount;
      m_data.Result = result;
      m_data.Identity = player.getGender();
      strcpy( m_data.InviteName, player.getName().c_str() );
    };
  };
}
