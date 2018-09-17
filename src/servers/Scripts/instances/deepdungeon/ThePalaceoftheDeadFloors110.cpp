#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThePalaceoftheDeadFloors110 :
  public InstanceContentScript
{
public:
  ThePalaceoftheDeadFloors110() :
    InstanceContentScript( 60001 )
  {
  }

  void onInit( InstanceContentPtr instance ) override
  {
    instance->registerEObj( "sgvf_w_lvd_b0959", 2002872, 6324883, 4, { -300.000000f, -0.000010f, -220.000000f },
                            1.000000f, 0.000000f );
    // States -> vf_bextwall_on vf_bextwall_on2off vf_bextwall_off

  }

  void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};