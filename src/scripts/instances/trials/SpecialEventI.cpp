#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SpecialEventI :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SpecialEventI() :
    Sapphire::ScriptAPI::InstanceContentScript( 20015 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 7579598, 5, { 107.893997f, 0.000000f, 114.054703f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 99.992310f, -0.015320f, 85.984497f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_0", 2007457, 7587533, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SpecialEventI );