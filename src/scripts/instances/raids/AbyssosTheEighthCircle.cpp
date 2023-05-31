#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AbyssosTheEighthCircle : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AbyssosTheEighthCircle() : Sapphire::ScriptAPI::InstanceContentScript( 30122 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 9337056, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 79.823174f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "PassagetoPandmonium", 2013032, 0, 4, { 99.998100f, 1.151500f, 120.237198f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AbyssosTheEighthCircle );