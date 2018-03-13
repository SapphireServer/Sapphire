#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheKeeperoftheLake : public InstanceContentScript
{
public:
   TheKeeperoftheLake() : InstanceContentScript( 32 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "unknown_0", 2002735, 0, 4, { -40.786701f, 641.215271f, -59.415600f }, 1.000000f, -0.000000f ); 
      instance->registerEObj( "sgvf_w_lvd_b0118", 2002872, 5097808, 4, { -40.752449f, 641.160522f, -54.934898f }, 1.000000f, 0.000000f ); 
      // States -> vf_bextwall_on vf_bextwall_of 
      instance->registerEObj( "unknown_1", 2004825, 5040985, 4, { 194.842896f, -0.000001f, -91.318947f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "sgbg_l1d1_q1_arm04", 2004826, 5097903, 4, { 139.959106f, 4.489269f, -37.319328f }, 1.000000f, 0.000000f ); 
      // States -> arm04_def arm04_def_anim arm04_down arm04_down_anim 
      instance->registerEObj( "unknown_2", 2004828, 5041736, 4, { -97.215271f, 329.152313f, -129.564407f }, 0.991760f, 0.000048f ); 
      instance->registerEObj( "Magitekterminal", 2004829, 5073686, 4, { -104.691200f, 328.877686f, -135.171402f }, 0.991760f, 0.000048f ); 
      instance->registerEObj( "unknown_3", 2004830, 5054264, 4, { -85.465736f, 329.158203f, -114.917397f }, 0.991760f, 0.000048f ); 
      instance->registerEObj( "unknown_4", 2004831, 5054260, 4, { -74.450752f, 350.933899f, -163.969894f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_5", 2004832, 5054262, 4, { -68.565010f, 338.613892f, -210.672806f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_6", 2004833, 5041738, 4, { -36.703850f, 338.613892f, -209.867294f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "Magitekterminal_1", 2004834, 5073702, 4, { -33.987030f, 338.612915f, -200.545197f }, 0.991760f, 0.000048f ); 
      instance->registerEObj( "unknown_7", 2004835, 5041733, 4, { -102.992203f, 338.700012f, -173.230301f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_8", 2004836, 5041740, 4, { -91.617867f, 338.742096f, -191.340103f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_9", 2004837, 5041734, 4, { -56.932819f, 338.613800f, -220.085907f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_10", 2004838, 5041739, 4, { -58.661549f, 338.321289f, -231.786407f }, 0.991760f, 0.000048f ); 
      instance->registerEObj( "sgbg_l1d1_q1_arm02", 2004840, 5097049, 4, { 60.261662f, 608.420776f, -64.327179f }, 1.000000f, 0.000000f ); 
      // States -> arm02_def arm02_def_anim arm02_des arm02_des_anim 
      instance->registerEObj( "sgbg_l1d1_q1_arm03", 2004842, 5097050, 4, { -42.140709f, 637.801575f, -13.313470f }, 1.000000f, 0.000000f ); 
      // States -> arm03_def arm03_def_anim arm03_des arm03_des_anim 
      instance->registerEObj( "unknown_11", 2002735, 0, 4, { 36.823841f, 26.884010f, -25.290840f }, 1.000000f, 1.175128f ); 
      instance->registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 5072855, 4, { 40.635441f, 24.890421f, -26.286221f }, 1.000000f, 0.000000f ); 
      // States -> vf_bextwall_on vf_bextwall_of 
      instance->registerEObj( "sgvf_w_lvd_b0118_2", 2004827, 5072856, 4, { 5.803720f, 26.994020f, -14.402020f }, 1.000000f, 0.000000f ); 
      // States -> vf_bextwall_on vf_bextwall_of 
      instance->registerEObj( "unknown_12", 2002735, 0, 4, { 8.333900f, 345.993805f, -169.028107f }, 1.000000f, -0.000000f ); 
      instance->registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 5076365, 4, { 9.495131f, 345.449799f, -172.095505f }, 1.000000f, 0.000000f ); 
      // States -> vf_bextwall_on vf_bextwall_of 
      instance->registerEObj( "sgvf_w_lvd_b0118_4", 2004839, 5076366, 4, { 7.837297f, 345.993805f, -134.142197f }, 1.000000f, 0.000000f ); 
      // States -> vf_bextwall_on vf_bextwall_of 
      instance->registerEObj( "Entrance", 2000182, 5072285, 5, { 294.405701f, 3.332572f, -157.864304f }, 1.000000f, 0.079727f ); 
      // States -> vf_lock_on vf_lock_of 
      instance->registerEObj( "Exit", 2000139, 0, 4, { -48.338951f, 641.026917f, -87.713493f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 279.041687f, 2.095404f, -159.624695f }, 0.991760f, 0.000048f ); 

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};