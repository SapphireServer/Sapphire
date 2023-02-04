#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Neverreap : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Neverreap() : Sapphire::ScriptAPI::InstanceContentScript( 33 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "Vanutotem", 2005373, 0, 5836439, 4, { 171.495407f, 64.000000f, -17.861130f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_1", 2005374, 0, 5836446, 4, { 172.963303f, 64.000000f, -17.254971f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_2", 2005375, 0, 5836447, 4, { 173.628693f, 64.000000f, -16.836420f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_3", 2005376, 0, 5836448, 4, { 173.837097f, 64.000000f, -15.707030f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_4", 2005377, 0, 5836449, 4, { 172.736298f, 64.000000f, -15.517540f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_5", 2005378, 0, 5836450, 4, { 172.030807f, 64.000000f, -15.895150f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_6", 2005379, 0, 5836451, 4, { 171.188904f, 64.000000f, -16.423241f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_7", 2005380, 0, 5836452, 4, { 170.423996f, 64.000000f, -18.803040f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_8", 2005381, 0, 5836453, 4, { 169.871201f, 64.000000f, -17.785959f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_9", 2005382, 0, 5836454, 4, { 170.450607f, 64.000000f, -15.978460f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_10", 2005383, 0, 5836455, 4, { 169.593307f, 64.000000f, -15.827410f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Vanutotem_11", 2005384, 0, 5836456, 4, { 170.206100f, 64.000000f, -15.102260f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cloudaltar", 2005130, 5786938, 5615426, 4, { -160.917892f, 5.000000f, 291.800598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_a2d2_b0636", 2005135, 5887646, 5615427, 4, { -160.814896f, 4.989685f, 291.432007f }, 0.991760f, 0.000048f, 0); 
    // States -> bef_offer (id: 2) aft_offer (id: 3) bef2aft (id: 4) 
    instance.addEObj( "Cloudaltar_1", 2005131, 5786940, 5615429, 4, { -87.421448f, 21.000000f, 290.602692f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_a2d2_b0636_1", 2005136, 5887670, 5615430, 4, { -97.348267f, 21.000000f, 290.468292f }, 1.000000f, 0.000000f, 0); 
    // States -> bef_offer (id: 2) aft_offer (id: 3) bef2aft (id: 4) 
    instance.addEObj( "sgvf_a2d2_b0636_2", 2005137, 5887709, 5615442, 4, { -1.889378f, 43.351429f, 215.919601f }, 1.000000f, 0.000000f, 0); 
    // States -> bef_offer (id: 2) aft_offer (id: 3) bef2aft (id: 4) 
    instance.addEObj( "Cloudaltar_2", 2005132, 5786943, 5615443, 4, { -4.570463f, 44.541019f, 216.505707f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5778078, 5778079, 4, { 74.175919f, 38.000000f, 213.378998f }, 1.000000f, 0.179771f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Cloudaltar_3", 2005133, 5786946, 5778043, 4, { 77.225830f, 37.979610f, 211.596802f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 5789280, 5789281, 4, { -5.153300f, 43.220901f, 215.814102f }, 1.000000f, -0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_0", 2002587, 0, 5789282, 4, { -5.153300f, 43.138199f, 214.261093f }, 1.000000f, 1.561701f, 0); 
    instance.addEObj( "sgvf_a2d2_b0636_3", 2005137, 5887710, 5778042, 4, { 79.964493f, 38.000000f, 209.654800f }, 1.000000f, 0.000000f, 0); 
    // States -> bef_offer (id: 2) aft_offer (id: 3) bef2aft (id: 4) 
    instance.addEObj( "unknown_1", 2005139, 5606925, 5615464, 4, { 132.122696f, 55.455528f, 135.050995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2005140, 5606936, 5615466, 4, { 142.889496f, 67.000000f, 67.840523f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5777608, 5777606, 4, { 165.085007f, 63.500000f, 10.671380f }, 1.000000f, 0.065608f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 5777614, 5777616, 4, { 178.430206f, 64.000000f, -23.500389f }, 1.000000f, 0.154718f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_3", 2002735, 0, 5777607, 4, { 163.308899f, 63.926491f, 9.173799f }, 1.000000f, 0.342174f, 0); 
    instance.addEObj( "unknown_4", 2005141, 5764461, 5615471, 4, { 165.941803f, 60.440922f, -205.985107f }, 1.000000f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2005142, 0, 5615473, 4, { 177.194199f, 60.250000f, -155.280502f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 5615515, 4, { 172.014893f, 58.670898f, -358.327606f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250", 2002872, 5615523, 5615520, 4, { 175.521805f, 59.299980f, -305.342804f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_6", 2002587, 0, 5615519, 4, { 175.153702f, 59.299980f, -310.144592f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cloudaltar_4", 2005134, 5786958, 5778045, 4, { 164.310806f, 60.349369f, -127.550201f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_a2d2_b0711", 2005143, 5900091, 5900092, 4, { 164.190903f, 61.358318f, -219.399506f }, 1.000000f, 0.000000f, 0); 
    // States -> bub_init (id: 1) bub_loop (id: 2) 
    instance.addEObj( "sgvf_a2d2_b0642", 2005146, 5894450, 5615485, 4, { 175.280396f, 59.281250f, -309.102112f }, 0.991760f, 0.000048f, 0); 
    // States -> wind_on (id: 2) wind_off (id: 3) 
    instance.addEObj( "sgvf_a2d2_b0645", 2005144, 5893679, 5615482, 4, { 158.342804f, 60.440922f, -191.393906f }, 0.991760f, 0.000048f, 0); 
    // States -> init (id: 2) loop2init (id: 3) loop (id: 4) init2loop (id: 5) 
    instance.addEObj( "sgvf_a2d2_b0645_1", 2005145, 5893776, 5615484, 4, { 162.635193f, 59.999939f, -271.153412f }, 1.000000f, 0.000000f, 0); 
    // States -> init (id: 2) loop2init (id: 3) loop (id: 4) init2loop (id: 5) 
    instance.addEObj( "Entrance", 2000182, 5614672, 5614674, 5, { -195.491302f, -0.022185f, 305.059296f }, 1.000000f, -0.128295f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 5615368, 4, { -179.874603f, 2.417616f, 306.529602f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Neverreap );