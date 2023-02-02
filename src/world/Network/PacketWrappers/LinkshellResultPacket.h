#pragma once

#include <Network/GamePacket.h>
#include "Forwards.h"
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Common.h>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  class LinkshellResultPacket : public ZoneChannelPacket< FFXIVIpcLinkshellResult >
  {
  public:
    enum UpdateStatus : uint8_t
    {
      None = 0,
      Execute = 10,
      Target = 11,
      Member = 12,
    };

    LinkshellResultPacket( Entity::Player& player, uint64_t linkshellId, uint64_t targetId,
                           uint16_t upPacketNo, uint32_t result, uint8_t updateStatus, const std::string& lsName, const std::string& targetName ) :

      ZoneChannelPacket< FFXIVIpcLinkshellResult >( player.getId(), player.getId() )
    {
      initialize( player, linkshellId, targetId, upPacketNo, result, updateStatus, lsName, targetName );
    };

  private:
    void initialize( Entity::Player& player, uint64_t linkshellId, uint64_t targetId,
                     uint16_t upPacketNo, uint32_t result, uint8_t updateStatus, const std::string& lsName, const std::string& targetName )
    {
      m_data.LinkshellID = linkshellId;
      m_data.Identity = 0xFF;
      m_data.UpPacketNo = static_cast< uint32_t >( upPacketNo );
      m_data.Result = result;
      m_data.UpdateStatus = updateStatus;
      m_data.TargetCharacterID = targetId;
      strcpy( m_data.LinkshellName, lsName.c_str() );
      strcpy( m_data.TargetName, targetName.c_str() );
    };
  };
  template< typename... Args >
  std::shared_ptr< LinkshellResultPacket > makeLinkshellResult( Args... args )
  {
    return std::make_shared< LinkshellResultPacket >( args... );
  }
}
