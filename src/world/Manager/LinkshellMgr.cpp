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
  query->setInt64( 5, lsId );
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
  auto& chatChannelMgr = Common::Service< Manager::ChatChannelMgr >::ref();
  auto chatChannelId = chatChannelMgr.createChatChannel( Common::ChatChannelType::LinkshellChat );

  uint64_t linkshellId = 1;

  if( !m_linkshellIdMap.empty() )
  {
    auto lastIdx = ( --m_linkshellIdMap.end() )->first;
    linkshellId = lastIdx + 1;
  }

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

  // TODO: insert in SQL

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
void Sapphire::World::Manager::LinkshellMgr::finishLinkshellCreation( const std::string& name, uint32_t result, Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto linkshellResult = makeZonePacket< FFXIVIpcLinkshellResult >( player.getId() );
  linkshellResult->data().Result = result;
  linkshellResult->data().UpPacketNo = 1;
  linkshellResult->data().Identity = 0xFF;
  strcpy( linkshellResult->data().LinkshellName, name.c_str() );
  server.queueForPlayer( player.getCharacterId(), linkshellResult );

}

const std::vector< Sapphire::LinkshellPtr > Sapphire::World::Manager::LinkshellMgr::getPlayerLinkshells( Entity::Player& player ) const
{
  std::vector< Sapphire::LinkshellPtr > lsVec;

  if( !m_linkshellIdMap.empty() )
  {
    for( const auto &[ key, value ] : m_linkshellIdMap )
    {
      auto& memberList = value->getMemberIdList();
      auto& inviteList = value->getInviteIdList();

      // find player id in LS member list
      if( memberList.count( player.getCharacterId() ) || inviteList.count( player.getCharacterId() ) )
      {
        lsVec.emplace_back( value );
      }
    }
  }

  return lsVec;
}


