#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheLabyrinthoftheAncients :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheLabyrinthoftheAncients() :
    Sapphire::ScriptAPI::InstanceContentScript( 30001 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002108, 0, 4, { -109.946503f, 44.168140f, -165.619995f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 4317322, 5, { -110.032799f, 30.372690f, 417.614990f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Allaganteleporter", 2001023, 3445281, 4, { -117.450104f, 45.942120f, 317.195892f }, 0.778198f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0294", 2002793, 4493308, 4, { -148.301498f, 48.301128f, 279.915802f }, 1.000000f, 0.000000f ); 
    // States -> barrier_2loop (id: 3) barrier_stop (id: 4) barrier_loop (id: 10) barrier_2stop (id: 11) 
    instance.registerEObj( "sgvf_w_lvd_b0294_1", 2002794, 4493309, 4, { -109.977203f, 48.251709f, 243.024094f }, 0.991760f, 0.000048f ); 
    // States -> barrier_2loop (id: 3) barrier_stop (id: 4) barrier_loop (id: 10) barrier_2stop (id: 11) 
    instance.registerEObj( "sgvf_w_lvd_b0294_2", 2002795, 4493310, 4, { -71.722931f, 48.301121f, 280.086487f }, 1.000000f, 0.000000f ); 
    // States -> barrier_2loop (id: 3) barrier_stop (id: 4) barrier_loop (id: 10) barrier_2stop (id: 11) 
    instance.registerEObj( "unknown_1", 2001024, 4199521, 4, { -451.214386f, 41.580811f, 182.050903f }, 1.000000f, 0.000048f ); 
    instance.registerEObj( "sgpl_l1r1_boss1wall", 2001025, 4303928, 4, { -451.373688f, 24.800070f, 73.862427f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2001026, 0, 4, { -451.305206f, 24.873600f, 73.806000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2002798, 0, 4, { -355.665405f, 41.884102f, 279.420288f }, 1.550000f, -1.570796f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2002801, 4478011, 4, { -346.181488f, 42.801510f, 279.988708f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002799, 0, 4, { -415.959198f, 42.400002f, 280.898804f }, 1.550000f, -1.570796f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_1", 2002802, 4478013, 4, { -415.761597f, 42.400002f, 279.982788f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2002800, 0, 4, { -452.406799f, 42.400002f, 239.395096f }, 1.550000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_2", 2002803, 4478015, 4, { -451.081909f, 41.580811f, 243.305099f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0269", 2002839, 4493435, 4, { -413.650909f, 42.000000f, 279.285889f }, 0.991760f, 0.000048f ); 
    // States -> barrier_2loop (id: 3) barrier_stop (id: 4) barrier_loop (id: 10) barrier_2stop (id: 11) 
    instance.registerEObj( "sgvf_w_lvd_b0269_1", 2002840, 4493436, 4, { -450.220612f, 41.580811f, 247.690399f }, 0.991760f, 0.000048f ); 
    // States -> barrier_2loop (id: 3) barrier_stop (id: 4) barrier_loop (id: 10) barrier_2stop (id: 11) 
    instance.registerEObj( "Allaganteleporter_1", 2002807, 3445282, 4, { -301.062592f, 54.375320f, 290.201904f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Allaganteleporter_2", 2002808, 3974161, 4, { -457.203400f, 38.418018f, 104.051903f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut", 2002804, 0, 4, { -451.176910f, 25.504910f, 18.912251f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_l1r1_trash2wall", 2001027, 4304910, 4, { 191.423996f, 51.658699f, 280.097992f }, 0.400000f, 0.000000f ); 
    // States -> on (id: 20) off (id: 21) 
    instance.registerEObj( "sgpl_l1r1_trash2line", 2001028, 4304912, 4, { 191.145798f, 51.767059f, 279.359497f }, 0.400000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2001032, 0, 4, { 409.496094f, 66.240303f, 280.004395f }, 0.800000f, -1.570451f ); 
    instance.registerEObj( "sgpl_l1r1_boss2wall", 2001031, 4304071, 4, { 438.027588f, 69.382690f, 281.602203f }, 0.778198f, -1.570451f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Allaganteleporter_3", 2002809, 3445284, 4, { 115.688499f, 65.110123f, 280.018311f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_7", 2002813, 4199883, 4, { 253.669495f, 51.066391f, 244.695007f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2002814, 4199882, 4, { 253.676102f, 51.066399f, 279.965607f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2002815, 4199881, 4, { 253.683899f, 51.066360f, 315.213013f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2002816, 4199880, 4, { 213.707596f, 51.052799f, 244.895493f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2002817, 4199878, 4, { 213.688202f, 51.052799f, 280.125214f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2002818, 4199879, 4, { 213.723404f, 51.052799f, 315.105286f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Allaganteleporter_4", 2002810, 3974166, 4, { 349.215515f, 60.567490f, 268.536591f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut_1", 2002805, 0, 4, { 455.122894f, 66.249268f, 279.987701f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2001030, 4199894, 4, { 264.739899f, 50.679981f, 279.921509f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_l1r1_boss3wall", 2001033, 4305031, 4, { -110.210899f, 44.083248f, -116.227997f }, 0.381470f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_14", 2001034, 0, 4, { -110.254898f, 44.168098f, -111.387901f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2001035, 4317566, 4, { -110.054497f, 46.072929f, -214.578705f }, 0.400000f, 0.000000f ); 
    instance.registerEObj( "sgpl_l1r1_boss3wall_1", 2001036, 4305191, 4, { -111.224899f, 67.886620f, -344.147797f }, 0.400000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_16", 2001037, 0, 4, { -109.930298f, 67.892403f, -338.731415f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Energytowerconsole", 2001038, 0, 4, { -85.032784f, 70.241432f, -343.493713f }, 0.800000f, 1.570451f ); 
    instance.registerEObj( "Energytowerconsole_1", 2001039, 0, 4, { -85.044861f, 70.240898f, -393.307587f }, 0.800000f, 0.000000f ); 
    instance.registerEObj( "Energytowerconsole_2", 2001040, 0, 4, { -134.983994f, 70.240898f, -343.431213f }, 0.800000f, 0.000000f ); 
    instance.registerEObj( "Energytowerconsole_3", 2001041, 0, 4, { -134.925201f, 70.240898f, -393.378296f }, 0.800000f, -1.570451f ); 
    instance.registerEObj( "Allaganteleporter_5", 2002811, 3445283, 4, { -117.500000f, 39.417461f, -60.409302f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2002819, 4317548, 4, { -109.942200f, 44.168140f, -140.697403f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2002820, 4317564, 4, { -109.933800f, 44.168140f, -190.218903f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Allaganteleporter_6", 2002812, 3974167, 4, { -117.461098f, 57.435680f, -288.075104f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut_2", 2002806, 0, 4, { -109.976601f, 68.215019f, -378.115906f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2002821, 4407451, 4, { -110.134598f, 68.248489f, -367.669708f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Allaganteleporter_7", 2002822, 4322323, 4, { -123.763496f, 650.608582f, 254.596695f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_l1r1_boss4wall", 2001042, 4491496, 4, { -110.122498f, 650.015808f, 227.968597f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_20", 2001043, 0, 4, { -110.052299f, 650.020020f, 227.514893f }, 0.800000f, 0.000048f ); 
    instance.registerEObj( "unknown_21", 2001044, 4497411, 4, { -109.941299f, 650.720886f, 194.445694f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_22", 2002823, 4101871, 4, { -86.638451f, 650.731018f, 191.568298f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2002824, 4101872, 4, { -109.887199f, 650.970886f, 207.029099f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2002825, 4101873, 4, { -132.905304f, 650.731018f, 191.279907f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2002826, 0, 4, { -78.160004f, 649.940125f, 206.024597f }, 0.800000f, -0.634151f ); 
    instance.registerEObj( "unknown_26", 2002832, 0, 4, { -85.569000f, 649.940125f, 213.420593f }, 0.800000f, -0.911137f ); 
    instance.registerEObj( "unknown_27", 2002833, 0, 4, { -94.658401f, 649.940125f, 218.672806f }, 0.800000f, -1.177247f ); 
    instance.registerEObj( "unknown_28", 2002834, 0, 4, { -125.350403f, 649.940125f, 218.672806f }, 0.800000f, -1.153363f ); 
    instance.registerEObj( "unknown_29", 2002835, 0, 4, { -134.429901f, 649.940125f, 213.420593f }, 0.800000f, -0.918754f ); 
    instance.registerEObj( "unknown_30", 2002836, 0, 4, { -141.827698f, 649.940125f, 206.024597f }, 0.800000f, -0.639576f ); 
    instance.registerEObj( "unknown_31", 2002837, 4478584, 4, { -89.563782f, 650.019226f, 209.632706f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_32", 2002838, 4478586, 4, { -131.352798f, 650.019226f, 210.327194f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -110.009903f, 650.972229f, 157.832199f }, 0.793408f, 0.000048f ); 
    instance.registerEObj( "unknown_33", 2001029, 4499125, 4, { -109.987602f, 650.731018f, 181.576202f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheLabyrinthoftheAncients );