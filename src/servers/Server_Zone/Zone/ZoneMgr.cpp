#include <src/servers/Server_Common/Logging/Logger.h>
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <boost/lexical_cast.hpp>

#include "ZoneMgr.h"
#include "Zone.h"
#include "ZonePosition.h"

#include <Server_Common/Database/DatabaseDef.h>

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;

namespace Core {

   ZoneMgr::ZoneMgr() = default;

   ZoneMgr::~ZoneMgr() = default;

   void ZoneMgr::loadZonePositionMap()
   {
      auto pQR = g_charaDb.query( "SELECT id, target_zone_id, pos_x, pos_y, pos_z, pos_o, radius FROM zonepositions;" );

      while( pQR->next() )
      {
         uint32_t id = pQR->getUInt( 1 );
         uint32_t targetZoneId = pQR->getUInt( 2 );
         Common::FFXIVARR_POSITION3 pos;
         pos.x = pQR->getFloat( 3 );
         pos.y = pQR->getFloat( 4 );
         pos.z = pQR->getFloat( 5 );
         float posO = pQR->getFloat( 6 );
         uint32_t radius = pQR->getUInt( 7 );
         
         m_zonePositionMap[id] = ZonePositionPtr( new ZonePosition( id, targetZoneId, pos, radius, posO ) );
      }
   }

   ZonePositionPtr ZoneMgr::getZonePosition( uint32_t zonePositionId )
   {
      auto it = m_zonePositionMap.find( zonePositionId );

      if( it != m_zonePositionMap.end() )
         return it->second;

      return nullptr;
   }

   bool ZoneMgr::createZones()
   {
      loadZonePositionMap();

      // find zone info from exd
      for( auto zone : g_exdData.m_zoneInfoMap )
      {
         uint32_t zoneId = zone.first;

 
         auto info = zone.second;
         g_log.Log( LoggingSeverity::info, std::to_string( info.id ) + "\t" + info.zone_str );

         ZonePtr pZone( new Zone( info.id, info.layout_id, info.zone_name, info.zone_str, false ) );
         pZone->init();
         m_zoneMap[info.id] = pZone;
      }

      return true;
   }

   void ZoneMgr::updateZones()
   {
      for( auto zone : m_zoneMap )
      {
         zone.second->runZoneLogic();
      }
   }

   ZonePtr ZoneMgr::getZone( uint32_t zoneId )
   {
      ZoneMap::iterator it;
      it = m_zoneMap.find( zoneId );

      if( it != m_zoneMap.end() )
         return it->second;

      return nullptr;
   }

}
