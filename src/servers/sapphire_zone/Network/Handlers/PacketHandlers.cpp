#include <boost/format.hpp>

#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacketNew.h>
#include <Network/CommonActorControl.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Chat/ServerChatDef.h>
#include <Database/DatabaseDef.h>
#include <Util/Util.h>

#include <unordered_map>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Logging/Logger.h>

#include "Network/GameConnection.h"

#include "Zone/TerritoryMgr.h"
#include "Zone/Zone.h"
#include "Zone/ZonePosition.h"

#include "Network/PacketWrappers/InitUIPacket.h"
#include "Network/PacketWrappers/PingPacket.h"
#include "Network/PacketWrappers/MoveActorPacket.h"
#include "Network/PacketWrappers/ChatPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "DebugCommand/DebugCommandHandler.h"

#include "Event/EventHelper.h"

#include "Action/Action.h"
#include "Action/ActionTeleport.h"

#include "Session.h"
#include "ServerZone.h"
#include "Forwards.h"
#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;
using namespace Core::Network::ActorControl;

void Core::Network::GameConnection::fcInfoReqHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                      Entity::Player& player )
{
  // TODO: use new packet struct for this
  //GamePacketPtr pPe( new GamePacket( 0xDD, 0x78, player.getId(), player.getId() ) );
  //pPe->setValAt< uint8_t >( 0x48, 0x01 );
  //queueOutPacket( pPe );
}

void Core::Network::GameConnection::setSearchInfoHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcSetSearchInfo >( inPacket );

  const auto& inval = packet.data().status1;
  const auto& inval1 = packet.data().status2;
  const auto& status = packet.data().status;
  const auto& selectRegion = packet.data().language;

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

  player.sendToInRangeSet( makeActorControl142( player.getId(), SetStatusIcon,
                                                static_cast< uint8_t >( player.getOnlineStatus() ) ), true );
}

void Core::Network::GameConnection::reqSearchInfoHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto searchInfoPacket = makeZonePacket< FFXIVIpcInitSearchInfo >( player.getId() );
  searchInfoPacket->data().onlineStatusFlags = player.getOnlineStatusMask();
  searchInfoPacket->data().selectRegion = player.getSearchSelectRegion();
  strcpy( searchInfoPacket->data().searchMessage, player.getSearchMessage() );
  queueOutPacket( searchInfoPacket );
}

void Core::Network::GameConnection::reqExamineSearchCommentHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{

  auto targetId = *reinterpret_cast< const uint32_t* >( &inPacket.data[ 0x10 ] );
  auto pSession = g_fw.get< Core::ServerZone >()->getSession( targetId );

  g_fw.get< Core::Logger >()->debug( std::to_string( targetId ) );

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

void Core::Network::GameConnection::reqExamineFcInfo( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{

  auto targetId = *reinterpret_cast< const uint32_t* >( &inPacket.data[ 0x18 ] );
  auto pSession = g_fw.get< Core::ServerZone >()->getSession( targetId );

  g_fw.get< Core::Logger >()->debug( std::to_string( targetId ) );

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

void Core::Network::GameConnection::linkshellListHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto linkshellListPacket = makeZonePacket< FFXIVIpcLinkshellList >( player.getId() );
  queueOutPacket( linkshellListPacket );
}

void Core::Network::GameConnection::updatePositionHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  // if the player is marked for zoning we no longer want to update his pos
  if( player.isMarkedForZoning() )
    return;

  Packets::FFXIVARR_PACKET_RAW copy = inPacket;

  struct testMov
  {
    uint32_t specialMovement : 23; // 0x00490FDA
    uint32_t strafe : 7;
    uint32_t moveBackward : 1;
    uint32_t strafeRight : 1; // if 0, strafe left.
  } IPC_OP_019A;

  struct testMov1
  {
    uint16_t bit1 : 1; // 0x00490FDA
    uint16_t bit2 : 1;
    uint16_t bit3 : 1;
    uint16_t bit4 : 1;
    uint16_t bit5 : 1;
    uint16_t bit6 : 1;
    uint16_t bit7 : 1;
    uint16_t bit8 : 1;
    uint16_t bit9 : 1; // 0x00490FDA
    uint16_t bit10 : 1;
    uint16_t bit11 : 1;
    uint16_t bit12 : 1;
    uint16_t bit13 : 1;
    uint16_t bit14 : 1;
    uint16_t bit15 : 1;
    uint16_t bit16 : 1;
  } IPC_OP_019AB;

  auto flags = *reinterpret_cast< uint16_t* >( &copy.data[ 0x18 ] );
  memcpy( &IPC_OP_019AB, &flags, 2 );

  auto flags1 = *reinterpret_cast< uint32_t* >( &copy.data[ 0x18 ] );
  memcpy( &IPC_OP_019A, &flags1, 4 );


  auto pLog = g_fw.get< Logger >();

  bool bPosChanged = false;
  if( ( player.getPos().x != *reinterpret_cast< float* >( &copy.data[ 0x1C ] ) ) ||
      ( player.getPos().y != *reinterpret_cast< float* >( &copy.data[ 0x20 ] ) ) ||
      ( player.getPos().z != *reinterpret_cast< float* >( &copy.data[ 0x24 ] ) ) )
    bPosChanged = true;
  if( !bPosChanged && player.getRot() == *reinterpret_cast< float* >( &copy.data[ 0x10 ] ) )
    return;

  player.setRot( *reinterpret_cast< float* >( &copy.data[ 0x10 ] ) );
  player.setPos( *reinterpret_cast< float* >( &copy.data[ 0x1C ] ),
                 *reinterpret_cast< float* >( &copy.data[ 0x20 ] ),
                 *reinterpret_cast< float* >( &copy.data[ 0x24 ] ) );

  if( ( player.getCurrentAction() != nullptr ) && bPosChanged )
    player.getCurrentAction()->setInterrupted();

  // if no one is in range, don't bother trying to send a position update
  if( !player.hasInRangeActor() )
    return;

  auto moveState = *reinterpret_cast< uint8_t* >( &copy.data[ 0x19 ] );
  auto moveType = *reinterpret_cast< uint8_t* >( &copy.data[ 0x18 ] );

  uint8_t unk1 = 0;
  uint8_t unk2 = 0;
  uint8_t unk3 = moveState;
  uint16_t unk4 = 0;

  // HACK: This part is hackish, we need to find out what all theese things really do.
  //pLog->debug( std::to_string( moveState ) + " -- moveState " );
  //pLog->debug( std::to_string( moveType ) + " -- moveType " );

  if( moveType & MoveType::Running )
  {
    unk1 = 0x7F;
    unk2 = 0x00;
    unk4 = 0x3C;
  }

  if( moveType & MoveType::Strafing )
  {
    unk2 = 0x40;
    unk1 = 0x7F;
    //if( IPC_OP_019A.strafeRight == 1 )
    //   unk1 = 0xbf;
    //else
    //   unk1 = 0x5f;
    unk4 = 0x3C;
  }

  if( moveType & MoveType::Walking )
  {
    unk1 = 0x7F;
    unk2 = 0x02;
    unk3 = 0x00;
    unk4 = 0x18;
  }

  if( moveType & MoveType::Walking && moveType & MoveType::Strafing )
  {
    unk2 = 0x06;
    unk1 = 0xFF;
    unk4 = 0x18;
  }

  if( moveType & MoveType::Jumping )
  {

    unk1 = 0x3F;
    unk2 = 0x32;
    unk4 = 0x5f18;
    if( moveState == MoveState::Land )
      unk2 = 0x02;

  }

  uint64_t currentTime = Util::getTimeMs();

  if( ( currentTime - player.m_lastMoveTime ) < 100 && player.m_lastMoveflag == moveState )
    return;

  player.m_lastMoveTime = currentTime;
  player.m_lastMoveflag = moveState;

  auto movePacket = boost::make_shared< MoveActorPacket >( player, unk1, unk2, moveState, unk4 );
  player.sendToInRangeSet( movePacket );

}

void
Core::Network::GameConnection::reqEquipDisplayFlagsHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  player.setEquipDisplayFlags( inPacket.data[ 0x10 ] );

  player.sendDebug( "EquipDisplayFlag CHANGE: " + std::to_string( player.getEquipDisplayFlags() ) );
}

void Core::Network::GameConnection::zoneLineHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                     Entity::Player& player )
{
  auto pTeriMgr = g_fw.get< TerritoryMgr >();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcZoneLineHandler >( inPacket );
  const auto& zoneLineId = packet.data().zoneLineId;

  player.sendDebug( "Walking ZoneLine " + std::to_string( zoneLineId ) );

  auto pZone = player.getCurrentZone();

  auto pLine = pTeriMgr->getTerritoryPosition( zoneLineId );

  Common::FFXIVARR_POSITION3 targetPos{};
  uint32_t targetZone;
  float rotation = 0.0f;

  if( pLine != nullptr )
  {
    player.sendDebug( "ZoneLine " + std::to_string( zoneLineId ) + " found." );
    targetPos = pLine->getTargetPosition();
    targetZone = pLine->getTargetZoneId();
    rotation = pLine->getTargetRotation();

    auto preparePacket = makeZonePacket< FFXIVIpcPrepareZoning >( player.getId() );
    preparePacket->data().targetZone = targetZone;

    //ActorControlPacket143 controlPacket( pPlayer, ActorControlType::DespawnZoneScreenMsg,
    //                                     0x03, player.getId(), 0x01, targetZone );
    player.queuePacket( preparePacket );
  }
  else
  {
    // No zoneline found, revert to last zone
    player.sendUrgent( "ZoneLine " + std::to_string( zoneLineId ) + " not found." );
    targetPos.x = 0;
    targetPos.y = 0;
    targetPos.z = 0;
    targetZone = pZone->getTerritoryId();
  }

  player.performZoning( targetZone, targetPos, rotation );
}


void Core::Network::GameConnection::discoveryHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                      Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcDiscoveryHandler >( inPacket );
  const auto& positionRef = packet.data().positionRef;

  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto pQR = pDb->query( "SELECT id, map_id, discover_id "
                         "FROM discoveryinfo "
                         "WHERE id = " + std::to_string( positionRef ) + ";" );

  if( !pQR->next() )
  {
    player.sendDebug( "Discovery ref pos ID: " + std::to_string( positionRef ) + " not found. " );
    return;
  }

  auto discoveryPacket = makeZonePacket< FFXIVIpcDiscovery >( player.getId() );
  discoveryPacket->data().map_id = pQR->getUInt( 2 );
  discoveryPacket->data().map_part_id = pQR->getUInt( 3 );

  player.queuePacket( discoveryPacket );
  player.sendDebug( "Discovery ref pos ID: " + std::to_string( positionRef ) );

  player.discover( pQR->getUInt16( 2 ), pQR->getUInt16( 3 ) );

}


void Core::Network::GameConnection::playTimeHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                     Entity::Player& player )
{
  auto playTimePacket = makeZonePacket< FFXIVIpcPlayTime >( player.getId() );
  playTimePacket->data().playTimeInMinutes = player.getPlayTime() / 60;
  player.queuePacket( playTimePacket );
}


void Core::Network::GameConnection::initHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                 Entity::Player& player )
{
  // init handler means this is a login procedure
  player.setIsLogin( true );

  player.sendZonePackets();
}


void Core::Network::GameConnection::blackListHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
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


void Core::Network::GameConnection::pingHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                 Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcPingHandler >( inPacket );

  queueOutPacket( boost::make_shared< Server::PingPacket >( player, packet.data().timestamp ) );

  player.setLastPing( static_cast< uint32_t >( time( nullptr ) ) );
}


void Core::Network::GameConnection::finishLoadingHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  player.getCurrentZone()->onFinishLoading( player );

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

  // notify the zone of a change in position to force an "inRangeActor" update
  player.getCurrentZone()->updateActorPosition( player );
}

void Core::Network::GameConnection::socialListHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                       Entity::Player& player )
{

  uint8_t type = inPacket.data[ 0x1A ];
  uint8_t count = inPacket.data[ 0x1B ];

  if( type == 0x02 )
  { // party list

    auto listPacket = makeZonePacket< FFXIVIpcSocialList >( player.getId() );

    listPacket->data().type = 2;
    listPacket->data().sequence = count;

    int32_t entrysizes = sizeof( listPacket->data().entries );
    memset( listPacket->data().entries, 0, sizeof( listPacket->data().entries ) );

    listPacket->data().entries[ 0 ].bytes[ 2 ] = player.getCurrentZone()->getTerritoryId();
    listPacket->data().entries[ 0 ].bytes[ 3 ] = 0x80;
    listPacket->data().entries[ 0 ].bytes[ 4 ] = 0x02;
    listPacket->data().entries[ 0 ].bytes[ 6 ] = 0x3B;
    listPacket->data().entries[ 0 ].bytes[ 11 ] = 0x10;
    listPacket->data().entries[ 0 ].classJob = static_cast< uint8_t >( player.getClass() );
    listPacket->data().entries[ 0 ].contentId = player.getContentId();
    listPacket->data().entries[ 0 ].level = player.getLevel();
    listPacket->data().entries[ 0 ].zoneId = player.getCurrentZone()->getTerritoryId();
    listPacket->data().entries[ 0 ].zoneId1 = 0x0100;
    // TODO: no idea what this does
    //listPacket.data().entries[0].one = 1;

    memcpy( listPacket->data().entries[ 0 ].name, player.getName().c_str(), strlen( player.getName().c_str() ) );

    // TODO: actually store and read language from somewhere
    listPacket->data().entries[ 0 ].bytes1[ 0 ] = 0x01;//flags (lang)
    // TODO: these flags need to be figured out
    //listPacket.data().entries[0].bytes1[1] = 0x00;//flags
    listPacket->data().entries[ 0 ].onlineStatusMask = player.getOnlineStatusMask();

    queueOutPacket( listPacket );

  }
  else if( type == 0x0b )
  { // friend list
    auto listPacket = makeZonePacket< FFXIVIpcSocialList >( player.getId() );
    listPacket->data().type = 0x0B;
    listPacket->data().sequence = count;
    memset( listPacket->data().entries, 0, sizeof( listPacket->data().entries ) );

  }
  else if( type == 0x0e )
  { // player search result
    // TODO: implement player search
  }

}

void Core::Network::GameConnection::chatHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                 Entity::Player& player )
{
  auto pDebugCom = g_fw.get< DebugCommandHandler >();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcChatHandler >( inPacket );

  if( packet.data().message[ 0 ] == '!' )
  {
    // execute game console command
    pDebugCom->execCommand( const_cast< char* >( packet.data().message ) + 1, player );
    return;
  }

  auto chatType = packet.data().chatType;

  //ToDo, need to implement sending GM chat types.
  auto chatPacket = boost::make_shared< Server::ChatPacket >( player, chatType, packet.data().message );

  switch( chatType )
  {
    case ChatType::Say:
    {
      if( player.isActingAsGm() )
        chatPacket->data().chatType = ChatType::GMSay;

      player.getCurrentZone()->queueOutPacketForRange( player, 50, chatPacket );
      break;
    }
    case ChatType::Yell:
    {
      if( player.isActingAsGm() )
        chatPacket->data().chatType = ChatType::GMYell;

      player.getCurrentZone()->queueOutPacketForRange( player, 6000, chatPacket );
      break;
    }
    case ChatType::Shout:
    {
      if( player.isActingAsGm() )
        chatPacket->data().chatType = ChatType::GMShout;

      player.getCurrentZone()->queueOutPacketForRange( player, 6000, chatPacket );
      break;
    }
    default:
    {
      player.getCurrentZone()->queueOutPacketForRange( player, 50, chatPacket );
      break;
    }
  }

}

// TODO: this handler needs to be improved for timed logout, also the session should be instantly removed
// currently we wait for the session to just time out after logout, this can be a problem is the user tries to
// log right back in.
// Also the packet needs to be converted to an ipc structure
void Core::Network::GameConnection::logoutHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                   Entity::Player& player )
{
  auto logoutPacket = makeZonePacket< FFXIVIpcLogout >( player.getId() );
  logoutPacket->data().flags1 = 0x02;
  logoutPacket->data().flags2 = 0x2000;
  queueOutPacket( logoutPacket );

  player.setMarkedForRemoval();
}


void Core::Network::GameConnection::tellHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                 Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcTellHandler >( inPacket );

  auto pZoneServer = g_fw.get< ServerZone >();

  auto pSession = pZoneServer->getSession( packet.data().targetPCName );

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

  if( pTargetPlayer->hasStateFlag( PlayerStateFlag::BoundByDuty ) )
  {
    // send error for player bound by duty
    // TODO: implement me
    return;
  }

  if( pTargetPlayer->getOnlineStatus() == OnlineStatus::Busy )
  {
    // send error for player being busy
    // TODO: implement me ( i've seen this done with packet type 67 i think )
    return;
  }

  auto tellPacket = makeChatPacket< FFXIVIpcTell >( player.getId() );
  strcpy( tellPacket->data().msg, packet.data().message );
  strcpy( tellPacket->data().receipientName, player.getName().c_str() );
  // TODO: do these have a meaning?
  //tellPacket.data().u1 = 0x92CD7337;
  //tellPacket.data().u2a = 0x2E;
  //tellPacket.data().u2b = 0x40;
  pTargetPlayer->queueChatPacket( tellPacket );

}

void Core::Network::GameConnection::performNoteHandler( const Core::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                        Entity::Player& player )
{
  auto performPacket = makeZonePacket< FFXIVIpcPerformNote >( player.getId() );
  memcpy( &performPacket->data().data[ 0 ], &inPacket.data[ 0x10 ], 32 );
  player.sendToInRangeSet( performPacket );
}
