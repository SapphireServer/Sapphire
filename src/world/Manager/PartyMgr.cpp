#include <Common.h>
#include <Exd/ExdData.h>
#include <Service.h>

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"

#include "PartyMgr.h"
#include "WorldServer.h"
#include "ChatChannelMgr.h"
#include "PlayerMgr.h"

#include "Session.h"

#include "Actor/Player.h"

#include "Network/PacketWrappers/PcPartyUpdatePacket.h"

#include "StatusEffect/StatusEffect.h"

#include <Util/Util.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

void PartyMgr::onJoin( Entity::Player& joiner, Entity::Player& inviter )
{
  auto& server = Common::Service< World::WorldServer >::ref();
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

  auto pcUpdateParty = makePcPartyUpdate( invitingPlayer, inviteePlayer, UpdateStatus::JOINED, party->PartyCount );
  auto members = getPartyMembers( *party );
  sendPartyUpdate( *party );
  for( const auto& member : members )
  {
    server.queueForPlayer( member->getCharacterId(), pcUpdateParty );
  }
}

void PartyMgr::onLeave( Sapphire::Entity::Player& leavingPlayer )
{
  auto& server = Common::Service< World::WorldServer >::ref();

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
        member->removeOnlineStatus( {
          Common::OnlineStatus::PartyMember,
          Common::OnlineStatus::PartyLeader
        } );

        server.queueForPlayer( leavingPlayer.getCharacterId(),
                               makeZonePacket< FFXIVIpcUpdateParty >( leavingPlayer.getId() ) );
        server.queueForPlayer( member->getCharacterId(), makePcPartyUpdate( leadingPlayer, nullptr,
                                                                            UpdateStatus::KICK_SELF,
                                                                            party->PartyCount ) );
      }
      else
      {
        if( leavingPlayer.getId() == party->LeaderId )
        {
          newLeaderId = party->MemberId[ 0 ];
          auto pPlayer = playerMgr().getPlayer( newLeaderId );
          if( !pPlayer || !pPlayer->isConnected() )
            continue;
          pPlayer->addOnlineStatus( Common::OnlineStatus::PartyLeader );
          server.queueForPlayer( member->getCharacterId(), makePcPartyUpdate( leavingPlayer, *pPlayer,
                                                                              UpdateStatus::LEAVELEADER_LEAVED_MEMBER,
                                                                              party->PartyCount ) );
        }
        else
        {
          server.queueForPlayer( member->getCharacterId(), makePcPartyUpdate( leavingPlayer,
                                                                              UpdateStatus::LEAVE_MEMBER,
                                                                              party->PartyCount ) );
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
  auto& server = Common::Service< World::WorldServer >::ref();
  auto party = getParty( disbandingPlayer.getPartyId() );
  assert( party );

  auto members = getPartyMembers( *party );
  for( const auto& member : members )
  {
    removeMember( *party, member );
    member->removeOnlineStatus( { Common::OnlineStatus::PartyMember, Common::OnlineStatus::PartyLeader } );
    server.queueForPlayer( member->getCharacterId(), {
                             makePcPartyUpdate( disbandingPlayer, disbandingPlayer, UpdateStatus::DISBAND,
                                                party->PartyCount ),
                             makeZonePacket< FFXIVIpcUpdateParty >( member->getId() )
                           } );
  }

  removeParty( party->PartyID );
}

void PartyMgr::onMoveZone( Sapphire::Entity::Player& movingPlayer )
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

  auto& server = Common::Service< World::WorldServer >::ref();
  auto party = getParty( disconnectingPlayer.getPartyId() );
  assert( party );
  auto members = getPartyMembers( *party );
  auto pLeader = getPartyLeader( *party );

  bool anyMembersOnline = false;

  for( const auto& member : members )
  {
    if( member->isConnected() )
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
    server.queueForPlayer( member->getCharacterId(), {
                             makePcPartyUpdate( disconnectingPlayer, UpdateStatus::OFFLINE_MEMBER, party->PartyCount ),
                             makeZonePacket< FFXIVIpcUpdateParty >( member->getId() )
                           } );
  }

  sendPartyUpdate( *party );
}

void PartyMgr::onMemberRejoin( Entity::Player& joiningPlayer )
{
  auto party = getParty( joiningPlayer.getPartyId() );
  assert( party );

  // TODO: do we need a party update here? move zone handler already handles it
}

void PartyMgr::onKick( const Entity::Player& kickedPlayer, const Entity::Player& leader )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto party = getParty( leader.getPartyId() );
  assert( party );
  auto pLeader = getPartyLeader( *party );
  auto members = getPartyMembers( *party );

  if( party->PartyCount == 2 )
  {
    onDisband( *pLeader );
  }
  else
  {
    for( const auto& member : members )
    {
      if( kickedPlayer.getId() == member->getId() )
      {
        removeMember( *party, member );
        member->removeOnlineStatus( Common::OnlineStatus::PartyMember );

        server.queueForPlayer( member->getCharacterId(), {
                                 makePcPartyUpdate( *pLeader, *member, UpdateStatus::KICK_SELF, party->PartyCount ),
                                 makeZonePacket< FFXIVIpcUpdateParty >( member->getId() )
                               } );
      }
      else
      {
        server.queueForPlayer( member->getCharacterId(),
                               makePcPartyUpdate( kickedPlayer, UpdateStatus::KICK_MEMBER, party->PartyCount ) );
      }
    }
    party->PartyCount--;
    sendPartyUpdate( *party );
  }
}

void PartyMgr::onChangeLeader( Entity::Player& newLeader, Entity::Player& oldLeader )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto party = getParty( oldLeader.getPartyId() );

  for( auto memberId : party->MemberId )
  {
    if( memberId == newLeader.getId() )
    {
      newLeader.addOnlineStatus( Common::OnlineStatus::PartyLeader );
      // this is not ideal, probably better to have a function which can add
      // and remove at the same time so packets are only triggered once
      oldLeader.addOnlineStatus( Common::OnlineStatus::PartyMember );
      oldLeader.removeOnlineStatus( Common::OnlineStatus::PartyLeader );

      party->LeaderId = newLeader.getId();
      break;
    }
  }

  auto members = getPartyMembers( *party );
  for( auto& member : members )
  {
    auto pcUpdateParty = makePcPartyUpdate( oldLeader, newLeader, UpdateStatus::CHANGELEADER, party->PartyCount );
    server.queueForPlayer( member->getCharacterId(), pcUpdateParty );
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

  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  for( auto& memberId : party.MemberId )
  {
    if( memberId == 0 )
      continue;

    auto pPlayer = playerMgr.getPlayer( memberId );

    members.push_back( pPlayer );
  }
  return members;
}

Entity::PlayerPtr PartyMgr::getPartyLeader( Party& party )
{
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();

  if( party.LeaderId == 0 )
    return nullptr;

  auto pLeader = playerMgr.getPlayer( party.LeaderId );

  return pLeader;
}

void PartyMgr::sendPartyUpdate( Party& party )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto partyMembers = getPartyMembers( party );
  std::vector< ZoneProtoDownPartyMember > entries;
  auto& server = Common::Service< World::WorldServer >::ref();

  for( const auto& member : partyMembers )
  {
    auto classJob = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( member->getClass() ) );
    if( !classJob )
      continue;

    ZoneProtoDownPartyMember memberEntry{};

    memberEntry.ParentEntityId = Common::INVALID_GAME_OBJECT_ID;
    memberEntry.PetEntityId = Common::INVALID_GAME_OBJECT_ID;
    memberEntry.Hp = member->getHp();
    memberEntry.HpMax = member->getMaxHp();
    memberEntry.Mp = member->getMp();
    memberEntry.MpMax = member->getMaxMp();
    memberEntry.ClassJob = static_cast< uint8_t >( member->getClass() );
    memberEntry.Lv = member->getLevel();
    memberEntry.ObjType = 4; // 1 PC, 2 Buddy ??
    memberEntry.TerritoryType = member->getTerritoryTypeId();
    memberEntry.Valid = 1;
    memberEntry.Tp = member->getTp();
    memberEntry.Role = classJob->data().Role;

    uint8_t statusIdx = 0;
    for( const auto& status : member->getStatusEffectMap() )
    {
      // cant send anymore statuses in this packet
      if( statusIdx == 30 )
        break;

      auto& pStatus = status.second;
      memberEntry.Status[ statusIdx ].Id = pStatus->getId();
      memberEntry.Status[ statusIdx ].Source = pStatus->getSrcActorId();
      memberEntry.Status[ statusIdx ].SystemParam = pStatus->getParam();
      memberEntry.Status[ statusIdx ].Time = pStatus->getDuration();

      ++statusIdx;
    }
    /*
    memberEntry.CharaId = member->getContentId();
    memberEntry.EntityId = member->getId();
    strcpy( memberEntry.Name, member->getName().c_str() );*/

    entries.push_back( memberEntry );
  }

  for( const auto& pMember : partyMembers )
  {
    size_t idx = 0;

    auto updatePartyPacket = makeZonePacket< FFXIVIpcUpdateParty >( partyMembers[ 0 ]->getId() );
    auto& data = updatePartyPacket->data();
    data.PartyID = party.PartyID;
    data.LeaderIndex = getPartyLeaderIndex( party );
    data.ChatChannel = party.ChatChannel;
    data.PartyCount = party.PartyCount;

    for( const auto& member : partyMembers )
    {
      bool isConnected = member->isConnected();
      // if player is online and in the same zone as current member in party, display more data in partylist
      bool hasInfo = isConnected && member->getTerritoryTypeId() == pMember->getTerritoryTypeId();

      if( hasInfo )
      {
        data.Member[ idx ] = entries[ idx ];
      }

      data.Member[ idx ].CharaId = member->getCharacterId();
      data.Member[ idx ].EntityId = member->getId();
      strcpy( data.Member[ idx ].Name, member->getName().c_str() );

      idx++;
    }

    server.queueForPlayer( pMember->getCharacterId(), updatePartyPacket );
  }
}

void PartyMgr::removeParty( uint64_t partyId )
{
  m_partyIdMap.erase( partyId );
}

int8_t PartyMgr::getPartyLeaderIndex( const Party& party )
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

void PartyMgr::removeMember( Party& party, const Entity::PlayerPtr& pMember )
{
  auto& ccMgr = Common::Service< World::Manager::ChatChannelMgr >::ref();
  pMember->setPartyId( 0 );
  ccMgr.removeFromChannel( party.ChatChannel, *pMember );
  party.MemberId.erase( std::remove( party.MemberId.begin(), party.MemberId.end(), pMember->getId() ),
                        party.MemberId.end() );
}
