#include <algorithm>
#include <iterator>

#include <Common.h>
#include <Exd/ExdData.h>
#include <Util/Util.h>
#include <Service.h>

#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Service.h>
#include <Manager/ChatChannelMgr.h>
#include <Network/GamePacket.h>

#include "Linkshell/Linkshell.h"
#include "LinkshellMgr.h"

#include "Actor/Player.h"

#include "WorldServer.h"

#include <Network/GameConnection.h>
#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/LinkshellResultPacket.h>
#include <Network/PacketDef/ClientIpcs.h>

#include "Session.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

bool Sapphire::World::Manager::LinkshellMgr::loadLinkshells()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto& chatChannelMgr = Common::Service< Manager::ChatChannelMgr >::ref();

  auto query = db.getPreparedStatement( Db::LINKSHELL_SEL_ALL );
  auto res = db.query( query );

  while( res->next() )
  {
    uint64_t linkshellId = res->getUInt64( 1 );
    uint64_t masterId = res->getUInt64( 2 );
    std::string name = res->getString( 4 );

    auto func = []( std::set< uint64_t >& outList, std::vector< char >& inData )
    {
      if( inData.size() )
      {
        size_t entryCount = inData.size() / 8;
        std::vector< uint64_t > list( entryCount );

        for( int i = 0; i < entryCount; ++i )
        {
          auto val = *reinterpret_cast< const uint64_t* >( &inData[ i * 8 ] );
          list[ i ] = val;
        }

        outList.insert( list.begin(), list.end() );
      }
    };

    std::set< uint64_t > members;
    std::vector< char > membersBin;
    membersBin = res->getBlobVector( 3 );
    func( members, membersBin );

    std::set< uint64_t > leaders;
    std::vector< char > leadersBin;
    leadersBin = res->getBlobVector( 5 );
    func( leaders, leadersBin );

    std::set< uint64_t > invites;
    std::vector< char > invitesBin;
    invitesBin = res->getBlobVector( 6 );
    func( invites, invitesBin );

    auto chatChannelId = chatChannelMgr.createChatChannel( Common::ChatChannelType::LinkshellChat );

    // TODO: remove shared_ptr, pass references instead
    auto lsPtr = std::make_shared< Linkshell >( linkshellId, name, chatChannelId, masterId, members, leaders, invites );
    m_linkshellIdMap[ linkshellId ] = lsPtr;
    m_linkshellNameMap[ name ] = lsPtr;

  }

  return true;
}

void LinkshellMgr::writeLinkshell( uint64_t lsId )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto ls = getLinkshellById( lsId );

  if( !ls )
  {
    Logger::error( "Linkshell {} not found for write!", lsId );
  }

  auto query = db.getPreparedStatement( Db::LINKSHELL_UP );

  auto& members = ls->getMemberIdList();
  auto& leaders = ls->getLeaderIdList();
  auto& invites = ls->getInviteIdList();
  std::vector< uint64_t > memberVec;
  std::vector< uint64_t > leaderVec;
  std::vector< uint64_t > inviteVec;

  std::copy( members.begin(), members.end(), std::back_inserter( memberVec ) );
  std::copy( leaders.begin(), leaders.end(), std::back_inserter( leaderVec ) );
  std::copy( invites.begin(), invites.end(), std::back_inserter( inviteVec ) );

  std::vector< uint8_t > memberBin( memberVec.size() * 8 );
  memcpy( memberBin.data(), memberVec.data(), memberVec.size() * 8 );

  std::vector< uint8_t > leaderBin( leaderVec.size() * 8 );
  memcpy( leaderBin.data(), leaderVec.data(), leaderVec.size() * 8 );

  std::vector< uint8_t > inviteBin( inviteVec.size() * 8 );
  memcpy( inviteBin.data(), inviteVec.data(), inviteVec.size() * 8 );

  query->setBinary( 1, memberBin );
  query->setString( 2, ls->getName() );
  query->setBinary( 3, leaderBin );
  query->setBinary( 4, inviteBin );
  query->setUInt64( 5, ls->getMasterId() );
  query->setInt64( 6, lsId );
  db.execute( query );

}

Sapphire::LinkshellPtr Sapphire::World::Manager::LinkshellMgr::getLinkshellByName( const std::string& name )
{
  auto it = m_linkshellNameMap.find( name );
  if( it == m_linkshellNameMap.end() )
    return nullptr;
  else
    return it->second;
}

Sapphire::LinkshellPtr Sapphire::World::Manager::LinkshellMgr::getLinkshellById( uint64_t lsId )
{
  auto it = m_linkshellIdMap.find( lsId );
  if( it == m_linkshellIdMap.end() )
    return nullptr;
  else
    return it->second;
}

Sapphire::LinkshellPtr Sapphire::World::Manager::LinkshellMgr::createLinkshell( const std::string& name, Entity::Player& player )
{
  uint64_t linkshellId = 1;

  if( !m_linkshellIdMap.empty() )
  {
    auto lastIdx = ( --m_linkshellIdMap.end() )->first;
    linkshellId = lastIdx + 1;
  }

  // check if a linkshell with the same name already exists
  auto lsIt = m_linkshellNameMap.find( name );
  if( lsIt != m_linkshellNameMap.end() )
    return nullptr;

  auto& chatChannelMgr = Common::Service< Manager::ChatChannelMgr >::ref();
  auto chatChannelId = chatChannelMgr.createChatChannel( Common::ChatChannelType::LinkshellChat );
  chatChannelMgr.addPlayerToChannel( chatChannelId, player );

  uint64_t masterId = player.getCharacterId();

  // TODO: remove this messy set
  std::set< uint64_t > memberSet;
  std::set< uint64_t > leaderSet;
  std::set< uint64_t > inviteSet;

  // we add linkshell owner to the list of members
  memberSet.insert( masterId );

  auto lsPtr = std::make_shared< Linkshell >( linkshellId, name, chatChannelId, masterId, memberSet, leaderSet, inviteSet );
  m_linkshellIdMap[ linkshellId ] = lsPtr;
  m_linkshellNameMap[ name ] = lsPtr;

  // TODO: generalize SQL update
  // TODO: handle player pkt

  // prepare binary data for SQL
  std::vector< uint64_t > members( 128, 0 );
  std::vector< uint64_t > leaders( 128, 0 );
  std::vector< uint64_t > invites( 128, 0 );

  // add player entry
  members[ 0 ] = masterId;
  
  std::vector< uint8_t > memVec( sizeof( members ) );
  memcpy( memVec.data(), members.data(), sizeof( members ) );

  std::vector< uint8_t > leadVec( sizeof( leaders ) );
  memcpy( leadVec.data(), leaders.data(), sizeof( leaders ) );

  std::vector< uint8_t > invVec( sizeof( invites ) );
  memcpy( invVec.data(), invites.data(), sizeof( invites ) );

  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::CHARA_LINKSHELL_INS );
  stmt->setUInt64( 1, linkshellId );
  stmt->setUInt64( 2, masterId );
  stmt->setBinary( 3, memVec );
  stmt->setString( 4, std::string( name ) );
  stmt->setBinary( 5, leadVec );
  stmt->setBinary( 6, invVec );

  db.directExecute( stmt );

  return lsPtr;
}

void Sapphire::World::Manager::LinkshellMgr::finishLinkshellAction( const std::string& name, uint32_t result, Entity::Player& player, uint8_t action )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto linkshellResult = makeLinkshellResult( player, 0, 0, action, result, 0, name, "" );
  server.queueForPlayer( player.getCharacterId(), linkshellResult );

}

const std::vector< Sapphire::LinkshellPtr > Sapphire::World::Manager::LinkshellMgr::getPlayerLinkshells( Entity::Player& player ) const
{
  std::vector< Sapphire::LinkshellPtr > lsVec;

  for( const auto &[ key, value ] : m_linkshellIdMap )
  {
    auto& memberList = value->getMemberIdList();
    auto& inviteList = value->getInviteIdList();

    // find player id in LS member or invite list
    if( memberList.count( player.getCharacterId() ) ||
        inviteList.count( player.getCharacterId() ) )
    {
      lsVec.emplace_back( value );
    }
  }

  return lsVec;
}

void LinkshellMgr::invitePlayer( Entity::Player& sourcePlayer, Entity::Player& invitedPlayer, uint64_t linkshellId )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto lsPtr = getLinkshellById( linkshellId );

  if( !lsPtr )
    return Logger::warn( "Failed to invite player to linkshell - linkshell not found!" );

  lsPtr->addInvite( invitedPlayer.getCharacterId() );
  writeLinkshell( lsPtr->getId() );
  sendLinkshellList( invitedPlayer );

  auto linkshellInviteResult = makeLinkshellResult( invitedPlayer, 0, 0,
                                                    WorldPackets::Client::LinkshellJoin, 0,
                                                    LinkshellResultPacket::UpdateStatus::Target,
                                                    lsPtr->getName(), sourcePlayer.getName() );

  server.queueForPlayer( invitedPlayer.getCharacterId(), linkshellInviteResult );

  auto linkshellInviteResult1 = makeLinkshellResult( sourcePlayer, 0, 0,
                                                     WorldPackets::Client::LinkshellJoin, 0,
                                                     LinkshellResultPacket::UpdateStatus::Execute,
                                                     lsPtr->getName(), invitedPlayer.getName() );

  server.queueForPlayer( sourcePlayer.getCharacterId(), linkshellInviteResult1 );
}

void LinkshellMgr::kickPlayer( Entity::Player& sourcePlayer, Entity::Player& kickedPlayer, uint64_t linkshellId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& chatChannelMgr = Common::Service< Manager::ChatChannelMgr >::ref();

  auto lsPtr = getLinkshellById( linkshellId );

  if( !lsPtr )
    return Logger::warn( "Failed to kick player from linkshell - linkshell not found!" );

  lsPtr->removeInvite( kickedPlayer.getCharacterId() );
  lsPtr->removeLeader( kickedPlayer.getCharacterId() );
  lsPtr->removeMember( kickedPlayer.getCharacterId() );
  writeLinkshell( lsPtr->getId() );
  sendLinkshellList( kickedPlayer );

  auto linkshellKickResult = makeLinkshellResult( kickedPlayer, 0, 0,
                                                    WorldPackets::Client::LinkshellKick, 0,
                                                    LinkshellResultPacket::UpdateStatus::Target,
                                                    lsPtr->getName(), sourcePlayer.getName() );

  server.queueForPlayer( kickedPlayer.getCharacterId(), linkshellKickResult );

  auto linkshellKickResult1 = makeLinkshellResult( sourcePlayer, 0, 0,
                                                     WorldPackets::Client::LinkshellKick, 0,
                                                     LinkshellResultPacket::UpdateStatus::Execute,
                                                     lsPtr->getName(), kickedPlayer.getName() );

  server.queueForPlayer( sourcePlayer.getCharacterId(), linkshellKickResult1 );
  chatChannelMgr.removePlayerFromChannel( lsPtr->getChatChannel(), kickedPlayer );
}

void LinkshellMgr::sendLinkshellList( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto linkshellListPacket = makeZonePacket< FFXIVIpcGetLinkshellListResult >( player.getId() );

  auto lsVec = getPlayerLinkshells( player );

  uint32_t chatFlag = player.isLogin() ? 0 : 1ul << 11;

  for( int i = 0; i < lsVec.size(); ++i )
  {
    auto pLs = lsVec[ i ];
    uint32_t hierarchy = 0;

    if( pLs->getMasterId() == player.getCharacterId() )
      hierarchy = Ls::LinkshellHierarchy::Master << 8;
    else if( pLs->getLeaderIdList().count( player.getCharacterId() ) )
      hierarchy = Ls::LinkshellHierarchy::Leader << 8;
    else if( pLs->getInviteIdList().count( player.getCharacterId() ) )
      hierarchy = Ls::LinkshellHierarchy::Invite << 8;
    else
      hierarchy = Ls::LinkshellHierarchy::Member << 8;

    hierarchy |= chatFlag;

    linkshellListPacket->data().LinkshellList[ i ].LinkshellID = pLs->getId();
    linkshellListPacket->data().LinkshellList[ i ].ChannelID = pLs->getChatChannel();
    linkshellListPacket->data().LinkshellList[ i ].HierarchyID = hierarchy;
    strcpy( linkshellListPacket->data().LinkshellList[ i ].LinkshellName, pLs->getName().c_str() );
  }

  server.queueForPlayer( player.getCharacterId(), linkshellListPacket );
}

void LinkshellMgr::leaveLinkshell( uint64_t lsId, uint64_t characterId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& chatChannelMgr = Common::Service< Manager::ChatChannelMgr >::ref();
  auto leavingPlayer = server.getPlayer( characterId );
  auto lsPtr = getLinkshellById( lsId );
  if( !leavingPlayer || !lsPtr )
    return;

  lsPtr->removeMember( characterId );
  writeLinkshell( lsId );

  chatChannelMgr.removePlayerFromChannel( lsPtr->getChatChannel(), *leavingPlayer );
  sendLinkshellList( *leavingPlayer );
}

void LinkshellMgr::joinLinkshell( uint64_t lsId, uint64_t characterId )
{
  auto &server = Common::Service< World::WorldServer >::ref();
  auto& chatChannelMgr = Common::Service< Manager::ChatChannelMgr >::ref();
  auto joiningPlayer = server.getPlayer( characterId );
  auto lsPtr = getLinkshellById( lsId );
  if( !joiningPlayer || !lsPtr )
    return;

  lsPtr->addMember( characterId );
  lsPtr->removeInvite( characterId );
  writeLinkshell( lsId );

  chatChannelMgr.addPlayerToChannel( lsPtr->getChatChannel(), *joiningPlayer );

  sendLinkshellList( *joiningPlayer );
}

void LinkshellMgr::addLeader( Sapphire::Entity::Player &sourcePlayer, Sapphire::Entity::Player &newLeaderPlayer, uint64_t linkshellId )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto lsPtr = getLinkshellById( linkshellId );

  if( !lsPtr )
    return Logger::warn( "Failed to promote player from linkshell - linkshell not found!" );

  lsPtr->addLeader( newLeaderPlayer.getCharacterId() );
  writeLinkshell( lsPtr->getId() );
  sendLinkshellList( newLeaderPlayer );

  auto linkshellResult = makeLinkshellResult( newLeaderPlayer, lsPtr->getId(), 0,
                                              WorldPackets::Client::LinkshellAddLeader, 0,
                                              LinkshellResultPacket::UpdateStatus::Target,
                                              lsPtr->getName(), sourcePlayer.getName() );

  server.queueForPlayer( newLeaderPlayer.getCharacterId(), linkshellResult );

  auto linkshellResult1 = makeLinkshellResult( sourcePlayer, lsPtr->getId(), 0,
                                               WorldPackets::Client::LinkshellAddLeader, 0,
                                               LinkshellResultPacket::UpdateStatus::Execute,
                                               lsPtr->getName(), newLeaderPlayer.getName() );

  server.queueForPlayer( sourcePlayer.getCharacterId(), linkshellResult1 );
}

