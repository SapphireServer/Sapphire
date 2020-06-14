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
#include "Territory/ZonePosition.h"
#include "Territory/House.h"
#include "Territory/InstanceObjectCache.h"

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

#include "Action/Action.h"

#include "Session.h"
#include "ServerMgr.h"
#include "Forwards.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

void Sapphire::Network::GameConnection::fcInfoReqHandler( const Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  // TODO: use new packet struct for this
  //GamePacketPtr pPe( new GamePacket( 0xDD, 0x78, player.getId(), player.getId() ) );
  //pPe->setValAt< uint8_t >( 0x48, 0x01 );
  //queueOutPacket( pPe );
}

void Sapphire::Network::GameConnection::setSearchInfoHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                              Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcSetSearchInfo >( inPacket );

  const auto inval = packet.data().status1;
  const auto inval1 = packet.data().status2;
  const auto status = packet.data().status;
  const auto selectRegion = packet.data().language;

  player.setSearchInfo( selectRegion, 0, packet.data().searchComment );

  player.setOnlineStatusMask( status );

  if( player.isNewAdventurer() && !( inval & 0x01000000 ) )
    // mark player as not new adventurer anymore
    player.setNewAdventurer( false );
  else if( inval & 0x01000000 )
    // mark player as new adventurer
    player.setNewAdventurer( true );

  auto statusPacket = makeZonePacket< FFXIVIpcSetOnlineStatus >( player.getId() );
  statusPacket->data().onlineStatusFlags = status;
  queueOutPacket( statusPacket );

  auto searchInfoPacket = makeZonePacket< FFXIVIpcSetSearchInfo >( player.getId() );
  searchInfoPacket->data().onlineStatusFlags = status;
  searchInfoPacket->data().selectRegion = player.getSearchSelectRegion();
  strcpy( searchInfoPacket->data().searchMessage, player.getSearchMessage() );
  queueOutPacket( searchInfoPacket );

  player.sendToInRangeSet( makeActorControl( player.getId(), SetStatusIcon,
                                             static_cast< uint8_t >( player.getOnlineStatus() ) ), true );
}

void Sapphire::Network::GameConnection::reqSearchInfoHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                              Entity::Player& player )
{
  auto searchInfoPacket = makeZonePacket< FFXIVIpcInitSearchInfo >( player.getId() );
  searchInfoPacket->data().onlineStatusFlags = player.getOnlineStatusMask();
  searchInfoPacket->data().selectRegion = player.getSearchSelectRegion();
  strcpy( searchInfoPacket->data().searchMessage, player.getSearchMessage() );
  queueOutPacket( searchInfoPacket );
}

void Sapphire::Network::GameConnection::reqExamineSearchCommentHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                        Entity::Player& player )
{

  auto targetId = *reinterpret_cast< const uint32_t* >( &inPacket.data[ 0x10 ] );
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();
  auto pSession = serverMgr.getSession( targetId );

  Logger::debug( "reqExamineSearchCommentHandler: {0}", targetId );

  if( pSession )
  {
    auto pPlayer = pSession->getPlayer();

    if( pPlayer )
    {
      if( pPlayer->isActingAsGm() || pPlayer->getZoneId() != player.getZoneId() )
        return;

      // retail sends the requester's id as both (isForSelf)
      auto searchInfoPacket = makeZonePacket< FFXIVIpcExamineSearchComment >( player.getId() );
      searchInfoPacket->data().charId = targetId;
      strcpy( searchInfoPacket->data().searchComment, pPlayer->getSearchMessage() );
      player.queuePacket( searchInfoPacket );
    }
  }
}

void Sapphire::Network::GameConnection::reqExamineFcInfo( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{

  auto targetId = *reinterpret_cast< const uint32_t* >( &inPacket.data[ 0x18 ] );

  auto& serverMgr = Common::Service< World::ServerMgr >::ref();
  auto pSession = serverMgr.getSession( targetId );

  Logger::debug( "reqExamineFcInfo: {0}", targetId );

  if( pSession )
  {
    auto pPlayer = pSession->getPlayer();

    if( pPlayer )
    {
      if( pPlayer->isActingAsGm() || pPlayer->getZoneId() != player.getZoneId() )
        return;

      // retail sends the requester's id as both (isForSelf)
      auto examineFcInfoPacket = makeZonePacket< FFXIVIpcExamineFreeCompanyInfo >( player.getId() );
      examineFcInfoPacket->data().charId = targetId;
      // todo: populate with fc info

      player.queuePacket( examineFcInfoPacket );
    }
  }
}

void Sapphire::Network::GameConnection::linkshellListHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                              Entity::Player& player )
{
  auto linkshellListPacket = makeZonePacket< FFXIVIpcLinkshellList >( player.getId() );
  queueOutPacket( linkshellListPacket );
}

void Sapphire::Network::GameConnection::updatePositionHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                               Entity::Player& player )
{
  // if the player is marked for zoning we no longer want to update his pos
  if( player.isMarkedForZoning() )
    return;

  const auto updatePositionPacket = ZoneChannelPacket< Client::FFXIVIpcUpdatePosition >( inPacket );

  bool bPosChanged = true;
  if( updatePositionPacket.data().position == player.getPos() )
    bPosChanged = false;

  //if( !bPosChanged && player.getRot() == updatePositionPacket.data().rotation )
    //return;

  player.setRot( updatePositionPacket.data().rotation );
  player.setPos( updatePositionPacket.data().position );

  if( ( player.getCurrentAction() != nullptr ) && bPosChanged )
    player.getCurrentAction()->setInterrupted( Common::ActionInterruptType::RegularInterrupt );

  // if no one is in range, don't bother trying to send a position update
  if( !player.hasInRangeActor() )
    return;

  auto clientAnimationType = updatePositionPacket.data().clientAnimationType;
  auto animationState = updatePositionPacket.data().animationState;
  auto animationType = updatePositionPacket.data().animationType;
  auto headRotation = updatePositionPacket.data().headPosition;
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
    if( animationState == MoveState::LeaveCollision )
    {
      if( orgAnimationType & clientAnimationType )
        animationType += 0x10;
      else
        animationType += 0x04;
    }
    if( animationState == MoveState::StartFalling )
      player.m_falling = true;
    if( animationState == MoveState::EnterCollision )
    {
      animationType = 2;
      player.m_falling = false;
    }
  }

  if( player.m_falling )
  {
    animationType += 0x10;
    unknownRotation = 0x7F;
  }


  uint64_t currentTime = Util::getTimeMs();

  player.m_lastMoveTime = currentTime;
  player.m_lastMoveflag = animationType;

  auto movePacket = std::make_shared< MoveActorPacket >( player, headRotation, animationType, animationState, animationSpeed, unknownRotation );
  player.sendToInRangeSet( movePacket );
}

void
Sapphire::Network::GameConnection::reqEquipDisplayFlagsHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                Entity::Player& player )
{
  player.setEquipDisplayFlags( inPacket.data[ 0x10 ] );

  player.sendDebug( "EquipDisplayFlag CHANGE: {0}", player.getEquipDisplayFlags() );
}

void Sapphire::Network::GameConnection::zoneLineHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                         Entity::Player& player )
{

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcZoneLineHandler >( inPacket );
  const auto zoneLineId = packet.data().zoneLineId;

  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
  auto tInfo = player.getCurrentTerritory()->getTerritoryTypeInfo();

  auto pExitRange = instanceObjectCache.getExitRange( player.getTerritoryTypeId(), zoneLineId );

  Common::FFXIVARR_POSITION3 targetPos{};
  uint32_t targetZone;
  float rotation = 0.0f;

  if( pExitRange )
  {
    auto pPopRange = instanceObjectCache.getPopRange( pExitRange->data.destTerritoryType,
                                                       pExitRange->data.destInstanceObjectId );
    if( pPopRange )
    {
      targetZone = pExitRange->data.destTerritoryType;
      rotation = pPopRange->header.transform.rotation.y;
      targetPos = Common::FFXIVARR_POSITION3 { pPopRange->header.transform.translation.x,
                                               pPopRange->header.transform.translation.y,
                                               pPopRange->header.transform.translation.z };

      player.sendDebug( "ZoneLine #{0} found.", zoneLineId );

      auto preparePacket = makeZonePacket< FFXIVIpcPrepareZoning >( player.getId() );
      preparePacket->data().targetZone = pExitRange->data.destTerritoryType;

      player.queuePacket( preparePacket );

    }
  }

  player.sendDebug( "Walking ZoneLine#{0}", zoneLineId );

  player.performZoning( targetZone, targetPos, rotation );
}


