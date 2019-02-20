#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class KuganeCastle :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  KuganeCastle() :
    Sapphire::ScriptAPI::InstanceContentScript( 57 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6891156, 4, { 280.110413f, -75.860001f, 341.057800f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 280.000000f, -75.860001f, 338.900696f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 280.000000f, -75.860001f, 375.299988f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 0, 4, { 280.179993f, -75.859993f, 363.578888f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Pileofgold", 2007814, 0, 4, { 289.943695f, -75.859993f, 360.566986f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007815, 0, 4, { 279.957306f, -75.883118f, 375.295685f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -110.000000f, 0.000003f, 0.000000f }, 1.000000f, -1.570796f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6886643, 4, { -108.904198f, 0.000003f, -0.184188f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6886655, 4, { -147.474503f, 0.100000f, -0.110550f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { 280.000000f, -90.771896f, 28.200001f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 6795321, 4, { 294.636414f, -90.775902f, 64.530403f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_6", 2007457, 6795322, 4, { 284.810699f, -90.771896f, 64.853622f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 6795323, 4, { 275.195496f, -90.771896f, 64.375351f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 6795324, 4, { 264.569000f, -90.771896f, 65.125214f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 6795325, 4, { 295.691193f, -90.771896f, 55.563641f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 6795326, 4, { 284.563385f, -90.771896f, 57.046230f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 6795327, 4, { 274.879486f, -90.771896f, 57.698601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 6795328, 4, { 264.951508f, -90.771896f, 57.270260f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 6795329, 4, { 294.813904f, -90.771896f, 45.369381f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007457, 6795330, 4, { 284.412811f, -90.775940f, 44.846191f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_15", 2007457, 6795331, 4, { 274.009003f, -90.771896f, 44.232479f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2007457, 6795332, 4, { 264.546387f, -90.771896f, 44.505569f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2007457, 6795333, 4, { 294.721802f, -90.771896f, 35.522999f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2007457, 6795334, 4, { 284.550293f, -90.771896f, 35.573021f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2007457, 6795335, 4, { 274.647095f, -90.775940f, 36.026489f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_20", 2007457, 6795336, 4, { 265.028992f, -90.771896f, 35.466030f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6972248, 4, { 279.929291f, -90.862122f, 25.802130f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 6972249, 4, { 279.425995f, -90.862122f, 73.752983f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_21", 2007457, 6795811, 4, { -18.923059f, -4.000000f, -47.771740f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2007457, 6795812, 4, { -82.884247f, 0.000003f, -0.161598f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2007457, 6795813, 4, { -179.231201f, 4.000000f, -0.161991f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2007812, 0, 4, { -60.365211f, -6.291489f, 11.147480f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_25", 2007812, 0, 4, { -60.697491f, -6.291489f, -12.243330f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_26", 2007812, 0, 4, { -64.355148f, -6.291490f, 11.308300f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_27", 2007812, 0, 4, { -64.521027f, -6.291490f, -11.570270f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_28", 2007812, 0, 4, { -55.949509f, -6.291489f, 9.962895f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_29", 2007812, 0, 4, { -56.575081f, -6.291490f, -10.074280f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgbg_e3d4_a1_leav1", 2007457, 6993778, 4, { -11.244300f, -5.961200f, -57.744499f }, 1.000000f, -0.872665f ); 
    instance.registerEObj( "sgbg_e3d4_a1_leav1_1", 2007457, 6994112, 4, { -17.911301f, -5.796600f, -65.317596f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_30", 2007812, 0, 4, { -49.310871f, -6.291489f, 10.600000f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_31", 2007812, 0, 4, { -49.310860f, -6.291490f, -10.674300f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_32", 2007457, 6795420, 4, { 248.664993f, -94.824402f, -117.732498f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_33", 2007457, 6795421, 4, { 279.489410f, -92.996399f, 3.845758f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_34", 2007457, 6795419, 4, { 280.175507f, -92.998596f, 93.664139f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_35", 2007813, 0, 4, { 248.706802f, -94.834801f, -131.982498f }, 1.000000f, -3.141593f ); 
    instance.registerEObj( "unknown_36", 2007813, 0, 4, { 286.988312f, -92.855598f, -10.582000f }, 1.000000f, 0.785398f ); 
    instance.registerEObj( "unknown_37", 2007813, 0, 4, { 273.011108f, -92.855598f, -10.581000f }, 1.000000f, -0.785398f ); 
    instance.registerEObj( "unknown_38", 2007813, 0, 4, { 279.995697f, -92.851196f, -21.638639f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_39", 2007813, 0, 4, { 279.987701f, -92.881706f, -7.278625f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_40", 2007457, 6795337, 4, { 279.713104f, -83.786652f, 143.480499f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_41", 2007457, 6795422, 4, { 280.061096f, -73.914101f, 313.413391f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_42", 2007457, 6795342, 4, { 289.140198f, -73.914101f, 284.393890f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_43", 2007457, 6795343, 4, { 288.888214f, -73.914200f, 303.585907f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_44", 2007457, 6795341, 4, { 271.105591f, -73.914101f, 284.355804f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_45", 2007457, 6795345, 4, { 271.048309f, -73.914200f, 302.845795f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_46", 2007457, 6795344, 4, { 289.058899f, -73.914101f, 291.958588f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_47", 2007457, 6795346, 4, { 288.715912f, -73.914299f, 310.894012f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_48", 2007457, 6795338, 4, { 271.824585f, -73.914101f, 292.335999f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_49", 2007457, 6795339, 4, { 271.103790f, -73.914299f, 311.710388f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6881046, 5, { 66.323036f, -6.000000f, -68.720047f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 49.699169f, -6.000000f, -60.817249f }, 1.000000f, 1.570796f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( KuganeCastle );