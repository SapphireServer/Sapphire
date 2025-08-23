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

#include <cstdio>
#include <cstring>
#include <Exd/Structs.h>
#include <Navi/NaviProvider.h>

namespace Sapphire
{
  using FestivalPair = std::pair< uint16_t, uint16_t >;

  namespace Data
  {
    struct InstanceContent;
    struct TerritoryType;
  }

  struct SpawnInfo
  {
    std::shared_ptr< Entity::BNpc > bnpcPtr;
    std::shared_ptr< Common::BNpcCacheEntry > infoPtr;
    uint32_t lastSpawn;
    uint32_t timeOfDeath;
  };

  class Territory : public CellHandler< Cell >, public std::enable_shared_from_this< Territory >
  {
  protected:
    uint32_t m_territoryTypeId;
    uint32_t m_guId;

    std::string m_placeName;
    std::string m_internalName;
    std::string m_bgPath;

    std::unordered_map< uint32_t, Entity::PlayerPtr > m_playerMap;
    std::unordered_map< uint32_t, Entity::BNpcPtr > m_bNpcMap;
    std::unordered_map< uint32_t, Entity::EventObjectPtr > m_eventObjects;
    std::unordered_map< uint32_t, Entity::AreaObjectPtr > m_playerAreaObjects;
    std::unordered_map< uint32_t, Entity::AreaObjectPtr > m_bNpcAreaObjects;

    std::unordered_map< uint32_t, std::shared_ptr< Common::BNpcCacheEntry > > m_bNpcBaseMap;

    Common::Weather m_currentWeather;
    Common::Weather m_weatherOverride;
    std::map< uint8_t, int32_t > m_weatherRateMap;

    uint64_t m_lastMobUpdate;
    uint64_t m_lastUpdate{};

    uint64_t m_lastActivityTime{};

    FestivalPair m_currentFestival;

    std::shared_ptr< Excel::ExcelStruct< Excel::TerritoryType > > m_territoryTypeInfo;

    uint32_t m_nextEObjId;
    uint32_t m_nextActorId;

    std::vector< SpawnInfo > m_spawnInfo;

    uint32_t m_effectCounter{};
    std::shared_ptr< Common::Navi::NaviProvider > m_pNaviProvider;

    Common::TerritoryIdent m_ident;

    float m_inRangeDistance;

  public:
    Territory();

    Territory( uint16_t territoryTypeId, uint32_t guId, const std::string& internalName, const std::string& placeName );

    virtual ~Territory();

    const Common::TerritoryIdent& getTerritoryIdent() const;

    /*! overrides the zone's weather, set to 0 to unlock */
    void setWeatherOverride( Common::Weather weather );

    Common::Weather getCurrentWeather() const;

    const FestivalPair& getCurrentFestival() const;

    void setCurrentFestival( uint16_t festivalId, uint16_t additionalFestivalId = 0 );

    std::shared_ptr< Excel::ExcelStruct< Excel::TerritoryType > > getTerritoryTypeInfo() const;

    uint64_t getLastActivityTime() const;

    virtual bool init();

    virtual uint32_t getTerritoryTypeId() const;

    virtual void onBeforePlayerZoneIn( Entity::Player& player ) {};

    virtual void onPlayerZoneIn( Entity::Player& player );

    virtual void onFinishLoading( Entity::Player& player );

    virtual void onInitDirector( Entity::Player& player );

    virtual void onDirectorSync( Entity::Player& player ) {};

    virtual void onLeaveTerritory( Entity::Player& player );

    virtual void onUpdate( uint64_t tickCount );

    virtual void onAddEObj( Entity::EventObjectPtr object ) {};

    virtual void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 );

    virtual void onEventHandlerOrder( Entity::Player& player, uint32_t arg0, uint32_t arg1, uint32_t arg2,
                                      uint32_t arg3, uint32_t arg4 );

    virtual float getInRangeDistance();

    Common::Weather getNextWeather();

    void pushActor( const Entity::GameObjectPtr& pActor );

    void removeActor( const Entity::GameObjectPtr &pActor );

    void updateActorPosition( Entity::GameObject& pActor );

    bool isCellActive( uint32_t x, uint32_t y );

    void updateCellActivity( uint32_t x, uint32_t y, int32_t radius );

    void updateInRangeSet( Entity::GameObjectPtr pActor, CellPtr pCell );

    void queuePacketForRange( Entity::Player& sourcePlayer, float range,
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

    bool loadBNpcs();

    bool checkWeather();
    virtual void updateBNpcs( uint64_t tickCount );

    bool update( uint64_t tickCount );

    void updateSessions( uint64_t tickCount, bool changedWeather );

    Entity::EventObjectPtr addEObj( const std::string& name, uint32_t objectId, uint32_t mapLink, uint32_t instanceId,
                                    uint8_t state, Common::FFXIVARR_POSITION3 pos, float scale,
                                    float rotation, uint8_t permissionInv );

    void addEObj( Entity::EventObjectPtr object );

    Entity::BNpcPtr createBNpcFromLayoutId( uint32_t levelId, uint32_t hp, Common::BNpcType bnpcType, uint32_t triggerOwnerId = 0 );
    Entity::BNpcPtr createBNpcFromLayoutIdNoPush( uint32_t levelId, uint32_t hp, Common::BNpcType bnpcType, uint32_t triggerOwnerId = 0 );

    Entity::BNpcPtr getActiveBNpcByEntityId( uint32_t entityId );

    Entity::BNpcPtr getActiveBNpcByLayoutId( uint32_t instanceId );

    Entity::BNpcPtr getActiveBNpcByLayoutIdAndTriggerOwner( uint32_t instanceId, uint32_t triggerOwnerId );

    Entity::EventObjectPtr getEObj( uint32_t objId );

    Entity::PlayerPtr getPlayer( uint32_t playerId );

    const std::unordered_map< uint32_t, Entity::PlayerPtr >& getPlayers();

    InstanceContentPtr getAsInstanceContent();

    QuestBattlePtr getAsQuestBattle();

    void updateSpawnPoints();

    uint32_t getNextActionResultId();

    std::shared_ptr< Common::Navi::NaviProvider > getNaviProvider();
  };

}

#endif
