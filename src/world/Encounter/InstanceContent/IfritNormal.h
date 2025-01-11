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

      if( m_status == EncounterFightStatus::ACTIVE && ifrit && ( !ifrit->hateListGetHighest() || !ifrit->hateListGetHighest()->isAlive() ) )
      {
        m_status = EncounterFightStatus::FAIL;
      }

      m_pInstance->getEncounterTimeline().update( getInstance(), deltaTime );

    }
  };
}// namespace Sapphire