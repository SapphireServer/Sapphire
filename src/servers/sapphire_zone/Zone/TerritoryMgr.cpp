#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>

#include <unordered_map>

#include "Actor/Player.h"

#include "Zone.h"
#include "HousingZone.h"
#include "ZonePosition.h"
#include "InstanceContent.h"
#include "TerritoryMgr.h"
#include "Framework.h"

extern Core::Framework g_fw;

Core::TerritoryMgr::TerritoryMgr() :
  m_lastInstanceId( 10000 )
{

}

void Core::TerritoryMgr::loadTerritoryTypeDetailCache()
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto idList = pExdData->getTerritoryTypeIdList();

  for( auto id : idList )
  {
    auto teri1 = pExdData->get< Core::Data::TerritoryType >( id );

    if( !teri1->name.empty() )
      m_territoryTypeDetailCacheMap[ id ] = teri1;
  }
}

bool Core::TerritoryMgr::isValidTerritory( uint32_t territoryTypeId ) const
{
  return !( m_territoryTypeDetailCacheMap.find( territoryTypeId ) == m_territoryTypeDetailCacheMap.end() );
}

bool Core::TerritoryMgr::init()
{
  loadTerritoryTypeDetailCache();
  loadTerritoryPositionMap();

  createDefaultTerritories();
  createHousingTerritories();

  return true;
}

uint32_t Core::TerritoryMgr::getNextInstanceId()
{
  return ++m_lastInstanceId;
}

Core::Data::TerritoryTypePtr Core::TerritoryMgr::getTerritoryDetail( uint32_t territoryTypeId ) const
{
  auto tIt = m_territoryTypeDetailCacheMap.find( territoryTypeId );
  if( tIt == m_territoryTypeDetailCacheMap.end() )
    return nullptr;

  return tIt->second;
}

bool Core::TerritoryMgr::isInstanceContentTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  auto intendedUse = pTeri->territoryIntendedUse;

  return intendedUse == TerritoryIntendedUse::AllianceRaid ||
         intendedUse == TerritoryIntendedUse::BeforeTrialDung ||
         intendedUse == TerritoryIntendedUse::Trial ||
         intendedUse == TerritoryIntendedUse::Dungeon ||
         intendedUse == TerritoryIntendedUse::OpenWorldInstanceBattle ||
         intendedUse == TerritoryIntendedUse::PalaceOfTheDead ||
         intendedUse == TerritoryIntendedUse::RaidFights ||
         intendedUse == TerritoryIntendedUse::Raids ||
         intendedUse == TerritoryIntendedUse::TreasureMapInstance ||
         intendedUse == TerritoryIntendedUse::EventTrial;
}

bool Core::TerritoryMgr::isPrivateTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->territoryIntendedUse == TerritoryIntendedUse::OpeningArea ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::Inn ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::HousingPrivateArea ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::JailArea ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::MSQPrivateArea;
}


bool Core::TerritoryMgr::createDefaultTerritories()
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto pLog = g_fw.get< Logger >();
  // for each entry in territoryTypeExd, check if it is a normal and if so, add the zone object
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryId = territory.first;
    auto territoryInfo = territory.second;

    // if the zone has no name set
    if( territoryInfo->name.empty() )
      continue;

    auto pPlaceName = pExdData->get< Core::Data::PlaceName >( territoryInfo->placeName );

    if( !pPlaceName || pPlaceName->name.empty() || !isDefaultTerritory( territoryId ) )
      continue;

    uint32_t guid = getNextInstanceId();
    pLog->info( std::to_string( territoryId ) +
                "\t" + std::to_string( guid ) +
                "\t" + std::to_string( territoryInfo->territoryIntendedUse ) +
                "\t" + ( territoryInfo->name.length() <= 4 ? territoryInfo->name + "\t" : territoryInfo->name ) +
                "\t" + ( isPrivateTerritory( territoryId ) ? "PRIVATE" : "PUBLIC" ) +
                "\t" + pPlaceName->name );

    auto pZone = make_Zone( territoryId, guid, territoryInfo->name, pPlaceName->name );
    pZone->init();

    InstanceIdToZonePtrMap instanceMap;
    instanceMap[ guid ] = pZone;
    m_instanceIdToZonePtrMap[ guid ] = pZone;
    m_territoryIdToInstanceGuidMap[ territoryId ] = instanceMap;
    m_zoneSet.insert( { pZone } );

  }

  return true;
}

bool Core::TerritoryMgr::createHousingTerritories()
{
  //separate housing zones from default
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto pLog = g_fw.get< Logger >();
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryId = territory.first;
    auto territoryInfo = territory.second;
    uint32_t wardNum;
    uint32_t wardMaxNum = 1;

    if( territoryInfo->name.empty() )
      continue;

    auto pPlaceName = pExdData->get< Core::Data::PlaceName >( territoryInfo->placeName );

    if( !pPlaceName || pPlaceName->name.empty() || !isHousingTerritory( territoryId ) )
      continue;

    for( wardNum = 0; wardNum < wardMaxNum; wardNum++ )
    {
      uint32_t guid = getNextInstanceId();
      pLog->info( std::to_string( territoryId ) +
                  "\t" + std::to_string( guid ) +
                  "\t" + std::to_string( territoryInfo->territoryIntendedUse ) +
                  "\t" + ( territoryInfo->name.length() <= 4 ? territoryInfo->name + "\t" : territoryInfo->name ) +
                  "\t" + "HOUSING" +
                  "\t" + pPlaceName->name +
                  "#" + std::to_string( wardNum ) );

      auto pHousingZone = make_HousingZone( wardNum, territoryId, guid, territoryInfo->name, pPlaceName->name );
      pHousingZone->init();
      wardMaxNum = pHousingZone->m_wardMaxNum;

      InstanceIdToZonePtrMap instanceMap;
      instanceMap[ guid ] = pHousingZone;
      m_instanceIdToZonePtrMap[ guid ] = pHousingZone;
      m_territoryIdToInstanceGuidMap[ territoryId ][ guid ] = pHousingZone;
      m_zoneSet.insert( { pHousingZone } );
    }

  }

  return true;
}

Core::ZonePtr Core::TerritoryMgr::createTerritoryInstance( uint32_t territoryTypeId )
{
  if( !isValidTerritory( territoryTypeId ) )
    return nullptr;

  if( isInstanceContentTerritory( territoryTypeId ) )
    return nullptr;

  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto pLog = g_fw.get< Logger >();
  auto pTeri = getTerritoryDetail( territoryTypeId );
  auto pPlaceName = pExdData->get< Core::Data::PlaceName >( pTeri->placeName );

  if( !pTeri || !pPlaceName )
    return nullptr;

  pLog->debug(
    "Starting instance for territory: " + std::to_string( territoryTypeId ) + " (" + pPlaceName->name + ")" );

  auto pZone = make_Zone( territoryTypeId, getNextInstanceId(), pTeri->name, pPlaceName->name );
  pZone->init();

  m_instanceIdToZonePtrMap[ pZone->getGuId() ] = pZone;
  m_territoryIdToInstanceGuidMap[ pZone->getTerritoryId() ][ pZone->getGuId() ] = pZone;
  m_zoneSet.insert( { pZone } );

  return pZone;
}

Core::ZonePtr Core::TerritoryMgr::createInstanceContent( uint32_t contentFinderConditionId )
{

  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto pContentFinderCondition = pExdData->get< Core::Data::ContentFinderCondition >( contentFinderConditionId );
  if( !pContentFinderCondition )
    return nullptr;
  auto instanceContentId = pContentFinderCondition->instanceContent;

  auto pInstanceContent = pExdData->get< Core::Data::InstanceContent >( instanceContentId );
  if( !pInstanceContent )
    return nullptr;

  if( !isInstanceContentTerritory( pContentFinderCondition->territoryType ) )
    return nullptr;

  auto pTeri = getTerritoryDetail( pContentFinderCondition->territoryType );

  if( !pTeri || pInstanceContent->name.empty() )
    return nullptr;

  auto pLog = g_fw.get< Logger >();
  pLog->debug( "Starting instance for InstanceContent id: " + std::to_string( instanceContentId ) +
               " (" + pInstanceContent->name + ")" );

  auto pZone = make_InstanceContent( pInstanceContent, pContentFinderCondition->territoryType, getNextInstanceId(),
                                     pTeri->name, pInstanceContent->name, instanceContentId );
  pZone->init();

  m_instanceContentToInstanceMap[ instanceContentId ][ pZone->getGuId() ] = pZone;
  m_instanceIdToZonePtrMap[ pZone->getGuId() ] = pZone;
  m_instanceZoneSet.insert( pZone );

  return pZone;
}

bool Core::TerritoryMgr::removeTerritoryInstance( uint32_t instanceId )
{
  ZonePtr pZone;
  if( ( pZone = getInstanceZonePtr( instanceId ) ) == nullptr )
    return false;

  m_instanceIdToZonePtrMap.erase( pZone->getGuId() );

  m_instanceZoneSet.erase( pZone );
  m_zoneSet.erase( pZone );

  if( isInstanceContentTerritory( pZone->getTerritoryId() ) )
  {
    auto instance = boost::dynamic_pointer_cast< InstanceContent >( pZone );
    m_instanceContentToInstanceMap[ instance->getInstanceContentId() ].erase( pZone->getGuId() );
  }
  else
    m_territoryIdToInstanceGuidMap[ pZone->getTerritoryId() ].erase( pZone->getGuId() );


  return true;
}

Core::ZonePtr Core::TerritoryMgr::getInstanceZonePtr( uint32_t instanceId ) const
{
  auto it = m_instanceIdToZonePtrMap.find( instanceId );
  if( it == m_instanceIdToZonePtrMap.end() )
    return nullptr;

  return it->second;
}

void Core::TerritoryMgr::loadTerritoryPositionMap()
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pQR = pDb->query( "SELECT id, target_zone_id, pos_x, pos_y, pos_z, pos_o, radius FROM zonepositions;" );

  while( pQR->next() )
  {
    uint32_t id = pQR->getUInt( 1 );
    uint32_t targetZoneId = pQR->getUInt( 2 );
    Common::FFXIVARR_POSITION3 pos{};
    pos.x = pQR->getFloat( 3 );
    pos.y = pQR->getFloat( 4 );
    pos.z = pQR->getFloat( 5 );
    float posO = pQR->getFloat( 6 );
    uint32_t radius = pQR->getUInt( 7 );

    m_territoryPositionMap[ id ] = make_ZonePosition( id, targetZoneId, pos, radius, posO );
  }
}

bool Core::TerritoryMgr::isDefaultTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->territoryIntendedUse == TerritoryIntendedUse::Inn ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::Town ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::OpenWorld ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::OpeningArea;

}

bool Core::TerritoryMgr::isHousingTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->territoryIntendedUse == TerritoryIntendedUse::HousingArea;
}

Core::ZonePositionPtr Core::TerritoryMgr::getTerritoryPosition( uint32_t territoryPositionId ) const
{
  auto it = m_territoryPositionMap.find( territoryPositionId );

  if( it != m_territoryPositionMap.end() )
    return it->second;

  return nullptr;
}

Core::ZonePtr Core::TerritoryMgr::getZoneByTerriId( uint32_t territoryId ) const
{
  auto zoneMap = m_territoryIdToInstanceGuidMap.find( territoryId );
  if( zoneMap == m_territoryIdToInstanceGuidMap.end() )
    return nullptr;

  // TODO: actually select the proper one
  return zoneMap->second.begin()->second;
}

void Core::TerritoryMgr::updateTerritoryInstances( uint32_t currentTime )
{
  for( auto& zone : m_zoneSet )
  {
    zone->update( currentTime );
  }

  for( auto& zone : m_instanceZoneSet )
  {
    zone->update( currentTime );
  }
}

Core::TerritoryMgr::InstanceIdList Core::TerritoryMgr::getInstanceContentIdList( uint16_t instanceContentId ) const
{
  std::vector< uint32_t > idList;
  auto zoneMap = m_instanceContentToInstanceMap.find( instanceContentId );
  if( zoneMap == m_instanceContentToInstanceMap.end() )
    return idList;

  for( auto& entry : zoneMap->second )
  {
    idList.push_back( entry.first );
  }

  return idList;
}

bool Core::TerritoryMgr::movePlayer( uint32_t territoryId, Core::Entity::PlayerPtr pPlayer )
{
  auto pZone = getZoneByTerriId( territoryId );
  assert( pZone );
  return movePlayer( pZone, pPlayer );
}

bool Core::TerritoryMgr::movePlayer( ZonePtr pZone, Core::Entity::PlayerPtr pPlayer )
{
  auto pLog = g_fw.get< Logger >();
  if( !pZone )
  {
    pLog->error( "Zone not found on this server." );
    return false;
  }

  pPlayer->initSpawnIdQueue();

  pPlayer->setTerritoryId( pZone->getTerritoryId() );

  // mark character as zoning in progress
  pPlayer->setLoadingComplete( false );

  //if( pPlayer->getLastPing() != 0 )
  //   pPlayer->getCurrentZone()->removeActor( pPlayer );

  pPlayer->setCurrentZone( pZone );
  pZone->pushActor( pPlayer );

  // map player to instanceId so it can be tracked.
  m_playerIdToInstanceMap[ pPlayer->getId() ] = pZone->getGuId();

  return true;
}

Core::ZonePtr Core::TerritoryMgr::getLinkedInstance( uint32_t playerId ) const
{
  auto it = m_playerIdToInstanceMap.find( playerId );
  if( it != m_playerIdToInstanceMap.end() )
  {
    return getInstanceZonePtr( it->second );
  }
  return nullptr;
}

const std::pair< uint16_t, uint16_t >& Core::TerritoryMgr::getCurrentFestival() const
{
  return m_currentFestival;
}

void Core::TerritoryMgr::setCurrentFestival( uint16_t festivalId, uint16_t additionalFestival )
{
  m_currentFestival = { festivalId, additionalFestival };

  for( const auto& zone : m_zoneSet )
  {
    zone->setCurrentFestival( festivalId, additionalFestival );
  }
}

void Core::TerritoryMgr::disableCurrentFestival()
{
  setCurrentFestival( 0 );
}



