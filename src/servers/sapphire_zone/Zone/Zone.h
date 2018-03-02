#ifndef _ZONE_H
#define _ZONE_H

#include <unordered_map>
#include <common/Common.h>

#include "Cell.h"
#include "CellHandler.h"
#include "Actor/InstanceObject.h"

#include "Forwards.h"

#include <set>
#include <boost/enable_shared_from_this.hpp>

#include <stdio.h>
#include <string.h>
#include <common/Exd/ExdDataGenerated.h>
namespace Core {

class Session;

class ZonePosition;

using SessionSet = std::set< SessionPtr >;

class Zone : public CellHandler< Cell >, public boost::enable_shared_from_this< Zone >
{
protected:
   uint32_t	m_territoryId;
   uint32_t	m_guId;

   std::string m_placeName;
   std::string m_internalName;

   std::unordered_map< int32_t, Entity::PlayerPtr > m_playerMap;
   std::unordered_map< int32_t, Entity::BattleNpcPtr > m_BattleNpcMap;
   std::unordered_map< int32_t, Entity::EventNpcPtr > m_EventNpcMap;
   std::unordered_map< int32_t, Entity::InstanceObjectPtr > m_instanceObjects;

   std::set< Entity::BattleNpcPtr > m_BattleNpcDeadMap;

   SessionSet m_sessionSet;

   CellCache** m_pCellCache[_sizeX];

   uint8_t m_currentWeather;
   uint8_t m_weatherOverride;

   uint64_t m_lastMobUpdate;

   uint16_t m_currentFestivalId;
   boost::shared_ptr< Data::TerritoryType > m_territoryTypeInfo;

   std::map< uint8_t, int32_t> m_weatherRateMap;



public:
   Zone();

   Zone( uint16_t territoryId, uint32_t guId, const std::string& internalName, const std::string& placeName );
   virtual ~Zone();

   bool init();

   /*! overrides the zone's weather, set to 0 to unlock */
   void setWeatherOverride( uint8_t weather );

   uint8_t getCurrentWeather() const;

   uint16_t getCurrentFestival() const;
   void setCurrentFestival( uint16_t festivalId );

   CellCache* getCellCacheList( uint32_t cellx, uint32_t celly );

   CellCache* getCellCacheAndCreate( uint32_t cellx, uint32_t celly );

   virtual void loadCellCache();
   virtual uint32_t getTerritoryId() const;
   virtual void onEnterTerritory( Entity::Player& player );
   virtual void onFinishLoading( Entity::Player& player );
   virtual void onInitDirector( Entity::Player& player );
   virtual void onLeaveTerritory( Entity::Player& player );
   virtual void onUpdate( uint32_t currTime );

   uint8_t getNextWeather();

   void pushActor( Entity::ActorPtr pActor );

   void removeActor( Entity::ActorPtr pActor );

   void updateActorPosition( Entity::Actor &pActor );

   bool isCellActive( uint32_t x, uint32_t y );

   void updateCellActivity( uint32_t x, uint32_t y, int32_t radius );

   void updateInRangeSet( Entity::ActorPtr pActor, Cell* pCell );

   void queueOutPacketForRange( Entity::Player& sourcePlayer, uint32_t range, Network::Packets::GamePacketPtr pPacketEntry );

   uint32_t getGuId() const;

   const std::string& getName() const;
   const std::string& getInternalName() const;

   std::size_t getPopCount() const;
   bool checkWeather();
   void updateBnpcs( int64_t tickCount );

   bool update( uint32_t currTime );

   void registerInstanceObj( Entity::InstanceObjectPtr object );
   Entity::InstanceObjectPtr getInstanceObject( uint32_t objId );
   void updateInstanceObj( Entity::InstanceObjectPtr object );

   InstanceContentPtr getAsInstanceContent();

};

}

#endif
