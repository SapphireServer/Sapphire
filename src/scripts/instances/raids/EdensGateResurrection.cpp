#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class EdensGateResurrection : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  EdensGateResurrection() : Sapphire::ScriptAPI::InstanceContentScript( 30078 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7920817, 4, { 105.479103f, -0.000000f, 106.369301f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 7923948, 4, { 105.479103f, -0.000000f, 106.369301f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 7919517, 4, { 60.000000f, 0.000000f, 60.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 7921141, 4, { 60.000000f, 0.000000f, 60.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8009831, 4, { 105.479103f, -0.000000f, 106.369301f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2010540, 0, 4, { 89.325417f, 0.000000f, 100.184502f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2010656, 0, 4, { 109.350800f, 0.000000f, 93.897614f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 7917644, 5, { 100.000000f, 0.000000f, 116.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( EdensGateResurrection );