#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFinalStepsofFaith :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFinalStepsofFaith() :
    Sapphire::ScriptAPI::InstanceContentScript( 20039 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007132, 0, 4, { 1.180504f, -0.000001f, -5.348264f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007360, 0, 4, { 0.893822f, -0.000029f, 9.867915f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6243772, 5, { 5.791933f, 0.049998f, 17.147869f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.802442f, 0.050000f, -16.948071f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007393, 6279966, 4, { 0.867247f, -0.000024f, 9.141238f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFinalStepsofFaith );