#ifndef _ZONE_H
#define _ZONE_H

#include <unordered_map>
#include <Common.h>

#include "Cell.h"
#include "CellHandler.h"

#include "ForwardsZone.h"

#include <set>
#include <map>
#include <memory>

#include <stdio.h>
#include <string.h>

namespace Sapphire
{

  class ZonePosition;

  using SessionSet = std::set< World::SessionPtr >;
  using FestivalPair = std::pair< uint16_t, uint16_t >;

  namespace Data
  {
    struct InstanceContent;
    struct TerritoryType;
  }

  class Zone : public CellHandler< Cell >, public std::enable_shared_from_this< Zone >
  {
  protected:
    uint32_t m_territoryTypeId;
    uint32_t m_guId;

    std::string m_placeName;
    std::string m_internalName;

    std::unordered_map< int32_t, Entity::PlayerPtr > m_playerMap;
    std::unordered_map< int32_t, Entity::BNpcPtr > m_bNpcMap;
    std::unordered_map< int32_t, Entity::EventObjectPtr > m_eventObjects;

    SessionSet m_sessionSet;

    Common::Weather m_currentWeather;
    Common::Weather m_weatherOverride;

    uint64_t m_lastMobUpdate;

    FestivalPair m_currentFestival;

    std::shared_ptr< Data::TerritoryType > m_territoryTypeInfo;

    std::map< uint8_t, int32_t > m_weatherRateMap;

    uint32_t m_nextEObjId;
    FrameworkPtr m_pFw;

    std::vector< Entity::SpawnGroup > m_spawnGroups;

  public:
    Zone();

    Zone( uint16_t territoryTypeId, uint32_t guId, const std::string& internalName,
          const std::string& placeName, FrameworkPtr pFw );

    virtual ~Zone();

    /*! overrides the zone's weather, set to 0 to unlock */
    void setWeatherOverride( Common::Weather weather );

    Common::Weather getCurrentWeather() const;

    const FestivalPair& getCurrentFestival() const;

    void setCurrentFestival( uint16_t festivalId, uint16_t additionalFestivalId = 0 );

    std::shared_ptr< Data::TerritoryType > getTerritoryTypeInfo() const;

    virtual bool init();

    virtual void loadCellCache();

    virtual uint32_t getTerritoryTypeId() const;

    virtual void onBeforePlayerZoneIn( Entity::Player& player ) {};

    virtual void onPlayerZoneIn( Entity::Player& player );

    virtual void onFinishLoading( Entity::Player& player );

    virtual void onInitDirector( Entity::Player& player );

    virtual void onDirectorSync( Entity::Player& player ) {};

    virtual void onLeaveTerritory( Entity::Player& player );

    virtual void onUpdate( uint32_t currTime );

    virtual void onRegisterEObj( Entity::EventObjectPtr object ) {};

    virtual void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 );

    Common::Weather getNextWeather();

    void pushActor( Entity::ActorPtr pActor );

    void removeActor( Entity::ActorPtr pActor );

    void updateActorPosition( Entity::Actor& pActor );

    bool isCellActive( uint32_t x, uint32_t y );

    void updateCellActivity( uint32_t x, uint32_t y, int32_t radius );

    void updateInRangeSet( Entity::ActorPtr pActor, Cell* pCell );

    void queuePacketForRange( Entity::Player& sourcePlayer, uint32_t range,
                              Network::Packets::FFXIVPacketBasePtr pPacketEntry );

    void queuePacketForZone( Entity::Player& sourcePlayer, Network::Packets::FFXIVPacketBasePtr pPacketEntry,
                             bool forSelf = false );

    uint32_t getGuId() const;

    uint32_t getNextEObjId();

    const std::string& getName() const;

    const std::string& getInternalName() const;

    std::size_t getPopCount() const;

    void loadWeatherRates();

    bool loadSpawnGroups();

    bool checkWeather();
    //void updateBnpcs( int64_t tickCount );

    bool update( uint32_t currTime );

    void updateSessions( bool changedWeather );

    Entity::EventObjectPtr registerEObj( const std::string& name, uint32_t objectId, uint32_t mapLink,
                                         uint8_t state, Common::FFXIVARR_POSITION3 pos, float scale, float rotation );

    void registerEObj( Entity::EventObjectPtr object );

    Entity::EventObjectPtr getEObj( uint32_t objId );

    InstanceContentPtr getAsInstanceContent();

    void updateSpawnPoints();
  };

}

#endif
