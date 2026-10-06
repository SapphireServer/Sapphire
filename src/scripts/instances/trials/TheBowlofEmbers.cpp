#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Encounter/Encounter.h>
#include <Actor/Player.h>

using namespace Sapphire;
using namespace Sapphire::World::Encounter;

class TheBowlofEmbers : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  static constexpr int NPC_IFRIT = 4126276;
  static constexpr int VAL_IFRIT_HP = 13884;

  TheBowlofEmbers() : Sapphire::ScriptAPI::InstanceContentScript( 20001 )
  {}

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "Entrance", 2000182, 4177874, 4177871, 5, { -16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 );

    auto instanceContent = instance.shared_from_this()->getAsInstanceContent();
    auto director = std::static_pointer_cast< Event::Director >( instanceContent );

    EncounterDefinition def;
    def.key = "Ifrit";
    def.timeline = "trials/IfritNormal";
    def.shape = EncounterShape::CYLINDER;
    def.position = { 0, 0, 0 };   // centre
    def.position2 = { 80, 10, 0 };// radius, height, unused
    def.hasLockout = true;
    def.participants = {
      { NPC_IFRIT, VAL_IFRIT_HP, Common::BNpcType::Enemy, Entity::BNpcFlag::NoRoam, EncounterBNpcCompletionRole::Required }
    };

    auto pEncounter = std::make_shared< World::Encounter::Encounter >( instanceContent, director, def );
    instance.setControllerEncounter( pEncounter );
    pEncounter->init();
  }

  void onReset( InstanceContent& instance ) override
  {
  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {
    auto pEncounter = instance.getControllerEncounter();
    if( pEncounter )
    {
      // Fight start condition
      auto ifrit = pEncounter->getBNpc( NPC_IFRIT );
      if( ifrit && ifrit->hateListGetHighestValue() != 0 && pEncounter->getStatus() == EncounterStatus::IDLE )
      {
        pEncounter->setStartTime( tickCount );
        pEncounter->start();
      }

      pEncounter->update( tickCount );

      // Fight end condition
      if( pEncounter->getStatus() != EncounterStatus::SUCCESS )
      {
        if( ifrit && ( !ifrit->isAlive() ) )
        {
          //Logger::debug( "Setting duty state to failed!" );
          pEncounter->setStatus( EncounterStatus::SUCCESS );
          instance.setState( InstanceContentState::DutyFinished );
        }
      }

      auto deadPlayers = 0;
      for( const auto& player : instance.getPlayers() )
      {
        if( player.second->getHp() != 0 )
          break;

        ++deadPlayers;
      }

      if( deadPlayers == instance.getInstancePlayerCount() )
      {
        pEncounter->setStatus( EncounterStatus::FAIL );
        instance.setState( InstanceContentState::DutyReset );
      }
    }
  }

  void onStateChange( InstanceContent& instance, InstanceContentState oldState, InstanceContentState newState ) override
  {
    switch( newState )
    {
      case InstanceContentState::DutyFinished:
      {
        instance.addEObj( "Exit", 2000139, 0, 4177870, 4, { 16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 );
        break;
      }
      default:
        break;
    }
  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {
  }
};

EXPOSE_SCRIPT( TheBowlofEmbers );