#include <Encounter/EncounterFight.h>

namespace Sapphire
{
  class IfritNormalData
  {
  public:
    static constexpr int IFRIT = 4126276;
    static constexpr int HELLFIRE = 0;
  };
  class IfritStateOne : public EncounterState
  {
  public:
    IfritStateOne( EncounterFightPtr pEncounter ) : EncounterState( pEncounter )
    {
    }

    void init() override
    {
      Logger::info( "ifrit FAN CLUB GEOcities <blink>EUNUCH ONLY</blink>" );
    }

    void update( double deltaTime ) override
    {
      auto pIfrit = m_pEncounter->getBNpc( IfritNormalData::IFRIT );
    }

    void finish() override
    {

    }
  };

  class IfritStateTwo : public EncounterState
  {
  public:
    IfritStateTwo( EncounterFightPtr pEncounter ) : EncounterState( pEncounter )
    {
    }

    void init() override
    {
      Logger::info( "ifrit FAN CLUB GEOcities <blink>EUNUCH ONLY</blink>" );
    }

    void update( double deltaTime ) override
    {
      auto pIfrit = m_pEncounter->getBNpc( IfritNormalData::IFRIT );
    }

    void finish() override
    {
    }
  };


  class IfritEncounterFight : public EncounterFight
  {
  public:
    IfritEncounterFight( InstanceContentPtr pInstance ) : EncounterFight( pInstance )
    {

    };

    void init() override
    {
      m_status = EncounterFightStatus::IDLE;

      m_stateStack = std::make_shared< EncounterState::StateStack >();

      // todo: i don't like this
      auto boss = m_pInstance->createBNpcFromLayoutId( IfritNormalData::IFRIT, 13884, Common::BNpcType::Enemy );
      addBNpc( boss );

      //instance.sendForward();
      /*
      auto ifritStateTwo = std::make_shared< IfritStateTwo >( m_stateStack );
      m_stateStack->push( ifritStateTwo );*/
    }

    void addState( EncounterState::EncounterStatePtr pState, bool initState = true ) override
    {
      m_stateStack->push( pState );
      if( initState )
        pState->init();
    }

    void start() override
    {
      auto ifritInitState = std::make_shared< IfritStateOne >( shared_from_this() );
      addState( ifritInitState );

      m_status = EncounterFightStatus::ACTIVE;
    }

    void update( double deltaTime ) override
    {
      if( m_stateStack; !m_stateStack->empty() )
      {
        if( m_stateStack->top()->shouldFinish() )
        {
          m_stateStack->top()->finish();
          m_stateStack->pop();
        }
          
        m_stateStack->top()->update( deltaTime );
      }
    }

    void reset() override
    {
      auto boss = m_pInstance->getActiveBNpcByLayoutId( IfritNormalData::IFRIT );
      m_pInstance->removeActor( boss );

      init();
    }

    EncounterFightStatus getEncounterFightStatus() const override
    {
      return m_status;
    }

    void addBNpc( Entity::BNpcPtr pBNpc ) override
    {
      m_bnpcs[ pBNpc->getLayoutId() ] = pBNpc;
    }

    Entity::BNpcPtr getBNpc( uint32_t layoutId ) override
    {
      auto bnpc = m_bnpcs.find( layoutId );
      if( bnpc != std::end( m_bnpcs ) )
        return bnpc->second;
    }
  };
}
