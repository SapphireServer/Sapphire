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
#include <Manager/QuestMgr.h>

#include <Script/ScriptMgr.h>
#include <WorldServer.h>
#include <Common.h>

#include <Network/PacketContainer.h>
#include <Network/GameConnection.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlPacket.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Network/PacketWrappers/ActorControlTargetPacket.h>
#include <Network/PacketWrappers/InitZonePacket.h>
#include <Network/PacketWrappers/ModelEquipPacket.h>
#include <Network/PacketWrappers/PlayerSetupPacket.h>
#include <Network/PacketWrappers/ConditionPacket.h>
#include <Network/PacketWrappers/UpdateHpMpTpPacket.h>
#include <Network/PacketWrappers/ServerNoticePacket.h>
#include <Network/PacketWrappers/ChatPacket.h>
#include <Network/PacketWrappers/HudParamPacket.h>

#include <Actor/Player.h>
#include <Actor/BNpc.h>

#include <Inventory/Item.h>

#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;


void PlayerMgr::onOnlineStatusChanged( Entity::Player& player, bool updateProfile )
{
  auto statusPacket = makeZonePacket< FFXIVIpcSetOnlineStatus >( player.getId() );
  statusPacket->data().onlineStatusFlags = player.getFullOnlineStatusMask();
  server().queueForPlayer( player.getCharacterId(), statusPacket );

  if( updateProfile )
  {
    auto searchInfoPacket = makeZonePacket< FFXIVIpcSetProfileResult >( player.getId());
    searchInfoPacket->data().OnlineStatus = player.getFullOnlineStatusMask();
    searchInfoPacket->data().Region = player.getSearchSelectRegion();
    strcpy( searchInfoPacket->data().SearchComment, player.getSearchMessage());
    server().queueForPlayer( player.getCharacterId(), searchInfoPacket );
  }

  server().queueForPlayers( player.getInRangePlayerIds( true ),
                            makeActorControl( player.getId(), SetStatusIcon, static_cast< uint8_t >( player.getOnlineStatus() ) ) );
}

void PlayerMgr::onEquipDisplayFlagsChanged( Entity::Player& player )
{
  auto paramPacket = makeZonePacket< FFXIVIpcConfig >( player.getId() );
  paramPacket->data().flag = player.getEquipDisplayFlags();
  server().queueForPlayers( player.getInRangePlayerIds( true ), paramPacket );
}

void PlayerMgr::onConditionChanged( Entity::Player& player, bool updateInRange )
{

  server().queueForPlayer( player.getCharacterId(), std::make_shared< ConditionPacket >( player ) );

  if( updateInRange )
    server().queueForPlayers( player.getInRangePlayerIds( true ),
                              makeActorControl( player.getId(), SetStatusIcon, static_cast< uint8_t >( player.getOnlineStatus() ) ) );
}

void PlayerMgr::onAchievementListChanged( Entity::Player& player )
{
  auto achvData = player.getAchievementData();

  auto achvPacket = makeZonePacket< FFXIVIpcAchievement >( player.getId() );
  std::memcpy( &achvPacket->data().complete[ 0 ], &achvData.unlockList[ 0 ], sizeof( achvPacket->data().complete ) );
  std::memcpy( &achvPacket->data().history[ 0 ], &achvData.history[ 0 ], sizeof( achvPacket->data().history ) );

  server().queueForPlayer( player.getCharacterId(), achvPacket );
}

void PlayerMgr::onAchievementProgressChanged( Entity::Player& player, uint32_t achievementId )
{

  auto& achvMgr = Common::Service< Manager::AchievementMgr >::ref();

  auto achvProgress = achvMgr.getAchievementDataById( player, achievementId );

  auto pAchvProgressPacket = makeActorControl( player.getId(), AchievementSetRate, achievementId, achvProgress.first, achvProgress.second );
  server().queueForPlayer( player.getCharacterId(), pAchvProgressPacket );
}

void PlayerMgr::onUnlockAchievement( Entity::Player& player, uint32_t achievementId )
{
  onAchievementListChanged( player );

  server().queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), AchievementComplete, achievementId ) );
  server().queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), AchievementObtainMsg, achievementId ) );
}

void PlayerMgr::onStatsChanged( Entity::Player& player )
{
  std::array< uint32_t, 50 > statParams{};
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
  server().queueForPlayer( player.getCharacterId(), statPacket );
}

void PlayerMgr::onPlayerStatusUpdate( Entity::Player& player )
{
  auto playerStatusUpdate = makeZonePacket< FFXIVIpcPlayerStatusUpdate >( player.getId() );
  playerStatusUpdate->data().ClassJob = static_cast< uint8_t >( player.getClass() );
  playerStatusUpdate->data().Lv = player.getLevel();
  playerStatusUpdate->data().Lv1 = player.getLevel();
  playerStatusUpdate->data().LvSync = 0; //player.getLevelSync();
  playerStatusUpdate->data().Exp = player.getExp();

  server().queueForPlayer( player.getCharacterId(), playerStatusUpdate );
}

void PlayerMgr::onPlayerHpMpTpChanged( Entity::Player& player )
{
  server().queueForPlayers( player.getInRangePlayerIds( true ), std::make_shared< UpdateHpMpTpPacket >( player ) );
  auto hudParamPacket = makeHudParam( player );
  server().queueForPlayer( player.getCharacterId(), hudParamPacket );
}

void PlayerMgr::onPlayerItemLevelUpdate( Entity::Player& player )
{
  server().queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), SetItemLevel, player.getItemLevel(), 0 ) );
}

void PlayerMgr::onLevelUp( Entity::Player& player )
{
  player.calculateStats();
  player.sendStats();
  onPlayerHpMpTpChanged( player );

  auto inRangePlayerIds = player.getInRangePlayerIds( true );

  server().queueForPlayers( inRangePlayerIds, makeHudParam( player ) );
  server().queueForPlayers( inRangePlayerIds, makeActorControl( player.getId(), LevelUpEffect, static_cast< uint8_t >( player.getClass() ),
                                                              player.getLevel(), player.getLevel() - 1 ) );

  onPlayerStatusUpdate( player );

  auto& achvMgr = Common::Service< World::Manager::AchievementMgr >::ref();
  achvMgr.progressAchievementByType< Common::Achievement::Type::Classjob >( player, static_cast< uint32_t >( player.getClass() ) );
}

void PlayerMgr::onSetLevelForClass( Entity::Player& player, Common::ClassJob classJob )
{
  auto& achvMgr = Common::Service< World::Manager::AchievementMgr >::ref();

  server().queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), Network::ActorControl::ClassJobUpdate,
                                                                          static_cast< uint8_t >( classJob ), player.getLevelForClass( classJob ) ) );

  achvMgr.progressAchievementByType< Common::Achievement::Type::Classjob >( player, static_cast< uint32_t >( classJob ) );
}


void PlayerMgr::onGainExp( Entity::Player& player, uint32_t exp )
{

  if( exp != 0 )
    server().queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), GainExpMsg,
                                                                            static_cast< uint8_t >( player.getClass() ), exp ) );

  server().queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), UpdateUiExp,
                                                                          static_cast< uint8_t >( player.getClass() ), player.getExp() ) );
}

void PlayerMgr::onUnlockOrchestrion( Entity::Player& player, uint8_t songId, uint32_t itemId )
{
  player.learnSong( songId, itemId );

  server().queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), ToggleOrchestrionUnlock, songId, 1, itemId ) );
}

void PlayerMgr::onGearChanged( Entity::Player& player )
{
  server().queueForPlayers( player.getInRangePlayerIds( true ), std::make_shared< ModelEquipPacket >( player ) );
}

void PlayerMgr::onGrandCompanyChanged( Entity::Player& player )
{
  auto gcAffPacket = makeZonePacket< FFXIVIpcGrandCompany >( player.getId() );
  gcAffPacket->data().ActiveCompanyId = player.getGc();
  gcAffPacket->data().MaelstromRank = player.getGcRankArray()[ 0 ];
  gcAffPacket->data().TwinAdderRank = player.getGcRankArray()[ 1 ];
  gcAffPacket->data().ImmortalFlamesRank = player.getGcRankArray()[ 2 ];

  server().queueForPlayer( player.getCharacterId(), gcAffPacket );
}

void PlayerMgr::setGrandCompany( Entity::Player& player, uint8_t gc )
{
  player.setGc( gc );

  onGrandCompanyChanged( player );
}

void PlayerMgr::setGrandCompanyRank( Entity::Player& player, uint8_t gc, uint8_t rank )
{
  player.setGcRankAt( gc, rank );

  onGrandCompanyChanged( player );
}

void PlayerMgr::onCompanionUpdate( Entity::Player& player, uint8_t companionId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto companion = exdData.getRow< Excel::Companion >( companionId );
  if( !companion )
    return;

  player.setCompanion( companionId );
  server().queueForPlayers( player.getInRangePlayerIds( true ), makeActorControl( player.getId(), ActorControlType::ToggleCompanion, companionId ) );
}

void PlayerMgr::onMountUpdate( Entity::Player& player, uint32_t mountId )
{

  auto inRangePlayerIds = player.getInRangePlayerIds( true );
  if( mountId != 0 )
  {
    server().queueForPlayers( inRangePlayerIds,
                            makeActorControl( player.getId(), ActorControlType::SetStatus, static_cast< uint8_t >( Common::ActorStatus::Mounted ) ) );
    server().queueForPlayers( inRangePlayerIds, makeActorControlSelf( player.getId(), 0x39e, 12 ) );
  }
  else
  {
    server().queueForPlayers( inRangePlayerIds,
                            makeActorControl( player.getId(), ActorControlType::SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) ) );
    server().queueForPlayers( inRangePlayerIds, makeActorControlSelf( player.getId(), ActorControlType::Dismount, 1 ) );
  }

  auto mountPacket = makeZonePacket< FFXIVIpcMount >( player.getId() );
  mountPacket->data().id = mountId;
  server().queueForPlayers( inRangePlayerIds, mountPacket );
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

  server().queueForPlayer( player.getCharacterId(), { hateListPacket, hateRankPacket } );
}

void PlayerMgr::onClassChanged( Entity::Player& player )
{
  server().queueForPlayers( player.getInRangePlayerIds( true ), makeActorControl( player.getId(), ClassJobChange, 0x04 ) );
  onPlayerHpMpTpChanged( player );
}

void PlayerMgr::onLogin( Entity::Player& player )
{
  auto motd = server().getConfig().motd;

  std::istringstream ss( motd );
  std::string msg;
  while( std::getline( ss, msg, ';' ) )
  {
    sendServerNotice( player, msg );
  }
}

void PlayerMgr::onLogout( Entity::Player &player )
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

void PlayerMgr::onMoveZone( Sapphire::Entity::Player& player )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto& housingMgr = Common::Service< HousingMgr >::ref();
  auto& partyMgr = Common::Service< World::Manager::PartyMgr >::ref();

  auto pZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  if( !pZone )
  {
    Logger::error( "Territory GuID#{} not found!", player.getTerritoryId() );
    return;
  }
  auto& teri = *pZone;

  auto initPacket = makeZonePacket< FFXIVIpcLogin >( player.getId() );
  initPacket->data().playerActorId = player.getId();

  server().queueForPlayer( player.getCharacterId(), initPacket );

  player.sendInventory();

  if( player.isLogin() )
  {
    server().queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), SetConfigFlags, player.getEquipDisplayFlags(), 1 ) );
    server().queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), SetMaxGearSets, player.getMaxGearSets() ) );
  }

  // set flags, will be reset automatically by zoning ( only on client side though )
  //setStateFlag( PlayerStateFlag::BetweenAreas );
  //setStateFlag( PlayerStateFlag::BetweenAreas1 );

  player.sendHuntingLog();

  if( player.isLogin() )
    server().queueForPlayer( player.getCharacterId(), makePlayerSetup( player ) );

  player.sendRecastGroups();
  player.sendStats();
  player.sendItemLevel();
  if( player.isLogin() )
  {
    auto classInfo = makeZonePacket< FFXIVIpcChangeClass >( player.getId() );
    classInfo->data().ClassJob = static_cast< uint8_t >( player.getClass() );
    classInfo->data().Lv = player.getLevel();
    classInfo->data().Lv1 = player.getLevel();
    if( player.isLogin() )
      classInfo->data().Login = 1;
    server().queueForPlayer( player.getCharacterId(), classInfo );

    server().queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), 0x112, 0x24 ) ); // unknown

    auto contentFinderList = makeZonePacket< FFXIVIpcContentAttainFlags >( player.getId() );
    std::memset( &contentFinderList->data(), 0xFF, sizeof( contentFinderList->data() ) );
    server().queueForPlayer( player.getCharacterId(), contentFinderList );

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

  server().queueForPlayer( player.getCharacterId(), makeInitZone( player, teri ) );

  teri.onPlayerZoneIn( player );

  if( player.isLogin() )
  {
    server().queueForPlayer( player.getCharacterId(),
                             {
                               makeZonePacket< FFXIVIpcDailyQuests >( player.getId() ),
                               makeZonePacket< FFXIVIpcQuestRepeatFlags >( player.getId() )
                             } );

    auto &questMgr = Common::Service< World::Manager::QuestMgr >::ref();
    questMgr.sendQuestsInfo( player );
    onGrandCompanyChanged( player );
  }

  if( player.getPartyId() != 0 )
  {
    partyMgr.onMoveZone( player );
  }

}

void PlayerMgr::onUpdate( Entity::Player& player, uint64_t tickCount )
{
  if( player.getHp() <= 0 && player.getStatus() != Common::ActorStatus::Dead )
  {
    player.die();
    onDeath( player );
  }

  if( !player.isAlive() )
    return;

  if( !player.checkAction() && ( player.getTargetId() && player.getStance() == Common::Stance::Active && player.isAutoattackOn() ) )
  {
    auto mainWeap = player.getItemAt( Common::GearSet0, Common::GearSetSlot::MainHand );

    // @TODO i dislike this, iterating over all in range actors when you already know the id of the actor you need...
    for( const auto& actor : player.getInRangeActors() )
    {
      if( actor->getId() == player.getTargetId() && actor->getAsChara()->isAlive() && mainWeap )
      {
        auto chara = actor->getAsChara();

        // default autoattack range
        float range = 3.f + chara->getRadius() + player.getRadius() * 0.5f;

        // default autoattack range for ranged classes
        auto classJob = player.getClass();

        if( classJob == Common::ClassJob::Machinist || classJob == Common::ClassJob::Bard || classJob == Common::ClassJob::Archer )
          range = 25.f + chara->getRadius() + player.getRadius() * 0.5f;

        if( Common::Util::distance( player.getPos(), actor->getPos() ) <= range )
        {
          if( ( tickCount - player.getLastAttack() ) > mainWeap->getDelay() )
          {
            player.setLastAttack( tickCount );
            player.autoAttack( actor->getAsChara() );
          }
        }
      }
    }
  }
}

void PlayerMgr::setCondition( Sapphire::Entity::Player& player, Common::PlayerCondition flag )
{
  auto prevOnlineStatus = player.getOnlineStatus();

  player.setCondition( flag );

  auto newOnlineStatus = player.getOnlineStatus();
  onConditionChanged( player, prevOnlineStatus != newOnlineStatus );
}

void PlayerMgr::removeCondition( Sapphire::Entity::Player& player, Common::PlayerCondition flag )
{
  auto prevOnlineStatus = player.getOnlineStatus();

  player.removeCondition( flag );

  auto newOnlineStatus = player.getOnlineStatus();
  onConditionChanged( player, prevOnlineStatus != newOnlineStatus );
}

////////// Helper ///////////

void PlayerMgr::sendServerNotice( Entity::Player& player, const std::string& message ) //Purple Text
{
  server().queueForPlayer( player.getCharacterId(), std::make_shared< ServerNoticePacket >( player.getId(), message ) );
}

void PlayerMgr::sendUrgent( Entity::Player& player, const std::string& message ) //Red Text
{
  server().queueForPlayer( player.getCharacterId(), std::make_shared< ChatPacket >( player, Common::ChatType::ServerUrgent, message ) );
}

void PlayerMgr::sendDebug( Entity::Player& player, const std::string& message ) //Grey Text
{
  server().queueForPlayer( player.getCharacterId(), std::make_shared< ChatPacket >( player, Common::ChatType::SystemMessage, message ) );
}

void PlayerMgr::sendLogMessage( Entity::Player& player, uint32_t messageId, uint32_t param2, uint32_t param3,
                                uint32_t param4, uint32_t param5, uint32_t param6 )
{
  server().queueForPlayer( player.getCharacterId(), makeActorControlTarget( player.getId(), ActorControlType::LogMsg, messageId,
                                                                            param2, param3, param4, param5, param6 ) );
}
