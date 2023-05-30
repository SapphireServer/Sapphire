#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheSeatofSacrifice : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSeatofSacrifice() : Sapphire::ScriptAPI::InstanceContentScript( 20071 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_n4ff_b2000", 2007457, 8372176, 4, { 99.992310f, 1.174927f, 99.992310f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8366049, 5, { 100.000000f, 0.000061f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000042f, 80.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Towerexit", 2011102, 0, 4, { 100.000000f, 1.500000f, 123.480003f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2011103, 0, 4, { 100.000000f, 0.000042f, 112.543404f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheSeatofSacrifice );