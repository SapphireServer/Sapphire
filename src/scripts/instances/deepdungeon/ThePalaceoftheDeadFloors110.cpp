#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ThePalaceoftheDeadFloors110 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThePalaceoftheDeadFloors110() :
    Sapphire::ScriptAPI::InstanceContentScript( 60001 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0959", 2002872, 6324883, 4, { -300.000000f, -0.000010f, -220.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_on2off (id: 4) vf_bextwall_off (id: 10) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ThePalaceoftheDeadFloors110 );