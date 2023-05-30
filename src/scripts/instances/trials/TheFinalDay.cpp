#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFinalDay : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFinalDay() : Sapphire::ScriptAPI::InstanceContentScript( 20079 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8865316, 5, { 100.000000f, 0.000000f, 109.849998f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2012371, 0, 4, { 100.000000f, 0.000000f, 106.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2012380, 0, 4, { 100.000000f, 1.300000f, 119.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFinalDay );