#include <Encounter/EncounterFight.h>

#include <Encounter/EncounterTimeline.h>

namespace Sapphire
{
  class IfritEncounterFight : public EncounterFight
  {
  private:
    static constexpr int NPC_IFRIT = 4126276;
    static constexpr int VAL_IFRIT_HP = 13884;
    static constexpr int ACT_HELLFIRE = 0;

  public:
    IfritEncounterFight( InstanceContentPtr pInstance ) : EncounterFight( pInstance )
    {
      pInstance->setEncounterTimeline( "IfritNormal" );
    };

    void init() override
    {
      m_status = EncounterFightStatus::IDLE;
      m_startTime = 0;

      m_stateStack = std::make_shared< EncounterState::StateStack >();

      // todo: i don't like this
      auto boss = m_pInstance->createBNpcFromLayoutId( NPC_IFRIT, VAL_IFRIT_HP, Common::BNpcType::Enemy );
      boss->init();
      addBNpc( boss );
    }

    void start() override
    {
      auto ifritInitState = makeIfritPhaseOneState();

      addState( ifritInitState );

      m_status = EncounterFightStatus::ACTIVE;
    }
    
    void reset() override
    {
      if( auto boss = m_pInstance->getActiveBNpcByLayoutId( NPC_IFRIT ); boss )
      {
        removeBNpc( NPC_IFRIT );
        m_pInstance->removeActor( boss );
      }
      m_pInstance->getEncounterTimeline().reset( getInstance() );

      init();
    }

    EncounterStatePtr makeIfritPhaseOneState()
    {
      auto ifritInitState = std::make_shared< EncounterState >( shared_from_this() );
      ifritInitState->setOnUpdateCallback( [ & ]( EncounterFightPtr pEncounter, EncounterState state )
        {
          auto timeElapsedMs = state.getElapsedTime();

          auto pIfrit = pEncounter->getBNpc( NPC_IFRIT );

          pIfrit->setRot( pIfrit->getRot() + .2f );

          // todo: use gambits+timelines for this
          if( timeElapsedMs > 10000 )
          {
            state.setFinishFlag();
            return;
          }

          // todo: use gambits+timelines for this
          if( timeElapsedMs > 5000 )
          {
            auto ifritTwoState = makeIfritPhaseTwoState();
            pEncounter->addState( ifritTwoState );
          }
        }
      );

      ifritInitState->setOnFinishCallback( [ & ]( EncounterFightPtr pEncounter, EncounterState state )
        {
          Logger::info( "stage 1 finish - enrage" );

          auto pIfrit = pEncounter->getBNpc( NPC_IFRIT );
          pIfrit->hateListGetHighest()->die();
        }
      );

      return ifritInitState;
    }

    EncounterStatePtr makeIfritPhaseTwoState()
    {
      auto ifritTwoState = std::make_shared< EncounterState >( shared_from_this() );
      ifritTwoState->setOnUpdateCallback( [ & ]( EncounterFightPtr pEncounter, EncounterState state ) {
        auto timeElapsedMs = state.getElapsedTime();

        auto pIfrit = pEncounter->getBNpc( NPC_IFRIT );

        pIfrit->setRot( pIfrit->getRot() - .2f );

        // todo: use gambits+timelines for this
        if( timeElapsedMs > 5000 )
        {
          state.setFinishFlag();
        }
      } );

      return ifritTwoState;
    }

    void update( uint64_t deltaTime ) override
    {
      // todo: better way to start fights here..
      // this probably doesn't need to be overriden either

      auto ifrit = getBNpc( NPC_IFRIT );

      if( ifrit; ifrit->hateListGetHighestValue() != 0 && m_status == EncounterFightStatus::IDLE )
      {
        m_startTime = deltaTime;
        start();
      }

      if( m_status == EncounterFightStatus::ACTIVE && ifrit && (!ifrit->hateListGetHighest() || !ifrit->hateListGetHighest()->isAlive() ) )
      {
        m_status = EncounterFightStatus::FAIL;
      }

      m_pInstance->getEncounterTimeline().update( getInstance(), deltaTime );

      //*
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
      //*/
    }
  };
}