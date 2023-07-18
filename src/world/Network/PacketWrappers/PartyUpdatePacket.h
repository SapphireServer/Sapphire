#pragma once

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{
  class PartyUpdatePacket : public ZoneChannelPacket< FFXIVIpcPartyUpdate >
  {
  public:
    PartyUpdatePacket( Entity::Player& executePlayer, Entity::Player& targetPlayer, uint8_t updateStatus, uint8_t count ) :
      ZoneChannelPacket< FFXIVIpcPartyUpdate >( executePlayer.getId(), executePlayer.getId() )
    {
      initialize( executePlayer, targetPlayer, updateStatus, count );
    };

    PartyUpdatePacket( Entity::Player& executePlayer, uint8_t updateStatus, uint8_t count ) :
      ZoneChannelPacket< FFXIVIpcPartyUpdate >( executePlayer.getId(), executePlayer.getId() )
    {
      initialize( executePlayer, updateStatus, count );
    };

    PartyUpdatePacket( const Entity::PlayerPtr& executePlayer, const Entity::PlayerPtr& targetPlayer, uint8_t updateStatus, uint8_t count ) :
      ZoneChannelPacket< FFXIVIpcPartyUpdate >( executePlayer->getId(), executePlayer->getId() )
    {
      initialize( executePlayer, targetPlayer, updateStatus, count );
    };

  private:
    void initialize( Entity::Player& executePlayer, Entity::Player& targetPlayer, uint8_t updateStatus, uint8_t partySize )
    {
      m_data.executeContentId = executePlayer.getContentId();
      m_data.targetContentId = targetPlayer.getContentId();
      m_data.executeGender = executePlayer.getGender();
      m_data.targetGender = targetPlayer.getGender();
      m_data.updateStatus = updateStatus;
      m_data.partySize = partySize;
      strcpy( m_data.executeName, executePlayer.getName().c_str() );
      strcpy( m_data.targetName, targetPlayer.getName().c_str() );
    };

    void initialize( Entity::Player& executePlayer, uint8_t updateStatus, uint8_t partySize )
    {
      m_data.executeContentId = executePlayer.getContentId();
      m_data.targetContentId = 0;
      m_data.executeGender = executePlayer.getGender();
      m_data.targetGender = 0;
      m_data.updateStatus = updateStatus;
      m_data.partySize = partySize;
      strcpy( m_data.targetName, executePlayer.getName().c_str() );
    };

    void initialize( const Entity::PlayerPtr& executePlayer, const Entity::PlayerPtr& targetPlayer, uint8_t updateStatus, uint8_t partySize )
    {
      if( targetPlayer )
      {
        m_data.targetContentId = targetPlayer->getContentId();
        m_data.targetGender = targetPlayer->getGender();
        strcpy( m_data.targetName, targetPlayer->getName().c_str() );
      }

      if( executePlayer )
      {
        m_data.executeContentId = executePlayer->getContentId();
        m_data.executeGender = executePlayer->getGender();
        strcpy( m_data.executeName, executePlayer->getName().c_str() );
      }

      m_data.updateStatus = updateStatus;
      m_data.partySize = partySize;

    };

  };

  template< typename... Args >
  std::shared_ptr< PartyUpdatePacket > makePartyUpdate( Args... args )
  {
    return std::make_shared< PartyUpdatePacket >( args... );
  }

}
