#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>

#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/GamePacket.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonNetwork.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Database/DatabaseDef.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>

#include "Territory.h"
#include "InstanceContent.h"
#include "QuestBattle.h"
#include "Manager/TerritoryMgr.h"
#include "Navi/NaviProvider.h"

#include "Session.h"
#include "Actor/Chara.h"
#include "Actor/Actor.h"
#include "Actor/BNpc.h"
#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Actor/SpawnGroup.h"
#include "Actor/SpawnPoint.h"
#include "Actor/BNpcTemplate.h"

#include "Action/EffectResult.h"

#include "Network/GameConnection.h"

#include "Script/ScriptMgr.h"

#include "ForwardsZone.h"
#include "ServerMgr.h"
#include "CellHandler.h"
#include "Framework.h"

#include "Manager/RNGMgr.h"
#include "Manager/NaviMgr.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

/**
* \brief
*/
Sapphire::Territory::Territory() :
  m_territoryTypeId( 0 ),
  m_guId( 0 ),
  m_currentWeather( Weather::FairSkies ),
  m_weatherOverride( Weather::None ),
  m_lastMobUpdate( 0 ),
  m_nextEObjId( 0x400D0000 ),
  m_nextActorId( 0x500D0000 )
{
}

Sapphire::Territory::Territory( uint16_t territoryTypeId, uint32_t guId,
                                const std::string& internalName, const std::string& placeName,
                                FrameworkPtr pFw ) :
  m_currentWeather( Weather::FairSkies ),
  m_nextEObjId( 0x400D0000 ),
  m_nextActorId( 0x500D0000 ),
  m_pFw( pFw ),
  m_lastUpdate( 0 ),
  m_lastActivityTime( Util::getTimeMs() )
{
  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  m_guId = guId;

  m_territoryTypeId = territoryTypeId;
  m_internalName = internalName;
  m_placeName = placeName;
  m_lastMobUpdate = 0;

  m_weatherOverride = Weather::None;
  m_territoryTypeInfo = pExdData->get< Sapphire::Data::TerritoryType >( territoryTypeId );
  m_bgPath = m_territoryTypeInfo->bg;

  loadWeatherRates();
  loadSpawnGroups();

  m_currentWeather = getNextWeather();
}

void Sapphire::Territory::loadWeatherRates()
{
  if( !m_territoryTypeInfo )
    return;

  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();

  uint8_t weatherRateId = m_territoryTypeInfo->weatherRate > pExdData->getWeatherRateIdList().size() ?
                          uint8_t{ 0 } : m_territoryTypeInfo->weatherRate;

  uint8_t sumPc = 0;
  auto weatherRateFields = pExdData->m_WeatherRateDat.get_row( weatherRateId );
  for( size_t i = 0; i < 16; )
  {
    int32_t weatherId = std::get< int32_t >( weatherRateFields[ i ] );

    if( weatherId == 0 )
      break;

    sumPc += std::get< uint8_t >( weatherRateFields[ i + 1 ] );
    m_weatherRateMap[ sumPc ] = weatherId;
    i += 2;
  }
}

Sapphire::Territory::~Territory() = default;

bool Sapphire::Territory::init()
{
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();

  if( pScriptMgr->onZoneInit( shared_from_this() ) )
  {
    // all good
  }

  auto pNaviMgr = m_pFw->get< World::Manager::NaviMgr >();
  pNaviMgr->setupTerritory( m_territoryTypeInfo->bg );

  m_pNaviProvider = pNaviMgr->getNaviProvider( m_territoryTypeInfo->bg );

  if( !m_pNaviProvider )
  {
    Logger::warn( "No navmesh found for TerritoryType#{}", getTerritoryTypeId() );
  }

  return true;
}

void Sapphire::Territory::setWeatherOverride( Weather weather )
{
  m_weatherOverride = weather;
}

Weather Sapphire::Territory::getCurrentWeather() const
{
  return m_currentWeather;
}

const Sapphire::FestivalPair& Sapphire::Territory::getCurrentFestival() const
{
  return m_currentFestival;
}

void Sapphire::Territory::setCurrentFestival( uint16_t festivalId, uint16_t additionalFestivalId )
{
  m_currentFestival = { festivalId, additionalFestivalId };

  for( const auto& playerEntry : m_playerMap )
  {
    auto player = playerEntry.second;

    auto enableFestival = makeActorControl143( player->getId(), SetFestival, festivalId, additionalFestivalId );
    playerEntry.second->queuePacket( enableFestival );
  }
}

void Sapphire::Territory::loadCellCache()
{
}

Weather Sapphire::Territory::getNextWeather()
{
  uint32_t unixTime = Util::getTimeSeconds();
  // Get Eorzea hour for weather start
  uint32_t bell = unixTime / 175;
  // Do the magic 'cause for calculations 16:00 is 0, 00:00 is 8 and 08:00 is 16
  int32_t increment = ( ( bell + 8 - ( bell % 8 ) ) ) % 24;

  // Take Eorzea days since unix epoch
  uint32_t totalDays = ( unixTime / 4200 );

  uint32_t calcBase = ( totalDays * 0x64 ) + increment;

  uint32_t step1 = ( calcBase << 0xB ) ^calcBase;
  uint32_t step2 = ( step1 >> 8 ) ^step1;

  auto rate = static_cast< uint8_t >( step2 % 0x64 );

  for( auto entry : m_weatherRateMap )
  {
    uint8_t sRate = entry.first;
    auto weatherId = static_cast< Weather >( entry.second );

    if( rate <= sRate )
      return weatherId;
  }

  return Weather::FairSkies;
}

void Sapphire::Territory::pushActor( Entity::ActorPtr pActor )
{
  float mx = pActor->getPos().x;
  float my = pActor->getPos().z;
  uint32_t cx = getPosX( mx );
  uint32_t cy = getPosY( my );

  Cell* pCell = getCellPtr( cx, cy );
  if( !pCell )
  {
    pCell = create( cx, cy );
    pCell->init( cx, cy, shared_from_this() );
  }

  pCell->addActor( pActor );

  pActor->setCell( pCell );

  uint32_t cellX = getPosX( pActor->getPos().x );
  uint32_t cellY = getPosY( pActor->getPos().z );

  uint32_t endX = cellX <= _sizeX ? cellX + 1 : ( _sizeX - 1 );
  uint32_t endY = cellY <= _sizeY ? cellY + 1 : ( _sizeY - 1 );
  uint32_t startX = cellX > 0 ? cellX - 1 : 0;
  uint32_t startY = cellY > 0 ? cellY - 1 : 0;
  uint32_t posX, posY;

  for( posX = startX; posX <= endX; ++posX )
  {
    for( posY = startY; posY <= endY; ++posY )
    {
      pCell = getCellPtr( posX, posY );
      if( pCell )
        updateInRangeSet( pActor, pCell );
    }
  }

  int32_t agentId = -1;

  if( pActor->isPlayer() )
  {
    auto pPlayer = pActor->getAsPlayer();

    if( m_pNaviProvider )
      agentId = m_pNaviProvider->addAgent( *pPlayer );
    pPlayer->setAgentId( agentId );

    auto pServerZone = m_pFw->get< World::ServerMgr >();
    m_playerMap[ pPlayer->getId() ] = pPlayer;
    updateCellActivity( cx, cy, 2 );
  }
  else if( pActor->isBattleNpc() )
  {
    auto pBNpc = pActor->getAsBNpc();

    if( m_pNaviProvider )
      agentId = m_pNaviProvider->addAgent( *pBNpc );
    pBNpc->setAgentId( agentId );

    m_bNpcMap[ pBNpc->getId() ] = pBNpc;
    updateCellActivity( cx, cy, 2 );

  }
}

void Sapphire::Territory::removeActor( Entity::ActorPtr pActor )
{
  float mx = pActor->getPos().x;
  float my = pActor->getPos().z;
  uint32_t cx = getPosX( mx );
  uint32_t cy = getPosY( my );

  Cell* pCell = getCellPtr( cx, cy );
  if( pCell && pCell->hasActor( pActor ) )
    pCell->removeActorFromCell( pActor );

  if( pActor->isPlayer() )
  {

    if( m_pNaviProvider )
      m_pNaviProvider->removeAgent( *pActor->getAsChara() );

    // If it's a player and he's inside boundaries - update his nearby cells
    if( pActor->getPos().x <= _maxX && pActor->getPos().x >= _minX &&
        pActor->getPos().z <= _maxY && pActor->getPos().z >= _minY )
    {
      uint32_t x = getPosX( pActor->getPos().x );
      uint32_t y = getPosY( pActor->getPos().z );
      updateCellActivity( x, y, 3 );
    }
    m_playerMap.erase( pActor->getId() );

    onLeaveTerritory( *pActor->getAsPlayer() );

  }
  else if( pActor->isBattleNpc() )
  {
    if( m_pNaviProvider )
      m_pNaviProvider->removeAgent( *pActor->getAsChara() );
    m_bNpcMap.erase( pActor->getId() );
  }

  // remove from lists of other actors
  pActor->removeFromInRange();
  pActor->clearInRangeSet();

}

void Sapphire::Territory::queuePacketForRange( Entity::Player& sourcePlayer, uint32_t range,
                                          Network::Packets::FFXIVPacketBasePtr pPacketEntry )
{
  auto pTeriMgr = m_pFw->get< TerritoryMgr >();
  if( pTeriMgr->isPrivateTerritory( getTerritoryTypeId() ) )
    return;

  auto pServerZone = m_pFw->get< World::ServerMgr >();
  for( auto entry : m_playerMap )
  {
    auto player = entry.second;
    float distance = Util::distance( sourcePlayer.getPos().x, sourcePlayer.getPos().y, sourcePlayer.getPos().z,
                                     player->getPos().x, player->getPos().y, player->getPos().z );

    if( ( distance < range ) && sourcePlayer.getId() != player->getId() )
    {

      auto pSession = pServerZone->getSession( player->getId() );
      //pPacketEntry->setValAt< uint32_t >( 0x08, player->getId() );
      if( pSession )
        pSession->getZoneConnection()->queueOutPacket( pPacketEntry );
    }
  }
}

void Sapphire::Territory::queuePacketForZone( Entity::Player& sourcePlayer,
                                         Network::Packets::FFXIVPacketBasePtr pPacketEntry,
                                         bool forSelf )
{
  auto pTeriMgr = m_pFw->get< TerritoryMgr >();
  if( pTeriMgr->isPrivateTerritory( getTerritoryTypeId() ) )
    return;

  auto pServerZone = m_pFw->get< World::ServerMgr >();
  for( auto entry : m_playerMap )
  {
    auto player = entry.second;
    if( ( sourcePlayer.getId() != player->getId() ) ||
        ( ( sourcePlayer.getId() == player->getId() ) && forSelf ) )
    {
      auto pSession = pServerZone->getSession( player->getId() );
      if( pSession )
        pSession->getZoneConnection()->queueOutPacket( pPacketEntry );
    }
  }
}

uint32_t Sapphire::Territory::getTerritoryTypeId() const
{
  return m_territoryTypeId;
}

uint32_t Sapphire::Territory::getGuId() const
{
  return m_guId;
}

const std::string& Sapphire::Territory::getName() const
{
  return m_placeName;
}

const std::string& Sapphire::Territory::getInternalName() const
{
  return m_internalName;
}

const std::string& Sapphire::Territory::getBgPath() const
{
  return m_bgPath;
}

std::size_t Sapphire::Territory::getPopCount() const
{
  return m_playerMap.size();
}

bool Sapphire::Territory::checkWeather()
{
  if( m_weatherOverride != Weather::None )
  {
    if( m_weatherOverride != m_currentWeather )
    {
      m_currentWeather = m_weatherOverride;
      return true;
    }
  }
  else
  {
    auto nextWeather = getNextWeather();
    if( nextWeather != m_currentWeather )
    {
      m_currentWeather = nextWeather;
      return true;
    }
  }
  return false;
}

void Sapphire::Territory::updateBNpcs( uint64_t tickCount )
{
  if( ( tickCount - m_lastMobUpdate ) <= 250 )
    return;

  m_lastMobUpdate = tickCount;
  uint64_t currTime = Common::Util::getTimeSeconds();

  for( const auto& entry : m_bNpcMap )
  {
    Entity::BNpcPtr pBNpc = entry.second;

    if( !pBNpc )
      continue;

    if( !pBNpc->isAlive() )
      if( currTime - pBNpc->getTimeOfDeath() > 10 )
      {
        removeActor( pBNpc );
        break;
      }
  }

  // Update loop may move actors from cell to cell, breaking iterator validity
  std::vector< Entity::BNpcPtr > m_activeBNpc;

  for( uint32_t y = 0; y < _sizeY; ++y )
  {
    for( uint32_t x = 0; x < _sizeX; ++x )
    {
      auto cell = getCellPtr( x, y );
      if( !cell )
        continue;

      // todo: this is a pretty shit because we will visit the same cells multiple times over
      // ideally we run a pass every tick and cache active cells during that initial pass over every cell
      // that way we don't have an expensive lookup for every actor

      if( !isCellActive( x, y ) )
        continue;

      for( const auto& actor : cell->m_actors )
      {
        if( actor->isBattleNpc() )
          m_activeBNpc.push_back( actor->getAsBNpc() );
      }
    }
  }

  // iterate the cached active bnpcs
  for( const auto& actor : m_activeBNpc )
    actor->update( tickCount );

}

uint64_t Sapphire::Territory::getLastActivityTime() const
{
  return m_lastActivityTime;
}

bool Sapphire::Territory::update( uint64_t tickCount )
{
  //TODO: this should be moved to a updateWeather call and pulled out of updateSessions
  bool changedWeather = checkWeather();

  auto dt = std::difftime( tickCount, m_lastUpdate ) / 1000.f;

  if( m_pNaviProvider )
    m_pNaviProvider->updateCrowd( dt );

  updateSessions( tickCount, changedWeather );
  onUpdate( tickCount );

  updateSpawnPoints();

  processEffectResults( tickCount );

  if( !m_playerMap.empty() )
    m_lastActivityTime = tickCount;

  m_lastUpdate = tickCount;

  return true;
}

void Sapphire::Territory::updateSessions( uint64_t tickCount, bool changedWeather )
{
  // update sessions in this zone
  for( auto it = m_playerMap.begin(); it != m_playerMap.end(); ++it )
  {

    auto pPlayer = it->second;

    if( !pPlayer )
    {
      m_playerMap.erase( it );
      return;
    }

    // this session is not linked to this area anymore, remove it from zone session list
    if( ( !pPlayer->getCurrentTerritory() ) || ( pPlayer->getCurrentTerritory() != shared_from_this() ) )
    {
      removeActor( pPlayer );
      return;
    }

    if( changedWeather )
    {
      auto weatherChangePacket = makeZonePacket< FFXIVIpcWeatherChange >( pPlayer->getId() );
      weatherChangePacket->data().weatherId = static_cast< uint8_t >( m_currentWeather );
      weatherChangePacket->data().delay = 5.0f;
      pPlayer->queuePacket( weatherChangePacket );
    }

    // perform session duties
    pPlayer->getSession()->update();

    // this session is not linked to this area anymore, remove it from zone session list
    if( ( !pPlayer->getCurrentTerritory() ) || ( pPlayer->getCurrentTerritory() != shared_from_this() ) )
      return;
  }
}

bool Sapphire::Territory::isCellActive( uint32_t x, uint32_t y )
{
  uint32_t endX = ( ( x + 1 ) <= _sizeX ) ? x + 1 : ( _sizeX - 1 );
  uint32_t endY = ( ( y + 1 ) <= _sizeY ) ? y + 1 : ( _sizeY - 1 );
  uint32_t startX = x > 0 ? x - 1 : 0;
  uint32_t startY = y > 0 ? y - 1 : 0;
  uint32_t posX;
  uint32_t posY;

  Cell* pCell;

  for( posX = startX; posX <= endX; posX++ )
  {
    for( posY = startY; posY <= endY; posY++ )
    {
      pCell = getCellPtr( posX, posY );

      if( pCell && ( pCell->hasPlayers() || pCell->isForcedActive() ) )
        return true;
    }
  }

  return false;
}

void Sapphire::Territory::updateCellActivity( uint32_t x, uint32_t y, int32_t radius )
{

  uint32_t endX = ( x + radius ) <= _sizeX ? x + radius : ( _sizeX - 1 );
  uint32_t endY = ( y + radius ) <= _sizeY ? y + radius : ( _sizeY - 1 );
  uint32_t startX = x - radius > 0 ? x - radius : 0;
  uint32_t startY = y - radius > 0 ? y - radius : 0;
  uint32_t posX, posY;

  Cell* pCell;

  for( posX = startX; posX <= endX; posX++ )
  {
    for( posY = startY; posY <= endY; posY++ )
    {
      pCell = getCellPtr( posX, posY );

      if( !pCell )
      {
        if( isCellActive( posX, posY ) )
        {
          pCell = create( posX, posY );
          pCell->init( posX, posY, shared_from_this() );

          pCell->setActivity( true );

          assert( !pCell->isLoaded() );

        }
      }
      else
      {
        //Cell is now active
        if( isCellActive( posX, posY ) && !pCell->isActive() )
        {
          pCell->setActivity( true );

          if( !pCell->isLoaded() )
          {

          }
        }
        else if( !isCellActive( posX, posY ) && pCell->isActive() )
          pCell->setActivity( false );
      }
    }
  }
}

void Sapphire::Territory::updateActorPosition( Entity::Actor& actor )
{

  if( actor.getCurrentTerritory() != shared_from_this() )
    return;

  //actor.checkInRangeActors();

  uint32_t cellX = getPosX( actor.getPos().x );
  uint32_t cellY = getPosY( actor.getPos().z );

  if( cellX >= _sizeX || cellY >= _sizeY )
    return;

  auto pCell = getCellPtr( cellX, cellY );

  auto pOldCell = actor.getCellPtr();
  if( !pCell )
  {
    pCell = create( cellX, cellY );
    pCell->init( cellX, cellY, shared_from_this() );
  }

  // If object moved cell
  if( pCell != pOldCell )
  {

    if( pOldCell )
    {
      pOldCell->removeActorFromCell( actor.shared_from_this() );
    }

    pCell->addActor( actor.shared_from_this() );
    actor.setCell( pCell );
    pOldCell = pCell;

    // if player we need to update cell activity
    // radius = 2 is used in order to update both
    // old and new cells
    if( actor.isPlayer() )
    {
      updateCellActivity( cellX, cellY, 2 );
      if( pOldCell != nullptr )
      {
        // only do the second check if theres -/+ 2 difference
        if( abs( ( int32_t ) cellX - ( int32_t ) pOldCell->m_posX ) > 2 ||
            abs( ( int32_t ) cellY - ( int32_t ) pOldCell->m_posY ) > 2 )
          updateCellActivity( pOldCell->m_posX, pOldCell->m_posY, 2 );
      }
    }
  }

  // update in range actor set
  uint32_t endX = cellX <= _sizeX ? cellX + 1 : ( _sizeX - 1 );
  uint32_t endY = cellY <= _sizeY ? cellY + 1 : ( _sizeY - 1 );
  uint32_t startX = cellX > 0 ? cellX - 1 : 0;
  uint32_t startY = cellY > 0 ? cellY - 1 : 0;
  uint32_t posX, posY;

  for( posX = startX; posX <= endX; ++posX )
  {
    for( posY = startY; posY <= endY; ++posY )
    {
      pCell = getCellPtr( posX, posY );
      if( pCell )
        updateInRangeSet( actor.shared_from_this(), pCell );
    }
  }
}


void Sapphire::Territory::updateInRangeSet( Entity::ActorPtr pActor, Cell* pCell )
{
  if( pCell == nullptr )
    return;

  auto pTeriMgr = m_pFw->get< TerritoryMgr >();
  // TODO: make sure gms can overwrite this. Potentially temporary solution
  if( pTeriMgr->isPrivateTerritory( getTerritoryTypeId() ) )
    return;

  auto iter = pCell->m_actors.begin();

  float fRange = pTeriMgr->getInRangeDistance();
  int32_t count = 0;
  while( iter != pCell->m_actors.end() )
  {
    auto pCurAct = *iter;
    ++iter;

    if( !pCurAct || pCurAct == pActor )
      continue;

    float distance = Util::distance( pCurAct->getPos(), pActor->getPos() );

    bool isInRange = ( fRange == 0.0f || distance <= fRange );
    bool isInRangeSet = pActor->isInRangeSet( pCurAct );

    // Add if range == 0 or distance is withing range.
    if( isInRange && !isInRangeSet )
    {

      if( pActor->isPlayer() && !pActor->getAsPlayer()->isLoadingComplete() )
        continue;

      if( pCurAct->isPlayer() && !pCurAct->getAsPlayer()->isLoadingComplete() )
        continue;

      pActor->addInRangeActor( pCurAct );
      pCurAct->addInRangeActor( pActor );

    }
    else if( !isInRange && isInRangeSet )
    {
      pCurAct->removeInRangeActor( *pActor );
      pActor->removeInRangeActor( *pCurAct );
    }
  }
}

void Sapphire::Territory::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "Territory::onEnterTerritory: Territory#{0}|{1}, Entity#{2}", getGuId(), getTerritoryTypeId(), player.getId() );
}

void Sapphire::Territory::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "Territory::onLeaveTerritory: Territory#{0}|{1}, Entity#{2}", getGuId(), getTerritoryTypeId(), player.getId() );
}

void Sapphire::Territory::onUpdate( uint64_t tickCount )
{
  updateBNpcs( tickCount );
}

void Sapphire::Territory::onFinishLoading( Entity::Player& player )
{

}

void Sapphire::Territory::onInitDirector( Entity::Player& player )
{

}

void Sapphire::Territory::onEnterTerritory( Sapphire::Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{

}

void Sapphire::Territory::registerEObj( Entity::EventObjectPtr object )
{
  if( !object )
    return;

  pushActor( object );

  m_eventObjects[ object->getId() ] = object;

  onRegisterEObj( object );

  //Logger::debug( "Registered instance eobj: " + std::to_string( object->getId() ) );
}

Sapphire::Entity::EventObjectPtr Sapphire::Territory::getEObj( uint32_t objId )
{
  auto obj = m_eventObjects.find( objId );
  if( obj == m_eventObjects.end() )
    return nullptr;

  return obj->second;
}

Sapphire::InstanceContentPtr Sapphire::Territory::getAsInstanceContent()
{
  return std::dynamic_pointer_cast< InstanceContent, Territory >( shared_from_this() );
}

Sapphire::QuestBattlePtr Sapphire::Territory::getAsQuestBattle()
{
  return std::dynamic_pointer_cast< QuestBattle, Territory >( shared_from_this() );
}

uint32_t Sapphire::Territory::getNextEObjId()
{
  return ++m_nextEObjId;
}

uint32_t Sapphire::Territory::getNextActorId()
{
  return ++m_nextActorId;
}


Sapphire::Entity::EventObjectPtr Sapphire::Territory::registerEObj( const std::string& name, uint32_t objectId, uint32_t mapLink,
                                                               uint8_t state, FFXIVARR_POSITION3 pos, float scale,
                                                               float rotation )
{
  auto eObj = Entity::make_EventObject( getNextEObjId(), objectId, mapLink, state, pos, rotation, name );
  eObj->setScale( scale );
  registerEObj( eObj );

  return eObj;
}

Sapphire::Data::TerritoryTypePtr Sapphire::Territory::getTerritoryTypeInfo() const
{
  return m_territoryTypeInfo;
}

bool Sapphire::Territory::loadSpawnGroups()
{
  auto pDb = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto stmt = pDb->getPreparedStatement( Db::ZoneDbStatements::ZONE_SEL_SPAWNGROUPS );
  stmt->setUInt( 1, getTerritoryTypeId() );
  auto res = pDb->query( stmt );

  while( res->next() )
  {
    uint32_t id = res->getUInt( 1 );
    uint32_t templateId = res->getUInt( 2 );
    uint32_t level = res->getUInt( 3 );
    uint32_t maxHp = res->getUInt( 4 );

    m_spawnGroups.emplace_back( id, templateId, level, maxHp );

    Logger::trace( "id: {0}, template: {1}, level: {2}, maxHp: {3}", id, m_spawnGroups.back().getTemplateId(), level, maxHp );
  }

  res.reset();
  stmt.reset();

  stmt = pDb->getPreparedStatement( Db::ZoneDbStatements::ZONE_SEL_SPAWNPOINTS );
  for( auto& group : m_spawnGroups )
  {
    stmt->setUInt( 1, group.getId() );
    auto res = pDb->query( stmt );

    while( res->next() )
    {
      uint32_t id = res->getUInt( 1 );
      float x = res->getFloat( 2 );
      float y = res->getFloat( 3 );
      float z = res->getFloat( 4 );
      float r = res->getFloat( 5 );
      uint32_t gimmickId = res->getUInt( 6 );

      group.getSpawnPointList().emplace_back( std::make_shared< Entity::SpawnPoint >( x, y, z, r, gimmickId ) );

      Logger::trace( "id: {0}, x: {1}, y: {2}, z: {3}, gimmickId: {4}", id, x, y, z, gimmickId );
    }
  }
  return false;
}

void Sapphire::Territory::updateSpawnPoints()
{
  auto pRNGMgr = m_pFw->get< World::Manager::RNGMgr >();
  auto rng = pRNGMgr->getRandGenerator< float >( 0.f, PI * 2 );

  for( auto& group : m_spawnGroups )
  {
    for( auto& point : group.getSpawnPointList() )
    {
      if( !point->getLinkedBNpc() && ( Util::getTimeSeconds() - point->getTimeOfDeath() ) > 60 )
      {
        auto serverZone = m_pFw->get< World::ServerMgr >();

        auto bNpcTemplate = serverZone->getBNpcTemplate( group.getTemplateId() );

        if( !bNpcTemplate )
        {
          //Logger::error( "No template found for templateId#{0}", group.getTemplateId() );
          continue;
        }

        auto pBNpc = std::make_shared< Entity::BNpc >( getNextActorId(),
                                                       bNpcTemplate,
                                                       point->getPosX(),
                                                       point->getPosY(),
                                                       point->getPosZ(),
                                                       rng.next(),
                                                       group.getLevel(),
                                                       group.getMaxHp(), shared_from_this(), m_pFw );
        point->setLinkedBNpc( pBNpc );

        pushActor( pBNpc );
      }
      else if( point->getLinkedBNpc() && !point->getLinkedBNpc()->isAlive() )
      {
        point->setTimeOfDeath( Util::getTimeSeconds() );
        point->setLinkedBNpc( nullptr );
      }
    }
  }

}

uint32_t Sapphire::Territory::getNextEffectSequence()
{
  return m_effectCounter++;
}

Sapphire::Entity::BNpcPtr
  Sapphire::Territory::createBNpcFromLevelEntry( uint32_t levelId, uint8_t level, uint8_t type,
                                            uint32_t hp, uint16_t nameId, uint32_t directorId,
                                            uint8_t bnpcType )
{
  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  auto levelData = pExdData->get< Sapphire::Data::Level >( levelId );
  if( !levelData )
    return nullptr;

  if( levelData->type != 9 )
    return nullptr;

  auto bnpcBaseId = levelData->object;

  auto bnpcBaseData = pExdData->get< Sapphire::Data::BNpcBase >( bnpcBaseId );
  if( !bnpcBaseData )
    return nullptr;

  //BNpcTemplate( uint32_t id, uint32_t baseId, uint32_t nameId, uint64_t weaponMain, uint64_t weaponSub,
  //  uint8_t aggressionMode, uint8_t enemyType, uint8_t onlineStatus, uint8_t pose,
  //  uint16_t modelChara, uint32_t displayFlags, uint32_t* modelEquip,
  //  uint8_t* customize )

  std::vector< uint8_t > customize( 26 );
  if( bnpcBaseData->bNpcCustomize != 0 )
  {
    auto bnpcCustomizeData = pExdData->get< Sapphire::Data::BNpcCustomize >( bnpcBaseData->bNpcCustomize );
    if( bnpcCustomizeData )
    {
      customize[0] = bnpcCustomizeData->race;
      customize[1] = bnpcCustomizeData->gender;
      customize[2] = bnpcCustomizeData->bodyType;
      customize[3] = bnpcCustomizeData->height;
      customize[4] = bnpcCustomizeData->tribe;
      customize[5] = bnpcCustomizeData->face;
      customize[6] = bnpcCustomizeData->hairStyle;
      customize[7] = bnpcCustomizeData->hairHighlight;
      customize[8] = bnpcCustomizeData->skinColor;
      customize[9] = bnpcCustomizeData->eyeHeterochromia;
      customize[10] = bnpcCustomizeData->hairColor;
      customize[11] = bnpcCustomizeData->hairHighlightColor;
      customize[12] = bnpcCustomizeData->facialFeature;
      customize[13] = bnpcCustomizeData->facialFeatureColor;
      customize[14] = bnpcCustomizeData->eyebrows;
      customize[15] = bnpcCustomizeData->eyeColor;
      customize[16] = bnpcCustomizeData->eyeShape;
      customize[17] = bnpcCustomizeData->nose;
      customize[18] = bnpcCustomizeData->jaw;
      customize[19] = bnpcCustomizeData->mouth;
      customize[20] = bnpcCustomizeData->lipColor;
      customize[21] = bnpcCustomizeData->bustOrTone1;
      customize[22] = bnpcCustomizeData->extraFeature1;
      customize[23] = bnpcCustomizeData->extraFeature2OrBust;
      customize[24] = bnpcCustomizeData->facePaint;
      customize[25] = bnpcCustomizeData->facePaintColor;
    }
  }

  std::vector< uint32_t > models( 10 );
  uint64_t modelMain = 0;
  uint64_t modeloff = 0;
  if( bnpcBaseData->npcEquip != 0 )
  {
    auto npcEquipData = pExdData->get< Sapphire::Data::NpcEquip >( bnpcBaseData->npcEquip );
    if( npcEquipData )
    {
      modelMain = npcEquipData->modelMainHand;
      modeloff = npcEquipData->modelOffHand;

      models[0] = npcEquipData->modelHead;
      models[1] = npcEquipData->modelBody;
      models[2] = npcEquipData->modelHands;
      models[3] = npcEquipData->modelLegs;
      models[4] = npcEquipData->modelFeet;
      models[5] = npcEquipData->modelEars;
      models[6] = npcEquipData->modelNeck;
      models[7] = npcEquipData->modelWrists;
      models[8] = npcEquipData->modelLeftRing;
      models[9] = npcEquipData->modelRightRing;
    }
  }

  auto tmp = std::make_shared< Entity::BNpcTemplate >( 0, bnpcBaseId, nameId, modelMain, modeloff, 1, bnpcType, 0, 4,
                                                       bnpcBaseData->modelChara, 0, &models[0], &customize[0] );

  auto bnpc = std::make_shared< Entity::BNpc >( getNextActorId(), tmp, levelData->x, levelData->y, levelData->z,
                                                levelData->yaw, level, hp, shared_from_this(), m_pFw );

  bnpc->setDirectorId( directorId );
  bnpc->setLevelId( levelId );
  pushActor( bnpc );
  return bnpc;
}

Sapphire::Entity::BNpcPtr Sapphire::Territory::getActiveBNpcByLevelId( uint32_t levelId )
{
  for( const auto& bnpcIt : m_bNpcMap )
  {
    if( bnpcIt.second->getLevelId() == levelId )
      return bnpcIt.second;
  }
  return nullptr;
}

std::shared_ptr< Sapphire::World::Navi::NaviProvider > Sapphire::Territory::getNaviProvider()
{
  return m_pNaviProvider;
}

void Sapphire::Territory::addEffectResult( Sapphire::World::Action::EffectResultPtr result )
{
  m_effectResults.emplace_back( std::move( result ) );
}

void Sapphire::Territory::processEffectResults( uint64_t tickCount )

{
  // todo: move this to generic territory/instance delay wrapper cause it might be useful scheduling other things
  for( auto it = m_effectResults.begin(); it != m_effectResults.end(); )
  {
    auto effect = *it;

    if( tickCount < effect->getDelay() )
    {
      ++it;
      continue;
    }

    effect->execute();

    it = m_effectResults.erase( it );
  }
}