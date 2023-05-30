#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AnabaseiosTheNinthCircleSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AnabaseiosTheNinthCircleSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30127 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2013313, 0, 4, { 110.000000f, -0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 9749538, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, -3.141593f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 82.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AnabaseiosTheNinthCircleSavage );