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

  protected:
    uint64_t m_startTime{ 0 };
    std::string m_timelineName;
    std::set< Entity::PlayerPtr > m_playerList;
    std::unordered_map< uint32_t, Entity::BNpcPtr > m_bnpcs;
    TerritoryPtr m_pTeri;
    EncounterStatus m_status{ EncounterStatus::IDLE };
    std::shared_ptr< TimelinePack > m_pTimeline;
    Event::DirectorPtr m_pDirector;
  };


}
