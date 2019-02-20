#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFeastRanked :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFeastRanked() :
    Sapphire::ScriptAPI::InstanceContentScript( 40023 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2008986, 7403947, 4, { -58.000000f, 0.250000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2008987, 7403946, 4, { 58.000000f, 0.250000f, 0.000000f }, 1.000000f, -3.141593f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFeastRanked );