#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheJadeStoa :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheJadeStoa() :
    Sapphire::ScriptAPI::InstanceContentScript( 20051 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009431, 0, 4, { -2.722647f, -0.000001f, 7.311604f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7174720, 5, { 5.504887f, 0.000000f, 14.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -14.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7181535, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2009214, 0, 4, { 2.987230f, 0.000000f, -2.908927f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheJadeStoa );