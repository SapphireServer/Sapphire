#include <Server_Common/Common.h>
#include <Server_Common/CommonNetwork.h>
#include <Server_Common/Database.h>
#include <Server_Common/GamePacketNew.h>
#include <Server_Common/Logger.h>
#include <Server_Common/ExdData.h>
#include <Server_Common/PacketContainer.h>

#include <boost/format.hpp>


#include "GameConnection.h"

#include "Session.h"
#include "Zone.h"
#include "ZonePosition.h"
#include "ServerZone.h"
#include "ZoneMgr.h"

#include "InitUIPacket.h"
#include "PingPacket.h"
#include "MoveActorPacket.h"
#include "ChatPacket.h"
#include "ServerNoticePacket.h"
#include "ActorControlPacket142.h"
#include "ActorControlPacket143.h"
#include "ActorControlPacket144.h"
#include "EventStartPacket.h"
#include "EventFinishPacket.h"
#include "PlayerStateFlagsPacket.h"


#include "GameCommandHandler.h"

#include "Player.h"
#include "Inventory.h"

#include "Forwards.h"

#include "EventHelper.h"

#include "Action.h"
#include "ActionTeleport.h"

extern Core::Logger g_log;
extern Core::Db::Database g_database;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::GameCommandHandler g_gameCommandMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Network::GameConnection::fcInfoReqHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                               Core::Entity::PlayerPtr pPlayer )
{
   GamePacketPtr pPe( new GamePacket( 0xDD, 0x78, pPlayer->getId(), pPlayer->getId() ) );
   pPe->setValAt< uint8_t >( 0x48, 0x01 );
   queueOutPacket( pPe );
}

void Core::Network::GameConnection::setSearchInfoHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                          Core::Entity::PlayerPtr pPlayer )
{
   uint32_t inval = pInPacket->getValAt< uint32_t >( 0x20 );
   uint32_t inval1 = pInPacket->getValAt< uint32_t >( 0x24 );
   uint64_t status = pInPacket->getValAt< uint64_t >( 0x20 );

   uint8_t selectRegion = pInPacket->getValAt< uint8_t >( 0x31 );

   pPlayer->setSearchInfo( selectRegion, 0, pInPacket->getStringAt( 0x32 ) );

   pPlayer->setOnlineStatusMask( status );

   if( pPlayer->isNewAdventurer() && !( inval & 0x01000000 ) )
      // mark player as not new adventurer anymore
      pPlayer->setNewAdventurer( false );
   else if( inval & 0x01000000 )
      // mark player as new adventurer
      pPlayer->setNewAdventurer( true );

   GamePacketNew< FFXIVIpcSetOnlineStatus > statusPacket( pPlayer->getId() );
   statusPacket.data().onlineStatusFlags = status;
   queueOutPacket( statusPacket );

   GamePacketNew< FFXIVIpcSetSearchInfo > searchInfoPacket( pPlayer->getId() );
   searchInfoPacket.data().onlineStatusFlags = status;
   searchInfoPacket.data().selectRegion = pPlayer->getSearchSelectRegion();
   sprintf( searchInfoPacket.data().searchMessage, pPlayer->getSearchMessage() );
   queueOutPacket( searchInfoPacket );

   pPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), SetStatusIcon,
                                                     static_cast< uint8_t >( pPlayer->getOnlineStatus() ) ),
                              true );
}

void Core::Network::GameConnection::reqSearchInfoHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                          Core::Entity::PlayerPtr pPlayer )
{
   GamePacketNew< FFXIVIpcInitSearchInfo > searchInfoPacket( pPlayer->getId() );
   searchInfoPacket.data().onlineStatusFlags = pPlayer->getOnlineStatusMask();
   searchInfoPacket.data().selectRegion = pPlayer->getSearchSelectRegion();
   sprintf( searchInfoPacket.data().searchMessage, pPlayer->getSearchMessage() );
   queueOutPacket( searchInfoPacket );
}

void Core::Network::GameConnection::linkshellListHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                          Core::Entity::PlayerPtr pPlayer )
{
   GamePacketNew< FFXIVIpcLinkshellList > linkshellListPacket( pPlayer->getId() );
   queueOutPacket( linkshellListPacket );
}

// TODO: move this and the handlers to a gm command handler
enum GmCommand
{
   Pos = 0x0000,
   Lv = 0x0001,
   Race = 0x0002,
   Tribe = 0x0003,
   Sex = 0x0004,
   Time = 0x0005,
   Weather = 0x0006,
   Call = 0x0007,
   Inspect = 0x0008,
   Speed = 0x0009,
   Invis = 0x000D,

   Raise = 0x0010,
   Kill = 0x000E,
   Icon = 0x0012,

   Hp = 0x0064,
   Mp = 0x0065,
   Tp = 0x0066,
   Gp = 0x0067,

   Item = 0x00C8,
   Gil = 0x00C9,
   Collect = 0x00CA,

   QuestAccept = 0x012C,
   QuestCancel = 0x012D,
   QuestComplete = 0x012E,
   QuestIncomplete = 0x012F,
   QuestSequence = 0x0130,
   QuestInspect = 0x0131,
   GC = 0x0154,
   GCRank = 0x0155,
   TeriInfo = 0x025D,
   Jump = 0x025E,
   JumpNpc = 0x025F,
};
void Core::Network::GameConnection::gm1Handler( Core::Network::Packets::GamePacketPtr pInPacket,
   Core::Entity::PlayerPtr pPlayer )
{
   uint32_t commandId = pInPacket->getValAt< uint32_t >( 0x20 );
   uint32_t param1 = pInPacket->getValAt< uint32_t >( 0x24 );
   uint32_t param2 = pInPacket->getValAt< uint32_t >( 0x28 );
   uint32_t param3 = pInPacket->getValAt< uint32_t >( 0x38 );

   g_log.debug( pPlayer->getName() + " used GM1 commandId: " + std::to_string( commandId ) + ", params: " + std::to_string( param1 ) + ", " + std::to_string( param2 ) + ", " + std::to_string( param3 ) );

   Core::Entity::ActorPtr targetActor;

   if( pPlayer->getId() == param3 )
   {
      targetActor = pPlayer;
   }
   else {
      auto inRange = pPlayer->getInRangeActors();
      for( auto actor : inRange )
      {
         if( actor->getId() == param3 )
         {
            targetActor = actor;
         }
      }
   }

   switch( commandId )
   {
   case GmCommand::Kill:
   {
      targetActor->takeDamage( 9999999 );
      pPlayer->sendNotice( "Killed " + std::to_string( targetActor->getId() ) );
      break;
   }
   case GmCommand::QuestSequence:
   {
      targetActor->getAsPlayer()->updateQuest( param1, param2 );
      break;
   }
   case GmCommand::QuestComplete:
   {
      targetActor->getAsPlayer()->finishQuest( param1 );
      break;
   }
   case GmCommand::QuestAccept:
   {
      targetActor->getAsPlayer()->updateQuest( param1, 1 );
      break;
   }
   case GmCommand::QuestCancel:
   {
      targetActor->getAsPlayer()->removeQuest( param1 );
      break;
   }
   case GmCommand::QuestIncomplete:
   {
      targetActor->getAsPlayer()->unfinishQuest( param1 );
      break;
   }
   case GmCommand::Speed:
   {
      targetActor->getAsPlayer()->queuePacket( ActorControlPacket143( pPlayer->getId(), Flee, param1 ) );
      pPlayer->sendNotice( "Speed for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Gil:
   {
      targetActor->getAsPlayer()->addCurrency( 1, param1 );
      pPlayer->sendNotice( "Added  " + std::to_string( param1 ) + " Gil for " + targetActor->getAsPlayer()->getName() );
      break;
   }
   case GmCommand::Lv:
   {
      targetActor->getAsPlayer()->setLevel( param1 );
      pPlayer->sendNotice( "Level for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Hp:
   {
      targetActor->getAsPlayer()->setHp( param1 );
      pPlayer->sendNotice( "Tp for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Mp:
   {
      targetActor->getAsPlayer()->setMp( param1 );
      pPlayer->sendNotice( "Mp for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Gp:
   {
      targetActor->getAsPlayer()->setHp( param1 );
      pPlayer->sendNotice( "Gp for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Sex:
   {
      targetActor->getAsPlayer()->setLookAt( CharaLook::Gender, param1 );
      pPlayer->sendNotice( "Sex for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      targetActor->spawn( targetActor->getAsPlayer() );
      auto inRange = targetActor->getInRangeActors();
      for( auto actor : inRange )
      {
         targetActor->getAsPlayer()->despawn( actor->getAsPlayer() );
         targetActor->getAsPlayer()->spawn( actor->getAsPlayer() );
      }
      break;
   }
   case GmCommand::Race:
   {
      targetActor->getAsPlayer()->setLookAt( CharaLook::Race, param1 );
      pPlayer->sendNotice( "Race for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      targetActor->spawn( targetActor->getAsPlayer() );
      auto inRange = targetActor->getInRangeActors();
      for( auto actor : inRange )
      {
         targetActor->getAsPlayer()->despawn( actor->getAsPlayer() );
         targetActor->getAsPlayer()->spawn( actor->getAsPlayer() );
      }
      break;
   }
   case GmCommand::Tribe:
   {
      targetActor->getAsPlayer()->setLookAt( CharaLook::Tribe, param1 );
      pPlayer->sendNotice( "Tribe for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      targetActor->spawn( targetActor->getAsPlayer() );
      auto inRange = targetActor->getInRangeActors();
      for( auto actor : inRange )
      {
         targetActor->getAsPlayer()->despawn( actor->getAsPlayer() );
         targetActor->getAsPlayer()->spawn( actor->getAsPlayer() );
      }
      break;
   }
   case GmCommand::Item:
   {
      if( param2 < 1 || param2 > 99 )
      {
         param2 = 1;
      }

      if( ( param1 == 0xcccccccc ) )
      {
         pPlayer->sendUrgent( "Syntaxerror." );
         return;
      }

      if( !targetActor->getAsPlayer()->addItem( -1, param1, param2 ) )
         pPlayer->sendUrgent( "Item " + std::to_string( param1 ) + " not found..." );
      break;
   }
   case GmCommand::Weather:
   {
      targetActor->getAsPlayer()->getCurrentZone()->setWeatherOverride( param1 );
      pPlayer->sendNotice( "Weather in Zone \"" + targetActor->getAsPlayer()->getCurrentZone()->getName() + "\" of " + targetActor->getAsPlayer()->getName() + " set in range." );
      break;
   }
   case GmCommand::TeriInfo:
   {
      pPlayer->sendNotice( "ZoneId: " + std::to_string( pPlayer->getZoneId() ) + "\nName: " + pPlayer->getCurrentZone()->getName() + "\nInternalName: " + pPlayer->getCurrentZone()->getInternalName() + "\nPopCount: " + std::to_string( pPlayer->getCurrentZone()->getPopCount() ) + 
                           "\nCurrentWeather:" + std::to_string( pPlayer->getCurrentZone()->getCurrentWeather() ) + "\nNextWeather:" + std::to_string( pPlayer->getCurrentZone()->getNextWeather() ) );
      break;
   }
   case GmCommand::Jump:
   {
      
      auto inRange = pPlayer->getInRangeActors();
      for( auto actor : inRange )
      {
         pPlayer->changePosition( targetActor->getPos().x, targetActor->getPos().y, targetActor->getPos().z, targetActor->getRotation() );
      }
      pPlayer->sendNotice( "Jumping to " + targetActor->getAsPlayer()->getName() + " in range." );
      break;
   }
   case GmCommand::Collect:
   {
      uint32_t gil = targetActor->getAsPlayer()->getCurrency( 1 );
      
      if( gil < param1 )
      {
         pPlayer->sendUrgent( "Player does not have enough Gil(" + std::to_string( gil ) + ")" );
      }
      else
      {
         targetActor->getAsPlayer()->removeCurrency( 1, param1 );
         pPlayer->sendNotice( "Removed " + std::to_string( param1 ) + " Gil from " + targetActor->getAsPlayer()->getName() + "(" + std::to_string( gil ) + " before)" );
      }
      break;
   }
   case GmCommand::Icon:
   {
      targetActor->getAsPlayer()->setOnlineStatusMask( param1 );

      GamePacketNew< FFXIVIpcSetOnlineStatus > statusPacket( targetActor->getAsPlayer()->getId() );
      statusPacket.data().onlineStatusFlags = param1;
      queueOutPacket( statusPacket );

      GamePacketNew< FFXIVIpcSetSearchInfo > searchInfoPacket( targetActor->getAsPlayer()->getId() );
      searchInfoPacket.data().onlineStatusFlags = param1;
      searchInfoPacket.data().selectRegion = targetActor->getAsPlayer()->getSearchSelectRegion();
      sprintf( searchInfoPacket.data().searchMessage, targetActor->getAsPlayer()->getSearchMessage() );
      targetActor->getAsPlayer()->queuePacket( searchInfoPacket );

      targetActor->getAsPlayer()->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), SetStatusIcon,
         static_cast< uint8_t >( pPlayer->getOnlineStatus() ) ),
         true );
      pPlayer->sendNotice( "Icon for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::GC:
   {
      targetActor->getAsPlayer()->setGc( param1 );
      pPlayer->sendNotice( "GC for " + targetActor->getAsPlayer()->getName() + " was set to " + std::to_string( targetActor->getAsPlayer()->getGc() ) );
      break;
   }
   case GmCommand::GCRank:
   {
      targetActor->getAsPlayer()->setGcRankAt( targetActor->getAsPlayer()->getGc() - 1, param1 );
      pPlayer->sendNotice( "GC Rank for  " + targetActor->getAsPlayer()->getName() + " for GC " + std::to_string( targetActor->getAsPlayer()->getGc()) + " was set to " + std::to_string( targetActor->getAsPlayer()->getGcRankArray()[targetActor->getAsPlayer()->getGc() - 1] ) );
      break;
   }

   default:
      pPlayer->sendUrgent( "GM1 Command not implemented: " + std::to_string( commandId ) );
      break;
   }

}

void Core::Network::GameConnection::gm2Handler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                Core::Entity::PlayerPtr pPlayer )
{
   uint32_t commandId = pInPacket->getValAt< uint32_t >( 0x20 );
   std::string param1 = pInPacket->getStringAt( 0x34 );

   g_log.debug( pPlayer->getName() + " used GM2 commandId: " + std::to_string( commandId ) + ", params: " + param1 );

   auto targetSession = g_serverZone.getSession( param1 );
   Core::Entity::ActorPtr targetActor;

   if( targetSession != nullptr )
   {
      targetActor = targetSession->getPlayer();
   }
   else
   {
      if( param1 == "self" )
      {
         targetActor = pPlayer;
      }
      else 
      {
         pPlayer->sendUrgent("Player " + param1 + " not found on this server.");
         return;
      }
   }

   switch( commandId )
   {
   case GmCommand::Raise:
   {
      targetActor->getAsPlayer()->resetHp();
      targetActor->getAsPlayer()->resetMp();
      targetActor->getAsPlayer()->setStatus( Entity::Actor::ActorStatus::Idle );
      targetActor->getAsPlayer()->setSyncFlag( Status );

      targetActor->getAsPlayer()->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01, 0x01, 0, 113 ), true );
      targetActor->getAsPlayer()->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), SetStatus, static_cast< uint8_t >( Entity::Actor::ActorStatus::Idle ) ), true );
      pPlayer->sendNotice( "Raised  " + targetActor->getAsPlayer()->getName());
      break;
   }
   case GmCommand::Jump:
   {
      if( targetActor->getAsPlayer()->getZoneId() != pPlayer->getZoneId() )
      {
         pPlayer->setZone( targetActor->getAsPlayer()->getZoneId() );
      }
      pPlayer->changePosition( targetActor->getPos().x, targetActor->getPos().y, targetActor->getPos().z, targetActor->getRotation() );
      pPlayer->sendNotice( "Jumping to " + targetActor->getAsPlayer()->getName());
      break;
   }
   case GmCommand::Call:
   {
      if( targetActor->getAsPlayer()->getZoneId() != pPlayer->getZoneId() )
      {
         targetActor->getAsPlayer()->setZone( pPlayer->getZoneId() );
      }
      targetActor->getAsPlayer()->changePosition( pPlayer->getPos().x, pPlayer->getPos().y, pPlayer->getPos().z, pPlayer->getRotation() );
      pPlayer->sendNotice( "Calling " + targetActor->getAsPlayer()->getName() );
      break;
   }
   case GmCommand::Inspect:
   {
      pPlayer->sendNotice( "Name: " + targetActor->getAsPlayer()->getName() + "\nGil: " + std::to_string( targetActor->getAsPlayer()->getCurrency( 1 ) ) + "\nZone: " + targetActor->getAsPlayer()->getCurrentZone()->getName() + "(" + std::to_string( targetActor->getAsPlayer()->getZoneId() ) + ")" +
         "\nClass: " + std::to_string( targetActor->getAsPlayer()->getClass() ) + "\nLevel: " + std::to_string( targetActor->getAsPlayer()->getLevel() ) + "\nExp: " + std::to_string( targetActor->getAsPlayer()->getExp() ) + "\nSearchMessage: " + targetActor->getAsPlayer()->getSearchMessage() +
         "\nPlayTime: " + std::to_string( targetActor->getAsPlayer()->getPlayTime() ) );
      break;
   }

   default:
      pPlayer->sendUrgent( "GM2 Command not implemented: " + std::to_string( commandId ) );
      break;
   }
}

void Core::Network::GameConnection::updatePositionHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                           Core::Entity::PlayerPtr pPlayer )
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

   uint16_t flags = pInPacket->getValAt<uint16_t>( 0x28 );
   memcpy( &IPC_OP_019AB, &flags, 2 );

   uint32_t flags1 = pInPacket->getValAt<uint32_t>( 0x24 );
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
   if( ( pPlayer->getPos().x != pInPacket->getValAt< float >( 0x2c ) ) ||
       ( pPlayer->getPos().y != pInPacket->getValAt< float >( 0x30 ) ) ||
       ( pPlayer->getPos().z != pInPacket->getValAt< float >( 0x34 ) ) )
      bPosChanged = true;
   if( !bPosChanged  && pPlayer->getRotation() == pInPacket->getValAt< float >( 0x20 ) )
      return;

   pPlayer->setRotation( pInPacket->getValAt< float >( 0x20 ) );
   pPlayer->setPosition( pInPacket->getValAt< float >( 0x2c ),
                         pInPacket->getValAt< float >( 0x30 ),
                         pInPacket->getValAt< float >( 0x34 ) );

   pPlayer->setSyncFlag( PlayerSyncFlags::Position );

   if( ( pPlayer->getCurrentAction() != nullptr ) && bPosChanged )
      pPlayer->getCurrentAction()->setInterrupted();

   // if no one is in range, don't bother trying to send a position update
   if( !pPlayer->hasInRangeActor() )
      return;

   uint8_t unk = pInPacket->getValAt< uint8_t >( 0x29 );

   uint16_t moveType = pInPacket->getValAt< uint16_t >( 0x28 );

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
      if( static_cast< int >( IPC_OP_019A.moveBackward ) )
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



void Core::Network::GameConnection::zoneLineHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                     Core::Entity::PlayerPtr pPlayer )
{
   uint32_t zoneLineId = pInPacket->getValAt< uint32_t >( 0x20 );

   auto pZone = pPlayer->getCurrentZone();

   auto pLine = g_zoneMgr.getZonePosition( zoneLineId );

   Common::FFXIVARR_POSITION3 targetPos;
   uint32_t targetZone;
   float rotation = 0.0f;

   if( pLine != nullptr )
   {
      g_log.debug( "ZoneLine " + std::to_string( zoneLineId ) + " found." );
      targetPos = pLine->getTargetPosition();
      targetZone = pLine->getTargetZoneId();
      rotation = pLine->getTargetRotation();

      GamePacketNew< FFXIVIpcPrepareZoning > preparePacket( pPlayer->getId() );
      preparePacket.data().targetZone = targetZone;

      //ActorControlPacket143 controlPacket( pPlayer, ActorControlType::DespawnZoneScreenMsg,
      //                                     0x03, pPlayer->getId(), 0x01, targetZone );
      pPlayer->queuePacket( preparePacket );
   }
   else
   {
      // No zoneline found, revert to last zone
      g_log.debug( "ZoneLine " + std::to_string( zoneLineId ) + " not found." );
      targetPos.x = 0;
      targetPos.y = 0;
      targetPos.z = 0;
      targetZone = pZone->getId();
   }

   pPlayer->performZoning( targetZone, targetPos, rotation);
   pPlayer->setSyncFlag( PlayerSyncFlags::Position );

}



void Core::Network::GameConnection::discoveryHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                      Core::Entity::PlayerPtr pPlayer )
{
   uint32_t ref_position_id = pInPacket->getValAt< uint32_t >( 0x20 );

   auto pQR = g_database.query( "SELECT id, map_id, discover_id "
                                "FROM discoveryinfo "
                                "WHERE id = " + std::to_string( ref_position_id ) + ";" );

   if( !pQR )
   {
      pPlayer->sendNotice( "Discovery ref pos ID: " + std::to_string( ref_position_id ) + " not found. " );
      return;
   }

   Db::Field *field = pQR->fetch();

   GamePacketNew< FFXIVIpcDiscovery > discoveryPacket( pPlayer->getId() );
   discoveryPacket.data().map_id = field[1].getInt16();
   discoveryPacket.data().map_part_id = field[2].getInt16();

   pPlayer->queuePacket( discoveryPacket );
   pPlayer->sendNotice( "Discovery ref pos ID: " + std::to_string( ref_position_id ) );

   pPlayer->discover( field[1].getInt16(), field[2].getInt16() );

}

void Core::Network::GameConnection::inventoryModifyHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                            Core::Entity::PlayerPtr pPlayer )
{
   uint32_t seq = pInPacket->getValAt< uint32_t >( 0x20 );
   uint8_t action = pInPacket->getValAt< uint8_t >( 0x24 );
   uint8_t fromSlot = pInPacket->getValAt< uint8_t >( 0x30 );
   uint8_t toSlot = pInPacket->getValAt< uint8_t >( 0x44 );
   uint16_t fromContainer = pInPacket->getValAt< uint16_t >( 0x2C );
   uint16_t toContainer = pInPacket->getValAt< uint16_t >( 0x40 );

   GamePacketNew< FFXIVIpcInventoryActionAck > ackPacket( pPlayer->getId() );
   ackPacket.data().sequence = seq;
   ackPacket.data().type = 7;
   pPlayer->queuePacket( ackPacket );
   

   g_log.debug( pInPacket->toString() );
   g_log.debug( "InventoryAction: " + std::to_string( action ) );

   // TODO: other inventory operations need to be implemented
   switch( action )
   {

   case 0x07: // discard item action
   {
      pPlayer->getInvetory()->discardItem( fromContainer, fromSlot );
   }
   break;

   case 0x08: // move item action
   {
      pPlayer->getInvetory()->moveItem( fromContainer, fromSlot, toContainer, toSlot );
   }
   break;

   case 0x09: // swap item action
   {
      pPlayer->getInvetory()->swapItem( fromContainer, fromSlot, toContainer, toSlot );
   }
   break;

   case 0x0C: // merge stack action
   {

   }
   break;

   case 0x0A: // split stack action
   {

   }
   break;

   default:

      break;
   }

   pPlayer->setSyncFlag( PlayerSyncFlags::Status );

}


void Core::Network::GameConnection::actionHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                   Core::Entity::PlayerPtr pPlayer )
{
   uint16_t commandId = pInPacket->getValAt< uint16_t >( 0x20 );
   uint64_t param1 = pInPacket->getValAt< uint64_t >( 0x24 );
   uint32_t param11 = pInPacket->getValAt< uint32_t >( 0x24 );
   uint32_t param12 = pInPacket->getValAt< uint32_t >( 0x28 );
   uint32_t param2 = pInPacket->getValAt< uint32_t >( 0x2c );
   uint64_t param3 = pInPacket->getValAt< uint64_t >( 0x38 );

   g_log.debug( "[" + std::to_string( m_pSession->getId() ) + "] Incoming action: " +
                boost::str( boost::format( "%|04X|" ) % ( uint32_t ) ( commandId & 0xFFFF ) ) +
                "\nparam1: " + boost::str( boost::format( "%|016X|" ) % ( uint64_t ) ( param1 & 0xFFFFFFFFFFFFFFF ) ) +
                "\nparam2: " + boost::str( boost::format( "%|08X|" ) % ( uint32_t ) ( param2 & 0xFFFFFFFF ) ) +
                "\nparam3: " + boost::str( boost::format( "%|016X|" ) % ( uint64_t ) ( param3 & 0xFFFFFFFFFFFFFFF ) )
   );


   //g_log.Log(LoggingSeverity::debug, "[" + std::to_string(m_pSession->getId()) + "] " + pInPacket->toString());

   switch( commandId )
   {
   case 0x01:
   {
      if( param11 == 1 )
         pPlayer->setStance( Entity::Actor::Stance::Active );
      else
         pPlayer->setStance( Entity::Actor::Stance::Passive );

      pPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), 0, param11, 1 ) );

      break;
   }
   case 0x02:
   {
      if (param11 == 1)
         pPlayer->setAutoattack( true );
      else
         pPlayer->setAutoattack( false );

      pPlayer->sendToInRangeSet(ActorControlPacket142(pPlayer->getId(), 1, param11, 1));

      break;
   }
   case 0x03: // Change target
   {

      uint64_t targetId = pInPacket->getValAt< uint64_t >( 0x24 );
      pPlayer->changeTarget( targetId );
      break;
   }

   case 0x133: // Update howtos seen
   {
      uint32_t howToId = static_cast< uint32_t >( param1 );
      pPlayer->updateHowtosSeen( howToId );
      break;
   }
   case 0x1F4: // emote
   {
      uint64_t targetId = pPlayer->getTargetId();
      uint32_t emoteId = pInPacket->getValAt< uint32_t >( 0x24 );

      pPlayer->sendToInRangeSet( ActorControlPacket144( pPlayer->getId(), Emote, emoteId, 0, 0, 0, targetId ) );
      break;
   }
   case 0xC8: // return dead
   {
      pPlayer->setZoningType( Common::ZoneingType::Return );
      pPlayer->teleport( pPlayer->getHomepoint(), 3 );
      break;
   }
   case 0xC9: // Finish zoning
   {
      switch( pPlayer->getZoningType() )
      {
      case ZoneingType::None: 
         pPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01 ), true ); 
         break;
      case ZoneingType::Teleport: 
         pPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01, 0, 0, 110 ), true );
         break;
      case ZoneingType::Return:
      case ZoneingType::ReturnDead:
         {
            if( pPlayer->getStatus() == Entity::Actor::ActorStatus::Dead )
            {
               pPlayer->resetHp();
               pPlayer->resetMp();
               pPlayer->setStatus( Entity::Actor::ActorStatus::Idle );
               pPlayer->setSyncFlag( Status );
               pPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01, 0x01, 0, 111 ), true );
               pPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), SetStatus, static_cast< uint8_t >( Entity::Actor::ActorStatus::Idle ) ), true );
            }
            else
               pPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01, 0x00, 0, 111 ), true );
         }
         break;
      case ZoneingType::FadeIn:
         break;
      default: 
         break;
      }
    
      pPlayer->setZoningType( Common::ZoneingType::None );

      pPlayer->unsetStateFlag( PlayerStateFlag::BetweenAreas );
      pPlayer->unsetStateFlag( PlayerStateFlag::BetweenAreas1 );
      pPlayer->sendStateFlags();
      break;
   }

   case 0xCA: // Teleport
   {
      // TODO: only register this action if enough gil is in possession
      auto targetAetheryte = g_exdData.getAetheryteInfo( param11 );
      
      if( targetAetheryte )
      {
         auto fromAetheryte = g_exdData.getAetheryteInfo( g_exdData.m_zoneInfoMap[pPlayer->getZoneId()].aetheryte_index );

         // calculate cost - does not apply for favorite points or homepoints neither checks for aether tickets
         auto cost = ( sqrt( pow( fromAetheryte->map_coord_x - targetAetheryte->map_coord_x, 2 ) +
                             pow( fromAetheryte->map_coord_y - targetAetheryte->map_coord_y, 2 ) ) / 2 ) + 100;

         // cap at 999 gil
         cost = cost > 999 ? 999 : cost;

         bool insufficientGil = pPlayer->getCurrency( Inventory::CurrencyType::Gil ) < cost;
         // todo: figure out what param1 really does
         pPlayer->queuePacket( ActorControlPacket143( pPlayer->getId(), TeleportStart, insufficientGil ? 2 : 0, param11 ) );

         if( !insufficientGil )
         {
            Action::ActionTeleportPtr pActionTeleport( new Action::ActionTeleport( pPlayer, param11, cost ) );
            pPlayer->setCurrentAction( pActionTeleport );
         }
      }
      break;
   }

   }
}


void Core::Network::GameConnection::playTimeHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                     Core::Entity::PlayerPtr pPlayer )
{
   GamePacketNew< FFXIVIpcPlayTime > playTimePacket( pPlayer->getId() );
   playTimePacket.data().playTimeInMinutes = pPlayer->getPlayTime() / 60;
   pPlayer->queuePacket( playTimePacket );
}


void Core::Network::GameConnection::initHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                 Core::Entity::PlayerPtr pPlayer )
{
   // init handler means this is a login procedure
   pPlayer->setIsLogin( true );

   pPlayer->setZone( pPlayer->getZoneId() );
}


void Core::Network::GameConnection::blackListHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                      Core::Entity::PlayerPtr pPlayer )
{
   uint8_t count = pInPacket->getValAt< uint8_t >( 0x21 );

   GamePacketNew< FFXIVIpcBlackList > blackListPacket( pPlayer->getId() );
   blackListPacket.data().sequence = count;
   // TODO: Fill with actual blacklist data
   //blackListPacket.data().entry[0].contentId = 1;
   //sprintf( blackListPacket.data().entry[0].name, "Test Test" );
   queueOutPacket( blackListPacket );

}


void Core::Network::GameConnection::pingHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                 Core::Entity::PlayerPtr pPlayer )
{
   int32_t inVal = pInPacket->getValAt< int32_t >( 0x20 );
   PingPacket pingPacket( pPlayer, inVal );
   queueOutPacket( pingPacket );

   pPlayer->setLastPing( static_cast< uint32_t >( time( nullptr ) ) );
}


void Core::Network::GameConnection::finishLoadingHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                          Core::Entity::PlayerPtr pPlayer )
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

void Core::Network::GameConnection::socialListHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                       Core::Entity::PlayerPtr pPlayer )
{

   uint8_t type = pInPacket->getValAt< uint8_t >( 0x2A );
   uint8_t count = pInPacket->getValAt< uint8_t >( 0x2B );

   if( type == 0x02 )
   { // party list

      GamePacketNew< FFXIVIpcSocialList > listPacket( pPlayer->getId() );;

      listPacket.data().type = 2;
      listPacket.data().sequence = count;

      int entrysizes = sizeof( listPacket.data().entries );
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
      listPacket.data().entries[0].zoneId1 = 0x0100;
      // TODO: no idea what this does
      //listPacket.data().entries[0].one = 1;

      memcpy( listPacket.data().entries[0].name, pPlayer->getName().c_str(), strlen( pPlayer->getName().c_str() ) );

      // TODO: actually store and read language from somewhere
      listPacket.data().entries[0].bytes1[0] = 0x01;//flags (lang)
                                                    // TODO: these flags need to be figured out
                                                    //listPacket.data().entries[0].bytes1[1] = 0x00;//flags
      listPacket.data().entries[0].onlineStatusMask = pPlayer->getOnlineStatusMask();

      queueOutPacket( listPacket );

   }
   else if( type == 0x0b )
   { // friend list

      GamePacketNew< FFXIVIpcSocialList > listPacket( pPlayer->getId() );
      listPacket.data().type = 0x0B;
      listPacket.data().sequence = count;
      memset( listPacket.data().entries, 0, sizeof( listPacket.data().entries ) );

   }
   else if( type == 0x0e )
   { // player search result
     // TODO: implement player search
     /*CGamePacket * pPE = new CGamePacket(0xCC, 0x3A0, pPlayer->getId(), pPlayer->getId());
     pPE->setInt8At(0x2C, 0x0E);
     pPE->setInt8At(0x2D, count);

     std::set<CPlayer*> tmpSet = m_playerSearchResult;

     std::set<CPlayer*>::iterator it;

     int i = 0x30;
     for(it = tmpSet.begin(); it != tmpSet.end(); it++)
     {
     if((*it)->getId() == pPlayer->getId())
     {
     continue;
     }
     pPE->setInt64At(i, (*it)->getContentId());
     pPE->setInt8At(i+0x16, 0x2);
     pPE->setInt16At(i+0x0A, (*it)->getZone()->getLayoutId());
     pPE->setInt16At(i+0x0C, (*it)->getZone()->getLayoutId());
     pPE->setInt16At(i+0x0E, 0x46);
     pPE->setInt16At(i+0x14, 0x100);

     pPE->setInt16At(i+0x1A, 0x8000);
     pPE->setInt16At(i + 0x20, static_cast<uint8_t>((*it)->getClass()));
     pPE->setInt16At(i+0x22,(*it)->getLevel());
     pPE->setStringAt(i+0x26, (*it)->getName());
     i += 0x48;
     }


     pPlayer->queuePacket(pPE);*/

   }

}

void Core::Network::GameConnection::chatHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                 Core::Entity::PlayerPtr pPlayer )
{

   std::string chatString( pInPacket->getStringAt( 0x3a ) );

   uint32_t sourceId;
   sourceId = pInPacket->getValAt< uint32_t >( 0x24 );

   if( chatString.at( 0 ) == '@' )
   {
      // execute game console command
      g_gameCommandMgr.execCommand( const_cast< char * >( chatString.c_str() ) + 1, pPlayer );
      return;
   }

   ChatType chatType = static_cast<ChatType>( pInPacket->getValAt< uint8_t >( 0x38 ) );

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
void Core::Network::GameConnection::logoutHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                   Core::Entity::PlayerPtr pPlayer )
{
   GamePacketNew< FFXIVIpcLogout > logoutPacket( pPlayer->getId() );
   logoutPacket.data().flags1 = 0x02;
   logoutPacket.data().flags2 = 0x2000;
   queueOutPacket( logoutPacket );
}
