#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheMinstrelsBalladHadessElegy : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheMinstrelsBalladHadessElegy() : Sapphire::ScriptAPI::InstanceContentScript( 20067 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 8058261, 4, { 91.611221f, 0.000000f, 108.424103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 8058263, 4, { 91.611221f, 0.000000f, 108.424103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 8058264, 4, { 93.150467f, 0.000000f, 108.424103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 8058258, 4, { 98.017128f, -0.000000f, 98.795761f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8058465, 4, { 93.218163f, 0.000000f, 111.359100f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, -0.000000f, 85.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8097018, 5, { 97.074989f, -0.000000f, 115.178299f }, 1.000000f, 0.000000f); 
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

EXPOSE_SCRIPT( TheMinstrelsBalladHadessElegy );