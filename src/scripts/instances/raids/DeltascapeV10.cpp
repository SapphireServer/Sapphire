#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class DeltascapeV10 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  DeltascapeV10() :
    Sapphire::ScriptAPI::InstanceContentScript( 30049 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 6791878, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 6885561, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 6852121, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6910535, 5, { 0.000000f, 0.000000f, 15.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -16.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( DeltascapeV10 );