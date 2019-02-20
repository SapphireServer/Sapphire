#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheUnendingCoilofBahamutUltimate :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheUnendingCoilofBahamutUltimate() :
    Sapphire::ScriptAPI::InstanceContentScript( 30057 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7040178, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7040443, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7040473, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7144982, 4, { 0.000000f, 0.017127f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 7075281, 4, { 0.000000f, 0.017127f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 7144855, 4, { 0.000000f, 0.017127f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -20.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7068018, 5, { 0.000000f, 0.000000f, 18.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheUnendingCoilofBahamutUltimate );