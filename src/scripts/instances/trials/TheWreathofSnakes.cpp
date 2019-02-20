#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheWreathofSnakes :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWreathofSnakes() :
    Sapphire::ScriptAPI::InstanceContentScript( 20060 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009660, 0, 4, { 112.312302f, 0.000000f, 94.229156f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2007457, 7719011, 5, { 100.000000f, 0.000000f, 116.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, -0.000007f, 85.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheWreathofSnakes );