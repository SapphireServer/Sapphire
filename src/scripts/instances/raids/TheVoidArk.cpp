#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheVoidArk :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheVoidArk() :
    Sapphire::ScriptAPI::InstanceContentScript( 30029 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -288.000000f, 196.497299f, 30.140800f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char", 2002872, 5965588, 4, { -288.643890f, 196.450897f, 30.140779f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_1", 2002872, 5965606, 4, { -315.195099f, 196.497299f, 1.375446f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2006489, 5961744, 4, { -289.112610f, 196.497299f, -1.589648f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 0.220062f, -191.999893f, 170.174606f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_2", 2002872, 5965590, 4, { 0.354952f, -191.297607f, 150.971207f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6047090, 4, { -0.028858f, -192.000000f, 97.337067f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2006559, 5996197, 4, { -0.306469f, -192.000000f, 68.934158f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2006595, 6067109, 4, { 0.064018f, -192.000107f, 129.936996f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2002735, 0, 4, { 288.000000f, -400.000000f, 205.443207f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_3", 2002872, 5965591, 4, { 287.996399f, -400.000000f, 205.904694f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_z2r1_b0762", 2006503, 6046596, 4, { 288.000000f, -415.885803f, 122.751602f }, 1.000000f, 0.000000f ); 
    // States -> tower_hide (id: 2) tower_show_anim (id: 4) tower_hide_anim (id: 5) 
    instance.registerEObj( "sgvf_z2r1_b0762_1", 2006504, 6046597, 4, { 304.000000f, -415.885803f, 138.751602f }, 1.000000f, 0.000000f ); 
    // States -> tower_hide (id: 2) tower_show_anim (id: 4) tower_hide_anim (id: 5) 
    instance.registerEObj( "sgvf_z2r1_b0762_2", 2006505, 6046598, 4, { 288.000000f, -415.885803f, 154.751602f }, 1.000000f, 0.000000f ); 
    // States -> tower_hide (id: 2) tower_show_anim (id: 4) tower_hide_anim (id: 5) 
    instance.registerEObj( "sgvf_z2r1_b0762_3", 2006506, 6046599, 4, { 272.000000f, -415.885803f, 138.751602f }, 1.000000f, 0.000000f ); 
    // States -> tower_hide (id: 2) tower_show_anim (id: 4) tower_hide_anim (id: 5) 
    instance.registerEObj( "unknown_6", 2006507, 5960467, 4, { 287.856598f, -415.885803f, 143.716400f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2006508, 5960881, 4, { 285.596008f, -415.885803f, 140.864807f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z2r1_b0764", 2006509, 6046600, 4, { 302.141998f, -415.885803f, 124.609596f }, 1.000000f, 0.000000f ); 
    // States -> sign_hide (id: 2) sign_show (id: 3) sign_show_anim (id: 4) sign_hide_anim (id: 5) 
    instance.registerEObj( "sgvf_z2r1_b0764_1", 2006510, 6046601, 4, { 302.141998f, -415.885803f, 152.893600f }, 1.000000f, 0.000000f ); 
    // States -> sign_hide (id: 2) sign_show (id: 3) sign_show_anim (id: 4) sign_hide_anim (id: 5) 
    instance.registerEObj( "sgvf_z2r1_b0764_2", 2006511, 6046603, 4, { 273.858002f, -415.885803f, 152.893600f }, 1.000000f, 0.000000f ); 
    // States -> sign_hide (id: 2) sign_show (id: 3) sign_show_anim (id: 4) sign_hide_anim (id: 5) 
    instance.registerEObj( "sgvf_z2r1_b0764_3", 2006512, 6046605, 4, { 273.858002f, -415.885803f, 124.609596f }, 1.000000f, 0.000000f ); 
    // States -> sign_hide (id: 2) sign_show (id: 3) sign_show_anim (id: 4) sign_hide_anim (id: 5) 
    instance.registerEObj( "unknown_8", 2006557, 0, 4, { 287.799805f, -404.548615f, 195.221893f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2002735, 0, 4, { 288.000000f, -384.162506f, -95.628960f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_4", 2002872, 5965592, 4, { 288.000000f, -384.162506f, -95.628960f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 288.126709f, -384.000000f, -148.276505f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2006553, 5963619, 4, { 315.121185f, -383.995300f, -124.638199f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2006554, 5963620, 4, { 306.932800f, -383.996399f, -105.577400f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2006555, 5963624, 4, { 269.917114f, -383.996613f, -104.726303f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2006556, 5963623, 4, { 260.673615f, -383.995697f, -124.058601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2006558, 5962617, 4, { 290.482605f, -383.959595f, -120.825897f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_collison_only", 2002618, 6081545, 4, { -299.194611f, 190.131699f, 168.493698f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2006480, 6038921, 4, { 0.900612f, -170.857101f, -94.333923f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2006481, 6038938, 4, { -0.336078f, -173.837097f, -233.919296f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_17", 2006482, 6038951, 4, { 288.027313f, -389.776489f, 270.818390f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_18", 2006483, 6038992, 4, { 287.894806f, -401.574585f, 187.283997f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2006484, 6038994, 4, { 284.993500f, -415.823212f, 86.327766f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2006485, 6039015, 4, { 287.921509f, -390.522614f, 3.389776f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 5965364, 4, { -300.557312f, 212.000000f, 117.936600f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 5965516, 4, { -278.075989f, 212.000000f, 79.110680f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_21", 2006486, 6035569, 4, { -315.424896f, 212.000000f, 174.253601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2006487, 6034672, 4, { -258.244904f, 212.000000f, 126.032799f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_z2r1_lvd_collison", 2006488, 6048680, 4, { -328.040894f, 212.000000f, 55.589699f }, 1.000000f, 0.000000f ); 
    // States -> collison_off (id: 10) collison_on (id: 11) 
    instance.registerEObj( "unknown_23", 2002735, 0, 4, { -419.231812f, 186.000000f, -74.560600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_5", 2002872, 5965586, 4, { -419.093201f, 186.000000f, -73.534798f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_24", 2006513, 6035498, 4, { -419.235107f, 186.000000f, -161.599701f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2006514, 0, 4, { -431.485107f, 186.000000f, -119.195801f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2006515, 6035399, 4, { -436.306396f, 186.750000f, -119.027199f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_27", 2006516, 6035398, 4, { -435.929291f, 186.750000f, -118.520103f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_28", 2006517, 6035400, 4, { -436.270203f, 186.750000f, -119.108101f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_29", 2006518, 6035453, 4, { -456.071899f, 186.169495f, -117.249802f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2006519, 6046161, 4, { -422.286713f, 186.000000f, -116.948799f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_31", 2002735, 0, 4, { 0.000000f, -191.204102f, -65.541000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_6", 2002872, 5965587, 4, { -0.369300f, -191.254105f, -64.493927f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_32", 2006490, 5960825, 4, { 0.213054f, -159.951599f, -180.332703f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_33", 2006491, 5960830, 4, { -8.808896f, -159.965195f, -172.749893f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_34", 2006492, 5960829, 4, { 0.816076f, -160.000000f, -164.794800f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_35", 2006493, 5960826, 4, { 9.567483f, -160.000000f, -172.413895f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_36", 2006494, 5960831, 4, { 11.416360f, -160.000000f, -185.623001f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_37", 2006495, 5960837, 4, { 21.345461f, -160.000000f, -178.053101f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_38", 2006496, 5960835, 4, { 21.132700f, -159.955307f, -155.512405f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_39", 2006497, 5960832, 4, { 10.413970f, -159.959305f, -145.012100f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_40", 2006498, 5960833, 4, { -11.132170f, -159.967697f, -145.107101f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_41", 2006499, 5960834, 4, { -23.702101f, -159.669800f, -155.260895f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_42", 2006500, 5960836, 4, { -22.808531f, -160.000000f, -178.798004f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_43", 2006501, 5960817, 4, { -11.047090f, -159.967697f, -185.956802f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Basicconveyanceunit", 2006473, 5939346, 4, { -319.478088f, 216.000000f, 222.247696f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Basicconveyanceunit_1", 2006474, 5939357, 4, { -288.014099f, 196.138107f, 47.531738f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Basicconveyanceunit_2", 2006475, 5938845, 4, { -429.923004f, 190.000000f, -34.653320f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Basicconveyanceunit_3", 2006476, 5938846, 4, { 10.635500f, -192.000000f, 224.872192f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Basicconveyanceunit_4", 2006477, 5937335, 4, { 4.501404f, -192.000000f, -0.015320f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Basicconveyanceunit_5", 2006478, 5941617, 4, { 283.497314f, -400.000000f, 229.022598f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Basicconveyanceunit_6", 2006479, 5941618, 4, { 292.469604f, -400.000000f, 48.325321f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 5965017, 5, { -312.459290f, 216.000000f, 229.715897f }, 1.000000f, 0.000000f ); 
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

EXPOSE_SCRIPT( TheVoidArk );