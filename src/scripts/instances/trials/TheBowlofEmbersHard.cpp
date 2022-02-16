#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheBowlofEmbersHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheBowlofEmbersHard() : Sapphire::ScriptAPI::InstanceContentScript( 20004 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "Entrance", 2000182, 4177874, 4177871, 5, { -16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 4177870, 4, { 16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheBowlofEmbersHard );