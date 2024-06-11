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
#include "Territory/Housing/HousingInteriorTerritory.h"
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
#include "Network/PacketWrappers/UpdateInventorySlotPacket.h"

#include "Manager/DebugCommandMgr.h"
#include "Manager/EventMgr.h"
#include "Manager/MarketMgr.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/HousingMgr.h"
#include "Manager/RNGMgr.h"
#include "Manager/ItemMgr.h"
#include "Manager/PartyMgr.h"
#include "Manager/ChatChannelMgr.h"

#include "Action/Action.h"
#include "Inventory/Item.h"

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

  auto searchInfoPacket = makeZonePacket< FFXIVIpcSetSearchInfo >( player.getId() );
  searchInfoPacket->data().onlineStatusFlags = status;
  searchInfoPacket->data().selectRegion = player.getSearchSelectRegion();
  strcpy( searchInfoPacket->data().searchMessage, player.getSearchMessage() );
  queueOutPacket( searchInfoPacket );

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
  if( player.isLogin() )
  {
    player.sendQuestInfo();

    // TODO: load and save this data instead of hardcoding
    auto gcPacket = makeZonePacket< FFXIVGCAffiliation >( player.getId() );
    gcPacket->data().gcId = player.getGc();
    gcPacket->data().gcRank[ 0 ] = player.getGcRankArray()[ 0 ];
    gcPacket->data().gcRank[ 1 ] = player.getGcRankArray()[ 1 ];
    gcPacket->data().gcRank[ 2 ] = player.getGcRankArray()[ 2 ];
    player.queuePacket( gcPacket );
  }

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

    auto fillEntryAt = [ &listPacket ]( int i, Entity::PlayerPtr nextPlayer, bool isLeader )
    {
      listPacket->data().entries[ i ].bytes[ 2 ] = nextPlayer->getCurrentTerritory()->getTerritoryTypeId();
      listPacket->data().entries[ i ].bytes[ 3 ] = 0x80;
      listPacket->data().entries[ i ].bytes[ 4 ] = 0x02;
      listPacket->data().entries[ i ].bytes[ 6 ] = 0x3B;
      listPacket->data().entries[ i ].bytes[ 8 ] = isLeader;
      listPacket->data().entries[ i ].bytes[ 11 ] = 0x10;
      listPacket->data().entries[ i ].classJob = static_cast< uint8_t >( nextPlayer->getClass() );
      listPacket->data().entries[ i ].contentId = nextPlayer->getContentId();
      listPacket->data().entries[ i ].level = nextPlayer->getLevel();
      listPacket->data().entries[ i ].zoneId = nextPlayer->getCurrentTerritory()->getTerritoryTypeId();
      listPacket->data().entries[ i ].zoneId1 = 0x0100;
      // TODO: no idea what this does
      //listPacket.data().entries[0].one = 1;

      memcpy( listPacket->data().entries[ i ].name, nextPlayer->getName().c_str(), strlen( nextPlayer->getName().c_str() ) );

      // GC icon
      listPacket->data().entries[ i ].bytes1[ 0 ] = 2;
      // client language J = 0, E = 1, D = 2, F = 3
      listPacket->data().entries[ i ].bytes1[ 1 ] = 1;
      // user language settings flag J = 1, E = 2, D = 4, F = 8
      listPacket->data().entries[ i ].bytes1[ 2 ] = 1 + 2 + 4 + 8; 
      listPacket->data().entries[ i ].onlineStatusMask = nextPlayer->getOnlineStatusMask();
    };
    auto nextPlayer = player.getAsPlayer();
    fillEntryAt( 0, nextPlayer, false );
    if( player.getPartyId() != 0 )
    {
      // fill party members
      auto& partyMgr = Common::Service< World::Manager::PartyMgr >::ref();
      auto& server = Common::Service< World::ServerMgr >::ref();
      auto pParty = partyMgr.getParty( player.getPartyId() );
      assert( pParty );

      int i = 1;
      for( auto id : pParty->MemberId )
      {
        nextPlayer = server.getSession( id )->getPlayer();
        if( nextPlayer->getId() == player.getId() )
        {
          // data already in entry 0, only change the leader flag
          listPacket->data().entries[ 0 ].bytes[ 8 ] = pParty->LeaderId == id;
          continue;
        }
        fillEntryAt( i, nextPlayer, pParty->LeaderId == id );
        i++;
      }
    }

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
    tellPacket->data().flags |= ChatFromType::GmTellMsg;
  }

  pTargetPlayer->queueChatPacket( tellPacket );
}

void Sapphire::Network::GameConnection::channelChatHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ChatChannelPacket< Client::FFXIVIpcChannelChatHandler >( inPacket );
  auto& data = packet.data();

  auto& chatChannelMgr = Common::Service< ChatChannelMgr >::ref();

  std::string message = std::string( data.message );

  chatChannelMgr.sendMessageToChannel( data.channelId, player, message );
}

void Sapphire::Network::GameConnection::performNoteHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto performPacket = makeZonePacket< FFXIVIpcPerformNote >( player.getId() );
  memcpy( &performPacket->data().data[ 0 ], &inPacket.data[ 0x10 ], 16 );
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

void Sapphire::Network::GameConnection::housingEditExterior( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& housingMgr = Common::Service< HousingMgr >::ref();
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcHousingEditExterior >( inPacket );
  auto terri = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() );
  if( !terri )
    return;

  std::vector< uint16_t > containerList;
  std::vector< uint8_t > slotList;
  for( int i = 0; i < 9; i++ )
  {
    auto container = packet.data().container[i];
    containerList.push_back( container );
    slotList.push_back( container != 0x270F ? static_cast< uint8_t >( packet.data().slot[i] ) : 0xFF );
  }

  housingMgr.editAppearance( false, player, terri->getLand( packet.data().landId )->getLandIdent(), containerList, slotList, packet.data().removeFlag );
}

void Sapphire::Network::GameConnection::housingEditInterior( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& housingMgr = Common::Service< HousingMgr >::ref();
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcHousingEditInterior >( inPacket );
  auto terri = std::dynamic_pointer_cast< World::Territory::Housing::HousingInteriorTerritory >( player.getCurrentTerritory() );
  if( !terri )
    return;
  
  std::vector< uint16_t > containerList;
  std::vector< uint8_t > slotList;
  for( int i = 0; i < 10; i++ )
  {
    auto container = packet.data().container[i];
    containerList.push_back( container );
    slotList.push_back( container != 0x270F ? static_cast< uint8_t >( packet.data().slot[i] ) : 0xFF );
  }

  housingMgr.editAppearance( true, player, terri->getLandIdent(), containerList, slotList, 0 );
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
  switch( action )
  {
    case 0x1F5: // emote
    {
      auto emote = packet.data().param1;
      if( emote == 0x32 || emote == 0x33 ) // "/sit"
      {
        auto param4 = packet.data().param4;
        auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
        auto emoteData = exdData.get< Data::Emote >( emote );

        if( !emoteData )
          break;

        player.setPos( packet.data().position );
        player.setRot( Util::floatFromUInt16Rot( param4 ) );
        if( emote == 0x32 && player.hasInRangeActor() )
        {
          auto setpos = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
          setpos->data().r16 = param4;
          setpos->data().waitForLoad = 18;
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
      break;
    }
    case 0x1F8:
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
      break;
    }
    case 0x25E: // coming out from water
    case 0xD1: // underwater town portal
    {
      auto p = makeZonePacket< FFXIVIpcPrepareZoning >( player.getId() );
      p->data().targetZone = player.getCurrentTerritory()->getTerritoryTypeId();
      p->data().param4 = action == 0xD1 ? 14 : 227;
      p->data().hideChar = action == 0xD1 ? 2 : 1;
      p->data().fadeOut = action == 0xD1 ? 24 : 25;
      p->data().fadeOutTime = 1;
      p->data().unknown = action == 0xD1 ? 4 : 6;
      auto x = packet.data().position.x;
      auto y = packet.data().position.y;
      auto z = packet.data().position.z;
      auto rot = player.getRot();
      if( action == 0xD1 )
      {
        auto exitRange = packet.data().param1;

        auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
        auto exit = instanceObjectCache.getExitRange( p->data().targetZone, exitRange );
        if( exit )
        {
          player.sendDebug( "exitRange {0} found!", exitRange );
          auto destZone = exit->data.destTerritoryType;
          if( destZone == 0 )
            destZone = p->data().targetZone;
          else
            p->data().targetZone = destZone;
          auto pop = instanceObjectCache.getPopRange( destZone, exit->data.destInstanceObjectId );
          if( pop )
          {
            player.sendDebug( "popRange {0} found!", exit->data.destInstanceObjectId );
            x = pop->header.transform.translation.x;
            y = pop->header.transform.translation.y;
            z = pop->header.transform.translation.z;
            //rot = pop->header.transform.rotation.y; all x/y/z not correct, maybe we don't need it since we have to be facing the portal anyway?
          }
          else
          {
            player.sendUrgent( "popRange {0} not found in {1}!", exit->data.destInstanceObjectId, destZone );
          }
        }
        else
        {
          player.sendUrgent( "exitRange {0} not found in {1}!", exitRange, p->data().targetZone );
        }
      }
      player.queuePacket( p );
      player.setPos( x, y, z, true );
      player.setRot( rot );
      auto setPos = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
      setPos->data().r16 = Common::Util::floatToUInt16Rot( player.getRot() );
      setPos->data().x = x;
      setPos->data().y = y;
      setPos->data().z = z;
      setPos->data().waitForLoad = action == 0xD1 ? 24 : 25;
      setPos->data().unknown1 = 0;
      player.queuePacket( setPos ); // this packet needs a delay of 0.8 second to wait for the client finishing its water animation otherwise it looks odd.
      break;
    }
  }
}

void Sapphire::Network::GameConnection::diveHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packetIn = ZoneChannelPacket< Client::FFXIVIpcDive >( inPacket );
  auto p = makeZonePacket< FFXIVIpcPrepareZoning >( player.getId() );
  p->data().targetZone = player.getCurrentTerritory()->getTerritoryTypeId();
  p->data().param4 = 218;
  p->data().hideChar = 1;
  p->data().fadeOut = 25;
  p->data().fadeOutTime = 1;
  p->data().unknown = 6;
  player.queuePacket( p );

  player.setStance( Common::Stance::Passive );

  auto x = packetIn.data().posTarget.x;
  auto y = packetIn.data().posTarget.y;
  auto z = packetIn.data().posTarget.z;
  player.setPos( x, y, z, true );
  auto setPos = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
  setPos->data().r16 = Common::Util::floatToUInt16Rot( player.getRot() );
  setPos->data().x = x;
  setPos->data().y = y;
  setPos->data().z = z;
  setPos->data().waitForLoad = 25;
  setPos->data().unknown1 = 0;
  player.queuePacket( setPos ); // need delay, same as above.
}

// Also used for gearsets
void Sapphire::Network::GameConnection::inventoryEquipRecommendedItemsHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVInventoryEquipRecommendedItemsHandler >( inPacket );

  // Loop over all slots
  for (int slot = 0; slot < 14; slot++ )
  {
    const auto fromSlot = packet.data().containerIndex[ slot ];
    const auto fromContainer = packet.data().storageId[ slot ];
    
    if ( fromContainer == Common::GearSet0 )
      continue;

    const auto fromItem = fromSlot == -1 ? nullptr : player.getItemAt( fromContainer, fromSlot );
    const auto equippedItem = player.getItemAt( Common::GearSet0, slot );

    if ( fromItem && equippedItem )
    {
      player.swapItem( fromContainer, fromSlot, Common::GearSet0, slot, slot == 0 || slot == 13 );
      player.queuePacket( std::make_shared< UpdateInventorySlotPacket >( player.getId(), fromSlot, fromContainer, *equippedItem, 0 ) );
      player.queuePacket( std::make_shared< UpdateInventorySlotPacket >( player.getId(), slot, Common::GearSet0, *fromItem, 0 ) );
    }
    else if ( fromItem && !equippedItem )
    {
      player.moveItem( fromContainer, fromSlot, Common::GearSet0, slot, slot == 0 || slot == 13 );
      player.queuePacket( std::make_shared< UpdateInventorySlotPacket >( player.getId(), fromSlot, fromContainer, 0 ) );
      player.queuePacket( std::make_shared< UpdateInventorySlotPacket >( player.getId(), slot, Common::GearSet0, *fromItem, 0 ) );
    }
    else if ( !fromItem && equippedItem )
    {
      auto containerId = World::Manager::ItemMgr::getCharaEquipSlotCategoryToArmoryId( static_cast< Common::EquipSlotCategory >( equippedItem->getEquipSlotCategory() ) );
      auto freeContainerSlot = player.getFreeContainerSlot( containerId );
      if( freeContainerSlot.second > 0 )
        player.moveItem( Common::GearSet0, slot, freeContainerSlot.first, freeContainerSlot.second, slot == 0 || slot == 13 );
      else
      {
        for( int i = Common::Bag0; i <= Common::Bag3; i++ )
        {
          freeContainerSlot = player.getFreeContainerSlot( i );
          if( freeContainerSlot.second > 0 )
            break;
        }
        if( freeContainerSlot.second > 0 )
          player.moveItem( Common::GearSet0, slot, freeContainerSlot.first, freeContainerSlot.second, slot == 0 || slot == 13 );
        else
        {
          player.sendUrgent( "No free inventory space to swap out item at container:{}, slot{}", Common::GearSet0, slot );
          continue;
        }
      }
      player.queuePacket( std::make_shared< UpdateInventorySlotPacket >( player.getId(), freeContainerSlot.second, freeContainerSlot.first, *equippedItem, 0 ) );
      player.queuePacket( std::make_shared< UpdateInventorySlotPacket >( player.getId(), slot, Common::GearSet0, 0 ) );
    }
  }

  // Send the gear inventory
  player.sendGearInventory();

  // Send the player stats
  player.sendStats();

  // Send the player model
  player.sendModel();

  // Send the item level
  player.calculateItemLevel();
  player.sendItemLevel();

  // Send status effect update
  player.sendStatusEffectUpdate();

  if( packet.data().contextId < 0xFE ) // >= 0xFE are not geaesets
  {
    auto actorControl2 = makeZonePacket< FFXIVIpcActorControlSelf >( player.getId(), player.getId() );
    actorControl2->data().category = static_cast< uint16_t >( Network::ActorControl::GearSetEquipMsg );
    actorControl2->data().param1 = packet.data().contextId;
    player.queuePacket( actorControl2 );
  }
}