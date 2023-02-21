#include <iterator>

#include <Common.h>
#include <Exd/ExdData.h>
#include <Service.h>

#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Manager/ChatChannelMgr.h>
#include <Network/GamePacket.h>

#include "FreeCompany/FreeCompany.h"
#include "FreeCompanyMgr.h"

#include "Actor/Player.h"

#include "WorldServer.h"

#include <Network/GameConnection.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/FreeCompanyResultPacket.h>
#include <Network/PacketDef/ClientIpcs.h>

#include "Session.h"
#include <Event/EventDefinitions/EventDefinitions.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

void FreeCompanyMgr::handleEvent( const Common::EventSystem::Event& e )
{
  if( e.type() == Common::EventSystem::LoginEvent::descriptor )
  {
    const Common::EventSystem::LoginEvent& loginEvent = static_cast< const Common::EventSystem::LoginEvent& >( e );
    onFcLogin( loginEvent.characterId );
  }

}

bool FreeCompanyMgr::loadFreeCompanies()
{
  auto& chatChannelMgr = Common::Service< Manager::ChatChannelMgr >::ref();

  auto fcList = dbSelectFcsAll();

  for( const auto& fcPtr : fcList )
  {
    if( m_maxFcId < fcPtr->getId() )
      m_maxFcId = fcPtr->getId();

    auto chatChannelId = chatChannelMgr.createChatChannel( Common::ChatChannelType::FreeCompanyChat );
    fcPtr->setChatChannel( chatChannelId );
    m_fcIdMap[ fcPtr->getId() ] = fcPtr;
    m_fcNameMap[ fcPtr->getName() ] = fcPtr;

    auto members = dbSelectMembersByFc( fcPtr->getId() );
    for( const auto& member : members )
    {
      fcPtr->addMember( member.characterId, member.hierarchyId, member.lastLogout );
      m_charaIdToFcIdMap[ member.characterId ] = fcPtr->getId();
    }
  }

  return true;
}

void FreeCompanyMgr::writeFreeCompany( uint64_t fcId )
{
  auto fc = getFreeCompanyById( fcId );

  if( !fc )
  {
    Logger::error( "FreeCompanyMgr: FreeCompany {} not found for write!", fcId );
    return;
  }

  dbUpdateFc( *fc );
}

FreeCompanyPtr FreeCompanyMgr::getFreeCompanyByName( const std::string& name )
{
  auto it = m_fcNameMap.find( name );
  if( it == m_fcNameMap.end() )
    return nullptr;
  else
    return it->second;
}

FreeCompanyPtr FreeCompanyMgr::getFreeCompanyById( uint64_t fcId )
{
  auto it = m_fcIdMap.find( fcId );
  if( it == m_fcIdMap.end() )
    return nullptr;
  else
    return it->second;
}

FreeCompanyPtr FreeCompanyMgr::createFreeCompany( const std::string& name, const std::string& tag, Entity::Player& player )
{
  uint64_t freeCompanyId = ++m_maxFcId;

  // check if a fc with the same name already exists
  auto lsIt = m_fcNameMap.find( name );
  if( lsIt != m_fcNameMap.end() )
    return nullptr;

  auto& chatChannelMgr = Common::Service< Manager::ChatChannelMgr >::ref();
  auto chatChannelId = chatChannelMgr.createChatChannel( Common::ChatChannelType::FreeCompanyChat );
  chatChannelMgr.addToChannel( chatChannelId, player );

  uint64_t masterId = player.getCharacterId();
  m_charaIdToFcIdMap[ masterId ] = freeCompanyId;

  uint32_t createDate = Common::Util::getTimeSeconds();

  auto fcPtr = std::make_shared< FreeCompany >( freeCompanyId, name, tag, masterId, chatChannelId );
  fcPtr->setCreateDate( createDate );
  fcPtr->setGrandCompany( player.getGc() );
  fcPtr->setFcStatus( Common::FreeCompanyStatus::InviteStart );
  fcPtr->setRank( 1 );
  m_fcIdMap[ freeCompanyId ] = fcPtr;
  m_fcNameMap[ name ] = fcPtr;

  dbInsertFc( *fcPtr );
  dbInsertMember( freeCompanyId, masterId, 0 );

  fcPtr->addMember( masterId, 0, createDate );

  auto& server = Common::Service< World::WorldServer >::ref();

  auto fcResult = makeFcResult( player, freeCompanyId,
                                2, FreeCompanyResultPacket::ResultType::Create,
                                0, FreeCompanyResultPacket::UpdateStatus::Execute,
                                fcPtr->getName(), fcPtr->getTag() );

  server.queueForPlayer( player.getCharacterId(), fcResult );

  return fcPtr;
}

void FreeCompanyMgr::sendFreeCompanyStatus( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto fcStatusResult = makeZonePacket< FFXIVIpcGetFcStatusResult >( player.getId() );

  auto playerFc = getPlayerFreeCompany( player.getCharacterId() );
  if( !playerFc )
    return;

  fcStatusResult->data().AuthorityList = 0;
  fcStatusResult->data().ChannelID = playerFc->getChatChannel();
  fcStatusResult->data().Param = 2; // this appears to control which packets are requested afterwards
  fcStatusResult->data().CharaFcParam = 0;
  fcStatusResult->data().CrestID = playerFc->getCrest();
  fcStatusResult->data().FcRank = playerFc->getRank();
  fcStatusResult->data().FcStatus = static_cast< uint8_t >( playerFc->getFcStatus() );
  fcStatusResult->data().FreeCompanyID = playerFc->getId();
  fcStatusResult->data().GrandCompanyID = playerFc->getGrandCompany();

  server.queueForPlayer( player.getCharacterId(), fcStatusResult );

}

FreeCompanyPtr FreeCompanyMgr::getPlayerFreeCompany( uint64_t characterId )
{
  auto it = m_charaIdToFcIdMap.find( characterId );
  if( it != m_charaIdToFcIdMap.end() )
    return getFreeCompanyById( it->second );

  return nullptr;
}

void FreeCompanyMgr::sendFcInviteList( Entity::Player& player )
{
  auto fc = getPlayerFreeCompany( player.getCharacterId() );
  if( !fc )
    return;

  auto& server = Common::Service< World::WorldServer >::ref();

  auto inviteListPacket = makeZonePacket< FFXIVIpcGetFcInviteListResult >( player.getId() );
  inviteListPacket->data().GrandCompanyID = fc->getGrandCompany();
  inviteListPacket->data().FreeCompanyID = fc->getId();
  std::strcpy( inviteListPacket->data().FcTag, fc->getTag().c_str() );
  std::strcpy( inviteListPacket->data().FreeCompanyName, fc->getName().c_str() );

  // fill master character data
  auto masterCharacter = server.getPlayer( fc->getMasterId() );
  if( !masterCharacter )
  {
    Logger::error( "FreeCompanyMgr: Unable to look up master character#{}!", fc->getMasterId() );
    return;
  }

  inviteListPacket->data().MasterCharacter.GrandCompanyID = masterCharacter->getGc();
  inviteListPacket->data().MasterCharacter.CharacterID = masterCharacter->getCharacterId();
  strcpy( inviteListPacket->data().MasterCharacter.CharacterName, masterCharacter->getName().c_str() );
  inviteListPacket->data().MasterCharacter.SelectRegion = masterCharacter->getSearchSelectRegion();
  inviteListPacket->data().MasterCharacter.OnlineStatus = static_cast< uint64_t >( masterCharacter->getOnlineStatus() );
  inviteListPacket->data().MasterCharacter.GrandCompanyRank[ 0 ] = masterCharacter->getGcRankArray()[ 0 ];
  inviteListPacket->data().MasterCharacter.GrandCompanyRank[ 1 ] = masterCharacter->getGcRankArray()[ 1 ];
  inviteListPacket->data().MasterCharacter.GrandCompanyRank[ 2 ] = masterCharacter->getGcRankArray()[ 2 ];

  uint8_t idx = 0;
  for( auto& entry : fc->getMemberIdList() )
  {
    if( entry == 0 || entry == fc->getMasterId() )
      continue;

    auto signee = server.getPlayer( entry );
    if( !signee )
      continue;

    inviteListPacket->data().InviteCharacter[ idx ].CharacterID = signee->getCharacterId();
    strcpy( inviteListPacket->data().InviteCharacter[ idx ].CharacterName, signee->getName().c_str() );
    inviteListPacket->data().InviteCharacter[ idx ].SelectRegion = signee->getSearchSelectRegion();
    inviteListPacket->data().InviteCharacter[ idx ].OnlineStatus = static_cast< uint64_t >( masterCharacter->getOnlineStatus() );
    idx++;
  }

  server.queueForPlayer( player.getCharacterId(), inviteListPacket );
}

