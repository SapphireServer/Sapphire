#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AbyssosTheFifthCircle : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AbyssosTheFifthCircle() : Sapphire::ScriptAPI::InstanceContentScript( 30116 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 9324128, 5, { 100.000000f, 0.000000f, 111.000000f }, 1.000000f, -3.141593f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, -300.000000f, 90.000000f }, 1.000000f, -3.141593f); 
    instance.registerEObj( "Entrance_1", 2007457, 9324144, 5, { 100.000000f, -300.000000f, 111.000000f }, 1.000000f, -3.141593f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit_1", 2000139, 0, 4, { 100.000000f, -300.000000f, 90.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AbyssosTheFifthCircle );