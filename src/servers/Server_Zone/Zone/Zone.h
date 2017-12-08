#ifndef _ZONE_H
#define _ZONE_H

#include <unordered_map>
#include <Server_Common/Common.h>

#include "Cell.h"
#include "CellHandler.h"

#include "Forwards.h"

#include <set>
#include <boost/enable_shared_from_this.hpp>

#include <stdio.h>
#include <string.h>
namespace Core {
namespace Entity
{
   class Actor;
   class Player;
}

class Session;

class ZonePosition;

typedef std::set< SessionPtr > SessionSet;

class Zone : public CellHandler< Cell >, public boost::enable_shared_from_this< Zone >
{
protected:
   uint32_t	m_zoneId;
   uint32_t	m_layoutId;

   std::string m_zoneName;
   std::string m_zoneCode;

   bool m_bPrivate;

   std::unordered_map< int32_t, Entity::PlayerPtr > m_playerMap;
   std::unordered_map< int32_t, Entity::BattleNpcPtr > m_BattleNpcMap;

   std::set< Entity::BattleNpcPtr > m_BattleNpcDeadMap;

   SessionSet m_sessionSet;

   CellCache** m_pCellCache[_sizeX];

   Common::RegionType m_type;

   uint8_t m_currentWeather;
   uint8_t m_weatherOverride;

   uint64_t m_lastMobUpdate;

public:
   Zone();

   Zone( uint16_t zoneId, uint32_t layoutId, std::string name, std::string interName, bool bPrivate );
   virtual ~Zone();

   bool init();

   bool isPrivateZone() const;

   /*! overrides the zone's weather, set to 0 to unlock */
   void setWeatherOverride( uint8_t weather );

   uint8_t getCurrentWeather() const;

   CellCache* getCellCacheList( uint32_t cellx, uint32_t celly );

   CellCache* getCellCacheAndCreate( uint32_t cellx, uint32_t celly );

   virtual void loadCellCache();

   uint8_t getNextWeather();

   void pushActor( Entity::ActorPtr pActor );

   void removeActor( Entity::ActorPtr pActor );

   void changeActorPosition( Entity::ActorPtr pActor );

   bool isCellActive( uint32_t x, uint32_t y );

   void updateCellActivity( uint32_t x, uint32_t y, int32_t radius );

   void updateInRangeSet( Entity::ActorPtr pActor, Cell* pCell );

   void queueOutPacketForRange( Entity::Player& sourcePlayer, uint32_t range, Network::Packets::GamePacketPtr pPacketEntry );

   virtual uint32_t getId();

   Common::RegionType getType() const;

   uint16_t getLayoutId() const;

   bool isInstance() const;

   const std::string& getName() const;

   const std::string& getInternalName() const;

   std::size_t getPopCount() const;
   bool checkWeather();
   void updateBnpcs( int64_t tickCount );

   bool runZoneLogic();

};

}

#endif
