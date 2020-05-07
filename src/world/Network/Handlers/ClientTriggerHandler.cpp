#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Util/Util.h>

#include "Territory/Territory.h"
#include "Territory/ZonePosition.h"
#include "Manager/HousingMgr.h"

#include "Network/GameConnection.h"

#include "Network/PacketWrappers/ExaminePacket.h"
#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/PingPacket.h"
#include "Network/PacketWrappers/MoveActorPacket.h"
#include "Network/PacketWrappers/ChatPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

#include "Manager/DebugCommandMgr.h"
#include "Manager/EventMgr.h"

#include "Action/Action.h"


#include "Session.h"
#include "ServerMgr.h"
#include "Forwards.h"
#include <Service.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

void examineHandler( Sapphire::Entity::Player& player, uint32_t targetId )
{
  using namespace Sapphire;

  auto& serverMgr = Common::Service< World::ServerMgr >::ref();
  auto pSession = serverMgr.getSession( targetId );
  if( pSession )
  {
    auto pTarget = pSession->getPlayer();
    if( pTarget )
    {
      if( pTarget->isActingAsGm() || pTarget->getZoneId() != player.getZoneId() )
      {
        player.queuePacket( makeActorControl( player.getId(), ActorControlType::ExamineError ) );
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

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcClientTrigger >( inPacket );

  const auto commandId = packet.data().commandId;
  const auto param1 = *reinterpret_cast< const uint64_t* >( &packet.data().param11 );
  const auto param11 = packet.data().param11;
  const auto param12 = packet.data().param12;
  const auto param2 = packet.data().param2;
  const auto param3 = packet.data().param3;
  const auto param4 = packet.data().param4;
  const auto param5 = packet.data().param5;

  Logger::debug( "[{0}] Incoming action: {1:X} ( p1:{2:X} p2:{3:X} p3:{4:X} )",
                 m_pSession->getId(), commandId, param1, param2, param3 );

  //Logger::Log(LoggingSeverity::debug, "[" + std::to_string(m_pSession->getId()) + "] " + pInPacket->toString());

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

      player.sendToInRangeSet( makeActorControl( player.getId(), 0, param11, 1 ) );

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

      player.sendToInRangeSet( makeActorControl( player.getId(), 1, param11, 1 ) );

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
    case ClientTriggerType::SpawnCompanionReq:
    {
      player.spawnCompanion( static_cast< uint16_t >( param1 ) );
      break;
    }
    case ClientTriggerType::DespawnCompanionReq:
    {
      player.spawnCompanion( 0 );
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
        player.getCurrentAction()->setInterrupted( Common::ActionInterruptType::RegularInterrupt );
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

      auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
      auto emoteData = exdData.get< Data::Emote >( emoteId );

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

        player.sendToInRangeSet( makeActorControl( player.getId(), ActorControlType::SetStatus,
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
      auto pSetStatusPacket = makeActorControl( player.getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );
      player.sendToInRangeSet( pSetStatusPacket );
      break;
    }
    case ClientTriggerType::PoseChange: // change pose
    case ClientTriggerType::PoseReapply: // reapply pose
    {
      player.setPose( static_cast< uint8_t >( param12 ) );
      auto pSetStatusPacket = makeActorControl( player.getId(), SetPose, param11, param12 );
      player.sendToInRangeSet( pSetStatusPacket, true );
      break;
    }
    case ClientTriggerType::PoseCancel: // cancel pose
    {
      player.setPose( static_cast< uint8_t >( param12 ) );
      auto pSetStatusPacket = makeActorControl( player.getId(), SetPose, param11, param12 );
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

      player.teleportQuery( static_cast< uint16_t >( param11 ) );
      break;
    }
    case ClientTriggerType::DyeItem: // Dye item
    {
      // param11 = item to dye container
      // param12 = item to dye slot
      // param2 = dye bag container
      // param4 = dye bag slot
      player.setDyeingInfo( param11, param12, param2, param4 );
      break;
    }
    case ClientTriggerType::DirectorInitFinish: // Director init finish
    {
      player.getCurrentTerritory()->onInitDirector( player );
      break;
    }
    case ClientTriggerType::DirectorSync: // Director init finish
    {
      player.getCurrentTerritory()->onDirectorSync( player );
      break;
    }
    case ClientTriggerType::EnterTerritoryEventFinished:// this may still be something else. I think i have seen it elsewhere
    {
      player.setOnEnterEventDone( true );
      break;
    }
    case ClientTriggerType::RequestInstanceLeave:
    {
      // todo: apply cf penalty if applicable, make sure player isn't in combat
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
      auto zone = player.getCurrentTerritory();
      auto hZone = std::dynamic_pointer_cast< HousingZone >( zone );
      if (!hZone)
        return;

      player.setActiveLand( static_cast< uint8_t >( param11 ), hZone->getWardNum() );

      auto pShowBuildPresetUIPacket = makeActorControl( player.getId(), ShowBuildPresetUI, param11 );
      player.queuePacket( pShowBuildPresetUIPacket );

      break;
    }
    case ClientTriggerType::RequestLandSignFree:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.sendLandSignFree( player, ident );

      break;
    }
    case ClientTriggerType::RequestLandSignOwned:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12, false );
      housingMgr.sendLandSignOwned( player, ident );

      break;
    }
    case ClientTriggerType::RequestWardLandInfo:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      housingMgr.sendWardLandInfo( player, static_cast< uint8_t >( param12 ), static_cast< uint8_t >( param11 ) );

      break;
    }
    case ClientTriggerType::RequestLandRelinquish:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto plot = static_cast< uint8_t >( param12 & 0xFF );
      housingMgr.relinquishLand( player, plot );

      break;
    }
    case ClientTriggerType::RequestEstateRename:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.requestEstateRename( player, ident );

      break;
    }
    case ClientTriggerType::RequestEstateEditGreeting:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.requestEstateEditGreeting( player, ident );

      break;
    }
    case ClientTriggerType::RequestEstateEditGuestAccessSettings:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.requestEstateEditGuestAccess( player, ident );

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
      auto pShowHousingItemUIPacket = makeActorControl( player.getId(), ShowHousingItemUI, 0, plot );

      player.queuePacket( pShowHousingItemUIPacket );

      //TODO: show item housing container

      break;
    }
    case ClientTriggerType::RequestEstateGreeting:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.sendEstateGreeting( player, ident );

      break;
    }
    case ClientTriggerType::RequestLandInventory:
    {
      uint8_t plot = ( param12 & 0xFF );

      auto& housingMgr = Common::Service< HousingMgr >::ref();

      uint16_t inventoryType = Common::InventoryType::HousingExteriorPlacedItems;
      if( param2 == 1 )
        inventoryType = Common::InventoryType::HousingExteriorStoreroom;

      housingMgr.sendEstateInventory( player, inventoryType, plot );

      break;
    }
    case ClientTriggerType::RequestEstateInventory:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      // param1 = 1 - storeroom
      // param1 = 0 - placed items

      if( param1 == 1 )
        housingMgr.sendInternalEstateInventoryBatch( player, true );
      else
        housingMgr.sendInternalEstateInventoryBatch( player );

      break;
    }
    case ClientTriggerType::RequestHousingItemRemove:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto slot = param4 & 0xFF;
      auto sendToStoreroom = ( param4 >> 16 ) != 0;

      //player, plot, containerId, slot, sendToStoreroom
      housingMgr.reqRemoveHousingItem( player, static_cast< uint16_t >( param12 ), static_cast< uint16_t >( param2 ), static_cast< uint8_t >( slot ), sendToStoreroom );

      break;
    }
    case ClientTriggerType::RequestEstateExteriorRemodel:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      housingMgr.reqEstateExteriorRemodel( player, static_cast< uint16_t >( param11 ) );

      break;
    }
    case ClientTriggerType::RequestEstateInteriorRemodel:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      housingMgr.reqEstateInteriorRemodel( player );

      break;
    }
    case ClientTriggerType::UpdateEstateGuestAccess:
    {
      auto canTeleport = ( param2 & 0xFF ) == 1;
      auto unk1 = ( param2 >> 8 & 0xFF ) == 1; // todo: related to fc? or unused?
      auto privateEstateAccess = ( param2 >> 16 & 0xFF ) == 1;
      auto unk = ( param2 >> 24 & 0xFF ) == 1; // todo: related to fc? or unused?

      player.sendDebug( "can teleport: {0}, unk: {1}, privateEstateAccess: {2}, unk: {3}",
                        canTeleport, unk1, privateEstateAccess, unk );
      break;
    }
    case ClientTriggerType::RequestEventBattle:
    {
      auto packet = makeActorControlSelf( player.getId(), ActorControl::EventBattleDialog, 0, param12, param2 );
      player.queuePacket( packet );

      player.sendDebug( "event battle level sync: {0}, ilevel sync?: {1}", param12, param2 );
      break;
    }

    default:
    {
      Logger::debug( "[{0}] Unhandled action: {1:04X}", m_pSession->getId(), commandId );
      break;
    }
  }
}
