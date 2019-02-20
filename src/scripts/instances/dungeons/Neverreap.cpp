#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Neverreap :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Neverreap() :
    Sapphire::ScriptAPI::InstanceContentScript( 33 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Vanutotem", 2005373, 0, 4, { 171.495407f, 64.000000f, -17.861130f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_1", 2005374, 0, 4, { 172.963303f, 64.000000f, -17.254971f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_2", 2005375, 0, 4, { 173.628693f, 64.000000f, -16.836420f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_3", 2005376, 0, 4, { 173.837097f, 64.000000f, -15.707030f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_4", 2005377, 0, 4, { 172.736298f, 64.000000f, -15.517540f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_5", 2005378, 0, 4, { 172.030807f, 64.000000f, -15.895150f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_6", 2005379, 0, 4, { 171.188904f, 64.000000f, -16.423241f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_7", 2005380, 0, 4, { 170.423996f, 64.000000f, -18.803040f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_8", 2005381, 0, 4, { 169.871201f, 64.000000f, -17.785959f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_9", 2005382, 0, 4, { 170.450607f, 64.000000f, -15.978460f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_10", 2005383, 0, 4, { 169.593307f, 64.000000f, -15.827410f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vanutotem_11", 2005384, 0, 4, { 170.206100f, 64.000000f, -15.102260f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Cloudaltar", 2005130, 5786938, 4, { -160.917892f, 5.000000f, 291.800598f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2d2_b0636", 2005135, 5887646, 4, { -160.814896f, 4.989685f, 291.432007f }, 0.991760f, 0.000048f ); 
    // States -> bef_offer (id: 2) aft_offer (id: 3) bef2aft (id: 4) 
    instance.registerEObj( "Cloudaltar_1", 2005131, 5786940, 4, { -87.421448f, 21.000000f, 290.602692f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2d2_b0636_1", 2005136, 5887670, 4, { -97.348267f, 21.000000f, 290.468292f }, 1.000000f, 0.000000f ); 
    // States -> bef_offer (id: 2) aft_offer (id: 3) bef2aft (id: 4) 
    instance.registerEObj( "sgvf_a2d2_b0636_2", 2005137, 5887709, 4, { -1.889378f, 43.351429f, 215.919601f }, 1.000000f, 0.000000f ); 
    // States -> bef_offer (id: 2) aft_offer (id: 3) bef2aft (id: 4) 
    instance.registerEObj( "Cloudaltar_2", 2005132, 5786943, 4, { -4.570463f, 44.541019f, 216.505707f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 5778078, 4, { 74.175919f, 38.000000f, 213.378998f }, 1.000000f, 0.179771f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Cloudaltar_3", 2005133, 5786946, 4, { 77.225830f, 37.979610f, 211.596802f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 5789280, 4, { -5.153300f, 43.220901f, 215.814102f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002587, 0, 4, { -5.153300f, 43.138199f, 214.261093f }, 1.000000f, 1.561701f ); 
    instance.registerEObj( "sgvf_a2d2_b0636_3", 2005137, 5887710, 4, { 79.964493f, 38.000000f, 209.654800f }, 1.000000f, 0.000000f ); 
    // States -> bef_offer (id: 2) aft_offer (id: 3) bef2aft (id: 4) 
    instance.registerEObj( "unknown_1", 2005139, 5606925, 4, { 132.122696f, 55.455528f, 135.050995f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2005140, 5606936, 4, { 142.889496f, 67.000000f, 67.840523f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 5777608, 4, { 165.085007f, 63.500000f, 10.671380f }, 1.000000f, 0.065608f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 5777614, 4, { 178.430206f, 64.000000f, -23.500389f }, 1.000000f, 0.154718f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 163.308899f, 63.926491f, 9.173799f }, 1.000000f, 0.342174f ); 
    instance.registerEObj( "unknown_4", 2005142, 0, 4, { 177.194199f, 60.250000f, -155.280502f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 172.014893f, 58.670898f, -358.327606f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2002872, 5615523, 4, { 175.494003f, 59.281250f, -305.348297f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2002587, 0, 4, { 175.127701f, 59.281250f, -310.170197f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Cloudaltar_4", 2005134, 5786958, 4, { 164.310806f, 60.349369f, -127.550201f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_a2d2_b0711", 2005143, 5900091, 4, { 164.190903f, 61.358318f, -219.399506f }, 1.000000f, 0.000000f ); 
    // States -> bub_init (id: 1) bub_loop (id: 2) 
    instance.registerEObj( "sgvf_a2d2_b0642", 2005146, 5894450, 4, { 175.280396f, 59.281250f, -309.102112f }, 0.991760f, 0.000048f ); 
    // States -> wind_on (id: 2) wind_off (id: 3) 
    instance.registerEObj( "sgvf_a2d2_b0645", 2005144, 5893679, 4, { 158.342804f, 60.440922f, -191.393906f }, 0.991760f, 0.000048f ); 
    // States -> init (id: 2) loop2init (id: 3) loop (id: 4) init2loop (id: 5) 
    instance.registerEObj( "sgvf_a2d2_b0645_1", 2005145, 5893776, 4, { 162.635193f, 59.999939f, -271.153412f }, 1.000000f, 0.000000f ); 
    // States -> init (id: 2) loop2init (id: 3) loop (id: 4) init2loop (id: 5) 
    instance.registerEObj( "unknown_6", 2005141, 5764461, 4, { 165.941803f, 60.440899f, -205.985107f }, 1.000000f, 0.000047f ); 
    instance.registerEObj( "Entrance", 2000182, 5614672, 5, { -195.491302f, -0.022185f, 305.059296f }, 1.000000f, -0.128295f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -179.874603f, 2.417616f, 306.529602f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Neverreap );