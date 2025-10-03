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

  struct EncounterActor
  {
    uint32_t layoutId;
    uint32_t hp;
    Common::BNpcType type;
    uint32_t flags;
  };

  struct EncounterSetup
  {
    std::string timelineName;
    std::vector< EncounterActor > actorSetupList;
    EncounterShape encounterShape;
    // for BOX shape, this would be m_position = min, m_position2 = max
    // for CYLINDER m_position = center, m_position2.x radius, position2.y height
    Common::FFXIVARR_POSITION3 position;
    Common::FFXIVARR_POSITION3 position2;
    bool hasLockout{false};
  };

  class Encounter : public std::enable_shared_from_this< Encounter >
  {
  public:
    Encounter( TerritoryPtr pInstance,
               Event::DirectorPtr pDirector,
               const std::string& timelineName );

    virtual ~Encounter() = default;

    void init();

    virtual void start();

    virtual void update( uint64_t currTime );

    void reset();

    void removeBNpcs();

    void setStartTime( uint64_t startTime );

    EncounterStatus getStatus() const;

    void setStatus( EncounterStatus status );

    void addBNpc( Entity::BNpcPtr pBNpc );

    Entity::BNpcPtr getBNpc( uint32_t layoutId ) const;

    void removeBNpc( uint32_t layoutId );

    TerritoryPtr getTeriPtr();

    Event::DirectorPtr getDirector();

    void setInitialActorSetup( const std::vector< EncounterActor >& actorSetupList );

    EncounterSetup& getSetup();

  protected:
    uint64_t m_startTime{ 0 };

    std::set< Entity::PlayerPtr > m_playerList;
    std::unordered_map< uint32_t, Entity::BNpcPtr > m_bnpcs;
    EncounterStatus m_status{ EncounterStatus::IDLE };
    Event::DirectorPtr m_pDirector;
    TerritoryPtr m_pTeri;
    std::shared_ptr< TimelinePack > m_pTimeline;

    // encountersetup
    EncounterSetup m_setup;

  };


}