void Sapphire::Network::GameConnection::discoveryHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
  auto tInfo = player.getCurrentTerritory()->getTerritoryTypeInfo();
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcDiscoveryHandler >( inPacket );
  const auto positionRef = packet.data().positionRef;

  auto pRefInfo = instanceObjectCache.getMapRange( player.getTerritoryTypeId(), positionRef );

  player.sendDebug( "Discovery ref pos id#{0}", positionRef );

  if( pRefInfo )
  {
    auto discoveryPacket = makeZonePacket< FFXIVIpcDiscovery >( player.getId() );
    discoveryPacket->data().mapId = tInfo->map;
    discoveryPacket->data().mapPartId = pRefInfo->data.discoveryIndex;
    player.queuePacket( discoveryPacket );
    player.discover( tInfo->map, pRefInfo->data.discoveryIndex );
  }

}


void Sapphire::Network::GameConnection::playTimeHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                         Entity::Player& player )
{
  auto playTimePacket = makeZonePacket< FFXIVIpcPlayTime >( player.getId() );
  playTimePacket->data().playTimeInMinutes = player.getPlayTime() / 60;
  player.queuePacket( playTimePacket );
}


void Sapphire::Network::GameConnection::initHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                     Entity::Player& player )
{
  // init handler means this is a login procedure
  player.setIsLogin( true );

  player.sendZonePackets();
}


void Sapphire::Network::GameConnection::blackListHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  uint8_t count = inPacket.data[ 0x11 ];

  auto blackListPacket = makeZonePacket< FFXIVIpcBlackList >( player.getId() );
  blackListPacket->data().sequence = count;
  // TODO: Fill with actual blacklist data
  //blackListPacket.data().entry[0].contentId = 1;
  //sprintf( blackListPacket.data().entry[0].name, "Test Test" );
  queueOutPacket( blackListPacket );

}


void Sapphire::Network::GameConnection::pingHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                     Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcPingHandler >( inPacket );

  queueOutPacket( std::make_shared< Server::PingPacket >( player, packet.data().timestamp ) );

  player.setLastPing( Common::Util::getTimeSeconds() );
}


void Sapphire::Network::GameConnection::finishLoadingHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                              Entity::Player& player )
{
  player.sendQuestInfo();

  // TODO: load and save this data instead of hardcoding
  auto gcPacket = makeZonePacket< FFXIVGCAffiliation >( player.getId() );
  gcPacket->data().gcId = player.getGc();
  gcPacket->data().gcRank[ 0 ] = player.getGcRankArray()[ 0 ];
  gcPacket->data().gcRank[ 1 ] = player.getGcRankArray()[ 1 ];
  gcPacket->data().gcRank[ 2 ] = player.getGcRankArray()[ 2 ];
  player.queuePacket( gcPacket );

  player.getCurrentTerritory()->onFinishLoading( player );

  // player is done zoning
  player.setLoadingComplete( true );

  // if this is a login event
  if( player.isLogin() )
  {
    // fire the onLogin Event
    player.onLogin();
    player.setIsLogin( false );
  }

  // spawn the player for himself
  player.spawn( player.getAsPlayer() );

  player.gaugeClear();
  player.sendActorGauge();

  // notify the zone of a change in position to force an "inRangeActor" update
  player.getCurrentTerritory()->updateActorPosition( player );
}

void Sapphire::Network::GameConnection::socialListHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{

  uint8_t type = inPacket.data[ 0x1A ];
  uint8_t count = inPacket.data[ 0x1B ];

  if( type == 1 )
  { // party list

    auto listPacket = makeZonePacket< FFXIVIpcSocialList >( player.getId() );

    listPacket->data().type = 1;
    listPacket->data().sequence = count;

    int32_t entrysizes = sizeof( listPacket->data().entries );
    memset( listPacket->data().entries, 0, sizeof( listPacket->data().entries ) );

    listPacket->data().entries[ 0 ].bytes[ 2 ] = player.getCurrentTerritory()->getTerritoryTypeId();
    listPacket->data().entries[ 0 ].bytes[ 3 ] = 0x80;
    listPacket->data().entries[ 0 ].bytes[ 4 ] = 0x02;
    listPacket->data().entries[ 0 ].bytes[ 6 ] = 0x3B;
    listPacket->data().entries[ 0 ].bytes[ 11 ] = 0x10;
    listPacket->data().entries[ 0 ].classJob = static_cast< uint8_t >( player.getClass() );
    listPacket->data().entries[ 0 ].contentId = player.getContentId();
    listPacket->data().entries[ 0 ].level = player.getLevel();
    listPacket->data().entries[ 0 ].zoneId = player.getCurrentTerritory()->getTerritoryTypeId();
    listPacket->data().entries[ 0 ].zoneId1 = 0x0100;
    // TODO: no idea what this does
    //listPacket.data().entries[0].one = 1;

    memcpy( listPacket->data().entries[ 0 ].name, player.getName().c_str(), strlen( player.getName().c_str() ) );

    // GC icon
    listPacket->data().entries[ 0 ].bytes1[ 0 ] = 2;
    // client language J = 0, E = 1, D = 2, F = 3
    listPacket->data().entries[ 0 ].bytes1[ 1 ] = 1;
    // user language settings flag J = 1, E = 2, D = 4, F = 8
    listPacket->data().entries[ 0 ].bytes1[ 2 ] = 1 + 2; 
    listPacket->data().entries[ 0 ].onlineStatusMask = player.getOnlineStatusMask();

    queueOutPacket( listPacket );

  }
  else if( type == 2 )
  { // friend list
    auto listPacket = makeZonePacket< FFXIVIpcSocialList >( player.getId() );
    listPacket->data().type = 2;
    listPacket->data().sequence = count;
    memset( listPacket->data().entries, 0, sizeof( listPacket->data().entries ) );

  }
  else if( type == 0x0e )
  { // player search result
    // TODO: implement player search
  }

}

void Sapphire::Network::GameConnection::chatHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                     Entity::Player& player )
{
  auto& debugCommandMgr = Common::Service< DebugCommandMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcChatHandler >( inPacket );

  if( packet.data().message[ 0 ] == '!' )
  {
    // execute game console command
    debugCommandMgr.execCommand( const_cast< char* >( packet.data().message ) + 1, player );
    return;
  }

  auto chatType = packet.data().chatType;

  //ToDo, need to implement sending GM chat types.
  auto chatPacket = std::make_shared< Server::ChatPacket >( player, chatType, packet.data().message );

  switch( chatType )
  {
    case ChatType::Say:
    {
      if( player.isActingAsGm() )
        chatPacket->data().chatType = ChatType::GMSay;

      player.getCurrentTerritory()->queuePacketForRange( player, 50, chatPacket );
      break;
    }
    case ChatType::Yell:
    {
      if( player.isActingAsGm() )
        chatPacket->data().chatType = ChatType::GMYell;

      player.getCurrentTerritory()->queuePacketForRange( player, 6000, chatPacket );
      break;
    }
    case ChatType::Shout:
    {
      if( player.isActingAsGm() )
        chatPacket->data().chatType = ChatType::GMShout;

      player.getCurrentTerritory()->queuePacketForRange( player, 6000, chatPacket );
      break;
    }
    default:
    {
      player.getCurrentTerritory()->queuePacketForRange( player, 50, chatPacket );
      break;
    }
  }

}

// TODO: this handler needs to be improved for timed logout, also the session should be instantly removed
// currently we wait for the session to just time out after logout, this can be a problem is the user tries to
// log right back in.
// Also the packet needs to be converted to an ipc structure
void Sapphire::Network::GameConnection::logoutHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                       Entity::Player& player )
{
  auto logoutPacket = makeZonePacket< FFXIVIpcLogout >( player.getId() );
  logoutPacket->data().flags1 = 0x02;
  logoutPacket->data().flags2 = 0x2000;
  queueOutPacket( logoutPacket );

  player.setMarkedForRemoval();
}


void Sapphire::Network::GameConnection::tellHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                     Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcTellHandler >( inPacket );

  auto& serverMgr = Common::Service< World::ServerMgr >::ref();

  auto pSession = serverMgr.getSession( packet.data().targetPCName );

  if( !pSession )
  {
    auto tellErrPacket = makeZonePacket< FFXIVIpcTellErrNotFound >( player.getId() );
    strcpy( tellErrPacket->data().receipientName, packet.data().targetPCName );
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

  if( pTargetPlayer->hasStateFlag( PlayerStateFlag::BoundByDuty ) && !player.isActingAsGm() )
  {
    // send error for player bound by duty
    // TODO: implement me
    return;
  }

  if( pTargetPlayer->getOnlineStatus() == OnlineStatus::Busy && !player.isActingAsGm() )
  {
    // send error for player being busy
    // TODO: implement me ( i've seen this done with packet type 67 i think )
    return;
  }

  auto tellPacket = makeChatPacket< FFXIVIpcTell >( player.getId() );
  strcpy( tellPacket->data().msg, packet.data().message );
  strcpy( tellPacket->data().receipientName, player.getName().c_str() );
  // TODO: world id from server
  tellPacket->data().contentId = player.getContentId();
  tellPacket->data().worldId = 67;

  if( player.isActingAsGm() )
  {
    tellPacket->data().flags |= TellFlags::GmTellMsg;
  }

  pTargetPlayer->queueChatPacket( tellPacket );
}

void Sapphire::Network::GameConnection::performNoteHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto performPacket = makeZonePacket< FFXIVIpcPerformNote >( player.getId() );
  memcpy( &performPacket->data().data[ 0 ], &inPacket.data[ 0x10 ], 32 );
  player.sendToInRangeSet( performPacket );
}

void Sapphire::Network::GameConnection::landRenameHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcRenameLandHandler >( inPacket );

  auto& housingMgr = Common::Service< HousingMgr >::ref();

  auto landSetId = housingMgr.toLandSetId( packet.data().ident.territoryTypeId, packet.data().ident.wardNum );

  auto pZone = housingMgr.getHousingZoneByLandSetId( landSetId );
  if( !pZone )
    return;

  auto pLand = pZone->getLand( packet.data().ident.landId );
  if( !pLand )
    return;

  // todo: check perms for fc houses and shit
  if( pLand->getOwnerId() != player.getId() )
    return;

  auto pHouse = pLand->getHouse();
  if( pHouse )
    pHouse->setHouseName( packet.data().houseName );

  // todo: this packet is weird, retail sends it with some unknown shit at the start but it doesn't seem to do anything
  auto nameUpdatePacket = makeZonePacket< Server::FFXIVIpcLandUpdateHouseName >( player.getId() );
  memcpy( &nameUpdatePacket->data().houseName, &packet.data().houseName, sizeof( packet.data().houseName ) );

  // todo: who does this get sent to? just the person who renamed it?
  player.queuePacket( nameUpdatePacket );
}

void Sapphire::Network::GameConnection::buildPresetHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcBuildPresetHandler >( inPacket );

  auto& housingMgr = Common::Service< HousingMgr >::ref();
  housingMgr.buildPresetEstate( player, packet.data().plotNum, packet.data().itemId );
}

void Sapphire::Network::GameConnection::housingUpdateGreetingHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                      Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcHousingUpdateHouseGreeting >( inPacket );

  auto& housingMgr = Common::Service< HousingMgr >::ref();

  housingMgr.updateEstateGreeting( player, packet.data().ident, std::string( packet.data().greeting ) );
}

void Sapphire::Network::GameConnection::reqPlaceHousingItem( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                             Entity::Player& player )
{
  auto& housingMgr = Common::Service< HousingMgr >::ref();
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcReqPlaceHousingItem >( inPacket );
  const auto& data = packet.data();

  if( data.shouldPlaceItem == 1 )
  {
    housingMgr.reqPlaceHousingItem( player, data.landId, data.sourceInvContainerId, data.sourceInvSlotId,
                                     data.position, data.rotation );
  }
  else
    housingMgr.reqPlaceItemInStore( player, data.landId, data.sourceInvContainerId, data.sourceInvSlotId );

}

void Sapphire::Network::GameConnection::reqMoveHousingItem( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto& housingMgr = Common::Service< HousingMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcHousingUpdateObjectPosition >( inPacket );
  const auto& data = packet.data();

  housingMgr.reqMoveHousingItem( player, data.ident, data.slot, data.pos, data.rotation );
}

void Sapphire::Network::GameConnection::marketBoardSearch( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& marketMgr = Common::Service< MarketMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcMarketBoardSearch >( inPacket );
  const auto& data = packet.data();

  std::string_view searchStr( data.searchStr );

  marketMgr.searchMarketboard( player, data.itemSearchCategory, data.maxEquipLevel, data.classJobId, data.searchStr,
                                data.requestId, data.startIdx );
}

void Sapphire::Network::GameConnection::marketBoardRequestItemInfo( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                    Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcMarketBoardRequestItemListingInfo >( inPacket );

  auto& marketMgr = Common::Service< MarketMgr >::ref();

  marketMgr.requestItemListingInfo( player, packet.data().catalogId, packet.data().requestId );
}

void Sapphire::Network::GameConnection::marketBoardRequestItemListings( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                        Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcMarketBoardRequestItemListings >( inPacket );

  auto& marketMgr = Common::Service< MarketMgr >::ref();

  marketMgr.requestItemListings( player, packet.data().itemCatalogId );
}

void Sapphire::Network::GameConnection::worldInteractionhandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
  Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcWorldInteractionHandler >( inPacket );
  auto action = packet.data().action;
  player.sendDebug( "WorldInteraction {}", action );
  if( action == 0x1F5 )
  {
    auto emote = packet.data().param1;
    if( emote == 0x32 || emote == 0x33 ) // "/sit"
    {
      auto param4 = packet.data().param4;
      auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
      auto emoteData = exdData.get< Data::Emote >( emote );

      if( !emoteData )
        return;

      player.setPos( packet.data().position );
      if( emote == 0x32 && player.hasInRangeActor() )
      {
        auto setpos = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
        setpos->data().r16 = param4;
        setpos->data().waitForLoad = 18;
        setpos->data().unknown1 = 1;
        setpos->data().x = packet.data().position.x;
        setpos->data().y = packet.data().position.y;
        setpos->data().z = packet.data().position.z;
        player.sendToInRangeSet( setpos, false );
      }
      player.sendToInRangeSet( makeActorControlTarget( player.getId(), ActorControl::ActorControlType::Emote, emote, 0, 0, param4, 0xE0000000 ), true );

      if( emote == 0x32 && emoteData->emoteMode != 0 )
      {
        player.setStance( Common::Stance::Passive );
        player.setAutoattack( false );
        player.setPersistentEmote( emoteData->emoteMode );
        player.setStatus( Common::ActorStatus::EmoteMode );
      }
    }
  }
  else if( action == 0x1F8 )
  {
    if( player.getPersistentEmote() > 0 )
    {
      auto param2 = packet.data().param2;

      player.setPos( packet.data().position );
      if( player.hasInRangeActor() )
      {
        auto setpos = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
        setpos->data().r16 = param2;
        setpos->data().waitForLoad = 18;
        setpos->data().unknown1 = 2;
        setpos->data().x = packet.data().position.x;
        setpos->data().y = packet.data().position.y;
        setpos->data().z = packet.data().position.z;
        player.sendToInRangeSet( setpos, false );
      }

      player.setPersistentEmote( 0 );
      player.emoteInterrupt();
      player.setStatus( Common::ActorStatus::Idle );
      auto pSetStatusPacket = makeActorControl( player.getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );
      player.sendToInRangeSet( pSetStatusPacket );
    }
  }
}