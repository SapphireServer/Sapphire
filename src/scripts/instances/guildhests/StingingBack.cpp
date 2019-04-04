#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class StingingBack :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  StingingBack() :
    Sapphire::ScriptAPI::InstanceContentScript( 10006 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 5021407, 5, { 623.000000f, 23.872311f, 94.505638f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 623.000000f, 23.656260f, 61.956181f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( StingingBack );