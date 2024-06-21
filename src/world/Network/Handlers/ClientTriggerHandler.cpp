#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Util/Util.h>

#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include "Territory/Territory.h"
#include "Territory/ZonePosition.h"
#include <Territory/InstanceObjectCache.h>
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
  const auto p1u64 = *reinterpret_cast< const uint64_t* >( &packet.data().param1 );
  const auto p1 = packet.data().param1;
  const auto p2 = packet.data().param2;
  const auto p3 = packet.data().param3;
  const auto p4 = packet.data().param4;
  const auto pos = packet.data().position;

  Logger::debug( "[{0}] Type: {1:X} (p1u64:{2:X} p1:{3} p2:{4} p3:{5} p4:{6} x:{7} y:{8} z:{9}",
                 m_pSession->getId(), commandId, p1u64, p1, p2, p3, p4, pos.x, pos.y, pos.z );

  //Logger::Log(LoggingSeverity::debug, "[" + std::to_string(m_pSession->getId()) + "] " + pInPacket->toString());

  switch( commandId )
  {
    case ClientTriggerType::ToggleSheathe:  // Toggle sheathe
    {
      if( p1 == 1 )
        player.setStance( Common::Stance::Active );
      else
      {
        player.setStance( Common::Stance::Passive );
        player.setAutoattack( false );
      }

      player.sendToInRangeSet( makeActorControl( player.getId(), 0, p1, 1 ) );

      break;
    }
    case ClientTriggerType::ToggleAutoAttack:  // Toggle auto-attack
    {
      if( p1 == 1 )
      {
        player.setAutoattack( true );
        player.setStance( Common::Stance::Active );
      }
      else
        player.setAutoattack( false );

      // the client seems to ignore source actor of this packet and always set auto-attack on itself. causing everyone on screen take their weapons out
      player.queuePacket( makeActorControl( player.getId(), 1, p1, 1 ) );
      //player.sendToInRangeSet( makeActorControl( player.getId(), 1, p1, 1 ) );

      break;
    }
    case ClientTriggerType::ChangeTarget: // Change target
    {

      uint64_t targetId = p1u64;
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
      player.spawnCompanion( static_cast< uint16_t >( p1 ) );
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
      player.removeSingleStatusEffectById( static_cast< uint32_t >( p1 ) );
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
      uint32_t targetId = p1u64;
      examineHandler( player, targetId );
      break;
    }
    case ClientTriggerType::MarkPlayer: // Mark player
    {
      break;
    }
    case ClientTriggerType::SetTitleReq: // Set player title
    {
      player.setTitle( static_cast< uint16_t >( p1 ) );
      break;
    }
    case ClientTriggerType::TitleList: // Get title list
    {
      player.sendTitleList();
      break;
    }
    case ClientTriggerType::UpdatedSeenHowTos: // Update howtos seen
    {
      uint32_t howToId = p1;
      player.updateHowtosSeen( howToId );
      break;
    }
    case ClientTriggerType::CharaNameReq:
    {
      uint64_t targetContentId = p1u64;
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
    case ClientTriggerType::EmoteWithWarp:
    {
      uint64_t targetId = player.getTargetId();
      uint32_t emoteId = p1;
      bool isSilent = p3 == 1;

      auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
      auto emoteData = exdData.get< Data::Emote >( emoteId );

      if( !emoteData )
        return;

      if( commandId == ClientTriggerType::EmoteWithWarp )
      {
        player.setPos( packet.data().position );
        player.setRot( Util::floatFromUInt16Rot( static_cast< uint16_t >( p4 ) ) );
        if( player.hasInRangeActor() )
        {
          auto setpos = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
          setpos->data().r16 = static_cast< uint16_t >( p4 );
          setpos->data().waitForLoad = 18;
          setpos->data().x = packet.data().position.x;
          setpos->data().y = packet.data().position.y;
          setpos->data().z = packet.data().position.z;
          player.sendToInRangeSet( setpos, false );
        }
      }

      player.emote( emoteId, targetId, isSilent, commandId == ClientTriggerType::EmoteWithWarp ? static_cast< uint16_t >( p4 ) : 0 );

      bool isPersistent = emoteData->emoteMode != 0;

      if( isPersistent )
      {
        player.setStance( Common::Stance::Passive );
        player.setAutoattack( false );
        player.setPersistentEmote( emoteData->emoteMode );
        player.setStatus( Common::ActorStatus::EmoteMode );
      }

      if( emoteData->drawsWeapon )
      {
        player.setStance( Common::Stance::Active );
      }

      break;
    }
    case ClientTriggerType::EmoteCancel: // emote cancel
    case ClientTriggerType::PersistentEmoteCancel: // cancel persistent emote
    case ClientTriggerType::EmoteCancelWithWarp:
    {
      if( commandId == ClientTriggerType::EmoteCancelWithWarp )
      {
        player.setPos( packet.data().position );
        if( player.hasInRangeActor() )
        {
          auto setpos = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
          setpos->data().r16 = p2;
          setpos->data().waitForLoad = 18;
          setpos->data().x = packet.data().position.x;
          setpos->data().y = packet.data().position.y;
          setpos->data().z = packet.data().position.z;
          player.sendToInRangeSet( setpos, false );
        }
      }
      player.emoteInterrupt();
      if( player.getPersistentEmote() )
      {
        player.setPersistentEmote( 0 );
        player.setStatus( Common::ActorStatus::Idle );
        auto pSetStatusPacket = makeActorControl( player.getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );
        player.sendToInRangeSet( pSetStatusPacket );
      }
      break;
    }
    case ClientTriggerType::PoseChange: // change pose
    case ClientTriggerType::PoseReapply: // reapply pose
    {
      player.setPose( static_cast< uint8_t >( p2 ) );
      auto pSetStatusPacket = makeActorControl( player.getId(), SetPose, p1, p2 );
      player.sendToInRangeSet( pSetStatusPacket, true );
      break;
    }
    case ClientTriggerType::PoseCancel: // cancel pose
    {
      player.setPose( static_cast< uint8_t >( p2 ) );
      auto pSetStatusPacket = makeActorControl( player.getId(), SetPose, p1, p2 );
      player.sendToInRangeSet( pSetStatusPacket, false );
      break;
    }
    case ClientTriggerType::Return: // return dead / accept raise
    {
      switch( static_cast < ResurrectType >( p1 ) )
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

      player.teleportQuery( static_cast< uint16_t >( p1 ) );
      break;
    }
    case ClientTriggerType::DyeItem: // Dye item
    {
      // p1 = item to dye container
      // p2 = item to dye slot
      // p3 = dye bag container
      // p4 = dye bag slot
      player.setDyeingInfo( p1, p2, p3, p4 );
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
      player.removeQuest( static_cast< uint16_t >( p1 ) );
      break;
    }
    case ClientTriggerType::RequestHousingBuildPreset:
    {
      auto zone = player.getCurrentTerritory();
      auto hZone = std::dynamic_pointer_cast< HousingZone >( zone );
      if (!hZone)
        return;

      player.setActiveLand( static_cast< uint8_t >( p1 ), hZone->getWardNum() );

      auto pShowBuildPresetUIPacket = makeActorControl( player.getId(), ShowBuildPresetUI, p1 );
      player.queuePacket( pShowBuildPresetUIPacket );

      break;
    }
    case ClientTriggerType::RequestLandSignFree:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( p1, p2 );
      housingMgr.sendLandSignFree( player, ident );

      break;
    }
    case ClientTriggerType::RequestLandSignOwned:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( p1, p2, false );
      housingMgr.sendLandSignOwned( player, ident );

      break;
    }
    case ClientTriggerType::RequestWardLandInfo:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      housingMgr.sendWardLandInfo( player, static_cast< uint8_t >( p2 ), static_cast< uint8_t >( p1 ) );

      break;
    }
    case ClientTriggerType::RequestLandRelinquish:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto plot = static_cast< uint8_t >( p2 & 0xFF );
      housingMgr.relinquishLand( player, plot );

      break;
    }
    case ClientTriggerType::RequestEstateRename:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( p1, p2 );
      housingMgr.requestEstateRename( player, ident );

      break;
    }
    case ClientTriggerType::RequestEstateEditGreeting:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( p1, p2 );
      housingMgr.requestEstateEditGreeting( player, ident );

      break;
    }
    case ClientTriggerType::RequestEstateEditGuestAccessSettings:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( p1, p2 );
      housingMgr.requestEstateEditGuestAccess( player, ident );

      break;
    }
    case ClientTriggerType::RequestHousingItemUI:
    {
      // close ui
      if( p1 == 1 )
        break;

      // p2 is 0 when inside a house

      uint8_t ward = ( p2 >> 16 ) & 0xFF;
      uint8_t plot = ( p2 & 0xFF );
      auto pShowHousingItemUIPacket = makeActorControl( player.getId(), ShowHousingItemUI, 0, plot );

      player.queuePacket( pShowHousingItemUIPacket );

      //TODO: show item housing container

      break;
    }
    case ClientTriggerType::RequestEstateGreeting:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto ident = housingMgr.clientTriggerParamsToLandIdent( p1, p2 );
      housingMgr.sendEstateGreeting( player, ident );

      break;
    }
    case ClientTriggerType::RequestLandInventory:
    {
      uint8_t plot = ( p2 & 0xFF );

      auto& housingMgr = Common::Service< HousingMgr >::ref();

      uint16_t inventoryType = Common::InventoryType::HousingExteriorPlacedItems;
      if( p3 == 1 )
        inventoryType = Common::InventoryType::HousingExteriorStoreroom;

      housingMgr.sendEstateInventory( player, inventoryType, plot );

      break;
    }
    case ClientTriggerType::RequestEstateInventory:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      // p1 = 1 - storeroom
      // p1 = 0 - placed items

      if( p1 == 1 )
        housingMgr.sendInternalEstateInventoryBatch( player, true );
      else
        housingMgr.sendInternalEstateInventoryBatch( player );

      break;
    }
    case ClientTriggerType::RequestHousingItemRemove:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      auto slot = p4 & 0xFF;
      auto sendToStoreroom = ( p4 >> 16 ) != 0;

      //player, plot, containerId, slot, sendToStoreroom
      housingMgr.reqRemoveHousingItem( player, static_cast< uint16_t >( p2 ), static_cast< uint16_t >( p3 ), static_cast< uint8_t >( slot ), sendToStoreroom );

      break;
    }
    case ClientTriggerType::RequestEstateExteriorRemodel:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      housingMgr.reqEstateExteriorRemodel( player, static_cast< uint16_t >( p1 ) );

      break;
    }
    case ClientTriggerType::RequestEstateInteriorRemodel:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      housingMgr.reqEstateInteriorRemodel( player );

      break;
    }
    case ClientTriggerType::RequestEstateHallRemoval:
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();

      housingMgr.removeHouse( player, static_cast< uint16_t >( p1 ) );

      break;
    }
    case ClientTriggerType::UpdateEstateGuestAccess:
    {
      auto canTeleport = ( p3 & 0xFF ) == 1;
      auto unk1 = ( p3 >> 8 & 0xFF ) == 1; // todo: related to fc? or unused?
      auto privateEstateAccess = ( p3 >> 16 & 0xFF ) == 1;
      auto unk = ( p3 >> 24 & 0xFF ) == 1; // todo: related to fc? or unused?

      player.sendDebug( "can teleport: {0}, unk: {1}, privateEstateAccess: {2}, unk: {3}",
                        canTeleport, unk1, privateEstateAccess, unk );
      break;
    }
    case ClientTriggerType::RequestEventBattle:
    {
      auto packet = makeActorControlSelf( player.getId(), ActorControl::EventBattleDialog, 0, p2, p3 );
      player.queuePacket( packet );
      break;
    }
    case ClientTriggerType::CutscenePlayed:
    {
      player.sendDebug( "cutscene: {}", p1 );
      break;
    }
    case ClientTriggerType::OpenPerformInstrumentUI:
    {
      //p1 = instrument, 0 = end
      player.sendDebug( "perform: {}", p1 );
      if( p1 == 0 )
      {
        player.sendToInRangeSet( makeActorControl( player.getId(), ActorControl::SetStatus, 1, 0, 0, 0 ), true );
        player.unsetStateFlag( PlayerStateFlag::Performing );
      }
      else
      {
        player.sendToInRangeSet( makeActorControl( player.getId(), ActorControl::SetStatus, 16, p1, 0, 0 ), true );
        player.setStateFlag( PlayerStateFlag::Performing );
      }
      break;
    }
    case ClientTriggerType::CameraMode:
    {
      if( ( p1 & 0xFF ) == 1 )
      {
        player.setOnlineStatusMask( player.getOnlineStatusMask() | 0x0000000000040000 );
      }
      else
      {
        player.setOnlineStatusMask( player.getOnlineStatusMask() & 0xFFFFFFFFFFFBFFFF );
      }
      break;
    }
    case 0x25E: // coming out from water (no 3.x name)
    case 0xD1: // underwater town portal (3.x NEWBIE_TELEPO_INQUIRY)
    {
      auto p = makeZonePacket< FFXIVIpcPrepareZoning >( player.getId() );
      p->data().targetZone = player.getCurrentTerritory()->getTerritoryTypeId();
      p->data().param4 = commandId == 0xD1 ? 14 : 227;
      p->data().hideChar = commandId == 0xD1 ? 2 : 1;
      p->data().fadeOut = commandId == 0xD1 ? 24 : 25;
      p->data().fadeOutTime = 1;
      p->data().unknown = commandId == 0xD1 ? 4 : 6;
      auto x = pos.x;
      auto y = pos.y;
      auto z = pos.z;
      auto rot = player.getRot();
      if( commandId == 0xD1 )
      {
        auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
        auto exit = instanceObjectCache.getExitRange( p->data().targetZone, p1 );
        if( exit )
        {
          player.sendDebug( "exitRange {0} found!", p1 );
          auto destZone = exit->data.destTerritoryType;
          if( destZone == 0 )
            destZone = p->data().targetZone;
          else
            p->data().targetZone = destZone;
          auto pop = instanceObjectCache.getPopRange( destZone, exit->data.destInstanceObjectId );
          if( pop )
          {
            player.sendDebug( "popRange {0} found!", exit->data.destInstanceObjectId );
            x = pop->header.transform.translation.x;
            y = pop->header.transform.translation.y;
            z = pop->header.transform.translation.z;
            //rot = pop->header.transform.rotation.y; all x/y/z not correct, maybe we don't need it since we have to be facing the portal anyway?
          }
          else
          {
            player.sendUrgent( "popRange {0} not found in {1}!", exit->data.destInstanceObjectId, destZone );
          }
        }
        else
        {
          player.sendUrgent( "exitRange {0} not found in {1}!", p1, p->data().targetZone );
        }
      }
      player.queuePacket( p );
      player.setPos( x, y, z, true );
      player.setRot( rot );
      auto setPos = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
      setPos->data().r16 = Common::Util::floatToUInt16Rot( player.getRot() );
      setPos->data().x = x;
      setPos->data().y = y;
      setPos->data().z = z;
      setPos->data().waitForLoad = commandId == 0xD1 ? 24 : 25;
      setPos->data().unknown1 = 0;
      player.queuePacket( setPos ); // this packet needs a delay of 0.8 second to wait for the client finishing its water animation otherwise it looks odd.
      break;
    }
    default:
    {
      Logger::debug( "[{0}] Unhandled action: {1:04X}", m_pSession->getId(), commandId );
      break;
    }
  }
}
