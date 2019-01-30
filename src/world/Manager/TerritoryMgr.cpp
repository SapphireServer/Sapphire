#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>

#include "ServerMgr.h"

#include <unordered_map>

#include "Actor/Player.h"

#include "Territory/Zone.h"
#include "Territory/ZonePosition.h"
#include "Territory/InstanceContent.h"
#include "TerritoryMgr.h"
#include "HousingMgr.h"
#include "Framework.h"

#include "Territory/Land.h"
#include "Territory/House.h"
#include "Territory/Housing/HousingInteriorTerritory.h"
#include "NaviMgr.h"

Sapphire::World::Manager::TerritoryMgr::TerritoryMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw ),
  m_lastInstanceId( 10000 )
{

}

void Sapphire::World::Manager::TerritoryMgr::loadTerritoryTypeDetailCache()
{
  auto pExdData = framework()->get< Data::ExdDataGenerated >();
  auto idList = pExdData->getTerritoryTypeIdList();

  for( auto id : idList )
  {
    auto teri1 = pExdData->get< Sapphire::Data::TerritoryType >( id );

    if( !teri1->name.empty() )
      m_territoryTypeDetailCacheMap[ id ] = teri1;
  }
}

bool Sapphire::World::Manager::TerritoryMgr::isValidTerritory( uint32_t territoryTypeId ) const
{
  return !( m_territoryTypeDetailCacheMap.find( territoryTypeId ) == m_territoryTypeDetailCacheMap.end() );
}

bool Sapphire::World::Manager::TerritoryMgr::init()
{
  try
  {
    loadTerritoryTypeDetailCache();
    loadTerritoryPositionMap();

    createDefaultTerritories();
    createHousingTerritories();
  }
  catch( std::runtime_error& )
  {
    return false;
  }

  auto& cfg = framework()->get< World::ServerMgr >()->getConfig();

  m_inRangeDistance = cfg.network.inRangeDistance;

  return true;
}

uint32_t Sapphire::World::Manager::TerritoryMgr::getNextInstanceId()
{
  return ++m_lastInstanceId;
}

Sapphire::Data::TerritoryTypePtr Sapphire::World::Manager::TerritoryMgr::getTerritoryDetail( uint32_t territoryTypeId ) const
{
  auto tIt = m_territoryTypeDetailCacheMap.find( territoryTypeId );
  if( tIt == m_territoryTypeDetailCacheMap.end() )
    return nullptr;

  return tIt->second;
}

bool Sapphire::World::Manager::TerritoryMgr::isInstanceContentTerritory( uint32_t territoryTypeId ) const
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

bool Sapphire::World::Manager::TerritoryMgr::isPrivateTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->territoryIntendedUse == TerritoryIntendedUse::OpeningArea ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::Inn ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::JailArea ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::MSQPrivateArea;
}

bool Sapphire::World::Manager::TerritoryMgr::isInternalEstateTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->territoryIntendedUse == TerritoryIntendedUse::HousingPrivateArea;
}

bool Sapphire::World::Manager::TerritoryMgr::isDefaultTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->territoryIntendedUse == TerritoryIntendedUse::Inn ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::Town ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::OpenWorld ||
         pTeri->territoryIntendedUse == TerritoryIntendedUse::OpeningArea;

}

bool Sapphire::World::Manager::TerritoryMgr::isHousingTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->territoryIntendedUse == TerritoryIntendedUse::HousingArea;
}

bool Sapphire::World::Manager::TerritoryMgr::createDefaultTerritories()
{
  auto pExdData = framework()->get< Data::ExdDataGenerated >();
  // for each entry in territoryTypeExd, check if it is a normal and if so, add the zone object
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryTypeId = territory.first;
    auto territoryInfo = territory.second;

    // if the zone has no name set
    if( territoryInfo->name.empty() )
      continue;

    auto pPlaceName = pExdData->get< Sapphire::Data::PlaceName >( territoryInfo->placeName );

    if( !pPlaceName || pPlaceName->name.empty() || !isDefaultTerritory( territoryTypeId ) )
      continue;

    uint32_t guid = getNextInstanceId();

    auto pNaviMgr = framework()->get< Manager::NaviMgr >();
    std::string bgPath = territoryInfo->bg;
    bool hasNaviMesh = pNaviMgr->setupTerritory( bgPath );

    Logger::info( "{0}\t{1}\t{2}\t{3:<10}\t{4}\t{5}\t{6}",
                  territoryTypeId,
                  guid,
                  territoryInfo->territoryIntendedUse,
                  territoryInfo->name,
                  ( isPrivateTerritory( territoryTypeId ) ? "PRIVATE" : "PUBLIC" ),
                  hasNaviMesh ? "NAVI" : "",
                  pPlaceName->name );

    auto pZone = make_Zone( territoryTypeId, guid, territoryInfo->name, pPlaceName->name, framework() );
    pZone->init();

    InstanceIdToZonePtrMap instanceMap;
    instanceMap[ guid ] = pZone;
    m_instanceIdToZonePtrMap[ guid ] = pZone;
    m_territoryTypeIdToInstanceGuidMap[ territoryTypeId ] = instanceMap;
    m_zoneSet.insert( { pZone } );

  }

  return true;
}

bool Sapphire::World::Manager::TerritoryMgr::createHousingTerritories()
{
  //separate housing zones from default
  auto pExdData = framework()->get< Data::ExdDataGenerated >();
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryTypeId = territory.first;
    auto territoryInfo = territory.second;
    uint32_t wardNum;
    uint32_t wardMaxNum = 18;

    if( territoryInfo->name.empty() )
      continue;

    auto pPlaceName = pExdData->get< Sapphire::Data::PlaceName >( territoryInfo->placeName );

    if( !pPlaceName || pPlaceName->name.empty() || !isHousingTerritory( territoryTypeId ) )
      continue;

    for( wardNum = 0; wardNum < wardMaxNum; wardNum++ )
    {
      uint32_t guid = getNextInstanceId();

      Logger::info( "{0}\t{1}\t{2}\t{3:<10}\tHOUSING\t\t{4}#{5}",
                    territoryTypeId,
                    guid,
                    territoryInfo->territoryIntendedUse,
                    territoryInfo->name,
                    pPlaceName->name,
                    wardNum );

      auto pHousingZone = make_HousingZone( wardNum, territoryTypeId, guid, territoryInfo->name,
                                            pPlaceName->name, framework() );
      pHousingZone->init();

      InstanceIdToZonePtrMap instanceMap;
      instanceMap[ guid ] = pHousingZone;
      m_instanceIdToZonePtrMap[ guid ] = pHousingZone;
      m_territoryTypeIdToInstanceGuidMap[ territoryTypeId ][ guid ] = pHousingZone;
      m_landSetIdToZonePtrMap[ pHousingZone->getLandSetId() ] = pHousingZone;
      m_zoneSet.insert( { pHousingZone } );
    }

  }

  return true;
}

Sapphire::ZonePtr Sapphire::World::Manager::TerritoryMgr::createTerritoryInstance( uint32_t territoryTypeId )
{
  if( !isValidTerritory( territoryTypeId ) )
    return nullptr;

  if( isInstanceContentTerritory( territoryTypeId ) )
    return nullptr;

  auto pExdData = framework()->get< Data::ExdDataGenerated >();
  auto pTeri = getTerritoryDetail( territoryTypeId );
  auto pPlaceName = pExdData->get< Sapphire::Data::PlaceName >( pTeri->placeName );

  if( !pTeri || !pPlaceName )
    return nullptr;

  Logger::debug( "Starting instance for territory: {0} ({1})", territoryTypeId, pPlaceName->name );

  auto pZone = make_Zone( territoryTypeId, getNextInstanceId(), pTeri->name, pPlaceName->name, framework() );
  pZone->init();

  m_instanceIdToZonePtrMap[ pZone->getGuId() ] = pZone;
  m_territoryTypeIdToInstanceGuidMap[ pZone->getTerritoryTypeId() ][ pZone->getGuId() ] = pZone;
  m_zoneSet.insert( { pZone } );

  return pZone;
}

Sapphire::ZonePtr Sapphire::World::Manager::TerritoryMgr::createInstanceContent( uint32_t contentFinderConditionId )
{

  auto pExdData = framework()->get< Data::ExdDataGenerated >();
  auto pContentFinderCondition = pExdData->get< Sapphire::Data::ContentFinderCondition >( contentFinderConditionId );
  if( !pContentFinderCondition )
    return nullptr;
  auto instanceContentId = pContentFinderCondition->content;

  auto pInstanceContent = pExdData->get< Sapphire::Data::InstanceContent >( instanceContentId );
  if( !pInstanceContent )
    return nullptr;

  if( !isInstanceContentTerritory( pContentFinderCondition->territoryType ) )
    return nullptr;

  auto pTeri = getTerritoryDetail( pContentFinderCondition->territoryType );

  if( !pTeri || pInstanceContent->name.empty() )
    return nullptr;

  Logger::debug( "Starting instance for InstanceContent id: {0} ({1})", instanceContentId, pInstanceContent->name );

  auto pZone = make_InstanceContent( pInstanceContent, pContentFinderCondition->territoryType, getNextInstanceId(),
                                     pTeri->name, pInstanceContent->name, instanceContentId, framework() );
  pZone->init();

  m_instanceContentIdToInstanceMap[ instanceContentId ][ pZone->getGuId() ] = pZone;
  m_instanceIdToZonePtrMap[ pZone->getGuId() ] = pZone;
  m_instanceZoneSet.insert( pZone );

  return pZone;
}

Sapphire::ZonePtr Sapphire::World::Manager::TerritoryMgr::findOrCreateHousingInterior( const Common::LandIdent landIdent )
{
  // check if zone already spawned first
  auto ident = *reinterpret_cast< const uint64_t* >( &landIdent );

  auto it = m_landIdentToZonePtrMap.find( ident );
  if( it != m_landIdentToZonePtrMap.end() )
  {
    return it->second;
  }

  // otherwise, create it
  auto housingMgr = framework()->get< Manager::HousingMgr >();

  auto parentZone = std::dynamic_pointer_cast< HousingZone >(
    getZoneByLandSetId( housingMgr->toLandSetId( static_cast< uint16_t >( landIdent.territoryTypeId ),
                                                 static_cast< uint8_t >( landIdent.wardNum ) ) ) );

  if( !parentZone )
    return nullptr;

  auto land = parentZone->getLand( landIdent.landId );
  if( !land )
    return nullptr;

  auto house = land->getHouse();
  if( !house )
    return nullptr;

  // get house instance id
  uint16_t territoryTypeId = 0;
  switch( landIdent.territoryTypeId )
  {
    case 339: // mist
      territoryTypeId = 282;
      break;

    case 340: // lavender beds
      territoryTypeId = 342;
      break;

    case 341: // goblet
      territoryTypeId = 345;
      break;

    case 641: // shirogane
      territoryTypeId = 649;
      break;

    default:
      return nullptr;
  }

  // zones are sequential in the exd for small, med, large
  territoryTypeId += land->getSize();

  auto terriInfo = getTerritoryDetail( territoryTypeId );
  if( !terriInfo )
    return nullptr;

  auto zone = World::Territory::Housing::make_HousingInteriorTerritory( landIdent, territoryTypeId,
                                                                        getNextInstanceId(), terriInfo->name,
                                                                        house->getHouseName(), framework() );

  zone->init();

  m_landIdentToZonePtrMap[ ident ] = zone;
  m_instanceIdToZonePtrMap[ zone->getGuId() ] = zone;
  m_zoneSet.insert( { zone } );

  return zone;
}

bool Sapphire::World::Manager::TerritoryMgr::removeTerritoryInstance( uint32_t instanceId )
{
  ZonePtr pZone;
  if( ( pZone = getInstanceZonePtr( instanceId ) ) == nullptr )
    return false;

  m_instanceIdToZonePtrMap.erase( pZone->getGuId() );

  m_instanceZoneSet.erase( pZone );
  m_zoneSet.erase( pZone );

  if( isInstanceContentTerritory( pZone->getTerritoryTypeId() ) )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( pZone );
    m_instanceContentIdToInstanceMap[ instance->getInstanceContentId() ].erase( pZone->getGuId() );
  }
  else
    m_territoryTypeIdToInstanceGuidMap[ pZone->getTerritoryTypeId() ].erase( pZone->getGuId() );


  return true;
}

Sapphire::ZonePtr Sapphire::World::Manager::TerritoryMgr::getInstanceZonePtr( uint32_t instanceId ) const
{
  auto it = m_instanceIdToZonePtrMap.find( instanceId );
  if( it == m_instanceIdToZonePtrMap.end() )
    return nullptr;

  return it->second;
}

void Sapphire::World::Manager::TerritoryMgr::loadTerritoryPositionMap()
{
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
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

Sapphire::ZonePositionPtr Sapphire::World::Manager::TerritoryMgr::getTerritoryPosition( uint32_t territoryPositionId ) const
{
  auto it = m_territoryPositionMap.find( territoryPositionId );

  if( it != m_territoryPositionMap.end() )
    return it->second;

  return nullptr;
}

Sapphire::ZonePtr Sapphire::World::Manager::TerritoryMgr::getZoneByTerritoryTypeId( uint32_t territoryTypeId ) const
{
  auto zoneMap = m_territoryTypeIdToInstanceGuidMap.find( territoryTypeId );
  if( zoneMap == m_territoryTypeIdToInstanceGuidMap.end() )
    return nullptr;

  // TODO: actually select the proper one
  return zoneMap->second.begin()->second;
}

Sapphire::ZonePtr Sapphire::World::Manager::TerritoryMgr::getZoneByLandSetId( uint32_t landSetId ) const
{
  auto zoneMap = m_landSetIdToZonePtrMap.find( landSetId );
  if( zoneMap == m_landSetIdToZonePtrMap.end() )
    return nullptr;

  return zoneMap->second;
}

void Sapphire::World::Manager::TerritoryMgr::updateTerritoryInstances( uint32_t currentTime )
{
  for( auto& zone : m_zoneSet )
  {
    zone->update( currentTime );
  }

  for( auto& zone : m_instanceZoneSet )
  {
    zone->update( currentTime );
  }

  // remove internal house zones with nobody in them
  for( auto it = m_landIdentToZonePtrMap.begin(); it != m_landIdentToZonePtrMap.end(); )
  {
    auto zone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >( it->second );
    assert( zone ); // wtf??

    auto diff = std::difftime( currentTime, zone->getLastActivityTime() );

    // todo: make this timeout configurable, though should be pretty relaxed in any case
    if( diff > 60 )
    {
      Logger::info( "Removing HousingInteriorTerritory#{0} - has been inactive for 60 seconds", zone->getGuId() );

      // remove zone from maps
      m_zoneSet.erase( zone );
      it = m_landIdentToZonePtrMap.erase( it );
    }
    else
      it++;
  }
}

Sapphire::World::Manager::TerritoryMgr::InstanceIdList Sapphire::World::Manager::TerritoryMgr::getInstanceContentIdList( uint16_t instanceContentId ) const
{
  std::vector< uint32_t > idList;
  auto zoneMap = m_instanceContentIdToInstanceMap.find( instanceContentId );
  if( zoneMap == m_instanceContentIdToInstanceMap.end() )
    return idList;

  for( auto& entry : zoneMap->second )
  {
    idList.push_back( entry.first );
  }

  return idList;
}

bool Sapphire::World::Manager::TerritoryMgr::movePlayer( uint32_t territoryTypeId, Sapphire::Entity::PlayerPtr pPlayer )
{
  auto pZone = getZoneByTerritoryTypeId( territoryTypeId );
  assert( pZone );
  return movePlayer( pZone, pPlayer );
}

bool Sapphire::World::Manager::TerritoryMgr::movePlayer( ZonePtr pZone, Sapphire::Entity::PlayerPtr pPlayer )
{
  if( !pZone )
  {
    Logger::error( "Zone not found on this server." );
    return false;
  }

  pPlayer->initSpawnIdQueue();

  pPlayer->setTerritoryTypeId( pZone->getTerritoryTypeId() );

  if( isHousingTerritory( pZone->getTerritoryTypeId() ) )
  {
    auto pHousing = std::dynamic_pointer_cast< HousingZone >( pZone );
    if( pHousing )
      pPlayer->setTerritoryId( pHousing->getLandSetId() );
  }
  else if( isInstanceContentTerritory( pZone->getTerritoryTypeId() ) )
  {
    pPlayer->setTerritoryId( pZone->getGuId() );
  }
  else
  {
    pPlayer->setTerritoryId( 0 );
  }

  // mark character as zoning in progress
  pPlayer->setLoadingComplete( false );

  if( pPlayer->getLastPing() != 0 && pPlayer->getCurrentZone() )
    pPlayer->getCurrentZone()->removeActor( pPlayer );

  pPlayer->setCurrentZone( pZone );
  pZone->pushActor( pPlayer );

  // map player to instanceId so it can be tracked.
  m_playerIdToInstanceMap[ pPlayer->getId() ] = pZone->getGuId();

  pPlayer->sendZonePackets();

  return true;
}

Sapphire::ZonePtr Sapphire::World::Manager::TerritoryMgr::getLinkedInstance( uint32_t playerId ) const
{
  auto it = m_playerIdToInstanceMap.find( playerId );
  if( it != m_playerIdToInstanceMap.end() )
  {
    return getInstanceZonePtr( it->second );
  }
  return nullptr;
}

const std::pair< uint16_t, uint16_t >& Sapphire::World::Manager::TerritoryMgr::getCurrentFestival() const
{
  return m_currentFestival;
}

void Sapphire::World::Manager::TerritoryMgr::setCurrentFestival( uint16_t festivalId, uint16_t additionalFestival )
{
  m_currentFestival = { festivalId, additionalFestival };

  for( const auto& zone : m_zoneSet )
  {
    zone->setCurrentFestival( festivalId, additionalFestival );
  }
}

void Sapphire::World::Manager::TerritoryMgr::disableCurrentFestival()
{
  setCurrentFestival( 0 );
}

float Sapphire::World::Manager::TerritoryMgr::getInRangeDistance() const
{
  return m_inRangeDistance;
}


