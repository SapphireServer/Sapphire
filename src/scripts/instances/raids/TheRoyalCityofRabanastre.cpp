#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheRoyalCityofRabanastre :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheRoyalCityofRabanastre() :
    Sapphire::ScriptAPI::InstanceContentScript( 30058 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -319.173004f, 9.994568f, 320.515686f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7069100, 4, { -319.896515f, 10.000000f, 325.206085f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_z3r1_b1269", 2007457, 7075766, 4, { -320.000000f, 1.230700f, 221.199997f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1269_1", 2007457, 7075769, 4, { -320.351501f, 1.230694f, 262.307892f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1269_2", 2007457, 7075770, 4, { -346.200012f, 1.229800f, 238.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009060, 0, 4, { -311.306702f, 1.230747f, 242.805496f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2009061, 0, 4, { -316.517914f, 1.205444f, 246.509399f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7069107, 4, { -319.661407f, 10.000000f, -11.625690f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2009055, 0, 4, { -336.110504f, 9.964111f, -51.682369f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_4", 2009057, 0, 4, { -306.355408f, 9.964111f, -48.539001f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 7075611, 4, { -320.081390f, 10.000000f, -69.048653f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgbg_z3r1_a2_lc01a", 2007457, 7075799, 4, { -320.000702f, 10.000000f, -56.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r1_a2_lc01a_1", 2007457, 7075800, 4, { -310.799988f, 10.000000f, -41.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r1_a2_lc01a_2", 2007457, 7075801, 4, { -329.200012f, 10.000000f, -41.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 7076220, 4, { -315.688690f, 10.000000f, -47.888401f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_btl_b0527", 2007457, 7075820, 4, { -316.520996f, 10.000000f, -31.534470f }, 1.000000f, 0.000000f ); 
    // States -> hadokyu_off_a (id: 7) hadokyu_on_a (id: 8) hadokyu_on_b (id: 9) hadokyu_on_c (id: 10) 
    instance.registerEObj( "unknown_6", 2007457, 7077538, 4, { -338.909393f, 10.000000f, -32.073681f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007791, 0, 4, { -319.963013f, 10.052400f, -16.952101f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2009242, 0, 4, { -332.255402f, 10.108630f, -33.994350f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2007457, 7080565, 4, { 106.000000f, -694.000000f, -128.399994f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_9", 2007791, 0, 4, { 106.000000f, -694.000000f, -128.399994f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_btl_b1275", 2007457, 7082088, 4, { 108.221199f, -694.000000f, -208.120697f }, 1.000000f, 0.000000f ); 
    // States -> cd_off (id: 3) cd_omen (id: 4) cd_omen_anim (id: 5) cd_on (id: 6) cd_on_anim (id: 7) cd_off_anim (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b1275_1", 2007457, 7082089, 4, { 121.728897f, -694.000000f, -183.748199f }, 1.000000f, 0.000000f ); 
    // States -> cd_off (id: 3) cd_omen (id: 4) cd_omen_anim (id: 5) cd_on (id: 6) cd_on_anim (id: 7) cd_off_anim (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b1275_2", 2007457, 7082090, 4, { 94.008781f, -694.000000f, -182.456207f }, 1.000000f, 0.000000f ); 
    // States -> cd_off (id: 3) cd_omen (id: 4) cd_omen_anim (id: 5) cd_on (id: 6) cd_on_anim (id: 7) cd_off_anim (id: 8) 
    instance.registerEObj( "Darkcircle", 2009076, 0, 4, { 83.147507f, -694.000000f, -193.267899f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_1", 2009203, 0, 4, { 83.057159f, -694.000000f, -182.946304f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_2", 2009204, 0, 4, { 89.546783f, -694.000000f, -172.278000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_3", 2009205, 0, 4, { 96.837830f, -694.000000f, -165.190094f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_4", 2009206, 0, 4, { 105.990601f, -694.000000f, -164.696304f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_5", 2009207, 0, 4, { 117.216599f, -694.000000f, -169.060196f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_6", 2009208, 0, 4, { 125.204498f, -694.000000f, -175.811493f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_7", 2009209, 0, 4, { 130.969604f, -694.000000f, -185.265594f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_8", 2009210, 0, 4, { 130.999893f, -694.000000f, -195.328003f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_9", 2009211, 0, 4, { 124.798302f, -694.000000f, -204.280807f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_10", 2009212, 0, 4, { 114.994301f, -694.000000f, -210.576996f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Darkcircle_11", 2009213, 0, 4, { 103.221703f, -694.000000f, -213.151794f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_1", 2007457, 7079402, 4, { 104.478500f, -679.000000f, -322.819489f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_10", 2007791, 0, 4, { 106.449997f, -679.000000f, -328.250000f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_11", 2009068, 0, 4, { 97.794479f, -679.000000f, -387.672394f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2009069, 0, 4, { 101.213097f, -679.000000f, -388.533600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2009070, 0, 4, { 104.362602f, -679.000000f, -388.768097f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1284", 2007457, 7081152, 4, { 101.446701f, -679.000000f, -398.626587f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1278", 2007457, 7081153, 4, { 114.988701f, -679.000000f, -399.119598f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1277", 2007457, 7081154, 4, { 105.230202f, -679.000000f, -389.831512f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r1_a4_stn03", 2007457, 7151392, 4, { 105.983803f, -679.025024f, -386.058899f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1258", 2009221, 7094307, 4, { -323.781189f, 9.994568f, 322.467499f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_z3r1_b1258_1", 2009222, 7094363, 4, { -325.789886f, 1.230697f, 217.839005f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007457, 7041438, 4, { -274.571594f, 2.310245f, 37.022179f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Waterwaygatelever", 2009184, 7080218, 4, { 338.918091f, -262.287415f, 267.698608f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Waterwaygatelever_1", 2009186, 7080217, 4, { 337.924988f, -322.267212f, 299.494385f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Waterwaygatelever_2", 2009188, 7080216, 4, { 338.580200f, -292.267212f, 331.283905f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007457, 7080221, 4, { 323.797211f, -262.267395f, 275.364105f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2007457, 7080220, 4, { 324.137909f, -322.267303f, 308.012604f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2007457, 7080219, 4, { 325.866394f, -292.267212f, 339.968201f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2007457, 7080213, 4, { 205.647507f, -374.000092f, 339.617889f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2007457, 7080215, 4, { 164.959000f, -374.000092f, 324.108002f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Passagecontrols", 2009200, 0, 4, { 189.533096f, -373.602295f, 305.302490f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Passagecontrols_1", 2009201, 0, 4, { 162.416901f, -373.621887f, 283.383911f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Passagecontrols_2", 2009202, 0, 4, { 167.371002f, -373.190186f, 332.672913f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Scratchedlettering", 2009271, 0, 4, { 272.859009f, -490.182709f, 293.584595f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Scratchedlettering_1", 2009272, 0, 4, { 212.923599f, -491.264191f, 290.957306f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Scratchedlettering_2", 2009273, 0, 4, { 211.674301f, -491.485199f, 242.033600f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Skypiratesscrawlings", 2009435, 0, 4, { 222.766403f, -333.455414f, 360.799591f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_z3r1_b1258_2", 2009223, 7102857, 4, { 101.048698f, -694.000000f, -122.909698f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1258_3", 2009224, 7102858, 4, { 99.562241f, -694.000000f, -216.590393f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1258_4", 2009225, 7102860, 4, { 99.290398f, -679.011230f, -323.639587f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_20", 2009190, 0, 4, { -298.663086f, -4.197479f, 44.907139f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_21", 2009191, 0, 4, { -301.684296f, -4.350000f, 41.550209f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_22", 2009192, 0, 4, { -304.369995f, -4.219625f, 44.113739f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_23", 2009193, 0, 4, { -316.182190f, -4.226807f, 42.099609f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_24", 2009194, 0, 4, { -319.364990f, -4.219666f, 44.197979f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2009195, 0, 4, { -322.700989f, -4.219666f, 42.268631f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2009196, 0, 4, { -331.298615f, -4.379395f, 42.587891f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_27", 2009197, 0, 4, { -334.136810f, -4.379395f, 39.322510f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_28", 2009198, 0, 4, { -337.097107f, -4.379391f, 41.112068f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_29", 2009199, 0, 4, { -320.000000f, 19.928169f, -182.845596f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2002735, 0, 4, { -320.106812f, 19.946039f, -144.699493f }, 1.750000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7099082, 4, { -320.132294f, 19.899990f, -145.586395f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 7099092, 4, { -319.884003f, 19.900000f, -202.859207f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Teleportationcrystal", 2009176, 7102798, 4, { -326.309998f, 5.729747f, 406.047699f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Teleportationcrystal_1", 2009177, 7102799, 4, { -326.251099f, 9.753006f, 115.489799f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_2", 2009178, 7102800, 4, { -326.389801f, 10.000000f, -10.478860f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_3", 2009179, 7102801, 4, { -312.818115f, 19.899851f, -141.350296f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_4", 2009180, 7102802, 4, { 439.169189f, -229.561905f, 292.789886f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_5", 2009181, 7102803, 4, { 133.837006f, -374.000092f, 311.904785f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_6", 2009182, 7102804, 4, { 114.414299f, -694.000000f, -113.204399f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_7", 2009183, 7102805, 4, { 97.279610f, -679.000000f, -305.258087f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7069095, 5, { -328.378906f, 0.730057f, 439.144012f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 106.318901f, -679.000000f, -398.354614f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheRoyalCityofRabanastre );