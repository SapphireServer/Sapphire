#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheTowerofBabil : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheTowerofBabil() : Sapphire::ScriptAPI::InstanceContentScript( 80 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8860871, 4, { -300.000000f, -175.000000f, 91.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -300.000000f, -175.000000f, 91.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8860878, 4, { -300.000000f, -175.000000f, 51.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 8866812, 4, { 221.000000f, 1.112100f, 326.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 221.000000f, 1.112100f, 326.750000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8866817, 4, { 221.000000f, 1.109500f, 285.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 8861135, 4, { 0.000000f, 479.770386f, -159.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 0.000000f, 479.770386f, -159.250000f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_3", 2007457, 8685736, 4, { -257.700012f, -199.000000f, 237.600006f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8658615, 4, { -300.000000f, -175.000000f, 97.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8966359, 4, { -269.110992f, -180.399994f, 282.747009f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "Controlterminal", 2011745, 0, 4, { 400.000000f, 0.100000f, -177.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8663022, 4, { 400.000000f, 0.000000f, -164.250000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8662368, 4, { 221.000198f, 0.000000f, 362.299988f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8662714, 4, { -11.817600f, 487.000305f, -86.297203f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "Controlterminal_1", 2011746, 0, 4, { 0.000000f, 499.999908f, 0.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 8665013, 4, { 0.000000f, 500.000000f, -6.700000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 8663636, 4, { 0.150000f, 481.700012f, -126.900002f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 8864034, 5, { -265.000000f, -199.500000f, 379.000000f }, 1.000000f, -0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -264.476410f, -199.500000f, 374.139587f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.000000f, 480.000092f, -192.500000f }, 0.991760f, -1.570451f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2002872, 9067181, 4, { -0.000000f, 479.770386f, -159.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_6", 2002872, 9067131, 4, { 221.000000f, 1.112100f, 326.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_11", 2002735, 0, 4, { 221.000000f, 1.112100f, 326.750000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_7", 2002872, 9067135, 4, { 221.000000f, 1.109500f, 285.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_12", 2007457, 8662368, 4, { 221.000198f, 0.000000f, 362.299988f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2002735, 0, 4, { -300.000000f, -175.000000f, 91.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_8", 2002872, 9602521, 4, { -300.000000f, -175.000000f, 91.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheTowerofBabil );