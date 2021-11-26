#pragma once

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

    uint64_t ExecuteCharacterID;
    uint64_t TargetCharacterID;
    uint8_t ExecuteIdentity;
    uint8_t TargetIdentity;
    uint8_t UpdateStatus;
    uint8_t Count;
    char ExecuteCharacterName[32];
    char TargetCharacterName[32];

  class PcPartyUpdatePacket : public ZoneChannelPacket< FFXIVIpcPcPartyUpdate >
  {
  public:
    PcPartyUpdatePacket( Entity::Player& executePlayer, Entity::Player& targetPlayer, uint8_t updateStatus, uint8_t count ) :
      ZoneChannelPacket< FFXIVIpcPcPartyUpdate >( executePlayer.getId(), executePlayer.getId() )
    {
      initialize( executePlayer, targetPlayer, updateStatus, count );
    };

    PcPartyUpdatePacket( Entity::Player& executePlayer, uint8_t updateStatus, uint8_t count ) :
      ZoneChannelPacket< FFXIVIpcPcPartyUpdate >( executePlayer.getId(), executePlayer.getId() )
    {
      initialize( executePlayer, updateStatus, count );
    };

    PcPartyUpdatePacket( const Entity::PlayerPtr& executePlayer, const Entity::PlayerPtr& targetPlayer, uint8_t updateStatus, uint8_t count ) :
      ZoneChannelPacket< FFXIVIpcPcPartyUpdate >( executePlayer->getId(), executePlayer->getId() )
    {
      initialize( executePlayer, targetPlayer, updateStatus, count );
    };

  private:
    void initialize( Entity::Player& executePlayer, Entity::Player& targetPlayer, uint8_t updateStatus, uint8_t count )
    {
      m_data.ExecuteCharacterID = executePlayer.getCharacterId();
      m_data.TargetCharacterID = targetPlayer.getCharacterId();
      m_data.ExecuteIdentity = executePlayer.getGender();
      m_data.TargetIdentity = targetPlayer.getGender();
      m_data.UpdateStatus = updateStatus;
      m_data.Count = count;
      strcpy( m_data.ExecuteCharacterName, executePlayer.getName().c_str() );
      strcpy( m_data.TargetCharacterName, targetPlayer.getName().c_str() );
    };

    void initialize( Entity::Player& executePlayer, uint8_t updateStatus, uint8_t count )
    {
      m_data.ExecuteCharacterID = executePlayer.getCharacterId();
      m_data.TargetCharacterID = 0;
      m_data.ExecuteIdentity = executePlayer.getGender();
      m_data.TargetIdentity = 0;
      m_data.UpdateStatus = updateStatus;
      m_data.Count = count;
      strcpy( m_data.TargetCharacterName, executePlayer.getName().c_str() );
    };

    void initialize( const Entity::PlayerPtr& executePlayer, const Entity::PlayerPtr& targetPlayer, uint8_t updateStatus, uint8_t count )
    {
      if( targetPlayer )
      {
        m_data.TargetCharacterID = targetPlayer->getCharacterId();
        m_data.TargetIdentity = targetPlayer->getGender();
        strcpy( m_data.TargetCharacterName, targetPlayer->getName().c_str() );
      }

      if( executePlayer )
      {
        m_data.ExecuteCharacterID = executePlayer->getCharacterId();
        m_data.ExecuteIdentity = executePlayer->getGender();
        strcpy( m_data.ExecuteCharacterName, executePlayer->getName().c_str() );
      }

      m_data.UpdateStatus = updateStatus;
      m_data.Count = count;

    };

  };

  template< typename... Args >
  std::shared_ptr< PcPartyUpdatePacket > makePcPartyUpdate( Args... args )
  {
    return std::make_shared< PcPartyUpdatePacket >( args... );
  }

}
