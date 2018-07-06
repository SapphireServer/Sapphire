#include <boost/format.hpp>

#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacketNew.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>

#include "Zone/Zone.h"
#include "Zone/ZonePosition.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/InitUIPacket.h"
#include "Network/PacketWrappers/PingPacket.h"
#include "Network/PacketWrappers/MoveActorPacket.h"
#include "Network/PacketWrappers/ChatPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"

#include "DebugCommand/DebugCommandHandler.h"

#include "Event/EventHelper.h"

#include "Action/Action.h"
#include "Action/ActionTeleport.h"

#include "Session.h"
#include "ServerZone.h"
#include "Forwards.h"
#include "Framework.h"
#include <Network/PacketDef/Lobby/ServerLobbyDef.h>

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;
using namespace Core::Network::ActorControl;

void Core::Network::GameConnection::clientTriggerHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
   Packets::FFXIVARR_PACKET_RAW copy = inPacket;

   auto pLog = g_fw.get< Logger >();
   uint16_t commandId = *reinterpret_cast< uint16_t* >( &copy.data[0x10] );
   uint64_t param1 = *reinterpret_cast< uint64_t* >( &copy.data[0x14] );
   uint32_t param11 = *reinterpret_cast< uint32_t* >( &copy.data[0x14] );
   uint32_t param12 = *reinterpret_cast< uint32_t* >( &copy.data[0x18] );
   uint32_t param2 = *reinterpret_cast< uint32_t* >( &copy.data[0x1C] );
   uint64_t param3 = *reinterpret_cast< uint64_t* >( &copy.data[0x28] );

   pLog->debug( "[" + std::to_string( m_pSession->getId() ) + "] Incoming action: " +
              boost::str( boost::format( "%|04X|" ) % ( uint32_t ) ( commandId & 0xFFFF ) ) +
              "\nparam1: " + boost::str( boost::format( "%|016X|" ) % ( uint64_t ) ( param1 & 0xFFFFFFFFFFFFFFF ) ) +
              "\nparam2: " + boost::str( boost::format( "%|08X|" ) % ( uint32_t ) ( param2 & 0xFFFFFFFF ) ) +
              "\nparam3: " + boost::str( boost::format( "%|016X|" ) % ( uint64_t ) ( param3 & 0xFFFFFFFFFFFFFFF ) )
   );


   //g_log.Log(LoggingSeverity::debug, "[" + std::to_string(m_pSession->getId()) + "] " + pInPacket->toString());

   switch( commandId )
   {
       case ClientTriggerType::ToggleSheathe:  // Toggle sheathe
       {
          if ( param11 == 1 )
              player.setStance( Entity::Chara::Stance::Active );
          else
          {
              player.setStance( Entity::Chara::Stance::Passive );
              player.setAutoattack( false );
          }

          player.sendToInRangeSet( boost::make_shared< ActorControlPacket142 >( player.getId(), 0, param11, 1 ) );

          break;
       }
       case ClientTriggerType::ToggleAutoAttack:  // Toggle auto-attack
       {
          if ( param11 == 1 )
          {
              player.setAutoattack( true );
              player.setStance( Entity::Chara::Stance::Active );
          }
          else
              player.setAutoattack( false );

          player.sendToInRangeSet( boost::make_shared< ActorControlPacket142 >( player.getId(), 1, param11, 1 ) );

          break;
       }
       case ClientTriggerType::ChangeTarget: // Change target
       {

          uint64_t targetId = param1;
          player.changeTarget( targetId );
          break;
       }
       case ClientTriggerType::DismountReq:
       {
          player.dismount();
          break;
       }
       case ClientTriggerType::RemoveStatusEffect: // Remove status (clicking it off)
       {
          // todo: check if status can be removed by client from exd
          player.removeSingleStatusEffectById( static_cast< uint32_t >( param1 ) );
          break;
       }
       case ClientTriggerType::CastCancel: // Cancel cast
       {
          if( player.getCurrentAction() )
              player.getCurrentAction()->setInterrupted();
          break;
       }
       case ClientTriggerType::MarkPlayer: // Mark player
       {
          break;
       }
       case ClientTriggerType::SetTitleReq: // Set player title
       {
          player.setTitle( static_cast< uint16_t >( param1 ) );
          break;
       }
       case ClientTriggerType::TitleList: // Get title list
       {
          player.sendTitleList();
          break;
       }
       case ClientTriggerType::UpdatedSeenHowTos: // Update howtos seen
       {
          uint32_t howToId = param11;
          player.updateHowtosSeen( howToId );
          break;
       }
       case ClientTriggerType::EmoteReq: // emote
       {
          uint64_t targetId = player.getTargetId();
          uint32_t emoteId = param11;

          player.emote( emoteId, targetId );
          break;
       }
       case ClientTriggerType::PersistantEmoteCancel: // cancel persistant emote
       {
          break;
       }
       case ClientTriggerType::PoseChange: // change pose
       {
          break;
       }
       case ClientTriggerType::PoseReapply: // reapply pose
       {
          break;
       }
       case ClientTriggerType::PoseCancel: // cancel pose
       {
          break;
       }
       case ClientTriggerType::Return: // return dead / accept raise
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
       case ClientTriggerType::FinishZoning: // Finish zoning
       {
          player.finishZoning();
          break;
       }

       case ClientTriggerType::Teleport: // Teleport
       {

          player.teleportQuery( param11 );
          break;
       }
       case ClientTriggerType::DyeItem: // Dye item
       {
          break;
       }
       case ClientTriggerType::DirectorInitFinish: // Director init finish
       {
          player.getCurrentZone()->onInitDirector( player );
          break;
       }
       case ClientTriggerType::SomeDirectorEvent: // Director init finish
       {
          player.getCurrentZone()->onSomeDirectorEvent( player );
          break;
       }
       case ClientTriggerType::EnterTerritoryEventFinished:// this may still be something else. I think i have seen it elsewhere
       {
          player.setOnEnterEventDone( true );
          break;
       }
       case ClientTriggerType::RequestInstanceLeave:
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
