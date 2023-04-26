#include <stdio.h>
#include <vector>
#include <time.h>
#include <random>

#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/GamePacket.h>
#include <Exd/ExdData.h>
#include <Network/CommonNetwork.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Database/DatabaseDef.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Service.h>

#include "Territory.h"
#include "InstanceContent.h"
#include "QuestBattle.h"
#include "Manager/TerritoryMgr.h"
#include "Navi/NaviProvider.h"

#include "Session.h"
#include "Actor/Chara.h"
#include "Actor/GameObject.h"
#include "Actor/BNpc.h"
#include "Actor/Player.h"
#include "Actor/EventObject.h"

#include "Action/ActionResult.h"

#include "Network/GameConnection.h"

#include "Script/ScriptMgr.h"

#include "ForwardsZone.h"
#include "WorldServer.h"
#include "CellHandler.h"

#include "Manager/RNGMgr.h"
#include "Manager/NaviMgr.h"
#include "Math/CalcStats.h"

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

#define START_EOBJ_ID 0x400D0000
#define START_GAMEOBJECT_ID 0x500D0000

Territory::Territory() :
  m_territoryTypeId( 0 ),
  m_ident(),
  m_guId( 0 ),
  m_currentWeather( Common::Weather::FairSkies ),
  m_weatherOverride( Common::Weather::None ),
  m_lastMobUpdate( 0 ),
  m_nextEObjId( START_EOBJ_ID ),
  m_nextActorId( START_GAMEOBJECT_ID ),
  m_inRangeDistance( 80.f )
{
}

Territory::Territory( uint16_t territoryTypeId, uint32_t guId, const std::string& internalName, const std::string& placeName ) :
  m_currentWeather( Common::Weather::FairSkies ),
  m_nextEObjId( START_EOBJ_ID ),
  m_nextActorId( START_GAMEOBJECT_ID ),
  m_lastUpdate( 0 ),
  m_lastActivityTime( Common::Util::getTimeMs() ),
  m_inRangeDistance( 80.f )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  m_guId = guId;

  m_territoryTypeId = territoryTypeId;
  m_internalName = internalName;
  m_placeName = placeName;
  m_lastMobUpdate = 0;

  m_weatherOverride = Common::Weather::None;
  m_territoryTypeInfo = exdData.getRow< Excel::TerritoryType >( territoryTypeId );
  m_bgPath = m_territoryTypeInfo->getString( m_territoryTypeInfo->data().LVB );

  m_ident.territoryTypeId = territoryTypeId;
  loadWeatherRates();

  loadBNpcs();

  m_currentWeather = getNextWeather();
}

void Territory::loadWeatherRates()
{
  if( !m_territoryTypeInfo )
    return;

  auto& exdData = Common::Service< Data::ExdData >::ref();

  uint8_t weatherRateId = m_territoryTypeInfo->data().WeatherRate > exdData.getIdList< Excel::WeatherRate >().size() ?
                          uint8_t{ 0 } : m_territoryTypeInfo->data().WeatherRate;

  uint8_t sumPc = 0;
  auto weatherRate = exdData.getRow< Excel::WeatherRate >( weatherRateId );
  for( size_t i = 0; i < 8; ++i )
  {
    int32_t weatherId = weatherRate->data().WeatherId[ i ];

    if( weatherId == 0 )
      break;

    sumPc += weatherRate->data().Rate[ i ];
    m_weatherRateMap[ sumPc ] = weatherId;
  }
}

Territory::~Territory() = default;

bool Territory::init()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  if( scriptMgr.onZoneInit( *this ) )
  {
    // all good
  }

  auto& naviMgr = Common::Service< NaviMgr >::ref();
  std::string lvb = m_territoryTypeInfo->getString( m_territoryTypeInfo->data().LVB );

  naviMgr.setupTerritory( lvb, m_guId );

  m_pNaviProvider = naviMgr.getNaviProvider( lvb, m_guId );

  if( !m_pNaviProvider )
  {
    Logger::warn( "No navmesh found for TerritoryType#{}", getTerritoryTypeId() );
  }

  onUpdate( 0 );

  return true;
}

void Territory::setWeatherOverride( Common::Weather weather )
{
  m_weatherOverride = weather;
}

Common::Weather Territory::getCurrentWeather() const
{
  return m_currentWeather;
}

const FestivalPair& Territory::getCurrentFestival() const
{
  return m_currentFestival;
}

void Territory::setCurrentFestival( uint16_t festivalId, uint16_t additionalFestivalId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  m_currentFestival = { festivalId, additionalFestivalId };

  for( const auto& playerEntry : m_playerMap )
  {
    auto player = playerEntry.second;

    auto enableFestival = makeActorControlSelf( player->getId(), SetFestival, festivalId, additionalFestivalId );
    server.queueForPlayer( playerEntry.second->getCharacterId(), enableFestival );
  }
}

Common::Weather Territory::getNextWeather()
{
  uint32_t unixTime = Common::Util::getTimeSeconds();
  // Get Eorzea hour for weather start
  uint32_t bell = unixTime / 175;
  // Do the magic 'cause for calculations 16:00 is 0, 00:00 is 8 and 08:00 is 16
  uint32_t increment = ( ( bell + 8 - ( bell % 8 ) ) ) % 24;

  // Take Eorzea days since unix epoch
  uint32_t totalDays = ( unixTime / 4200 );

  uint32_t calcBase = ( totalDays * 0x64 ) + increment;

  uint32_t step1 = ( calcBase << 0xB ) ^calcBase;
  uint32_t step2 = ( step1 >> 8 ) ^step1;

  auto rate = static_cast< uint8_t >( step2 % 0x64 );

  for( auto entry : m_weatherRateMap )
  {
    uint8_t sRate = entry.first;
    auto weatherId = static_cast< Common::Weather >( entry.second );

    if( rate <= sRate )
      return weatherId;
  }

  return Common::Weather::FairSkies;
}

void Territory::pushActor( const Entity::GameObjectPtr& pActor )
{
  float mx = pActor->getPos().x;
  float my = pActor->getPos().z;
  uint32_t cx = getPosX( mx );
  uint32_t cy = getPosY( my );

  CellPtr pCell = getCellPtr( cx, cy );
  if( !pCell )
  {
    pCell = create( cx, cy );
    pCell->init( cx, cy );
  }

  pCell->addActor( pActor );

  pActor->setCellId( { cx, cy } );

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

    m_playerMap[ pPlayer->getId() ] = pPlayer;
    updateCellActivity( cx, cy, 1 );
  }
  else if( pActor->isBattleNpc() )
  {
    auto pBNpc = pActor->getAsBNpc();

    if( m_pNaviProvider )
      agentId = m_pNaviProvider->addAgent( *pBNpc );
    pBNpc->setAgentId( agentId );

    m_bNpcMap[ pBNpc->getId() ] = pBNpc;
    updateCellActivity( cx, cy, 1 );

  }
  else if( pActor->isEventObj() )
  {
    auto pEObj = pActor->getAsEventObj();

    m_eventObjects[ pEObj->getId() ] = pEObj;
  }
}

void Territory::removeActor( const Entity::GameObjectPtr& pActor )
{
  auto cellId = pActor->getCellId();
  CellPtr pCell = getCellPtr( cellId.x, cellId.y );
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
  else if( pActor->isEventObj() )
  {
    m_eventObjects.erase( pActor->getId() );
  }

  // remove from lists of other actors
  pActor->removeFromInRange();
  pActor->clearInRangeSet();

}

void Territory::queuePacketForRange( Entity::Player& sourcePlayer, float range, Network::Packets::FFXIVPacketBasePtr pPacketEntry )
{
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  if( teriMgr.isPrivateTerritory( getTerritoryTypeId() ) )
    return;

  auto& server = Common::Service< World::WorldServer >::ref();

  for( const auto& entry : m_playerMap )
  {
    auto player = entry.second;
    float distance = Common::Util::distance( sourcePlayer.getPos(), player->getPos() );

    if( ( distance < range ) && sourcePlayer.getId() != player->getId() )
    {
      server.queueForPlayer( player->getCharacterId(), pPacketEntry );
    }
  }
}

void Territory::queuePacketForZone( Entity::Player& sourcePlayer, Network::Packets::FFXIVPacketBasePtr pPacketEntry, bool forSelf )
{
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  if( teriMgr.isPrivateTerritory( getTerritoryTypeId() ) )
    return;

  auto& server = Common::Service< World::WorldServer >::ref();

  for( const auto& entry : m_playerMap )
  {
    auto player = entry.second;
    if( ( sourcePlayer.getId() != player->getId() ) || ( ( sourcePlayer.getId() == player->getId() ) && forSelf ) )
    {
      server.queueForPlayer( player->getCharacterId(), pPacketEntry );
    }
  }
}

uint32_t Territory::getTerritoryTypeId() const
{
  return m_territoryTypeId;
}

uint32_t Territory::getGuId() const
{
  return m_guId;
}

const std::string& Territory::getName() const
{
  return m_placeName;
}

const std::string& Territory::getInternalName() const
{
  return m_internalName;
}

const std::string& Territory::getBgPath() const
{
  return m_bgPath;
}

std::size_t Territory::getPopCount() const
{
  return m_playerMap.size();
}

bool Territory::checkWeather()
{
  if( m_weatherOverride != Common::Weather::None )
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

void Territory::updateBNpcs( uint64_t tickCount )
{
  if( ( tickCount - m_lastMobUpdate ) <= 250 )
    return;

  m_lastMobUpdate = tickCount;
  uint64_t currTime = Common::Util::getTimeSeconds();

  // Update loop may move actors from cell to cell, breaking iterator validity
  std::vector< Entity::BNpcPtr > activeBNpc;

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
          activeBNpc.push_back( actor->getAsBNpc() );
      }
    }
  }

  // iterate the cached active bnpcs
  for( const auto& actor : activeBNpc )
    actor->update( tickCount );

}

uint64_t Territory::getLastActivityTime() const
{
  return m_lastActivityTime;
}

bool Territory::update( uint64_t tickCount )
{
  //TODO: this should be moved to a updateWeather call and pulled out of updateSessions
  bool changedWeather = checkWeather();

  auto dt = static_cast< float >( std::difftime( tickCount, m_lastUpdate ) / 1000.f );

  if( m_pNaviProvider )
    m_pNaviProvider->updateCrowd( dt );

  updateSessions( tickCount, changedWeather );
  onUpdate( tickCount );

  if( !m_playerMap.empty() )
    m_lastActivityTime = tickCount;

  m_lastUpdate = tickCount;

  return true;
}

void Territory::updateSessions( uint64_t tickCount, bool changedWeather )
{
  auto& server = Common::Service< World::WorldServer >::ref();
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
    if( pPlayer->getTerritoryId() != m_guId || !pPlayer->isConnected() )
    {
      Logger::debug( "[{}] removeActor( pPlayer );", pPlayer->getId() );
      removeActor( pPlayer );
      return;
    }

    if( changedWeather )
    {
      auto weatherChangePacket = makeZonePacket< FFXIVIpcWeatherId >( pPlayer->getId() );
      weatherChangePacket->data().WeatherId = static_cast< uint8_t >( m_currentWeather );
      weatherChangePacket->data().TransitionTime = 5.0f;
      server.queueForPlayer( pPlayer->getCharacterId(), weatherChangePacket );
    }

    // perform session duties
    auto playerSession = server.getSession( pPlayer->getCharacterId() );
    if( playerSession )
    {
      playerSession->update();
    }

    // this session is not linked to this area anymore, remove it from zone session list
    if( pPlayer->getTerritoryId() != getGuId() )
      return;
  }
}

bool Territory::isCellActive( uint32_t x, uint32_t y )
{
  uint32_t endX = ( ( x + 1 ) <= _sizeX ) ? x + 1 : ( _sizeX - 1 );
  uint32_t endY = ( ( y + 1 ) <= _sizeY ) ? y + 1 : ( _sizeY - 1 );
  uint32_t startX = x > 0 ? x - 1 : 0;
  uint32_t startY = y > 0 ? y - 1 : 0;
  uint32_t posX;
  uint32_t posY;

  CellPtr pCell;
  uint32_t time = Common::Util::getTimeSeconds();

  for( posX = startX; posX <= endX; posX++ )
  {
    for( posY = startY; posY <= endY; posY++ )
    {
      pCell = getCellPtr( posX, posY );

      if( pCell && ( pCell->hasPlayers() || pCell->isForcedActive() || ( time - pCell->getLastActiveTime() ) < 20 ) )
        return true;
    }
  }

  return false;
}

void Territory::updateCellActivity( uint32_t x, uint32_t y, int32_t radius )
{

  uint32_t endX = ( x + radius ) <= _sizeX ? x + radius : ( _sizeX - 1 );
  uint32_t endY = ( y + radius ) <= _sizeY ? y + radius : ( _sizeY - 1 );
  uint32_t startX = x - radius > 0 ? x - radius : 0;
  uint32_t startY = y - radius > 0 ? y - radius : 0;
  uint32_t posX, posY;

  CellPtr pCell;

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
          pCell->init( posX, posY );
          pCell->setActivity( true );
          pCell->setLastActiveTime( Common::Util::getTimeSeconds() );
        }
      }
      else
      {
        pCell->setLastActiveTime( Common::Util::getTimeSeconds() );
        //Cell is now active
        if( isCellActive( posX, posY ) && !pCell->isActive() )
        {
          pCell->setActivity( true );
        }
        else if( !isCellActive( posX, posY ) && pCell->isActive() )
          pCell->setActivity( false );
      }

    }
  }
}

void Territory::updateActorPosition( Entity::GameObject& actor )
{

  if( actor.getTerritoryTypeId() != getTerritoryTypeId() )
    return;

  //actor.checkInRangeActors();

  uint32_t cellX = getPosX( actor.getPos().x );
  uint32_t cellY = getPosY( actor.getPos().z );

  if( cellX >= _sizeX || cellY >= _sizeY )
    return;

  auto pCell = getCellPtr( cellX, cellY );
  auto oldCellId = actor.getCellId();
  auto pOldCell = getCellPtr( oldCellId.x, oldCellId.y );
  if( !pCell )
  {
    pCell = create( cellX, cellY );
    pCell->init( cellX, cellY );
  }

  // If object moved cell
  if( pCell != pOldCell )
  {

    if( pOldCell )
    {
      pOldCell->removeActorFromCell( actor.shared_from_this() );
    }

    pCell->addActor( actor.shared_from_this() );
    actor.setCellId( { cellX, cellY } );
    pOldCell = pCell;

    // if player we need to update cell activity
    // radius = 2 is used in order to update both
    // old and new cells
    if( actor.isPlayer() )
    {
      updateCellActivity( cellX, cellY, 2 );
      if( pOldCell )
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

float Territory::getInRangeDistance()
{
  return m_inRangeDistance;
}


void Territory::updateInRangeSet( Entity::GameObjectPtr pActor, CellPtr pCell )
{
  if( pCell == nullptr )
    return;

  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  // TODO: make sure gms can overwrite this. Potentially temporary solution
  if( teriMgr.isPrivateTerritory( getTerritoryTypeId() ) )
    return;

  auto iter = pCell->m_actors.begin();

  float fRange = getInRangeDistance();
  int32_t count = 0;
  while( iter != pCell->m_actors.end() )
  {
    auto pCurAct = *iter;
    ++iter;

    if( !pCurAct || pCurAct == pActor )
      continue;

    float distance = Common::Util::distance( pCurAct->getPos(), pActor->getPos() );

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

void Territory::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "[{2}] Territory::onEnterTerritory: Territory#{0}|{1}", getGuId(), getTerritoryTypeId(), player.getId() );
}

void Territory::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "[{2}] Territory::onLeaveTerritory: Territory#{0}|{1}", getGuId(), getTerritoryTypeId(), player.getId() );
}

void Territory::onUpdate( uint64_t tickCount )
{
  updateSpawnPoints();
  updateBNpcs( tickCount );
}

void Territory::onFinishLoading( Entity::Player& player )
{

}

void Territory::onInitDirector( Entity::Player& player )
{

}

void Territory::onEnterTerritory( Sapphire::Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{

}

void Territory::addEObj( Entity::EventObjectPtr object )
{
  if( !object )
    return;

  pushActor( object );

  onAddEObj( object );

  //Logger::debug( "Registered instance eobj: " + std::to_string( object->getId() ) );
}

Entity::EventObjectPtr Territory::getEObj( uint32_t objId )
{
  auto obj = m_eventObjects.find( objId );
  if( obj == m_eventObjects.end() )
    return nullptr;

  return obj->second;
}

InstanceContentPtr Territory::getAsInstanceContent()
{
  return std::dynamic_pointer_cast< InstanceContent, Territory >( shared_from_this() );
}

QuestBattlePtr Territory::getAsQuestBattle()
{
  return std::dynamic_pointer_cast< QuestBattle, Territory >( shared_from_this() );
}

uint32_t Territory::getNextEObjId()
{
  return ++m_nextEObjId;
}

uint32_t Territory::getNextActorId()
{
  return ++m_nextActorId;
}

Entity::EventObjectPtr Territory::addEObj( const std::string& name, uint32_t objectId, uint32_t mapLink, uint32_t instanceId,
                                           uint8_t state, Common::FFXIVARR_POSITION3 pos, float scale,
                                           float rotation, uint8_t permissionInv )
{
  auto eObj = Entity::make_EventObject( getNextEObjId(), objectId, mapLink, instanceId, state, pos, rotation, name, permissionInv );
  eObj->setScale( scale );

  addEObj( eObj );

  return eObj;
}

std::shared_ptr< Excel::ExcelStruct< Excel::TerritoryType > > Territory::getTerritoryTypeInfo() const
{
  return m_territoryTypeInfo;
}

void Territory::updateSpawnPoints()
{
  auto& server = Common::Service< World::WorldServer >::ref();

  for( auto& spawn : m_spawnInfo )
  {
    if( !spawn.bnpcPtr && ( Common::Util::getTimeSeconds() - spawn.timeOfDeath ) > spawn.infoPtr->PopInterval )
    {
      auto pBNpc = std::make_shared< Entity::BNpc >( getNextActorId(), spawn.infoPtr, *this );
      pBNpc->init();
      spawn.bnpcPtr = pBNpc;

      pushActor( pBNpc );
    }
    else if( spawn.bnpcPtr && !spawn.bnpcPtr->isAlive() )
    {
      spawn.timeOfDeath = Common::Util::getTimeSeconds();
      spawn.bnpcPtr.reset();
    }
  }
}

uint32_t Territory::getNextActionResultId()
{
  return m_effectCounter++;
}

Entity::BNpcPtr Territory::createBNpcFromLayoutId( uint32_t layoutId, uint32_t hp, Common::BNpcType bnpcType, uint32_t triggerOwnerId )
{
  auto infoPtr = m_bNpcBaseMap.find( layoutId );
  if( infoPtr == m_bNpcBaseMap.end() )
    return nullptr;

  auto pBNpc = std::make_shared< Entity::BNpc >( getNextActorId(), infoPtr->second, *this, hp, bnpcType );
  pBNpc->init();
  pBNpc->setTriggerOwnerId( triggerOwnerId );
  pushActor( pBNpc );
  return pBNpc;
}

Entity::BNpcPtr Territory::getActiveBNpcByEntityId( uint32_t entityId )
{
  auto it = m_bNpcMap.find( entityId );
  if( it == m_bNpcMap.end() )
    return nullptr;

  return it->second;
}

Entity::BNpcPtr Territory::getActiveBNpcByLayoutId( uint32_t instanceId )
{
  for( const auto& bnpcIt : m_bNpcMap )
  {
    if( bnpcIt.second->getLayoutId() == instanceId )
      return bnpcIt.second;
  }
  return nullptr;
}

Entity::BNpcPtr Territory::getActiveBNpcByLayoutIdAndTriggerOwner( uint32_t instanceId, uint32_t triggerOwnerId )
{
  for( const auto& bnpcIt : m_bNpcMap )
  {
    if( bnpcIt.second->getLayoutId() == instanceId && bnpcIt.second->getTriggerOwnerId() == triggerOwnerId )
      return bnpcIt.second;
  }
  return nullptr;
}

std::shared_ptr< World::Navi::NaviProvider > Territory::getNaviProvider()
{
  return m_pNaviProvider;
}

bool Territory::loadBNpcs()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::ZONE_SEL_BNPCS_BY_TERI );
  stmt->setUInt( 1, getTerritoryTypeId() );
  auto res = db.query( stmt );

  while( res->next() )
  {
    auto bnpc = std::make_shared< Common::BNPCInstanceObject >();

    bnpc->territoryType = res->getInt( 1 );
    bnpc->bnpcName = res->getString( 3 );
    bnpc->instanceId = res->getInt( 4 );
    bnpc->x = res->getFloat( 5 );
    bnpc->y = res->getFloat( 6 );
    bnpc->z = res->getFloat( 7 );
    bnpc->BaseId = res->getInt( 8 );
    bnpc->PopWeather = res->getInt( 9 );
    bnpc->PopTimeStart = res->getInt( 10 );
    bnpc->PopTimeEnd = res->getInt( 11 );
    bnpc->MoveAI = res->getInt( 12 );
    bnpc->WanderingRange = res->getInt( 13 );
    bnpc->Route = res->getInt( 14 );
    bnpc->EventGroup = res->getInt( 15 );
    bnpc->NameId = res->getInt( 16 );
    bnpc->DropItem = res->getInt( 17 );
    bnpc->SenseRangeRate = res->getFloat( 18 );
    bnpc->Level = res->getInt( 19 );
    bnpc->ActiveType = res->getInt( 20 );
    bnpc->PopInterval = res->getInt( 21 );
    bnpc->PopRate = res->getInt( 22 );
    bnpc->PopEvent = res->getInt( 23 );
    bnpc->LinkGroup = res->getInt( 24 );
    bnpc->LinkFamily = res->getInt( 25 );
    bnpc->LinkRange = res->getInt( 26 );
    bnpc->LinkCountLimit = res->getInt( 27 );
    bnpc->NonpopInitZone = res->getInt( 28 );
    bnpc->InvalidRepop = res->getInt( 29 );
    bnpc->LinkParent = res->getInt( 30 );
    bnpc->LinkOverride = res->getInt( 31 );
    bnpc->LinkReply = res->getInt( 32 );
    bnpc->HorizontalPopRange = res->getFloat( 33 );
    bnpc->VerticalPopRange = res->getFloat( 34 );
    bnpc->BNpcBaseData = res->getInt( 35 );
    bnpc->RepopId = res->getInt( 36 );
    bnpc->BNPCRankId = res->getInt( 37 );
    bnpc->TerritoryRange = res->getInt( 38 );
    bnpc->BoundInstanceID = res->getInt( 39 );
    bnpc->FateLayoutLabelId = res->getInt( 40 );
    bnpc->NormalAI = res->getInt( 41 );
    bnpc->ServerPathId = res->getInt( 42 );
    bnpc->EquipmentID = res->getInt( 43 );
    bnpc->CustomizeID = res->getInt( 44 );
    bnpc->rotation = res->getFloat( 45 );
    bnpc->Nonpop = res->getInt( 46 );

    m_bNpcBaseMap[ bnpc->instanceId ] = bnpc;

    if( bnpc->Nonpop != 1 )
    {
      SpawnInfo info;
      info.bnpcPtr = nullptr;
      info.infoPtr = bnpc;
      info.lastSpawn = 0;
      info.timeOfDeath = 0;

      m_spawnInfo.emplace_back( info );
    }

  }
  return true;
}

void Territory::onEventHandlerOrder( Entity::Player& player, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4 )
{

}

const Common::TerritoryIdent& Territory::getTerritoryIdent() const
{
  return m_ident;
}
