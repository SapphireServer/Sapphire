#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlphascapeV40 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlphascapeV40() :
    Sapphire::ScriptAPI::InstanceContentScript( 30072 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7570953, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7624865, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7624868, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7624869, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 7624870, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 7624871, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 7624872, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 7624873, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 7672994, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7581279, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, -0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 84.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlphascapeV40 );