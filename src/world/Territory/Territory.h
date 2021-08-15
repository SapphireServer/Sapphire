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

  using FestivalPair = std::pair< uint16_t, uint16_t >;

  namespace Data
  {
    struct InstanceContent;
    struct TerritoryType;
  }

  class Territory : public CellHandler< Cell >, public std::enable_shared_from_this< Territory >
  {
  protected:
    uint32_t m_territoryTypeId;
    uint32_t m_guId;

    std::string m_placeName;
    std::string m_internalName;
    std::string m_bgPath;

    std::unordered_map< int32_t, Entity::PlayerPtr > m_playerMap;
    std::unordered_map< int32_t, Entity::BNpcPtr > m_bNpcMap;
    std::unordered_map< int32_t, Entity::EventObjectPtr > m_eventObjects;

    Common::Weather m_currentWeather;
    Common::Weather m_weatherOverride;
    std::map< uint8_t, int32_t > m_weatherRateMap;

    int64_t m_lastMobUpdate;
    int64_t m_lastUpdate;

    uint64_t m_lastActivityTime;

    FestivalPair m_currentFestival;

    std::shared_ptr< Data::TerritoryType > m_territoryTypeInfo;

    uint32_t m_nextEObjId;
    uint32_t m_nextActorId;

    std::vector< Entity::SpawnGroup > m_spawnGroups;

    uint32_t m_effectCounter;
    std::shared_ptr< World::Navi::NaviProvider > m_pNaviProvider;

    std::vector< World::Action::EffectResultPtr > m_effectResults;

  public:
    Territory();

    Territory( uint16_t territoryTypeId, uint32_t guId, const std::string& internalName,
               const std::string& placeName );

    virtual ~Territory();

    /*! overrides the zone's weather, set to 0 to unlock */
    void setWeatherOverride( Common::Weather weather );

    Common::Weather getCurrentWeather() const;

    const FestivalPair& getCurrentFestival() const;

    void setCurrentFestival( uint16_t festivalId, uint16_t additionalFestivalId = 0 );

    std::shared_ptr< Data::TerritoryType > getTerritoryTypeInfo() const;

    uint64_t getLastActivityTime() const;

    virtual bool init();

    virtual void loadCellCache();

    virtual uint32_t getTerritoryTypeId() const;

    virtual void onBeforePlayerZoneIn( Entity::Player& player ) {};

    virtual void onPlayerZoneIn( Entity::Player& player );

    virtual void onFinishLoading( Entity::Player& player );

    virtual void onInitDirector( Entity::Player& player );

    virtual void onDirectorSync( Entity::Player& player ) {};

    virtual void onLeaveTerritory( Entity::Player& player );

    virtual void onUpdate( uint64_t tickCount );

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

    uint32_t getNextActorId();

    const std::string& getName() const;

    const std::string& getInternalName() const;

    const std::string& getBgPath() const;

    std::size_t getPopCount() const;

    void loadWeatherRates();

    bool loadSpawnGroups();

    bool checkWeather();
    void updateBNpcs( uint64_t tickCount );

    bool update( uint64_t tickCount );

    void updateSessions( uint64_t tickCount, bool changedWeather );

    Entity::EventObjectPtr registerEObj( const std::string& name, uint32_t objectId, uint32_t mapLink,
                                         uint8_t state, Common::FFXIVARR_POSITION3 pos, float scale, float rotation );

    void registerEObj( Entity::EventObjectPtr object );
    Entity::BNpcPtr createBNpcFromLevelEntry( uint32_t levelId, uint8_t level, uint8_t type,
                                              uint32_t hp, uint16_t nameId, uint32_t directorId, uint8_t bnpcType );
    Entity::BNpcPtr getActiveBNpcByLevelId( uint32_t levelId );

    Entity::EventObjectPtr getEObj( uint32_t objId );

    Event::DirectorPtr getAsDirector();

    InstanceContentPtr getAsInstanceContent();

    QuestBattlePtr getAsQuestBattle();

    PublicContentPtr getAsPublicContent();

    void updateSpawnPoints();

    uint32_t getNextEffectSequence();

    std::shared_ptr< World::Navi::NaviProvider > getNaviProvider();

    void addEffectResult( World::Action::EffectResultPtr result );

    void processEffectResults( uint64_t tickCount );

    Entity::PlayerPtr getPlayer( uint32_t charId );

    void foreachPlayer( std::function< void( Entity::PlayerPtr player ) > callback );
  };

}

#endif
