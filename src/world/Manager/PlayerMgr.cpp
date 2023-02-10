#include "PlayerMgr.h"

#include <Service.h>

#include <Exd/ExdData.h>

#include <Territory/Territory.h>
#include <Territory/Land.h>

#include <Manager/TerritoryMgr.h>
#include <Manager/AchievementMgr.h>
#include <Manager/PartyMgr.h>
#include <Manager/HousingMgr.h>
#include <Manager/FreeCompanyMgr.h>

#include "Script/ScriptMgr.h"
#include "WorldServer.h"
#include <Common.h>

#include <Network/PacketContainer.h>
#include <Network/GameConnection.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlPacket.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/InitZonePacket.h"
#include <Network/PacketWrappers/ModelEquipPacket.h>
#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include <Network/PacketWrappers/PlayerStateFlagsPacket.h>
#include <Network/PacketWrappers/UpdateHpMpTpPacket.h>
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ChatPacket.h"
#include "Network/PacketWrappers/HudParamPacket.h"

#include <Actor/Player.h>
#include <Actor/BNpc.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;


void PlayerMgr::onOnlineStatusChanged( Entity::Player& player, bool updateProfile )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto statusPacket = makeZonePacket< FFXIVIpcSetOnlineStatus >( player.getId() );
  statusPacket->data().onlineStatusFlags = player.getFullOnlineStatusMask();
  server.queueForPlayer( player.getCharacterId(), statusPacket );

  if( updateProfile )
  {
    auto searchInfoPacket = makeZonePacket< FFXIVIpcSetProfileResult >( player.getId());
    searchInfoPacket->data().OnlineStatus = player.getFullOnlineStatusMask();
    searchInfoPacket->data().Region = player.getSearchSelectRegion();
    strcpy( searchInfoPacket->data().SearchComment, player.getSearchMessage());
    server.queueForPlayer( player.getCharacterId(), searchInfoPacket );
  }

  player.sendToInRangeSet( makeActorControl( player.getId(), SetStatusIcon, static_cast< uint8_t >( player.getOnlineStatus() ) ), true );
}

void PlayerMgr::onEquipDisplayFlagsChanged( Entity::Player& player )
{
  auto paramPacket = makeZonePacket< FFXIVIpcConfig >( player.getId() );
  paramPacket->data().flag = player.getEquipDisplayFlags();
  player.sendToInRangeSet( paramPacket, true );
}

void PlayerMgr::onSendStateFlags( Entity::Player& player, bool updateInRange )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), std::make_shared< PlayerStateFlagsPacket >( player ) );

  if( updateInRange )
    player.sendToInRangeSet( makeActorControl( player.getId(), SetStatusIcon,
                                        static_cast< uint8_t >( player.getOnlineStatus() ) ), true );
}

void PlayerMgr::onSendAchievementList( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto achvData = player.getAchievementData();

  auto achvPacket = makeZonePacket< FFXIVIpcAchievement >( player.getId() );
  std::memcpy( &achvPacket->data().complete[ 0 ], &achvData.unlockList[ 0 ], sizeof( achvPacket->data().complete ) );
  std::memcpy( &achvPacket->data().history[ 0 ], &achvData.history[ 0 ], sizeof( achvPacket->data().history ) );

  server.queueForPlayer( player.getCharacterId(), achvPacket );
}

void PlayerMgr::onSendAchievementProgress( Entity::Player& player, uint32_t achievementId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& achvMgr = Common::Service< Manager::AchievementMgr >::ref();

  auto achvProgress = achvMgr.getAchievementDataById( player, achievementId );

  auto pAchvProgressPacket = makeActorControl( player.getId(), AchievementSetRate, achievementId, achvProgress.first, achvProgress.second );
  server.queueForPlayer( player.getCharacterId(), pAchvProgressPacket );
}

void PlayerMgr::onUnlockAchievement( Entity::Player& player, uint32_t achievementId )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  onSendAchievementList( player );

  server.queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), AchievementComplete, achievementId ) );
  server.queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), AchievementObtainMsg, achievementId ) );
}

void PlayerMgr::onSendStats( Entity::Player& player )
{
  std::array< uint32_t, 50 > statParams;
  std::fill( std::begin( statParams ), std::end( statParams ), 0 );

  auto& exd = Common::Service< Data::ExdData >::ref();

  // todo: this is no doubt slow as shit...
  auto idList = exd.getIdList< Excel::BaseParam >();

  for( const auto id : idList )
  {
    auto row = exd.getRow< Excel::BaseParam >( id );
    if( !row )
    {
      continue;
    }

    if( row->data().PacketIndex < 0 )
    {
      continue;
    }

    statParams[ row->data().PacketIndex ] = player.getStatValue( static_cast< Common::BaseParam >( id ) );
  }

  auto statPacket = makeZonePacket< FFXIVIpcBaseParam >( player.getId() );
  memcpy( statPacket->data().Param, statParams.data(), sizeof( uint32_t ) * statParams.size() );

  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), statPacket );
}

void PlayerMgr::onPlayerStatusUpdate( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto playerStatusUpdate = makeZonePacket< FFXIVIpcPlayerStatusUpdate >( player.getId() );
  playerStatusUpdate->data().ClassJob = static_cast< uint8_t >( player.getClass() );
  playerStatusUpdate->data().Lv = player.getLevel();
  playerStatusUpdate->data().Lv1 = player.getLevel();
  playerStatusUpdate->data().LvSync = 0; //player.getLevelSync();
  playerStatusUpdate->data().Exp = player.getExp();

  server.queueForPlayer( player.getCharacterId(), playerStatusUpdate );
}

void PlayerMgr::onPlayerHpMpTpChanged( Entity::Player& player )
{
  player.sendToInRangeSet( std::make_shared< UpdateHpMpTpPacket >( player ), true );
}

void PlayerMgr::onPlayerItemLevelUpdate( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), SetItemLevel, player.getItemLevel(), 0 ) );
}

void PlayerMgr::onLevelUp( Entity::Player& player )
{
  player.calculateStats();
  player.sendStats();
  onPlayerHpMpTpChanged( player );

  player.sendToInRangeSet( makeHudParam( player ), true );

  player.sendToInRangeSet( makeActorControl( player.getId(), LevelUpEffect, static_cast< uint8_t >( player.getClass() ),
                           player.getLevel(), player.getLevel() - 1 ), true );

  onPlayerStatusUpdate( player );

  auto& achvMgr = Common::Service< World::Manager::AchievementMgr >::ref();
  achvMgr.progressAchievementByType< Common::Achievement::Type::Classjob >( player, static_cast< uint32_t >( player.getClass() ) );
}

void PlayerMgr::onSetLevelForClass( Entity::Player& player, Common::ClassJob classJob )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& achvMgr = Common::Service< World::Manager::AchievementMgr >::ref();

  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), Network::ActorControl::ClassJobUpdate,
                                                       static_cast< uint8_t >( classJob ), player.getLevelForClass( classJob ) ) );

  achvMgr.progressAchievementByType< Common::Achievement::Type::Classjob >( player, static_cast< uint32_t >( classJob ) );
}


void PlayerMgr::onGainExp( Entity::Player& player, uint32_t exp )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  if( exp != 0 )
    server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), GainExpMsg, static_cast< uint8_t >( player.getClass() ), exp ) );

  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), UpdateUiExp, static_cast< uint8_t >( player.getClass() ), player.getExp() ) );
}

void PlayerMgr::onUnlockOrchestrion( Entity::Player& player, uint8_t songId, uint32_t itemId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), ToggleOrchestrionUnlock, songId, 1, itemId ) );
}

void PlayerMgr::onChangeGear( Entity::Player& player )
{
  player.sendToInRangeSet( std::make_shared< ModelEquipPacket >( player ), true );
}

void PlayerMgr::onGcUpdate( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto gcAffPacket = makeZonePacket< FFXIVIpcGrandCompany >( player.getId() );
  gcAffPacket->data().ActiveCompanyId = player.getGc();
  gcAffPacket->data().MaelstromRank = player.getGcRankArray()[ 0 ];
  gcAffPacket->data().TwinAdderRank = player.getGcRankArray()[ 1 ];
  gcAffPacket->data().ImmortalFlamesRank = player.getGcRankArray()[ 2 ];
  server.queueForPlayer( player.getCharacterId(), gcAffPacket );
}

void PlayerMgr::onCompanionUpdate( Entity::Player& player, uint8_t companionId )
{
  player.sendToInRangeSet( makeActorControl( player.getId(), ActorControlType::ToggleCompanion, companionId ), true );
}

void PlayerMgr::onMountUpdate( Entity::Player& player, uint32_t mountId )
{
  if( mountId != 0 )
  {
    player.sendToInRangeSet( makeActorControl( player.getId(), ActorControlType::SetStatus,
                      static_cast< uint8_t >( Common::ActorStatus::Mounted ) ), true );
    player.sendToInRangeSet( makeActorControlSelf( player.getId(), 0x39e, 12 ), true ); //?
  }
  else
  {
    player.sendToInRangeSet( makeActorControl( player.getId(), ActorControlType::SetStatus,
                      static_cast< uint8_t >( Common::ActorStatus::Idle ) ), true );
    player.sendToInRangeSet( makeActorControlSelf( player.getId(), ActorControlType::Dismount, 1 ), true );
  }

  auto mountPacket = makeZonePacket< FFXIVIpcMount >( player.getId() );
  mountPacket->data().id = mountId;
  player.sendToInRangeSet( mountPacket, true );
}

void PlayerMgr::onMobKill( Entity::Player& player, Entity::BNpc& bnpc )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onBNpcKill( player, bnpc );

  if( player.hasReward( Common::UnlockEntry::HuntingLog ) )
  {
    player.updateHuntingLog( bnpc.getBNpcNameId() );
  }
}

void PlayerMgr::onHateListChanged( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();

  auto hateListPacket = makeZonePacket< FFXIVIpcHateList >( player.getId() );
  auto hateRankPacket = makeZonePacket< FFXIVIpcHaterList >( player.getId() );

  auto actorIdToHateSlotMap = player.getActorIdToHateSlotMap();

  hateListPacket->data().Count = static_cast< uint8_t >( actorIdToHateSlotMap.size() );
  
  hateRankPacket->data().Count = static_cast< uint8_t >( actorIdToHateSlotMap.size() );
  auto it = actorIdToHateSlotMap.begin();

  auto zone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  if( !zone )
    return;

  for( int32_t i = 0; it != actorIdToHateSlotMap.end(); ++it, ++i )
  {
    auto pBNpc = zone->getActiveBNpcByEntityId( it->first );
    if( !pBNpc )
      continue;

    auto hateValue = pBNpc->hateListGetValue( player.getAsChara() );
    if( hateValue == 0 )
      continue;

    auto hatePercent = ( hateValue / static_cast< float >( pBNpc->hateListGetHighestValue() ) ) * 100.f;

    hateListPacket->data().List[ i ].Id = player.getId();
    hateListPacket->data().List[ i ].Value = hateValue;

    hateRankPacket->data().List[ i ].Id = it->first;
    hateRankPacket->data().List[ i ].Rate = static_cast< uint8_t >( hatePercent );
  }

  server.queueForPlayer( player.getCharacterId(), { hateListPacket, hateRankPacket } );
}

void PlayerMgr::onChangeClass( Entity::Player& player )
{
  player.sendToInRangeSet( makeActorControl( player.getId(), ClassJobChange, 0x04 ), true );
  onPlayerHpMpTpChanged( player );
}

void PlayerMgr::onLogin( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto motd = server.getConfig().motd;

  std::istringstream ss( motd );
  std::string msg;
  while( std::getline( ss, msg, ';' ) )
  {
    sendServerNotice( player, msg );
  }
}

void PlayerMgr::onLogout( Entity::Player& player )
{
  auto& partyMgr = Common::Service< World::Manager::PartyMgr >::ref();
  auto& fcMgr = Common::Service< World::Manager::FreeCompanyMgr >::ref();
  // send updates to mgrs
  if( player.getPartyId() != 0 )
    partyMgr.onMemberDisconnect( player );

  fcMgr.onFcLogout( player.getCharacterId() );
}

void PlayerMgr::onDeath( Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onPlayerDeath( player );
}

void PlayerMgr::onZone( Sapphire::Entity::Player& player )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto& housingMgr = Common::Service< HousingMgr >::ref();
  auto& partyMgr = Common::Service< World::Manager::PartyMgr >::ref();
  auto& server = Common::Service< World::WorldServer >::ref();


  auto pZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  if( !pZone )
  {
    Logger::error( "Territory GuID#{} not found!", player.getTerritoryId() );
    return;
  }
  auto& teri = *pZone;

  auto initPacket = makeZonePacket< FFXIVIpcLogin >( player.getId() );
  initPacket->data().playerActorId = player.getId();

  server.queueForPlayer( player.getCharacterId(), initPacket );

  player.sendInventory();

  if( player.isLogin() )
  {
    server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), SetCharaGearParamUI, player.getEquipDisplayFlags(), 1 ) );
    server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), SetMaxGearSets, player.getMaxGearSets() ) );
  }

  // set flags, will be reset automatically by zoning ( only on client side though )
  //setStateFlag( PlayerStateFlag::BetweenAreas );
  //setStateFlag( PlayerStateFlag::BetweenAreas1 );

  if( player.hasReward( Common::UnlockEntry::HuntingLog ) )
    player.sendHuntingLog();

  player.sendStats();

  // only initialize the UI if the player in fact just logged in.
  if( player.isLogin() )
  {
    auto contentFinderList = makeZonePacket< FFXIVIpcContentAttainFlags >( player.getId() );
    std::memset( &contentFinderList->data(), 0xFF, sizeof( contentFinderList->data() ) );

    server.queueForPlayer( player.getCharacterId(), { contentFinderList, makePlayerSetup( player ) } );

    onPlayerStatusUpdate( player );

    player.sendItemLevel();

    player.clearSoldItems();
  }

  if( Sapphire::LandPtr pLand = housingMgr.getLandByOwnerId( player.getCharacterId() ) )
  {
    uint32_t state = 0;
    if( pLand->getHouse() )
    {
      state |= Common::LandFlags::CHARA_HOUSING_LAND_DATA_FLAG_HOUSE;

      // todo: remove this, debug for now
      state |= Common::LandFlags::CHARA_HOUSING_LAND_DATA_FLAG_AETHERYTE;
    }

    player.setLandFlags( Common::LandFlagsSlot::Private, state, pLand->getLandIdent() );
  }

  housingMgr.sendLandFlags( player );

  server.queueForPlayer( player.getCharacterId(), makeInitZone( player, teri ) );

  teri.onPlayerZoneIn( player );

  if( player.isLogin() )
  {
    server.queueForPlayer( player.getCharacterId(),
                           {
                             makeZonePacket< FFXIVIpcQuestRepeatFlags >( player.getId() ),
                             makeZonePacket< FFXIVIpcDailyQuests >( player.getId() )
                           } );
  }

  if( player.getPartyId() != 0 )
  {
    partyMgr.onMoveZone( player );
  }

}

////////// Helper ///////////



void PlayerMgr::sendServerNotice( Entity::Player& player, const std::string& message ) //Purple Text
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), std::make_shared< ServerNoticePacket >( player.getId(), message ) );

}

void PlayerMgr::sendUrgent( Entity::Player& player, const std::string& message ) //Red Text
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), std::make_shared< ChatPacket >( player, Common::ChatType::ServerUrgent, message ) );
}

void PlayerMgr::sendDebug( Entity::Player& player, const std::string& message ) //Grey Text
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), std::make_shared< ChatPacket >( player, Common::ChatType::SystemMessage, message ) );
}

void PlayerMgr::sendLogMessage( Entity::Player& player, uint32_t messageId, uint32_t param2, uint32_t param3,
                                uint32_t param4, uint32_t param5, uint32_t param6 )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControlTarget( player.getId(), ActorControlType::LogMsg, messageId,
                                                                                 param2, param3, param4, param5, param6 ) );
}
