#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class EmanationExtreme :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  EmanationExtreme() :
    Sapphire::ScriptAPI::InstanceContentScript( 20049 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 6894521, 5, { 0.000796f, 0.035467f, 12.032630f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.062970f, -12.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( EmanationExtreme );