void FreeCompanyMgr::sendFcStatus( Entity::Player& player )
{
  auto fc = getPlayerFreeCompany( player.getCharacterId() );
  auto fcResultPacket = makeZonePacket< FFXIVIpcGetFcStatusResult >( player.getId() );
  auto& resultData = fcResultPacket->data();
  resultData.CharaFcParam = 1;

  if( fc )
  {
    resultData.FreeCompanyID = fc->getId();
    resultData.AuthorityList = 0;
    resultData.HierarchyType = player.getCharacterId() == fc->getMasterId() ? 0 : 1;
    resultData.GrandCompanyID = fc->getGrandCompany();
    resultData.FcRank = fc->getRank();
    resultData.CrestID = fc->getCrest();
    resultData.FcStatus = static_cast< uint8_t >( fc->getFcStatus() );
    resultData.ChannelID = fc->getChatChannel();
    //resultData.CharaFcParam = 1;
    //resultData.CharaFcState = 1;
  }

  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), fcResultPacket );
}

void FreeCompanyMgr::onFcLogin( uint64_t characterId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto player = server.getPlayer( characterId );
  if( !player )
    return;

  auto fc = getPlayerFreeCompany( player->getCharacterId() );
  if( !fc )
    return;

  m_onlinePlayers++;
  auto fcResultSelf = makeFcResult( *player, fc->getId(), m_onlinePlayers,
                                    FreeCompanyResultPacket::ResultType::FcLogin,
                                    0, FreeCompanyResultPacket::UpdateStatus::Execute,
                                    fc->getName(), fc->getTag() );

  server.queueForPlayer( player->getCharacterId(), fcResultSelf );

  auto fcResultOthers = makeFcResult( *player, fc->getId(), m_onlinePlayers,
                                      FreeCompanyResultPacket::ResultType::FcLogin,
                                      0, FreeCompanyResultPacket::UpdateStatus::Member,
                                      fc->getName(), player->getName() );

  server.queueForFreeCompany( fc->getId(), fcResultOthers, { characterId } );
}

void FreeCompanyMgr::onFcLogout( uint64_t characterId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto player = server.getPlayer( characterId );
  if( !player )
    return;

  auto fc = getPlayerFreeCompany( player->getCharacterId() );
  if( !fc )
    return;

  m_onlinePlayers--;
  auto fcResultOthers = makeFcResult( *player, fc->getId(), m_onlinePlayers,
                                      FreeCompanyResultPacket::ResultType::FcLogout,
                                      0, FreeCompanyResultPacket::UpdateStatus::Member,
                                      fc->getName(), player->getName() );

  server.queueForFreeCompany( fc->getId(), fcResultOthers, { characterId } );
}

void FreeCompanyMgr::onSignPetition( Entity::Player& source, Entity::Player& target )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto fc = getPlayerFreeCompany( target.getCharacterId() );
  if( !fc )
    return;

  addMember( fc->getId(), source.getCharacterId() );
  auto fcResultSelf = makeFcResult( source, fc->getId(), m_onlinePlayers,
                                    FreeCompanyResultPacket::ResultType::FcCreateAccept,
                                    0, FreeCompanyResultPacket::UpdateStatus::Execute,
                                    fc->getName(), fc->getTag() );

  server.queueForPlayer( source.getCharacterId(), fcResultSelf );

  auto fcResultOthers = makeFcResult( source, fc->getId(), m_onlinePlayers,
                                      FreeCompanyResultPacket::ResultType::FcCreateAccept,
                                      0, FreeCompanyResultPacket::UpdateStatus::Member,
                                      fc->getName(), source.getName() );

  server.queueForFreeCompany( fc->getId(), fcResultOthers, { source.getCharacterId() } );

}

void FreeCompanyMgr::addMember( uint64_t fcId, uint64_t memberId )
{
  auto pFc = getFreeCompanyById( fcId );
  if( !pFc )
    return;

  m_charaIdToFcIdMap[ memberId ] = fcId;
  dbInsertMember( fcId, memberId, 0 );
  pFc->addMember( memberId, 0, 0 );
}

void FreeCompanyMgr::dbInsertMember( uint64_t fcId, uint64_t characterId, uint8_t hierarchyId )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  /*! FreeCompanyId, FcMemberId, HierarchyType, LastLogout */
  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::FC_MEMBERS_INS );
  stmt->setUInt64( 1, fcId );
  stmt->setUInt64( 2, characterId );
  stmt->setUInt( 3, hierarchyId );
  stmt->setUInt( 4, 0 );
  db.directExecute( stmt );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// DB Related functions
//////////////////////////////////////////////////////////////////////////////////////////////////////


void FreeCompanyMgr::dbInsertFc( const FreeCompany& fc )
{
  //FreeCompanyId, MasterCharacterId, FcName, FcTag, FcCredit, FcCreditAccumu, FcRank, FcPoint,
  //ReputationList, CrestId, CreateDate, GrandCompanyID, FcStatus, FcBoard, FcMotto
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::FC_INS );
  stmt->setUInt64( 1, fc.getId() );
  stmt->setUInt64( 2, fc.getMasterId() );
  stmt->setString( 3, fc.getName() );
  stmt->setString( 4, fc.getTag() );
  stmt->setUInt64( 5, 0 );
  stmt->setUInt64( 6, 0 );
  stmt->setUInt( 7, 1 );
  stmt->setUInt64( 8, 0 );
  std::vector< uint8_t > rep( 24 );
  stmt->setBinary( 9, rep );
  stmt->setUInt64( 10, 0 );
  stmt->setUInt( 11, Common::Util::getTimeSeconds() );
  stmt->setUInt( 12, fc.getGrandCompany() );
  stmt->setUInt( 13, static_cast< uint8_t >( Common::FreeCompanyStatus::InviteStart ) );
  stmt->setString( 14, std::string( "" ) );
  stmt->setString( 15, std::string( "" ) );
  db.directExecute( stmt );
}

void FreeCompanyMgr::dbUpdateFc( const FreeCompany& fc )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto query = db.getPreparedStatement( Db::FC_UP );

  /*  MasterCharacterId = ?, FcName = ?, FcTag = ?, FcCredit = ?, FcCreditAccumu = ?,
   *  FcRank = ?, FcPoint = ?, ReputationList = ?, CrestId = ?,"
   *  CreateDate = ?, GrandCompanyID = ?, FcStatus = ?, FcBoard = ?, "
   *  FcMotto = ?, ActiveActionList = ?, , ActiveActionLeftTimeList = ?, StockActionList = ? "
   */

  query->setUInt64( 1, fc.getMasterId() );
  query->setString( 2, fc.getName() );
  query->setString( 3, fc.getTag() );
  query->setUInt64( 4, fc.getCredit() );
  query->setUInt64( 5, fc.getCreditAccumulated() );
  query->setUInt( 6, fc.getRank() );
  query->setUInt64( 7, fc.getPoints() );
  std::vector< uint8_t > repList( 24 );
  query->setBinary( 8, repList );
  query->setUInt64( 9, fc.getCrest() );
  query->setUInt( 10, fc.getCreateDate() );
  query->setUInt( 11, fc.getGrandCompany() );
  query->setUInt( 12, static_cast< uint8_t >( fc.getFcStatus() ) );
  query->setString( 13, fc.getFcBoard() );
  query->setString( 14, fc.getFcMotto() );
  std::vector< uint8_t > activeActionList( 24 );
  query->setBinary( 15, activeActionList );
  std::vector< uint8_t > activeActionLeftTimeList( 24 );
  query->setBinary( 16, activeActionLeftTimeList );
  std::vector< uint8_t > stockActionList( 120 );
  query->setBinary( 17, stockActionList );

  query->setInt64( 18, static_cast< int64_t >( fc.getId() ) );
  db.execute( query );

}

std::vector< FreeCompanyPtr > FreeCompanyMgr::dbSelectFcsAll()
{
  std::vector< FreeCompanyPtr > fcList;
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto query = db.getPreparedStatement( Db::FC_SEL_ALL );
  auto res = db.query( query );

  /* FreeCompanyId, MasterCharacterId, FcName, FcTag, FcCredit, FcCreditAccumu, FcRank, FcPoint, CrestId, CreateDate, GrandCompanyID, "
                    "       ReputationList, FcStatus, FcBoard, FcMotto, ActiveActionList, ActiveActionLeftTimeList, StockActionList */
  while( res->next() )
  {
    uint64_t fcId = res->getUInt64( 1 );
    uint64_t masterId = res->getUInt64( 2 );
    std::string name = res->getString( 3 );
    std::string tag = res->getString( 4 );
    uint64_t credit = res->getUInt64( 5 );
    uint64_t creditAcc = res->getUInt64( 6 );
    uint8_t rank = res->getUInt8( 7 );
    uint64_t points = res->getUInt64( 8 );
    uint64_t crestId = res->getUInt64( 9 );
    uint32_t creationDate = res->getUInt( 10 );
    uint8_t gcId = res->getUInt8( 11 );
    auto reputationListVec = res->getBlobVector( 12 );
    uint8_t status = res->getUInt8( 13 );
    std::string board = res->getString( 14 );
    std::string motto = res->getString( 15 );

    auto fcPtr = std::make_shared< FreeCompany >( fcId, name, tag, masterId, 0 );
    fcPtr->setCredit( credit );
    fcPtr->setCreditAccumulated( creditAcc );
    fcPtr->setRank( rank );
    fcPtr->setPoints( points );
    fcPtr->setCrest( crestId );
    fcPtr->setCreateDate( creationDate );
    fcPtr->setGrandCompany( gcId );
    fcPtr->setFcStatus( static_cast< Common::FreeCompanyStatus >( status ) );
    fcPtr->setFcBoard( board );
    fcPtr->setFcMotto( motto );
    fcList.push_back( fcPtr );
  }
  return fcList;
}

std::vector< FreeCompany::FcMember > FreeCompanyMgr::dbSelectMembersByFc( uint64_t fcId )
{
  std::vector< FreeCompany::FcMember > memberList;
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  /* FcMemberId, HierarchyType, LastLogout */
  auto queryMember = db.getPreparedStatement( Db::FC_MEMBERS_SEL_FC );
  queryMember->setUInt64( 1, fcId );
  auto resMember = db.query( queryMember );
  while( resMember->next() )
  {
    struct FreeCompany::FcMember member;
    member.characterId = resMember->getUInt64( 1 );
    member.hierarchyId = resMember->getUInt8( 2 );
    member.lastLogout = resMember->getUInt( 3 );
    memberList.push_back( member );
  }
  return memberList;
}