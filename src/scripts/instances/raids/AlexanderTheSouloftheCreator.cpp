#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheSouloftheCreator :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheSouloftheCreator() :
    Sapphire::ScriptAPI::InstanceContentScript( 30042 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 400.000000f, -21.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2007468, 0, 4, { 14.140000f, 400.049988f, -14.140000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007468, 0, 4, { 14.140000f, 400.049988f, -14.140000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007468, 0, 4, { 14.140000f, 400.049988f, 14.140000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007468, 0, 4, { -14.140000f, 400.049988f, -14.140000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007468, 0, 4, { -14.140000f, 400.049988f, 14.140000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007519, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_6", 2007520, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_7", 2007521, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 6421491, 4, { 0.000000f, 400.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007516, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 6487368, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 6487369, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 6487367, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 6487366, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007457, 6483882, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007457, 6421479, 4, { 0.000000f, 400.168701f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2007499, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_17", 2007534, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_18", 2007457, 6539545, 4, { 0.024963f, -480.000000f, 52.037621f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6449508, 5, { -0.015367f, 400.000000f, 21.278250f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlexanderTheSouloftheCreator );