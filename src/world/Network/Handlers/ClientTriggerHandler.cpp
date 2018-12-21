#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacketNew.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Util/Util.h>

#include "Territory/Zone.h"
#include "Territory/ZonePosition.h"
#include "Manager/HousingMgr.h"

#include "Network/GameConnection.h"

#include "Network/PacketWrappers/ExaminePacket.h"
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
#include "ServerMgr.h"
#include "Forwards.h"
#include "Framework.h"
#include <Network/PacketDef/Lobby/ServerLobbyDef.h>

extern Sapphire::Framework g_fw;

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

void examineHandler( Sapphire::Entity::Player& player, uint32_t targetId )
{
  using namespace Sapphire;

  auto pSession = g_fw.get< Sapphire::ServerMgr >()->getSession( targetId );
  if( pSession )
  {
    auto pTarget = pSession->getPlayer();
    if( pTarget )
    {
      if( pTarget->isActingAsGm() || pTarget->getZoneId() != player.getZoneId() )
      {
        player.queuePacket( makeActorControl142( player.getId(), ActorControlType::ExamineError ) );
      }
      else
      {
        player.queuePacket( std::make_shared< ExaminePacket >( player, pTarget ) );
      }
    }
  }
}

void Sapphire::Network::GameConnection::clientTriggerHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto pLog = g_fw.get< Logger >();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcClientTrigger >( inPacket );

  const auto commandId = packet.data().commandId;
  const auto param1 = *reinterpret_cast< const uint64_t* >( &packet.data().param11 );
  const auto param11 = packet.data().param11;
  const auto param12 = packet.data().param12;
  const auto param2 = packet.data().param2;
  const auto param3 = packet.data().param3;

  pLog->debug( "[" + std::to_string( m_pSession->getId() ) + "] Incoming action: " +
               Util::intToHexString( static_cast< uint32_t >( commandId & 0xFFFF ), 4 ) +
               "\nparam1: " + Util::intToHexString( static_cast< uint64_t >( param1 & 0xFFFFFFFFFFFFFFF ), 16 ) +
               "\nparam2: " + Util::intToHexString( static_cast< uint32_t >( param2 & 0xFFFFFFFF ), 8 ) +
               "\nparam3: " + Util::intToHexString( static_cast< uint64_t >( param3 & 0xFFFFFFFFFFFFFFF ), 16 )
  );


  //g_log.Log(LoggingSeverity::debug, "[" + std::to_string(m_pSession->getId()) + "] " + pInPacket->toString());

  switch( commandId )
  {
    case ClientTriggerType::ToggleSheathe:  // Toggle sheathe
    {
      if( param11 == 1 )
        player.setStance( Common::Stance::Active );
      else
      {
        player.setStance( Common::Stance::Passive );
        player.setAutoattack( false );
      }

      player.sendToInRangeSet( makeActorControl142( player.getId(), 0, param11, 1 ) );

      break;
    }
    case ClientTriggerType::ToggleAutoAttack:  // Toggle auto-attack
    {
      if( param11 == 1 )
      {
        player.setAutoattack( true );
        player.setStance( Common::Stance::Active );
      }
      else
        player.setAutoattack( false );

      player.sendToInRangeSet( makeActorControl142( player.getId(), 1, param11, 1 ) );

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
    case ClientTriggerType::Examine:
    {
      uint32_t targetId = param11;
      examineHandler( player, targetId );
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
    case ClientTriggerType::CharaNameReq:
    {
      uint64_t targetContentId = param1;
      // todo: look up player by content id
      /*
        auto packet = makeZonePacket< FFXIVIpcCharaNameReq >( player.getId() );
        packet->data().contentId = targetContentId;

        // lookup the name

        strcpy( packet->data().name, name );

        player.queuePacket( packet );
      */
     break;
    }
    case ClientTriggerType::EmoteReq: // emote
    {
      uint64_t targetId = player.getTargetId();
      uint32_t emoteId = param11;
      bool isSilent = param2 == 1;

      auto pExdData = g_fw.get< Data::ExdDataGenerated >();
      auto emoteData = pExdData->get< Data::Emote >( emoteId );

      if( !emoteData )
        return;

      player.emote( emoteId, targetId, isSilent );

      bool isPersistent = emoteData->emoteMode != 0;

      if( isPersistent )
      {
        player.setStance( Common::Stance::Passive );
        player.setAutoattack( false );
        player.setPersistentEmote( emoteData->emoteMode );
        player.setStatus( Common::ActorStatus::EmoteMode );

        player.sendToInRangeSet( makeActorControl142( player.getId(), ActorControlType::SetStatus,
                                                      static_cast< uint8_t >( Common::ActorStatus::EmoteMode ),
                                                      emoteData->hasCancelEmote ? 1 : 0 ), true );
      }

      if( emoteData->drawsWeapon )
      {
        player.setStance( Common::Stance::Active );
      }

      break;
    }
    case ClientTriggerType::EmoteCancel: // emote
    {
      player.emoteInterrupt();
      break;
    }
    case ClientTriggerType::PersistentEmoteCancel: // cancel persistent emote
    {
      player.setPersistentEmote( 0 );
      player.emoteInterrupt();
      player.setStatus( Common::ActorStatus::Idle );
      auto pSetStatusPacket = makeActorControl142( player.getId(), SetStatus,
                                                   static_cast< uint8_t >( Common::ActorStatus::Idle ) );
      player.sendToInRangeSet( pSetStatusPacket );
      break;
    }
    case ClientTriggerType::PoseChange: // change pose
    case ClientTriggerType::PoseReapply: // reapply pose
    {
      player.setPose( param12 );
      auto pSetStatusPacket = makeActorControl142( player.getId(), SetPose, param11, param12 );
      player.sendToInRangeSet( pSetStatusPacket, true );
      break;
    }
    case ClientTriggerType::PoseCancel: // cancel pose
    {
      player.setPose( param12 );
      auto pSetStatusPacket = makeActorControl142( player.getId(), SetPose, param11, param12 );
      player.sendToInRangeSet( pSetStatusPacket, true );
      break;
    }
    case ClientTriggerType::Return: // return dead / accept raise
    {
      switch( static_cast < ResurrectType >( param1 ) )
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
    case ClientTriggerType::DirectorSync: // Director init finish
    {
      player.getCurrentZone()->onDirectorSync( player );
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
    case ClientTriggerType::AbandonQuest:
    {
      player.removeQuest( static_cast< uint16_t >( param1 ) );
      break;
    }
    case ClientTriggerType::RequestHousingBuildPreset:
    {
      auto zone = player.getCurrentZone();
      auto hZone = std::dynamic_pointer_cast< HousingZone >( zone );
      if (!hZone)
        return;

      player.setActiveLand( param11, hZone->getWardNum() );

      auto pShowBuildPresetUIPacket = makeActorControl142( player.getId(), ShowBuildPresetUI, param11 );
      player.queuePacket( pShowBuildPresetUIPacket );

      break;
    }
    case ClientTriggerType::RequestLandSignFree:
    {
      auto pHousingMgr = g_fw.get< HousingMgr >();

      auto ident = pHousingMgr->clientTriggerParamsToLandIdent( param11, param12 );
      pHousingMgr->sendLandSignFree( player, ident );

      break;
    }
    case ClientTriggerType::RequestLandSignOwned:
    {
      auto pHousingMgr = g_fw.get< HousingMgr >();

      auto ident = pHousingMgr->clientTriggerParamsToLandIdent( param11, param12, false );
      pHousingMgr->sendLandSignOwned( player, ident );

      break;
    }
    case ClientTriggerType::RequestWardLandInfo:
    {
      auto pHousingMgr = g_fw.get< HousingMgr >();
      if( !pHousingMgr )
        break;

      pHousingMgr->sendWardLandInfo( player, param12, param11 );

      break;
    }
    case ClientTriggerType::RequestLandRelinquish:
    {
      auto plot = static_cast< uint8_t >( param12 & 0xFF );
      auto pHousingMgr = g_fw.get< HousingMgr >();
      pHousingMgr->relinquishLand( player, plot );

      break;
    }
    case ClientTriggerType::RequestEstateRename:
    {
      auto pHousingMgr = g_fw.get< HousingMgr >();
      if( !pHousingMgr )
        break;

      auto ident = pHousingMgr->clientTriggerParamsToLandIdent( param11, param12 );
      pHousingMgr->requestEstateRename( player, ident );

      break;
    }
    case ClientTriggerType::RequestEstateEditGreeting:
    {
      auto pHousingMgr = g_fw.get< HousingMgr >();
      if( !pHousingMgr )
        break;

      auto ident = pHousingMgr->clientTriggerParamsToLandIdent( param11, param12 );
      pHousingMgr->requestEstateEditGreeting( player, ident );

      break;
    }
    case ClientTriggerType::RequestEstateEditGuestAccessSettings:
    {
      auto pHousingMgr = g_fw.get< HousingMgr >();
      if( !pHousingMgr )
        break;

      auto ident = pHousingMgr->clientTriggerParamsToLandIdent( param11, param12 );
      pHousingMgr->requestEstateEditGuestAccess( player, ident );

      break;
    }
    case ClientTriggerType::RequestHousingItemUI:
    {
      // close ui
      if( param11 == 1 )
        break;

      // param12 is 0 when inside a house

      uint8_t ward = ( param12 >> 16 ) & 0xFF;
      uint8_t plot = ( param12 & 0xFF );
      auto pShowHousingItemUIPacket = makeActorControl142( player.getId(), ShowHousingItemUI, 0, plot );

      player.queuePacket( pShowHousingItemUIPacket );

      //TODO: show item housing container

      break;
    }
    case ClientTriggerType::RequestEstateGreeting:
    {
      auto housingMgr = g_fw.get< HousingMgr >();
      if( !housingMgr )
        break;

      auto ident = housingMgr->clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr->sendEstateGreeting( player, ident );

      break;
    }
    case ClientTriggerType::RequestLandInventory:
    {
      uint8_t plot = ( param12 & 0xFF );


      auto housingMgr = g_fw.get< HousingMgr >();
      if( !housingMgr )
        break;

      uint16_t inventoryType = Common::InventoryType::HousingOutdoorPlacedItems;
      if( param2 == 1 )
        inventoryType = Common::InventoryType::HousingOutdoorStoreroom;

      housingMgr->sendHousingInventory( player, inventoryType, plot );

      break;
    }
    case ClientTriggerType::RequestEstateInventory:
    {
      // only sent if param1 is 1, because the client sends this with 0 when you open the ui for whatever reason
      if( param1 != 1 )
        return;

      auto housingMgr = g_fw.get< HousingMgr >();
      if( !housingMgr )
        break;

      // housingMgr->sendHousingInventory( player, Common::InventoryType::HousingInd, 255 );

      break;
    }

    default:
    {
      pLog->debug( "[" + std::to_string( m_pSession->getId() ) + "] Unhandled action: " +
                   Util::intToHexString( static_cast< uint32_t >( commandId & 0xFFFF ), 4 ) );
      break;
    }
  }
}
