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

  enum class EncounterType
  {
    Fate,
    DungeonBoss,
    Trial
  };

  struct EncounterEObj
  {
    uint32_t eobjId{ 0xE0000000 };
    Common::Vector3 pos;
    float rot;
    float scale{ 1.0 };
    uint8_t permissionInvisibility{ 0 };
    uint8_t state{ 0 };
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
    EncounterType type;
    std::string timelineName;
    std::vector< EncounterBNpc > bnpcSetupList;
    std::vector< EncounterEObj > eobjSetupList;
    EncounterEObj lockoutEntrance;
    EncounterEObj lockoutExit;
    EncounterShape encounterShape;
    // for BOX shape, this would be m_position = min, m_position2 = max
    // for CYLINDER m_position = center, m_position2.x radius, position2.y height
    Common::Vector3 position;
    Common::Vector3 position2;
    uint64_t duration{ 0 };
    bool hasLockout{false};
  };

  class Encounter : public std::enable_shared_from_this< Encounter >
  {
  public:
    Encounter( TerritoryPtr pInstance,
               Event::DirectorPtr pDirector,
               const std::string& timelineName );

    virtual ~Encounter() = default;

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

    void addBNpc( Entity::BNpcPtr pBNpc );

    Entity::BNpcPtr getBNpc( uint32_t layoutId ) const;

    void removeBNpc( uint32_t layoutId );

    void addPlayer( Entity::PlayerPtr pPlayer, bool bind = false );

    void removePlayer( Entity::PlayerPtr pPlayer );

    const std::set< Entity::PlayerPtr >& getPlayers() const;

    TerritoryPtr getTeriPtr();

    Event::DirectorPtr getDirector();

    EncounterSetup& getSetup();

    uint32_t getLockoutTime() const;

    // todo:
    virtual void onEnterRange( Entity::GameObjectPtr pActor );

    virtual void onExitRange( Entity::GameObjectPtr pActor );

    virtual void onChangeStatus( EncounterStatus oldStatus, EncounterStatus newStatus );

    void setEntranceEObjLocked( bool locked );

    void setExitEObjLocked( bool locked );

    bool canBindActors() const;
    void bindActor( Entity::GameObjectPtr pActor );
    void unbindActor( Entity::GameObjectPtr pActor );
    void unbindActors();

  protected:
    uint32_t m_id{ 0 };
    EncounterType m_type;
    uint64_t m_startTime{ 0 };
    uint64_t m_duration{ 0 }; // 0 for unlimited duration
    uint64_t m_lastTick{ 0 };
    uint64_t m_lastRangeTick{ 0 };
    uint64_t m_lockoutTime{ 0 };
    uint64_t m_failTime{ 0 };
    uint64_t m_finishTime{ 0 };

    Common::Vector3 m_position;

    Entity::EventObjectPtr m_pEntranceEObj;
    Entity::EventObjectPtr m_pExitEObj;

    std::set< Entity::GameObjectPtr > m_boundActors;
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
