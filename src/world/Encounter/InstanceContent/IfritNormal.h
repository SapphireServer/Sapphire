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
      m_startTime = 0;

      // todo: i don't like this
      auto boss = m_pInstance->createBNpcFromLayoutId( NPC_IFRIT, VAL_IFRIT_HP, Common::BNpcType::Enemy );
      boss->init();
      addBNpc( boss );
    }

    void start() override
    {

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
      m_pInstance->getEncounterTimeline().update( getInstance(), deltaTime );
    }
  };
}// namespace Sapphire