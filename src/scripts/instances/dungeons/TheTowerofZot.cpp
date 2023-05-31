#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheTowerofZot : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheTowerofZot() : Sapphire::ScriptAPI::InstanceContentScript( 78 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8803729, 4, { 68.000000f, -442.941803f, -100.695396f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 68.000000f, -442.920013f, -104.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8803736, 4, { 68.046310f, -442.991791f, -149.389008f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8803808, 4, { -258.000000f, -169.000000f, -11.000000f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 8803795, 4, { -257.500000f, -168.684601f, -50.500000f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -258.000000f, -168.887299f, -6.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 8803822, 4, { -44.000000f, 546.279785f, -32.000000f }, 1.000000f, 0.785398f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -41.642101f, 546.279785f, -35.357899f }, 0.991760f, 0.785398f); 
    instance.registerEObj( "unknown_3", 2007457, 8537269, 4, { -0.015320f, -465.812195f, 44.968262f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8537270, 4, { 67.978882f, -444.022308f, -47.013062f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8537313, 4, { -87.242241f, 541.691284f, -33.504650f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8903669, 4, { 45.000000f, 537.195679f, -77.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8860014, 5, { -0.015320f, -466.575104f, 255.000000f }, 0.991760f, 0.000048f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -5.000000f, -466.481812f, 245.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -19.191271f, 546.103210f, -57.775421f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheTowerofZot );