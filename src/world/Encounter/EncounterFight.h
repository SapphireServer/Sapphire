#include <memory>
#include <set>
#include <stack>
#include <Territory/InstanceContent.h>
#include <Logging/Logger.h>
#include <Actor/BNpc.h>

namespace Sapphire
{
  class EncounterState
  {
  public:
    using EncounterStatePtr = std::shared_ptr< EncounterState >;
    using StateStack = std::stack< EncounterStatePtr >;
    using StateStackPtr = std::shared_ptr< StateStack >;

  protected:
    bool m_bShouldFinish{ false };
    StateStackPtr m_stateStack;
    std::shared_ptr< EncounterFight > m_pEncounter;
    uint64_t m_startTime{ 0 };

  public:
    EncounterState( std::shared_ptr< EncounterFight > pEncounter ) :
      m_pEncounter( pEncounter )
    {
    };

    virtual ~EncounterState() = default;
    bool shouldFinish() { return m_bShouldFinish; };

    virtual void init() = 0;
    virtual void update( uint64_t deltaTime ) = 0;

    virtual void finish() = 0;
  };

  enum class EncounterFightStatus
  {
    IDLE,
    ACTIVE,
    FAIL,
    SUCCESS
  };

  class EncounterFight : public std::enable_shared_from_this< EncounterFight >
  {
  public:
    EncounterFight( InstanceContentPtr pInstance ) :
      m_pInstance( pInstance )
    {
    };
    virtual ~EncounterFight() = default;

    virtual void init() = 0;
    virtual void start() = 0;
    virtual void update( uint64_t deltaTime ) = 0;
    virtual void reset() = 0;

    virtual void addState( EncounterState::EncounterStatePtr pState, bool initState = true ) = 0;
    virtual void addBNpc( Entity::BNpcPtr pBNpc ) = 0;
    virtual void removeBNpc( uint32_t layoutId ) = 0;
    virtual Entity::BNpcPtr getBNpc( uint32_t layoutId ) = 0;

    virtual EncounterFightStatus getEncounterFightStatus() const = 0;

  protected:
    uint64_t m_startTime{ 0 };
    EncounterState::StateStackPtr m_stateStack;
    std::set< Entity::PlayerPtr > m_playerList;
    std::unordered_map< uint32_t, Entity::BNpcPtr > m_bnpcs;
    InstanceContentPtr m_pInstance;
    EncounterFightStatus m_status{ EncounterFightStatus::IDLE };
  };
}