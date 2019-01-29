#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>

#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/GamePacketNew.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonNetwork.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Database/DatabaseDef.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>

#include "Zone.h"
#include "InstanceContent.h"
#include "Manager/TerritoryMgr.h"

#include "Session.h"
#include "Actor/Chara.h"
#include "Actor/Actor.h"
#include "Actor/BNpc.h"
#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Actor/SpawnGroup.h"
#include "Actor/SpawnPoint.h"

#include "Network/GameConnection.h"

#include "Script/ScriptMgr.h"

#include "Session.h"
#include "ForwardsZone.h"
#include "ServerMgr.h"
#include "CellHandler.h"
#include "Zone.h"
#include "Framework.h"

#include <Manager/RNGMgr.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

/**
* \brief
*/
Sapphire::Zone::Zone() :
  m_territoryTypeId( 0 ),
  m_guId( 0 ),
  m_currentWeather( Weather::FairSkies ),
  m_weatherOverride( Weather::None ),
  m_lastMobUpdate( 0 ),
  m_nextEObjId( 0x400D0000 ),
  m_nextActorId( 0x500D0000 )
{
}

Sapphire::Zone::Zone( uint16_t territoryTypeId, uint32_t guId,
                      const std::string& internalName, const std::string& placeName,
                      FrameworkPtr pFw ) :
  m_currentWeather( Weather::FairSkies ),
  m_nextEObjId( 0x400D0000 ),
  m_nextActorId( 0x500D0000 ),
  m_pFw( pFw )
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

void Sapphire::Zone::loadWeatherRates()
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

Sapphire::Zone::~Zone()
{
}

bool Sapphire::Zone::init()
{
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();

  if( pScriptMgr->onZoneInit( shared_from_this() ) )
  {
    // all good
  }

  return true;
}

void Sapphire::Zone::setWeatherOverride( Weather weather )
{
  m_weatherOverride = weather;
}

Weather Sapphire::Zone::getCurrentWeather() const
{
  return m_currentWeather;
}

const Sapphire::FestivalPair& Sapphire::Zone::getCurrentFestival() const
{
  return m_currentFestival;
}

void Sapphire::Zone::setCurrentFestival( uint16_t festivalId, uint16_t additionalFestivalId )
{
  m_currentFestival = { festivalId, additionalFestivalId };

  for( const auto& playerEntry : m_playerMap )
  {
    auto player = playerEntry.second;

    auto enableFestival = makeActorControl143( player->getId(), SetFestival, festivalId, additionalFestivalId );
    playerEntry.second->queuePacket( enableFestival );
  }
}

void Sapphire::Zone::loadCellCache()
{
}

Weather Sapphire::Zone::getNextWeather()
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

void Sapphire::Zone::pushActor( Entity::ActorPtr pActor )
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

  if( pActor->isPlayer() )
  {
    auto pPlayer = pActor->getAsPlayer();

    auto pServerZone = m_pFw->get< World::ServerMgr >();
    auto pSession = pServerZone->getSession( pPlayer->getId() );
    if( pSession )
      m_sessionSet.insert( pSession );
    m_playerMap[ pPlayer->getId() ] = pPlayer;
    updateCellActivity( cx, cy, 2 );
  }
  else if( pActor->isBattleNpc() )
  {
    auto pBNpc = pActor->getAsBNpc();

    m_bNpcMap[ pBNpc->getId() ] = pBNpc;
    updateCellActivity( cx, cy, 2 );

  }
}

void Sapphire::Zone::removeActor( Entity::ActorPtr pActor )
{
  float mx = pActor->getPos().x;
  float my = pActor->getPos().z;
  uint32_t cx = getPosX( mx );
  uint32_t cy = getPosY( my );

  Cell* pCell = getCellPtr( cx, cy );
  if( pCell && pCell->hasActor( pActor ) )
    pCell->removeActor( pActor );

  if( pActor->isPlayer() )
  {

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
    m_bNpcMap.erase( pActor->getId() );
  }

  // remove from lists of other actors
  pActor->removeFromInRange();
  pActor->clearInRangeSet();

}

void Sapphire::Zone::queuePacketForRange( Entity::Player& sourcePlayer, uint32_t range,
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

void Sapphire::Zone::queuePacketForZone( Entity::Player& sourcePlayer,
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

uint32_t Sapphire::Zone::getTerritoryTypeId() const
{
  return m_territoryTypeId;
}

uint32_t Sapphire::Zone::getGuId() const
{
  return m_guId;
}

const std::string& Sapphire::Zone::getName() const
{
  return m_placeName;
}

const std::string& Sapphire::Zone::getInternalName() const
{
  return m_internalName;
}

const std::string& Sapphire::Zone::getBgPath() const
{
  return m_bgPath;
}

std::size_t Sapphire::Zone::getPopCount() const
{
  return m_playerMap.size();
}

bool Sapphire::Zone::checkWeather()
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

void Sapphire::Zone::updateBNpcs( int64_t tickCount )
{
  if( ( tickCount - m_lastMobUpdate ) <= 250 )
    return;

  m_lastMobUpdate = tickCount;
  uint32_t currTime = Sapphire::Util::getTimeSeconds();

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
          actor->getAsBNpc()->update( tickCount );
      }
    }
  }
}


bool Sapphire::Zone::update( uint32_t currTime )
{
  int64_t tickCount = Util::getTimeMs();

  //TODO: this should be moved to a updateWeather call and pulled out of updateSessions
  bool changedWeather = checkWeather();

  updateSessions( changedWeather );
  updateBNpcs( tickCount );
  onUpdate( currTime );

  updateSpawnPoints();
  return true;
}

void Sapphire::Zone::updateSessions( bool changedWeather )
{
  auto it = m_sessionSet.begin();

  // update sessions in this zone
  for( ; it != m_sessionSet.end(); )
  {

    auto pSession = ( *it );

    if( !pSession )
    {
      it = m_sessionSet.erase( it );
      continue;
    }

    auto pPlayer = pSession->getPlayer();

    // this session is not linked to this area anymore, remove it from zone session list
    if( ( !pPlayer->getCurrentZone() ) || ( pPlayer->getCurrentZone() != shared_from_this() ) )
    {
      removeActor( pSession->getPlayer() );

      it = m_sessionSet.erase( it );
      continue;
    }

    if( changedWeather )
    {
      auto weatherChangePacket = makeZonePacket< FFXIVIpcWeatherChange >( pPlayer->getId() );
      weatherChangePacket->data().weatherId = static_cast< uint8_t >( m_currentWeather );
      weatherChangePacket->data().delay = 5.0f;
      pSession->getPlayer()->queuePacket( weatherChangePacket );
    }

    // perform session duties
    pSession->update();
    ++it;
  }
}

bool Sapphire::Zone::isCellActive( uint32_t x, uint32_t y )
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

void Sapphire::Zone::updateCellActivity( uint32_t x, uint32_t y, int32_t radius )
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

void Sapphire::Zone::updateActorPosition( Entity::Actor& actor )
{

  if( actor.getCurrentZone() != shared_from_this() )
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
      pOldCell->removeActor( actor.shared_from_this() );
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


void Sapphire::Zone::updateInRangeSet( Entity::ActorPtr pActor, Cell* pCell )
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

void Sapphire::Zone::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "Zone::onEnterTerritory: Zone#{0}|{1}, Entity#{2}", getGuId(), getTerritoryTypeId(), player.getId() );
}

void Sapphire::Zone::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "Zone::onLeaveTerritory: Zone#{0}|{1}, Entity#{2}", getGuId(), getTerritoryTypeId(), player.getId() );
}

void Sapphire::Zone::onUpdate( uint32_t currTime )
{

}

void Sapphire::Zone::onFinishLoading( Entity::Player& player )
{

}

void Sapphire::Zone::onInitDirector( Entity::Player& player )
{

}

void Sapphire::Zone::onEnterTerritory( Sapphire::Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{

}

void Sapphire::Zone::registerEObj( Entity::EventObjectPtr object )
{
  if( !object )
    return;

  pushActor( object );

  m_eventObjects[ object->getId() ] = object;

  onRegisterEObj( object );

  //Logger::debug( "Registered instance eobj: " + std::to_string( object->getId() ) );
}

Sapphire::Entity::EventObjectPtr Sapphire::Zone::getEObj( uint32_t objId )
{
  auto obj = m_eventObjects.find( objId );
  if( obj == m_eventObjects.end() )
    return nullptr;

  return obj->second;
}

Sapphire::InstanceContentPtr Sapphire::Zone::getAsInstanceContent()
{
  return std::dynamic_pointer_cast< InstanceContent, Zone >( shared_from_this() );
}

uint32_t Sapphire::Zone::getNextEObjId()
{
  return ++m_nextEObjId;
}

uint32_t Sapphire::Zone::getNextActorId()
{
  return ++m_nextActorId;
}


Sapphire::Entity::EventObjectPtr Sapphire::Zone::registerEObj( const std::string& name, uint32_t objectId, uint32_t mapLink,
                                                               uint8_t state, FFXIVARR_POSITION3 pos, float scale,
                                                               float rotation )
{
  auto eObj = Entity::make_EventObject( getNextEObjId(), objectId, mapLink, state, pos, rotation, name );
  eObj->setScale( scale );
  registerEObj( eObj );

  return eObj;
}

Sapphire::Data::TerritoryTypePtr Sapphire::Zone::getTerritoryTypeInfo() const
{
  return m_territoryTypeInfo;
}

bool Sapphire::Zone::loadSpawnGroups()
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

void Sapphire::Zone::updateSpawnPoints()
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

