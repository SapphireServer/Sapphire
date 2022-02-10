#include <Common.h>
#include <Vector3.cpp>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Network/CommonActorControl.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Chat/ServerChatDef.h>
#include <Database/DatabaseDef.h>
#include <Util/Util.h>

#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include <unordered_map>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Logging/Logger.h>
#include <Service.h>

#include "Network/GameConnection.h"

#include "Territory/Territory.h"
#include "Territory/HousingZone.h"
#include "Territory/Land.h"
#include "Territory/House.h"
#include "Territory/InstanceObjectCache.h"

#include "Linkshell/Linkshell.h"

#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/PingPacket.h"
#include "Network/PacketWrappers/MoveActorPacket.h"
#include "Network/PacketWrappers/ChatPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "Manager/DebugCommandMgr.h"
#include "Manager/EventMgr.h"
#include "Manager/MarketMgr.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/HousingMgr.h"
#include "Manager/RNGMgr.h"
#include "Manager/ChatChannelMgr.h"
#include "Manager/QuestMgr.h"
#include "Manager/LinkshellMgr.h"
#include "Manager/PartyMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/WarpMgr.h"

#include "Action/Action.h"

#include "Session.h"
#include "WorldServer.h"
#include "Forwards.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

void Sapphire::Network::GameConnection::setProfileHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcSetSearchInfo >( inPacket );

  player.setOnlineStatusCustomMask( packet.data().OnlineStatus );
  const auto status = player.getOnlineStatusCustomMask() | player.getOnlineStatusMask();
  const auto selectRegion = packet.data().Region;

  player.setSearchInfo( selectRegion, 0, packet.data().SearchComment );

  if( player.isNewAdventurer() && !( status & ( static_cast< uint64_t >( 1 ) << static_cast< uint8_t >( OnlineStatus::NewAdventurer ) ) ) )
    // mark player as not new adventurer anymore
    player.setNewAdventurer( false );
  else if( status & ( static_cast< uint64_t >( 1 ) << static_cast< uint8_t >( OnlineStatus::NewAdventurer ) ) )
    // mark player as new adventurer
    player.setNewAdventurer( true );

  auto statusPacket = makeZonePacket< FFXIVIpcSetOnlineStatus >( player.getId() );
  statusPacket->data().onlineStatusFlags = status;
  queueOutPacket( statusPacket );

  auto searchInfoPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcSetProfileResult >( player.getId() );
  searchInfoPacket->data().OnlineStatus = status;
  searchInfoPacket->data().Region = player.getSearchSelectRegion();
  searchInfoPacket->data().SelectClassID = packet.data().SelectClassID;
  searchInfoPacket->data().CurrentSelectClassID = packet.data().CurrentSelectClassID;
  strcpy( searchInfoPacket->data().SearchComment, player.getSearchMessage() );
  queueOutPacket( searchInfoPacket );

  player.sendToInRangeSet( makeActorControl( player.getId(), SetStatusIcon,
                                             static_cast< uint8_t >( player.getOnlineStatus() ) ), true );
}

void Sapphire::Network::GameConnection::getProfileHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto searchInfoPacket = makeZonePacket< FFXIVIpcGetProfileResult >( player.getId() );
  searchInfoPacket->data().OnlineStatus = player.getOnlineStatusMask() | player.getOnlineStatusCustomMask();
  searchInfoPacket->data().Region = player.getSearchSelectRegion();
  strcpy( searchInfoPacket->data().SearchComment, player.getSearchMessage() );
  queueOutPacket( searchInfoPacket );
}

void Sapphire::Network::GameConnection::getSearchCommentHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{

  auto targetId = *reinterpret_cast< const uint32_t* >( &inPacket.data[ 0x10 ] );
  auto& server = Common::Service< World::WorldServer >::ref();
  auto pPlayer = server.getPlayer( targetId );

  Logger::debug( "getSearchCommentHandler: {0}", targetId );

  if( pPlayer )
  {
    if( pPlayer->isActingAsGm() || pPlayer->getTerritoryTypeId() != player.getTerritoryTypeId() )
      return;

    // retail sends the requester's id as both (isForSelf)
    auto searchInfoPacket = makeZonePacket< FFXIVIpcExamineSearchComment >( player.getId() );
    searchInfoPacket->data().charId = targetId;
    strcpy( searchInfoPacket->data().searchComment, pPlayer->getSearchMessage() );
    server.queueForPlayer( player.getCharacterId(), searchInfoPacket );
  }
}

void Sapphire::Network::GameConnection::reqExamineFcInfo( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{

  auto targetId = *reinterpret_cast< const uint32_t* >( &inPacket.data[ 0x18 ] );

  auto& server = Common::Service< World::WorldServer >::ref();
  auto pPlayer = server.getPlayer( targetId );

  Logger::debug( "reqExamineFcInfo: {0}", targetId );

  if( pPlayer )
  {
    if( pPlayer->isActingAsGm() || pPlayer->getTerritoryTypeId() != player.getTerritoryTypeId() )
      return;

    // retail sends the requester's id as both (isForSelf)
    auto examineFcInfoPacket = makeZonePacket< FFXIVIpcExamineFreeCompanyInfo >( player.getId() );
    examineFcInfoPacket->data().charId = targetId;
    // todo: populate with fc info

    server.queueForPlayer( player.getCharacterId(), examineFcInfoPacket );
  }

}

void Sapphire::Network::GameConnection::joinChatChannelHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto joinChannelPacket = ZoneChannelPacket< Client::FFXIVIpcJoinChatChannel >( inPacket );
  const uint64_t channelIdReq = joinChannelPacket.data().ChannelID;

  auto& chatChannelMgr = Common::Service< ChatChannelMgr >::ref();

  if( !chatChannelMgr.isChannelValid( joinChannelPacket.data().ChannelID ) )
    return Logger::warn( "Failed to join chat channel - Invalid chat channel specified!" );

  chatChannelMgr.addToChannel( joinChannelPacket.data().ChannelID, player );

  auto chatChannelResultPacket = makeZonePacket< FFXIVIpcChatChannelResult >( player.getId() );

  chatChannelResultPacket->data().ChannelID = channelIdReq;
  chatChannelResultPacket->data().TargetCharacterID = player.getId();
  chatChannelResultPacket->data().CommunityID = player.getCharacterId();
  chatChannelResultPacket->data().UpPacketNo = 0; // todo: define behavior
  chatChannelResultPacket->data().Result = 0; // todo: define behavior

  queueOutPacket( chatChannelResultPacket );

  auto joinChannelResultPacket = makeChatPacket< Packets::Server::FFXIVJoinChannelResult >( player.getId() );

  joinChannelResultPacket->data().channelID = channelIdReq;
  joinChannelResultPacket->data().characterID = player.getId();
  joinChannelResultPacket->data().result = 0;

  auto& server = Common::Service< World::WorldServer >::ref();
  auto pSession = server.getSession( player.getCharacterId() );

  if( !pSession )
  {
    Logger::error( std::string( __FUNCTION__ ) + ": Session not found for player#{}", player.getCharacterId() );
    return;
  }

  pSession->getChatConnection()->queueOutPacket( joinChannelResultPacket );
}


void Sapphire::Network::GameConnection::moveHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  if( player.hasStateFlag( Common::BetweenAreas ) )
    return;
  const auto updatePositionPacket = ZoneChannelPacket< Client::FFXIVIpcUpdatePosition >( inPacket );
  auto& data = updatePositionPacket.data();

  bool bPosChanged = true;
  if( data.pos.x == player.getPos().x && data.pos.y == player.getPos().y && data.pos.z == player.getPos().z )
    bPosChanged = false;

  //if( !bPosChanged && player.getRot() == data.rotation )
    //return;

  player.setRot( data.dir );
  player.setPos( { data.pos.x, data.pos.y, data.pos.z } );

  if( player.getCurrentAction() && bPosChanged && player.getCurrentAction()->getCastTimeRest() > 500 )
    player.getCurrentAction()->setInterrupted( Common::ActionInterruptType::RegularInterrupt );

  auto clientAnimationType = data.flag;
  auto animationState = data.flag;
  auto animationType = data.flag2;
  auto animColType = data.flag2;
  auto headRotation = data.flag_unshared;
  uint8_t orgAnimationType = animationType;
  uint8_t unknownRotation = 0;
  uint16_t animationSpeed = MoveSpeed::Walk;

  animationType |= clientAnimationType;

  if( animationType & MoveType::Strafing )
  {
    if( animationType & MoveType::Walking )
      headRotation = 0xFF;
    else if( headRotation < 0x7F )
      headRotation += 0x7F;
    else if( headRotation > 0x7F )
      headRotation -= 0x7F;
  }
  if( animationType == MoveType::Running )
  {
    headRotation = 0x7F;
    animationSpeed = MoveSpeed::Run;
  }
  if( animationType & MoveType::Jumping )
  {

    if( animColType == MoveState::LeaveCollision )
    {
      if( orgAnimationType & clientAnimationType )
        animationType += 0x10;
      else
        animationType += 0x04;
    }

    if( animColType == MoveState::LeaveCollision || animColType == MoveState::StartFalling )
    {
      player.setFalling( true, { data.pos.x, data.pos.y, data.pos.z } );
    }
  }

  if( animColType == MoveState::EnterCollision )
  {
    animationType = 2;
    player.setFalling( false, { data.pos.x, data.pos.y, data.pos.z } );
  }

  if( player.isFalling() )
  {
    animationType += 0x10;
    unknownRotation = 0x7F;
  }

  uint64_t currentTime = Util::getTimeMs();

  player.m_lastMoveTime = currentTime;
  player.m_lastMoveflag = animationType;

  // if no one is in range, don't bother trying to send a position update
  if( !player.hasInRangeActor() )
    return;

  //auto movePacket = std::make_shared< MoveActorPacket >( player, headRotation, animationType, animationState, animationSpeed, unknownRotation );
  auto movePacket = std::make_shared< MoveActorPacket >( player, headRotation, data.flag, data.flag2, animationSpeed, unknownRotation );
  player.sendToInRangeSet( movePacket );
}

void Sapphire::Network::GameConnection::configHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcConfig >( inPacket );

  player.setEquipDisplayFlags( packet.data().flag );
  Service< World::Manager::PlayerMgr >::ref().onEquipDisplayFlagsChanged( player );
}

void Sapphire::Network::GameConnection::zoneJumpHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcZoneJump >( inPacket );
  auto& data = packet.data();
  const auto exitBoxId = data.ExitBox;

  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
  auto& server = Common::Service< World::WorldServer >::ref();

  auto pTeri = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  auto tInfo = pTeri->getTerritoryTypeInfo();

  auto pExitRange = instanceObjectCache.getExitRange( player.getTerritoryTypeId(), exitBoxId );

  Common::FFXIVARR_POSITION3 targetPos{};
  Common::FFXIVARR_POSITION3 targetRot{};
  uint32_t targetZone{128};
  float rotation = 0.0f;

  if( pExitRange )
  {
    auto pPopRange = instanceObjectCache.getPopRangeInfo( pExitRange->data.destInstanceObjectId );
    if( pPopRange )
    {
      targetZone = pExitRange->data.destTerritoryType;
      targetPos = pPopRange->m_pos;
      rotation = pPopRange->m_rotation;
      PlayerMgr::sendDebug( player, "ZoneLine #{0} found. Rotation: {1}, Zone: #{2} ", exitBoxId, rotation, targetZone );
    }
  }

  PlayerMgr::sendDebug( player, "Walking ZoneLine#{0}", exitBoxId );
  auto pTargetTeri = teriMgr.getZoneByTerritoryTypeId( targetZone );
  if( !pTargetTeri )
    return;

  auto& warpMgr = Common::Service< WarpMgr >::ref();
  warpMgr.requestMoveTerritory( player, Common::WARP_TYPE_EXIT_RANGE, pTargetTeri->getGuId(), targetPos, rotation );

}


void Sapphire::Network::GameConnection::newDiscoveryHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
  auto pTeri = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  auto tInfo = pTeri->getTerritoryTypeInfo();
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcNewDiscovery >( inPacket );
  const auto layoutId = packet.data().LayoutId;

  auto pRefInfo = instanceObjectCache.getMapRange( player.getTerritoryTypeId(), layoutId );

  PlayerMgr::sendDebug( player, "Discovery ref pos id#{0}", layoutId );

  if( pRefInfo )
  {
    auto discoveryPacket = makeZonePacket< FFXIVIpcDiscoveryReply >( player.getId() );
    discoveryPacket->data().mapId = tInfo->data().Map;
    discoveryPacket->data().mapPartId = pRefInfo->data.discoveryIndex;
    server.queueForPlayer( player.getCharacterId(), discoveryPacket );
    player.discover( tInfo->data().Map, pRefInfo->data.discoveryIndex );
  }

}

void Sapphire::Network::GameConnection::loginHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcLoginHandler >( inPacket );
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  // init handler means this is a login procedure
  player.setIsLogin( true );
  player.setConnected( true );
  teriMgr.joinWorld( player );
}

void Sapphire::Network::GameConnection::syncHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcPingHandler >( inPacket );
  auto& data = packet.data();

  queueOutPacket( std::make_shared< WorldPackets::Server::PingPacket >( player, data.clientTimeValue ) );

  auto pSession = server.getSession( player.getCharacterId() );
  if( !pSession )
    return;

  pSession->setLastPing( Common::Util::getTimeSeconds() );
}

void Sapphire::Network::GameConnection::setLanguageHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  if( player.isLogin() )
  {
    auto &questMgr = Common::Service< World::Manager::QuestMgr >::ref();
    questMgr.sendQuestsInfo( player );
  }

  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto pCurrentZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );

  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();

/*  // TODO: load and save this data instead of hardcoding
  auto gcPacket = makeZonePacket< FFXIVGCAffiliation >( player.getId() );
  gcPacket->data().gcId = player.getGc();
  gcPacket->data().gcRank[ 0 ] = player.getGcRankArray()[ 0 ];
  gcPacket->data().gcRank[ 1 ] = player.getGcRankArray()[ 1 ];
  gcPacket->data().gcRank[ 2 ] = player.getGcRankArray()[ 2 ];
  player.queuePacket( gcPacket );*/

  pCurrentZone->onFinishLoading( player );

  // player is done zoning
  player.setLoadingComplete( true );

  // if this is a login event
  if( player.isLogin() )
  {
    // fire the onLogin Event
    playerMgr.onLogin( player );
  }

  // spawn the player for himself
  player.spawn( player.getAsPlayer() );

  // notify the zone of a change in position to force an "inRangeActor" update
  pCurrentZone->updateActorPosition( player );
}

void Sapphire::Network::GameConnection::pcSearchHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcPcSearch >( inPacket );
  auto& data = packet.data();

  // TODO: implement player search
  auto& server = Common::Service< World::WorldServer >::ref();

  bool isLastName = data.CharacterName[ 0 ] == ' ';

  std::string queryName = data.CharacterName;
  if( !isLastName )
    queryName += " ";

  // on lastName, client automatically adds a space to first character - no need to manually add space

  auto queryPlayers = server.searchSessionByName( queryName );

  // store result in player - we don't map out query keys to data yet
  std::vector< uint32_t > entityIdVec;

  for( const auto& pSession : queryPlayers )
  {
    if( !pSession )
      continue;

    entityIdVec.emplace_back( pSession->getPlayer()->getId() );
  }

  player.setLastPcSearchResult( entityIdVec );

  // send amount of results found - client requires this to "enable" displaying new queries

  auto pcSearchResultPacket = makeZonePacket< FFXIVIpcPcSearchResult >( player.getId() );
  pcSearchResultPacket->data().ResultCount = static_cast< int16_t >( entityIdVec.size() );

  queueOutPacket( pcSearchResultPacket );
}

void Sapphire::Network::GameConnection::chatHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& debugCommandMgr = Common::Service< DebugCommandMgr >::ref();
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcChatHandler >( inPacket );
  auto& data = packet.data();

  auto pCurrentZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );

  if( data.message[ 0 ] == '!' )
  {
    // execute game console command
    debugCommandMgr.execCommand( const_cast< char* >( data.message ) + 1, player );
    return;
  }

  auto chatType = packet.data().chatType;

  //ToDo, need to implement sending GM chat types.
  auto chatPacket = std::make_shared< WorldPackets::Server::ChatPacket >( player, chatType, data.message );

  switch( chatType )
  {
    case ChatType::Say:
    {
      if( player.isActingAsGm() )
        chatPacket->data().type = static_cast< uint16_t >( ChatType::GMSay );

      pCurrentZone->queuePacketForRange( player, 50.f, chatPacket );
      break;
    }
    case ChatType::Yell:
    {
      if( player.isActingAsGm() )
        chatPacket->data().type = static_cast< uint16_t >( ChatType::GMYell );

      pCurrentZone->queuePacketForRange( player, 6000.f, chatPacket );
      break;
    }
    case ChatType::Shout:
    {
      if( player.isActingAsGm() )
        chatPacket->data().type = static_cast< uint16_t >( ChatType::GMShout );

      pCurrentZone->queuePacketForRange( player, 6000.f, chatPacket );
      break;
    }
    default:
    {
      pCurrentZone->queuePacketForRange( player, 50.f, chatPacket );
      break;
    }
  }

}

// TODO: this handler needs to be improved for timed logout, also the session should be instantly removed
// currently we wait for the session to just time out after logout, this can be a problem is the user tries to
// log right back in.
// Also the packet needs to be converted to an ipc structure
void Sapphire::Network::GameConnection::logoutHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto logoutPacket = makeZonePacket< FFXIVIpcEnableLogout >( player.getId() );
  logoutPacket->data().content = 0x02;
//  logoutPacket->data().flags2 = 0x2000;
  queueOutPacket( logoutPacket );

  player.setMarkedForRemoval();
}


void Sapphire::Network::GameConnection::tellHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcChatTo >( inPacket );
  auto& data = packet.data();

  auto& server = Common::Service< World::WorldServer >::ref();

  auto pSession = server.getSession( data.toName );

  if( !pSession )
  {
    auto tellErrPacket = makeZonePacket< Packets::Server::FFXIVIpcTellNotFound >( player.getId() );
    strcpy( tellErrPacket->data().toName, data.toName );
    sendSinglePacket( tellErrPacket );
    return;
  }

  auto pTargetPlayer = pSession->getPlayer();

  if( pTargetPlayer->hasStateFlag( PlayerStateFlag::BetweenAreas ) )
  {
    // send error for player between areas
    // TODO: implement me
    return;
  }

  auto pSessionSource = server.getSession( player.getCharacterId() );

  if( !pSession )
  {
    Logger::error( std::string( __FUNCTION__ ) + ": Session not found for player#{}", player.getCharacterId() );
    return;
  }

  if( pTargetPlayer->hasStateFlag( PlayerStateFlag::BoundByDuty ) && !player.isActingAsGm() )
  {
    auto boundPacket = makeChatPacket< Packets::Server::FFXIVRecvFinderStatus >( player.getId() );
    strcpy( boundPacket->data().toName, data.toName );
    pSessionSource->getChatConnection()->queueOutPacket( boundPacket );
    return;
  }

  if( pTargetPlayer->getOnlineStatus() == OnlineStatus::Busy && !player.isActingAsGm() )
  {
    auto busyPacket = makeChatPacket< Packets::Server::FFXIVRecvBusyStatus >( player.getId() );
    strcpy( busyPacket->data().toName, data.toName );
    pSessionSource->getChatConnection()->queueOutPacket( busyPacket );
    return;
  }

  auto tellPacket = makeChatPacket< Packets::Server::FFXIVChatFrom >( player.getId() );
  strcpy( tellPacket->data().message, data.message );
  strcpy( tellPacket->data().fromName, player.getName().c_str() );
  tellPacket->data().fromCharacterID = player.getCharacterId();

  if( player.isActingAsGm() )
  {
    tellPacket->data().type |= ChatFromType::GmTellMsg; //TODO: Is there an enum for this? or is it only GM?
  }

  pSession->getChatConnection()->queueOutPacket( tellPacket );
}

void Sapphire::Network::GameConnection::chatToChannelHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ChatChannelPacket< Client::FFXIVIpcChatToChannel >( inPacket );
  auto& data = packet.data();

  auto& chatChannelMgr = Common::Service< ChatChannelMgr >::ref();

  std::string message = std::string( data.message );

  chatChannelMgr.sendMessageToChannel( data.channelID, player, message );
}

void Sapphire::Network::GameConnection::catalogSearch( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& marketMgr = Common::Service< MarketMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcCatalogSearch >( inPacket );
  const auto& data = packet.data();

  marketMgr.searchMarketboard(
    player,
    data.SearchCategory,
    data.MaxLevel,
    data.ClassJob,
    data.ItemName,
    data.RequestKey,
    data.NextIndex
  );
}

void Sapphire::Network::GameConnection::marketBoardRequestItemInfo( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcMarketBoardRequestItemListingInfo >( inPacket );

  auto& marketMgr = Common::Service< MarketMgr >::ref();

  marketMgr.requestItemListingInfo( player, packet.data().catalogId, packet.data().requestId );
}

void Sapphire::Network::GameConnection::marketBoardRequestItemListings( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcMarketBoardRequestItemListings >( inPacket );

  auto& marketMgr = Common::Service< MarketMgr >::ref();

  marketMgr.requestItemListings( player, packet.data().itemCatalogId );
}

void Sapphire::Network::GameConnection::getFcStatus( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{

}

void Sapphire::Network::GameConnection::getFcProfile( const Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcGetFcProfile >( inPacket );

  auto& server = Common::Service< World::WorldServer >::ref();

  auto resultPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcGetFcProfileResult >( player.getId() );
  resultPacket->data().TargetCharacterID = packet.data().TargetCharacterID;
  resultPacket->data().TargetEntityID = packet.data().TargetEntityID;

  // haha test code
  resultPacket->data().FreeCompanyID = 1;
  resultPacket->data().CrestID = 0x0001000100010001;
  resultPacket->data().LandID = Common::INVALID_GAME_OBJECT_ID64;
  resultPacket->data().OnlineMemberCount = 69;
  resultPacket->data().TotalMemberCount = 420;
  resultPacket->data().JoinRequestCount = 69;
  resultPacket->data().FcRank = 1;
  resultPacket->data().FcStatus = 1;
  resultPacket->data().FcRole = 1;
  resultPacket->data().FcActivity = 1;
  resultPacket->data().GrandCompanyID = 1;
  resultPacket->data().CreateDate = 1587305592;
  resultPacket->data().Reputation = 500;
  resultPacket->data().FcActiveTimeFlag = 0xFF;
  resultPacket->data().FcJoinRequestFlag = 0xFF;
  strcpy( resultPacket->data().MasterCharacterName, "Biggus Dickus" );
  strcpy( resultPacket->data().FcTag, "Wang" );
  strcpy( resultPacket->data().FreeCompanyName, "Test FC" );
  strcpy( resultPacket->data().CompanyMotto, "nobody here but us chickens" );


  server.queueForPlayer( player.getCharacterId(), resultPacket );

}

void Sapphire::Network::GameConnection::getRequestItemListHandler( const Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{

}
