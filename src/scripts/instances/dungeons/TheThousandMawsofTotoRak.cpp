#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheThousandMawsofTotoRak :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheThousandMawsofTotoRak() :
    Sapphire::ScriptAPI::InstanceContentScript( 1 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2000404, 0, 4, { 216.937500f, -35.568851f, -142.076797f }, 0.961304f, 0.000144f ); 
    instance.registerEObj( "unknown_1", 2000133, 0, 4, { 185.564896f, -34.195511f, -144.640305f }, 0.900235f, 0.000336f ); 
    instance.registerEObj( "Exit", 2000683, 0, 4, { 237.565506f, -38.900299f, -144.195099f }, 1.000000f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2000041, 3879345, 4, { 191.261795f, -36.122822f, -143.910904f }, 1.267374f, -1.570451f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2000040, 0, 4, { 191.150696f, -36.117340f, -144.592300f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_3", 2001005, 0, 4, { 188.864594f, -35.987011f, -144.216095f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_f1r1_subboss1line", 2000131, 4126014, 4, { -117.593002f, -4.171226f, 107.608299f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_f1r1_subboss2line", 2000132, 4127292, 4, { -76.504066f, -8.171217f, -41.161350f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_f1r1_subboss1wall", 2000137, 4127387, 4, { -119.798599f, -4.165526f, 104.508904f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_f1r1_subboss2wall", 2000138, 4127414, 4, { -78.310173f, -8.133030f, -44.002850f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_f1r1_bossplusfloor", 2001152, 4374098, 4, { 197.405899f, -39.475101f, -147.966705f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Waterstainednote", 2000093, 0, 4, { -241.596100f, 4.936373f, -72.770317f }, 0.930753f, 0.000240f ); 
    instance.registerEObj( "Waterstainednote_1", 2000094, 0, 4, { -211.121002f, 2.082635f, -67.117737f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "Waterstainednote_2", 2000095, 0, 4, { -204.427002f, -1.617569f, 21.831829f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Waterstainednote_3", 2000096, 0, 4, { -149.074097f, -2.569309f, 101.795403f }, 0.930753f, 0.000240f ); 
    instance.registerEObj( "Magitekphotocell", 2000100, 0, 4, { -202.105804f, 0.318934f, -79.179108f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "Magitekphotocell_1", 2000101, 0, 4, { -221.659195f, -4.425579f, 54.985451f }, 0.869717f, 0.000432f ); 
    instance.registerEObj( "Magitekphotocell_2", 2000102, 0, 4, { -204.699799f, -4.926546f, 88.822723f }, 0.900235f, 0.000336f ); 
    instance.registerEObj( "Magitekphotocell_3", 2000103, 0, 4, { -104.023300f, -3.463795f, 104.075897f }, 0.839199f, 0.000527f ); 
    instance.registerEObj( "Magitekterminal", 2000116, 0, 4, { -112.013199f, -4.132327f, 112.031403f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2000117, 1699196, 4, { -95.990372f, -4.125101f, 111.985901f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "Magitekterminal_1", 2000118, 0, 4, { -80.026077f, -8.132326f, -47.971760f }, 0.961271f, 0.000144f ); 
    instance.registerEObj( "unknown_5", 2000121, 1699201, 4, { -95.538803f, -8.133920f, -48.020191f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "Accusationchamberdoor", 2000384, 3302267, 4, { -207.996994f, 0.110343f, -95.749359f }, 0.961271f, 0.000144f ); 
    instance.registerEObj( "Abacinationchamberdoor", 2000385, 3302270, 4, { 96.210892f, -19.927860f, -112.002098f }, 0.961271f, 0.000144f ); 
    instance.registerEObj( "unknown_6", 2000389, 3302276, 4, { -223.993698f, 2.170142f, -111.314598f }, 0.900235f, 0.000336f ); 
    instance.registerEObj( "unknown_7", 2000390, 3302281, 4, { 15.396310f, -12.161490f, -31.967699f }, 0.961271f, 0.000144f ); 
    instance.registerEObj( "unknown_8", 2000391, 3302277, 4, { -111.986000f, -11.694670f, -63.677799f }, 0.961271f, 0.000144f ); 
    instance.registerEObj( "unknown_9", 2000392, 3302279, 4, { -54.326931f, -12.619540f, -135.517899f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2000393, 3302283, 4, { 127.918297f, -24.124969f, -112.616798f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2000397, 3302282, 4, { -66.330208f, -8.057444f, -48.020191f }, 0.961271f, 0.000144f ); 
    instance.registerEObj( "unknown_12", 2000398, 3302278, 4, { -103.188698f, -12.587360f, -137.701004f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2000399, 3302280, 4, { -7.119315f, -12.783910f, -137.865402f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2000400, 3302275, 4, { 175.723206f, -34.137970f, -140.074005f }, 0.930753f, 0.000240f ); 
    instance.registerEObj( "Magitekphotocell_4", 2000104, 0, 4, { -130.358597f, -8.977930f, -71.240982f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_15", 2000111, 0, 4, { -221.057495f, -0.076355f, -113.847603f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_16", 2000112, 0, 4, { 18.393040f, -12.250300f, -28.183680f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2000113, 0, 4, { -109.852501f, -11.441870f, -58.962391f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2000114, 0, 4, { -55.111301f, -12.534730f, -140.141006f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2000115, 0, 4, { 121.910698f, -23.325809f, -110.515297f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekphotocell_5", 2000105, 0, 4, { -130.724106f, -9.414856f, -68.131592f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekphotocell_6", 2000106, 0, 4, { -130.418900f, -9.567444f, -67.856873f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekphotocell_7", 2000107, 0, 4, { -130.101807f, -9.739193f, -67.526657f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "Magitekphotocell_8", 2000107, 0, 4, { -129.796707f, -9.914070f, -67.221481f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "Magitekphotocell_9", 2000039, 0, 4, { -73.754570f, -6.333896f, 21.536640f }, 0.991789f, 0.000048f ); 
    instance.registerEObj( "Magitekphotocell_10", 2000108, 0, 4, { -186.655807f, -0.160111f, -10.531350f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekphotocell_11", 2000109, 0, 4, { -143.922195f, 0.079653f, 1.801933f }, 0.961271f, 0.000144f ); 
    instance.registerEObj( "Magitekphotocell_12", 2000110, 0, 4, { -233.539398f, -0.167908f, -103.013702f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -311.485504f, 9.496978f, -76.989082f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 4127435, 5, { -322.238495f, 11.991770f, -78.470192f }, 0.991760f, 0.000048f ); 
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

EXPOSE_SCRIPT( TheThousandMawsofTotoRak );