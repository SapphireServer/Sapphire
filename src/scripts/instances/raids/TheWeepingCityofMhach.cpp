#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheWeepingCityofMhach : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWeepingCityofMhach() : Sapphire::ScriptAPI::InstanceContentScript( 30038 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 6247654, 6247656, 5, { 81.884888f, 13.000000f, 208.698303f }, 0.991760f, 0.292740f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 83.599518, 14.983521, 214.396484 }, 2.848853, 2.477390, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 80.166023, 14.983521, 203.001404 }, 2.848853, 2.479804, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 76.188736, 14.983521, 210.419662 }, 1.278402, 2.480036, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 87.582710, 14.983521, 206.982498 }, 1.278402, 2.484129, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 87.073730, 14.983521, 211.487015 }, 2.063455, 2.628866, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 76.696045, 14.983520, 205.909592 }, 2.063455, 2.623060, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 79.098740, 14.983521, 213.888519 }, -2.648934, 2.625963, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 84.671036, 14.983521, 203.508087 }, -2.648934, 2.625963, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "Basicconveyanceunit", 2007054, 6277013, 6248112, 4, { 29.465090f, 12.072440f, 173.291306f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_1", 2007055, 6277014, 6248117, 4, { 10.055660f, 10.610950f, 59.293789f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_2", 2007056, 6277015, 6248159, 4, { 21.985451f, -1.159537f, -124.736298f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_3", 2007057, 6277012, 6248225, 4, { -290.684998f, -71.292747f, -368.263885f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_4", 2007058, 6235460, 6248390, 4, { -244.833099f, -390.428986f, 258.731689f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_5", 2007059, 6235461, 6248463, 4, { 276.184296f, -461.318604f, -294.996796f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_6", 2007060, 6235463, 6248491, 4, { -304.521301f, -435.890594f, 23.143780f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 6255272, 4, { 16.000000f, -0.599972f, -25.600000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_wide", 2002872, 6255278, 6255273, 4, { 15.499620f, -0.600000f, -32.576271f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 15.499620, 1.900000, -32.576271 }, -0.000000, 16.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_wide_1", 2002872, 6255280, 6255282, 4, { 16.000000f, -0.599986f, -84.500000f }, 1.200000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 16.000000, 1.900014, -84.500000 }, -0.000000, 19.200001, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_5", 2002735, 0, 6256298, 4, { -300.000000f, -73.990967f, -386.829315f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_wide_2", 2002872, 6256300, 6256299, 4, { -298.284485f, -74.099991f, -394.606812f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -298.284485, -71.599991, -394.606812 }, -0.000000, 16.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_6", 2002872, 6252961, 6256302, 4, { -298.284485f, -74.000061f, -446.164307f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -298.284485, -74.000061, -415.164307 }, -0.000000, 10.000000, 15.000000, 0.500000 );

    pEObj = instance.addEObj( "unknown_10", 2002735, 0, 6256310, 4, { 280.000000f, -468.750000f, -352.734314f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_wide_3", 2002872, 6256312, 6256311, 4, { 279.076385f, -468.799988f, -346.734894f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 279.076385, -466.299988, -346.734894 }, -0.000000, 16.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_19", 2002735, 0, 6256350, 4, { -300.007690f, -436.179108f, -3.677429f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_wide_4", 2002872, 6256352, 6256351, 4, { -299.044006f, -436.200012f, 1.934000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -299.044006, -433.700012, 1.934000 }, -0.000000, 16.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6256358, 4, { -300.007690f, -436.057098f, -56.789539f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2007092, 6246904, 6258771, 4, { 271.681488f, -269.434998f, 263.484192f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2007093, 6246906, 6258772, 4, { 299.983093f, -269.438812f, 263.439911f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_13", 2007094, 6246909, 6258773, 4, { 328.133606f, -269.459900f, 263.349915f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2007095, 6246905, 6258774, 4, { 272.007812f, -270.624695f, 249.703201f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_15", 2007096, 6246907, 6258775, 4, { 299.972198f, -270.615295f, 249.808594f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2007097, 6246910, 6258776, 4, { 327.886597f, -270.637299f, 249.556503f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_z2r2_b0908", 2007098, 6276590, 6258777, 4, { 271.976288f, -270.275513f, 254.027298f }, 1.000000f, 0.000000f, 0 ); 
    // States -> grv_hide (id: 3) grv_show (id: 4) grv_show_anim (id: 5) grv_react (id: 6) 

    pEObj = instance.addEObj( "sgvf_z2r2_b0908_1", 2007099, 6276603, 6258778, 4, { 300.073914f, -270.279907f, 253.881897f }, 1.000000f, 0.000000f, 0 ); 
    // States -> grv_hide (id: 3) grv_show (id: 4) grv_show_anim (id: 5) grv_react (id: 6) 

    pEObj = instance.addEObj( "sgvf_z2r2_b0908_2", 2007100, 6276618, 6258779, 4, { 328.117798f, -270.282501f, 253.919098f }, 1.000000f, 0.000000f, 0 ); 
    // States -> grv_hide (id: 3) grv_show (id: 4) grv_show_anim (id: 5) grv_react (id: 6) 

    pEObj = instance.addEObj( "sgvf_z2r2_b0906", 2007101, 6277276, 6258780, 4, { 300.580688f, -329.902802f, 215.101807f }, 1.000000f, 0.000000f, 0 ); 
    // States -> swt3a_off (id: 1) swt3a_pre (id: 2) swt3a_pre_anim (id: 3) wormhole_hide (id: 5) 

    pEObj = instance.addEObj( "unknown_17", 2007102, 0, 6258781, 4, { 313.999695f, -254.436203f, 249.057007f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_25", 2007108, 6252917, 6258883, 4, { 52.989189f, 8.000000f, 109.725502f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 52.989189, 8.700001, 111.125504 }, -0.000000, 10.000000, 4.000000, 0.500000 );

    pEObj = instance.addEObj( "unknown_26", 2007109, 6252933, 6258884, 4, { 40.849979f, 7.999999f, 54.685509f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 40.849979, 9.899999, 55.185509 }, -0.000000, 14.000000, 3.000000, 0.500000 );

    pEObj = instance.addEObj( "sgvf_z2r2_b0893", 2007110, 6258888, 6258885, 4, { -217.946503f, -116.000000f, -210.519608f }, 0.991760f, 0.000048f, 0 ); 
    // States -> grudge_hide (id: 2) grudge_show (id: 3) grudge_show_ani (id: 4) grudge_hide_ani (id: 6) 

    pEObj = instance.addEObj( "sgvf_z2r2_b0893_1", 2007111, 6258889, 6258886, 4, { -351.721313f, -116.000000f, -260.105499f }, 1.000000f, 0.000000f, 0 ); 
    // States -> grudge_hide (id: 2) grudge_show (id: 3) grudge_show_ani (id: 4) grudge_hide_ani (id: 6) 

    pEObj = instance.addEObj( "unknown_27", 2007112, 6252937, 6258887, 4, { -249.593796f, -116.000000f, -229.014603f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -249.593796, -109.411194, -218.407501 }, -0.000000, 11.000000, 5.000000, 0.500000 );

    pEObj = instance.addEObj( "unknown_29", 2002735, 0, 6259367, 4, { -185.956604f, -394.699890f, 235.090607f }, 1.000000f, 1.047197f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char", 2002872, 6259368, 6259424, 4, { -189.835297f, -394.768494f, 236.985107f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -189.835297, -388.925049, 236.985107 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_1", 2002872, 6259369, 6259425, 4, { -152.910706f, -394.522003f, 215.716797f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -152.910431, -388.726715, 215.716522 }, 0.000048, 7.438202, 7.282938, 0.743820 );

    pEObj = instance.addEObj( "unknown_30", 2007114, 6265979, 6259484, 4, { -179.125702f, -394.522003f, 205.950897f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -178.947189, -394.488800, 205.950897 }, 1.570499, 17.851686, 3.669513, 0.495880 );

    pEObj = instance.addEObj( "unknown_31", 2007115, 6265980, 6259485, 4, { -157.763107f, -394.522003f, 242.664200f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -157.584595, -394.488800, 242.664200 }, 1.570499, 17.851686, 3.669513, 0.495880 );

    pEObj = instance.addEObj( "unknown_32", 2007116, 6265977, 6259487, 4, { -181.536697f, -394.522003f, 201.556396f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_33", 2007117, 6275728, 6259576, 4, { -180.590607f, -394.522003f, 231.158905f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_34", 2007118, 6262272, 6259577, 4, { -156.623795f, -394.500092f, 244.445908f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_35", 2007119, 6264911, 6259578, 4, { -168.688507f, -391.866913f, 224.567001f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2007127, 6263439, 6261089, 4, { 2.786298f, 1.130917f, -81.495903f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2007128, 6263438, 6261090, 4, { 44.322010f, 1.937706f, -52.936489f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2007129, 6263356, 6261091, 4, { -1.414551f, 2.361187f, -31.816429f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2007130, 6259583, 6261095, 4, { 16.141850f, -0.600000f, -58.088329f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_z2r2_b0919", 2007131, 6271618, 6261096, 4, { 16.141850f, -0.600000f, -58.088329f }, 1.000000f, 0.000000f, 0 ); 
    // States -> sand_hide (id: 2) sand_show (id: 3) sand_show_anim (id: 4) sand_hide_anim (id: 5) 

    pEObj = instance.addEObj( "unknown_7", 2007174, 0, 6275859, 4, { -301.925903f, -74.099998f, -434.771606f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_z2r2_b0917", 2007175, 6275855, 6275860, 4, { -305.091309f, -74.099998f, -434.266205f }, 1.000000f, 0.000000f, 0 ); 
    // States -> omen_off (id: 2) omen_on_anim (id: 3) 

    pEObj = instance.addEObj( "sgvf_z2r2_b0909", 2007176, 6275857, 6275862, 4, { -299.330200f, -74.099998f, -441.272186f }, 1.000000f, 0.000000f, 0 ); 
    // States -> db_hide (id: 2) db1_show (id: 3) db1_show_anim (id: 4) db1_firing (id: 5) db2_show (id: 6) db2_1to2_anim (id: 7) db3_show (id: 8) db3_2to3_anim (id: 9) db3_firing (id: 10) db4_show (id: 11) db4_3to4_anim (id: 12) db4_firing (id: 13) db2_firing (id: 14) 

    pEObj = instance.addEObj( "unknown_18", 2007091, 6253623, 6276414, 4, { 280.196686f, -468.799988f, -340.444214f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 280.196686, -468.799988, -340.444214 }, -0.000000, 50.000000, 0.200000, 50.000000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0186", 2000015, 6323645, 6323659, 4, { 280.035004f, -444.700012f, -381.003815f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0186_1", 2000015, 6323651, 6323660, 4, { 255.731705f, -444.700012f, -423.649811f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0186_2", 2000015, 6323650, 6323661, 4, { 304.734985f, -444.700012f, -424.385590f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_38", 2007103, 6259793, 6331874, 4, { 16.303080f, -3.864367f, -114.426003f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2000034, 6252960, 6362735, 4, { -301.382507f, -74.111649f, -397.150391f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2000035, 0, 6362736, 4, { -300.012909f, -74.111687f, -411.038788f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_22", 2007104, 6253621, 6383105, 4, { -293.853302f, -417.190002f, 338.020691f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_23", 2007105, 6262270, 6383107, 4, { 279.377411f, -481.421112f, -273.999298f }, 1.000000f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_24", 2007106, 6253622, 6383108, 4, { 282.739197f, -506.212494f, -377.761414f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_20", 2000019, 6223041, 6384626, 4, { -293.815094f, -436.100006f, -36.657909f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_z2r2_b0954", 2007350, 6405524, 6395678, 4, { 280.000000f, -446.006287f, -410.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> on (id: 2) off (id: 3) 

    pEObj = instance.addEObj( "sgvf_z2r2_b0955", 2007363, 6403167, 6403168, 4, { -300.000000f, -436.100006f, -34.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> barri_hide (id: 2) barri_show_anim (id: 3) barri_hide_anim (id: 4) 

    pEObj = instance.addEObj( "unknown_28", 2007112, 6403165, 6403169, 4, { -354.681885f, -116.000298f, -278.960693f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -354.681885, -108.000298, -278.960693 }, -0.000000, 8.000000, 8.000000, 0.500000 );

    pEObj = instance.addEObj( "unknown_36", 2007378, 6404242, 6403965, 4, { -170.886597f, -394.500092f, 228.890305f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_37", 2007379, 6404243, 6403966, 4, { -174.892807f, -394.500092f, 226.853806f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_cylinder_col_on_off", 2002618, 6405504, 6405505, 4, { 271.693695f, -445.000000f, -398.334412f }, 1.000000f, 0.000000f, 0 ); 
    // States -> col_on (id: 17) col_off (id: 18) 

    pEObj = instance.addEObj( "unknown_21", 2007381, 0, 6405546, 4, { -288.659698f, -436.100006f, -36.228500f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_z2r2_a4_navi1", 2002618, 6413337, 6413338, 4, { 284.413513f, -444.945587f, -428.864410f }, 1.000000f, 0.000000f, 0 ); 


  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, Entity::EventObject& eobj, uint32_t eventId ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint64_t actorId ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

  void onLeaveTerritory( InstanceContent& instance, Entity::Player& player ) override
  {

  }

};

EXPOSE_SCRIPT( TheWeepingCityofMhach );