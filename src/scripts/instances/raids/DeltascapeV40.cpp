#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class DeltascapeV40 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  DeltascapeV40() :
    Sapphire::ScriptAPI::InstanceContentScript( 30052 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 6925502, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 6925503, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 6925504, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 6936015, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 6865650, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 6872744, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2008483, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -17.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6914211, 5, { 0.000000f, 0.000000f, 15.000000f }, 1.000000f, 0.000000f ); 
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

EXPOSE_SCRIPT( DeltascapeV40 );