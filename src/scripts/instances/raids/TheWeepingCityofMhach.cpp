#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheWeepingCityofMhach :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWeepingCityofMhach() :
    Sapphire::ScriptAPI::InstanceContentScript( 30038 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 16.000000f, -0.599972f, -25.600000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_wide", 2002872, 6255278, 4, { 15.499620f, -0.600000f, -32.576271f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_lvd_b0118_wide_1", 2002872, 6255280, 4, { 16.000000f, -0.599986f, -84.500000f }, 1.200000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2007130, 6259583, 4, { 16.141850f, -0.600000f, -58.088329f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0919", 2007131, 6271618, 4, { 16.141850f, -0.600000f, -58.088329f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007127, 6263439, 4, { 2.786298f, 1.130917f, -81.495903f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007128, 6263438, 4, { 44.322010f, 1.937706f, -52.936489f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2007129, 6263356, 4, { -1.414551f, 2.361187f, -31.816429f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2002735, 0, 4, { -300.000000f, -73.990967f, -386.829315f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_wide_2", 2002872, 6256300, 4, { -298.284485f, -74.099991f, -394.606812f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_6", 2002872, 6252961, 4, { -298.284485f, -74.000061f, -446.164307f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007174, 0, 4, { -301.925903f, -74.099998f, -434.771606f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0917", 2007175, 6275855, 4, { -305.091309f, -74.099998f, -434.266205f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0909", 2007176, 6275857, 4, { -299.330200f, -74.099998f, -441.272186f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2000034, 6252960, 4, { -301.382507f, -74.111649f, -397.150391f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2000035, 0, 4, { -300.012909f, -74.111687f, -411.038788f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2002735, 0, 4, { 280.000000f, -468.750000f, -352.734314f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_wide_3", 2002872, 6256312, 4, { 279.076385f, -468.799988f, -346.734894f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_11", 2007092, 6246904, 4, { 271.681488f, -269.434998f, 263.484192f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007093, 6246906, 4, { 299.983093f, -269.438812f, 263.439911f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007094, 6246909, 4, { 328.133606f, -269.459900f, 263.349915f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007095, 6246905, 4, { 272.007812f, -270.624695f, 249.703201f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007096, 6246907, 4, { 299.972198f, -270.615295f, 249.808594f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2007097, 6246910, 4, { 327.886597f, -270.637299f, 249.556503f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0908", 2007098, 6276590, 4, { 271.976288f, -270.275513f, 254.027298f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0908_1", 2007099, 6276603, 4, { 300.073914f, -270.279907f, 253.881897f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0908_2", 2007100, 6276618, 4, { 328.117798f, -270.282501f, 253.919098f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0906", 2007101, 6277276, 4, { 300.580688f, -329.902802f, 215.101807f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2007102, 0, 4, { 313.999695f, -254.436203f, 249.057007f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2007091, 6253623, 4, { 280.196686f, -468.799988f, -340.444214f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0186", 2000015, 6323645, 4, { 280.035004f, -444.700012f, -381.003815f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0186_1", 2000015, 6323651, 4, { 255.731705f, -444.700012f, -423.649811f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0186_2", 2000015, 6323650, 4, { 304.734985f, -444.700012f, -424.385590f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0954", 2007350, 6405524, 4, { 280.000000f, -446.006287f, -410.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_cylinder_col_on_off", 2002618, 6405504, 4, { 271.693695f, -445.000000f, -398.334412f }, 1.000000f, 0.000000f ); 
    // States -> col_on (id: 17) col_off (id: 18) 
    instance.registerEObj( "sgbg_z2r2_a4_navi1", 2002618, 6413337, 4, { 284.413513f, -444.945587f, -428.864410f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2002735, 0, 4, { -300.007690f, -436.179108f, -3.677429f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_wide_4", 2002872, 6256352, 4, { -299.044006f, -436.200012f, 1.934000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -300.007690f, -436.057098f, -56.789539f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_20", 2000019, 6223041, 4, { -293.815094f, -436.100006f, -36.657909f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0955", 2007363, 6403167, 4, { -300.000000f, -436.100006f, -34.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2007381, 0, 4, { -288.659698f, -436.100006f, -36.228500f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2007104, 6253621, 4, { -293.853302f, -417.190002f, 338.020691f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2007105, 6262270, 4, { 279.377411f, -481.421112f, -273.999298f }, 1.000000f, 0.000048f ); 
    instance.registerEObj( "unknown_24", 2007106, 6253622, 4, { 282.739197f, -506.212494f, -377.761414f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2007630, 0, 4, { -307.311310f, -74.111656f, -404.095490f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0606", 2007457, 6873350, 4, { -287.981812f, -74.111671f, -418.439789f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "b0893_onen_y_qic_s", 2007457, 7008372, 4, { -286.682404f, -74.111656f, -414.302185f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2000034, 6252960, 4, { -299.669098f, -74.111687f, -422.791412f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a", 2008306, 6873007, 4, { -299.592712f, -123.000000f, -313.306885f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_27", 2002735, 0, 4, { -300.000000f, -73.990967f, -386.829315f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a_1", 2002872, 6873032, 4, { -298.298706f, -74.113159f, -394.613586f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_28", 2007112, 6252937, 4, { -258.522614f, -114.655602f, -231.454193f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_29", 2007112, 6403165, 4, { -360.672485f, -116.000198f, -271.268707f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_a_evt_flyingship02", 2008452, 6889796, 4, { -239.520905f, -116.014397f, -230.853806f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a_2", 2007457, 6941894, 4, { -299.583099f, -75.000023f, -353.118500f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2007108, 6252917, 4, { 52.989189f, 8.000000f, 109.725502f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_31", 2007109, 6252933, 4, { 40.849979f, 7.999999f, 54.685509f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r2_b0893", 2007110, 6258888, 4, { -217.946503f, -116.000000f, -210.519608f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_z2r2_b0893_1", 2007111, 6258889, 4, { -351.721313f, -116.000000f, -260.105499f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_32", 2007112, 6252937, 4, { -249.593796f, -116.000000f, -229.014603f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_33", 2007112, 6403165, 4, { -354.681885f, -116.000298f, -278.960693f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_34", 2002735, 0, 4, { -185.956604f, -394.699890f, 235.090607f }, 1.000000f, 1.047197f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char", 2002872, 6259368, 4, { -189.835297f, -394.768494f, 236.985107f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_1", 2002872, 6259369, 4, { -152.910706f, -394.522003f, 215.716797f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_35", 2007114, 6265979, 4, { -179.125702f, -394.522003f, 205.950897f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_36", 2007115, 6265980, 4, { -157.763107f, -394.522003f, 242.664200f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_37", 2007116, 6265977, 4, { -181.536697f, -394.522003f, 201.556396f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_38", 2007117, 6275728, 4, { -180.590607f, -394.522003f, 231.158905f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_39", 2007118, 6262272, 4, { -156.623795f, -394.500092f, 244.445908f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_40", 2007119, 6264911, 4, { -168.688507f, -391.866913f, 224.567001f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_41", 2007378, 6404242, 4, { -170.886597f, -394.500092f, 228.890305f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_42", 2007379, 6404243, 4, { -174.892807f, -394.500092f, 226.853806f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Basicconveyanceunit", 2007054, 6277013, 4, { 29.465090f, 12.072440f, 173.291306f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Basicconveyanceunit_1", 2007055, 6277014, 4, { 10.055660f, 10.610950f, 59.293789f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Basicconveyanceunit_2", 2007056, 6277015, 4, { 21.985451f, -1.159537f, -124.736298f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Basicconveyanceunit_3", 2007057, 6277012, 4, { -290.684998f, -71.292747f, -368.263885f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Basicconveyanceunit_4", 2007058, 6235460, 4, { -244.833099f, -390.428986f, 258.731689f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Basicconveyanceunit_5", 2007059, 6235461, 4, { 276.184296f, -461.318604f, -294.996796f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Basicconveyanceunit_6", 2007060, 6235463, 4, { -304.521301f, -435.890594f, 23.143780f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_43", 2007103, 6259793, 4, { 16.303080f, -3.864367f, -114.426003f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6247654, 5, { 81.884888f, 13.000000f, 208.698303f }, 0.991760f, 0.292740f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheWeepingCityofMhach );