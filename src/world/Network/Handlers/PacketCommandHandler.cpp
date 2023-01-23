#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Exd/ExdData.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Manager/HousingMgr.h"
#include "Manager/WarpMgr.h"

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
#include <Manager/PlayerMgr.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

const char* packetCommandToString( uint16_t commandId )
{
  switch( commandId )
  {
    case DRAWN_SWORD:
      return "DRAWN_SWORD";
    case AUTO_ATTACK:
      return "DRAWN_SWORD";
    case TARGET_DECIDE:
      return "TARGET_DECIDE";
    case REQUEST_ACTION:
      return "REQUEST_ACTION";
    case CANCEL_MOUNT:
      return "CANCEL_MOUNT";
    case COMPANION:
      return "COMPANION";
    case COMPANION_CANCEL:
      return "COMPANION_CANCEL";
    case REQUEST_STATUS_RESET:
      return "REQUEST_STATUS_RESET";
    case CANCEL_CAST:
      return "CANCEL_CAST";
    case MOUNT_LINK:
      return "MOUNT_LINK";
    case UNMOUNT_LINK:
      return "UNMOUNT_LINK";
    case BALLISTA_ACCESS:
      return "BALLISTA_ACCESS";
    case REVIVE:
      return "REVIVE";
    case FINISH_LOADING:
      return "FINISH_LOADING";
    case TELEPO_INQUIRY:
      return "TELEPO_INQUIRY";
    case TELEPO_INVITATION_ANSWER:
      return "TELEPO_INVITATION_ANSWER";
    case TELEPO_CANCEL:
      return "TELEPO_CANCEL";
    case RAISE_CANCEL:
      return "RAISE_CANCEL";
    case WARP_REPLY:
      return "WARP_REPLY";
    case REQUEST_MODE:
      return "REQUEST_MODE";
    case PUBLIC_INSTANCE:
      return "PUBLIC_INSTANCE";
    case NEWBIE_TELEPO_INQUIRY:
      return "NEWBIE_TELEPO_INQUIRY";
    case INSPECT:
      return "INSPECT";
    case MARKING:
      return "MARKING";
    case ACTIVE_TITLE:
      return "ACTIVE_TITLE";
    case TITLE_LIST:
      return "TITLE_LIST";
    case BORROW_ACTION:
      return "BORROW_ACTION";
    case RANDOM:
      return "RANDOM";
    case NAME:
      return "NAME";
    case SET_HOWTO:
      return "SET_HOWTO";
    case SET_CUTSCENE:
      return "SET_CUTSCENE";
    case PHYSICAL_BONUS:
      return "PHYSICAL_BONUS";
    case GROUND_MARKING:
      return "GROUND_MARKING";
    case CONTENTS_NOTE_REQUEST:
      return "CONTENTS_NOTE_REQUEST";
    case BAHAMUTGUIDE_AGREEMENT_CHECK_REPLY:
      return "BAHAMUTGUIDE_AGREEMENT_CHECK_REPLY";
    case SET_MARKET_PRICE:
      return "SET_MARKET_PRICE";
    case DEPOP_RETAINER:
      return "DEPOP_RETAINER";
    case MARKET_EDIT_START:
      return "MARKET_EDIT_START";
    case MARKET_EDIT_END:
      return "MARKET_EDIT_END";
    case MONSTER_NOTE_RANK_NEW_FLAG:
      return "MONSTER_NOTE_RANK_NEW_FLAG";
    case CHANGE_ITEM_COLOR:
      return "CHANGE_ITEM_COLOR";
    case LOAD_LEGACY_ITEM:
      return "LOAD_LEGACY_ITEM";
    case BRING_OUT_LEGACY_ITEM:
      return "BRING_OUT_LEGACY_ITEM";
    case FCCHEST_LOAD:
      return "FCCHEST_LOAD";
    case FCCHEST_LOCK:
      return "FCCHEST_LOCK";
    case FCCHEST_UNLOCK:
      return "FCCHEST_UNLOCK";
    case START_MATERIA_CRAFT:
      return "START_MATERIA_CRAFT";
    case PREPARE_MATERIA_CRAFT:
      return "PREPARE_MATERIA_CRAFT";
    case CANCEL_MATERIA_CRAFT:
      return "CANCEL_MATERIA_CRAFT";
    case ACCEPT_MATERIA_REQUEST:
      return "ACCEPT_MATERIA_REQUEST";
    case CANCEL_ATTACH_MATERIA_REQUEST:
      return "CANCEL_ATTACH_MATERIA_REQUEST";
    case CHECK_FOR_MATERIA_REQUEST:
      return "CHECK_FOR_MATERIA_REQUEST";
    case EXCHANGE_INACTIVE_MATERIA:
      return "EXCHANGE_INACTIVE_MATERIA";
    case DECAL_ITEM:
      return "DECAL_ITEM";
    case DECAL_MANNEQUIN:
      return "DECAL_MANNEQUIN";
    case DECAL_STORAGE_GROUP:
      return "DECAL_STORAGE_GROUP";
    case SELL_INACTIVE_MATERIA:
      return "SELL_INACTIVE_MATERIA";
    case MATERIA_REQUEST_CLASS_CHANGED:
      return "MATERIA_REQUEST_CLASS_CHANGED";
    case ITEM_RESYNC:
      return "ITEM_RESYNC";
    case FCCHEST_GIL_DEPOSIT:
      return "FCCHEST_GIL_DEPOSIT";
    case FCCHEST_GIL_TAKE:
      return "FCCHEST_GIL_TAKE";
    case FCCHEST_LOAD_LOG:
      return "FCCHEST_LOAD_LOG";
    case SET_VANITY_PATTERN:
      return "SET_VANITY_PATTERN";
    case REQUEST_RETAINER_LIST:
      return "REQUEST_RETAINER_LIST";
    case REMOVE_VANITY_PATTERN:
      return "REMOVE_VANITY_PATTERN";
    case CABINET_REQUEST:
      return "CABINET_REQUEST";
    case CABINET_STORAGE:
      return "CABINET_STORAGE";
    case CABINET_TAKEOUT:
      return "CABINET_TAKEOUT";
    case SALVAGE:
      return "SALVAGE";
    case REQUEST_SALVAGE_SUCCESS_RATE:
      return "REQUEST_SALVAGE_SUCCESS_RATE";
    case MOBHUNT_RECEIPT_ORDER:
      return "MOBHUNT_RECEIPT_ORDER";
    case MOBHUNT_BREAK_ORDER:
      return "MOBHUNT_BREAK_ORDER";
    case EMOTE:
      return "EMOTE";
    case EMOTE_WITH_WARP:
      return "EMOTE_WITH_WARP";
    case EMOTE_CANCEL:
      return "EMOTE_CANCEL";
    case EMOTE_MODE_CANCEL:
      return "EMOTE_MODE_CANCEL";
    case EMOTE_MODE_CANCEL_WITH_WARP:
      return "EMOTE_MODE_CANCEL_WITH_WARP";
    case POSE_EMOTE_CONFIG:
      return "POSE_EMOTE_CONFIG";
    case POSE_EMOTE_WORK:
      return "POSE_EMOTE_WORK";
    case POSE_EMOTE_CANCEL:
      return "POSE_EMOTE_CANCEL";
    case JUMP_START:
      return "JUMP_START";
    case JUMP_LANDING:
      return "JUMP_LANDING";
    case GIMMICK_JUMP_END:
      return "GIMMICK_JUMP_END";
    case START_CRAFT:
      return "START_CRAFT";
    case FISHING:
      return "FISHING";
    case PACKET_COMMOND_TRACKING:
      return "PACKET_COMMOND_TRACKING";
    case PACKET_COMMOND_JOURNAL_CONFIG:
      return "PACKET_COMMOND_JOURNAL_CONFIG";
    case GATHERING_NOTEBOOK_START:
      return "GATHERING_NOTEBOOK_START";
    case GATHERING_NOTEBOOK_DIVISION:
      return "GATHERING_NOTEBOOK_DIVISION";
    case GATHERING_NOTEBOOK_AREA:
      return "GATHERING_NOTEBOOK_AREA";
    case RECIPE_NOTEBOOK_START:
      return "RECIPE_NOTEBOOK_START";
    case RECIPE_NOTEBOOK_DIVISION:
      return "RECIPE_NOTEBOOK_DIVISION";
    case END_AUTO_CRAFT:
      return "END_AUTO_CRAFT";
    case CANCEL_QUEST:
      return "CANCEL_QUEST";
    case DIRECTOR_INIT_RETURN:
      return "DIRECTOR_INIT_RETURN";
    case CANCEL_GUILDLEVE:
      return "CANCEL_GUILDLEVE";
    case RETRY_GUILDLEVE:
      return "RETRY_GUILDLEVE";
    case START_GUILDLEVE:
      return "START_GUILDLEVE";
    case RETIRE_GUILDLEVE:
      return "RETIRE_GUILDLEVE";
    case CHANGE_GUILDLEVE_DIFFICULTY:
      return "CHANGE_GUILDLEVE_DIFFICULTY";
    case SYNC_DIRECTOR:
      return "SYNC_DIRECTOR";
    case EVENT_HANDLER:
      return "EVENT_HANDLER";
    case FATE_START:
      return "FATE_START";
    case FATE_INIT_RETURN:
      return "FATE_INIT_RETURN";
    case FATE_CREATE_CHARACTER_RETURN:
      return "FATE_CREATE_CHARACTER_RETURN";
    case FATE_SYNC_CONTEXT_WORK:
      return "FATE_SYNC_CONTEXT_WORK";
    case FATE_LEVEL_SYNC:
      return "FATE_LEVEL_SYNC";
    case FATE_INIT_CHARACTER_RETURN:
      return "FATE_INIT_CHARACTER_RETURN";
    case ACHIEVEMENT_REQUEST_RATE:
      return "ACHIEVEMENT_REQUEST_RATE";
    case ACHIEVEMENT_REQUEST:
      return "ACHIEVEMENT_REQUEST";
    case TROPHY_RECEPTION:
      return "TROPHY_RECEPTION";
    case TROPHY_ACQUISITION:
      return "TROPHY_ACQUISITION";
    case HOUSING_LOCK_LAND_BY_BUILD:
      return "HOUSING_LOCK_LAND_BY_BUILD";
    case HOUSING_LOCK_LAND_BY_EXTERIOR:
      return "HOUSING_LOCK_LAND_BY_EXTERIOR";
    case HOUSING_LOCK_LAND_BY_INTERIOR:
      return "HOUSING_LOCK_LAND_BY_INTERIOR";
    case HOUSING_LOCK_LAND_BY_BREAK:
      return "HOUSING_LOCK_LAND_BY_BREAK";
    case HOUSING_UNLOCK_HOUSE:
      return "HOUSING_UNLOCK_HOUSE";
    case HOUSING_AUCTION_INFO:
      return "HOUSING_AUCTION_INFO";
    case HOUSING_GET_PROFILE:
      return "HOUSING_GET_PROFILE";
    case HOUSING_GET_PROFILE_LIST:
      return "HOUSING_GET_PROFILE_LIST";
    case HOUSING_RELEASE:
      return "HOUSING_RELEASE";
    case HOUSING_BUILD:
      return "HOUSING_BUILD";
    case HOUSING_BREAK:
      return "HOUSING_BREAK";
    case HOUSING_LOAD_PARTS:
      return "HOUSING_LOAD_PARTS";
    case HOUSING_LOAD_ROOM:
      return "HOUSING_LOAD_ROOM";
    case HOUSING_LOAD_YARD:
      return "HOUSING_LOAD_YARD";
    case HOUSING_UNPLACE:
      return "HOUSING_UNPLACE";
    case HOUSING_HOUSE_NAME:
      return "HOUSING_HOUSE_NAME";
    case HOUSING_GREETING:
      return "HOUSING_GREETING";
    case HOUSING_GREETING_BY_ADDRESS:
      return "HOUSING_GREETING_BY_ADDRESS";
    case HOUSING_WELCOME:
      return "HOUSING_WELCOME";
    case HOUSING_LOAD_FURNITURE:
      return "HOUSING_LOAD_FURNITURE";
    case HOUSING_WARP_TO_SAFE:
      return "HOUSING_WARP_TO_SAFE";
    case HOUSING_LAYOUTMODE:
      return "HOUSING_LAYOUTMODE";
    case HOUSING_RELEASE_PERSONAL_ROOM:
      return "HOUSING_RELEASE_PERSONAL_ROOM";
    case HOUSING_GET_PERSONAL_ROOM_PROFILE_LIST:
      return "HOUSING_GET_PERSONAL_ROOM_PROFILE_LIST";
    case HOUSING_GET_PERSONAL_ROOM_PROFILE:
      return "HOUSING_GET_PERSONAL_ROOM_PROFILE";
    case HOUSING_GET_BUDDY_STABLE_LIST:
      return "HOUSING_GET_BUDDY_STABLE_LIST";
    case HOUSING_TRAIN_BUDDY:
      return "HOUSING_TRAIN_BUDDY";
    case HOUSING_FEED_BUDDY:
      return "HOUSING_FEED_BUDDY";
    case PVP_LEARN_ACTION:
      return "PVP_LEARN_ACTION";
    case PVP_LEARN_ACTION_TRAIT:
      return "PVP_LEARN_ACTION_TRAIT";
    case PVP_LEARN_TRAIT:
      return "PVP_LEARN_TRAIT";
    case PVP_ACTION:
      return "PVP_ACTION";
    case PVP_RESET_REWARD:
      return "PVP_RESET_REWARD";
    case DISCARD_TREASURE_MAP:
      return "DISCARD_TREASURE_MAP";
    case TREASURE_HUNT_GET_MAP_TIME:
      return "TREASURE_HUNT_GET_MAP_TIME";
    case SET_RETAINER_TASK:
      return "SET_RETAINER_TASK";
    case CANCEL_RETAINER_TASK:
      return "CANCEL_RETAINER_TASK";
    case SET_VENTURE_TUTORIAL_FLAGS:
      return "SET_VENTURE_TUTORIAL_FLAGS";
    case SET_RETAINER_FLAGS:
      return "SET_RETAINER_FLAGS";
    case RELIC_NOTE_CLEAR:
      return "RELIC_NOTE_CLEAR";
    case RELIC_GEM_ABSORB_MATERIA:
      return "RELIC_GEM_ABSORB_MATERIA";
    case REPAIR_ITEM:
      return "REPAIR_ITEM";
    case REPAIR_ITEM_NPC:
      return "REPAIR_ITEM_NPC";
    case REPAIR_STORAGE_GROUP:
      return "REPAIR_STORAGE_GROUP";
    case REPAIR_STORAGE_GROUP_NPC:
      return "REPAIR_STORAGE_GROUP_NPC";
    case REPAIR_MANNEQUIN:
      return "REPAIR_MANNEQUIN";
    case REPAIR_MANNEQUIN_NPC:
      return "REPAIR_MANNEQUIN_NPC";
    case BUDDY_ACTION:
      return "BUDDY_ACTION";
    case BUDDY_EQUIP:
      return "BUDDY_EQUIP";
    case BUDDY_INCREASE_SKILL_LINE:
      return "BUDDY_INCREASE_SKILL_LINE";
    case PET_COMMAND:
      return "PET_COMMAND";
    case SCREEN_SHOT:
      return "SCREEN_SHOT";
    default:
      return "UNKNOWN";
  }
}

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


  Logger::debug( "\t\t {5} | {1:X} ( p1:{2:X} p2:{3:X} p3:{4:X} )",
                 m_pSession->getId(), commandId, param1, param2, param3, packetCommandToString( commandId ) );

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

      if( targetId == player.getTargetId() || targetId == Common::INVALID_GAME_OBJECT_ID )
        targetId = 0;

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
      player.setCompanion( static_cast< uint8_t >( param1 ) );
      break;
    }
    case PacketCommand::COMPANION_CANCEL:
    {
      player.setCompanion( 0 );
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
      auto emoteData = exdData.getRow< Excel::Emote >( emoteId );

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

      break;
    }
    case PacketCommand::FINISH_LOADING: // Finish zoning
    {
      auto& warpMgr = Service< WarpMgr >::ref();
      warpMgr.finishWarp( player );
      player.setLoadingComplete( true );
      if( player.isLogin() )
        player.setIsLogin( false );
      break;
    }
    case PacketCommand::ACHIEVEMENT_REQUEST_RATE:
    {
      Service< World::Manager::PlayerMgr >::ref().onSendAchievementProgress( player, param11 );
      break;
    }
    case PacketCommand::ACHIEVEMENT_REQUEST:
    {
      Service< World::Manager::PlayerMgr >::ref().onSendAchievementList( player );
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
      if( !hZone )
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
      if( !hZone )
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
      Logger::debug( "[{0}] Unhandled Command: {1:04X}", m_pSession->getId(), commandId );
      break;
    }
  }
}
