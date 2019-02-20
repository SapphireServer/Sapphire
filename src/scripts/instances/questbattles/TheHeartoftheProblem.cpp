#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheHeartoftheProblem :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheHeartoftheProblem() :
    Sapphire::ScriptAPI::InstanceContentScript( 5015 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2008290, 6894789, 4, { 375.272888f, -4.893838f, 290.605011f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Yol", 2008330, 0, 4, { 466.995514f, 21.157949f, -328.188995f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Ovoo", 2008289, 6872570, 4, { 354.000000f, -0.790344f, 296.500000f }, 0.991760f, 0.000048f ); 
    // States -> land_def (id: 3) land_def_anim (id: 4) land_on (id: 5) land_on_anim (id: 6) land_on_omen (id: 7) land_on_omen (id: 8) land_off (id: 19) land_off_anim (id: 20) 
    instance.registerEObj( "unknown_1", 2004967, 0, 4, { -187.899506f, 1.653982f, 760.298279f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_e3f3_q1_gmc02", 2007457, 7653044, 4, { -223.010605f, 3.178310f, 519.218811f }, 0.991760f, 0.000048f ); 
    // States -> smto_on (id: 19) smto_c_on (id: 3) smto_off (id: 1) smto_off_anim (id: 2) smto_c_off (id: 4) smto_fdout (id: 18) 
    instance.registerEObj( "sgvf_w_lvd_b1472", 2007457, 7653055, 4, { -186.572403f, 4.189117f, 532.602173f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1472_1", 2007457, 7653056, 4, { -186.602600f, 6.933841f, 568.871582f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b1199", 2007457, 7669017, 4, { -186.572403f, 5.921182f, 550.737427f }, 1.000000f, 0.000000f ); 
    // States -> circle_off (id: 3) circle_off (id: 4) circle_on (id: 5) circle_on (id: 6) 
    instance.registerEObj( "sgvf_w_lvd_b1199_1", 2007457, 7632420, 4, { -223.165497f, 2.660000f, 519.000000f }, 1.000000f, 0.000000f ); 
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

EXPOSE_SCRIPT( TheHeartoftheProblem );