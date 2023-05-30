#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheMinstrelsBalladHydaelynsCall : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheMinstrelsBalladHydaelynsCall() : Sapphire::ScriptAPI::InstanceContentScript( 20078 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8860246, 5, { 100.000000f, 0.000004f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2012230, 0, 4, { 99.959557f, -0.000000f, 99.858963f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exittotheaetherialsea", 2012341, 0, 4, { 100.000000f, 1.000000f, 123.580597f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheMinstrelsBalladHydaelynsCall );