#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Util/Util.h>
#include <Logging/Logger.h>
#include <utility>

#include <Network/Acceptor.h>
#include <Network/PacketContainer.h>
#include <Network/GamePacketParser.h>
#include <Service.h>

#include "Network/PacketWrappers/PlayerSetupPacket.h"

#include "GameConnection.h"
#include "WorldServer.h"
#include "Session.h"
#include "Forwards.h"

#include "Manager/PlayerMgr.h"

using namespace Sapphire::Common;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::Packets::WorldPackets::Client;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

GameConnection::GameConnection( Sapphire::Network::HivePtr pHive, Sapphire::Network::AcceptorPtr pAcceptor ) :
  Connection( std::move( pHive ) ),
  m_pAcceptor( std::move( pAcceptor ) ),
  m_conType( ConnectionType::None )
{
  auto setZoneHandler = [ = ]( uint16_t opcode, std::string handlerName, GameConnection::Handler pHandler )
  {
    m_zoneHandlerMap[ opcode ] = pHandler;
    m_zoneHandlerStrMap[ opcode ] = std::move( handlerName );
  };

  auto setChatHandler = [ = ]( uint16_t opcode, std::string handlerName, GameConnection::Handler pHandler )
  {
    m_chatHandlerMap[ opcode ] = pHandler;
    m_chatHandlerStrMap[ opcode ] = std::move( handlerName );
  };

  setZoneHandler( Sync, "syncHandler", &GameConnection::syncHandler );
  setZoneHandler( ClientZoneIpcType::Login, "loginHandler", &GameConnection::loginHandler );
  setZoneHandler( ChatHandler, "ChatHandler", &GameConnection::chatHandler );
  setZoneHandler( JoinChatChannel, "JoinChatChannel", &GameConnection::joinChatChannelHandler );

  setZoneHandler( SetLanguage, "SetLanguage", &GameConnection::setLanguageHandler );

  setZoneHandler( StartLogoutCountdown, "StartLogoutCountdown", &GameConnection::logoutHandler );

  setZoneHandler( SetProfile, "SetProfile", &GameConnection::setProfileHandler );
  setZoneHandler( GetProfile, "GetProfile", &GameConnection::getProfileHandler );
  setZoneHandler( GetSearchComment, "GetSearchComment", &GameConnection::getSearchCommentHandler );
  setZoneHandler( PcSearch, "PcSearch", &GameConnection::pcSearchHandler );

  setZoneHandler( GetCommonlist, "GetCommonlist", &GameConnection::getCommonlistHandler );
  setZoneHandler( GetCommonlistDetail, "GetCommonlistDetail", &GameConnection::getCommonlistDetailHandler );

  setZoneHandler( GetLinkshellList, "GetLinkshellList", &GameConnection::linkshellListHandler );
  setZoneHandler( LinkshellJoin, "LinkshellJoin", &GameConnection::linkshellJoinHandler );
  setZoneHandler( LinkshellKick, "LinkshellKick", &GameConnection::linkshellKickHandler );
  setZoneHandler( LinkshellLeave, "LinkshellLeave", &GameConnection::linkshellLeaveHandler );
  setZoneHandler( LinkshellChangeMaster, "LinkshellChangeMaster", &GameConnection::linkshellChangeMasterHandler );
  setZoneHandler( LinkshellJoinOfficial, "LinkshellJoinOfficial", &GameConnection::linkshellJoinOfficialHandler );
  setZoneHandler( LinkshellAddLeader, "LinkshellAddLeader", &GameConnection::linkshellAddLeaderHandler );
  setZoneHandler( LinkshellRemoveLeader, "LinkshellRemoveLeader", &GameConnection::linkshellRemoveLeaderHandler );
  setZoneHandler( LinkshellDeclineLeader, "LinkshellDeclineLeader", &GameConnection::linkshellDeclineLeaderHandler );

  setZoneHandler( ReqExamineFcInfo, "ReqExamineFcInfo", &GameConnection::reqExamineFcInfo );
  setZoneHandler( ZoneJump, "ZoneJump", &GameConnection::zoneJumpHandler );
  setZoneHandler( Command, "Command", &GameConnection::commandHandler );

  setZoneHandler( NewDiscovery, "NewDiscovery", &GameConnection::newDiscoveryHandler );

  setZoneHandler( ActionRequest, "ActionRequest", &GameConnection::actionRequest );
  setZoneHandler( SelectGroundActionRequest, "SelectGroundActionRequest", &GameConnection::selectGroundActionRequest );

  setZoneHandler( GMCommand, "GMCommand", &GameConnection::gmCommandHandler );
  setZoneHandler( GMCommandName, "GMCommandName", &GameConnection::gmCommandNameHandler );

  setZoneHandler( Move, "Move", &GameConnection::moveHandler );

  setZoneHandler( ClientItemOperation, "ItemOperation", &GameConnection::itemOperation );

  setZoneHandler( BuildPresetHandler, "BuildPresetHandler", &GameConnection::buildPresetHandler );
  setZoneHandler( ClientZoneIpcType::HousingHouseName, "HousingHouseName", &GameConnection::landRenameHandler );
  setZoneHandler( ClientZoneIpcType::HousingGreeting, "HousingUpdateHouseGreeting", &GameConnection::housingUpdateGreetingHandler );
  setZoneHandler( HousingPlaceYardItem, "HousingPlaceYardItem", &GameConnection::reqPlaceHousingItem );
  setZoneHandler( HousingExteriorChange, "HousingExteriorChange", &GameConnection::reqMoveHousingItem );

  setZoneHandler( StartTalkEvent, "StartTalkEvent", &GameConnection::eventHandlerTalk );
  setZoneHandler( StartEmoteEvent, "StartEmoteEvent", &GameConnection::eventHandlerEmote );
  setZoneHandler( StartWithinRangeEvent, "StartWithinRangeEvent", &GameConnection::eventHandlerWithinRange );
  setZoneHandler( StartOutsideRangeEvent, "StartOutsideRangeEvent", &GameConnection::eventHandlerOutsideRange );
  setZoneHandler( StartEnterTerritoryEvent, "StartEnterTerritoryEvent", &GameConnection::eventHandlerEnterTerritory );

  setZoneHandler( ReturnEventSceneHeader, "ReturnEventSceneHeader", &GameConnection::returnEventSceneHeader );
  setZoneHandler( ReturnEventScene2, "ReturnEventScene2", &GameConnection::returnEventScene2 );
  setZoneHandler( ReturnEventScene4, "ReturnEventScene4", &GameConnection::returnEventScene4 );
  setZoneHandler( ReturnEventScene8, "ReturnEventScene8", &GameConnection::returnEventScene8 );
  setZoneHandler( ReturnEventScene16, "ReturnEventScene16", &GameConnection::returnEventScene16 );
  setZoneHandler( ReturnEventScene32, "ReturnEventScene32", &GameConnection::returnEventScene32 );
  setZoneHandler( ReturnEventScene64, "ReturnEventScene64", &GameConnection::returnEventScene64 );
  setZoneHandler( ReturnEventScene128, "ReturnEventScene128", &GameConnection::returnEventScene128 );
  setZoneHandler( ReturnEventScene255, "ReturnEventScene255", &GameConnection::returnEventScene255 );

  setZoneHandler( YieldEventSceneHeader, "YieldEventSceneHeader", &GameConnection::yieldEventSceneHeader );
  setZoneHandler( YieldEventScene2, "YieldEventScene2", &GameConnection::yieldEventScene2 );
  setZoneHandler( YieldEventScene4, "YieldEventScene4", &GameConnection::yieldEventScene4 );
  setZoneHandler( YieldEventScene8, "YieldEventScene8", &GameConnection::yieldEventScene8 );
  setZoneHandler( YieldEventScene16, "YieldEventScene16", &GameConnection::yieldEventScene16 );
  setZoneHandler( YieldEventScene32, "YieldEventScene32", &GameConnection::yieldEventScene32 );
  setZoneHandler( YieldEventScene64, "YieldEventScene64", &GameConnection::yieldEventScene64 );
  setZoneHandler( YieldEventScene128, "YieldEventScene128", &GameConnection::yieldEventScene128 );
  setZoneHandler( YieldEventScene255, "YieldEventScene255", &GameConnection::yieldEventScene255 );

  setZoneHandler( StartUIEvent, "StartUIEvent", &GameConnection::startUiEvent );

  setZoneHandler( YieldEventSceneString8, "YieldEventSceneString8", &GameConnection::yieldEventString );
  setZoneHandler( YieldEventSceneString16, "YieldEventSceneString16", &GameConnection::yieldEventString );
  setZoneHandler( YieldEventSceneString32, "YieldEventSceneString32", &GameConnection::yieldEventString );

  setZoneHandler( YieldEventSceneIntAndString, "YieldEventSceneIntAndString", &GameConnection::yieldEventSceneIntAndString );

  setZoneHandler( RequestPenalties, "RequestPenalties", &GameConnection::cfRequestPenalties );
  setZoneHandler( RequestBonus, "RequestBonus", &GameConnection::requestBonus );
  setZoneHandler( FindContent, "FindContent", &GameConnection::findContent );
  setZoneHandler( Find5Contents, "Find5Contents", &GameConnection::find5Contents );
  setZoneHandler( FindContentAsRandom, "FindContentAsRandom", &GameConnection::findContentAsRandom );
  setZoneHandler( CFCommenceHandler, "CFDutyAccepted", &GameConnection::cfDutyAccepted );
  setZoneHandler( CancelFindContent, "CancelFindContent", &GameConnection::cancelFindContent );
  setZoneHandler( AcceptContent, "AcceptContent", &GameConnection::acceptContent );

  setZoneHandler( ClientZoneIpcType::Config, "Config", &GameConnection::configHandler );

  setZoneHandler( CatalogSearch, "CatalogSearch", &GameConnection::catalogSearch );

  setZoneHandler( GearSetEquip, "GearSetEquip", &GameConnection::gearSetEquip );

  setZoneHandler( MarketBoardRequestItemListingInfo, "MarketBoardRequestItemListingInfo", &GameConnection::marketBoardRequestItemInfo );
  setZoneHandler( MarketBoardRequestItemListings, "MarketBoardRequestItemListings", &GameConnection::marketBoardRequestItemListings );

  setChatHandler( ClientChatIpcType::ChatTo, "ChatTo", &GameConnection::tellHandler );
  setChatHandler( ClientChatIpcType::ChatToChannel, "ChatToChannel", &GameConnection::chatToChannelHandler );

  setZoneHandler( GetFcStatus, "GetFcStatus", &GameConnection::getFcStatus );
  setZoneHandler( GetFcProfile, "GetFcProfile", &GameConnection::getFcProfile );

  setZoneHandler( GetRequestItemList, "GetRequestItemList", &GameConnection::getRequestItemListHandler );

  setZoneHandler( Invite, "Invite", &GameConnection::inviteHandler );
  setZoneHandler( InviteReply, "InviteReply", &GameConnection::inviteReplyHandler );

  setZoneHandler( PcPartyLeave, "PcPartyLeave", &GameConnection::pcPartyLeaveHandler );
  setZoneHandler( PcPartyDisband, "PcPartyDisband", &GameConnection::pcPartyDisbandHandler );
  setZoneHandler( PcPartyKick, "PcPartyKick", &GameConnection::pcPartyKickHandler );
  setZoneHandler( PcPartyChangeLeader, "PcPartyChangeLeader", &GameConnection::pcPartyChangeLeaderHandler );

  setZoneHandler( FriendlistRemove, "FriendlistRemove", &GameConnection::friendlistRemoveHandler );
  setZoneHandler( SetFriendlistGroup, "SetFriendlistGroup", &GameConnection::setFriendlistGroupHandler );

  setZoneHandler( GetBlacklist, "GetBlacklist", &GameConnection::getBlacklistHandler );
  setZoneHandler( BlacklistAdd, "BlacklistAdd", &GameConnection::blacklistAddHandler );
  setZoneHandler( BlacklistRemove, "BlacklistRemove", &GameConnection::blacklistRemoveHandler );

  setZoneHandler( GetFcInviteList, "GetFcInviteList", &GameConnection::getFcInviteListHandler );
}

GameConnection::~GameConnection() = default;


// overwrite the parents onConnect for our game socket needs
void GameConnection::onAccept( const std::string& host, uint16_t port )
{
  auto connection = std::make_shared< GameConnection >( m_hive, m_pAcceptor );
  m_pAcceptor->accept( connection );
  Logger::info( "Connect from {0}:{1}", m_socket.remote_endpoint().address().to_string(), m_socket.remote_endpoint().port() );
}


void GameConnection::onDisconnect()
{
  if( m_pSession )
    Logger::debug( "[{0}] Disconnect {1}:{2}\"", m_pSession->getId() );
  else
    Logger::debug( "Disconnect of lost session." );
  m_pSession.reset();
}

void GameConnection::onRecv( std::vector< uint8_t >& buffer )
{
  m_packets.insert( std::end( m_packets ), std::begin( buffer ), std::end( buffer ) );
  // This is assumed packet always start with valid FFXIVARR_PACKET_HEADER for now.
  Packets::FFXIVARR_PACKET_HEADER packetHeader{};
  const auto headerResult = Packets::getHeader( m_packets, 0, packetHeader );

  if( headerResult == Incomplete )
    return;

  if( headerResult == Malformed )
  {
    Logger::info( "Dropping connection due to malformed packet header." );
    disconnect();
    return;
  }

  // Dissect packet list
  std::vector< Packets::FFXIVARR_PACKET_RAW > packetList;
  const auto packetResult = Packets::getPackets( m_packets, sizeof( struct FFXIVARR_PACKET_HEADER ), packetHeader, packetList );

  if( packetResult == Incomplete )
    return;

  if( packetResult == Malformed )
  {
    Logger::info( "Dropping connection due to malformed packets." );
    disconnect();
    return;
  }

  // Handle it
  handlePackets( packetHeader, packetList );
  m_packets.clear();
}

void GameConnection::onError( const asio::error_code& error )
{
  Logger::debug( "GameConnection ERROR: {0}", error.message() );
}

void GameConnection::queueInPacket( Packets::FFXIVARR_PACKET_RAW inPacket )
{
  m_inQueue.push( std::move( inPacket ) );
}

void GameConnection::queueOutPacket( Packets::FFXIVPacketBasePtr outPacket )
{
  m_outQueue.push( std::move( outPacket ) );
}

void GameConnection::queueOutPacket( std::vector< Packets::FFXIVPacketBasePtr > vector )
{
  for( auto& packet : vector )
  {
    m_outQueue.push( packet );
  }
}

void GameConnection::handleZonePacket( Packets::FFXIVARR_PACKET_RAW& pPacket )
{
  uint16_t opcode = Util::getOpCode( pPacket );
  auto it = m_zoneHandlerMap.find( opcode );

  if( it != m_zoneHandlerMap.end() )
  {
    auto itStr = m_zoneHandlerStrMap.find( opcode );
    std::string name = itStr != m_zoneHandlerStrMap.end() ? itStr->second : "unknown";
    // dont display packet notification if it is a ping or pos update, don't want the spam
    if( opcode != Sync && opcode != Client::Move )
      Logger::debug( "[{0}] Zone IPC : {1} ( {2:04X} )", m_pSession->getId(), name, opcode );

    ( this->*( it->second ) )( pPacket, *m_pSession->getPlayer() );
  }
  else
  {
    auto packetName = zonePacketToString( opcode );
    auto player = m_pSession->getPlayer();
    PlayerMgr::sendUrgent( *player, "Unimplemented zone IPC: {} ({:04X}) len: {}", packetName, opcode, pPacket.data.size() );

    Logger::debug( "[{}] Unimplemented World IPC : {} ({:04X})", m_pSession->getId(), packetName, opcode );

    Logger::debug(
      "Dump:\n{0}",
      Util::binaryToHexDump( const_cast< uint8_t* >( &pPacket.data[ 0 ] ),
      static_cast< uint16_t >( pPacket.segHdr.size - 0x10 ) )
    );
  }
}

