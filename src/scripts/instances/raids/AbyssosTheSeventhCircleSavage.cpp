#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AbyssosTheSeventhCircleSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AbyssosTheSeventhCircleSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30119 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 9325466, 5, { 100.000000f, 0.000000f, 116.500000f }, 1.000000f, -3.141593f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 87.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AbyssosTheSeventhCircleSavage );