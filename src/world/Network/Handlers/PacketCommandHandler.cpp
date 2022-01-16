#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Exd/ExdData.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Territory/Territory.h"
#include "Manager/HousingMgr.h"

#include "Network/GameConnection.h"

#include "Network/PacketWrappers/InspectPacket.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"

#include "Action/Action.h"


#include "Session.h"
#include "WorldServer.h"
#include "Forwards.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

void examineHandler( Sapphire::Entity::Player& player, uint32_t targetId )
{
  using namespace Sapphire;

  auto& server = Service< World::WorldServer >::ref();
  auto pSession = server.getSession( targetId );
  if( pSession )
  {
    auto pTarget = pSession->getPlayer();
    if( pTarget )
    {
      if( pTarget->isActingAsGm() || pTarget->getTerritoryTypeId() != player.getTerritoryTypeId() )
      {
        server.queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), ActorControlType::ExamineError ) );
      }
      else
      {
        server.queueForPlayer( player.getCharacterId(), std::make_shared< InspectPacket >( player, pTarget ) );
      }
    }
  }
}

void Sapphire::Network::GameConnection::commandHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{

  const auto packet = ZoneChannelPacket< FFXIVIpcClientTrigger >( inPacket );
  auto& server = Service< World::WorldServer >::ref();
  auto& teriMgr = Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );

  const auto commandId = packet.data().Id;
  const auto param1 = *reinterpret_cast< const uint64_t* >( &packet.data().Arg0 );
  const auto param11 = packet.data().Arg0;
  const auto param12 = packet.data().Arg1;
  const auto param2 = packet.data().Arg2;
  const auto param4 = packet.data().Arg3;
  const auto param3 = packet.data().Target;


  Logger::debug( "[{0}] Incoming Packet Command: {1:X} ( p1:{2:X} p2:{3:X} p3:{4:X} )",
                 m_pSession->getId(), commandId, param1, param2, param3 );

  //Logger::Log(LoggingSeverity::debug, "[" + std::to_string(m_pSession->getId()) + "] " + pInPacket->toString());

  switch( commandId )
  {
    case PacketCommand::DRAWN_SWORD:  // Toggle sheathe
    {
      if( param11 == 1 )
        player.setStance( Stance::Active );
      else
      {
        player.setStance( Stance::Passive );
        player.setAutoattack( false );
      }

      player.sendToInRangeSet( makeActorControl( player.getId(), 0, param11, 1 ) );

      break;
    }
    case PacketCommand::AUTO_ATTACK:  // Toggle auto-attack
    {
      if( param11 == 1 )
      {
        player.setAutoattack( true );
        player.setStance( Stance::Active );
      }
      else
        player.setAutoattack( false );

      player.sendToInRangeSet( makeActorControl( player.getId(), 1, param11, 1 ) );

      break;
    }
    case PacketCommand::TARGET_DECIDE: // Change target
    {

      uint64_t targetId = param1;
      player.changeTarget( targetId );
      break;
    }
    case PacketCommand::CANCEL_MOUNT:
    {
      player.setMount( 0 );
      break;
    }
    case PacketCommand::COMPANION:
    {
      player.setCompanion( static_cast< uint16_t >( param1 ) );
      break;
    }
    case PacketCommand::REQUEST_STATUS_RESET: // Remove status (clicking it off)
    {
      // todo: check if status can be removed by client from exd
      player.removeSingleStatusEffectById( static_cast< uint32_t >( param1 ) );
      break;
    }
    case PacketCommand::CANCEL_CAST:
    {
      if( player.getCurrentAction() )
        player.getCurrentAction()->setInterrupted( ActionInterruptType::RegularInterrupt );
      break;
    }
    case PacketCommand::INSPECT:
    {
      uint32_t targetId = param11;
      examineHandler( player, targetId );
      break;
    }
    case PacketCommand::MARKING: // Mark player
    {
      break;
    }
    case PacketCommand::ACTIVE_TITLE: // Set player title
    {
      player.setTitle( static_cast< uint16_t >( param1 ) );
      break;
    }
    case PacketCommand::TITLE_LIST: // Get title list
    {
      player.sendTitleList();
      break;
    }
    case PacketCommand::SET_HOWTO: // Update howtos seen
    {
      uint32_t howToId = param11;
      player.updateHowtosSeen( howToId );
      break;
    }
    case PacketCommand::SET_CUTSCENE:
    {
      server.queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), ActorControlType::SetCutsceneFlag, param11, 1 ) );
      break;
    }
    case PacketCommand::EMOTE: // emote
    {
      uint64_t targetId = player.getTargetId();
      uint32_t emoteId = param11;
      bool isSilent = param2 == 1;

      auto& exdData = Service< Data::ExdData >::ref();
      auto emoteData = exdData.getRow< Component::Excel::Emote >( emoteId );

      if( !emoteData )
        return;

      player.sendToInRangeSet( makeActorControlTarget( player.getId(), ActorControlType::Emote, emoteId, 0, isSilent ? 1 : 0, 0, targetId ) );

      bool isPersistent = emoteData->data().Mode != 0;

      if( isPersistent )
      {
        player.setStance( Stance::Passive );
        player.setAutoattack( false );
        player.setPersistentEmote( emoteData->data().Mode );
        player.setStatus( ActorStatus::EmoteMode );

        player.sendToInRangeSet( makeActorControl( player.getId(), ActorControlType::SetStatus,
                                                          static_cast< uint8_t >( ActorStatus::EmoteMode ),
                                                         emoteData->data().IsEndEmoteMode ? 1 : 0 ), true );
      }

      if( emoteData->data().IsAvailableWhenDrawn )
      {
        player.setStance( Stance::Active );
      }

      break;
    }
    case PacketCommand::EMOTE_CANCEL: // emote
    {
      player.sendToInRangeSet( makeActorControl( player.getId(), ActorControlType::EmoteInterrupt ) );
      break;
    }
 /*   case PacketCommand::PersistentEmoteCancel: // cancel persistent emote
    {
      player.setPersistentEmote( 0 );
      player.emoteInterrupt();
      player.setStatus( ActorStatus::Idle );
      auto pSetStatusPacket = makeActorControl( player.getId(), SetStatus, static_cast< uint8_t >( ActorStatus::Idle ) );
      player.sendToInRangeSet( pSetStatusPacket );
      break;
    }*/
    case PacketCommand::POSE_EMOTE_CONFIG: // change pose
    case PacketCommand::POSE_EMOTE_WORK: // reapply pose
    {
      player.setPose( static_cast< uint8_t >( param12 ) );
      auto pSetStatusPacket = makeActorControl( player.getId(), SetPose, param11, param12 );
      player.sendToInRangeSet( pSetStatusPacket, true );
      break;
    }
    case PacketCommand::POSE_EMOTE_CANCEL: // cancel pose
    {
      player.setPose( static_cast< uint8_t >( param12 ) );
      auto pSetStatusPacket = makeActorControl( player.getId(), SetPose, param11, param12 );
      player.sendToInRangeSet( pSetStatusPacket, true );
      break;
    }
    case PacketCommand::REVIVE: // return dead / accept raise
    {
      switch( static_cast < ResurrectType >( param1 ) )
      {
        case ResurrectType::RaiseSpell:
          // todo: handle raise case (set position to raiser, apply weakness status, set hp/mp/tp as well as packet)
          player.teleport( player.getHomepoint(), 3 );
          break;
        case ResurrectType::Return:
          player.teleport( player.getHomepoint(), 3 );
          break;
        default:
          break;
      }

    }
    case PacketCommand::FINISH_LOADING: // Finish zoning
    {
      player.finishZoning();
      player.setLoadingComplete( true );
      if( player.isLogin() )
        player.setIsLogin( false );
      break;
    }

    case PacketCommand::TELEPO_INQUIRY: // Teleport
    {

      player.teleportQuery( static_cast< uint16_t >( param11 ) );
      break;
    }
  /*  case PacketCommand::DyeItem: // Dye item
    {
      // param11 = item to dye container
      // param12 = item to dye slot
      // param2 = dye bag container
      // param4 = dye bag slot
      player.setDyeingInfo( param11, param12, param2, param4 );
      break;
    }*/
    case PacketCommand::DIRECTOR_INIT_RETURN: // Director init finish
    {
      pZone->onInitDirector( player );
      break;
    }
    case PacketCommand::SYNC_DIRECTOR: // Director init finish
    {
      pZone->onDirectorSync( player );
      break;
    }
/*    case PacketCommand::EnterTerritoryEventFinished:// this may still be something else. I think i have seen it elsewhere
    {
      player.setOnEnterEventDone( true );
      break;
    }*/
    case PacketCommand::EVENT_HANDLER:
    {
      pZone->onEventHandlerOrder( player, param11, param12, param2, param3, param4 );

      break;
    }
    case PacketCommand::CANCEL_QUEST:
    {
      player.removeQuest( static_cast< uint16_t >( param1 ) );
      break;
    }
    case PacketCommand::HOUSING_LOCK_LAND_BY_BUILD:
    {
      auto hZone = std::dynamic_pointer_cast< HousingZone >( pZone );
      if (!hZone)
        return;

      player.setActiveLand( static_cast< uint8_t >( param11 ), hZone->getWardNum() );

      auto pShowBuildPresetUIPacket = makeActorControl( player.getId(), ShowBuildPresetUI, param11 );
      server.queueForPlayer( player.getCharacterId(), pShowBuildPresetUIPacket );

      break;
    }
    case PacketCommand::HOUSING_AUCTION_INFO:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.sendLandSignFree( player, ident );

      break;
    }
    case PacketCommand::HOUSING_GET_PROFILE:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12, false );
      housingMgr.sendLandSignOwned( player, ident );

      break;
    }
    case PacketCommand::HOUSING_GET_PROFILE_LIST:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      housingMgr.sendWardLandInfo( player, static_cast< uint8_t >( param12 ), static_cast< uint8_t >( param11 ) );

      break;
    }
    case PacketCommand::HOUSING_RELEASE:
    {
      auto& housingMgr = Service< HousingMgr >::ref();
      auto hZone = std::dynamic_pointer_cast< HousingZone >( pZone );
      if (!hZone)
        return;

      auto plot = static_cast< uint8_t >( param12 & 0xFF );
      housingMgr.relinquishLand( player, *hZone, plot );

      break;
    }
    case PacketCommand::HOUSING_HOUSE_NAME:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.requestEstateRename( player, ident );

      break;
    }
    case PacketCommand::HOUSING_EDIT_WELCOME:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.requestEstateEditGreeting( player, ident );

      break;
    }
   /* case PacketCommand::RequestEstateEditGuestAccessSettings:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.requestEstateEditGuestAccess( player, ident );

      break;
    }*/
   case PacketCommand::HOUSING_LAYOUTMODE:
    {
      // close ui
      if( param11 == 1 )
        break;

      // param12 is 0 when inside a house

      uint8_t ward = ( param12 >> 16 ) & 0xFF;
      uint8_t plot = ( param12 & 0xFF );
      auto pShowHousingItemUIPacket = makeActorControl( player.getId(), ShowHousingItemUI, 0, plot );

      server.queueForPlayer( player.getCharacterId(), pShowHousingItemUIPacket );

      //TODO: show item housing container

      break;
    }
    case PacketCommand::HOUSING_WELCOME:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( param11, param12 );
      housingMgr.sendEstateGreeting( player, ident );

      break;
    }
/*    case PacketCommand::RequestLandInventory:
    {
      uint8_t plot = ( param12 & 0xFF );

      auto& housingMgr = Service< HousingMgr >::ref();

      uint16_t inventoryType = InventoryType::HousingExteriorPlacedItems;
      if( param2 == 1 )
        inventoryType = InventoryType::HousingExteriorStoreroom;

      housingMgr.sendEstateInventory( player, inventoryType, plot );

      break;
    }
    case PacketCommand::RequestEstateInventory:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      // param1 = 1 - storeroom
      // param1 = 0 - placed items

      if( param1 == 1 )
        housingMgr.sendInternalEstateInventoryBatch( player, true );
      else
        housingMgr.sendInternalEstateInventoryBatch( player );

      break;
    }
    case PacketCommand::RequestHousingItemRemove:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      auto slot = param4 & 0xFF;
      auto sendToStoreroom = ( param4 >> 16 ) != 0;

      //player, plot, containerId, slot, sendToStoreroom
      housingMgr.reqRemoveHousingItem( player, static_cast< uint16_t >( param12 ), static_cast< uint16_t >( param2 ), static_cast< uint8_t >( slot ), sendToStoreroom );

      break;
    }
    case PacketCommand::RequestEstateExteriorRemodel:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      housingMgr.reqEstateExteriorRemodel( player, static_cast< uint16_t >( param11 ) );

      break;
    }
    case PacketCommand::RequestEstateInteriorRemodel:
    {
      auto& housingMgr = Service< HousingMgr >::ref();

      housingMgr.reqEstateInteriorRemodel( player );

      break;
    }
    case PacketCommand::UpdateEstateGuestAccess:
    {
      auto canTeleport = ( param2 & 0xFF ) == 1;
      auto unk1 = ( param2 >> 8 & 0xFF ) == 1; // todo: related to fc? or unused?
      auto privateEstateAccess = ( param2 >> 16 & 0xFF ) == 1;
      auto unk = ( param2 >> 24 & 0xFF ) == 1; // todo: related to fc? or unused?

      player.sendDebug( "can teleport: {0}, unk: {1}, privateEstateAccess: {2}, unk: {3}",
                        canTeleport, unk1, privateEstateAccess, unk );
      break;
    }
    case PacketCommand::RequestEventBattle:
    {
      auto packet = makeActorControlSelf( player.getId(), ActorControl::EventBattleDialog, 0, param12, param2 );
      player.queuePacket( packet );

      player.sendDebug( "event battle level sync: {0}, ilevel sync?: {1}", param12, param2 );
      break;
    }*/

    default:
    {
      Logger::debug( "[{0}] Unhandled action: {1:04X}", m_pSession->getId(), commandId );
      break;
    }
  }
}
