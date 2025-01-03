#include <memory>
#include <set>
#include <stack>
#include <Territory/InstanceContent.h>
#include <Logging/Logger.h>
#include <Actor/BNpc.h>

namespace Sapphire
{
  using EncounterCallback = std::function< void( EncounterFightPtr, EncounterState ) >;

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
    uint64_t m_currTime{ 0 };

    EncounterCallback m_onInitCb;
    EncounterCallback m_onUpdateCb;
    EncounterCallback m_onFinishCb;

  public:
    EncounterState( std::shared_ptr< EncounterFight > pEncounter ) :
      m_pEncounter( pEncounter )
    {
    };

    bool shouldFinish() const { return m_bShouldFinish; };

    void setFinishFlag() { m_bShouldFinish = true; };

    uint64_t getStartTime() const { return m_startTime; };
    uint64_t getCurrTime() const { return m_currTime; };
    uint64_t getElapsedTime() const { return m_currTime - m_startTime; };

    void init()
    {
      if( m_onInitCb )
        m_onInitCb( m_pEncounter, *this );
    }

    void update( uint64_t currTime )
    {
      if( m_startTime == 0 )
        m_startTime = currTime;

      m_currTime = currTime;

      if( m_onUpdateCb )
        m_onUpdateCb( m_pEncounter, *this );
    }

    void finish()
    {
      if( m_onFinishCb )
        m_onFinishCb( m_pEncounter, *this );
    }

    void setOnInitCallback( EncounterCallback cb )
    {
      m_onInitCb = cb;
    }

    void setOnUpdateCallback( EncounterCallback cb )
    {
      m_onUpdateCb = cb;
    }

    void setOnFinishCallback( EncounterCallback cb )
    {
      m_onFinishCb = cb;
    }
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
    virtual void update( uint64_t currTime ) = 0;
    virtual void reset() = 0;

    void addState( EncounterState::EncounterStatePtr pState, bool initState = true )
    {
      m_stateStack->push( pState );
      if( initState )
        pState->init();
    }

    EncounterFightStatus getEncounterFightStatus() const
    {
      return m_status;
    }

    void addBNpc( Entity::BNpcPtr pBNpc )
    {
      m_bnpcs[ pBNpc->getLayoutId() ] = pBNpc;
    }

    Entity::BNpcPtr getBNpc( uint32_t layoutId ) const
    {
      auto bnpc = m_bnpcs.find( layoutId );
      if( bnpc != std::end( m_bnpcs ) )
        return bnpc->second;

      return nullptr;
    }

    void removeBNpc( uint32_t layoutId )
    {
      m_bnpcs.erase( layoutId );
    }

    InstanceContentPtr getInstance()
    {
      return m_pInstance;
    }

  protected:
    uint64_t m_startTime{ 0 };
    EncounterState::StateStackPtr m_stateStack;
    std::set< Entity::PlayerPtr > m_playerList;
    std::unordered_map< uint32_t, Entity::BNpcPtr > m_bnpcs;
    InstanceContentPtr m_pInstance;
    EncounterFightStatus m_status{ EncounterFightStatus::IDLE };
  };
}