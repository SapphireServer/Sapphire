#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheStrikingTreeHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheStrikingTreeHard() : Sapphire::ScriptAPI::InstanceContentScript( 20022 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "Entrance", 2000182, 4712008, 4712006, 5, { 5.026201f, 74.994751f, 16.039301f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 4712009, 4, { 0.000000f, 75.000000f, -7.671923f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheStrikingTreeHard );