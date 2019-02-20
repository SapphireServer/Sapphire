#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class EmissaryoftheDawn :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  EmissaryoftheDawn() :
    Sapphire::ScriptAPI::InstanceContentScript( 5025 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgbg_e3e9_a1_grk01", 2007457, 7463402, 4, { -7.066119f, -0.015320f, 4.851629f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "WoundedPopularis", 2009561, 7508935, 4, { -6.516740f, -0.015320f, 6.499700f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b1199", 2007457, 7420739, 4, { -0.523771f, 0.000000f, 2.522100f }, 1.000000f, 0.000000f ); 
    // States -> circle_off (id: 3) circle_off (id: 4) circle_on (id: 5) circle_on (id: 6) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( EmissaryoftheDawn );