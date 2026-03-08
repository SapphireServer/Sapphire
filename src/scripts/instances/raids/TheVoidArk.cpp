#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheVoidArk : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheVoidArk() : Sapphire::ScriptAPI::InstanceContentScript( 30029 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5965017, 5965018, 5, { -312.459290f, 216.000000f, 229.715897f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -312.456604, 218.000000, 223.715897 }, -0.000000, 2.497972, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -312.457520, 218.000000, 235.715897 }, -0.000000, 2.500406, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -306.459290, 218.000000, 229.711502 }, -1.570451, 2.500640, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -318.459290, 218.000000, 229.714432 }, -1.570451, 2.504768, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -316.657227, 218.000000, 225.513824 }, -0.785398, 2.650707, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -308.261353, 218.000000, 233.917969 }, -0.785398, 2.644853, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -308.259277, 218.000000, 225.515900 }, 0.785398, 2.647780, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -316.659302, 218.000000, 233.915894 }, 0.785398, 2.647780, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Basicconveyanceunit", 2006473, 5939346, 5965026, 4, { -319.478088f, 216.000000f, 222.247696f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_1", 2006474, 5939357, 5965027, 4, { -288.014099f, 196.138107f, 47.531738f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_2", 2006475, 5938845, 5965028, 4, { -429.923004f, 190.000000f, -34.653320f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_3", 2006476, 5938846, 5965029, 4, { 10.635500f, -192.000000f, 224.872192f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_4", 2006477, 5937335, 5965030, 4, { 4.501404f, -192.000000f, -0.015320f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_5", 2006478, 5941617, 5965031, 4, { 283.497314f, -400.000000f, 229.022598f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Basicconveyanceunit_6", 2006479, 5941618, 5965033, 4, { 292.469604f, -400.000000f, 48.325321f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 5965364, 5965365, 4, { -300.557312f, 212.000000f, 117.936600f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -300.557312, 214.500000, 117.936600 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5965516, 5965519, 4, { -278.075989f, 212.000000f, 79.110680f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -278.075989, 214.500000, 79.110680 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_21", 2006486, 6035569, 5965541, 4, { -315.424896f, 212.000000f, 174.253601f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_22", 2006487, 6034672, 5965543, 4, { -258.244904f, 212.000000f, 126.032799f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_z2r1_lvd_collison", 2006488, 6048680, 5965551, 4, { -328.040894f, 212.000000f, 55.589699f }, 1.000000f, 0.000000f, 0 ); 
    // States -> collison_off (id: 10) collison_on (id: 11) 
    pEObj->addCollisionBox( { -333.855743, 212.000000, 51.436230 }, -2.268928, 5.188600, 4.000000, 1.000000 );
    pEObj->addCollisionBox( { -326.677277, 212.000000, 58.597443 }, -2.443461, 5.188600, 4.000000, 1.000000 );
    pEObj->addCollisionBox( { -321.061371, 212.000000, 62.943478 }, -2.583087, 2.076200, 4.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5965568, 4, { -288.000000f, 196.497299f, 30.140800f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2002735, 0, 5965569, 4, { 0.220062f, -191.999893f, 170.174606f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2002735, 0, 5965570, 4, { 288.000000f, -400.000000f, 205.443207f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2002735, 0, 5965571, 4, { 288.000000f, -384.162506f, -95.628960f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_31", 2002735, 0, 5965572, 4, { 0.000000f, -191.204102f, -65.541000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_23", 2002735, 0, 5965573, 4, { -419.231812f, 186.000000f, -74.560600f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_5", 2002872, 5965586, 5965594, 4, { -419.093201f, 186.000000f, -73.534798f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -419.093201, 191.843445, -73.534798 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_6", 2002872, 5965587, 5965595, 4, { -0.369300f, -191.254105f, -64.493927f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -0.369300, -185.410660, -64.493927 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char", 2002872, 5965588, 5965596, 4, { -288.643890f, 196.450897f, 30.140779f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -288.643890, 202.294342, 30.140779 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_2", 2002872, 5965590, 5965598, 4, { 0.354952f, -191.297607f, 150.971207f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.354952, -185.454163, 150.971207 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_3", 2002872, 5965591, 5965600, 4, { 287.996399f, -400.000000f, 205.904694f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 287.996399, -394.156555, 205.904694 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_4", 2002872, 5965592, 5965601, 4, { 288.000000f, -384.162506f, -95.628960f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 288.000000, -378.319061, -95.628960 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_1", 2002872, 5965606, 5965607, 4, { -315.195099f, 196.497299f, 1.375446f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -315.195099, 202.340744, 1.375446 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5965609, 4, { 288.126709f, -384.000000f, -148.276505f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2006489, 5961744, 5965667, 4, { -289.112610f, 196.497299f, -1.589648f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_32", 2006490, 5960825, 5966436, 4, { 0.213054f, -159.951599f, -180.332703f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_33", 2006491, 5960830, 5966437, 4, { -8.808896f, -159.965195f, -172.749893f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_34", 2006492, 5960829, 5966438, 4, { 0.816076f, -160.000000f, -164.794800f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_35", 2006493, 5960826, 5966439, 4, { 9.567483f, -160.000000f, -172.413895f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_36", 2006494, 5960831, 5966440, 4, { 11.416360f, -160.000000f, -185.623001f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_37", 2006495, 5960837, 5966441, 4, { 21.345461f, -160.000000f, -178.053101f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_38", 2006496, 5960835, 5966442, 4, { 21.132700f, -159.955307f, -155.512405f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_39", 2006497, 5960832, 5966443, 4, { 10.413970f, -159.959305f, -145.012100f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_40", 2006498, 5960833, 5966444, 4, { -11.132170f, -159.967697f, -145.107101f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_41", 2006499, 5960834, 5966445, 4, { -23.702101f, -159.669800f, -155.260895f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_42", 2006500, 5960836, 5966446, 4, { -22.808531f, -160.000000f, -178.798004f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_43", 2006501, 5960817, 5966447, 4, { -11.047090f, -159.967697f, -185.956802f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_15", 2006480, 6038921, 5966544, 4, { 0.900612f, -170.857101f, -94.333923f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2006481, 6038938, 5966545, 4, { -0.336078f, -173.837097f, -233.919296f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2006482, 6038951, 5966546, 4, { 288.027313f, -389.776489f, 270.818390f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_18", 2006483, 6038992, 5966547, 4, { 287.894806f, -401.574585f, 187.283997f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_19", 2006484, 6038994, 5966548, 4, { 284.993500f, -415.823212f, 86.327766f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_20", 2006485, 6039015, 5966549, 4, { 287.921509f, -390.522614f, 3.389776f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_z2r1_b0762", 2006503, 6046596, 6034260, 4, { 288.000000f, -415.885803f, 122.751602f }, 1.000000f, 0.000000f, 0 ); 
    // States -> tower_hide (id: 2) tower_show_anim (id: 4) tower_hide_anim (id: 5) 

    pEObj = instance.addEObj( "sgvf_z2r1_b0762_1", 2006504, 6046597, 6034261, 4, { 304.000000f, -415.885803f, 138.751602f }, 1.000000f, 0.000000f, 0 ); 
    // States -> tower_hide (id: 2) tower_show_anim (id: 4) tower_hide_anim (id: 5) 

    pEObj = instance.addEObj( "sgvf_z2r1_b0762_2", 2006505, 6046598, 6034262, 4, { 288.000000f, -415.885803f, 154.751602f }, 1.000000f, 0.000000f, 0 ); 
    // States -> tower_hide (id: 2) tower_show_anim (id: 4) tower_hide_anim (id: 5) 

    pEObj = instance.addEObj( "sgvf_z2r1_b0762_3", 2006506, 6046599, 6034263, 4, { 272.000000f, -415.885803f, 138.751602f }, 1.000000f, 0.000000f, 0 ); 
    // States -> tower_hide (id: 2) tower_show_anim (id: 4) tower_hide_anim (id: 5) 

    pEObj = instance.addEObj( "unknown_6", 2006507, 5960467, 6034280, 4, { 287.856598f, -415.885803f, 143.716400f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2006508, 5960881, 6034290, 4, { 285.596008f, -415.885803f, 140.864807f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_z2r1_b0764", 2006509, 6046600, 6034301, 4, { 302.141998f, -415.885803f, 124.609596f }, 1.000000f, 0.000000f, 0 ); 
    // States -> sign_hide (id: 2) sign_show (id: 3) sign_show_anim (id: 4) sign_hide_anim (id: 5) 

    pEObj = instance.addEObj( "sgvf_z2r1_b0764_1", 2006510, 6046601, 6034302, 4, { 302.141998f, -415.885803f, 152.893600f }, 1.000000f, 0.000000f, 0 ); 
    // States -> sign_hide (id: 2) sign_show (id: 3) sign_show_anim (id: 4) sign_hide_anim (id: 5) 

    pEObj = instance.addEObj( "sgvf_z2r1_b0764_2", 2006511, 6046603, 6034303, 4, { 273.858002f, -415.885803f, 152.893600f }, 1.000000f, 0.000000f, 0 ); 
    // States -> sign_hide (id: 2) sign_show (id: 3) sign_show_anim (id: 4) sign_hide_anim (id: 5) 

    pEObj = instance.addEObj( "sgvf_z2r1_b0764_3", 2006512, 6046605, 6034304, 4, { 273.858002f, -415.885803f, 124.609596f }, 1.000000f, 0.000000f, 0 ); 
    // States -> sign_hide (id: 2) sign_show (id: 3) sign_show_anim (id: 4) sign_hide_anim (id: 5) 

    pEObj = instance.addEObj( "unknown_24", 2006513, 6035498, 6042629, 4, { -419.235107f, 186.000000f, -161.599701f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -424.131104, 196.000000, -152.332291 }, 2.356196, 0.500000, 10.000000, 2.736500 );
    pEObj->addCollisionBox( { -420.667358, 196.000000, -150.683090 }, 1.362546, 0.500000, 10.000000, 1.358207 );
    pEObj->addCollisionBox( { -417.813293, 196.000000, -150.748627 }, 1.733042, 0.500000, 10.000000, 1.358900 );
    pEObj->addCollisionBox( { -414.436981, 196.000000, -152.407806 }, 0.785398, 0.500000, 10.000000, 2.696300 );
    pEObj->addCollisionBox( { -422.123688, 196.000000, -150.468796 }, 1.767141, 0.500000, 10.000000, 0.334848 );
    pEObj->addCollisionBox( { -416.369049, 196.000000, -150.582077 }, 1.374444, 0.500000, 10.000000, 0.287010 );

    pEObj = instance.addEObj( "unknown_25", 2006514, 0, 6042666, 4, { -431.485107f, 186.000000f, -119.195801f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_26", 2006515, 6035399, 6042672, 4, { -436.306396f, 186.750000f, -119.027199f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_27", 2006516, 6035398, 6042673, 4, { -435.929291f, 186.750000f, -118.520103f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_28", 2006517, 6035400, 6042674, 4, { -436.270203f, 186.750000f, -119.108101f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_29", 2006518, 6035453, 6042688, 4, { -456.071899f, 186.169495f, -117.249802f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_30", 2006519, 6046161, 6042695, 4, { -422.286713f, 186.000000f, -116.948799f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2006553, 5963619, 6047038, 4, { 315.121185f, -383.995300f, -124.638199f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2006554, 5963620, 6047039, 4, { 306.932800f, -383.996399f, -105.577400f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2006555, 5963624, 6047040, 4, { 269.917114f, -383.996613f, -104.726303f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_13", 2006556, 5963623, 6047041, 4, { 260.673615f, -383.995697f, -124.058601f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2006557, 0, 6047053, 4, { 287.799805f, -404.548615f, 195.221893f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2006558, 5962617, 6047069, 4, { 290.482605f, -383.959595f, -120.825897f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 6047090, 6047091, 4, { -0.028858f, -192.000000f, 97.337067f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -0.028858, -189.500000, 97.337067 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_3", 2006559, 5996197, 6047099, 4, { -0.306469f, -192.000000f, 68.934158f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -5.202456, -182.000000, 78.201576 }, 2.356196, 0.500000, 10.000000, 2.736500 );
    pEObj->addCollisionBox( { -1.738705, -182.000000, 79.850769 }, 1.362546, 0.500000, 10.000000, 1.358207 );
    pEObj->addCollisionBox( { 1.115353, -182.000000, 79.785240 }, 1.733042, 0.500000, 10.000000, 1.358900 );
    pEObj->addCollisionBox( { 4.491664, -182.000000, 78.126053 }, 0.785398, 0.500000, 10.000000, 2.696300 );
    pEObj->addCollisionBox( { -3.195062, -182.000000, 80.065056 }, 1.767141, 0.500000, 10.000000, 0.334848 );
    pEObj->addCollisionBox( { 2.559591, -182.000000, 79.951790 }, 1.374444, 0.500000, 10.000000, 0.287010 );

    pEObj = instance.addEObj( "unknown_4", 2006595, 6067109, 6068517, 4, { 0.064018f, -192.000107f, 129.936996f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_collison_only", 2002618, 6081545, 6081546, 4, { -299.194611f, 190.131699f, 168.493698f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -299.194611, 190.131699, 168.493698 }, -0.000000, 1.000000, 1.000000, 1.000000 );


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

EXPOSE_SCRIPT( TheVoidArk );