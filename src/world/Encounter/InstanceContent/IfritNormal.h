#include <Encounter/EncounterFight.h>

namespace Sapphire
{
  class IfritNormalData
  {
  public:
    static constexpr int IFRIT = 4126276;
    static constexpr int HELLFIRE = 0;
  };

  class IfritStateTwo : public EncounterState
  {
  public:
    IfritStateTwo( EncounterFightPtr pEncounter ) : EncounterState( pEncounter )
    {
    }

    void init() override
    {
      Logger::info( "stage 2 init" );
    }

    void update( uint64_t deltaTime ) override
    {
      if( m_startTime == 0 )
        m_startTime = deltaTime;

      auto timeElapsedMs = deltaTime - m_startTime;

      auto pIfrit = m_pEncounter->getBNpc( IfritNormalData::IFRIT );

      pIfrit->setRot( pIfrit->getRot() - .2f );
      pIfrit->sendPositionUpdate();

      if( timeElapsedMs > 5000 )
      {
        m_bShouldFinish = true;
      }
    }

    void finish() override
    {
      Logger::info( "stage 2 done, going back to stage 1" );
    }
  };


  class IfritStateOne : public EncounterState
  {
  public:
    IfritStateOne( EncounterFightPtr pEncounter ) : EncounterState( pEncounter )
    {
    }

    void init() override
    {
      Logger::info( "stage 1 init" );
    }

    void update( uint64_t deltaTime ) override
    {
      if( m_startTime == 0 )
        m_startTime = deltaTime;

      auto timeElapsedMs = deltaTime - m_startTime;

      auto pIfrit = m_pEncounter->getBNpc( IfritNormalData::IFRIT );

      pIfrit->setRot( pIfrit->getRot() + .2f );
      pIfrit->sendPositionUpdate();

      if( timeElapsedMs > 10000 )
      {
        m_bShouldFinish = true;
        return;
      }

      if( timeElapsedMs > 5000 )
      {
        auto ifritTwoState = std::make_shared< IfritStateTwo >( m_pEncounter );
        m_pEncounter->addState( ifritTwoState );
      }
    }

    void finish() override
    {
      Logger::info( "stage 1 finish - enrage" );

      auto pIfrit = m_pEncounter->getBNpc( IfritNormalData::IFRIT );
      pIfrit->hateListGetHighest()->die();
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
      m_startTime = 0;

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

    void update( uint64_t deltaTime ) override
    {
      // todo: better way to start fights here..

      auto ifrit = getBNpc( IfritNormalData::IFRIT );

      if( ifrit; ifrit->hateListGetHighestValue() != 0 && m_status == EncounterFightStatus::IDLE )
      {
        m_startTime = deltaTime;
        start();
      }

      if( m_status == EncounterFightStatus::ACTIVE && ifrit && !ifrit->hateListGetHighest()->isAlive() )
      {
        m_status = EncounterFightStatus::FAIL;
      }

      if( m_stateStack; !m_stateStack->empty() )
      {
        if( m_stateStack->top()->shouldFinish() )
        {
          m_stateStack->top()->finish();
          m_stateStack->pop();
        }

        if( !m_stateStack->empty() )
          m_stateStack->top()->update( deltaTime );
      }
    }

    void reset() override
    {
      auto boss = m_pInstance->getActiveBNpcByLayoutId( IfritNormalData::IFRIT );
      if( boss )
      {
        removeBNpc( IfritNormalData::IFRIT );
        m_pInstance->removeActor( boss );
        
      }

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

      return nullptr;
    }

    void removeBNpc( uint32_t layoutId ) override
    {
       m_bnpcs.erase( layoutId );
    }
  };
}
