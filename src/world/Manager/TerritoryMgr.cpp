#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdData.h>

#include "WorldServer.h"
#include "Session.h"

#include <unordered_map>
#include <Service.h>

#include "Actor/Player.h"

#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"
#include "TerritoryMgr.h"
#include "HousingMgr.h"
#include "WarpMgr.h"
#include "PlayerMgr.h"
#include "Linkshell/Linkshell.h"

#include "Territory/Land.h"
#include "Territory/House.h"
#include "Territory/Housing/HousingInteriorTerritory.h"

using namespace Sapphire;
using namespace Sapphire::World::Manager;

TerritoryMgr::TerritoryMgr() :
  m_lastInstanceId( 10000 )
{

}

void TerritoryMgr::loadTerritoryTypeDetailCache()
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto idList = exdData.getIdList< Excel::TerritoryType >();

  for( auto id : idList )
  {
    auto teri1 = exdData.getRow< Excel::TerritoryType >( id );

    if( !teri1->getString( teri1->data().Name ).empty() && id > 90 )
      m_territoryTypeDetailCacheMap[ id ] = teri1;
  }

}

bool TerritoryMgr::isValidTerritory( uint32_t territoryTypeId ) const
{
  return !( m_territoryTypeDetailCacheMap.find( territoryTypeId ) == m_territoryTypeDetailCacheMap.end() );
}

bool TerritoryMgr::init()
{
  try
  {
    loadTerritoryTypeDetailCache();

    createDefaultTerritories();
    createHousingTerritories();
  }
  catch( const std::runtime_error& ex )
  {
    Logger::fatal( "Caught exception during territory init: {}", ex.what() );
    return false;
  }

  return true;
}

uint32_t TerritoryMgr::getNextInstanceId()
{
  return ++m_lastInstanceId;
}

Excel::ExcelStructPtr< Excel::TerritoryType > TerritoryMgr::getTerritoryDetail( uint32_t territoryTypeId ) const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto teri1 = exdData.getRow< Excel::TerritoryType >( territoryTypeId );
  if( !teri1 )
    return nullptr;

  return teri1;
}

bool TerritoryMgr::isInstanceContentTerritory( uint32_t territoryTypeId ) const
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

bool TerritoryMgr::isPrivateTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->data().IntendedUse == TerritoryIntendedUse::OpeningArea ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::Inn ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::JailArea ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::MSQPrivateArea;
}

bool TerritoryMgr::isInternalEstateTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->data().IntendedUse == TerritoryIntendedUse::HousingPrivateArea;
}

bool TerritoryMgr::isDefaultTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->data().IntendedUse == TerritoryIntendedUse::Inn ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::Town ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::OpenWorld ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::OpeningArea ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::GoldSaucer ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::ChocoboSquare ||
         pTeri->data().IntendedUse == TerritoryIntendedUse::BeforeTrialDung;

}

bool TerritoryMgr::isHousingTerritory( uint32_t territoryTypeId ) const
{
  auto pTeri = getTerritoryDetail( territoryTypeId );

  if( !pTeri )
    return false;

  return pTeri->data().IntendedUse == TerritoryIntendedUse::HousingArea;
}

uint32_t TerritoryMgr::getInstanceContentId( uint32_t territoryTypeId ) const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto contentListIds = exdData.getIdList< Excel::InstanceContent >();

  for( auto id : contentListIds )
  {
    auto instanceContent = exdData.getRow< Excel::InstanceContent >( id );
    if( instanceContent->data().TerritoryType == territoryTypeId )
    {
      return id;
    }
  }

  return 0;
}

bool TerritoryMgr::createDefaultTerritories()
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  // for each entry in territoryTypeExd, check if it is a normal and if so, add the zone object
  for( const auto& territory : m_territoryTypeDetailCacheMap )
  {
    auto territoryTypeId = territory.first;
    auto territoryInfo = territory.second;
    auto& territoryData = territoryInfo->data();

    // if the zone has no name set
    if( territoryInfo->getString( territoryData.Name ).empty() )
      continue;

    auto pPlaceName = exdData.getRow< Excel::PlaceName >( territoryData.Area );

    if( !pPlaceName || pPlaceName->getString( pPlaceName->data().Text.SGL ).empty() || !isDefaultTerritory( territoryTypeId ) )
      continue;

    uint32_t guid = getNextInstanceId();

    auto pZone = make_Territory( territoryTypeId, guid, territoryInfo->getString( territoryData.Name ),
                                                 pPlaceName->getString( pPlaceName->data().Text.SGL ) );
    pZone->init();

    std::string bgPath = territoryInfo->getString( territoryData.LVB );

    bool hasNaviMesh = pZone->getNaviProvider() != nullptr;

    Logger::info( "{0}\t{1}\t{2}\t{3:<10}\t{4}\t{5}\t{6}",
                  std::to_string( territoryTypeId ),
                  guid,
                  territoryData.IntendedUse,
                  territoryInfo->getString( territoryData.Name ),
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

bool TerritoryMgr::createHousingTerritories()
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

    auto pPlaceName = exdData.getRow< Excel::PlaceName >( territoryInfo->data().Area );

    if( !pPlaceName || pPlaceName->getString( pPlaceName->data().Text.SGL ).empty() || !isHousingTerritory( territoryTypeId ) )
      continue;

    for( wardNum = 0; wardNum < wardMaxNum; wardNum++ )
    {

      auto pHousingZone = make_HousingZone( wardNum, territoryTypeId, territoryInfo->getString( territoryInfo->data().Name ),
                                                                pPlaceName->getString( pPlaceName->data().Text.SGL ) );
      pHousingZone->init();

      Logger::info( "{0}\t{1}\t{2}\t{3:<10}\tHOUSING\t\t{4}#{5}",
                    territoryTypeId,
                    pHousingZone->getLandSetId(),
                    territoryInfo->data().IntendedUse,
                    territoryInfo->getString( territoryInfo->data().Name ),
                    pPlaceName->getString( pPlaceName->data().Text.SGL ),
                    wardNum );

      InstanceIdToTerritoryPtrMap instanceMap;
      instanceMap[ pHousingZone->getLandSetId() ] = pHousingZone;
      m_guIdToTerritoryPtrMap[ pHousingZone->getLandSetId() ] = pHousingZone;
      m_territoryTypeIdToInstanceGuidMap[ territoryTypeId ][ pHousingZone->getLandSetId() ] = pHousingZone;
      m_territorySet.insert( { pHousingZone } );
    }

  }

  return true;
}

TerritoryPtr TerritoryMgr::createTerritoryInstance( uint32_t territoryTypeId )
{
  if( !isValidTerritory( territoryTypeId ) )
    return nullptr;

//  nb: disabled for now because there's not a real reason to have this constraint, makes testing some stuff easier too
//  if( isInstanceContentTerritory( territoryTypeId ) )
//    return nullptr;

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto pTeri = getTerritoryDetail( territoryTypeId );
  auto pPlaceName = exdData.getRow< Excel::PlaceName >( pTeri->data().Area );

  if( !pTeri || !pPlaceName )
    return nullptr;

  auto placeName = pPlaceName->getString( pPlaceName->data().Text.SGL );
  Logger::debug( "Starting instance for territory: {0} ({1})", territoryTypeId, placeName );

  auto pZone = make_Territory( territoryTypeId, getNextInstanceId(), pTeri->getString( pTeri->data().Name ), placeName );
  pZone->init();

  m_guIdToTerritoryPtrMap[ pZone->getGuId() ] = pZone;
  m_territoryTypeIdToInstanceGuidMap[ pZone->getTerritoryTypeId() ][ pZone->getGuId() ] = pZone;
  m_territorySet.insert( { pZone } );

  return pZone;
}

TerritoryPtr TerritoryMgr::createQuestBattle( uint32_t questBattleId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto pQuestBattleInfo = exdData.getRow< Excel::QuestBattle >( questBattleId );
  if( !pQuestBattleInfo )
    return nullptr;

  auto pQuestInfo = exdData.getRow< Excel::Quest >( pQuestBattleInfo->data().Quest );
  if( !pQuestInfo || pQuestInfo->getString( pQuestInfo->data().Text.Name ).empty() )
    return nullptr;

  for( auto& teriId : exdData.getIdList< Excel::TerritoryType >() )
  {

    auto pTeri = exdData.getRow< Excel::TerritoryType >( teriId );
    if( !pTeri || pTeri->data().QuestBattle != questBattleId )
      continue;

    if( !isInstanceContentTerritory( teriId ) )
      return nullptr;

    auto questName = pQuestInfo->getString( pQuestInfo->data().Text.Name );
    Logger::debug( "Starting instance for QuestBattle id: {0} ({1})", questBattleId, questName );

    auto instanceId = getNextInstanceId();
    auto pZone = make_QuestBattle( pQuestBattleInfo, teriId, instanceId,
                                                     pTeri->getString( pTeri->data().Name ), questName, questBattleId );
    pZone->init();

    m_questBattleIdToInstanceMap[ questBattleId ][ pZone->getGuId() ] = pZone;
    m_guIdToTerritoryPtrMap[ pZone->getGuId() ] = pZone;
    m_instanceZoneSet.insert( pZone );

    return pZone;


  }

  return nullptr;
}

TerritoryPtr TerritoryMgr::createInstanceContent( uint32_t contentFinderId )
{

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto pContentFinderCondition = exdData.getRow< Excel::ContentFinderCondition >( contentFinderId );
  if( !pContentFinderCondition )
    return nullptr;

  auto pInstanceContent = exdData.getRow< Excel::InstanceContent >( pContentFinderCondition->data().InstanceContentId );
  if( !pInstanceContent )
    return nullptr;

  auto& instanceContentData = pInstanceContent->data();

  if( !isInstanceContentTerritory( instanceContentData.TerritoryType ) )
    return nullptr;

  auto pTeri = getTerritoryDetail( instanceContentData.TerritoryType );

  auto name = pInstanceContent->getString( instanceContentData.Text.Name );

  if( !pTeri || name.empty() )
    return nullptr;

  Logger::debug( "Starting instance for InstanceContent id: {0} ({1})", contentFinderId, name );

  auto pZone = make_InstanceContent( pInstanceContent, pContentFinderCondition, instanceContentData.TerritoryType, getNextInstanceId(), " ", name, contentFinderId );
  pZone->init();

  m_instanceContentIdToInstanceMap[ contentFinderId ][ pZone->getGuId() ] = pZone;
  m_guIdToTerritoryPtrMap[ pZone->getGuId() ] = pZone;
  m_instanceZoneSet.insert( pZone );

  return pZone;
}

TerritoryPtr TerritoryMgr::findOrCreateHousingInterior( const Common::LandIdent landIdent )
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
    getTerritoryByGuId( housingMgr.toLandSetId( landIdent.territoryTypeId, landIdent.wardNum ) ) );

  if( !parentZone )
    return nullptr;

  auto land = parentZone->getLand( static_cast< uint8_t >( landIdent.landId ) );
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

  auto zone = Territory::Housing::make_HousingInteriorTerritory( landIdent, territoryTypeId,
                                                                        getNextInstanceId(), terriInfo->getString( terriInfo->data().Name ),
                                                                        house->getHouseName() );

  zone->init();

  m_landIdentToTerritoryPtrMap[ ident ] = zone;
  m_guIdToTerritoryPtrMap[ zone->getGuId() ] = zone;
  m_territorySet.insert( { zone } );

  return zone;
}

bool TerritoryMgr::removeTerritoryInstance( uint32_t guId )
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

TerritoryPtr TerritoryMgr::getTerritoryByGuId( uint32_t guId ) const
{
  auto it = m_guIdToTerritoryPtrMap.find( guId );
  if( it == m_guIdToTerritoryPtrMap.end() )
    return nullptr;

  return it->second;
}

TerritoryPtr TerritoryMgr::getZoneByTerritoryTypeId( uint32_t territoryTypeId ) const
{
  auto zoneMap = m_territoryTypeIdToInstanceGuidMap.find( territoryTypeId );
  if( zoneMap == m_territoryTypeIdToInstanceGuidMap.end() )
    return nullptr;

  // TODO: actually select the proper one
  return zoneMap->second.begin()->second;
}


void TerritoryMgr::updateTerritoryInstances( uint64_t tickCount )
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
  for( auto & it : m_questBattleIdToInstanceMap )
  {
    for( auto inIt = it.second.begin(); inIt != it.second.end(); )
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

  for( auto& it : m_instanceContentIdToInstanceMap )
  {
    for( auto inIt = it.second.begin(); inIt != it.second.end(); )
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

TerritoryMgr::InstanceIdList TerritoryMgr::getInstanceContentIdList( uint16_t instanceContentId ) const
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

bool TerritoryMgr::movePlayer( Sapphire::Territory& teri, Entity::Player& player )
{
  auto& playerMgr = Common::Service< Manager::PlayerMgr >::ref();

  auto pPrevZone = getTerritoryByGuId( player.getTerritoryId() );

  player.setStateFlag( Common::PlayerStateFlag::BetweenAreas );

  player.initSpawnIdQueue();

  player.setTerritoryTypeId( teri.getTerritoryTypeId() );
  player.setTerritoryId( teri.getGuId() );

  bool playerLoaded = player.isLoadingComplete();

  // mark character as zoning in progress
  player.setLoadingComplete( false );

  if( playerLoaded && pPrevZone )
    pPrevZone->removeActor( player.getAsPlayer() );

  teri.pushActor( player.getAsPlayer() );

  // map player to instanceId so it can be tracked.
  m_playerIdToInstanceMap[ player.getId() ] = teri.getGuId();

  teri.onBeforePlayerZoneIn( player );
  playerMgr.onZone( player );

  return true;
}

TerritoryPtr TerritoryMgr::getLinkedInstance( uint32_t playerId ) const
{
  auto it = m_playerIdToInstanceMap.find( playerId );
  if( it != m_playerIdToInstanceMap.end() )
  {
    return getTerritoryByGuId( it->second );
  }
  return nullptr;
}

const std::pair< uint16_t, uint16_t >& TerritoryMgr::getCurrentFestival() const
{
  return m_currentFestival;
}

void TerritoryMgr::setCurrentFestival( uint16_t festivalId, uint16_t additionalFestival )
{
  m_currentFestival = { festivalId, additionalFestival };

  for( const auto& zone : m_territorySet )
  {
    zone->setCurrentFestival( festivalId, additionalFestival );
  }
}

void TerritoryMgr::disableCurrentFestival()
{
  setCurrentFestival( 0 );
}

void TerritoryMgr::createAndJoinQuestBattle( Entity::Player& player, uint16_t questBattleId )
{
  auto qb = createQuestBattle( questBattleId );
  if( !qb )
    return;

  auto& warpMgr = Common::Service< WarpMgr >::ref();
  warpMgr.requestMoveTerritory( player, Common::WARP_TYPE_INSTANCE_CONTENT, qb->getGuId(), { 0, 0, 0 }, 0 );
}

bool TerritoryMgr::joinWorld( Entity::Player& player )
{

  TerritoryPtr pCurrZone;

  auto territoryTypeId = player.getTerritoryTypeId();

  // if the zone is an instanceContent zone, we need to actually find the instance
  if( isInstanceContentTerritory( territoryTypeId ) )
  {
    // try to find an instance actually linked to this player
    pCurrZone = getLinkedInstance( player.getId() );
    // if none found, revert to previous zone and position
    if( !pCurrZone )
    {
      territoryTypeId = player.getPrevTerritoryTypeId();
      auto prevPos = player.getPrevPos();
      player.setPos( prevPos, false );
      player.setRot( player.getPrevRot() );
      pCurrZone = getZoneByTerritoryTypeId( territoryTypeId );
    }
  }
  else if( isInternalEstateTerritory( territoryTypeId ) )
  {
    // todo: this needs to go to the area just outside of the plot door
    pCurrZone = getTerritoryByGuId( player.getPrevTerritoryId() );

    territoryTypeId = player.getPrevTerritoryTypeId();
    auto prevPos = player.getPrevPos();
    player.setPos( prevPos, false );
    player.setRot( player.getPrevRot() );
  }
  else if( isHousingTerritory( territoryTypeId ) )
  {
    pCurrZone = getTerritoryByGuId( player.getTerritoryId() );
  }
  else
  {
    pCurrZone = getZoneByTerritoryTypeId( territoryTypeId );
  }

  player.setTerritoryTypeId( territoryTypeId );

  // TODO: logic for instances needs to be added here
  // see if a valid zone could be found for the character
  if( !pCurrZone )
  {
    Logger::error( "[{0}] Territory #{1} not found, manual adjustment of territory required!", player.getCharacterId(), territoryTypeId );
    return false;
  }

  if( !movePlayer( *pCurrZone, player ) )
    return false;

  return true;
}


