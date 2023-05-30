#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheCopiedFactory : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheCopiedFactory() : Sapphire::ScriptAPI::InstanceContentScript( 30087 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -500.062012f, 423.564301f, 21.562880f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8127876, 4, { -500.062012f, 423.962708f, 21.562880f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2007457, 8156454, 4, { -501.201111f, 401.000000f, -30.586300f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -702.927979f, 333.582306f, -288.686798f }, 0.991760f, -1.570451f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8127884, 4, { -702.927979f, 333.582306f, -288.686798f }, 1.000000f, -1.570451f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2007457, 8193582, 4, { -804.150330f, -2.569809f, -239.550797f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { 900.000000f, -673.015808f, 827.839600f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8127740, 4, { 900.000000f, -673.015808f, 827.839600f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2007457, 0, 4, { 902.487671f, -700.000000f, 675.391174f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8143665, 4, { 899.043213f, -700.000000f, 763.735779f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8196980, 4, { 900.000000f, -700.000000f, 698.575928f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2002735, 0, 4, { 900.000000f, -700.000122f, 457.747986f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 8128002, 4, { 899.925293f, -700.000000f, 457.567688f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_lvd_collison_only", 2002618, 8513206, 4, { -500.053986f, 423.636597f, 19.335199f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2002735, 0, 4, { -606.236816f, 343.936005f, -287.000000f }, 0.991760f, -1.570451f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 8128069, 4, { -606.000916f, 343.936005f, -287.000000f }, 1.000000f, -1.570451f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2007457, 8128084, 4, { -626.500000f, 348.117889f, -287.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_6", 2007457, 8128099, 4, { -750.477173f, -495.990204f, 555.077393f }, 1.000000f, -1.570796f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_7", 2007457, 8128100, 4, { -801.180176f, -495.990204f, 534.327271f }, 1.000000f, -0.759259f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_10", 2002735, 0, 4, { -750.062317f, -495.990204f, 555.077393f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "sgbg_w_qic_004_05a", 2007457, 8155632, 4, { -750.477173f, -495.990204f, 555.077393f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "Accesspoint", 2010799, 8145319, 4, { -494.069489f, 484.002686f, 242.592606f }, 1.000000f, 1.224958f); 
    instance.registerEObj( "Accesspoint_1", 2010800, 8146573, 4, { -577.189270f, 352.994202f, -266.399994f }, 0.991760f, 1.417948f); 
    instance.registerEObj( "Accesspoint_2", 2010801, 8142101, 4, { -678.453125f, 338.311005f, -329.828094f }, 0.991760f, 1.540283f); 
    instance.registerEObj( "Accesspoint_3", 2010802, 8143950, 4, { -679.987793f, -482.902313f, 606.301880f }, 0.991760f, 1.506345f); 
    instance.registerEObj( "Accesspoint_4", 2010803, 8143953, 4, { 903.335815f, -677.000000f, 904.332581f }, 1.000000f, 0.035768f); 
    instance.registerEObj( "Accesspoint_5", 2010804, 8143955, 4, { 903.218323f, -701.000000f, 485.459412f }, 0.991760f, 0.144916f); 
    instance.registerEObj( "Accesspoint_6", 2010839, 8196872, 4, { -507.031586f, 423.999390f, 78.642242f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 8127769, 5, { -500.104187f, 484.002899f, 248.789597f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 900.000000f, -700.000122f, 403.452911f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "???", 2010848, 0, 4, { -504.783691f, 484.000885f, 234.820999f }, 0.991760f, -0.798825f); 
    instance.registerEObj( "???_1", 2010869, 0, 4, { -505.213715f, 463.978210f, 217.634003f }, 0.991760f, -0.021360f); 
    instance.registerEObj( "???_2", 2010870, 0, 4, { -541.603577f, 400.992096f, -36.202400f }, 0.991760f, 0.757763f); 
    instance.registerEObj( "???_3", 2010871, 0, 4, { -676.264587f, -482.902313f, 612.481812f }, 0.991760f, 1.570796f); 
    instance.registerEObj( "???_4", 2010872, 0, 4, { -697.844482f, 339.183289f, -378.339813f }, 0.991760f, 1.520213f); 
    instance.registerEObj( "???_5", 2010873, 0, 4, { -711.207825f, -498.008698f, 547.203674f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "???_6", 2010874, 0, 4, { -626.522827f, 340.980988f, -367.006012f }, 0.991760f, 1.570796f); 
    instance.registerEObj( "???_7", 2010875, 0, 4, { -712.132874f, -495.990387f, 562.363525f }, 0.991760f, 1.570796f); 
    instance.registerEObj( "???_8", 2010876, 0, 4, { 900.054626f, -673.029724f, 828.702087f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "???_9", 2010877, 0, 4, { 911.146423f, -677.000000f, 894.113586f }, 0.991760f, 0.268428f); 
    instance.registerEObj( "???_10", 2010878, 0, 4, { 874.795715f, -676.000000f, 885.001587f }, 0.991760f, -0.798825f); 
    instance.registerEObj( "Exittotheexcavationtunnels", 2010831, 0, 4, { -499.015808f, 485.302704f, 280.262512f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Passagetozone1", 2010881, 0, 4, { 903.524475f, -677.058105f, 904.030518f }, 0.991760f, 1.558214f); 
    instance.registerEObj( "Passagetozone1_1", 2010880, 0, 4, { -680.427002f, -482.900085f, 605.950806f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Passagetozone1_2", 2010879, 0, 4, { -678.003113f, 338.413513f, -329.509491f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Passagetozone4", 2010882, 0, 4, { -684.016174f, 335.879913f, -292.011993f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Passagetozone2", 2010883, 0, 4, { -683.113770f, -482.203094f, 646.662476f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Passagetozone1_3", 2010884, 0, 4, { -577.538696f, 352.986786f, -266.010590f }, 0.991760f, -1.570451f); 
    instance.registerEObj( "Passagetozone5", 2010944, 0, 4, { -836.636902f, -492.233612f, 498.069702f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Passagetozone4_1", 2010945, 0, 4, { 900.053284f, -673.243286f, 930.235718f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Passagetozone1_4", 2010947, 0, 4, { -507.415985f, 423.999390f, 78.374748f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Tarnishedthingamajig", 2010835, 0, 4, { -747.956787f, -489.979706f, 603.128418f }, 1.449585f, -1.320251f); 
    instance.registerEObj( "Rustywhatsit", 2010836, 0, 4, { -688.270874f, -483.979004f, 582.279785f }, 1.500000f, 0.586268f); 
    instance.registerEObj( "Brokenkickumbob", 2010825, 0, 4, { -708.186523f, 339.200012f, -350.575989f }, 1.480000f, 0.000047f); 
    instance.registerEObj( "Tarnishedthingamajig_1", 2010826, 0, 4, { -747.956787f, -489.979706f, 603.128418f }, 1.480042f, -1.320250f); 
    instance.registerEObj( "Rustywhatsit_1", 2010827, 0, 4, { -688.270874f, -483.979004f, 582.279785f }, 1.500000f, 0.586268f); 
    instance.registerEObj( "Brokenkickumbob_1", 2010834, 0, 4, { -708.186523f, 339.200012f, -350.575989f }, 1.480042f, 0.000047f); 
    instance.registerEObj( "Destination", 2011156, 0, 4, { -694.056580f, 339.162109f, -370.260193f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Machinelifeformwreckage", 2011456, 0, 4, { -679.534119f, 335.322113f, -307.875885f }, 0.991760f, 0.504248f); 
    instance.registerEObj( "Machinelifeformwreckage_1", 2011457, 0, 4, { -643.468872f, 338.413513f, -353.815796f }, 0.991760f, 0.869376f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheCopiedFactory );