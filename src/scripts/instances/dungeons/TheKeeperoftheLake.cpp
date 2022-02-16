#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheKeeperoftheLake : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheKeeperoftheLake() : Sapphire::ScriptAPI::InstanceContentScript( 32 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2002735, 0, 5097818, 4, { -40.786701f, 641.215271f, -59.415600f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5097808, 5097820, 4, { -40.752449f, 641.160522f, -54.934898f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2004825, 5040985, 5072812, 4, { 194.842896f, -0.000001f, -91.318947f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_l1d1_q1_arm04", 2004826, 5097903, 5097907, 4, { 139.959106f, 4.489269f, -37.319328f }, 1.000000f, 0.000000f, 0); 
    // States -> arm04_def (id: 2) arm04_def_anim (id: 3) arm04_down (id: 4) arm04_down_anim (id: 5) 
    instance.addEObj( "unknown_2", 2004828, 5041736, 5073685, 4, { -97.215271f, 329.152313f, -129.564407f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Magitekterminal", 2004829, 5073686, 5073687, 4, { -104.691200f, 328.877686f, -135.171402f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_3", 2004830, 5054264, 5073693, 4, { -85.465736f, 329.158203f, -114.917397f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_4", 2004831, 5054260, 5073694, 4, { -74.450752f, 350.933899f, -163.969894f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2004832, 5054262, 5073695, 4, { -68.565010f, 338.613892f, -210.672806f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2004833, 5041738, 5073697, 4, { -36.703850f, 338.613892f, -209.867294f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Magitekterminal_1", 2004834, 5073702, 5073698, 4, { -33.987030f, 338.612915f, -200.545197f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_7", 2004835, 5041733, 5073729, 4, { -102.992203f, 338.700012f, -173.230301f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2004836, 5041740, 5073730, 4, { -91.617867f, 338.742096f, -191.340103f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2004837, 5041734, 5073731, 4, { -56.932819f, 338.613800f, -220.085907f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2004838, 5041739, 5073732, 4, { -58.661549f, 338.321289f, -231.786407f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgbg_l1d1_q1_arm02", 2004840, 5097049, 5097053, 4, { 60.261662f, 608.420776f, -64.327179f }, 1.000000f, 0.000000f, 0); 
    // States -> arm02_def (id: 2) arm02_def_anim (id: 3) arm02_des (id: 4) arm02_des_anim (id: 5) 
    instance.addEObj( "sgbg_l1d1_q1_arm03", 2004842, 5097050, 5097054, 4, { -42.140709f, 637.801575f, -13.313470f }, 1.000000f, 0.000000f, 0); 
    // States -> arm03_def (id: 2) arm03_def_anim (id: 3) arm03_des (id: 4) arm03_des_anim (id: 5) 
    instance.addEObj( "unknown_11", 2002735, 0, 5072853, 4, { 36.823841f, 26.884010f, -25.290840f }, 1.000000f, 1.175128f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 5072855, 5072854, 4, { 40.635441f, 24.890421f, -26.286221f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2004827, 5072856, 5072857, 4, { 5.803720f, 26.994020f, -14.402020f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_12", 2002735, 0, 5076370, 4, { 8.333900f, 345.993805f, -169.028107f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 5076365, 5076371, 4, { 9.495131f, 345.449799f, -172.095505f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_4", 2004839, 5076366, 5076372, 4, { 7.837297f, 345.993805f, -134.142197f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Entrance", 2000182, 5072285, 5072294, 5, { 294.405701f, 3.332572f, -157.864304f }, 1.000000f, 0.079727f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 5072297, 4, { -48.338951f, 641.026917f, -87.713493f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Shortcut", 2000700, 0, 5072367, 4, { 279.041687f, 2.095404f, -159.624695f }, 0.991760f, 0.000048f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheKeeperoftheLake );