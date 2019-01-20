#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Util/Util.h>
#include <Logging/Logger.h>
#include <utility>

#include <Network/Acceptor.h>
#include <Network/PacketContainer.h>
#include <Network/GamePacketParser.h>

#include "Territory/Zone.h"

#include "Network/PacketWrappers/InitUIPacket.h"

#include "Manager/DebugCommandMgr.h"

#include "GameConnection.h"
#include "ServerMgr.h"
#include "Session.h"
#include "Framework.h"
#include "Forwards.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

Sapphire::Network::GameConnection::GameConnection( Sapphire::Network::HivePtr pHive,
                                                   Sapphire::Network::AcceptorPtr pAcceptor,
                                                   FrameworkPtr pFw ) :
  Connection( pHive, pFw ),
  m_pAcceptor( pAcceptor ),
  m_conType( ConnectionType::None )
{
  auto setZoneHandler = [ = ]( uint16_t opcode, std::string handlerName, GameConnection::Handler pHandler )
  {
    m_zoneHandlerMap[ opcode ] = pHandler;
    m_zoneHandlerStrMap[ opcode ] = handlerName;
  };

  auto setChatHandler = [ = ]( uint16_t opcode, std::string handlerName, GameConnection::Handler pHandler )
  {
    m_chatHandlerMap[ opcode ] = pHandler;
    m_chatHandlerStrMap[ opcode ] = handlerName;
  };

  setZoneHandler( ClientZoneIpcType::PingHandler, "PingHandler", &GameConnection::pingHandler );
  setZoneHandler( ClientZoneIpcType::InitHandler, "InitHandler", &GameConnection::initHandler );
  setZoneHandler( ClientZoneIpcType::ChatHandler, "ChatHandler", &GameConnection::chatHandler );

  setZoneHandler( ClientZoneIpcType::FinishLoadingHandler, "FinishLoadingHandler",
                  &GameConnection::finishLoadingHandler );

  setZoneHandler( ClientZoneIpcType::PlayTimeHandler, "PlayTimeHandler", &GameConnection::playTimeHandler );
  setZoneHandler( ClientZoneIpcType::LogoutHandler, "LogoutHandler", &GameConnection::logoutHandler );

  setZoneHandler( ClientZoneIpcType::SocialListHandler, "SocialListHandler", &GameConnection::socialListHandler );
  setZoneHandler( ClientZoneIpcType::SetSearchInfoHandler, "SetSearchInfoHandler",
                  &GameConnection::setSearchInfoHandler );
  setZoneHandler( ClientZoneIpcType::ReqSearchInfoHandler, "ReqSearchInfoHandler",
                  &GameConnection::reqSearchInfoHandler );
  setZoneHandler( ClientZoneIpcType::ReqExamineSearchCommentHandler, "ReqExamineSearchCommentHandler",
                  &GameConnection::reqExamineSearchCommentHandler );
  setZoneHandler( ClientZoneIpcType::BlackListHandler, "BlackListHandler", &GameConnection::blackListHandler );

  setZoneHandler( ClientZoneIpcType::LinkshellListHandler, "LinkshellListHandler",
                  &GameConnection::linkshellListHandler );

  setZoneHandler( ClientZoneIpcType::FcInfoReqHandler, "FcInfoReqHandler", &GameConnection::fcInfoReqHandler );
  setZoneHandler( ClientZoneIpcType::ReqExamineFcInfo, "ReqExamineFcInfo", &GameConnection::reqExamineFcInfo );
  setZoneHandler( ClientZoneIpcType::ZoneLineHandler, "ZoneLineHandler", &GameConnection::zoneLineHandler );
  setZoneHandler( ClientZoneIpcType::ClientTrigger, "ClientTrigger", &GameConnection::clientTriggerHandler );

  setZoneHandler( ClientZoneIpcType::DiscoveryHandler, "DiscoveryHandler", &GameConnection::discoveryHandler );

  setZoneHandler( ClientZoneIpcType::SkillHandler, "ActionHandler", &GameConnection::actionHandler );

  setZoneHandler( ClientZoneIpcType::GMCommand1, "GMCommand1", &GameConnection::gm1Handler );
  setZoneHandler( ClientZoneIpcType::GMCommand2, "GMCommand2", &GameConnection::gm2Handler );

  setZoneHandler( ClientZoneIpcType::UpdatePositionHandler, "UpdatePositionHandler",
                  &GameConnection::updatePositionHandler );

  setZoneHandler( ClientZoneIpcType::InventoryModifyHandler, "InventoryModifyHandler",
                  &GameConnection::inventoryModifyHandler );

  setZoneHandler( ClientZoneIpcType::BuildPresetHandler, "BuildPresetHandler", &GameConnection::buildPresetHandler );
  setZoneHandler( ClientZoneIpcType::LandRenameHandler, "LandRenameHandler", &GameConnection::landRenameHandler );
  setZoneHandler( ClientZoneIpcType::HousingUpdateHouseGreeting, "HousingUpdateHouseGreeting",
                  &GameConnection::housingUpdateGreetingHandler );
  setZoneHandler( ClientZoneIpcType::ReqPlaceHousingItem, "ReqPlaceHousingItem", &GameConnection::reqPlaceHousingItem );
  setZoneHandler( ClientZoneIpcType::HousingUpdateObjectPosition, "HousingUpdateObjectPosition",
                  &GameConnection::reqMoveHousingItem );

  setZoneHandler( ClientZoneIpcType::TalkEventHandler, "EventHandlerTalk", &GameConnection::eventHandlerTalk );
  setZoneHandler( ClientZoneIpcType::EmoteEventHandler, "EventHandlerEmote", &GameConnection::eventHandlerEmote );
  setZoneHandler( ClientZoneIpcType::WithinRangeEventHandler, "EventHandlerWithinRange",
                  &GameConnection::eventHandlerWithinRange );
  setZoneHandler( ClientZoneIpcType::OutOfRangeEventHandler, "EventHandlerOutsideRange",
                  &GameConnection::eventHandlerOutsideRange );
  setZoneHandler( ClientZoneIpcType::EnterTeriEventHandler, "EventHandlerEnterTeri",
                  &GameConnection::eventHandlerEnterTerritory );

  setZoneHandler( ClientZoneIpcType::ReturnEventHandler, "EventHandlerReturn", &GameConnection::eventHandlerReturn );
  setZoneHandler( ClientZoneIpcType::TradeReturnEventHandler, "EventHandlerReturn",
                  &GameConnection::eventHandlerReturn );

  setZoneHandler( ClientZoneIpcType::ShopEventHandler, "ShopEventHandler",
                  &GameConnection::eventHandlerShop );

  setZoneHandler( ClientZoneIpcType::LinkshellEventHandler, "LinkshellEventHandler",
                  &GameConnection::eventHandlerLinkshell );

  setZoneHandler( ClientZoneIpcType::LinkshellEventHandler1, "LinkshellEventHandler1",
                  &GameConnection::eventHandlerLinkshell );

  setZoneHandler( ClientZoneIpcType::CFDutyInfoHandler, "CFDutyInfoRequest", &GameConnection::cfDutyInfoRequest );
  setZoneHandler( ClientZoneIpcType::CFRegisterDuty, "CFRegisterDuty", &GameConnection::cfRegisterDuty );
  setZoneHandler( ClientZoneIpcType::CFRegisterRoulette, "CFRegisterRoulette", &GameConnection::cfRegisterRoulette );
  setZoneHandler( ClientZoneIpcType::CFCommenceHandler, "CFDutyAccepted", &GameConnection::cfDutyAccepted );

  setZoneHandler( ClientZoneIpcType::ReqEquipDisplayFlagsChange, "ReqEquipDisplayFlagsChange",
                  &GameConnection::reqEquipDisplayFlagsHandler );

  setZoneHandler( ClientZoneIpcType::PerformNoteHandler, "PerformNoteHandler", &GameConnection::performNoteHandler );

  setZoneHandler( ClientZoneIpcType::MarketBoardSearch, "MarketBoardSearch", &GameConnection::marketBoardSearch );
  setZoneHandler( ClientZoneIpcType::MarketBoardRequestItemListingInfo, "MarketBoardRequestItemListingInfo",
                  &GameConnection::marketBoardRequestItemInfo );
  setZoneHandler( ClientZoneIpcType::MarketBoardRequestItemListings, "MarketBoardRequestItemListings",
                  &GameConnection::marketBoardRequestItemListings );

  setChatHandler( ClientChatIpcType::TellReq, "TellReq", &GameConnection::tellHandler );

}

Sapphire::Network::GameConnection::~GameConnection() = default;


// overwrite the parents onConnect for our game socket needs
void Sapphire::Network::GameConnection::OnAccept( const std::string& host, uint16_t port )
{
  GameConnectionPtr connection( new GameConnection( m_hive, m_pAcceptor, m_pFw ) );
  m_pAcceptor->Accept( connection );
  Logger::info( "Connect from {0}", m_socket.remote_endpoint().address().to_string() );
}


void Sapphire::Network::GameConnection::OnDisconnect()
{
  Logger::debug( "GameConnection DISCONNECT" );
  m_pSession = nullptr;
}

void Sapphire::Network::GameConnection::OnRecv( std::vector< uint8_t >& buffer )
{
  // This is assumed packet always start with valid FFXIVARR_PACKET_HEADER for now.
  Packets::FFXIVARR_PACKET_HEADER packetHeader{};
  const auto headerResult = Packets::getHeader( buffer, 0, packetHeader );

  if( headerResult == Incomplete )
  {
    Logger::info( "Dropping connection due to incomplete packet header." );
    Logger::info( "FIXME: Packet message bounary is not implemented." );
    Disconnect();
    return;
  }
  else if( headerResult == Malformed )
  {
    Logger::info( "Dropping connection due to malformed packet header." );
    Disconnect();
    return;
  }

  // Dissect packet list
  std::vector< Packets::FFXIVARR_PACKET_RAW > packetList;
  const auto packetResult = Packets::getPackets( buffer, sizeof( struct FFXIVARR_PACKET_HEADER ),
                                                 packetHeader, packetList );

  if( packetResult == Incomplete )
  {
    Logger::info( "Dropping connection due to incomplete packets." );
    Logger::info( "FIXME: Packet message bounary is not implemented." );
    Disconnect();
    return;
  }
  else if( packetResult == Malformed )
  {
    Logger::info( "Dropping connection due to malformed packets." );
    Disconnect();
    return;
  }

  // Handle it
  handlePackets( packetHeader, packetList );
}

void Sapphire::Network::GameConnection::OnError( const asio::error_code& error )
{
  Logger::debug( "GameConnection ERROR: {0}", error.message() );
}

void Sapphire::Network::GameConnection::queueInPacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW inPacket )
{
  m_inQueue.push( inPacket );
}

void Sapphire::Network::GameConnection::queueOutPacket( Sapphire::Network::Packets::FFXIVPacketBasePtr outPacket )
{
  m_outQueue.push( outPacket );
}

void Sapphire::Network::GameConnection::handleZonePacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& pPacket )
{
  uint16_t opcode = *reinterpret_cast< uint16_t* >( &pPacket.data[ 0x02 ] );
  auto it = m_zoneHandlerMap.find( opcode );

  if( it != m_zoneHandlerMap.end() )
  {
    auto itStr = m_zoneHandlerStrMap.find( opcode );
    std::string name = itStr != m_zoneHandlerStrMap.end() ? itStr->second : "unknown";
    // dont display packet notification if it is a ping or pos update, don't want the spam
    if( opcode != PingHandler && opcode != UpdatePositionHandler )
      Logger::debug( "[{0}] Handling Zone IPC : {1} ( {2:04X} )", m_pSession->getId(), name, opcode );

    ( this->*( it->second ) )( m_pFw, pPacket, *m_pSession->getPlayer() );
  }
  else
  {
    Logger::debug( "[{0}] Undefined Zone IPC : Unknown ( {1:04X} )", m_pSession->getId(), opcode );
    Logger::debug( "Dump:\n{0}", Util::binaryToHexDump( const_cast< uint8_t* >( &pPacket.data[ 0 ] ),
                                                       pPacket.segHdr.size ) );
  }
}

void Sapphire::Network::GameConnection::handleChatPacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& pPacket )
{
  uint16_t opcode = *reinterpret_cast< uint16_t* >( &pPacket.data[ 0x02 ] );
  auto it = m_chatHandlerMap.find( opcode );

  if( it != m_chatHandlerMap.end() )
  {
    auto itStr = m_chatHandlerStrMap.find( opcode );
    std::string name = itStr != m_chatHandlerStrMap.end() ? itStr->second : "unknown";
    // dont display packet notification if it is a ping or pos update, don't want the spam

    Logger::debug( "[{0}] Handling Chat IPC : {1} ( {2:04X} )", m_pSession->getId(), name, opcode );

    ( this->*( it->second ) )( m_pFw, pPacket, *m_pSession->getPlayer() );
  }
  else
  {
    Logger::debug( "[{0}] Undefined Chat IPC : Unknown ( {1:04X} )", m_pSession->getId(), opcode );
  }
}

void Sapphire::Network::GameConnection::handlePacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& pPacket )
{
  if( !m_pSession )
    return;

  switch( m_conType )
  {
    case Network::ConnectionType::Zone:
      handleZonePacket( pPacket );
      break;

    case Network::ConnectionType::Chat:
      handleChatPacket( pPacket );
      break;

    default:
      break;
  }

}

void Sapphire::Network::GameConnection::sendPackets( Packets::PacketContainer* pPacket )
{
  std::vector< uint8_t > sendBuffer;

  pPacket->fillSendBuffer( sendBuffer );
  Send( sendBuffer );
}

void Sapphire::Network::GameConnection::processInQueue()
{
  // handle the incoming game packets
  while( m_inQueue.size() )
  {
    auto pPacket = m_inQueue.pop();
    handlePacket( pPacket );
  }
}

void Sapphire::Network::GameConnection::processOutQueue()
{
  if( m_outQueue.size() < 1 )
    return;

  int32_t totalSize = 0;

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

void Sapphire::Network::GameConnection::sendSinglePacket( Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket )
{
  PacketContainer pRP = PacketContainer();
  pRP.addPacket( pPacket );
  sendPackets( &pRP );
}

void Sapphire::Network::GameConnection::injectPacket( const std::string& packetpath, Sapphire::Entity::Player& player )
{

  char packet[ 0x11570 ];
  memset( packet, 0, 0x11570 );

  // get the packet name / path from the command arguments
  FILE* fp = nullptr;
  fp = fopen( packetpath.c_str(), "rb" );
  if( fp == nullptr )
  {
    player.sendDebug( "Packet {0} not found!", packetpath );
    return;
  }

  // read the packet into the buffer
  fseek( fp, 0, SEEK_END );
  auto size = static_cast< size_t >( ftell( fp ) );
  rewind( fp );
  if( fread( packet, sizeof( char ), size, fp ) != size )
  {
    player.sendDebug( "Packet {0} did not read full size: {1}", packetpath, size );
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

    queueOutPacket( FFXIVPacketBasePtr( new FFXIVRawPacket( packet + k, pSize ) ) );

    k += ( pSize );
  }
}

void Sapphire::Network::GameConnection::handlePackets( const Sapphire::Network::Packets::FFXIVARR_PACKET_HEADER& ipcHeader,
                                                       const std::vector< Sapphire::Network::Packets::FFXIVARR_PACKET_RAW >& packetData )
{
  auto pServerZone = m_pFw->get< World::ServerMgr >();

  // if a session is set, update the last time it recieved a game packet
  if( m_pSession )
    m_pSession->updateLastDataTime();

  for( auto inPacket : packetData )
  {
    switch( inPacket.segHdr.type )
    {
      case SEGMENTTYPE_SESSIONINIT:
      {
        char* id = ( char* ) &( inPacket.data[ 4 ] );
        uint32_t playerId = std::stoul( id );
        auto pCon = std::static_pointer_cast< GameConnection, Connection >( shared_from_this() );

        // try to retrieve the session for this id
        auto session = pServerZone->getSession( playerId );

        if( !session )
        {
          Logger::info( "[{0}] Session not registered, creating", id );
          // return;
          if( !pServerZone->createSession( playerId ) )
          {
            Disconnect();
            return;
          }
          session = pServerZone->getSession( playerId );
        }
          //TODO: Catch more things in lobby and send real errors
        else if( !session->isValid() || ( session->getPlayer() && session->getPlayer()->getLastPing() != 0 ) )
        {
          Logger::error( "[{0}] Session INVALID, disconnecting", id );
          Disconnect();
          return;
        }

        // if not set, set the session for this connection
        if( !m_pSession && session )
          m_pSession = session;

        auto pe = std::make_shared< FFXIVRawPacket >( 0x07, 0x18, 0, 0 );
        *( unsigned int* ) ( &pe->data()[ 0 ] ) = 0xE0037603;
        *( unsigned int* ) ( &pe->data()[ 4 ] ) = Sapphire::Util::getTimeSeconds();
        sendSinglePacket( pe );

        // main connection, assinging it to the session
        if( ipcHeader.connectionType == ConnectionType::Zone )
        {
          auto pe1 = std::make_shared< FFXIVRawPacket >( 0x02, 0x38, 0, 0 );
          *( unsigned int* ) ( &pe1->data()[ 0 ] ) = playerId;
          sendSinglePacket( pe1 );
          Logger::info( "[{0}] Setting session for zone connection", id );
          session->setZoneConnection( pCon );
        }
          // chat connection, assinging it to the session
        else if( ipcHeader.connectionType == ConnectionType::Chat )
        {
          auto pe2 = std::make_shared< FFXIVRawPacket >( 0x02, 0x38, 0, 0 );
          *( unsigned int* ) ( &pe2->data()[ 0 ] ) = playerId;
          sendSinglePacket( pe2 );

          auto pe3 = std::make_shared< FFXIVRawPacket >( 0x03, 0x28, playerId, playerId );
          *( unsigned short* ) ( &pe3->data()[ 2 ] ) = 0x02;
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
        uint32_t id = *( uint32_t* ) &inPacket.data[ 0 ];
        uint32_t timeStamp = *( uint32_t* ) &inPacket.data[ 4 ];

        auto pe4 = std::make_shared< FFXIVRawPacket >( 0x08, 0x18, 0, 0 );
        *( unsigned int* ) ( &pe4->data()[ 0 ] ) = id;
        *( unsigned int* ) ( &pe4->data()[ 4 ] ) = timeStamp;
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
