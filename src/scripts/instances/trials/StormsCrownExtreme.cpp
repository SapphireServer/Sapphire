#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class StormsCrownExtreme : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  StormsCrownExtreme() : Sapphire::ScriptAPI::InstanceContentScript( 20085 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Magitekarmor", 2012930, 0, 4, { 88.000000f, -0.000034f, 88.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 9319708, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, -0.000048f, 85.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2013052, 0, 4, { 99.770760f, -19.000000f, 176.985001f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2013167, 0, 4, { 99.976173f, -17.527321f, 197.329498f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( StormsCrownExtreme );