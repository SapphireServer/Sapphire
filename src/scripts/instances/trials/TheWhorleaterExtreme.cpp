#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheWhorleaterExtreme :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWhorleaterExtreme() :
    Sapphire::ScriptAPI::InstanceContentScript( 20018 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2003496, 4600311, 4, { 4.240293f, 0.025694f, 2.306607f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2003497, 4600310, 4, { 0.072974f, 0.025694f, 3.729535f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Elementalconverter", 2003498, 4600308, 4, { -0.068011f, 0.025694f, 18.829760f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2003499, 4600477, 4, { -0.427824f, 0.025694f, -1.602400f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2003503, 4536477, 4, { -4.721506f, 0.025694f, -0.558033f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 4600244, 5, { 2.559847f, 0.025694f, 16.605810f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.025694f, -15.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheWhorleaterExtreme );