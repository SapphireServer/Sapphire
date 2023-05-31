#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ThePuppetsBunker : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThePuppetsBunker() : Sapphire::ScriptAPI::InstanceContentScript( 30096 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Accesspoint", 2011120, 8384913, 4, { -355.043488f, 104.007004f, 367.216614f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Accesspoint_1", 2011121, 8384914, 4, { -231.091599f, 2.691960f, 58.272179f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Accesspoint_2", 2011122, 8384915, 4, { -211.289703f, -126.839104f, -57.984219f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Accesspoint_3", 2011123, 8387039, 4, { -366.265594f, -241.271698f, -338.876709f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Accesspoint_4", 2011124, 8384916, 4, { 207.413406f, -500.022888f, -140.027496f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Accesspoint_5", 2011125, 8384917, 4, { 189.700500f, -500.000000f, -507.957306f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 8350690, 5, { -362.319489f, 104.035400f, 366.992188f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 200.000000f, -480.033600f, -735.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2007457, 8381849, 4, { -366.244507f, -249.746597f, -276.232788f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 8385557, 4, { -294.725006f, -204.706406f, -335.678802f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4r2_a2_wall1", 2007457, 8406582, 4, { -230.481094f, -5.125448f, 13.695740f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -271.882690f, 69.714706f, 269.053802f }, 1.000000f, 0.733038f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8351896, 4, { -272.073608f, 69.878899f, 269.653992f }, 1.000000f, 0.733038f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002872, 8379563, 4, { -230.636505f, 30.000000f, 147.056793f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2002872, 8351915, 4, { -230.000000f, -114.943497f, -117.158600f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002872, 8359211, 4, { -230.636398f, -150.567307f, -214.202103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007791, 0, 4, { -230.000000f, -114.943497f, -117.158600f }, 1.300000f, -0.000000f); 
    instance.registerEObj( "unknown_6", 2002735, 0, 4, { -366.048706f, -249.746597f, -255.638901f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8352113, 4, { -366.051086f, -249.746704f, -254.671707f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_7", 2002872, 8378985, 4, { 194.811905f, -500.000000f, -117.850700f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8371387, 4, { 199.955093f, -500.000000f, -105.403702f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 8371386, 4, { 204.939194f, -500.000000f, -102.878899f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 8371385, 4, { 204.970703f, -500.000000f, -97.184334f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 8371384, 4, { 199.938797f, -500.000000f, -94.318733f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 8371389, 4, { 195.124893f, -500.000000f, -97.370781f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2007457, 8371388, 4, { 195.265106f, -500.000000f, -102.838997f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_14", 2007457, 8340396, 4, { 199.935501f, -496.868500f, -99.799042f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_15", 2007457, 8508855, 4, { 196.410507f, -500.000000f, -126.389702f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_16", 2002735, 0, 4, { 200.000000f, -480.000000f, -660.000000f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 8352128, 4, { 200.000000f, -480.000000f, -660.000000f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_17", 2011245, 0, 4, { 172.000000f, -480.000092f, -695.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_18", 2011246, 0, 4, { 166.000000f, -480.000092f, -697.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4r2_b2010", 2007457, 8436969, 4, { 186.000000f, -480.000092f, -707.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgpl_w_lvd_collison_only", 2002618, 8513160, 4, { -230.526901f, -3.899055f, 8.806126f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_19", 2002735, 0, 4, { -230.000000f, -3.720000f, 10.050000f }, 1.350000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8352136, 4, { -230.000000f, -3.720000f, 11.035000f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_20", 2002872, 8353120, 4, { -227.933105f, -30.000000f, -21.932159f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_21", 2002735, 0, 4, { 200.000000f, -499.830414f, -170.003098f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 8352150, 4, { 199.408493f, -499.999908f, -168.180099f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_22", 2002872, 0, 4, { 196.320999f, -501.827606f, -261.783295f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_23", 2007457, 8367959, 4, { 199.088104f, -501.000000f, -264.099396f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_24", 2007457, 8367960, 4, { 198.916397f, -501.000000f, -364.571808f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_25", 2007457, 8367961, 4, { 197.601196f, -501.000000f, -464.728485f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4r2_a4_bcol2", 2007457, 8384869, 4, { 198.000000f, -500.000000f, -244.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4r2_a4_bcol2_1", 2007457, 8384867, 4, { 198.000000f, -500.000000f, -344.378204f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4r2_a4_bcol2_2", 2007457, 8384868, 4, { 198.000000f, -500.000000f, -463.191406f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4r2_a4_bcol1", 2007457, 8435681, 4, { 200.000000f, -500.000000f, -404.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4r2_a4_bcol1_1", 2007457, 8435682, 4, { 200.000000f, -500.000000f, -434.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_26", 2007457, 8461824, 4, { 200.213593f, -500.000000f, -212.534393f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_27", 2007457, 8461825, 4, { 200.000000f, -500.000000f, -311.829407f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_28", 2007457, 8461826, 4, { 200.061005f, -500.000000f, -400.077393f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "???", 2011108, 0, 4, { -363.341614f, 104.009499f, 375.696686f }, 0.991760f, 0.075571f); 
    instance.registerEObj( "???_1", 2011109, 0, 4, { -254.184906f, 30.000000f, 178.040802f }, 0.991760f, -1.089808f); 
    instance.registerEObj( "???_2", 2011110, 0, 4, { -203.398895f, -150.500595f, -187.369995f }, 0.991760f, 1.062461f); 
    instance.registerEObj( "???_3", 2011111, 0, 4, { -227.326401f, -149.051498f, -320.743713f }, 0.991760f, 1.343656f); 
    instance.registerEObj( "???_4", 2011112, 0, 4, { -366.457794f, -249.774994f, -318.898285f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "???_5", 2011113, 0, 4, { -372.846985f, -244.770004f, -303.171692f }, 0.991760f, 0.548263f); 
    instance.registerEObj( "???_6", 2011114, 0, 4, { -345.151001f, -244.751999f, -321.402100f }, 0.991760f, 1.035487f); 
    instance.registerEObj( "???_7", 2011115, 0, 4, { -386.224091f, -241.317993f, -314.976196f }, 0.991760f, -1.570796f); 
    instance.registerEObj( "???_8", 2011116, 0, 4, { 193.908905f, -500.000000f, -89.723251f }, 0.991760f, 0.446006f); 
    instance.registerEObj( "???_9", 2011117, 0, 4, { 253.131805f, -500.022888f, -484.397614f }, 0.991760f, 1.570796f); 
    instance.registerEObj( "???_10", 2011118, 0, 4, { -295.887787f, -203.997894f, -320.973511f }, 0.991760f, 1.570796f); 
    instance.registerEObj( "ExittoKholusia", 2011155, 0, 4, { -383.780396f, 102.904198f, 389.139191f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Bunkerentrance", 2011234, 0, 4, { -230.103302f, -2.584678f, 11.621810f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shipentry", 2011269, 0, 4, { -366.483398f, -248.417603f, -285.670593f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination", 2011274, 0, 4, { -277.699005f, 69.927277f, 274.006195f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_1", 2011275, 0, 4, { -366.506500f, -241.317902f, -311.574005f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Passagetothebridge", 2011276, 0, 4, { 200.000000f, -478.457092f, -558.819702f }, 1.200000f, 0.000000f); 
    instance.registerEObj( "Entrancetothebridge", 2011440, 0, 4, { 200.000000f, -478.457092f, -558.819702f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Infiltrationpoint", 2011468, 0, 4, { -358.442688f, 106.392303f, 341.889587f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Indecipherabletomes", 2011458, 0, 4, { -295.155304f, -203.936905f, -329.365997f }, 0.991760f, -1.076406f); 
    instance.registerEObj( "Unidentifiedmachineparts", 2011459, 0, 4, { 205.891495f, -500.022888f, -167.858398f }, 0.991760f, -1.105010f); 
    instance.registerEObj( "Heavycontainer", 2011477, 0, 4, { -233.569901f, 2.548157f, 49.637569f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Exittothemountains", 2011236, 0, 4, { -211.338394f, -126.792397f, -57.965511f }, 1.022339f, 1.570796f); 
    instance.registerEObj( "Exittothemountains_1", 2011237, 0, 4, { -366.467102f, -241.348602f, -339.062988f }, 1.051045f, -0.392699f); 
    instance.registerEObj( "Exittothemountains_2", 2011238, 0, 4, { 189.318604f, -500.022888f, -508.110199f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Exittothemountains_3", 2011239, 0, 4, { -230.769699f, 2.691949f, 58.217270f }, 1.200000f, 0.947112f); 
    instance.registerEObj( "Exittothemountains_4", 2011235, 0, 4, { 207.604996f, -500.000000f, -140.007904f }, 1.000000f, 1.570451f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ThePuppetsBunker );