void GameConnection::handleChatPacket( Packets::FFXIVARR_PACKET_RAW& pPacket )
{
  uint16_t opcode = Util::getOpCode( pPacket );
  auto it = m_chatHandlerMap.find( opcode );

  if( it != m_chatHandlerMap.end() )
  {
    auto itStr = m_chatHandlerStrMap.find( opcode );
    std::string name = itStr != m_chatHandlerStrMap.end() ? itStr->second : "unknown";
    // dont display packet notification if it is a ping or pos update, don't want the spam

    Logger::debug( "[{0}] Handling Chat IPC : {1} ( {2:04X} )", m_pSession->getId(), name, opcode );

    ( this->*( it->second ) )( pPacket, *m_pSession->getPlayer() );
  }
  else
  {
    Logger::debug( "[{0}] Undefined Chat IPC : Unknown ( {1:04X} )", m_pSession->getId(), opcode );

    Logger::debug(
      "Dump:\n{0}",
      Util::binaryToHexDump( const_cast< uint8_t* >( &pPacket.data[ 0 ] ),
        static_cast< uint16_t >( pPacket.segHdr.size ) )
    );
  }
}

void GameConnection::handlePacket( Packets::FFXIVARR_PACKET_RAW& pPacket )
{
  if( !m_pSession )
    return;

  switch( m_conType )
  {
    case ConnectionType::Zone:
      handleZonePacket( pPacket );
      break;

    case ConnectionType::Chat:
      handleChatPacket( pPacket );
      break;

    default:
      break;
  }

}

void GameConnection::sendPackets( Packets::PacketContainer* pPacket )
{
  std::vector< uint8_t > sendBuffer;

  pPacket->fillSendBuffer( sendBuffer );
  send( sendBuffer );
}

void GameConnection::processInQueue()
{
  // handle the incoming game packets
  while( m_inQueue.size() )
  {
    auto pPacket = m_inQueue.pop();
    handlePacket( pPacket );
  }
}

void GameConnection::processOutQueue()
{
  if( m_outQueue.size() < 1 )
    return;

  size_t totalSize = 0;

  // create a new packet container
  PacketContainer pRP = PacketContainer( m_pSession->getId() );

  // get next packet off the queue
  while( auto pPacket = m_outQueue.pop() )
  {
    if( pPacket->getSize() == 0 )
    {
      Logger::debug( "end of packet set" );
      break;
    }

    pRP.addPacket( pPacket );
    totalSize += pPacket->getSize();

    // todo: figure out a good max set size and make it configurable
    if( totalSize > 10000 )
      break;
  }

  if( totalSize > 0 )
    sendPackets( &pRP );

}

void GameConnection::sendSinglePacket( Packets::FFXIVPacketBasePtr pPacket )
{
  PacketContainer pRP = PacketContainer();
  pRP.addPacket( std::move( pPacket ) );
  sendPackets( &pRP );
}

void GameConnection::injectPacket( const std::string& packetpath, Entity::Player& player )
{

  char packet[ 0x11570 ];
  memset( packet, 0, 0x11570 );

  // get the packet name / path from the command arguments
  FILE* fp = nullptr;
  fp = fopen( packetpath.c_str(), "rb" );
  if( fp == nullptr )
  {
    PlayerMgr::sendDebug( player, "Packet {0} not found!", packetpath );
    return;
  }

  // read the packet into the buffer
  fseek( fp, 0, SEEK_END );
  auto size = static_cast< size_t >( ftell( fp ) );
  rewind( fp );
  if( fread( packet, sizeof( char ), size, fp ) != size )
  {
    PlayerMgr::sendDebug( player, "Packet {0} did not read full size: {1}", packetpath, size );
    return;
  }
  fclose( fp );

  // cycle through the packet entries and queue each one
  for( int32_t k = 0x18; k < size; )
  {
    uint32_t tmpId = player.getId();
    // replace ids in the entryheader if needed
    if( !memcmp( packet + k + 0x04, packet + k + 0x08, 4 ) )
    {
      memcpy( packet + k + 0x04, &tmpId, 4 );
      memcpy( packet + k + 0x08, &tmpId, 4 );
    }
    else
      memcpy( packet + k + 0x08, &tmpId, 4 );


    uint16_t pSize = *reinterpret_cast< uint16_t* >( packet + k );
    // queue packet to the session
    if( pSize == 0 )
      return;

    queueOutPacket( std::make_shared< FFXIVRawPacket >( packet + k, pSize ) );

    k += ( pSize );
  }
}

void GameConnection::handlePackets( const Packets::FFXIVARR_PACKET_HEADER& ipcHeader, const std::vector< Packets::FFXIVARR_PACKET_RAW >& packetData )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  // if a session is set, update the last time it recieved a game packet
  if( m_pSession )
    m_pSession->updateLastDataTime();

  for( auto inPacket : packetData )
  {
    switch( inPacket.segHdr.type )
    {
      case SEGMENTTYPE_SESSIONINIT:
      {
        char* id = reinterpret_cast< char* >( &( inPacket.data[ 4 ] ) );
        uint32_t entityId = std::stoul( id );
        auto pCon = std::static_pointer_cast< GameConnection, Connection >( shared_from_this() );

        // try to retrieve the session for this id
        auto session = server.getSession( entityId );

        if( !session )
        {
          Logger::info( "[{0}] Session not registered, creating", id );
          // return;
          if( !server.createSession( entityId ) )
          {
            disconnect();
            return;
          }
          session = server.getSession( entityId );
        }
          //TODO: Catch more things in lobby and send real errors
        else if( !session->isValid() || ( session->getPlayer() && session->getLastPing() != 0 ) )
        {
          Logger::error( "[{0}] Session INVALID, disconnecting", id );
          disconnect();
          return;
        }

        // if not set, set the session for this connection
        if( !m_pSession && session )
          m_pSession = session;

        auto pe = std::make_shared< FFXIVRawPacket >( 0x07, 0x18, 0, 0 );
        *reinterpret_cast< unsigned int* >( &pe->data()[ 0 ] ) = 0xE00392b0;
        *reinterpret_cast< unsigned int* >( &pe->data()[ 4 ] ) = Common::Util::getTimeSeconds();
        sendSinglePacket( pe );

        // main connection, assinging it to the session
        if( ipcHeader.connectionType == ConnectionType::Zone )
        {
          auto pe1 = std::make_shared< FFXIVRawPacket >( 0x02, 0x38, 0, 0 );
          *reinterpret_cast< unsigned int* >( &pe1->data()[ 0 ] ) = entityId;
          *reinterpret_cast< unsigned int* >( &pe1->data()[ 0x08 ] ) = 0x90000b60;
          *reinterpret_cast< unsigned int* >( &pe1->data()[ 0x0C ] ) = 0x00007f8B;
          *reinterpret_cast< unsigned int* >( &pe1->data()[ 0x10 ] ) = 0x7b201bf0;
          *reinterpret_cast< unsigned int* >( &pe1->data()[ 0x14 ] ) = 0x00007f8b;
          *reinterpret_cast< unsigned int* >( &pe1->data()[ 0x20 ] ) = 0x00005e4c;
          //*reinterpret_cast< unsigned int* >( &pe1->data()[ 0x24 ] ) = Common::Util::getTimeSeconds();
          //*reinterpret_cast< unsigned int* >( &pe1->data()[ 0x0C ] ) = Common::Util::getTimeSeconds();
          //*reinterpret_cast< unsigned int* >( &pe1->data()[ 0x1C ] ) = Common::Util::getTimeSeconds();
          //*reinterpret_cast< unsigned int* >( &pe1->data()[ 0x18 ] ) = Common::Util::getTimeSeconds();
          sendSinglePacket( pe1 );
          Logger::info( "[{0}] Setting session for world connection", id );
          session->setZoneConnection( pCon );
        }
          // chat connection, assinging it to the session
        else if( ipcHeader.connectionType == ConnectionType::Chat )
        {
          auto pe2 = std::make_shared< FFXIVRawPacket >( 0x02, 0x38, 0, 0 );
          *reinterpret_cast< unsigned int* >( &pe2->data()[ 0 ] ) = entityId;
          sendSinglePacket( pe2 );

          auto pe3 = std::make_shared< FFXIVRawPacket >( 0x03, 0x28, entityId, entityId );
          *reinterpret_cast< unsigned short* >( &pe3->data()[ 2 ] ) = 0x02;
          sendSinglePacket( pe3 );

          Logger::info( "[{0}] Setting session for chat connection", id );
          session->setChatConnection( pCon );
        }

        break;

      }
      case SEGMENTTYPE_IPC: // game packet
      {
        queueInPacket( inPacket );
        break;
      }
      case SEGMENTTYPE_KEEPALIVE: // keep alive
      {
        uint32_t id = *reinterpret_cast< uint32_t* >( &inPacket.data[ 0 ] );
        uint32_t timeStamp = *reinterpret_cast< uint32_t* >( &inPacket.data[ 4 ] );

        auto pe4 = std::make_shared< FFXIVRawPacket >( 0x08, 0x18, 0, 0 );
        *reinterpret_cast< unsigned int* >( &pe4->data()[ 0 ] ) = id;
        *reinterpret_cast< unsigned int* >( &pe4->data()[ 4 ] ) = Util::getTimeSeconds();
        sendSinglePacket( pe4 );

        break;
      }
      case 8:
      {
        break;
      }
    }

  }
}

const char* GameConnection::zonePacketToString( uint32_t opcode )
{
  switch( opcode )
  {
    default:
      return "unknown client IPC";

    case Sync:
      return "Sync";

    case ClientZoneIpcType::Login:
      return "Login";

    case ChatHandler:
      return "ChatHandler";

    case SetLanguage:
      return "SetLanguage";

    case Invite:
      return "Invite";

    case InviteReply:
      return "InviteReply";

    case GetCommonlist:
      return "GetCommonlist";

    case GetCommonlistDetail:
      return "GetCommonlistDetail";

    case SetProfile:
      return "SetProfile";

    case GetProfile:
      return "GetProfile";

    case GetSearchComment:
      return "GetSearchComment";

    case PartyRecruitAdd:
      return "PartyRecruitAdd";

    case JoinChatChannel:
      return "JoinChatChannel";

    case LeaveChatChannel:
      return "LeaveChatChannel";

    case PartyRecruitRemove:
      return "PartyRecruitRemove";

    case PartyRecruitSearch:
      return "PartyRecruitSearch";

    case GetRecruitSearchList:
      return "GetRecruitSearchList";

    case GetRecruitDetail:
      return "GetRecruitDetail";

    case InviteReplyRecruitParty:
      return "InviteReplyRecruitParty";

    case PartyRecruitEdit:
      return "PartyRecruitEdit";

    case GetPurposeLevel:
      return "GetPurposeLevel";

    case AddRequestItem:
      return "AddRequestItem";

    case RemoveRequestItem:
      return "RemoveRequestItem";

    case PcPartyLeave:
      return "PcPartyLeave";

    case PcPartyDisband:
      return "PcPartyDisband";

    case PcPartyKick:
      return "PcPartyKick";

    case PcPartyChangeLeader:
      return "PcPartyChangeLeader";

    case GetRequestItem:
      return "GetRequestItem";

    case BlacklistAdd:
      return "BlacklistAdd";

    case BlacklistRemove:
      return "BlacklistRemove";

    case GetBlacklist:
      return "GetBlacklist";

    case GetRequestItemList:
      return "GetRequestItemList";

    case SendReadyCheck:
      return "SendReadyCheck";

    case FriendlistRemove:
      return "FriendlistRemove";

    case ReplyReadyCheck:
      return "ReplyReadyCheck";

    case GetPartyRecruitCount:
      return "GetPartyRecruitCount";

    case FcAddJoinRequest:
      return "FcAddJoinRequest";

    case FcRemoveJoinRequest:
      return "FcRemoveJoinRequest";

    case PcSearch:
      return "PcSearch";

    case GetFcJoinRequestComment:
      return "GetFcJoinRequestComment";

    case InviteCancel:
      return "InviteCancel";

    case LinkshellJoin:
      return "LinkshellJoin";

    case LinkshellJoinOfficial:
      return "LinkshellJoinOfficial";

    case LinkshellLeave:
      return "LinkshellLeave";

    case LinkshellChangeMaster:
      return "LinkshellChangeMaster";

    case LinkshellKick:
      return "LinkshellKick";

    case GetLinkshellList:
      return "GetLinkshellList";

    case LinkshellAddLeader:
      return "LinkshellAddLeader";

    case LinkshellRemoveLeader:
      return "LinkshellRemoveLeader";

    case LinkshellDeclineLeader:
      return "LinkshellDeclineLeader";

    case LetterSendMessage:
      return "LetterSendMessage";

    case LetterRemoveMessage:
      return "LetterRemoveMessage";

    case GetLetterMessage:
      return "GetLetterMessage";

    case GetLetterMessageDetail:
      return "GetLetterMessageDetail";

    case LetterMoveAppendItem:
      return "LetterMoveAppendItem";

    case CheckGiftMail:
      return "CheckGiftMail";

    case ItemSearch:
      return "ItemSearch";

    case GetItemSearchList:
      return "GetItemSearchList";

    case GetRetainerList:
      return "GetRetainerList";

    case BuyMarketRetainer:
      return "BuyMarketRetainer";

    case GetRetainerSalesHistory:
      return "GetRetainerSalesHistory";

    case CatalogSearch:
      return "CatalogSearch";

    case FreeCompanyLeave:
      return "FreeCompanyLeave";

    case FreeCompanyKick:
      return "FreeCompanyKick";

    case FcSetHierarchyName:
      return "FcSetHierarchyName";

    case FcSetAuthorityList:
      return "FcSetAuthorityList";

    case FcMoveHierarchyMember:
      return "FcMoveHierarchyMember";

    case FcAddHierarchy:
      return "FcAddHierarchy";

    case FcRemoveHierarchy:
      return "FcRemoveHierarchy";

    case FcSortHierarchy:
      return "FcSortHierarchy";

    case GetFcStatus:
      return "GetFcStatus";

    case FcForceDisband:
      return "FcForceDisband";

    case GetFcInviteList:
      return "GetFcInviteList";

    case GetFcProfile:
      return "GetFcProfile";

    case GetFcHeader:
      return "GetFcHeader";

    case SetCompanyBoard:
      return "SetCompanyBoard";

    case GetCompanyBoard:
      return "GetCompanyBoard";

    case GetFcHierarchy:
      return "GetFcHierarchy";

    case FcChangeMaster:
      return "FcChangeMaster";

    case GetFcActivityList:
      return "GetFcActivityList";

    case SetCompanyMotto:
      return "SetCompanyMotto";

    case GetCompanyMotto:
      return "GetCompanyMotto";

    case GetFcParams:
      return "GetFcParams";

    case SetCrestID:
      return "SetCrestID";

    case BuyFcAction:
      return "BuyFcAction";

    case FcActionCommand:
      return "FcActionCommand";

    case GetFcAction:
      return "GetFcAction";

    case SetFcMemo:
      return "SetFcMemo";

    case GetFcMemo:
      return "GetFcMemo";

    case InfoGMCommand:
      return "InfoGMCommand";

    case DebugInfoCommand:
      return "DebugInfoCommand";

    case RequestSyncTag:
      return "RequestSyncTag";

    case ZoneJump:
      return "ZoneJump";

    case Command:
      return "Command";

    case PhysicalBonus:
      return "PhysicalBonus";

    case NewDiscovery:
      return "NewDiscovery";

    case TargetPosCommand:
      return "TargetPosCommand";

    case ActionRequest:
      return "ActionRequest";

    case GMCommand:
      return "GMCommand";

    case GMCommandName:
      return "GMCommandName";

    case SelectGroundActionRequest:
      return "SelectGroundActionRequest";

    case Move:
      return "Move";

    case GMCommandBuddyName:
      return "GMCommandBuddyName";

    case GMCommandNameBuddyName:
      return "GMCommandNameBuddyName";

    case RequestStorageItems:
      return "RequestStorageItems";

    case ExchangeAttachedInactiveMateria:
      return "ExchangeAttachedInactiveMateria";

    case RetainerCustomize:
      return "RetainerCustomize";

    case ClientItemOperation:
      return "ClientItemOperation";

    case GearSetEquip:
      return "GearSetEquip";

    case HousingExteriorChange:
      return "HousingExteriorChange";

    case HousingPlaceYardItem:
      return "HousingPlaceYardItem";

    case HousingInteriorChange:
      return "HousingInteriorChange";

    case ClientZoneIpcType::TradeCommand:
      return "TradeCommand";

    case TreasureCheckCommand:
      return "TreasureCheckCommand";

    case SelectLootAction:
      return "SelectLootAction";

    case OpenTreasureWithKey:
      return "OpenTreasureWithKey";

    case StartTalkEvent:
      return "StartTalkEvent";

    case StartEmoteEvent:
      return "StartEmoteEvent";

    case StartWithinRangeEvent:
      return "StartWithinRangeEvent";

    case StartOutsideRangeEvent:
      return "StartOutsideRangeEvent";

    case StartEnterTerritoryEvent:
      return "StartEnterTerritoryEvent";

    case StartActionResultEvent:
      return "StartActionResultEvent";

    case StartUIEvent:
      return "StartUIEvent";

    case StartSayEvent:
      return "StartSayEvent";

    case ReturnEventSceneHeader:
      return "ReturnEventSceneHeader";

    case ReturnEventScene2:
      return "ReturnEventScene2";

    case ReturnEventScene4:
      return "ReturnEventScene4";

    case ReturnEventScene8:
      return "ReturnEventScene8";

    case ReturnEventScene16:
      return "ReturnEventScene16";

    case ReturnEventScene32:
      return "ReturnEventScene32";

    case ReturnEventScene64:
      return "ReturnEventScene64";

    case ReturnEventScene128:
      return "ReturnEventScene128";

    case ReturnEventScene255:
      return "ReturnEventScene255";

    case YieldEventSceneHeader:
      return "YieldEventSceneHeader";

    case YieldEventScene2:
      return "YieldEventScene2";

    case YieldEventScene4:
      return "YieldEventScene4";

    case YieldEventScene8:
      return "YieldEventScene8";

    case YieldEventScene16:
      return "YieldEventScene16";

    case YieldEventScene32:
      return "YieldEventScene32";

    case YieldEventScene64:
      return "YieldEventScene64";

    case YieldEventScene128:
      return "YieldEventScene128";

    case YieldEventScene255:
      return "YieldEventScene255";

    case YieldEventSceneStringHeader:
      return "YieldEventSceneStringHeader";

    case YieldEventSceneString8:
      return "YieldEventSceneString8";

    case YieldEventSceneString16:
      return "YieldEventSceneString16";

    case YieldEventSceneString32:
      return "YieldEventSceneString32";

    case YieldEventSceneIntAndString:
      return "YieldEventSceneIntAndString";

    case ClientZoneIpcType::DebugNull:
      return "DebugNull";

    case DebugCommand:
      return "DebugCommand";

    case DebugBnpcControl:
      return "DebugBnpcControl";

    case DebugMessage:
      return "DebugMessage";

    case FindContent:
      return "FindContent";

    case DebugFinishContent:
      return "DebugFinishContent";

    case AcceptContent:
      return "AcceptContent";

    case CancelFindContent:
      return "CancelFindContent";

    case Find5Contents:
      return "Find5Contents";

    case ClientZoneIpcType::FindContentAsRandom:
      return "FindContentAsRandom";

    case ChocoboTaxiPathEnd:
      return "ChocoboTaxiPathEnd";

    case ChocoboTaxiSetStep:
      return "ChocoboTaxiSetStep";

    case ChocoboTaxiUnmount:
      return "ChocoboTaxiUnmount";

    case ClientZoneIpcType::Config:
      return "Config";

    case StartLogoutCountdown:
      return "StartLogoutCountdown";

    case ClientZoneIpcType::CancelLogoutCountdown:
      return "CancelLogoutCountdown";

    case FateDebugCommand:
      return "FateDebugCommand";

    case ContentAction:
      return "ContentAction";

    case RequestPenalties:
      return "RequestPenalties";

    case Logout:
      return "Logout";

    case ClientZoneIpcType::HousingHouseName:
      return "HousingHouseName";

    case ClientZoneIpcType::HousingGreeting:
      return "HousingGreeting";

    case HousingChangeLayout:
      return "HousingChangeLayout";

    case VoteKickStart:
      return "VoteKickStart";

    case MVPRequest:
      return "MVPRequest";

    case HousingChangeLayoutMulti:
      return "HousingChangeLayoutMulti";

    case ConfusionApproachEnd:
      return "ConfusionApproachEnd";

    case ConfusionTurnEnd:
      return "ConfusionTurnEnd";

    case MovePvP:
      return "MovePvP";

    case CFCommenceHandler:
      return "CFCommenceHandler";

    case MarketBoardRequestItemListingInfo:
      return "MarketBoardRequestItemListingInfo";

    case MarketBoardRequestItemListings:
      return "MarketBoardRequestItemListings";

    case ReqExamineFcInfo:
      return "ReqExamineFcInfo";

  }
}