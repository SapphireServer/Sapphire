#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheDarkInside : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheDarkInside() : Sapphire::ScriptAPI::InstanceContentScript( 20080 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8860026, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 99.992310f, -0.015320f, 93.180382f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "ExittoMareLamentorum", 2012528, 0, 4, { 100.020599f, 0.778128f, 118.250000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2012122, 0, 4, { 99.966240f, 0.000000f, 103.254501f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheDarkInside );