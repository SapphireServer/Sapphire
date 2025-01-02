#include "PlayerMgr.h"

#include <Service.h>

#include <Exd/ExdData.h>
#include <Util/Util.h>
#include <Territory/Land.h>

#include <Manager/TerritoryMgr.h>
#include <Manager/HousingMgr.h>
#include <Manager/QuestMgr.h>

#include <Script/ScriptMgr.h>
#include <Common.h>

#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>

#include <Network/CommonActorControl.h>
#include <Network/Util/PacketUtil.h>

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
    onUpdateHuntingLog( player, bnpc.getBNpcNameId() );
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

  Network::Util::Packet::sendLogin( player );

  player.sendInventory();

  if( player.isLogin() )
  {
    Network::Util::Packet::sendActorControlSelf( player, player.getId(), SetConfigFlags, player.getConfigFlags(), 1 );
    Network::Util::Packet::sendActorControlSelf( player, player.getId(), SetMaxGearSets, player.getMaxGearSets() );
  }

  // set flags, will be reset automatically by zoning ( only on client side though )
  //setStateFlag( PlayerStateFlag::BetweenAreas );
  //setStateFlag( PlayerStateFlag::BetweenAreas1 );

  Network::Util::Packet::sendHuntingLog( player );

  if( player.isLogin() )
    Network::Util::Packet::sendPlayerSetup( player );

  Network::Util::Packet::sendRecastGroups( player );
  Network::Util::Packet::sendBaseParams( player );
  Network::Util::Packet::sendActorControl( player, player.getId(), SetItemLevel, player.getItemLevel() );
  if( player.isLogin() )
  {
    Network::Util::Packet::sendChangeClass( player );
    Network::Util::Packet::sendActorControl( player, player.getId(), 0x112, 0x24 ); // unknown
    Network::Util::Packet::sendContentAttainFlags( player );
    player.clearSoldItems();
  }

  housingMgr.sendLandFlags( player );

  Network::Util::Packet::sendInitZone( player );

  if( player.isLogin() )
  {
    Network::Util::Packet::sendDailyQuests( player );
    Network::Util::Packet::sendQuestRepeatFlags( player );

    auto &questMgr = Common::Service< World::Manager::QuestMgr >::ref();
    questMgr.sendQuestsInfo( player );
    Network::Util::Packet::sendGrandCompany( player );
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

  checkAutoAttack( player, tickCount );
}

void PlayerMgr::checkAutoAttack( Entity::Player& player, uint64_t tickCount ) const
{
  auto mainWeap = player.getItemAt( Common::GearSet0, Common::MainHand );
  if( !mainWeap || player.checkAction() || !player.isAutoattackOn() || !player.getTargetId() || player.getStance() != Common::Active )
    return;

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

    if( ( Common::Util::distance( player.getPos(), actor->getPos() ) <= range ) &&
        ( ( tickCount - player.getLastAttack() ) > mainWeap->getDelay() ) )
    {
      player.setLastAttack( tickCount );
      player.autoAttack( actor->getAsChara() );
    }
  }

}

void PlayerMgr::onGainExp( Entity::Player& player, uint32_t exp )
{
  uint32_t currentExp = player.getCurrentExp();
  uint16_t level = player.getLevel();
  auto currentClass = static_cast< uint8_t >( player.getClass() );

  if( level >= Common::MAX_PLAYER_LEVEL )
  {
    player.setCurrentExp( 0 );
    if( currentExp != 0 )
      Network::Util::Packet::sendActorControlSelf( player, player.getId(), UpdateUiExp, currentClass, 0 );

    return;
  }
  auto& exdData = Common::Service< Data::ExdData >::ref();

  uint32_t neededExpToLevel = exdData.getRow< Excel::ParamGrow >( level )->data().NextExp;
  uint32_t neededExpToLevelPlus1 = exdData.getRow< Excel::ParamGrow >( level + 1 )->data().NextExp;

  if( ( currentExp + exp ) >= neededExpToLevel )
  {
    // levelup
    exp = ( currentExp + exp - neededExpToLevel ) > neededExpToLevelPlus1 ? neededExpToLevelPlus1 - 1 : ( currentExp + exp - neededExpToLevel );

    if( level + 1 >= Common::MAX_PLAYER_LEVEL )
      exp = 0;

    player.setCurrentExp( exp );
    player.levelUp();
  }
  else
    player.setCurrentExp( currentExp + exp );

  Network::Util::Packet::sendActorControlSelf( player, player.getId(), GainExpMsg, currentClass, exp );
  Network::Util::Packet::sendActorControlSelf( player, player.getId(), UpdateUiExp, currentClass, player.getCurrentExp() );
}

void PlayerMgr::onDiscoverArea( Entity::Player& player, int16_t mapId, int16_t subId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  int32_t offset;

  auto info = exdData.getRow< Excel::Map >( mapId );
  if( !info )
  {
    sendDebug( player, "discover(): Could not obtain map data for map_id == {0}", mapId );
    return;
  }

  const auto& mapData = info->data();

  if( mapData.IsUint16Discovery )
    offset = 2 * mapData.DiscoveryIndex;
  else
    offset = 320 + 4 * mapData.DiscoveryIndex;

  uint16_t index;
  uint8_t value;
  Common::Util::valueToFlagByteIndexValue( subId, value, index );

  auto& discovery = player.getDiscoveryBitmask();

  discovery[ offset + index ] |= value;

  uint16_t level = player.getLevel();

  uint32_t exp = ( exdData.getRow< Excel::ParamGrow >( level )->data().NextExp * 5 / 100 );
  onGainExp( player, exp );

  // gain 10x additional EXP if entire map is completed
  uint32_t mask = mapData.DiscoveryFlag;
  uint32_t discoveredAreas;
  if( info->data().IsUint16Discovery )
  {
    discoveredAreas = ( discovery[ offset + 1 ] << 8 ) | discovery[ offset ];
  }
  else
  {
    discoveredAreas = ( discovery[ offset + 3 ] << 24 ) |
                      ( discovery[ offset + 2 ] << 16 ) |
                      ( discovery[ offset + 1 ] << 8  ) |
                        discovery[ offset ];
  }

  bool allDiscovered = ( ( discoveredAreas & mask ) == mask );

  if( allDiscovered )
  {
    onGainExp( player, exp * 10 );
  }
}


////////// Helper ///////////

void PlayerMgr::sendServerNotice( Entity::Player& player, const std::string& message ) //Purple Text
{
  Network::Util::Packet::sendServerNotice( player, message );
}

void PlayerMgr::sendUrgent( Entity::Player& player, const std::string& message ) //Red Text
{
  Network::Util::Packet::sendChat( player, Common::ChatType::ServerUrgent, message );
}

void PlayerMgr::sendDebug( Entity::Player& player, const std::string& message ) //Grey Text
{
  Network::Util::Packet::sendChat( player, Common::ChatType::SystemMessage, message );
}

void PlayerMgr::sendLogMessage( Entity::Player& player, uint32_t messageId, uint32_t param2, uint32_t param3,
                                uint32_t param4, uint32_t param5, uint32_t param6 )
{
  Network::Util::Packet::sendActorControlTarget( player, player.getId(), LogMsg, messageId, param2, param3, param4, param5, param6 );
}

void PlayerMgr::onUpdateHuntingLog( Entity::Player& player, uint8_t id )
{
  std::vector< uint32_t > rankRewards{ 2500, 10000, 20000, 30000, 40000 };
  const auto maxRank = 4;
  auto& pExdData = Common::Service< Data::ExdData >::ref();

  // make sure we get the matching base-class if a job is being used
  auto classJobInfo = pExdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( player.getClass() ) );
  if( !classJobInfo )
    return;

  auto currentClassId = classJobInfo->data().MainClass;

  auto& logEntry = player.getHuntingLogEntry( currentClassId - 1 );

  bool logChanged = false;


  bool allSectionsComplete = true;
  for( int i = 1; i <= 10; ++i )
  {
    bool sectionComplete = true;
    bool sectionChanged = false;
    auto monsterNoteId = static_cast< uint32_t >( classJobInfo->data().MainClass * 10000 + logEntry.rank * 10 + i );
    auto note = pExdData.getRow< Excel::MonsterNote >( monsterNoteId );

    // for classes that don't have entries, if the first fails the rest will fail
    if( !note )
      break;

    for( auto x = 0; x < 4; ++x )
    {
      auto note1 = pExdData.getRow< Excel::MonsterNoteTarget >( note->data().Target[ x ] );
      if( note1->data().Monster == id && logEntry.entries[ i - 1 ][ x ] < note->data().NeededKills[ x ] )
      {
        logEntry.entries[ i - 1 ][ x ]++;
        Network::Util::Packet::sendActorControlSelf( player, player.getId(), HuntingLogEntryUpdate, monsterNoteId, x, logEntry.entries[ i - 1 ][ x ] );
        logChanged = true;
        sectionChanged = true;
      }
      if( logEntry.entries[ i - 1 ][ x ] != note->data().NeededKills[ x ] )
        sectionComplete = false;
    }
    if( logChanged && sectionComplete && sectionChanged )
    {
      Network::Util::Packet::sendActorControlSelf( player, player.getId(), HuntingLogSectionFinish, monsterNoteId, i, 0 );
      onGainExp( player, note->data().RewardExp );
    }
    if( !sectionComplete )
    {
      allSectionsComplete = false;
    }
  }
  if( logChanged && allSectionsComplete )
  {
    Network::Util::Packet::sendActorControlSelf( player, player.getId(), HuntingLogRankFinish, 4 );
    onGainExp( player, rankRewards[ logEntry.rank ] );
    if( logEntry.rank < 4 )
    {
      logEntry.rank++;
      memset( logEntry.entries, 0, 40 );
      Network::Util::Packet::sendActorControlSelf( player, player.getId(), HuntingLogRankUnlock, currentClassId, logEntry.rank + 1, 0 );
    }
  }

  if( logChanged )
    Network::Util::Packet::sendHuntingLog( player );
}



