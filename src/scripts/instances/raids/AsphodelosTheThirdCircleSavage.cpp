#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AsphodelosTheThirdCircleSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AsphodelosTheThirdCircleSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30110 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8902761, 5, { 100.000000f, 0.000000f, 115.666298f }, 0.991760f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 88.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2011748, 0, 4, { 86.000000f, 0.000000f, 94.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AsphodelosTheThirdCircleSavage );