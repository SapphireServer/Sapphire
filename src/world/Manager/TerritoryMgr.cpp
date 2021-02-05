#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>

#include "ServerMgr.h"

#include <unordered_map>
#include <Service.h>

#include "Actor/Player.h"

#include "Territory/Territory.h"
#include "Territory/ZonePosition.h"
#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"
#include "TerritoryMgr.h"
#include "HousingMgr.h"

#include "Territory/Land.h"
#include "Territory/House.h"
#include "Territory/Housing/HousingInteriorTerritory.h"
#include "NaviMgr.h"

Sapphire::World::Manager::TerritoryMgr::TerritoryMgr() :
  m_lastInstanceId( 10000 )
{

}

void Sapphire::World::Manager::TerritoryMgr::loadTerritoryTypeDetailCache()
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto idList = exdData.getTerritoryTypeIdList();

  for( auto id : idList )
  {
    auto teri1 = exdData.get< Sapphire::Data::TerritoryType >( id );

    if( !teri1->name.empty() )
      m_territoryTypeDetailCacheMap[ id ] = teri1;
  }

  for( auto id : exdData.getContentFinderConditionIdList() )
  {
    auto cfc = exdData.get< Sapphire::Data::ContentFinderCondition >( id );
    if( !cfc || cfc->contentLinkType != 5 )
      continue;

    m_questBattleToContentFinderMap[ cfc->content ] = id;
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
  catch( const std::runtime_error& ex )
  {
    Logger::fatal( "Caught exception during territory init: {}", ex.what() );
    return false;
  }

  auto& serverMgr = Common::Service< World::ServerMgr >::ref();
  auto& cfg = serverMgr.getConfig();

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
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  // for each entry in territoryTypeExd, check if it is a normal and if so, add the zone object
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryTypeId = territory.first;
    auto territoryInfo = territory.second;

    // if the zone has no name set
    if( territoryInfo->name.empty() )
      continue;

    auto pPlaceName = exdData.get< Sapphire::Data::PlaceName >( territoryInfo->placeName );

    if( !pPlaceName || pPlaceName->name.empty() || !isDefaultTerritory( territoryTypeId ) )
      continue;

    uint32_t guid = getNextInstanceId();

    auto pZone = make_Territory( territoryTypeId, guid, territoryInfo->name, pPlaceName->name );
    pZone->init();

    std::string bgPath = territoryInfo->bg;

    bool hasNaviMesh = pZone->getNaviProvider() != nullptr;

    Logger::info( "{0}\t{1}\t{2}\t{3:<10}\t{4}\t{5}\t{6}",
                  territoryTypeId,
                  guid,
                  territoryInfo->territoryIntendedUse,
                  territoryInfo->name,
                  ( isPrivateTerritory( territoryTypeId ) ? "PRIVATE" : "PUBLIC" ),
                  hasNaviMesh ? "NAVI" : "",
                  pPlaceName->name );

    InstanceIdToTerritoryPtrMap instanceMap;
    instanceMap[ guid ] = pZone;
    m_guIdToTerritoryPtrMap[ guid ] = pZone;
    m_territoryTypeIdToInstanceGuidMap[ territoryTypeId ] = instanceMap;
    m_territorySet.insert( { pZone } );

  }

  return true;
}

bool Sapphire::World::Manager::TerritoryMgr::createHousingTerritories()
{
  //separate housing zones from default
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryTypeId = territory.first;
    auto territoryInfo = territory.second;
    uint32_t wardNum;
    uint32_t wardMaxNum = 18;

    if( territoryInfo->name.empty() )
      continue;

    auto pPlaceName = exdData.get< Sapphire::Data::PlaceName >( territoryInfo->placeName );

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

      auto pHousingZone = make_HousingZone( wardNum, territoryTypeId, guid, territoryInfo->name, pPlaceName->name );
      pHousingZone->init();

      InstanceIdToTerritoryPtrMap instanceMap;
      instanceMap[ guid ] = pHousingZone;
      m_guIdToTerritoryPtrMap[ guid ] = pHousingZone;
      m_territoryTypeIdToInstanceGuidMap[ territoryTypeId ][ guid ] = pHousingZone;
      m_landSetIdToTerritoryPtrMap[ pHousingZone->getLandSetId() ] = pHousingZone;
      m_territorySet.insert( { pHousingZone } );
    }

  }

  return true;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::createTerritoryInstance( uint32_t territoryTypeId )
{
  if( !isValidTerritory( territoryTypeId ) )
    return nullptr;

//  nb: disabled for now because there's not a real reason to have this constraint, makes testing some stuff easier too
//  if( isInstanceContentTerritory( territoryTypeId ) )
//    return nullptr;

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto pTeri = getTerritoryDetail( territoryTypeId );
  auto pPlaceName = exdData.get< Sapphire::Data::PlaceName >( pTeri->placeName );

  if( !pTeri || !pPlaceName )
    return nullptr;

  Logger::debug( "Starting instance for territory: {0} ({1})", territoryTypeId, pPlaceName->name );

  auto pZone = make_Territory( territoryTypeId, getNextInstanceId(), pTeri->name, pPlaceName->name );
  pZone->init();

  m_guIdToTerritoryPtrMap[ pZone->getGuId() ] = pZone;
  m_territoryTypeIdToInstanceGuidMap[ pZone->getTerritoryTypeId() ][ pZone->getGuId() ] = pZone;
  m_territorySet.insert( { pZone } );

  return pZone;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::createQuestBattle( uint32_t questBattleId )
{

  auto it = m_questBattleToContentFinderMap.find( questBattleId );
  if( it == m_questBattleToContentFinderMap.end() )
    return nullptr;

  auto contentFinderConditionId = it->second;

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto pContentFinderCondition = exdData.get< Sapphire::Data::ContentFinderCondition >( contentFinderConditionId );
  if( !pContentFinderCondition )
    return nullptr;

  auto pQuestBattleInfo = exdData.get< Sapphire::Data::QuestBattle >( questBattleId );
  if( !pQuestBattleInfo )
    return nullptr;

  auto pQuestInfo = exdData.get< Sapphire::Data::Quest >( pQuestBattleInfo->quest );
  if( !pQuestInfo )
    return nullptr;

  if( !isInstanceContentTerritory( pContentFinderCondition->territoryType ) )
    return nullptr;

  auto pTeri = getTerritoryDetail( pContentFinderCondition->territoryType );

  if( !pTeri || pQuestInfo->name.empty() )
    return nullptr;

  Logger::debug( "Starting instance for QuestBattle id: {0} ({1})", questBattleId, pQuestInfo->name );

  auto pZone = make_QuestBattle( pQuestBattleInfo, pContentFinderCondition->territoryType, getNextInstanceId(),
                                 pTeri->name, pQuestInfo->name, questBattleId );
  pZone->init();

  m_questBattleIdToInstanceMap[ questBattleId ][ pZone->getGuId() ] = pZone;
  m_guIdToTerritoryPtrMap[ pZone->getGuId() ] = pZone;
  m_instanceZoneSet.insert( pZone );

  return pZone;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::createInstanceContent( uint32_t contentFinderConditionId )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  auto pContentFinderCondition = exdData.get< Sapphire::Data::ContentFinderCondition >( contentFinderConditionId );
  if( !pContentFinderCondition )
    return nullptr;
  auto instanceContentId = pContentFinderCondition->content;

  auto pInstanceContent = exdData.get< Sapphire::Data::InstanceContent >( instanceContentId );
  if( !pInstanceContent )
    return nullptr;

  if( !isInstanceContentTerritory( pContentFinderCondition->territoryType ) )
    return nullptr;

  auto pTeri = getTerritoryDetail( pContentFinderCondition->territoryType );

  if( !pTeri || pContentFinderCondition->name.empty() )
    return nullptr;

  Logger::debug( "Starting instance for InstanceContent id: {0} ({1})", instanceContentId, pContentFinderCondition->name );

  auto pZone = make_InstanceContent( pInstanceContent, pContentFinderCondition->territoryType, getNextInstanceId(),
                                     pTeri->name, pContentFinderCondition->name, instanceContentId );
  pZone->init();

  m_instanceContentIdToInstanceMap[ instanceContentId ][ pZone->getGuId() ] = pZone;
  m_guIdToTerritoryPtrMap[ pZone->getGuId() ] = pZone;
  m_instanceZoneSet.insert( pZone );

  return pZone;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::findOrCreateHousingInterior( const Common::LandIdent landIdent )
{
  // check if zone already spawned first
  auto ident = *reinterpret_cast< const uint64_t* >( &landIdent );

  auto it = m_landIdentToTerritoryPtrMap.find( ident );
  if( it != m_landIdentToTerritoryPtrMap.end() )
  {
    return it->second;
  }

  // otherwise, create it
  auto& housingMgr = Common::Service< Manager::HousingMgr >::ref();

  auto parentZone = std::dynamic_pointer_cast< HousingZone >(
    getZoneByLandSetId( housingMgr.toLandSetId( static_cast< uint16_t >( landIdent.territoryTypeId ),
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
                                                                        house->getHouseName() );

  zone->init();

  m_landIdentToTerritoryPtrMap[ ident ] = zone;
  m_guIdToTerritoryPtrMap[ zone->getGuId() ] = zone;
  m_territorySet.insert( { zone } );

  return zone;
}

bool Sapphire::World::Manager::TerritoryMgr::removeTerritoryInstance( uint32_t guId )
{
  TerritoryPtr pZone;
  if( ( pZone = getTerritoryByGuId( guId ) ) == nullptr )
    return false;

  m_guIdToTerritoryPtrMap.erase( pZone->getGuId() );

  m_instanceZoneSet.erase( pZone );
  m_territorySet.erase( pZone );

  if( isInstanceContentTerritory( pZone->getTerritoryTypeId() ) )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( pZone );
    m_instanceContentIdToInstanceMap[ instance->getInstanceContentId() ].erase( pZone->getGuId() );
  }
  else
    m_territoryTypeIdToInstanceGuidMap[ pZone->getTerritoryTypeId() ].erase( pZone->getGuId() );

  return true;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::getTerritoryByGuId( uint32_t guId ) const
{
  auto it = m_guIdToTerritoryPtrMap.find( guId );
  if( it == m_guIdToTerritoryPtrMap.end() )
    return nullptr;

  return it->second;
}

void Sapphire::World::Manager::TerritoryMgr::loadTerritoryPositionMap()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto pQR = db.query( "SELECT id, target_zone_id, pos_x, pos_y, pos_z, pos_o, radius FROM zonepositions;" );

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

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::getZoneByTerritoryTypeId( uint32_t territoryTypeId ) const
{
  auto zoneMap = m_territoryTypeIdToInstanceGuidMap.find( territoryTypeId );
  if( zoneMap == m_territoryTypeIdToInstanceGuidMap.end() )
    return nullptr;

  // TODO: actually select the proper one
  return zoneMap->second.begin()->second;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::getZoneByLandSetId( uint32_t landSetId ) const
{
  auto zoneMap = m_landSetIdToTerritoryPtrMap.find( landSetId );
  if( zoneMap == m_landSetIdToTerritoryPtrMap.end() )
    return nullptr;

  return zoneMap->second;
}

void Sapphire::World::Manager::TerritoryMgr::updateTerritoryInstances( uint64_t tickCount )
{
  for( auto& zone : m_territorySet )
  {
    zone->update( tickCount );
  }

  for( auto& zone : m_instanceZoneSet )
  {
    zone->update( tickCount );
  }

  // remove internal house zones with nobody in them
  for( auto it = m_landIdentToTerritoryPtrMap.begin(); it != m_landIdentToTerritoryPtrMap.end(); )
  {
    auto zone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >( it->second );
    assert( zone ); // wtf??

    auto diff = std::difftime( tickCount, zone->getLastActivityTime() );

    // todo: make this timeout configurable, though should be pretty relaxed in any case
    if( diff > 60000 )
    {
      Logger::info( "Removing HousingInteriorTerritory#{0} - has been inactive for 60 seconds", zone->getGuId() );

      // remove zone from maps
      m_territorySet.erase( zone );
      m_guIdToTerritoryPtrMap.erase( zone->getGuId() );
      it = m_landIdentToTerritoryPtrMap.erase( it );
    }
    else
      it++;
  }

  // remove internal house zones with nobody in them
  for( auto it = m_questBattleIdToInstanceMap.begin(); it != m_questBattleIdToInstanceMap.end(); ++it )
  {
    for( auto inIt = it->second.begin(); inIt != it->second.end(); )
    {
      auto zone = std::dynamic_pointer_cast< QuestBattle >( inIt->second );
      if( !zone )
        continue;

      auto diff = std::difftime( tickCount, zone->getLastActivityTime() );

      // todo: make this timeout configurable, though should be pretty relaxed in any case
      if( diff > 60000 )
      {
        Logger::info( "Removing QuestBattle#{0} - has been inactive for 60 seconds", zone->getGuId() );

        // remove zone from maps
        m_instanceZoneSet.erase( zone );
        m_guIdToTerritoryPtrMap.erase( zone->getGuId() );
        inIt = m_questBattleIdToInstanceMap[ zone->getQuestBattleId() ].erase( inIt );
      }
      else
        inIt++;
    }

  }
}

Sapphire::World::Manager::TerritoryMgr::InstanceIdList
  Sapphire::World::Manager::TerritoryMgr::getInstanceContentIdList( uint16_t instanceContentId ) const
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

bool Sapphire::World::Manager::TerritoryMgr::movePlayer( TerritoryPtr pZone, Sapphire::Entity::PlayerPtr pPlayer )
{
  if( !pZone )
  {
    Logger::error( "Territory not found on this server." );
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

  bool zoneChanged = true;
  if( pPlayer->getLastPing() != 0 && pPlayer->getCurrentTerritory() )
  {
    zoneChanged = pPlayer->getCurrentTerritory()->getGuId() != pZone->getGuId();
    if( zoneChanged )
      pPlayer->getCurrentTerritory()->removeActor( pPlayer );
  }

  if( zoneChanged )
  {
    pPlayer->setCurrentZone( pZone );
    pZone->pushActor( pPlayer );

    // map player to instanceId so it can be tracked.
    m_playerIdToInstanceMap[ pPlayer->getId() ] = pZone->getGuId();
  }
  else
  {
    pPlayer->removeFromInRange();
    pPlayer->clearInRangeSet();
  }

  pPlayer->sendZonePackets();

  return true;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::getLinkedInstance( uint32_t playerId ) const
{
  auto it = m_playerIdToInstanceMap.find( playerId );
  if( it != m_playerIdToInstanceMap.end() )
  {
    return getTerritoryByGuId( it->second );
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

  for( const auto& zone : m_territorySet )
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

void Sapphire::World::Manager::TerritoryMgr::createAndJoinQuestBattle( Entity::Player& player, uint16_t questBattleId )
{
  auto qb = createQuestBattle( questBattleId );
  if( !qb )
    return;

  player.setInstance( qb );

}


