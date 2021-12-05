#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdData.h>

#include "WorldServer.h"
#include "Session.h"

#include <unordered_map>
#include <Service.h>

#include "Actor/Player.h"

#include "Territory/Territory.h"
#include "Territory/ZonePosition.h"
#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"
#include "TerritoryMgr.h"
#include "HousingMgr.h"
#include "ChatChannelMgr.h"
#include "LinkshellMgr.h"

#include "Linkshell/Linkshell.h"

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
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto idList = exdData.getIdList< Component::Excel::TerritoryType >();

  for( auto id : idList )
  {
    auto teri1 = exdData.getRow< Component::Excel::TerritoryType >( id );

    if( !teri1->getString( teri1->data().Name ).empty() )
      m_territoryTypeDetailCacheMap[ id ] = teri1;
  }

  for( auto id : exdData.getIdList< Component::Excel::InstanceContent >() )
  {
    // EXD TODO: how did this work back then...
    /*
    auto cfc = exdData.get< Sapphire::Data::ContentFinderCondition >( id );
    if( !cfc || cfc->contentLinkType != 5 )
      continue;

    m_questBattleToContentFinderMap[ cfc->content ] = id;
     */
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

  auto& server = Common::Service< World::WorldServer >::ref();
  auto& cfg = server.getConfig();

  m_inRangeDistance = cfg.network.inRangeDistance;

  return true;
}

uint32_t Sapphire::World::Manager::TerritoryMgr::getNextInstanceId()
{
  return ++m_lastInstanceId;
}

std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::TerritoryType > > Sapphire::World::Manager::TerritoryMgr::getTerritoryDetail( uint32_t territoryTypeId ) const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto teri1 = exdData.getRow< Component::Excel::TerritoryType >( territoryTypeId );
  if( !teri1 )
    return nullptr;

  return teri1;
}

bool Sapphire::World::Manager::TerritoryMgr::isInstanceContentTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  auto intendedUse = pTeri->data().IntendedUse;

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

  return pTeri->data().IntendedUse == TerritoryIntendedUse::OpeningArea ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::Inn ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::JailArea ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::MSQPrivateArea;
}

bool Sapphire::World::Manager::TerritoryMgr::isInternalEstateTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->data().IntendedUse == TerritoryIntendedUse::HousingPrivateArea;
}

bool Sapphire::World::Manager::TerritoryMgr::isDefaultTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->data().IntendedUse == TerritoryIntendedUse::Inn ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::Town ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::OpenWorld ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::OpeningArea;

}

bool Sapphire::World::Manager::TerritoryMgr::isHousingTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->data().IntendedUse == TerritoryIntendedUse::HousingArea;
}

uint32_t Sapphire::World::Manager::TerritoryMgr::getInstanceContentId( uint32_t territoryTypeId ) const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto contentListIds = exdData.getIdList< Component::Excel::InstanceContent >();

  for( auto id : contentListIds )
  {
    auto instanceContent = exdData.getRow< Component::Excel::InstanceContent >( id );
    if( instanceContent->data().TerritoryType == territoryTypeId )
    {
      return id;
    }
  }

  return 0;
}

bool Sapphire::World::Manager::TerritoryMgr::createDefaultTerritories()
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  // for each entry in territoryTypeExd, check if it is a normal and if so, add the zone object
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryTypeId = territory.first;
    auto territoryInfo = territory.second;

    // if the zone has no name set
    if( territoryInfo->getString( territoryInfo->data().Name ).empty() )
      continue;

    auto pPlaceName = exdData.getRow< Component::Excel::PlaceName >( territoryInfo->data().Area );

    if( !pPlaceName || pPlaceName->getString( pPlaceName->data().Text.SGL ).empty() || !isDefaultTerritory( territoryTypeId ) )
      continue;

    uint32_t guid = getNextInstanceId();

    auto pZone = make_Territory( territoryTypeId, guid, territoryInfo->getString( territoryInfo->data().Name ), pPlaceName->getString( pPlaceName->data().Text.SGL ) );
    pZone->init();

    std::string bgPath = territoryInfo->getString( territoryInfo->data().LVB );

    bool hasNaviMesh = pZone->getNaviProvider() != nullptr;

    Logger::info( "{0}\t{1}\t{2}\t{3:<10}\t{4}\t{5}\t{6}",
                  territoryTypeId,
                  guid,
                  territoryInfo->data().IntendedUse,
                  territoryInfo->getString( territoryInfo->data().Name ),
                  ( isPrivateTerritory( territoryTypeId ) ? "PRIVATE" : "PUBLIC" ),
                  hasNaviMesh ? "NAVI" : "",
                  pPlaceName->getString( pPlaceName->data().Text.SGL ) );

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
  auto& exdData = Common::Service< Data::ExdData >::ref();
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryTypeId = territory.first;
    auto territoryInfo = territory.second;
    uint32_t wardNum;
    uint32_t wardMaxNum = 8;

    if( territoryInfo->getString( territoryInfo->data().Name ).empty() )
      continue;

    auto pPlaceName = exdData.getRow< Component::Excel::PlaceName >( territoryInfo->data().Area );

    if( !pPlaceName || pPlaceName->getString( pPlaceName->data().Text.SGL ).empty() || !isHousingTerritory( territoryTypeId ) )
      continue;

    for( wardNum = 0; wardNum < wardMaxNum; wardNum++ )
    {
      uint32_t guid = getNextInstanceId();

      Logger::info( "{0}\t{1}\t{2}\t{3:<10}\tHOUSING\t\t{4}#{5}",
                    territoryTypeId,
                    guid,
                    territoryInfo->data().IntendedUse,
                    territoryInfo->getString( territoryInfo->data().Name ),
                    pPlaceName->getString( pPlaceName->data().Text.SGL ),
                    wardNum );

      auto pHousingZone = make_HousingZone( wardNum, territoryTypeId, guid, territoryInfo->getString( territoryInfo->data().Name ), pPlaceName->getString( pPlaceName->data().Text.SGL ) );
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

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto pTeri = getTerritoryDetail( territoryTypeId );
  auto pPlaceName = exdData.getRow< Component::Excel::PlaceName >( pTeri->data().Area );

  if( !pTeri || !pPlaceName )
    return nullptr;

  Logger::debug( "Starting instance for territory: {0} ({1})", territoryTypeId, pPlaceName->getString( pPlaceName->data().Text.SGL ) );

  auto pZone = make_Territory( territoryTypeId, getNextInstanceId(), pTeri->getString( pTeri->data().Name ), pPlaceName->getString( pPlaceName->data().Text.SGL ) );
  pZone->init();

  m_guIdToTerritoryPtrMap[ pZone->getGuId() ] = pZone;
  m_territoryTypeIdToInstanceGuidMap[ pZone->getTerritoryTypeId() ][ pZone->getGuId() ] = pZone;
  m_territorySet.insert( { pZone } );

  return pZone;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::createQuestBattle( uint32_t questBattleId )
{

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto pQuestBattleInfo = exdData.getRow< Component::Excel::QuestBattle >( questBattleId );
  if( !pQuestBattleInfo )
    return nullptr;

  auto pQuestInfo = exdData.getRow< Component::Excel::Quest >( pQuestBattleInfo->data().Quest );
  if( !pQuestInfo || pQuestInfo->getString( pQuestInfo->data().Text.Name ).empty() )
    return nullptr;

  uint16_t teriId = 0;
  for( auto& id : exdData.getIdList< Component::Excel::TerritoryType >() )
  {

    auto pTeri = exdData.getRow< Component::Excel::TerritoryType >( id );
    if( !pTeri )
      continue;

    if( pTeri->data().QuestBattle == questBattleId )
    {
      teriId = id;
      if( !isInstanceContentTerritory( teriId ) )
        return nullptr;

      Logger::debug( "Starting instance for QuestBattle id: {0} ({1})",
                     questBattleId, pQuestInfo->getString( pQuestInfo->data().Text.Name ) );

      auto instanceId = getNextInstanceId();
      auto pZone = make_QuestBattle( pQuestBattleInfo, teriId, instanceId,
                                     pTeri->getString( pTeri->data().Name ),
                                     pQuestInfo->getString( pQuestInfo->data().Text.Name ), questBattleId );
      pZone->init();

      m_questBattleIdToInstanceMap[ questBattleId ][ pZone->getGuId() ] = pZone;
      m_guIdToTerritoryPtrMap[ pZone->getGuId() ] = pZone;
      m_instanceZoneSet.insert( pZone );

      return pZone;
      break;
    }

  }

  return nullptr;
}

Sapphire::TerritoryPtr Sapphire::World::Manager::TerritoryMgr::createInstanceContent( uint32_t instanceContentId )
{

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto pInstanceContent = exdData.getRow< Component::Excel::InstanceContent >( instanceContentId );
  if( !pInstanceContent )
    return nullptr;

  if( !isInstanceContentTerritory( pInstanceContent->data().TerritoryType ) )
    return nullptr;

  auto pTeri = getTerritoryDetail( pInstanceContent->data().TerritoryType );

  std::string name = pInstanceContent->getString( pInstanceContent->data().Text.Name );

  if( !pTeri || name.empty() )
    return nullptr;

  Logger::debug( "Starting instance for InstanceContent id: {0} ({1})", instanceContentId, name );

  auto pZone = make_InstanceContent( pInstanceContent, pInstanceContent->data().TerritoryType, getNextInstanceId(),
                                     " ", name, instanceContentId );
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
                                                                        getNextInstanceId(), terriInfo->getString( terriInfo->data().Name ),
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

  for( auto it = m_instanceContentIdToInstanceMap.begin(); it != m_instanceContentIdToInstanceMap.end(); ++it )
  {
    for( auto inIt = it->second.begin(); inIt != it->second.end(); )
    {
      auto zone = std::dynamic_pointer_cast< InstanceContent >( inIt->second );
      if( !zone )
        continue;

      if( zone->isTerminationReady() )
      {
        Logger::info( "Removing InstanceContent#{0} - marked for terminate", zone->getGuId() );

        // remove zone from maps
        m_instanceZoneSet.erase( zone );
        m_guIdToTerritoryPtrMap.erase( zone->getGuId() );
        inIt = m_instanceContentIdToInstanceMap[ zone->getInstanceContentId() ].erase( inIt );
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

bool Sapphire::World::Manager::TerritoryMgr::movePlayer( uint32_t territoryTypeId, Sapphire::Entity::Player& player )
{
  auto pZone = getZoneByTerritoryTypeId( territoryTypeId );
  if( !pZone )
    return false;
  return movePlayer( pZone, player );
}

bool Sapphire::World::Manager::TerritoryMgr::movePlayer( TerritoryPtr pZone, Sapphire::Entity::Player& player )
{
  if( !pZone )
  {
    Logger::error( "Territory not found on this server." );
    return false;
  }

  player.setStateFlag( Common::PlayerStateFlag::BetweenAreas );

  player.initSpawnIdQueue();

  player.setTerritoryTypeId( pZone->getTerritoryTypeId() );

  if( isHousingTerritory( pZone->getTerritoryTypeId() ) )
  {
    auto pHousing = std::dynamic_pointer_cast< HousingZone >( pZone );
    if( pHousing )
      player.setTerritoryId( pHousing->getLandSetId() );
  }
  else if( isInstanceContentTerritory( pZone->getTerritoryTypeId() ) )
  {
    player.setTerritoryId( pZone->getGuId() );
  }
  else
  {
    player.setTerritoryId( 0 );
  }

  bool playerLoaded = player.isLoadingComplete();

  // mark character as zoning in progress
  player.setLoadingComplete( false );

  if( playerLoaded && player.getCurrentTerritory() )
    player.getCurrentTerritory()->removeActor( player.getAsPlayer() );

  player.setCurrentZone( pZone );
  pZone->pushActor( player.getAsPlayer() );

  // map player to instanceId so it can be tracked.
  m_playerIdToInstanceMap[ player.getId() ] = pZone->getGuId();

  pZone->onBeforePlayerZoneIn( player );
  player.sendZonePackets();

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

bool Sapphire::World::Manager::TerritoryMgr::joinWorld( Sapphire::Entity::Player& player )
{

  TerritoryPtr pCurrZone = nullptr;

  auto zoneId = player.getTerritoryTypeId();

  // if the zone is an instanceContent zone, we need to actually find the instance
  if( isInstanceContentTerritory( zoneId ) )
  {
    // try to find an instance actually linked to this player
    pCurrZone = getLinkedInstance( player.getId() );
    // if none found, revert to previous zone and position
    if( !pCurrZone )
    {
      zoneId = player.getPrevTerritoryTypeId();
      auto prevPos = player.getPrevPos();
      player.setPos( prevPos, false );
      player.setRot( player.getPrevRot() );
      pCurrZone = getZoneByTerritoryTypeId( zoneId );
    }
  }
  else if( isInternalEstateTerritory( zoneId ) )
  {
    // todo: this needs to go to the area just outside of the plot door
    pCurrZone = getZoneByLandSetId( player.getPrevTerritoryId() );

    zoneId = player.getPrevTerritoryTypeId();
    auto prevPos = player.getPrevPos();
    player.setPos( prevPos, false );
    player.setRot( player.getPrevRot() );
  }
  else if( isHousingTerritory( zoneId ) )
  {
    pCurrZone = getZoneByLandSetId( player.getTerritoryId() );
  }
  else
  {
    pCurrZone = getZoneByTerritoryTypeId( zoneId );
  }

  player.setTerritoryTypeId( zoneId );

  // TODO: logic for instances needs to be added here
  // see if a valid zone could be found for the character
  if( !pCurrZone )
  {
    Logger::error( "[{0}] Territory #{1} not found!", player.getCharacterId(), zoneId );
    Logger::error( "[{0}] Setting default zone instead", player.getCharacterId() );

    // default to new gridania
    // TODO: should probably just abort and mark character as corrupt
    pCurrZone = getZoneByTerritoryTypeId( 132 );

    player.setPos( { 0.0f, 0.0f, 0.0f }, false );
    player.setRot( 0.0f );
  }

  if( !movePlayer( pCurrZone, player ) )
    return false;

  return true;
}


