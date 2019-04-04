#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheGreatHuntExtreme :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheGreatHuntExtreme() :
    Sapphire::ScriptAPI::InstanceContentScript( 20054 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Foothold", 2009423, 0, 4, { 100.000000f, -0.500001f, 110.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7187910, 5, { 93.347504f, -0.503487f, 116.806297f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, -0.500096f, 78.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheGreatHuntExtreme );