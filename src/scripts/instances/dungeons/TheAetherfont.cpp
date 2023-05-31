#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheAetherfont : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheAetherfont() : Sapphire::ScriptAPI::InstanceContentScript( 90 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 9802909, 5, { -395.110504f, 0.045100f, 464.779785f }, 1.000000f, -0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -394.997711f, 0.240975f, 453.906006f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -370.296997f, -873.000000f, -348.337891f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -322.000000f, 0.079213f, 140.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 9748501, 4, { -322.000000f, 0.079213f, 140.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 9748510, 4, { -322.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 9747201, 4, { 425.000000f, 20.000000f, -425.200012f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 425.000000f, 20.000000f, -425.200012f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 9748597, 4, { 425.000000f, 20.000000f, -455.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -395.414703f, -815.253906f, -184.993896f }, 1.000000f, -0.019626f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 9749293, 4, { -395.414795f, -815.253906f, -184.993896f }, 1.000000f, -0.019626f); 
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

EXPOSE_SCRIPT( TheAetherfont );