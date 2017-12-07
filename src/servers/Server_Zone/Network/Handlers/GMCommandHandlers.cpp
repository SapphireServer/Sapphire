#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Network/CommonNetwork.h>
#include <src/servers/Server_Common/Network/GamePacketNew.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Network/PacketContainer.h>

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

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::DebugCommandHandler g_gameCommandMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

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
   Exp = 0x0068,
   Inv = 0x006A,

   Orchestrion = 0x0074,

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
   Aetheryte = 0x015E,
   Teri = 0x0258,
   Kick = 0x025C,
   TeriInfo = 0x025D,
   Jump = 0x025E,
   JumpNpc = 0x025F,
};

void Core::Network::GameConnection::gm1Handler( const Packets::GamePacket& inPacket, Entity::PlayerPtr pPlayer )
{
   if( pPlayer->getGmRank() <= 0 )
      return;

   uint32_t commandId = inPacket.getValAt< uint32_t >( 0x20 );
   uint32_t param1 = inPacket.getValAt< uint32_t >( 0x24 );
   uint32_t param2 = inPacket.getValAt< uint32_t >( 0x28 );
   uint32_t param3 = inPacket.getValAt< uint32_t >( 0x38 );

   g_log.debug( pPlayer->getName() + " used GM1 commandId: " + std::to_string( commandId ) +
      ", params: " + std::to_string( param1 ) + ", " +
      std::to_string( param2 ) + ", " + std::to_string( param3 ) );

   Core::Entity::ActorPtr targetActor;


   if( pPlayer->getId() == param3 )
   {
      targetActor = pPlayer;
   }
   else
   {
      auto inRange = pPlayer->getInRangeActors();
      for( auto actor : inRange )
      {
         if( actor->getId() == param3 )
            targetActor = actor;
      }
   }

   if( !targetActor )
      return;
   auto targetPlayer = targetActor->getAsPlayer();

   switch( commandId )
   {
   case GmCommand::Lv:
   {
      targetPlayer->setLevel( param1 );
      pPlayer->sendNotice( "Level for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Race:
   {
      targetPlayer->setLookAt( CharaLook::Race, param1 );
      pPlayer->sendNotice( "Race for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      targetPlayer->spawn( targetPlayer );
      auto inRange = targetPlayer->getInRangeActors();
      for ( auto actor : inRange )
      {
         targetPlayer->despawn( actor->getAsPlayer() );
         targetPlayer->spawn( actor->getAsPlayer() );
      }
      break;
   }
   case GmCommand::Tribe:
   {
      targetPlayer->setLookAt( CharaLook::Tribe, param1 );
      pPlayer->sendNotice( "Tribe for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      targetPlayer->spawn( targetPlayer );
      auto inRange = targetPlayer->getInRangeActors();
      for ( auto actor : inRange )
      {
         targetPlayer->despawn( actor->getAsPlayer() );
         targetPlayer->spawn( actor->getAsPlayer() );
      }
      break;
   }
   case GmCommand::Sex:
   {
      targetPlayer->setLookAt( CharaLook::Gender, param1 );
      pPlayer->sendNotice( "Sex for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      targetPlayer->spawn( targetPlayer );
      auto inRange = targetActor->getInRangeActors();
      for ( auto actor : inRange )
      {
         targetPlayer->despawn( actor->getAsPlayer() );
         targetPlayer->spawn( actor->getAsPlayer() );
      }
      break;
   }
   case GmCommand::Time:
   {
      pPlayer->setEorzeaTimeOffset( param2 );
      pPlayer->sendNotice( "Eorzea time offset: " + std::to_string( param2 ) );
      break;
   }
   case GmCommand::Weather:
   {
      targetPlayer->getCurrentZone()->setWeatherOverride( param1 );
      pPlayer->sendNotice( "Weather in Zone \"" + targetPlayer->getCurrentZone()->getName() + "\" of " +
         targetPlayer->getName() + " set in range." );
      break;
   }
   case GmCommand::Call:
   {
      if ( targetPlayer->getZoneId() != pPlayer->getZoneId() )
         targetPlayer->setZone( pPlayer->getZoneId() );

      targetPlayer->changePosition( pPlayer->getPos().x, pPlayer->getPos().y, pPlayer->getPos().z,
         pPlayer->getRotation() );
      pPlayer->sendNotice( "Calling " + targetPlayer->getName() );
      break;
   }
   case GmCommand::Inspect:
   {
      pPlayer->sendNotice( "Name: " + targetPlayer->getName() +
         "\nGil: " + std::to_string( targetPlayer->getCurrency( 1 ) ) +
         "\nZone: " + targetPlayer->getCurrentZone()->getName() +
         "(" + std::to_string( targetPlayer->getZoneId() ) + ")" +
         "\nClass: " + std::to_string( static_cast< uint8_t >( targetPlayer->getClass() ) ) +
         "\nLevel: " + std::to_string( targetPlayer->getLevel() ) +
         "\nExp: " + std::to_string( targetPlayer->getExp() ) +
         "\nSearchMessage: " + targetPlayer->getSearchMessage() +
         "\nPlayTime: " + std::to_string( targetPlayer->getPlayTime() ) );
      break;
   }
   case GmCommand::Speed:
   {
      targetPlayer->queuePacket( ActorControlPacket143( pPlayer->getId(), Flee, param1 ) );
      pPlayer->sendNotice( "Speed for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Kill:
   {
      targetActor->takeDamage( 9999999 );
      pPlayer->sendNotice( "Killed " + std::to_string( targetActor->getId() ) );
      break;
   }
   case GmCommand::Icon:
   {
      targetPlayer->setOnlineStatusMask( param1 );

      ZoneChannelPacket< FFXIVIpcSetOnlineStatus > statusPacket( targetPlayer->getId() );
      statusPacket.data().onlineStatusFlags = param1;
      queueOutPacket( statusPacket );

      ZoneChannelPacket< FFXIVIpcSetSearchInfo > searchInfoPacket( targetPlayer->getId() );
      searchInfoPacket.data().onlineStatusFlags = param1;
      searchInfoPacket.data().selectRegion = targetPlayer->getSearchSelectRegion();
      strcpy( searchInfoPacket.data().searchMessage, targetPlayer->getSearchMessage() );
      targetPlayer->queuePacket( searchInfoPacket );

      targetPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), SetStatusIcon,
         static_cast< uint8_t >( pPlayer->getOnlineStatus() ) ),
         true );
      pPlayer->sendNotice( "Icon for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Hp:
   {
      targetPlayer->setHp( param1 );
      pPlayer->sendNotice( "Hp for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Mp:
   {
      targetPlayer->setMp( param1 );
      pPlayer->sendNotice( "Mp for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Gp:
   {
      targetPlayer->setHp( param1 );
      pPlayer->sendNotice( "Gp for " + targetPlayer->getName() + " was set to " + std::to_string( param1 ) );
      break;
   }
   case GmCommand::Exp:
   {
      targetPlayer->gainExp( param1 );
      pPlayer->sendNotice( std::to_string( param1 ) + " Exp was added to " + targetPlayer->getName() );
      break;
   }
   case GmCommand::Inv:
   {
      if ( targetActor->getInvincibilityType() == Common::InvincibilityType::InvincibilityRefill )
         targetActor->setInvincibilityType( Common::InvincibilityType::InvincibilityNone );
      else
         targetActor->setInvincibilityType( Common::InvincibilityType::InvincibilityRefill );

      pPlayer->sendNotice( "Invincibility for " + targetPlayer->getName() +
         " was switched." );
      break;
   }
   case GmCommand::Orchestrion:
   {
      if ( param1 == 1 )
      {
         if ( param2 == 0 )
         {
            for ( uint8_t i = 0; i < 255; i++ )
               targetActor->getAsPlayer()->learnSong( i, 0 );

            pPlayer->sendNotice( "All Songs for " + targetPlayer->getName() +
               " were turned on." );
         }
         else
         {
            targetActor->getAsPlayer()->learnSong( param2, 0 );
            pPlayer->sendNotice( "Song " + std::to_string( param2 ) + " for " + targetPlayer->getName() +
               " was turned on." );
         }
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

      if( !targetPlayer->addItem( -1, param1, param2 ) )
         pPlayer->sendUrgent( "Item " + std::to_string( param1 ) + " not found..." );
      break;
   }
   case GmCommand::Gil:
   {
      targetPlayer->addCurrency( 1, param1 );
      pPlayer->sendNotice( "Added  " + std::to_string( param1 ) + " Gil for " + targetPlayer->getName() );
      break;
   }
   case GmCommand::Collect:
   {
      uint32_t gil = targetPlayer->getCurrency( 1 );

      if ( gil < param1 )
      {
         pPlayer->sendUrgent( "Player does not have enough Gil(" + std::to_string( gil ) + ")" );
      }
      else
      {
         targetPlayer->removeCurrency( 1, param1 );
         pPlayer->sendNotice( "Removed " + std::to_string( param1 ) +
            " Gil from " + targetPlayer->getName() +
            "(" + std::to_string( gil ) + " before)" );
      }
      break;
   }
   case GmCommand::QuestAccept:
   {
      targetPlayer->updateQuest( param1, 1 );
      break;
   }
   case GmCommand::QuestCancel:
   {
      targetPlayer->removeQuest( param1 );
      break;
   }
   case GmCommand::QuestComplete:
   {
      targetPlayer->finishQuest( param1 );
      break;
   }
   case GmCommand::QuestIncomplete:
   {
      targetPlayer->unfinishQuest( param1 );
      break;
   }
   case GmCommand::QuestSequence:
   {
      targetPlayer->updateQuest( param1, param2 );
      break;
   }
   case GmCommand::GC:
   {
      targetPlayer->setGc( param1 );
      pPlayer->sendNotice( "GC for " + targetPlayer->getName() +
         " was set to " + std::to_string( targetPlayer->getGc() ) );
      break;
   }
   case GmCommand::GCRank:
   {
      targetPlayer->setGcRankAt( targetPlayer->getGc() - 1, param1 );
      pPlayer->sendNotice( "GC Rank for  " + targetPlayer->getName() +
         " for GC " + std::to_string( targetPlayer->getGc() ) +
         " was set to " + std::to_string( targetPlayer->getGcRankArray()[targetPlayer->getGc() - 1] ) );
      break;
   }
   case GmCommand::Aetheryte:
   {
      if ( param1 == 0 )
      {
         if ( param2 == 0 )
         {
            for ( uint8_t i = 0; i < 255; i++ )
               targetActor->getAsPlayer()->registerAetheryte( i );

            pPlayer->sendNotice( "All Aetherytes for " + targetPlayer->getName() +
               " were turned on." );
         }
         else
         {
            targetActor->getAsPlayer()->registerAetheryte( param2 );
            pPlayer->sendNotice( "Aetheryte " + std::to_string( param2 ) + " for " + targetPlayer->getName() +
               " was turned on." );
         }
      }

      break;
   }
   case GmCommand::Teri:
   {
      auto zoneInfo = g_zoneMgr.getZone( param1 );
      if ( !zoneInfo )
      {
         pPlayer->sendUrgent( "Invalid zone " + std::to_string( param1 ) );
      }
      else
      {
         targetPlayer->setPosition( targetPlayer->getPos() );
         targetPlayer->performZoning( param1, targetPlayer->getPos(), 0 );
         pPlayer->sendNotice( targetPlayer->getName() + " was warped to zone " + std::to_string( param1 ) + " (" + zoneInfo->getName( ) + ")" );
      }
      break;
   }
   case GmCommand::TeriInfo:
   {
      pPlayer->sendNotice( "ZoneId: " + std::to_string( pPlayer->getZoneId() ) + "\nName: " +
         pPlayer->getCurrentZone()->getName() + "\nInternalName: " +
         pPlayer->getCurrentZone()->getInternalName() + "\nPopCount: " +
         std::to_string( pPlayer->getCurrentZone()->getPopCount() ) +
         "\nCurrentWeather:" + std::to_string( pPlayer->getCurrentZone()->getCurrentWeather() ) +
         "\nNextWeather:" + std::to_string( pPlayer->getCurrentZone()->getNextWeather() ) );
      break;
   }
   case GmCommand::Jump:
   {

      auto inRange = pPlayer->getInRangeActors();
      for( auto actor : inRange )
      {
         pPlayer->changePosition( targetActor->getPos().x, targetActor->getPos().y, targetActor->getPos().z,
            targetActor->getRotation() );
      }
      pPlayer->sendNotice( "Jumping to " + targetPlayer->getName() + " in range." );
      break;
   }
  
   default:
      pPlayer->sendUrgent( "GM1 Command not implemented: " + std::to_string( commandId ) );
      break;
   }

}

void Core::Network::GameConnection::gm2Handler( const Packets::GamePacket& inPacket, Entity::PlayerPtr pPlayer )
{
   if( pPlayer->getGmRank() <= 0 )
      return;

   uint32_t commandId = inPacket.getValAt< uint32_t >( 0x20 );
   std::string param1 = inPacket.getStringAt( 0x34 );

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
         pPlayer->sendUrgent( "Player " + param1 + " not found on this server." );
         return;
      }
   }

   if( !targetActor )
      return;

   auto targetPlayer = targetActor->getAsPlayer();

   switch( commandId )
   {
   case GmCommand::Raise:
   {
      targetPlayer->resetHp();
      targetPlayer->resetMp();
      targetPlayer->setStatus( Entity::Actor::ActorStatus::Idle );

      targetPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01, 0x01, 0, 113 ), true );
      targetPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), SetStatus,
         static_cast< uint8_t >( Entity::Actor::ActorStatus::Idle ) ), true );
      pPlayer->sendNotice( "Raised  " + targetPlayer->getName() );
      break;
   }
   case GmCommand::Jump:
   {
      if( targetPlayer->getZoneId() != pPlayer->getZoneId() )
      {
         pPlayer->setZone( targetPlayer->getZoneId() );
      }
      pPlayer->changePosition( targetActor->getPos().x, targetActor->getPos().y, targetActor->getPos().z,
         targetActor->getRotation() );
      pPlayer->sendNotice( "Jumping to " + targetPlayer->getName() );
      break;
   }
   default:
      pPlayer->sendUrgent( "GM2 Command not implemented: " + std::to_string( commandId ) );
      break;
   }

}
