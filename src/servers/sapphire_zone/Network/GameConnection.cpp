#include <boost/format.hpp>

#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Util/Util.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Network/GamePacketParser.h>

#include "Zone/Zone.h"

#include "Network/PacketWrappers/InitUIPacket.h"

#include "DebugCommand/DebugCommandHandler.h"

#include "Actor/Player.h"

#include "GameConnection.h"
#include "ServerZone.h"
#include "Session.h"
#include "Framework.h"
#include "Forwards.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::Network::GameConnection::GameConnection( Core::Network::HivePtr pHive,
                                               Core::Network::AcceptorPtr pAcceptor )
   : Connection( pHive )
   , m_pAcceptor( pAcceptor )
   , m_conType( ConnectionType::None )
{
   auto setZoneHandler = [=]( uint16_t opcode, std::string handlerName, GameConnection::Handler pHandler )
   {
      m_zoneHandlerMap[opcode] = pHandler;
      m_zoneHandlerStrMap[opcode] = handlerName;
   };

   auto setChatHandler = [=]( uint16_t opcode, std::string handlerName, GameConnection::Handler pHandler )
   {
      m_chatHandlerMap[opcode] = pHandler;
      m_chatHandlerStrMap[opcode] = handlerName;
   };

   setZoneHandler( ClientZoneIpcType::PingHandler,          "PingHandler",              &GameConnection::pingHandler );
   setZoneHandler( ClientZoneIpcType::InitHandler,          "InitHandler",              &GameConnection::initHandler );
   setZoneHandler( ClientZoneIpcType::ChatHandler,          "ChatHandler",              &GameConnection::chatHandler );

   setZoneHandler( ClientZoneIpcType::FinishLoadingHandler, "FinishLoadingHandler",     &GameConnection::finishLoadingHandler );

   setZoneHandler( ClientZoneIpcType::PlayTimeHandler,      "PlayTimeHandler",          &GameConnection::playTimeHandler );
   setZoneHandler( ClientZoneIpcType::LogoutHandler,        "LogoutHandler",            &GameConnection::logoutHandler );

   setZoneHandler( ClientZoneIpcType::SocialListHandler,    "SocialListHandler",        &GameConnection::socialListHandler );
   setZoneHandler( ClientZoneIpcType::SetSearchInfoHandler, "SetSearchInfoHandler",     &GameConnection::setSearchInfoHandler );
   setZoneHandler( ClientZoneIpcType::ReqSearchInfoHandler, "ReqSearchInfoHandler",     &GameConnection::reqSearchInfoHandler );

   setZoneHandler( ClientZoneIpcType::BlackListHandler,     "BlackListHandler",         &GameConnection::blackListHandler );

   setZoneHandler( ClientZoneIpcType::LinkshellListHandler, "LinkshellListHandler",     &GameConnection::linkshellListHandler );

   setZoneHandler( ClientZoneIpcType::FcInfoReqHandler,     "FcInfoReqHandler",         &GameConnection::fcInfoReqHandler );

   setZoneHandler( ClientZoneIpcType::ZoneLineHandler,      "ZoneLineHandler",          &GameConnection::zoneLineHandler );
   setZoneHandler( ClientZoneIpcType::ActionHandler,        "ActionHandler",            &GameConnection::actionHandler );

   setZoneHandler( ClientZoneIpcType::DiscoveryHandler,     "DiscoveryHandler",         &GameConnection::discoveryHandler );

   setZoneHandler( ClientZoneIpcType::SkillHandler,         "SkillHandler",             &GameConnection::skillHandler );

   setZoneHandler( ClientZoneIpcType::GMCommand1,           "GMCommand1",               &GameConnection::gm1Handler );
   setZoneHandler( ClientZoneIpcType::GMCommand2,           "GMCommand2",               &GameConnection::gm2Handler );

   setZoneHandler( ClientZoneIpcType::UpdatePositionHandler,"UpdatePositionHandler",    &GameConnection::updatePositionHandler );

   setZoneHandler( ClientZoneIpcType::InventoryModifyHandler,"InventoryModifyHandler",  &GameConnection::inventoryModifyHandler );

   setZoneHandler( ClientZoneIpcType::TalkEventHandler,     "EventHandlerTalk",         &GameConnection::eventHandlerTalk );
   setZoneHandler( ClientZoneIpcType::EmoteEventHandler,    "EventHandlerEmote",        &GameConnection::eventHandlerEmote );
   setZoneHandler( ClientZoneIpcType::WithinRangeEventHandler, "EventHandlerWithinRange", &GameConnection::eventHandlerWithinRange );
   setZoneHandler( ClientZoneIpcType::OutOfRangeEventHandler, "EventHandlerOutsideRange", &GameConnection::eventHandlerOutsideRange );
   setZoneHandler( ClientZoneIpcType::EnterTeriEventHandler, "EventHandlerEnterTeri",   &GameConnection::eventHandlerEnterTerritory );

   setZoneHandler( ClientZoneIpcType::ReturnEventHandler,      "EventHandlerReturn",    &GameConnection::eventHandlerReturn );
   setZoneHandler( ClientZoneIpcType::TradeReturnEventHandler, "EventHandlerReturn",    &GameConnection::eventHandlerReturn );

   setZoneHandler( ClientZoneIpcType::LinkshellEventHandler, "LinkshellEventHandler",   &GameConnection::eventHandlerLinkshell );
   setZoneHandler( ClientZoneIpcType::LinkshellEventHandler1, "LinkshellEventHandler1", &GameConnection::eventHandlerLinkshell );

   setZoneHandler( ClientZoneIpcType::CFDutyInfoHandler, "CFDutyInfoRequest",           &GameConnection::cfDutyInfoRequest );
   setZoneHandler( ClientZoneIpcType::CFRegisterDuty, "CFRegisterDuty",                 &GameConnection::cfRegisterDuty );
   setZoneHandler( ClientZoneIpcType::CFRegisterRoulette, "CFRegisterRoulette",         &GameConnection::cfRegisterRoulette );
   setZoneHandler( ClientZoneIpcType::CFCommenceHandler, "CFDutyAccepted",              &GameConnection::cfDutyAccepted);

   setZoneHandler( ClientZoneIpcType::ReqEquipDisplayFlagsChange, "ReqEquipDisplayFlagsChange", &GameConnection::reqEquipDisplayFlagsHandler );

   setZoneHandler( ClientZoneIpcType::PerformNoteHandler, "PerformNoteHandler", &GameConnection::performNoteHandler );

   setChatHandler( ClientChatIpcType::TellReq, "TellReq",                               &GameConnection::tellHandler);

}

Core::Network::GameConnection::~GameConnection() = default;


// overwrite the parents onConnect for our game socket needs
void Core::Network::GameConnection::OnAccept( const std::string & host, uint16_t port )
{
   GameConnectionPtr connection( new GameConnection( m_hive, m_pAcceptor ) );
   m_pAcceptor->Accept( connection );
   auto pLog = g_fw.get< Logger >();
   pLog->info( "Connect from " + m_socket.remote_endpoint().address().to_string() );
}


void Core::Network::GameConnection::OnDisconnect()
{
   auto pLog = g_fw.get< Logger >();
   pLog->debug( "GameConnection DISCONNECT" );
   m_pSession = nullptr;
}

void Core::Network::GameConnection::OnRecv( std::vector< uint8_t > & buffer )
{
   // This is assumed packet always start with valid FFXIVARR_PACKET_HEADER for now.
   auto pLog = g_fw.get< Logger >();
   Packets::FFXIVARR_PACKET_HEADER packetHeader{};
   const auto headerResult = Packets::getHeader( buffer, 0, packetHeader );

   if( headerResult == Incomplete )
   {
      pLog->info( "Dropping connection due to incomplete packet header." );
      pLog->info( "FIXME: Packet message bounary is not implemented." );
      Disconnect();
      return;
   }
   else if( headerResult == Malformed )
   {
      pLog->info( "Dropping connection due to malformed packet header." );
      Disconnect();
      return;
   }
   
   // Dissect packet list
   std::vector< Packets::FFXIVARR_PACKET_RAW > packetList;
   const auto packetResult = Packets::getPackets( buffer, sizeof( struct FFXIVARR_PACKET_HEADER ),
                                                  packetHeader, packetList );
   
   if( packetResult == Incomplete )
   {
      pLog->info( "Dropping connection due to incomplete packets." );
      pLog->info( "FIXME: Packet message bounary is not implemented." );
      Disconnect();
      return;
   }
   else if( packetResult == Malformed )
   {
      pLog->info( "Dropping connection due to malformed packets." );
      Disconnect();
      return;
   }
   
   // Handle it
   handlePackets( packetHeader, packetList );
}

void Core::Network::GameConnection::OnError( const boost::system::error_code & error )
{
   auto pLog = g_fw.get< Logger >();
   pLog->debug( "GameConnection ERROR: " + error.message() );
}

void Core::Network::GameConnection::queueInPacket( Core::Network::Packets::GamePacketPtr inPacket )
{
   m_inQueue.push( inPacket );
}

void Core::Network::GameConnection::queueOutPacket( Core::Network::Packets::GamePacketPtr outPacket )
{
   m_outQueue.push( outPacket );
}

void Core::Network::GameConnection::handleZonePacket( const Packets::GamePacket& pPacket )
{
   auto pLog = g_fw.get< Logger >();
   auto it = m_zoneHandlerMap.find( pPacket.getSubType() );

   std::string sessionStr = "[" + std::to_string( m_pSession->getId() ) + "]";

   if( it != m_zoneHandlerMap.end() )
   {
      auto itStr = m_zoneHandlerStrMap.find( pPacket.getSubType() );
      std::string name = itStr != m_zoneHandlerStrMap.end() ? itStr->second : "unknown";
      // dont display packet notification if it is a ping or pos update, don't want the spam
      if( pPacket.getSubType() != PingHandler &&
          pPacket.getSubType() != UpdatePositionHandler )

         pLog->debug( sessionStr + " Handling Zone IPC : " + name + "( " +
                      boost::str( boost::format( "%|04X|" ) %
                                         static_cast< uint32_t >( pPacket.getSubType() & 0xFFFF ) ) + " )" );

      ( this->*( it->second ) )( pPacket, *m_pSession->getPlayer() );
   }
   else
   {
      pLog->debug( sessionStr + " Undefined Zone IPC : Unknown ( " +
                   boost::str( boost::format( "%|04X|" ) %
                                      static_cast< uint32_t >( pPacket.getSubType() & 0xFFFF ) ) + " )" );
      pLog->debug( "\n" + pPacket.toString() );
   }
}


void Core::Network::GameConnection::handleChatPacket( const Packets::GamePacket& pPacket )
{
   auto pLog = g_fw.get< Logger >();
   auto it = m_chatHandlerMap.find( pPacket.getSubType() );

   std::string sessionStr = "[" + std::to_string( m_pSession->getId() ) + "]";

   if( it != m_chatHandlerMap.end() )
   {
      auto itStr = m_chatHandlerStrMap.find( pPacket.getSubType() );
      std::string name = itStr != m_chatHandlerStrMap.end() ? itStr->second : "unknown";
      // dont display packet notification if it is a ping or pos update, don't want the spam

      pLog->debug( sessionStr + " Handling Chat IPC : " + name + "( " +
                   boost::str( boost::format( "%|04X|" ) %
                                      static_cast< uint32_t >( pPacket.getSubType() & 0xFFFF ) ) + " )" );

      ( this->*( it->second ) )( pPacket, *m_pSession->getPlayer() );
   }
   else
   {
      pLog->debug( sessionStr + " Undefined Chat IPC : Unknown ( " +
                  boost::str( boost::format( "%|04X|" ) %
                                     static_cast< uint32_t >( pPacket.getSubType() & 0xFFFF ) ) + " )" );
      pLog->debug( pPacket.toString() );
   }
}

void Core::Network::GameConnection::handlePacket( Core::Network::Packets::GamePacketPtr pPacket )
{
   if( !m_pSession )
      return;

   switch( m_conType )
   {
      case Network::ConnectionType::Zone:
         handleZonePacket( *pPacket );
         break;

      case Network::ConnectionType::Chat:
         handleChatPacket( *pPacket );
         break;
   }

}

void Core::Network::GameConnection::sendPackets( Packets::PacketContainer* pPacket )
{
   //g_log.Log(LoggingSeverity::info, pPacket->toString());
   std::vector< uint8_t > sendBuffer;

   pPacket->fillSendBuffer( sendBuffer );
   Send( sendBuffer );
}

void Core::Network::GameConnection::processInQueue()
{
   // handle the incoming game packets
   while( auto pPacket = m_inQueue.pop() )
   {
      handlePacket( pPacket );
   }
}

void Core::Network::GameConnection::processOutQueue()
{
   auto pLog = g_fw.get< Logger >();
   if( m_outQueue.size() < 1 )
      return;

   int32_t totalSize = 0;

   // create a new packet container
   PacketContainer pRP = PacketContainer();

   // get next packet off the queue
   while( auto pPacket = m_outQueue.pop() )
   {
      if( pPacket->getSize() == 0 )
      {
         pLog->debug( "end of packet set" );
         break;
      }

      pRP.addPacket( *pPacket );
      totalSize += pPacket->getSize();
   }

   if( totalSize > 0 )
      sendPackets( &pRP );

}

void Core::Network::GameConnection::sendSinglePacket( Packets::GamePacket* pPacket )
{
   PacketContainer pRP = PacketContainer();
   pRP.addPacket( *pPacket );
   sendPackets( &pRP );
}

void Core::Network::GameConnection::injectPacket( const std::string& packetpath, Core::Entity::Player& player )
{

   char packet[0x11570];
   memset( packet, 0, 0x11570 );

   // get the packet name / path from the command arguments
   FILE *fp = nullptr;
   fp = fopen( packetpath.c_str(), "rb" );
   if( fp == nullptr )
   {
      player.sendDebug( "Packet " + packetpath + " not found!" );
      return;
   }

   // read the packet into the buffer
   fseek( fp, 0, SEEK_END );
   int32_t size = ftell( fp );
   rewind( fp );
   if ( fread( packet, sizeof( char ), size, fp ) != size )
   {
      player.sendDebug( "Packet " + packetpath + " did not read full size: " + std::to_string( size ) );
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

      queueOutPacket( GamePacketPtr( new GamePacket( packet + k, pSize, false ) ) );
      k += ( pSize );
   }
}

void Core::Network::GameConnection::handlePackets( const Core::Network::Packets::FFXIVARR_PACKET_HEADER& ipcHeader,
                                                   const std::vector< Core::Network::Packets::FFXIVARR_PACKET_RAW >& packetData )
{
   auto pLog = g_fw.get< Logger >();
   auto pServerZone = g_fw.get< ServerZone >();
   // if a session is set, update the last time it recieved a game packet
   if( m_pSession )
      m_pSession->updateLastDataTime();

   for( auto inPacket : packetData )
   {
      switch( inPacket.segHdr.type )
      {
      case 1:
      {
         char* id = ( char* ) &( inPacket.data[4] );
         uint32_t playerId = boost::lexical_cast< uint32_t >( id );
         auto pCon = boost::static_pointer_cast< GameConnection, Connection >( shared_from_this() );

         // try to retrieve the session for this id
         auto session = pServerZone->getSession( playerId );

         if( !session )
         {
            pLog->info( "[" + std::string( id ) + "] Session not registered, creating" );
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
            pLog->error( "[" + std::string(id) + "] Session INVALID, disconnecting" );
            Disconnect();
            return;
         }

         // if not set, set the session for this connection
         if( !m_pSession && session )
            m_pSession = session;

         GamePacket pPe( 0x00, 0x18, 0, 0, 0x07 );
         //pPe.setValAt< uint32_t >( 0x10, 0xE0000005 );
         pPe.setValAt< uint32_t >( 0x10, 0xE0037603 );
         pPe.setValAt< uint32_t >( 0x14, static_cast< uint32_t >( time( nullptr ) ) );
         sendSinglePacket( &pPe );

         // main connection, assinging it to the session
         if( ipcHeader.connectionType == ConnectionType::Zone )
         {
            pPe = GamePacket( 0x00, 0x38, 0, 0, 0x02 );
            pPe.setValAt< uint32_t >( 0x10, playerId );
            sendSinglePacket( &pPe );
            pLog->info( "[" + std::string( id ) + "] Setting session for zone connection" );
            session->setZoneConnection( pCon );
         }
         // chat connection, assinging it to the session
         else if( ipcHeader.connectionType == ConnectionType::Chat )
         {
            pPe = GamePacket( 0x00, 0x38, 0, 0, 0x02 );
            pPe.setValAt< uint32_t >( 0x10, playerId );
            sendSinglePacket( &pPe );

            pLog->info( "[" + std::string( id ) + "] Setting session for chat connection" );
            session->setChatConnection( pCon );
            pPe = GamePacket( 0x02, 0x28, playerId, playerId, 0x03 );
            sendSinglePacket( &pPe );
         }

         break;

      }
      case 3: // game packet
      {
         auto pPacket = new GamePacket( inPacket );
         queueInPacket( Packets::GamePacketPtr( pPacket ) );
         break;
      }
      case 7: // keep alive
      {
         uint32_t id = *( uint32_t* ) &inPacket.data[0];
         uint32_t timeStamp = *( uint32_t* ) &inPacket.data[4];

         GamePacket pPe( 0x00, 0x18, 0, 0, 0x08 );
         pPe.setValAt< uint32_t >( 0x10, id );
         pPe.setValAt< uint32_t >( 0x14, timeStamp );
         sendSinglePacket( &pPe );

         break;
      }
      case 8:
      {
         break;
      }
      }

   }
}
