#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Network/CommonNetwork.h>
#include <src/servers/Server_Common/Database/Database.h>
#include <src/servers/Server_Common/Util/Util.h>
#include <src/servers/Server_Common/Util/UtilNetwork.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <src/servers/Server_Common/Network/PacketContainer.h>
#include <boost/format.hpp>

#include "GameConnection.h"

#include "src/servers/Server_Zone/ServerZone.h"
#include "src/servers/Server_Zone/Session.h"
#include "src/servers/Server_Zone/Zone/Zone.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/InitUIPacket.h"
#include "src/servers/Server_Zone/DebugCommand/DebugCommandHandler.h"
#include "src/servers/Server_Zone/Actor/Player.h"
#include "src/servers/Server_Zone/Forwards.h"

extern Core::DebugCommandHandler g_gameCommandMgr;
extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::Network::GameConnection::GameConnection( Core::Network::HivePtr pHive,
                                               Core::Network::AcceptorPtr pAcceptor )
   : Connection( pHive )
   , m_pAcceptor( pAcceptor )
   , m_conType( ConnectionType::None )
{
   auto setHandler = [=]( uint16_t opcode, std::string handlerName, GameConnection::Handler pHandler )
   {
      m_packetHandlerMap[opcode] = pHandler;
      m_packetHandlerStrMap[opcode] = handlerName;
   };

   setHandler( ClientIpcType::PingHandler,          "PingHandler",              &GameConnection::pingHandler ); 
   setHandler( ClientIpcType::InitHandler,          "InitHandler",              &GameConnection::initHandler );
   setHandler( ClientIpcType::ChatHandler,          "ChatHandler",              &GameConnection::chatHandler ); 

   setHandler( ClientIpcType::FinishLoadingHandler, "FinishLoadingHandler",     &GameConnection::finishLoadingHandler ); 

   setHandler( ClientIpcType::PlayTimeHandler,      "PlayTimeHandler",          &GameConnection::playTimeHandler );
   setHandler( ClientIpcType::LogoutHandler,        "LogoutHandler",            &GameConnection::logoutHandler );

   setHandler( ClientIpcType::SocialListHandler,    "SocialListHandler",        &GameConnection::socialListHandler );
   setHandler( ClientIpcType::SetSearchInfoHandler, "SetSearchInfoHandler",     &GameConnection::setSearchInfoHandler );
   setHandler( ClientIpcType::ReqSearchInfoHandler, "ReqSearchInfoHandler",     &GameConnection::reqSearchInfoHandler );

   setHandler( ClientIpcType::BlackListHandler,     "BlackListHandler",         &GameConnection::blackListHandler );

   setHandler( ClientIpcType::LinkshellListHandler, "LinkshellListHandler",     &GameConnection::linkshellListHandler );

   setHandler( ClientIpcType::FcInfoReqHandler,     "FcInfoReqHandler",         &GameConnection::fcInfoReqHandler );

   setHandler( ClientIpcType::ZoneLineHandler,      "ZoneLineHandler",          &GameConnection::zoneLineHandler );
   setHandler( ClientIpcType::ActionHandler,        "ActionHandler",            &GameConnection::actionHandler );

   setHandler( ClientIpcType::DiscoveryHandler,     "DiscoveryHandler",         &GameConnection::discoveryHandler );

   setHandler( ClientIpcType::SkillHandler,         "SkillHandler",             &GameConnection::skillHandler );

   setHandler( ClientIpcType::GMCommand1,           "GMCommand1",               &GameConnection::gm1Handler );
   setHandler( ClientIpcType::GMCommand2,           "GMCommand2",               &GameConnection::gm2Handler );

   setHandler( ClientIpcType::UpdatePositionHandler,"UpdatePositionHandler",    &GameConnection::updatePositionHandler );

   setHandler( ClientIpcType::InventoryModifyHandler,"InventoryModifyHandler",  &GameConnection::inventoryModifyHandler );

   setHandler( ClientIpcType::TalkEventHandler,     "EventHandler",             &GameConnection::eventHandler );
   setHandler( ClientIpcType::EmoteEventHandler,    "EventHandler",             &GameConnection::eventHandler );
   setHandler( ClientIpcType::WithinRangeEventHandler, "EventHandler",          &GameConnection::eventHandler );
   setHandler( ClientIpcType::OutOfRangeEventHandler, "EventHandler",           &GameConnection::eventHandler );
   setHandler( ClientIpcType::EnterTeriEventHandler, "EventHandler",            &GameConnection::eventHandler );

   setHandler( ClientIpcType::ReturnEventHandler,      "EventHandlerReturn",    &GameConnection::eventHandler );
   setHandler( ClientIpcType::TradeReturnEventHandler, "EventHandlerReturn",    &GameConnection::eventHandler );

   setHandler( ClientIpcType::CFDutyInfoHandler, "CFDutyInfoRequest",           &GameConnection::cfDutyInfoRequest );
   setHandler( ClientIpcType::CFRegisterDuty, "CFRegisterDuty",                 &GameConnection::cfRegisterDuty );
   setHandler( ClientIpcType::CFRegisterRoulette, "CFRegisterRoulette",         &GameConnection::cfRegisterRoulette );
   setHandler( ClientIpcType::CFCommenceHandler, "CFDutyAccepted",              &GameConnection::cfDutyAccepted);

}

Core::Network::GameConnection::~GameConnection()
{

}


// overwrite the parents onConnect for our game socket needs
void Core::Network::GameConnection::OnAccept( const std::string & host, uint16_t port )
{
   GameConnectionPtr connection( new GameConnection( m_hive, m_pAcceptor ) );
   m_pAcceptor->Accept( connection );

   g_log.info( "Connect from " + m_socket.remote_endpoint().address().to_string() );
}


void Core::Network::GameConnection::OnDisconnect()
{
   g_log.debug( "DISCONNECT" );
   m_pSession = nullptr;
}

void Core::Network::GameConnection::OnRecv( std::vector< uint8_t > & buffer )
{
   Packets::FFXIVARR_PACKET_HEADER ipcHeader;
   std::vector< Packets::FFXIVARR_PACKET_RAW > packetList;

   Network::Util::bufferToPacketList( buffer, ipcHeader, packetList );

   handlePackets( ipcHeader, packetList );

}

void Core::Network::GameConnection::OnError( const boost::system::error_code & error )
{
   g_log.debug( "ERROR" );
}

void Core::Network::GameConnection::queueInPacket( Core::Network::Packets::GamePacketPtr inPacket )
{
   m_inQueue.push( inPacket );
}

void Core::Network::GameConnection::queueOutPacket( Core::Network::Packets::GamePacketPtr outPacket )
{
   m_outQueue.push( outPacket );
}

void Core::Network::GameConnection::handleGamePacket( Core::Network::Packets::GamePacketPtr pPacket )
{
   if( !m_pSession )
      return;

   auto it = m_packetHandlerMap.find( pPacket->getSubType() );

   if( it != m_packetHandlerMap.end() )
   {
      auto name = m_packetHandlerStrMap[pPacket->getSubType()];
      // dont display packet notification if it is a ping or pos update, don't want the spam
      if( pPacket->getSubType() != ClientIpcType::PingHandler 
          && pPacket->getSubType() != ClientIpcType::UpdatePositionHandler )
         g_log.debug( "[" + std::to_string( m_pSession->getId() ) + "] Handling packet : " + name + "( " +
                      boost::str( boost::format( "%|04X|" ) % static_cast< uint32_t >( pPacket->getSubType() & 0xFFFF ) )  + " )" );

      ( this->*( it->second ) )( *pPacket, m_pSession->getPlayer() );
   }
   else
   {
      g_log.debug( "[" + std::to_string( m_pSession->getId() ) + "] Undefined packet : Unknown ( " +
                   boost::str( boost::format( "%|04X|" ) % static_cast< uint32_t >( pPacket->getSubType() & 0xFFFF ) ) + " )" );
      g_log.debug( pPacket->toString() );
   }
      

}

void Core::Network::GameConnection::sendPackets( Packets::PacketContainer * pPacket )
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
      handleGamePacket( pPacket );
   }
}

void Core::Network::GameConnection::processOutQueue()
{

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
         g_log.debug( "end of packet set" );
         break;
      }

      pRP.addPacket( *pPacket );
      totalSize += pPacket->getSize();
   }

   if( totalSize > 0 )
      sendPackets( &pRP );

}

void Core::Network::GameConnection::sendSinglePacket( Packets::GamePacket * pPacket )
{
   PacketContainer pRP = PacketContainer();
   pRP.addPacket( *pPacket );
   sendPackets( &pRP );
}

void Core::Network::GameConnection::injectPacket( const std::string& packetpath, Core::Entity::PlayerPtr pPlayer )
{

   char packet[0x11570];
   memset( packet, 0, 0x11570 );

   // get the packet name / path from the command arguments
   FILE *fp = nullptr;
   fp = fopen( packetpath.c_str(), "rb" );
   if( fp == nullptr )
   {
      g_log.error( "Packet " + packetpath + " not found!" );
      return;
   }

   // read the packet into the buffer
   fseek( fp, 0, SEEK_END );
   int32_t size = ftell( fp );
   rewind( fp );
   fread( packet, sizeof( char ), size, fp );
   fclose( fp );

   // cycle through the packet entries and queue each one
   for( int32_t k = 0x18; k < size;)
   {
      uint32_t tmpId = pPlayer->getId();
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
                                                   const std::vector<Core::Network::Packets::FFXIVARR_PACKET_RAW>& packetData )
{

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
         auto session = g_serverZone.getSession( playerId );

         if( !session )
         {
            g_log.info( "[" + std::string( id ) + "] Session not registered, creating" );
            // return;
            g_serverZone.createSession( playerId );
            session = g_serverZone.getSession( playerId );
         }

         // if not set, set the session for this connection
         if( !m_pSession && session )
            m_pSession = session;

         // main connection, assinging it to the session
         if( ipcHeader.connectionType == 1 )
         {
            g_log.info( "[" + std::string( id ) + "] Setting session for zone connection" );
            session->setZoneConnection( pCon );
         }
         // chat connection, assinging it to the session
         else if( ipcHeader.connectionType == 2 )
         {
            g_log.info( "[" + std::string( id ) + "] Setting session for chat connection" );
           // session->setClientChatConnection( pCon );
         }

         GamePacket pPe( 0x00, 0x18, 0, 0, 0x07 );
         pPe.setValAt< uint32_t >( 0x10, 0xE0000005 );
         pPe.setValAt< uint32_t >( 0x14, static_cast< uint32_t >( time( nullptr ) ) );
         sendSinglePacket( &pPe );

         pPe = GamePacket( 0x00, 0x38, 0, 0, 0x02 );
         pPe.setValAt< uint32_t >( 0x10, playerId );
         sendSinglePacket( &pPe );

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


      //// try to retrieve the session for this id
      //auto session = g_serverZone.getSession( inPacket.segHdr.source_actor );
      //auto pCon = boost::static_pointer_cast< GameConnection, Connection >( shared_from_this() );

      //// check if this is a zoning notification
      //if( *reinterpret_cast< uint16_t* >( &inPacket.data[2] ) == 0x9999 )
      //{

      //   // if we already have a session in this connection, reload the player
      //   if( session )
      //      g_serverZone.updateSession( inPacket.segHdr.source_actor );
      //   else
      //   {
      //      // if not, create a new session
      //      g_serverZone.createSession( inPacket.segHdr.source_actor );
      //      session = g_serverZone.getSession( inPacket.segHdr.source_actor );
      //   }

      //   // set the zoneingType for the player so the correct animation can be played
      //   auto pPlayer = session->getPlayer();
      //   ZoneingType zoneType = static_cast< ZoneingType >( *reinterpret_cast< uint16_t* >( &inPacket.data[18] ) );
      //   switch( zoneType )
      //   {
      //   case ZoneingType::Teleport:
      //      pPlayer->setTeleporting( true );
      //      break;
      //   case ZoneingType::Return:
      //      pPlayer->setReturning( true );
      //      break;
      //   default:
      //      break;
      //   }
      //   // place this connection in the session
      //   session->setZoneConnection( pCon );
      //   // actually perform the zoning 
      //   session->getPlayer()->setZone( *reinterpret_cast< uint16_t* >( &inPacket.data[16] ) );
      //}
      //else
      //{
      //   if( !session )
      //   {
      //      g_serverZone.createSession( inPacket.segHdr.source_actor );
      //      session = g_serverZone.getSession( inPacket.segHdr.source_actor );
      //      session->setZoneConnection( pCon );
      //   }

      //   queueInPacket( GamePacketPtr( new GamePacket( inPacket ) ) );
      //}

      //// if not set, set the session for this connection
      //if( !m_pSession && session )
      //   m_pSession = session;
   }
}
