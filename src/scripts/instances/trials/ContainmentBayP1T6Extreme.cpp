#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ContainmentBayP1T6Extreme :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ContainmentBayP1T6Extreme() :
    Sapphire::ScriptAPI::InstanceContentScript( 20042 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007340, 6383469, 4, { -0.194161f, 0.000000f, 3.451970f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007442, 6424145, 4, { -5.251681f, 0.000000f, -1.313751f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007443, 0, 4, { -4.046182f, 0.000000f, 3.618896f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007449, 0, 4, { 2.914429f, -0.015320f, -2.731445f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2007464, 0, 4, { -0.015320f, -0.015320f, -14.419800f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_w_lvd_collison_only", 2002618, 6563705, 4, { 6.090889f, 0.000000f, -1.422338f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6392588, 5, { 0.132306f, 0.592461f, 10.611330f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.001971f, 0.000000f, -11.776730f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ContainmentBayP1T6Extreme );