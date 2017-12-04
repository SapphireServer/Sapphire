#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Network/CommonNetwork.h>
#include <src/servers/Server_Common/Network/GamePacketNew.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Network/PacketContainer.h>
#include <src/servers/Server_Common/Network/PacketDef/Chat/ServerChatDef.h>

#include <boost/format.hpp>


#include "src/servers/Server_Zone/Network/GameConnection.h"

#include "src/servers/Server_Zone/Session.h"
#include "src/servers/Server_Zone/Zone/Zone.h"
#include "src/servers/Server_Zone/Zone/ZonePosition.h"
#include "src/servers/Server_Zone/ServerZone.h"
#include "src/servers/Server_Zone/Zone/ZoneMgr.h"

#include "src/servers/Server_Zone/Network/PacketWrappers/InitUIPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/PingPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/MoveActorPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ChatPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ServerNoticePacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket144.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/EventStartPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/EventFinishPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "src/servers/Server_Zone/DebugCommand/DebugCommandHandler.h"
#include "src/servers/Server_Zone/Actor/Player.h"
#include "src/servers/Server_Zone/Inventory/Inventory.h"
#include "src/servers/Server_Zone/Forwards.h"
#include "src/servers/Server_Zone/Event/EventHelper.h"
#include "src/servers/Server_Zone/Action/Action.h"
#include "src/servers/Server_Zone/Action/ActionTeleport.h"

#include <Server_Common/Database/DatabaseDef.h>

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::DebugCommandHandler g_gameCommandMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Network::GameConnection::fcInfoReqHandler( const Packets::GamePacket& inPacket,
                                                      Entity::PlayerPtr pPlayer )
{
   GamePacketPtr pPe( new GamePacket( 0xDD, 0x78, pPlayer->getId(), pPlayer->getId() ) );
   pPe->setValAt< uint8_t >( 0x48, 0x01 );
   queueOutPacket( pPe );
}

void Core::Network::GameConnection::setSearchInfoHandler( const Packets::GamePacket& inPacket,
                                                          Entity::PlayerPtr pPlayer )
{
   uint32_t inval = inPacket.getValAt< uint32_t >( 0x20 );
   uint32_t inval1 = inPacket.getValAt< uint32_t >( 0x24 );
   uint64_t status = inPacket.getValAt< uint64_t >( 0x20 );

   uint8_t selectRegion = inPacket.getValAt< uint8_t >( 0x31 );

   pPlayer->setSearchInfo( selectRegion, 0, inPacket.getStringAt( 0x32 ) );

   pPlayer->setOnlineStatusMask( status );

   if( pPlayer->isNewAdventurer() && !( inval & 0x01000000 ) )
      // mark player as not new adventurer anymore
      pPlayer->setNewAdventurer( false );
   else if( inval & 0x01000000 )
      // mark player as new adventurer
      pPlayer->setNewAdventurer( true );

   ZoneChannelPacket< FFXIVIpcSetOnlineStatus > statusPacket( pPlayer->getId() );
   statusPacket.data().onlineStatusFlags = status;
   queueOutPacket( statusPacket );

   ZoneChannelPacket< FFXIVIpcSetSearchInfo > searchInfoPacket( pPlayer->getId() );
   searchInfoPacket.data().onlineStatusFlags = status;
   searchInfoPacket.data().selectRegion = pPlayer->getSearchSelectRegion();
   strcpy( searchInfoPacket.data().searchMessage, pPlayer->getSearchMessage() );
   queueOutPacket( searchInfoPacket );

   pPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), SetStatusIcon,
                                                     static_cast< uint8_t >( pPlayer->getOnlineStatus() ) ),
                              true );
}

void Core::Network::GameConnection::reqSearchInfoHandler( const Packets::GamePacket& inPacket,
                                                          Entity::PlayerPtr pPlayer )
{
   ZoneChannelPacket< FFXIVIpcInitSearchInfo > searchInfoPacket( pPlayer->getId() );
   searchInfoPacket.data().onlineStatusFlags = pPlayer->getOnlineStatusMask();
   searchInfoPacket.data().selectRegion = pPlayer->getSearchSelectRegion();
   strcpy( searchInfoPacket.data().searchMessage, pPlayer->getSearchMessage() );
   queueOutPacket( searchInfoPacket );
}

void Core::Network::GameConnection::linkshellListHandler( const Packets::GamePacket& inPacket,
                                                          Entity::PlayerPtr pPlayer )
{
   ZoneChannelPacket< FFXIVIpcLinkshellList > linkshellListPacket( pPlayer->getId() );
   queueOutPacket( linkshellListPacket );
}

void Core::Network::GameConnection::updatePositionHandler( const Packets::GamePacket& inPacket,
                                                           Entity::PlayerPtr pPlayer )
{
   // if the player is marked for zoning we no longer want to update his pos
   if( pPlayer->isMarkedForZoning() )
      return;

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

   uint16_t flags = inPacket.getValAt<uint16_t>( 0x28 );
   memcpy( &IPC_OP_019AB, &flags, 2 );

   uint32_t flags1 = inPacket.getValAt<uint32_t>( 0x24 );
   memcpy( &IPC_OP_019A, &flags1, 4 );

   //g_log.Log(LoggingSeverity::debug, "" + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit1)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit2)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit3)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit4)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit5)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit6)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit7)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit8)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit9)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit10)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit11)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit12)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit13)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit14)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit15)
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019AB.bit16)
   //                                     + " " + boost::lexical_cast<std::string>((int)flags));

   //g_log.Log(LoggingSeverity::debug, "\n" + boost::lexical_cast<std::string>((int)IPC_OP_019A.specialMovement) + "\n"
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019A.strafe) + "\n"
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019A.moveBackward) + "\n"
   //                                     + boost::lexical_cast<std::string>((int)IPC_OP_019A.strafeRight));

   //g_log.Log(LoggingSeverity::debug, pInPacket->toString());

   //pInPacket->debugPrint();

   bool bPosChanged = false;
   if( ( pPlayer->getPos().x != inPacket.getValAt< float >( 0x2c ) ) ||
       ( pPlayer->getPos().y != inPacket.getValAt< float >( 0x30 ) ) ||
       ( pPlayer->getPos().z != inPacket.getValAt< float >( 0x34 ) ) )
      bPosChanged = true;
   if( !bPosChanged  && pPlayer->getRotation() == inPacket.getValAt< float >( 0x20 ) )
      return;

   pPlayer->setRotation( inPacket.getValAt< float >( 0x20 ) );
   pPlayer->setPosition( inPacket.getValAt< float >( 0x2c ),
                         inPacket.getValAt< float >( 0x30 ),
                         inPacket.getValAt< float >( 0x34 ) );

   if( ( pPlayer->getCurrentAction() != nullptr ) && bPosChanged )
      pPlayer->getCurrentAction()->setInterrupted();

   // if no one is in range, don't bother trying to send a position update
   if( !pPlayer->hasInRangeActor() )
      return;

   uint8_t unk = inPacket.getValAt< uint8_t >( 0x29 );

   uint16_t moveType = inPacket.getValAt< uint16_t >( 0x28 );

   uint8_t unk1 = 0;
   uint8_t unk2 = 0;
   uint8_t unk3 = unk;
   uint16_t unk4 = 0;

   // HACK: This part is hackish, we need to find out what all theese things really do.
   switch( moveType )
   {
   case MoveType::Strafe:
   {
      if( IPC_OP_019A.strafeRight == 1 )
         unk1 = 0xbf;
      else
         unk1 = 0x5f;
      unk4 = 0x3C;
      break;
   }

   case 6:
   {
      unk1 = 0xFF;
      unk2 = 0x06;
      unk4 = 0x18;
      break;
   }

   //   case MoveType::Land:
   //	{
   //           unk1 = 0x7F;
   //		//unk2 = 0x40;
   //		unk4 = 0x3C;
   //		break;
   //	}

   //   case MoveType::Jump:
   //	{
   //		unk1 = 0x7F;
   //		if(unk == 0x01)
   //           {
   //		//	unk2 = 0x20;
   //			//unk4 = 0x32;
   //               unk4 = 0x32;
   //		}
   //           else
   //           {
   //		//	unk2 = 0xA0;
   //			unk4 = 0x3C;
   //		}
   //
   //		break;
   //	}
   //   case MoveType::Fall:
   //	{
   //		unk1 = 0x7F;
   //		//unk2 = 0xA0;
   //		unk4 = 0x3C;
   //
   //		break;
   //	}
   default:
   {
      if( static_cast< int32_t >( IPC_OP_019A.moveBackward ) )
      {
         unk1 = 0xFF;
         unk2 = 0x06;
         unk4 = 0x18; // animation speed?
      }
      else
      {
         unk1 = 0x7F;
         unk4 = 0x3C; // animation speed?
      }

      break;
   }
   }

   MoveActorPacket movePacket( pPlayer, unk1, unk2, unk3, unk4 );
   pPlayer->sendToInRangeSet( movePacket );

}

void Core::Network::GameConnection::reqEquipDisplayFlagsHandler( const Packets::GamePacket& inPacket,
                                                     Entity::PlayerPtr pPlayer )
{
   g_log.info( "[" + std::to_string( pPlayer->getId() ) + "] Setting EquipDisplayFlags to " + std::to_string( inPacket.getValAt< uint8_t >( 0x20 ) ) );
   pPlayer->setEquipDisplayFlags( inPacket.getValAt< uint8_t >( 0x20 ) );
}

void Core::Network::GameConnection::zoneLineHandler( const Packets::GamePacket& inPacket,
                                                     Entity::PlayerPtr pPlayer )
{
   uint32_t zoneLineId = inPacket.getValAt< uint32_t >( 0x20 );

   pPlayer->sendDebug( "Walking ZoneLine " + std::to_string( zoneLineId ) );

   auto pZone = pPlayer->getCurrentZone();

   auto pLine = g_zoneMgr.getZonePosition( zoneLineId );

   Common::FFXIVARR_POSITION3 targetPos{};
   uint32_t targetZone;
   float rotation = 0.0f;

   if( pLine != nullptr )
   {
      pPlayer->sendDebug( "ZoneLine " + std::to_string( zoneLineId ) + " found." );
      targetPos = pLine->getTargetPosition();
      targetZone = pLine->getTargetZoneId();
      rotation = pLine->getTargetRotation();

      ZoneChannelPacket< FFXIVIpcPrepareZoning > preparePacket( pPlayer->getId() );
      preparePacket.data().targetZone = targetZone;

      //ActorControlPacket143 controlPacket( pPlayer, ActorControlType::DespawnZoneScreenMsg,
      //                                     0x03, pPlayer->getId(), 0x01, targetZone );
      pPlayer->queuePacket( preparePacket );
   }
   else
   {
      // No zoneline found, revert to last zone
      pPlayer->sendUrgent( "ZoneLine " + std::to_string( zoneLineId ) + " not found." );
      targetPos.x = 0;
      targetPos.y = 0;
      targetPos.z = 0;
      targetZone = pZone->getId();
   }

   pPlayer->performZoning( targetZone, targetPos, rotation);
}


void Core::Network::GameConnection::discoveryHandler( const Packets::GamePacket& inPacket,
                                                      Entity::PlayerPtr pPlayer )
{
   uint32_t ref_position_id = inPacket.getValAt< uint32_t >( 0x20 );

   auto pQR = g_charaDb.query( "SELECT id, map_id, discover_id "
                               "FROM discoveryinfo "
                               "WHERE id = " + std::to_string( ref_position_id ) + ";" );

   if( !pQR->next() )
   {
      pPlayer->sendNotice( "Discovery ref pos ID: " + std::to_string( ref_position_id ) + " not found. " );
      return;
   }

   ZoneChannelPacket< FFXIVIpcDiscovery > discoveryPacket( pPlayer->getId() );
   discoveryPacket.data().map_id = pQR->getUInt( 2 );
   discoveryPacket.data().map_part_id = pQR->getUInt( 3 );

   pPlayer->queuePacket( discoveryPacket );
   pPlayer->sendNotice( "Discovery ref pos ID: " + std::to_string( ref_position_id ) );

   pPlayer->discover( pQR->getUInt16( 2 ), pQR->getUInt16( 3 ) );

}


void Core::Network::GameConnection::playTimeHandler( const Packets::GamePacket& inPacket,
                                                     Entity::PlayerPtr pPlayer )
{
   ZoneChannelPacket< FFXIVIpcPlayTime > playTimePacket( pPlayer->getId() );
   playTimePacket.data().playTimeInMinutes = pPlayer->getPlayTime() / 60;
   pPlayer->queuePacket( playTimePacket );
}


void Core::Network::GameConnection::initHandler( const Packets::GamePacket& inPacket,
                                                 Entity::PlayerPtr pPlayer )
{
   // init handler means this is a login procedure
   pPlayer->setIsLogin( true );

   pPlayer->setZone( pPlayer->getZoneId() );
}


void Core::Network::GameConnection::blackListHandler( const Packets::GamePacket& inPacket,
                                                      Entity::PlayerPtr pPlayer )
{
   uint8_t count = inPacket.getValAt< uint8_t >( 0x21 );

   ZoneChannelPacket< FFXIVIpcBlackList > blackListPacket( pPlayer->getId() );
   blackListPacket.data().sequence = count;
   // TODO: Fill with actual blacklist data
   //blackListPacket.data().entry[0].contentId = 1;
   //sprintf( blackListPacket.data().entry[0].name, "Test Test" );
   queueOutPacket( blackListPacket );

}


void Core::Network::GameConnection::pingHandler( const Packets::GamePacket& inPacket,
                                                 Entity::PlayerPtr pPlayer )
{
   int32_t inVal = inPacket.getValAt< int32_t >( 0x20 );
   PingPacket pingPacket( pPlayer, inVal );
   queueOutPacket( pingPacket );

   pPlayer->setLastPing( static_cast< uint32_t >( time( nullptr ) ) );
}


void Core::Network::GameConnection::finishLoadingHandler( const Packets::GamePacket& inPacket,
                                                          Entity::PlayerPtr pPlayer )
{
   // player is done zoning
   pPlayer->setLoadingComplete( true );

   // if this is a login event
   if( pPlayer->isLogin() )
   {
      // fire the onLogin Event
      pPlayer->onLogin();
      pPlayer->setIsLogin( false );
   }

   // spawn the player for himself
   pPlayer->spawn( pPlayer );

   // notify the zone of a change in position to force an "inRangeActor" update
   pPlayer->getCurrentZone()->changeActorPosition( pPlayer );
}

void Core::Network::GameConnection::socialListHandler( const Packets::GamePacket& inPacket,
                                                       Entity::PlayerPtr pPlayer )
{

   uint8_t type = inPacket.getValAt< uint8_t >( 0x2A );
   uint8_t count = inPacket.getValAt< uint8_t >( 0x2B );

   if( type == 0x02 )
   { // party list

      ZoneChannelPacket< FFXIVIpcSocialList > listPacket( pPlayer->getId() );;

      listPacket.data().type = 2;
      listPacket.data().sequence = count;

      int32_t entrysizes = sizeof( listPacket.data().entries );
      memset( listPacket.data().entries, 0, sizeof( listPacket.data().entries ) );

      listPacket.data().entries[0].bytes[2] = pPlayer->getCurrentZone()->getId();
      listPacket.data().entries[0].bytes[3] = 0x80;
      listPacket.data().entries[0].bytes[4] = 0x02;
      listPacket.data().entries[0].bytes[6] = 0x3B;
      listPacket.data().entries[0].bytes[11] = 0x10;
      listPacket.data().entries[0].classJob = static_cast< uint8_t >( pPlayer->getClass() );
      listPacket.data().entries[0].contentId = pPlayer->getContentId();
      listPacket.data().entries[0].level = pPlayer->getLevel();
      listPacket.data().entries[0].zoneId = pPlayer->getCurrentZone()->getId();
      listPacket.data().entries[0].grandCompany = pPlayer->getGc();
      memcpy( &listPacket.data().entries[0].fcTag[0], "Sapphire", sizeof( "Sapphire" ) );
      listPacket.data().entries[0].clientLanguage = 2;
      listPacket.data().entries[0].knownLanguages = 0x0F;
      // TODO: no idea what this does
      //listPacket.data().entries[0].one = 1;

      memcpy( listPacket.data().entries[0].name, pPlayer->getName().c_str(), strlen( pPlayer->getName().c_str() ) );

      listPacket.data().entries[0].onlineStatusMask = pPlayer->getOnlineStatusMask();

      queueOutPacket( listPacket );

   }
   else if( type == 0x0b )
   { // friend list

      ZoneChannelPacket< FFXIVIpcSocialList > listPacket( pPlayer->getId() );
      listPacket.data().type = 0x0B;
      listPacket.data().sequence = count;
      memset( listPacket.data().entries, 0, sizeof( listPacket.data().entries ) );

   }
   else if( type == 0x0e )
   { // player search result
     // TODO: implement player search
   }

}

void Core::Network::GameConnection::socialReqSendHandler(const Packets::GamePacket& inPacket,
   Entity::PlayerPtr pPlayer)
{
   g_log.debug("send");
}

void Core::Network::GameConnection::chatHandler( const Packets::GamePacket& inPacket,
                                                 Entity::PlayerPtr pPlayer )
{

   std::string chatString( inPacket.getStringAt( 0x3a ) );

   uint32_t sourceId = inPacket.getValAt< uint32_t >( 0x24 );

   if( chatString.at( 0 ) == '!' )
   {
      // execute game console command
      g_gameCommandMgr.execCommand( const_cast< char * >( chatString.c_str() ) + 1, pPlayer );
      return;
   }

   ChatType chatType = static_cast<ChatType>( inPacket.getValAt< uint8_t >( 0x38 ) );

   //ToDo, need to implement sending GM chat types.
   ChatPacket chatPacket( pPlayer, chatType, chatString );

   switch( chatType )
   {
   case ChatType::Say:
   {
      pPlayer->getCurrentZone()->queueOutPacketForRange( pPlayer, 50, chatPacket );
      break;
   }
   case ChatType::Yell:
   {
      pPlayer->getCurrentZone()->queueOutPacketForRange(pPlayer, 6000, chatPacket);
      break;
   }
   case ChatType::Shout:
   {
      pPlayer->getCurrentZone()->queueOutPacketForRange( pPlayer, 6000, chatPacket );
      break;
   }
   default:
   {
      pPlayer->getCurrentZone()->queueOutPacketForRange( pPlayer, 50, chatPacket );
      break;
   }
   }

}

// TODO: this handler needs to be improved for timed logout, also the session should be instantly removed
// currently we wait for the session to just time out after logout, this can be a problem is the user tries to
// log right back in.
// Also the packet needs to be converted to an ipc structure
void Core::Network::GameConnection::logoutHandler( const Packets::GamePacket& inPacket,
                                                   Entity::PlayerPtr pPlayer )
{
   ZoneChannelPacket< FFXIVIpcLogout > logoutPacket( pPlayer->getId() );
   logoutPacket.data().flags1 = 0x02;
   logoutPacket.data().flags2 = 0x2000;
   queueOutPacket( logoutPacket );

   pPlayer->setMarkedForRemoval();
}


void Core::Network::GameConnection::tellHandler( const Packets::GamePacket& inPacket,
                                                 Entity::PlayerPtr pPlayer )
{
   std::string targetPcName = inPacket.getStringAt( 0x21 );
   std::string msg = inPacket.getStringAt( 0x41 );

   auto pSession = g_serverZone.getSession( targetPcName );

   if( !pSession )
   {
      ChatChannelPacket< FFXIVIpcTellErrNotFound > tellErrPacket( pPlayer->getId() );
      strcpy( tellErrPacket.data().receipientName, targetPcName.c_str() );
      sendSinglePacket( tellErrPacket );

      g_log.debug( "TargetPc not found" );
      return;
   }

   auto pTargetPlayer = pSession->getPlayer();

   if( pTargetPlayer->hasStateFlag( PlayerStateFlag::BetweenAreas ) ||
       pTargetPlayer->hasStateFlag( PlayerStateFlag::BetweenAreas1 ) )
   {
      // send error for player between areas
      // TODO: implement me
      return;
   }

   if( pTargetPlayer->hasStateFlag( PlayerStateFlag::BoundByDuty ) ||
       pTargetPlayer->hasStateFlag( PlayerStateFlag::BoundByDuty1 ) )
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

   ChatChannelPacket< FFXIVIpcTell > tellPacket( pPlayer->getId() );
   strcpy( tellPacket.data().msg, msg.c_str() );
   strcpy( tellPacket.data().receipientName, pPlayer->getName().c_str() );
   // TODO: do these have a meaning?
   //tellPacket.data().u1 = 0x92CD7337;
   //tellPacket.data().u2a = 0x2E;
   //tellPacket.data().u2b = 0x40;
   pTargetPlayer->queueChatPacket( tellPacket );

}

void Core::Network::GameConnection::performNoteHandler( const Packets::GamePacket& inPacket,
                                                        Entity::PlayerPtr pPlayer )
{
   GamePacketNew< FFXIVIpcPerformNote, ServerZoneIpcType > performPacket( pPlayer->getId() );

   uint8_t inVal = inPacket.getValAt< uint8_t >( 0x20 );
   memcpy( &performPacket.data().data[0], &inVal, 32 );

   pPlayer->sendToInRangeSet( performPacket );
}
