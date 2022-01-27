#include "ContentFinder.h"
#include <Exd/ExdData.h>
#include <Service.h>
#include "Actor/Player.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/UpdateFindContentPacket.h"
#include "Network/PacketWrappers/NotifyFindContentPacket.h"

#include "Manager/PlayerMgr.h"

#include <WorldServer.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

void Sapphire::World::ContentFinder::update()
{
  auto& exdData = Service< Data::ExdData >::ref();
  auto& server = Service< WorldServer >::ref();
  for( auto& contentIt : m_queuedContent )
  {
    auto& content = contentIt.second;

    auto contentState = content->getState();
    switch( contentState )
    {
      case None:
        break;
      case MatchingInProgress:
        if( content->m_players.empty() )
        {
          Logger::info( "[ContentFinder] registerId#{} scheduled for removal, no more players in queue.", content->getRegisterId() );
          content->setState( ToBeRemoved );
        }
        break;
      case MatchingComplete:
      {
        auto contentInfo = exdData.getRow< Excel::InstanceContent >( content->getContentId() );
        for( auto& queuedPlayer : content->m_players )
        {
          uint32_t inProgress = 0; // 0x01 - in progress
          uint32_t dutyProgress = 0;
          uint32_t flags = 0; // 0x20 freerole, 0x40 ownrequest, 0x100 random
          auto updatePacket = makeUpdateFindContent( queuedPlayer->getEntityId(), contentInfo->data().TerritoryType,
                                                     SetResultMatched, inProgress, queuedPlayer->m_classJob, dutyProgress, flags );
          server.queueForPlayer( queuedPlayer->getCharacterId(), updatePacket );
        }

        content->setState( WaitingForAccept );
        break;
      }

      case WaitingForAccept:
        break;
      case Accepted:
        break;
      case InProgress:
        break;
      case InProgressRefill:
        break;
      case ToBeRemoved:
        auto regId = content->getRegisterId();
        bool contentRemoved = removeContentByRegisterId( regId );
        if( contentRemoved )
        {
          Logger::info( "[ContentFinder] registerId#{} removed", regId );
          return;
        }
        break;
    }




  }

}

void Sapphire::World::ContentFinder::registerContentsRequest( Sapphire::Entity::Player &player, const std::vector< uint32_t >& contentIds )
{
  queueForContent( player, contentIds );
  completeRegistration( player );
}

void Sapphire::World::ContentFinder::registerContentRequest( Sapphire::Entity::Player &player, uint32_t contentId )
{
  queueForContent( player, { contentId } );
  completeRegistration( player );
}

void Sapphire::World::ContentFinder::registerRandomContentRequest( Sapphire::Entity::Player &player, uint32_t randomContentTypeId )
{
  auto& exdData = Service< Data::ExdData >::ref();
  auto contentListIds = exdData.getIdList< Excel::InstanceContent >();
  std::vector< uint32_t > idList;

  for( auto id : contentListIds )
  {
    auto instanceContent = exdData.getRow< Excel::InstanceContent >( id );
    if( instanceContent->data().RandomContentType == randomContentTypeId )
    {
      if( instanceContent->data().LevelMin <= player.getLevel() )
        idList.push_back( id );
    }
  }

  queueForContent( player, idList );
  completeRegistration( player );
}

void Sapphire::World::ContentFinder::completeRegistration( const Sapphire::Entity::Player &player )
{

  auto& server = Service< WorldServer >::ref();
  auto queuedContent = m_queuedContent[ m_queuedPlayer[ player.getId() ]->getActiveRegisterId() ];

  auto& exdData = Service< Data::ExdData >::ref();
  auto content = exdData.getRow< Excel::InstanceContent >( queuedContent->getContentId() );

  auto updatePacket = makeUpdateFindContent( player.getId(), content->data().TerritoryType,
                                             CompleteRegistration, 1, static_cast< uint32_t >( player.getClass() ) );
  server.queueForPlayer( player.getCharacterId(), updatePacket );

  auto statusPacket = makeNotifyFindContentStatus( player.getId(), content->data().TerritoryType, 3, queuedContent->m_attackerCount + queuedContent->m_rangeCount,
                                                   queuedContent->m_healerCount, queuedContent->m_tankCount, 0xff );

  for( auto& queuedPlayer : queuedContent->m_players )
  {
    server.queueForPlayer( queuedPlayer->getCharacterId(), statusPacket );
  }
}

void Sapphire::World::ContentFinder::queueForContent( Sapphire::Entity::Player &player, const std::vector< uint32_t >& contentIds )
{
  for( auto contentId : contentIds )
  {
    auto contentList = getMatchingContentList( player, contentId );

    if( contentList.empty() )
    {
      Logger::error( "[ContentFinder] No matching content could be found or generated." );
      return;
    }

    for( auto &content : contentList )
    {
      Logger::info( "[{2}][ContentFinder] Content registered, contentId#{0} registerId#{1}", contentId, content->getRegisterId(), player.getId() );
      PlayerMgr::sendDebug( player, "Content registered, contentId#{0} registerId#{1}", contentId, content->getRegisterId() );
      m_queuedContent[ content->getRegisterId() ] = content;

      auto qPlayerIt = m_queuedPlayer.find( player.getId() );
      if( qPlayerIt == m_queuedPlayer.end() )
      {
        auto pQPlayer = std::make_shared< QueuedPlayer >( player, content->getRegisterId() );
        m_queuedPlayer[ player.getId() ] = pQPlayer;
      }
      else
      {
        m_queuedPlayer[ player.getId() ]->setActiveRegisterId( content->getRegisterId() );
      }
      content->queuePlayer( m_queuedPlayer[ player.getId() ] );
    }
  }
}

void Sapphire::World::QueuedContent::queuePlayer( const std::shared_ptr< QueuedPlayer >& pQPlayer )
{
  m_players.push_back( pQPlayer );
  m_partyMemberCount++;
  switch( pQPlayer->getRole() )
  {
    case Role::Tank:
      m_tankCount++;
      break;
    case Role::Healer:
      m_healerCount++;
      break;
    case Role::RangedPhysical:
    case Role::RangedMagical:
      m_rangeCount++;
      break;
    case Role::Melee:
      m_attackerCount++;
      break;
    case Role::None:
    case Role::Crafter:
    case Role::Gatherer:
      break;
  }
}

bool Sapphire::World::QueuedContent::withdrawPlayer( const std::shared_ptr< QueuedPlayer >& pQPlayer )
{
  auto preSize = m_players.size();
  auto it = m_players.begin();
  for( ; it != m_players.end(); ++it )
  {
    if( it->get()->getCharacterId() == pQPlayer->getCharacterId() )
    {
      m_players.erase( it );
      break;
    }
  }

  auto postSize = m_players.size();
  if( preSize == postSize )
    return false;

  m_partyMemberCount--;
  switch( pQPlayer->getRole() )
  {
    case Role::Tank:
      m_tankCount--;
      break;
    case Role::Healer:
      m_healerCount--;
      break;
    case Role::RangedPhysical:
    case Role::RangedMagical:
      m_rangeCount--;
      break;
    case Role::Melee:
      m_attackerCount--;
      break;
    case Role::None:
    case Role::Crafter:
    case Role::Gatherer:
      break;
  }
  return true;
}

uint32_t Sapphire::World::ContentFinder::getNextRegisterId()
{
  return ++m_nextRegisterId;
}

Sapphire::World::ContentFinder::QueuedContentPtrList Sapphire::World::ContentFinder::getMatchingContentList( Sapphire::Entity::Player &player, uint32_t contentId )
{
  QueuedContentPtrList outVec;
  for( auto& it : m_queuedContent )
  {
    auto& foundContent = it.second;
    uint32_t leftContentId = foundContent->getContentId();
    if( leftContentId != contentId )
      continue;

    auto& exdData = Common::Service< Data::ExdData >::ref();
    auto content = exdData.getRow< Excel::InstanceContent >( contentId );
    if( !content )
      continue;

    // make sure the player has at least the required level
    if( player.getLevel() < content->data().LevelMin )
      continue;

    if( foundContent->getState() != QueuedContentState::MatchingInProgress )
      continue;

    // skip if the party is already full
    if( foundContent->m_partyMemberCount >= content->data().PartyMemberCount )
      continue;

    switch( player.getRole() )
    {
      case Role::Tank:
      {
        if( content->data().TankCount <= foundContent->m_tankCount )
          continue;
        break;
      }
      case Role::Healer:
      {
        if( content->data().HealerCount <= foundContent->m_healerCount )
          continue;
        break;
      }
      case Role::RangedPhysical:
      case Role::RangedMagical:
      {
        if( content->data().RangeCount <= foundContent->m_rangeCount )
          continue;
        break;
      }
      case Role::Melee:
      {
        if( content->data().AttackerCount <= foundContent->m_attackerCount )
          continue;
        break;
      }
      case Role::Crafter:
      case Role::Gatherer:
      case Role::None:
        continue;
    }

    outVec.push_back( foundContent );
  }

  if( outVec.empty() )
  {
    auto queuedContent = std::make_shared< QueuedContent >( getNextRegisterId(), contentId );
    outVec.push_back( queuedContent );
  }
  return outVec;
}

void Sapphire::World::ContentFinder::withdraw( Entity::Player& player )
{
  auto& server = Service< WorldServer >::ref();
  auto& exdData = Service< Data::ExdData >::ref();

  auto queuedPlayer = m_queuedPlayer[ player.getId() ];
  auto contentInfo = exdData.getRow< Excel::InstanceContent >( m_queuedContent[ queuedPlayer->getActiveRegisterId() ]->getContentId() );

  // remove the player from the global CF list
  m_queuedPlayer.erase( player.getId() );

  // send packet to clear CF in the client. TODO needs to be moved elsewhere
  auto updatePacket = makeUpdateFindContent( player.getId(), contentInfo->data().TerritoryType, SetResultFailed2 );
  server.queueForPlayer( queuedPlayer->getCharacterId(), updatePacket );

  // check all queued contents for the player and remove if needed
  std::set< uint32_t > updateRegisterIdSet;
  for( auto& content : m_queuedContent )
  {
    if( content.second->withdrawPlayer( queuedPlayer ) )
    {
      Logger::info( "[{2}] Content withdrawn, contentId#{0} registerId#{1}",
                    content.second->getContentId(), content.second->getRegisterId(), player.getId() );
      updateRegisterIdSet.insert( content.second->getRegisterId() );
    }
  }

  // check for each queued content if players need to be updated
  for( auto& content : m_queuedContent )
  {
    auto regId = content.second->getRegisterId();
    // if this content does not require an update, skip.
    if( updateRegisterIdSet.count( regId ) == 0 )
      continue;

    auto queuedContentInfo = exdData.getRow< Excel::InstanceContent >( content.second->getContentId() );
    auto& playerList = content.second->m_players;
    for( const auto& pPlayer : playerList )
    {
      // only update players which have this content active (shown in UI)
      if( pPlayer->getActiveRegisterId() != regId )
        continue;

      auto statusPacket = makeNotifyFindContentStatus( player.getId(), queuedContentInfo->data().TerritoryType, 3,
                                                       content.second->m_attackerCount + content.second->m_rangeCount,
                                                       content.second->m_healerCount, content.second->m_tankCount, 0xff );

      server.queueForPlayer( pPlayer->getCharacterId(), statusPacket );
    }

  }

}

std::shared_ptr< Sapphire::World::QueuedContent > Sapphire::World::ContentFinder::findContentByRegisterId( uint32_t registerId )
{
  auto it = m_queuedContent.find( registerId );
  if( it != m_queuedContent.end() )
    return it->second;
  return nullptr;
}

bool Sapphire::World::ContentFinder::removeContentByRegisterId( uint32_t registerId )
{
  auto it = m_queuedContent.find( registerId );
  if( it == m_queuedContent.end() )
    return false;
  m_queuedContent.erase( it );
  return true;
}

//////////////////////////////////////////////////////////////////////

uint32_t Sapphire::World::QueuedContent::getContentId() const
{
  return m_contentId;
}

uint32_t Sapphire::World::QueuedContent::getRegisterId() const
{
  return m_registerId;
}

Sapphire::World::QueuedContent::QueuedContent( uint32_t registerId, uint32_t contentId ) :
  m_registerId( registerId ),
  m_contentId( contentId ),
  m_state( QueuedContentState::MatchingInProgress ),
  m_contentPopTime( 0 )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto content = exdData.getRow< Excel::InstanceContent >( contentId );


}

uint8_t Sapphire::World::QueuedContent::getRoleCount( Sapphire::Common::Role role ) const
{
  switch( role )
  {
    case Role::Tank:
      return m_tankCount;
    case Role::Healer:
      return m_healerCount;
    case Role::RangedPhysical:
    case Role::RangedMagical:
      return m_rangeCount;
    case Role::Melee:
      return m_attackerCount;
    case Role::Crafter:
    case Role::Gatherer:
    case Role::None:
      return 0;
  }
  return 0;
}

Sapphire::World::QueuedContentState Sapphire::World::QueuedContent::getState() const
{
  return m_state;
}

void Sapphire::World::QueuedContent::setState( Sapphire::World::QueuedContentState state )
{
  m_state = state;
}

//////////////////////////////////////////////////////////////////////


Sapphire::World::QueuedPlayer::QueuedPlayer( const Entity::Player &player, uint8_t registerId  )
{
  m_characterId = player.getCharacterId();
  m_classJob = static_cast< uint32_t >( player.getClass() );
  m_level = player.getLevel();
  m_activeRegisterId = registerId;
  m_role = player.getRole();
  m_entityId = player.getId();
}

Sapphire::Common::Role Sapphire::World::QueuedPlayer::getRole() const
{
  return m_role;
}

void Sapphire::World::QueuedPlayer::setActiveRegisterId( uint8_t registerId )
{
  m_activeRegisterId = registerId;
}

uint8_t Sapphire::World::QueuedPlayer::getActiveRegisterId() const
{
  return m_activeRegisterId;
}

uint64_t Sapphire::World::QueuedPlayer::getCharacterId() const
{
  return m_characterId;
}

uint32_t Sapphire::World::QueuedPlayer::getEntityId() const
{
  return m_entityId;
}
