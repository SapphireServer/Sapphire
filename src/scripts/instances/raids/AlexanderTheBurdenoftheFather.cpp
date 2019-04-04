#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheBurdenoftheFather :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheBurdenoftheFather() :
    Sapphire::ScriptAPI::InstanceContentScript( 30024 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005494, 5863691, 4, { 102.000000f, 43.646099f, 16.000000f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 5788043, 5, { -0.001985f, 10.900000f, 20.255680f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.015320f, 10.561610f, -23.025881f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlexanderTheBurdenoftheFather );