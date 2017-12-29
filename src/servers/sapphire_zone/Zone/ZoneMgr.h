#ifndef _ZONEMGR_H
#define _ZONEMGR_H


#include <unordered_map>
#include <map>
#include "Forwards.h"

namespace Core {

   using ZoneMap = std::unordered_map< uint32_t, ZonePtr >;

   class ZoneMgr
   {
   public:
      ZoneMgr();
      ~ZoneMgr();

      bool createZones();

      ZonePtr getZone( uint32_t zoneId );

      void loadZonePositionMap();

      ZonePositionPtr getZonePosition( uint32_t zonePositionId );

      void updateZones();

   private:
      ZoneMap m_zoneMap;

      std::unordered_map<int32_t, ZonePositionPtr > m_zonePositionMap;

   };

}

#endif

