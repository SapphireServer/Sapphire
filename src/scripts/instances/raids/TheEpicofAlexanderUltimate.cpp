#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheEpicofAlexanderUltimate : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheEpicofAlexanderUltimate() : Sapphire::ScriptAPI::InstanceContentScript( 30086 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 8150078, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 8150079, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 8150080, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 8150081, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8150082, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8150083, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8150084, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8150085, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 8132875, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 83.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheEpicofAlexanderUltimate );