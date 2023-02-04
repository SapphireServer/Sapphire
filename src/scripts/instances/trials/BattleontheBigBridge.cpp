#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class BattleontheBigBridge : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  BattleontheBigBridge() : Sapphire::ScriptAPI::InstanceContentScript( 20021 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2002735, 0, 4630946, 4, { 106.355499f, -5.000003f, -0.049812f }, 0.404395f, -1.570451f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 4630952, 4630953, 4, { 109.916496f, -5.000003f, -0.035030f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2002735, 0, 4635073, 4, { -75.653900f, 1.999997f, 0.149403f }, 0.500000f, -1.570451f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 4635071, 4635075, 4, { -72.579193f, 1.999997f, 0.830825f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2003902, 4635078, 4635080, 4, { -37.106110f, 2.000000f, 1.552188f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Entrance", 2000182, 4630929, 4630930, 5, { -141.564804f, 1.314597f, 3.459962f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 4630942, 4, { 143.814301f, -5.000000f, -0.081344f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Shortcut", 2000700, 0, 4682785, 4, { -136.750107f, 1.329580f, 5.374416f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( BattleontheBigBridge );