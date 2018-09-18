#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThePalaceoftheDeadFloors2130 :
  public InstanceContentScript
{
public:
  ThePalaceoftheDeadFloors2130() :
    InstanceContentScript( 60003 )
  {
  }

  void onInit( InstanceContentPtr instance ) override
  {
    instance->registerEObj( "sgvf_w_lvd_b0959", 2002872, 6387948, 4, { -300.000000f, -0.116918f, -237.513199f },
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