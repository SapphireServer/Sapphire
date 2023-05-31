#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AsphodelosTheSecondCircleSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AsphodelosTheSecondCircleSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30114 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8883650, 5, { 103.680603f, 0.807500f, 119.713898f }, 1.000000f, -3.141593f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.171898f, 0.027640f, 80.504860f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AsphodelosTheSecondCircleSavage );