#include <Common.h>
#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <Service.h>

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"

#include "PartyMgr.h"
#include "ServerMgr.h"
#include "ChatChannelMgr.h"
#include "PlayerMgr.h"

#include "Session.h"

#include "Actor/Player.h"

#include "Network/PacketWrappers/PartyUpdatePacket.h"

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

void PartyMgr::onJoin( Entity::Player& joiner, Entity::Player& inviter )
{
  auto& server = Common::Service< World::ServerMgr >::ref();
  auto& ccMgr = Common::Service< World::Manager::ChatChannelMgr >::ref();

  auto& inviteePlayer = joiner;
  auto& invitingPlayer = inviter;

  if( inviteePlayer.getPartyId() != 0 )
  {
    Logger::error( "Player#{} already in a party, cannot be invited!!", inviteePlayer.getId() );
    return;
  }

  uint64_t partyId;
  // if there is no party yet, one has to be created
  PartyPtr party;
  if( inviteePlayer.getPartyId() == 0 && invitingPlayer.getPartyId() == 0 )
  {
    partyId = createParty();
    party = getParty( partyId );
    assert( party );

    inviteePlayer.setPartyId( partyId );
    inviteePlayer.addOnlineStatus( Common::OnlineStatus::PartyMember );
    invitingPlayer.setPartyId( partyId );
    invitingPlayer.addOnlineStatus( Common::OnlineStatus::PartyLeader );

    ccMgr.addToChannel( party->ChatChannel, invitingPlayer );
    ccMgr.addToChannel( party->ChatChannel, inviteePlayer );

    party->MemberId.push_back( invitingPlayer.getId() );
    party->MemberId.push_back( inviteePlayer.getId() );
    party->PartyCount = 2;
    party->LeaderId = invitingPlayer.getId();
  }
  else if( inviteePlayer.getPartyId() == 0 )
  {
    partyId = invitingPlayer.getPartyId();
    party = getParty( partyId );

    inviteePlayer.setPartyId( partyId );
    inviteePlayer.addOnlineStatus( Common::OnlineStatus::PartyMember );

    ccMgr.addToChannel( party->ChatChannel, inviteePlayer );

    party->MemberId.push_back( inviteePlayer.getId() );
    party->PartyCount++;
  }

  auto pcUpdateParty = makePartyUpdate( invitingPlayer, inviteePlayer, UpdateStatus::JOINED, party->PartyCount );
  auto members = getPartyMembers( *party );
  sendPartyUpdate( *party );
  for( const auto& member : members )
  {
    member->queuePacket( pcUpdateParty );
  }
}

void PartyMgr::onLeave( Sapphire::Entity::Player &leavingPlayer )
{
  auto& server = Common::Service< World::ServerMgr >::ref();

  auto party = getParty( leavingPlayer.getPartyId() );
  assert( party );

  auto leadingPlayer = getPartyLeader( *party );
  assert( leadingPlayer );

  if( !leadingPlayer )
    return;

  if( party->PartyCount == 2 )
  {
    onDisband( *leadingPlayer );
  }
  else
  {
    auto members = getPartyMembers( *party );
    removeMember( *party, leavingPlayer.getAsPlayer() );

    uint32_t newLeaderId = 0;
    for( const auto& member : members )
    {
      if( member->getId() == leavingPlayer.getId() )
      {
        member->removeOnlineStatus( { Common::OnlineStatus::PartyMember,
                                      Common::OnlineStatus::PartyLeader } );

        leavingPlayer.queuePacket( makeZonePacket< FFXIVIpcPartyList >( leavingPlayer.getId() ) );
        member->queuePacket( makePartyUpdate( leadingPlayer, nullptr, UpdateStatus::KICK_SELF, party->PartyCount ) );
      }
      else
      {
        if( leavingPlayer.getId() == party->LeaderId )
        {
          newLeaderId = party->MemberId[ 0 ];
          auto pPlayer = server.getSession( newLeaderId )->getPlayer();
          if( !pPlayer /*|| !pPlayer->isConnected() */)
            continue;
          pPlayer->addOnlineStatus( Common::OnlineStatus::PartyLeader );
          member->queuePacket( makePartyUpdate( leavingPlayer.getAsPlayer(), pPlayer, UpdateStatus::LEAVELEADER_LEAVED_MEMBER, party->PartyCount ) );
        }
        else
        {
          member->queuePacket( makePartyUpdate( leavingPlayer.getAsPlayer(), nullptr, UpdateStatus::LEAVE_MEMBER, party->PartyCount ) );

        }
      }
    }
    if( newLeaderId != 0 )
      party->LeaderId = newLeaderId;
    party->PartyCount--;
    sendPartyUpdate( *party );
  }
}

void PartyMgr::onDisband( Entity::Player& disbandingPlayer )
{
  auto& server = Common::Service< World::ServerMgr >::ref();
  auto party = getParty( disbandingPlayer.getPartyId() );
  assert( party );

  auto members = getPartyMembers( *party );
  for( const auto& member : members )
  {
    removeMember( *party, member );
    member->removeOnlineStatus( { Common::OnlineStatus::PartyMember, Common::OnlineStatus::PartyLeader } );
    member->queuePacket( { makePartyUpdate( disbandingPlayer, disbandingPlayer, UpdateStatus::DISBAND, party->PartyCount ), makeZonePacket< FFXIVIpcPartyList >( member->getId() ) } );
  }

  removeParty( party->PartyID );
}

void PartyMgr::onMoveZone( Sapphire::Entity::Player &movingPlayer )
{
  if( movingPlayer.getPartyId() == 0 )
    return;
  auto party = getParty( movingPlayer.getPartyId() );
  assert( party );
  sendPartyUpdate( *party );
}

void PartyMgr::onMemberDisconnect( Entity::Player& disconnectingPlayer )
{
  if( disconnectingPlayer.getPartyId() == 0 )
    return;

  auto& server = Common::Service< World::ServerMgr >::ref();
  auto party = getParty( disconnectingPlayer.getPartyId() );
  assert( party );
  auto members = getPartyMembers( *party );
  auto pLeader = getPartyLeader( *party );

  bool anyMembersOnline = false;

  for( const auto& member : members )
  {
    if( member/*->isConnected()*/ )
    {
      anyMembersOnline = true;
      break;
    }
  }

  // if there are no party members online, destroy the party
  if( !anyMembersOnline )
    return onDisband( *pLeader );

  for( const auto& member : members )
  {
    // TODO: 2nd argument here makes it automatically send passing leadership message
    member->queuePacket( { makePartyUpdate( disconnectingPlayer, UpdateStatus::OFFLINE_MEMBER, party->PartyCount ), makeZonePacket< FFXIVIpcPartyList >( member->getId() ) } );
  }

  sendPartyUpdate( *party );
}

void PartyMgr::onMemberRejoin( Entity::Player& joiningPlayer )
{
  auto party = getParty( joiningPlayer.getPartyId() );
  assert( party );

  // TODO: do we need a party update here? move zone handler already handles it
}

void PartyMgr::onKick( const std::string& kickPlayerName, Entity::Player& leader )
{
  auto& server = Common::Service< World::ServerMgr >::ref();
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto party = getParty( leader.getPartyId() );
  assert( party );
  auto pLeader = getPartyLeader( *party );
  auto members = getPartyMembers( *party );
  auto pKickedPlayer = server.getSession( kickPlayerName )->getPlayer();
  if( !pKickedPlayer )
  {
    Logger::error( "Target player for kicking not found (\"{t}\")", kickPlayerName );
    return;
  }

  if( party->PartyCount == 2 )
  {
    onDisband( *pLeader );
  }
  else
  {
    for( const auto &member: members )
    {
      if( kickPlayerName == member->getName() )
      {
        removeMember( *party, member );
        member->removeOnlineStatus( Common::OnlineStatus::PartyMember );

        member->queuePacket( { makePartyUpdate( *pLeader, *member, UpdateStatus::KICK_SELF, party->PartyCount ),
                                                           makeZonePacket< FFXIVIpcPartyList >( member->getId() ) } );
      }
      else
      {
        member->queuePacket( makePartyUpdate( *pKickedPlayer, UpdateStatus::KICK_MEMBER, party->PartyCount ) );
      }
    }
    party->PartyCount--;
    sendPartyUpdate( *party );
  }
}

void PartyMgr::onChangeLeader( const std::string& newLeaderName, Entity::Player& oldLeader )
{
  auto& server = Common::Service< World::ServerMgr >::ref();
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto party = getParty( oldLeader.getPartyId() );

  auto pNewLeader = server.getSession( newLeaderName )->getPlayer();

  if( !pNewLeader )
  {
    Logger::error( "Target player for new leader not found (\"{t}\")", newLeaderName );
    return;
  }

  for( auto memberId : party->MemberId )
  {
    if( memberId == pNewLeader->getId() )
    {
      pNewLeader->addOnlineStatus( Common::OnlineStatus::PartyLeader );
      // this is not ideal, probably better to have a function which can add
      // and remove at the same time so packets are only triggered once
      oldLeader.addOnlineStatus( Common::OnlineStatus::PartyMember );
      oldLeader.removeOnlineStatus( Common::OnlineStatus::PartyLeader );

      party->LeaderId = pNewLeader->getId();
      break;
    }
  }

  auto members = getPartyMembers( *party );
  for( auto& member : members )
  {
    auto pcUpdateParty = makePartyUpdate( oldLeader.getAsPlayer(), pNewLeader, UpdateStatus::CHANGELEADER, party->PartyCount );
    member->queuePacket( pcUpdateParty );
  }

  sendPartyUpdate( *party );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t PartyMgr::createParty()
{
  auto& chatChannelMgr = Common::Service< ChatChannelMgr >::ref();
  auto party = std::make_shared< Party >();
  party->PartyID = getNextPartyId();
  party->ChatChannel = chatChannelMgr.createChatChannel( Common::ChatChannelType::PartyChat );
  m_partyIdMap[ party->PartyID ] = party;
  return party->PartyID;
}

uint64_t PartyMgr::getNextPartyId()
{
  return ++m_maxPartyId;
}

PartyPtr PartyMgr::getParty( uint64_t partyId )
{
  auto it = m_partyIdMap.find( partyId );
  if( it != m_partyIdMap.end() )
    return it->second;

  return nullptr;
}

std::vector< Entity::PlayerPtr > PartyMgr::getPartyMembers( Party& party )
{
  std::vector< Entity::PlayerPtr > members;

  auto& server = Common::Service< World::ServerMgr >::ref();
  for( auto& memberId : party.MemberId )
  {
    if( memberId == 0 )
      continue;

    auto pPlayer = server.getSession( memberId )->getPlayer();

    members.push_back( pPlayer );
  }
  return members;
}

Entity::PlayerPtr PartyMgr::getPartyLeader( Party& party )
{
  auto& server = Common::Service< World::ServerMgr >::ref();

  if( party.LeaderId == 0 )
    return nullptr;
  
  auto pLeader = server.getSession( party.LeaderId )->getPlayer();

  return pLeader;
}

void PartyMgr::sendPartyUpdate( Party& party )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto partyMembers = getPartyMembers( party );
  std::vector< PartyMember > entries;
  auto& server = Common::Service< World::ServerMgr >::ref();

  for( const auto& member : partyMembers )
  {
    auto classJob = exdData.get< Data::ClassJob >( static_cast< uint8_t >( member->getClass() ) );
    if( !classJob )
      continue;

    PartyMember memberEntry{};

    memberEntry./*ParentEntityId*/u1 = Common::INVALID_GAME_OBJECT_ID;
    memberEntry./*PetEntityId*/u2 = Common::INVALID_GAME_OBJECT_ID;
    memberEntry.hp = member->getHp();
    memberEntry.maxHp = member->getMaxHp();
    memberEntry.mp = member->getMp();
    memberEntry.maxMp = member->getMaxMp();
    memberEntry.classId = static_cast< uint8_t >( member->getClass() );
    memberEntry.level = member->getLevel();
    //memberEntry.ObjType = 4; // 1 PC, 2 Buddy ??
    memberEntry.zoneId = member->getTerritoryTypeId();
    memberEntry./*Valid*/gposeSelectable = 1;
    //memberEntry.Tp = member->getTp();
    //memberEntry.Role = classJob->role;

    entries.push_back( memberEntry );
  }

  for( const auto& pMember : partyMembers )
  {
    size_t idx = 0;

    auto updatePartyPacket = makeZonePacket< FFXIVIpcPartyList >( partyMembers[ 0 ]->getId() );
    auto& data = updatePartyPacket->data();
    data.partyId = party.PartyID;
    data.leaderIndex = getPartyLeaderIndex( party );
    data.channelId = party.ChatChannel;
    data.partySize = party.PartyCount;
    
    for( const auto& member : partyMembers )
    {
      bool isConnected = /*member->isConnected()*/true;
      // if player is online and in the same zone as current member in party, display more data in partylist
      bool hasInfo = isConnected && member->getTerritoryTypeId() == pMember->getTerritoryTypeId();

      if( hasInfo )
      {
        data.member[ idx ] = entries[ idx ];
      }

      data.member[ idx ].contentId = member->getContentId();
      data.member[ idx ].charaId = member->getId();
      strcpy( data.member[ idx ].name, member->getName().c_str() );

      idx++;
    }

    pMember->queuePacket( updatePartyPacket );
  }
}

void PartyMgr::removeParty( uint64_t partyId )
{
  m_partyIdMap.erase( partyId );
}

int8_t PartyMgr::getPartyLeaderIndex( const Party &party )
{
  size_t idx = 0;
  for( const auto& memberId : party.MemberId )
  {
    if( memberId == party.LeaderId )
      return static_cast< int8_t >( idx );
    idx++;
  }
  return -1;
}

void PartyMgr::removeMember( Party &party, const Entity::PlayerPtr& pMember )
{
  auto& ccMgr = Common::Service< World::Manager::ChatChannelMgr >::ref();
  pMember->setPartyId( 0 );
  ccMgr.removeFromChannel( party.ChatChannel, *pMember );
  party.MemberId.erase( std::remove( party.MemberId.begin(), party.MemberId.end(), pMember->getId() ), party.MemberId.end() );
}