void LinkshellMgr::declineLeader( Sapphire::Entity::Player &sourcePlayer, uint64_t linkshellId )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto lsPtr = getLinkshellById( linkshellId );

  if( !lsPtr )
    return Logger::warn( "Failed to decline leader from linkshell - linkshell not found!" );

  lsPtr->removeLeader( sourcePlayer.getCharacterId() );
  writeLinkshell( lsPtr->getId() );
  sendLinkshellList( sourcePlayer );

  auto linkshellResult = makeLinkshellResult( sourcePlayer, lsPtr->getId(), 0,
                                              WorldPackets::Client::LinkshellDeclineLeader, 0,
                                              LinkshellResultPacket::UpdateStatus::Execute,
                                              lsPtr->getName(), sourcePlayer.getName() );

  server.queueForPlayer( sourcePlayer.getCharacterId(), linkshellResult );

}

void LinkshellMgr::removeLeader( Sapphire::Entity::Player &sourcePlayer, Sapphire::Entity::Player &leaderPlayer, uint64_t linkshellId )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto lsPtr = getLinkshellById( linkshellId );

  if( !lsPtr )
    return Logger::warn( "Failed to remove leader from linkshell - linkshell not found!" );

  lsPtr->removeLeader( leaderPlayer.getCharacterId() );
  writeLinkshell( lsPtr->getId() );
  sendLinkshellList( leaderPlayer );

  auto linkshellResult = makeLinkshellResult( leaderPlayer, lsPtr->getId(), 0,
                                              WorldPackets::Client::LinkshellRemoveLeader, 0,
                                              LinkshellResultPacket::UpdateStatus::Target,
                                              lsPtr->getName(), sourcePlayer.getName() );

  server.queueForPlayer( leaderPlayer.getCharacterId(), linkshellResult );

  auto linkshellResult1 = makeLinkshellResult( sourcePlayer, lsPtr->getId(), 0,
                                               WorldPackets::Client::LinkshellRemoveLeader, 0,
                                               LinkshellResultPacket::UpdateStatus::Execute,
                                               lsPtr->getName(), leaderPlayer.getName() );

  server.queueForPlayer( sourcePlayer.getCharacterId(), linkshellResult1 );
}

void LinkshellMgr::changeMaster( Sapphire::Entity::Player &sourcePlayer, Sapphire::Entity::Player &nextMasterPlayer, uint64_t linkshellId )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto lsPtr = getLinkshellById( linkshellId );

  if( !lsPtr )
    return Logger::warn( "Failed to change master from linkshell - linkshell not found!" );

  lsPtr->setMasterId( nextMasterPlayer.getCharacterId() );
  writeLinkshell( lsPtr->getId() );
  sendLinkshellList( nextMasterPlayer );
  sendLinkshellList( sourcePlayer );

  auto linkshellResult = makeLinkshellResult( sourcePlayer, lsPtr->getId(), nextMasterPlayer.getCharacterId(),
                                              WorldPackets::Client::LinkshellChangeMaster, 0,
                                              LinkshellResultPacket::UpdateStatus::Target,
                                              lsPtr->getName(), nextMasterPlayer.getName() );

  server.queueForPlayer( nextMasterPlayer.getCharacterId(), linkshellResult );

  auto linkshellResult1 = makeLinkshellResult( sourcePlayer, lsPtr->getId(), nextMasterPlayer.getCharacterId(),
                                               WorldPackets::Client::LinkshellChangeMaster, 0,
                                               LinkshellResultPacket::UpdateStatus::Execute,
                                               lsPtr->getName(), nextMasterPlayer.getName() );

  server.queueForPlayer( sourcePlayer.getCharacterId(), linkshellResult1 );
}

bool LinkshellMgr::renameLinkshell( uint64_t linkshellId, const std::string &name, Sapphire::Entity::Player &player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto lsPtr = getLinkshellById( linkshellId );

  if( !lsPtr )
  {
    Logger::warn( "Failed to rename linkshell - linkshell not found!" );
    return false;
  }

  // can't rename to an already existing name
  if( getLinkshellByName( name ) )
    return false;

  lsPtr->setName( name );
  writeLinkshell( lsPtr->getId() );

  return true;
}
