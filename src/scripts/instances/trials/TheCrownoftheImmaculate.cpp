#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheCrownoftheImmaculate : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheCrownoftheImmaculate() : Sapphire::ScriptAPI::InstanceContentScript( 20064 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2010432, 0, 4, { 91.575500f, 0.001966f, 90.355698f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4fb_b1637", 2007457, 7953397, 4, { 110.500000f, 0.001966f, 89.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4fb_b1637_1", 2007457, 7953398, 4, { 110.500000f, 0.001965f, 110.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4fb_b1637_2", 2007457, 7953399, 4, { 89.500000f, 0.001966f, 110.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4fb_b1637_3", 2007457, 7953400, 4, { 89.500000f, 0.001966f, 89.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 7931192, 5, { 100.000000f, 0.445493f, 115.757401f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.001966f, 84.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "ExittoKholusia", 2010600, 0, 4, { 94.813919f, -74.000000f, 703.867615f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "ExittoKholusia_1", 2010601, 0, 4, { 99.999161f, 1.200000f, 119.166100f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2010234, 0, 4, { 108.748398f, -75.028229f, 689.935120f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheCrownoftheImmaculate );