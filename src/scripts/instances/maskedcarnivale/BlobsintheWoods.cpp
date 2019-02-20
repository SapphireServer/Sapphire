#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class BlobsintheWoods :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  BlobsintheWoods() :
    Sapphire::ScriptAPI::InstanceContentScript( 35014 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 7676036, 5, { 100.000000f, 2.000000f, 113.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_0", 2002618, 7738683, 4, { 96.000000f, 2.000000f, 104.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009702, 7767980, 4, { 103.000000f, 2.000000f, 105.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2009703, 7767985, 4, { 101.000000f, 2.000000f, 88.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2009704, 7767987, 4, { 100.053703f, 5.599999f, 100.556702f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( BlobsintheWoods );