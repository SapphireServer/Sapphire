#include <boost/format.hpp>

#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacketNew.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>

#include "Zone/Zone.h"
#include "Zone/ZonePosition.h"

#include "Network/GameConnection.h"
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

enum ClientTrigger
{
   ToggleSeathe = 0x01,
   ToggleAutoAttack = 0x02,
   ChangeTarget = 0x03,

   Dismount = 0x65,

   RemoveStatusEffect = 0x68,
   CastCancel = 0x69,

   Return = 0xC8, // return dead / accept raise
   FinishZoning = 0xC9,
   Teleport = 0xCA,

   MarkPlayer = 0x12D, // Mark player, visible to party only
   SetTitle = 0x12E,
   TitleList = 0x12F,

   UpdatedSeenHowTos = 0x133,
   AllotAttribute = 0x135,

   ClearWaymarks = 0x13A,

   HuntingLogDetails = 0x194,

   Timers = 0x1AB,

   DyeItem = 0x1B5,

   RequestChocoboInventory = 0x1C4,

   Emote = 0x1F4,
   PersistantEmoteCancel = 0x1F7,
   PoseChange = 0x1F9,
   PoseReapply = 0x1FA,
   PoseCancel = 0x1FB,

   AchievementCrit = 0x202,
   AchievementComp = 0x203,
   AchievementCatChat = 0x206,


   DirectorInitFinish = 0x321,

   SomeDirectorEvent = 0x328, // unsure what exactly triggers it, starts director when returning to instance though

   EnterTerritoryEventFinished = 0x330,
   RequestInstanceLeave = 0x333, // df menu button

   AchievementCritReq = 0x3E8,
   AchievementList = 0x3E9,

   CompanionAction = 0x6A4,
   CompanionSetBarding = 0x6A5,
   CompanionActionUnlock = 0x6A6,

   OpenPerformInstrumentUI = 0x71C,

   StartReplay = 0x7BC,
   EndReplay = 0x7BD, // request for restoring the original player state (actor, buff, gauge, etc..)

   OpenDuelUI = 0x898, // Open a duel ui
   DuelRequestResult = 0x899, // either accept/reject

};

void Core::Network::GameConnection::actionHandler( const Packets::GamePacket& inPacket,
                                                   Entity::Player& player )
{
   auto pLog = g_fw.get< Logger >();
   uint16_t commandId = inPacket.getValAt< uint16_t >( 0x20 );
   uint64_t param1 = inPacket.getValAt< uint64_t >( 0x24 );
   uint32_t param11 = inPacket.getValAt< uint32_t >( 0x24 );
   uint32_t param12 = inPacket.getValAt< uint32_t >( 0x28 );
   uint32_t param2 = inPacket.getValAt< uint32_t >( 0x2C );
   uint64_t param3 = inPacket.getValAt< uint64_t >( 0x38 );

   pLog->debug( "[" + std::to_string( m_pSession->getId() ) + "] Incoming action: " +
              boost::str( boost::format( "%|04X|" ) % ( uint32_t ) ( commandId & 0xFFFF ) ) +
              "\nparam1: " + boost::str( boost::format( "%|016X|" ) % ( uint64_t ) ( param1 & 0xFFFFFFFFFFFFFFF ) ) +
              "\nparam2: " + boost::str( boost::format( "%|08X|" ) % ( uint32_t ) ( param2 & 0xFFFFFFFF ) ) +
              "\nparam3: " + boost::str( boost::format( "%|016X|" ) % ( uint64_t ) ( param3 & 0xFFFFFFFFFFFFFFF ) )
   );


   //g_log.Log(LoggingSeverity::debug, "[" + std::to_string(m_pSession->getId()) + "] " + pInPacket->toString());

   switch( commandId )
   {
       case ClientTrigger::ToggleSeathe:  // Toggle sheathe
       {
          if ( param11 == 1 )
              player.setStance( Entity::Chara::Stance::Active );
          else
          {
              player.setStance( Entity::Chara::Stance::Passive );
              player.setAutoattack( false );
          }

          player.sendToInRangeSet( ActorControlPacket142( player.getId(), 0, param11, 1 ) );

          break;
       }
       case ClientTrigger::ToggleAutoAttack:  // Toggle auto-attack
       {
          if ( param11 == 1 )
          {
              player.setAutoattack( true );
              player.setStance( Entity::Chara::Stance::Active );
          }
          else
              player.setAutoattack( false );

          player.sendToInRangeSet( ActorControlPacket142( player.getId(), 1, param11, 1 ) );

          break;
       }
       case ClientTrigger::ChangeTarget: // Change target
       {

          uint64_t targetId = inPacket.getValAt< uint64_t >( 0x24 );
          player.changeTarget( targetId );
          break;
       }
       case ClientTrigger::Dismount:
       {
          player.dismount();
          break;
       }
       case ClientTrigger::RemoveStatusEffect: // Remove status (clicking it off)
       {
          // todo: check if status can be removed by client from exd
          player.removeSingleStatusEffectById( static_cast< uint32_t >( param1 ) );
          break;
       }
       case ClientTrigger::CastCancel: // Cancel cast
       {
          if( player.getCurrentAction() )
              player.getCurrentAction()->setInterrupted();
          break;
       }
       case ClientTrigger::MarkPlayer: // Mark player
       {
          break;
       }
       case ClientTrigger::SetTitle: // Set player title
       {
          player.setTitle( static_cast< uint16_t >( param1 ) );
          break;
       }
       case ClientTrigger::TitleList: // Get title list
       {
          player.sendTitleList();
          break;
       }
       case ClientTrigger::UpdatedSeenHowTos: // Update howtos seen
       {
          uint32_t howToId = param11;
          player.updateHowtosSeen( howToId );
          break;
       }
       case ClientTrigger::Emote: // emote
       {
          uint64_t targetId = player.getTargetId();
          uint32_t emoteId = inPacket.getValAt< uint32_t >( 0x24 );

          player.emote( emoteId, targetId );
          break;
       }
       case ClientTrigger::PersistantEmoteCancel: // cancel persistant emote
       {
          break;
       }
       case ClientTrigger::PoseChange: // change pose
       {
          break;
       }
       case ClientTrigger::PoseReapply: // reapply pose
       {
          break;
       }
       case ClientTrigger::PoseCancel: // cancel pose
       {
          break;
       }
       case ClientTrigger::Return: // return dead / accept raise
       {
          switch ( static_cast < ResurrectType >( param1 ) )
          {
             case ResurrectType::RaiseSpell:
                // todo: handle raise case (set position to raiser, apply weakness status, set hp/mp/tp as well as packet)
                player.returnToHomepoint();
                break;
             case ResurrectType::Return:
                player.returnToHomepoint();
                break;
             default:
                break;
          }

       }
       case ClientTrigger::FinishZoning: // Finish zoning
       {
          player.finishZoning();
          break;
       }

       case ClientTrigger::Teleport: // Teleport
       {

          player.teleportQuery( param11 );
          break;
       }
       case ClientTrigger::DyeItem: // Dye item
       {
          break;
       }
       case ClientTrigger::DirectorInitFinish: // Director init finish
       {
          player.getCurrentZone()->onInitDirector( player );
          break;
       }
       case ClientTrigger::SomeDirectorEvent: // Director init finish
       {
          player.getCurrentZone()->onSomeDirectorEvent( player );
          break;
       }
       case ClientTrigger::EnterTerritoryEventFinished:// this may still be something else. I think i have seen it elsewhere
       {
          player.setOnEnterEventDone( true );
          break;
       }
       case ClientTrigger::RequestInstanceLeave:
       {
          // todo: apply cf penalty if applicable, make sure player isnt in combat
          player.exitInstance();
          break;
       }


       default:
       {
          pLog->debug( "[" + std::to_string( m_pSession->getId() ) + "] Unhandled action: " +
             boost::str( boost::format( "%|04X|" ) % (uint32_t) ( commandId & 0xFFFF ) ) );
          break;
       }
   }
}
