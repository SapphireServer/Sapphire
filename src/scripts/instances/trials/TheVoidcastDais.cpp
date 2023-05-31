#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheVoidcastDais : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheVoidcastDais() : Sapphire::ScriptAPI::InstanceContentScript( 20089 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 9807563, 5, { 100.000000f, 0.000000f, 112.000000f }, 1.000000f, -0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 89.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Entrance", 2013364, 0, 4, { 100.000000f, 0.030000f, 101.828201f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exittotheredmoon", 2013366, 0, 4, { 100.000000f, 0.800000f, 114.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Gatetotheredmoon", 2013444, 0, 4, { 100.000000f, 0.800000f, 114.500000f }, 1.000000f, -0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheVoidcastDais );