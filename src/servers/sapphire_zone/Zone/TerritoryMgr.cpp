#include "TerritoryMgr.h"

#include <common/Logging/Logger.h>
#include <common/Database/DatabaseDef.h>
#include <common/Exd/ExdDataGenerated.h>

#include "Actor/Player.h"

#include "Zone.h"
#include "ZonePosition.h"
#include "InstanceContent.h"

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;
extern Core::Data::ExdDataGenerated g_exdDataGen;

Core::TerritoryMgr::TerritoryMgr() :
   m_lastInstanceId( 10000 )
{

}

void Core::TerritoryMgr::loadTerritoryTypeDetailCache()
{
   auto idList = g_exdDataGen.getTerritoryTypeIdList();

   for( auto id : idList )
   {
      auto teri1 = g_exdDataGen.getTerritoryType( id );

      if( !teri1->name.empty() )
         m_territoryTypeDetailCacheMap[id] = teri1;
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

   return pTeri->territoryIntendedUse == TerritoryIntendedUse::AllianceRaid ||
          pTeri->territoryIntendedUse == TerritoryIntendedUse::BeforeTrialDung ||
          pTeri->territoryIntendedUse == TerritoryIntendedUse::Trial ||
          pTeri->territoryIntendedUse == TerritoryIntendedUse::Dungeon ||
          pTeri->territoryIntendedUse == TerritoryIntendedUse::OpenWorldInstanceBattle ||
          pTeri->territoryIntendedUse == TerritoryIntendedUse::PalaceOfTheDead ||
          pTeri->territoryIntendedUse == TerritoryIntendedUse::RaidFights ||
          pTeri->territoryIntendedUse == TerritoryIntendedUse::Raids ||
          pTeri->territoryIntendedUse == TerritoryIntendedUse::TreasureMapInstance;
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
   // for each entry in territoryTypeExd, check if it is a normal and if so, add the zone object
   for( const auto& territory : m_territoryTypeDetailCacheMap )
   {
      auto territoryId = territory.first;
      auto territoryInfo = territory.second;

      // if the zone has no name set
      if( territoryInfo->name.empty() )
         continue;

      auto pPlaceName = g_exdDataGen.getPlaceName( territoryInfo->placeName );

      if( !pPlaceName || pPlaceName->name.empty() || !isDefaultTerritory( territoryId ) )
         continue;

      uint32_t guid = getNextInstanceId();
      g_log.Log( LoggingSeverity::info, std::to_string( territoryId ) +
                                        "\t" + std::to_string( guid ) +
                                        "\t" + std::to_string( territoryInfo->territoryIntendedUse ) +
                                        "\t" + territoryInfo->name +
                                        "\t" + pPlaceName->name );

      ZonePtr pZone( new Zone( territoryId, guid, territoryInfo->name, pPlaceName->name ) );
      pZone->init();

      InstanceIdToZonePtrMap instanceMap;
      instanceMap[guid] = pZone;
      m_instanceIdToZonePtrMap[guid] = pZone;
      m_territoryInstanceMap[territoryId] = instanceMap;
      m_zoneSet.insert( { pZone } );

   }

   return true;
}

Core::ZonePtr Core::TerritoryMgr::createTerritoryInstance( uint32_t territoryTypeId )
{
   if( !isValidTerritory( territoryTypeId ) )
      return nullptr;

   if( isInstanceContentTerritory( territoryTypeId ) )
      return nullptr;

   auto pTeri = getTerritoryDetail( territoryTypeId );
   auto pPlaceName = g_exdDataGen.getPlaceName( pTeri->placeName );

   if( !pTeri || !pPlaceName )
      return nullptr;

   g_log.debug( "Starting instance for territory: " + std::to_string( territoryTypeId ) + " (" + pPlaceName->name + ")" );

   ZonePtr pZone = ZonePtr( new Zone( territoryTypeId, getNextInstanceId(), pTeri->name, pPlaceName->name ) );
   pZone->init();

   m_territoryInstanceMap[pZone->getTerritoryId()][pZone->getGuId()] = pZone;
   m_instanceIdToZonePtrMap[pZone->getGuId()] = pZone;

   return pZone;
}

Core::ZonePtr Core::TerritoryMgr::createInstanceContent( uint32_t instanceContentId )
{
   auto pInstanceContent = g_exdDataGen.getInstanceContent( instanceContentId );
   if( !pInstanceContent )
      return nullptr;

   if( !isInstanceContentTerritory( pInstanceContent->territoryType ) )
      return nullptr;

   auto pTeri = getTerritoryDetail( pInstanceContent->territoryType );

   if( !pTeri || pInstanceContent->name.empty() )
      return nullptr;

   g_log.debug( "Starting instance for InstanceContent id: " + std::to_string( instanceContentId ) +
                                                           " (" + pInstanceContent->name + ")" );

   ZonePtr pZone = ZonePtr( new InstanceContent( pInstanceContent, getNextInstanceId(), pTeri->name,
                                                 pInstanceContent->name, instanceContentId ) );
   pZone->init();

   m_instanceContentToInstanceMap[instanceContentId][pZone->getGuId()] = pZone;
   m_instanceIdToZonePtrMap[pZone->getGuId()] = pZone;
   m_instanceZoneSet.insert( { pZone } );

   return pZone;
}

bool Core::TerritoryMgr::removeTerritoryInstance( uint32_t instanceId )
{
   ZonePtr pZone;
   if( ( pZone = getInstanceZonePtr( instanceId ) ) == nullptr )
      return false;

   m_instanceIdToZonePtrMap.erase( pZone->getGuId() );

   if( m_instanceZoneSet.count( pZone ) )
      m_instanceZoneSet.erase( pZone );

   if( isInstanceContentTerritory( pZone->getTerritoryId() ) )
   {
      auto instance = boost::dynamic_pointer_cast< InstanceContent >( pZone );
      m_instanceContentToInstanceMap[instance->getInstanceContentId()].erase( pZone->getGuId() );
   }
   else
      m_territoryInstanceMap[pZone->getTerritoryId()].erase( pZone->getGuId() );


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
   auto pQR = g_charaDb.query( "SELECT id, target_zone_id, pos_x, pos_y, pos_z, pos_o, radius FROM zonepositions;" );

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

      m_territoryPositionMap[id] = ZonePositionPtr( new ZonePosition( id, targetZoneId, pos, radius, posO ) );
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

Core::ZonePositionPtr Core::TerritoryMgr::getTerritoryPosition( uint32_t territoryPositionId ) const
{
   auto it = m_territoryPositionMap.find( territoryPositionId );

   if( it != m_territoryPositionMap.end() )
      return it->second;

   return nullptr;
}

Core::ZonePtr Core::TerritoryMgr::getZoneByTerriId( uint32_t territoryId ) const
{
   auto zoneMap = m_territoryInstanceMap.find( territoryId );
   if( zoneMap == m_territoryInstanceMap.end() )
      return nullptr;

   // TODO: actually select the proper one
   return zoneMap->second.begin()->second;
}

void Core::TerritoryMgr::updateTerritoryInstances( uint32_t currentTime )
{
   for( auto& zone : m_zoneSet )
   {
      zone->runZoneLogic( currentTime );
   }

   for( auto& zone : m_instanceZoneSet )
   {
      zone->runZoneLogic( currentTime );
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

   if( !pZone  )
   {
      g_log.error( "Zone " + std::to_string( territoryId ) + " not found on this server." );
      return false;
   }

   pPlayer->setTerritoryId( territoryId );

   // mark character as zoning in progress
   pPlayer->setLoadingComplete( false );

   if( pPlayer->getLastPing() != 0 )
      pPlayer->getCurrentZone()->removeActor( pPlayer );

   pPlayer->setCurrentZone( pZone );
   pZone->pushActor( pPlayer );

   return true;
}

bool Core::TerritoryMgr::movePlayer( ZonePtr pZone, Core::Entity::PlayerPtr pPlayer )
{
   if( !pZone  )
   {
      g_log.error( "Zone not found on this server." );
      return false;
   }

   pPlayer->setTerritoryId( pZone->getTerritoryId() );

   // mark character as zoning in progress
   pPlayer->setLoadingComplete( false );

   if( pPlayer->getLastPing() != 0 )
      pPlayer->getCurrentZone()->removeActor( pPlayer );

   pPlayer->setCurrentZone( pZone );
   pZone->pushActor( pPlayer );

   return true;
}



