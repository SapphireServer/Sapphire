#include <memory>
#include <set>
#include <stack>
#include <Territory/InstanceContent.h>
#include <Logging/Logger.h>
#include <Actor/BNpc.h>
#include <Encounter/Forwards.h>

#include "Network/PacketDef/ServerIpcs.h"


namespace Sapphire
{
  enum class EncounterStatus
  {
    UNINITIALIZED,
    IDLE,
    ACTIVE,
    FAIL,
    SUCCESS
  };

  enum class EncounterShape
  {
    BOX,
    CYLINDER
  };

  enum class EncounterLogMessage : uint32_t
  {
    WillBeSealed = 2012,
    IsSealed = 2013,
    IsNoLongerSealed = 2014
  };

  enum class EncounterEntityRemoveFlag : uint8_t
  {
    None      = 0x00,
    OnFail    = 0x01,
    OnSuccess = 0x02,
  };

  struct EncounterEObj
  {
    std::string name;
    uint32_t baseId;
    uint32_t boundInstanceId;
    uint32_t instanceId;
    uint8_t state;
    Common::Vector3 pos;
    float scale;
    float rotation;
    uint8_t permissionInvisibility;
    EncounterEntityRemoveFlag entityRemoveFlag;
  };

  struct EncounterBNpc
  {
    uint32_t layoutId;
    uint32_t hp;
    Common::BNpcType type;
    uint32_t flags;
    bool isBoss{ false };
  };

  struct EncounterSetup
  {
    std::string timelineName;
    std::vector< EncounterBNpc > bnpcSetupList;
    std::vector< EncounterEObj > onInitEObjSetupList;
    std::vector< EncounterEObj > onSuccessEObjSetupList;
    std::vector< EncounterEObj > lockoutEntrances;
    std::vector< EncounterEObj > lockoutExits;

    EncounterShape encounterShape;
    // for BOX shape, this would be m_position = min, m_position2 = max
    // for CYLINDER m_position = center, m_position2.x radius, position2.y height
    Common::Vector3 position;
    Common::Vector3 position2;
    uint64_t duration{ 0 };    // todo: implement this
    uint32_t placeName{ 0 };

    // todo: all FATEs need bgm handling too, currently only instances are handled
    uint16_t bgmOnEnterRange{ 0 };          // todo: (FATE) implement this in onEnterRange, FATEs change bgm for player on entering
    uint16_t bgmOnExitRangeTeri{ 0 };       // todo: (FATE) implement this in onExitRange
    uint16_t bgmOnExitRangeTeriCombat{ 0 }; // todo: (FATE) implement this in onExitRange

    uint16_t bgmInCombat{ 0 };              // bgm when encounter is active

    uint16_t bgmToRestore{ 0 };             // default teri bgm, set when encounter has failed
    uint16_t bgmToRestoreCombat{ 0 };       // default teri combat bgm, set when encounter has failed

    uint16_t bgmOnFinishTeri{ 0 };          // new teri bgm after encounter success
    uint16_t bgmOnFinishTeriCombat{ 0 };    // new teri bgm in combat after encounter success // todo: implement this, sastasha uses different combat bgm for trash after first boss

    bool hasLockout{ false };
  };

  class Encounter : public std::enable_shared_from_this< Encounter >
  {
  public:
    Encounter( TerritoryPtr pInstance,
               Event::DirectorPtr pDirector,
               const std::string& timelineName );

    virtual ~Encounter();

    uint32_t getId() const;

    void init();

    void setEncounterSetup( const EncounterSetup& setup );

    virtual void start();

    virtual void update( uint64_t currTime );

    void reset();

    void removeBNpcs( bool removeBoss = false );

    void setStartTime( uint64_t startTime );

    EncounterStatus getStatus() const;

    void setStatus( EncounterStatus status );

    void addBNpc( Entity::BNpcPtr pBNpc, bool bind = false );

    Entity::BNpcPtr getBNpc( uint32_t layoutId ) const;

    void removeBNpc( uint32_t layoutId );

    void addPlayer( Entity::PlayerPtr pPlayer, bool bind = false );

    void removePlayer( Entity::PlayerPtr pPlayer );

    void removePlayers();

    const std::set< Entity::PlayerPtr >& getPlayers() const;

    const std::set< Entity::PlayerPtr >& getPlayersInside() const;

    const std::set< Entity::GameObjectPtr >& getActorsInside() const;

    TerritoryPtr getTeriPtr();

    Event::DirectorPtr getDirector();

    EncounterSetup& getSetup();

    uint64_t getLockoutTime() const;

    bool isLocked() const;

    virtual void onEnterRange( Entity::GameObjectPtr pActor );

    virtual void onExitRange( Entity::GameObjectPtr pActor );

    virtual void onChangeStatus( EncounterStatus oldStatus, EncounterStatus newStatus );

    virtual void onLockout();

    void setEntranceEObjLocked( bool locked );

    void setExitEObjLocked( bool locked );

    bool isPositionInside( const Common::Vector3& pos ) const;

    //void addEObj( Entity::EventObjectPtr pEObj );
    Entity::EventObjectPtr getEObjByBaseId( uint32_t baseId ) const;
    Entity::EventObjectPtr getEObjByName( const std::string& name ) const;
    void removeEObj( Entity::EventObjectPtr pEObj );
    void removeEObjs();

    bool canBindActors() const;
    void bindActor( Entity::GameObjectPtr pActor );
    void unbindActor( Entity::GameObjectPtr pActor );
    void unbindActors();
    bool isActorBound( Entity::GameObjectPtr pActor ) const;

  protected:
    uint32_t m_id{ 0 };
    uint64_t m_startTime{ 0 };
    uint64_t m_duration{ 0 }; // 0 for unlimited duration
    uint64_t m_lastTick{ 0 };
    uint64_t m_lastRangeTick{ 0 };
    uint64_t m_lockoutTime{ 0 };
    uint64_t m_failTime{ 0 };
    uint64_t m_finishTime{ 0 };
    uint32_t m_placeName{ 0 };

    Common::Vector3 m_position;

    // <name, pEObj >
    std::map< std::string, Entity::EventObjectPtr > m_eobjs;
    std::map< std::string, Entity::EventObjectPtr > m_entranceEObjs;
    std::map< std::string, Entity::EventObjectPtr > m_exitEObjs;
    std::map< std::string, EncounterEObj > m_setupEObjs;

    std::set< Entity::GameObjectPtr > m_actorsInside;
    std::set< Entity::GameObjectPtr > m_boundActors;
    std::set< Entity::PlayerPtr > m_playersInside;
    std::set< Entity::PlayerPtr > m_playerList;
    std::unordered_map< uint32_t, Entity::BNpcPtr > m_bnpcs;
    std::unordered_map< uint32_t, Entity::BNpcPtr > m_bossBnpcs;
    EncounterStatus m_status{ EncounterStatus::IDLE };
    Event::DirectorPtr m_pDirector;
    TerritoryPtr m_pTeri;
    std::shared_ptr< TimelinePack > m_pTimeline;

    // encountersetup
    EncounterSetup m_setup;

  };


}
