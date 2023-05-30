#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class EdensPromiseEternitySavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  EdensPromiseEternitySavage() : Sapphire::ScriptAPI::InstanceContentScript( 30104 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 75.000000f, -92.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 8551190, 5, { 86.077698f, 0.000000f, -28.009600f }, 1.000000f, -0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Entrance_1", 2000182, 8551213, 5, { 0.000000f, 75.000000f, -61.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( EdensPromiseEternitySavage );