#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFractalContinuum : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFractalContinuum() : Sapphire::ScriptAPI::InstanceContentScript( 35 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5777077, 5777081, 4, { 140.603302f, 2.700000f, 34.720928f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2005259, 5777078, 5777083, 4, { 106.765198f, 2.700000f, 53.335590f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_0", 2002735, 0, 5777079, 4, { 138.876297f, 2.700000f, 35.495899f }, 1.000000f, -1.051032f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5777135, 5777137, 4, { -185.039200f, -0.000010f, 97.665123f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2005260, 5777136, 5777143, 4, { -143.174301f, -0.000001f, 86.487961f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2002735, 0, 5777138, 4, { -179.727097f, -0.015191f, 96.334610f }, 0.790818f, 1.311814f, 0); 
    instance.addEObj( "Biomassincubator", 2005480, 5627459, 5854755, 4, { -143.238602f, 2.285363f, 101.305000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Biomassincubator_1", 2005481, 5632316, 5854758, 4, { -150.372604f, 2.650113f, 73.551849f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Biomassincubator_2", 2005482, 5627460, 5854761, 4, { -170.712601f, 2.379743f, 108.801201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Biomassincubator_3", 2005483, 5632317, 5854762, 4, { -178.309097f, 2.550030f, 81.099091f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2005476, 5852048, 5854764, 4, { -143.988998f, 0.000000f, 100.704399f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2005477, 5852047, 5854765, 4, { -150.881500f, 0.000000f, 74.554863f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2005478, 5852050, 5854766, 4, { -170.231705f, 0.000000f, 108.158203f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2005479, 5852049, 5854768, 4, { -177.203705f, 0.000000f, 81.434868f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2002735, 0, 5777410, 4, { -0.027993f, 46.596539f, -329.937805f }, 1.701462f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_4", 2002872, 5777412, 5777409, 4, { -0.735815f, 46.585819f, -331.464386f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Shortcut", 2000700, 0, 5615537, 4, { 4.587201f, 0.167401f, 228.424301f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 5615539, 4, { -0.198364f, 46.585819f, -364.727509f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2000182, 5615534, 5615542, 5, { 1.419067f, -0.015320f, 234.058105f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Allaganteleporter", 2005242, 5722042, 5776628, 4, { 36.979809f, 1.210160f, 215.020599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2005251, 5754030, 5776632, 4, { 0.697166f, -0.000000f, 210.678497f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Guidepanel", 2005252, 0, 5776663, 4, { 189.739594f, 2.452829f, 125.865196f }, 0.991760f, 0.993538f, 0); 
    instance.addEObj( "Guidepanel_1", 2005253, 0, 5776665, 4, { 225.485703f, 3.355857f, 61.434238f }, 1.000000f, -0.867772f, 0); 
    instance.addEObj( "Guidepanel_2", 2005254, 0, 5776692, 4, { 158.995697f, 4.255857f, 31.260679f }, 1.000000f, -0.732914f, 0); 
    instance.addEObj( "unknown_8", 2005246, 5607049, 5776748, 4, { 230.547394f, 0.900000f, 95.770508f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2005247, 5607052, 5776790, 4, { 228.780106f, 1.800000f, 59.805061f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2005248, 5607058, 5776856, 4, { 184.888702f, 1.800000f, 26.321140f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Allaganteleporter_1", 2005243, 5722173, 5776875, 4, { 65.541313f, 3.869573f, 77.942459f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter_2", 2005261, 5722056, 5776627, 4, { 1.617853f, 1.549526f, 178.122406f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_11", 2005257, 5581056, 5795644, 4, { 130.087601f, 2.694753f, 39.807980f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2005425, 5829636, 5851227, 4, { 124.304901f, 2.666066f, 55.191471f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2005250, 5810989, 5852423, 4, { 2.160641f, 0.030060f, 207.184006f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2005249, 5614162, 5777002, 4, { -211.984406f, 0.000000f, 104.404701f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Allaganteleporter_3", 2005244, 5722174, 5777005, 4, { -103.539803f, 1.217043f, 76.015160f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_15", 2005358, 5763607, 5851271, 4, { -352.642700f, 1.499993f, 119.149300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2005359, 5763630, 5851272, 4, { -351.399994f, 1.480042f, 110.398903f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_17", 2005360, 5763608, 5851273, 4, { -349.473907f, 1.499977f, 99.800461f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2005364, 5650881, 5851274, 4, { -352.015686f, 1.499995f, 116.202499f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2005365, 5650883, 5851275, 4, { -350.711609f, 1.499995f, 107.232002f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2005366, 5819525, 5851276, 4, { -348.442902f, 1.499981f, 98.183548f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2005361, 5814450, 5851277, 4, { -288.068115f, -2.700021f, 113.654198f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2005362, 5814433, 5851278, 4, { -272.828888f, -2.700021f, 111.659203f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2005363, 5814516, 5851279, 4, { -268.089691f, -2.700021f, 117.225700f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2005367, 5819526, 5851280, 4, { -286.325989f, -2.700022f, 113.195000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2005368, 5650635, 5851281, 4, { -271.312897f, -2.700021f, 112.812401f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2005369, 5819527, 5851282, 4, { -266.722595f, -2.700022f, 118.620300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Informationpanel", 2005255, 0, 5776983, 4, { -230.635101f, 1.639121f, 176.464996f }, 1.000000f, 0.397825f, 0); 
    instance.addEObj( "Informationpanel_1", 2005256, 0, 5777001, 4, { -348.181610f, 1.613136f, 135.909897f }, 0.991760f, -1.475439f, 0); 
    instance.addEObj( "Informationpanel_2", 2005674, 0, 5879297, 4, { -345.653900f, 1.626497f, 98.636726f }, 0.991760f, -0.932389f, 0); 
    instance.addEObj( "Informationpanel_3", 2005675, 0, 5879298, 4, { -324.880798f, 1.642515f, 68.081039f }, 1.000000f, -0.418331f, 0); 
    instance.addEObj( "unknown_27", 2005268, 5652510, 5777015, 4, { -51.865479f, 53.147091f, -208.636703f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_28", 2005269, 5652511, 5777016, 4, { 54.518261f, 53.147091f, -208.602707f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_29", 2005270, 5643840, 5777019, 4, { -149.095901f, 53.147091f, -378.377991f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_30", 2005271, 5652506, 5777020, 4, { -96.421806f, 53.147091f, -467.216003f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_31", 2005272, 5652515, 5777021, 4, { 149.401093f, 53.147091f, -378.561096f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_32", 2005273, 5652509, 5777022, 4, { 98.842590f, 53.164989f, -466.923706f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_33", 2005318, 0, 5796526, 4, { -8.227161f, 53.165001f, -195.021896f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_34", 2005329, 5670473, 5820844, 4, { 130.894806f, 53.165001f, -422.856415f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_35", 2005330, 5670424, 5820853, 4, { 3.461859f, 53.165001f, -200.625595f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_36", 2005331, 5670459, 5820856, 4, { -131.889603f, 53.165001f, -421.513885f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Emeraldcontrolunit", 2005262, 5819696, 5777009, 4, { 127.567200f, 55.922291f, -423.497711f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Violetcontrolunit", 2005263, 5819695, 5777010, 4, { -0.232653f, 56.361301f, -203.010300f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Crimsoncontrolunit", 2005264, 5819698, 5777011, 4, { -126.342796f, 55.969429f, -423.260895f }, 0.991760f, 0.000048f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFractalContinuum );