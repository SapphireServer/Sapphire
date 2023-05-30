#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CinderDrift : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CinderDrift() : Sapphire::ScriptAPI::InstanceContentScript( 20068 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8240448, 5, { 99.794296f, -0.000000f, 114.723198f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, -0.000000f, 84.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2007457, 8240696, 4, { 100.000000f, -0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 8257763, 4, { 100.000000f, -0.000000f, 100.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CinderDrift );