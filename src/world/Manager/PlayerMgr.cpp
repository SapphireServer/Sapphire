#include "PlayerMgr.h"

#include <Service.h>

#include <Exd/ExdData.h>

#include <Territory/Land.h>

#include <Manager/TerritoryMgr.h>
#include <Manager/AchievementMgr.h>
#include <Manager/PartyMgr.h>
#include <Manager/HousingMgr.h>
#include <Manager/QuestMgr.h>

#include <Script/ScriptMgr.h>
#include <Common.h>

#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>

#include <Network/GameConnection.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlPacket.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Network/PacketWrappers/ActorControlTargetPacket.h>
#include <Network/PacketWrappers/InitZonePacket.h>
#include <Network/PacketWrappers/PlayerSetupPacket.h>
#include <Network/PacketWrappers/ServerNoticePacket.h>
#include <Network/PacketWrappers/ChatPacket.h>
#include <Network/PacketWrappers/HudParamPacket.h>
#include <Network/Util/PlayerUtil.h>

#include <Actor/Player.h>
#include <Actor/BNpc.h>

#include <Inventory/Item.h>

#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;


Sapphire::Entity::PlayerPtr PlayerMgr::getPlayer( uint32_t entityId )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_playerMapById.find( entityId );

  if( it != m_playerMapById.end() )
    return ( it->second );

  // not found (new character?) - we'll load from DB and hope it's there
  return loadPlayer( entityId );
}

Sapphire::Entity::PlayerPtr PlayerMgr::getPlayer( uint64_t characterId )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_playerMapByCharacterId.find( characterId );

  if( it != m_playerMapByCharacterId.end() )
    return ( it->second );

  // not found (new character?) - we'll load from DB and hope it's there
  return loadPlayer( characterId );
}

Sapphire::Entity::PlayerPtr PlayerMgr::getPlayer( const std::string& playerName )
{
  //std::lock_guard<std::mutex> lock( m_sessionMutex );
  auto it = m_playerMapByName.find( playerName );

  if( it != m_playerMapByName.end() )
    return ( it->second );

  // not found (new character?) - we'll load from DB and hope it's there
  return loadPlayer( playerName );
}

std::vector< Sapphire::Entity::PlayerPtr > PlayerMgr::searchPlayersByName( const std::string& playerName )
{
  std::vector< Sapphire::Entity::PlayerPtr > results{};

  for( auto& it : m_playerMapByName )
  {
    if( it.first.find( playerName ) != std::string::npos )
      results.push_back( it.second );
  }
  return results;
}


std::string PlayerMgr::getPlayerNameFromDb( uint64_t characterId, bool forceDbLoad )
{
  if( !forceDbLoad )
  {
    auto it = m_playerMapByCharacterId.find( characterId );

    if( it != m_playerMapByCharacterId.end() )
      return ( it->second->getName() );
  }

  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT name FROM charainfo WHERE characterid = " + std::to_string( characterId ) );

  if( !res->next() )
    return "Unknown";

  std::string playerName = res->getString( 1 );

  return playerName;
}


Sapphire::Entity::PlayerPtr PlayerMgr::addPlayer( uint64_t characterId )
{
  auto pPlayer = Entity::make_Player();

  if( !pPlayer->loadFromDb( characterId ) )
    return nullptr;

  m_playerMapById[ pPlayer->getId() ] = pPlayer;
  m_playerMapByCharacterId[ pPlayer->getCharacterId() ] = pPlayer;
  m_playerMapByName[ pPlayer->getName() ] = pPlayer;

  return pPlayer;
}

Sapphire::Entity::PlayerPtr PlayerMgr::loadPlayer( uint32_t entityId )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT CharacterId FROM charainfo WHERE EntityId = " + std::to_string( entityId ) );
  if( !res || !res->next() )
    return nullptr;

  uint64_t characterId = res->getUInt64( 1 );

  return addPlayer( characterId );
}

Sapphire::Entity::PlayerPtr PlayerMgr::loadPlayer( uint64_t characterId )
{
  return addPlayer( characterId );
}

Sapphire::Entity::PlayerPtr PlayerMgr::loadPlayer( const std::string& playerName )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT CharacterId FROM charainfo WHERE Name = " + playerName );
  if( !res || !res->next() )
    return nullptr;

  uint64_t characterId = res->getUInt64( 1 );

  return addPlayer( characterId );
}

bool PlayerMgr::loadPlayers()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT CharacterId FROM charainfo" );

  // no players or failed
  while( res->next() )
  {
    uint64_t characterId = res->getUInt64( 1 );
    if( !addPlayer( characterId ) )
      return false;
  }

  return true;
}

Sapphire::Entity::PlayerPtr PlayerMgr::syncPlayer( uint64_t characterId )
{
  auto pPlayer = getPlayer( characterId );
  if( !pPlayer )
    return nullptr;

  // get our cached last db write
  auto lastCacheSync = pPlayer->getLastDBWrite();

  // update this player's last db write
  if( !pPlayer->syncLastDBWrite() )
    return nullptr;

  // get db last write
  auto dbSync = pPlayer->getLastDBWrite();


  // db was updated and we lost track of it  - update
  // @todo for now, always reload the player on login.
  //if( dbSync != lastCacheSync )
  {
    // clear current maps
    m_playerMapById[ pPlayer->getId() ] = nullptr;
    m_playerMapByName[ pPlayer->getName() ] = nullptr;
    m_playerMapByCharacterId[ pPlayer->getCharacterId() ] = nullptr;

    if( !pPlayer->loadFromDb( characterId ) )
      return nullptr;

    m_playerMapById[ pPlayer->getId() ] = pPlayer;
    m_playerMapByCharacterId[ pPlayer->getCharacterId() ] = pPlayer;
    m_playerMapByName[ pPlayer->getName() ] = pPlayer;
  }

  return pPlayer;
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

void PlayerMgr::sendLoginMessage( Entity::Player& player )
{
  auto motd = server().getConfig().motd;

  std::istringstream ss( motd );
  std::string msg;
  while( std::getline( ss, msg, ';' ) )
  {
    sendServerNotice( player, msg );
  }
}

void PlayerMgr::onLogin( Entity::Player &player )
{
}

void PlayerMgr::onLogout( Entity::Player &player )
{
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

  auto pZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  if( !pZone )
  {
    Logger::error( "Territory GuID#{} not found!", player.getTerritoryId() );
    return;
  }
  auto& teri = *pZone;

  Network::Util::Player::sendLogin( player );

  player.sendInventory();

  if( player.isLogin() )
  {
    Network::Util::Player::sendActorControlSelf( player, SetConfigFlags, player.getConfigFlags(), 1 );
    Network::Util::Player::sendActorControlSelf( player, SetMaxGearSets, player.getMaxGearSets() );
  }

  // set flags, will be reset automatically by zoning ( only on client side though )
  //setStateFlag( PlayerStateFlag::BetweenAreas );
  //setStateFlag( PlayerStateFlag::BetweenAreas1 );

  Network::Util::Player::sendHuntingLog( player );

  if( player.isLogin() )
    Network::Util::Player::sendPlayerSetup( player );

  Network::Util::Player::sendRecastGroups( player );
  Network::Util::Player::sendBaseParams( player );
  Network::Util::Player::sendActorControl( player, SetItemLevel, player.getItemLevel() );
  if( player.isLogin() )
  {
    Network::Util::Player::sendChangeClass( player );
    Network::Util::Player::sendActorControl( player, 0x112, 0x24 ); // unknown
    Network::Util::Player::sendContentAttainFlags( player );
    player.clearSoldItems();
  }

  housingMgr.sendLandFlags( player );

  Network::Util::Player::sendInitZone( player );

  if( player.isLogin() )
  {
    Network::Util::Player::sendDailyQuests( player );
    Network::Util::Player::sendQuestRepeatFlags( player );

    auto &questMgr = Common::Service< World::Manager::QuestMgr >::ref();
    questMgr.sendQuestsInfo( player );
    Network::Util::Player::sendGrandCompany( player );
  }

  teri.onPlayerZoneIn( player );

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

  auto mainWeap = player.getItemAt( Common::GearSet0, Common::GearSetSlot::MainHand );
  if( mainWeap && !player.checkAction() && ( player.getTargetId() && player.getStance() == Common::Stance::Active && player.isAutoattackOn() ) )
  {
    // @TODO i dislike this, iterating over all in range actors when you already know the id of the actor you need...
    for( const auto& actor : player.getInRangeActors() )
    {
      if( actor->getId() != player.getTargetId() || !actor->getAsChara()->isAlive() )
        continue;
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
