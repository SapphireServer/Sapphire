#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Encounter/Encounter.h>

using namespace Sapphire;

class TheBowlofEmbers : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  static constexpr int NPC_IFRIT = 4126276;
  static constexpr int VAL_IFRIT_HP = 13884;

  TheBowlofEmbers() : Sapphire::ScriptAPI::InstanceContentScript( 20001 )
  { }

  void setupEncounter( InstanceContent& instance, EncounterPtr pEncounter )
  {
    pEncounter->init();
    auto boss = instance.createBNpcFromLayoutId( NPC_IFRIT, VAL_IFRIT_HP, Common::BNpcType::Enemy );
    boss->init();
    pEncounter->addBNpc( boss );
  }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "Entrance", 2000182, 4177874, 4177871, 5, { -16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0);
    auto pEncounter = std::make_shared< Encounter >( instance.shared_from_this()->getAsInstanceContent(),
      std::static_pointer_cast< Event::Director >( instance.shared_from_this()->getAsInstanceContent() ), "IfritNormal" );
    setupEncounter( instance, pEncounter );
    //instance.setEncounterTimeline(  );
    instance.setEncounter( pEncounter );
  }

  void onReset( InstanceContent& instance ) override
  {
    auto pEncounter = instance.getEncounter();
    if( !pEncounter )
      return;
    setupEncounter( instance, pEncounter );
  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {
    auto pEncounter = instance.getEncounter();
    if( pEncounter )
    {

      // Fight start condition
      auto ifrit = pEncounter->getBNpc( NPC_IFRIT );
      if( ifrit && ifrit->hateListGetHighestValue() != 0 && pEncounter->getStatus() == EncounterStatus::IDLE )
      {
        pEncounter->setStartTime( tickCount );
        pEncounter->start();
      }

      // Fight end condition
      if( pEncounter->getStatus() == EncounterStatus::ACTIVE && ifrit && ( !ifrit->isAlive() ) )
      {
        //Logger::debug( "Setting duty state to failed!" );
        pEncounter->setStatus( EncounterStatus::SUCCESS );
      }
    }
  }

  void onStateChange( InstanceContent& instance, InstanceContentState oldState, InstanceContentState newState ) override
  {
    switch( newState )
    {
      case InstanceContentState::DutyFinished:
      {
        instance.addEObj( "Exit", 2000139, 0, 4177870, 4, { 16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0);
      }
    }
  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheBowlofEmbers );