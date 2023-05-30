#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class MtGulg : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  MtGulg() : Sapphire::ScriptAPI::InstanceContentScript( 70 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7917841, 4, { 208.000000f, -48.000000f, -170.000000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 208.000000f, -48.000000f, -170.000000f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 7917848, 4, { 168.000000f, -48.000000f, -170.000000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7917881, 4, { -240.000000f, 210.000000f, -65.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -240.000000f, 210.000000f, -65.750000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 7917884, 4, { -240.009094f, 209.979294f, -12.001830f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2007457, 7833067, 4, { -240.000000f, 210.000000f, -33.000019f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 7917891, 4, { -240.000000f, 210.000000f, 216.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -240.000000f, 210.000000f, 216.250000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 7890143, 4, { -240.000000f, 210.000000f, 237.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 7921671, 4, { -240.000000f, 210.000000f, 237.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 7733697, 4, { 335.000000f, -72.000000f, -56.000000f }, 1.000000f, -0.261799f); 
    instance.registerEObj( "unknown_7", 2007457, 7733698, 4, { 288.000000f, -49.999981f, -170.000000f }, 1.000000f, 0.977384f); 
    instance.registerEObj( "unknown_8", 2007457, 7733410, 4, { -10.999970f, -31.000000f, -193.000000f }, 1.000000f, -1.221730f); 
    instance.registerEObj( "unknown_9", 2007457, 7733411, 4, { -204.000000f, 202.000000f, -103.999901f }, 1.000000f, -0.785398f); 
    instance.registerEObj( "unknown_10", 2007457, 7725168, 4, { -240.009201f, 201.983597f, 154.985794f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Entrance", 2000182, 7926247, 5, { 289.417694f, -79.087517f, 124.376198f }, 0.991760f, 0.000048f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -239.959900f, 210.000000f, 251.804092f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 283.185486f, -78.439682f, 117.079803f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MtGulg );