#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheDungeonsofLyheGhiah : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheDungeonsofLyheGhiah() : Sapphire::ScriptAPI::InstanceContentScript( 55006 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 7964004, 5, { -0.000001f, -40.032009f, 220.058899f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -5.397262f, -40.032009f, 214.389603f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4c1_b1658", 2007457, 7966223, 4, { 9.400000f, -40.000000f, 130.001007f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_1", 2007457, 7966221, 4, { -9.400000f, -40.000011f, 130.001007f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_2", 2007457, 7966222, 4, { 0.000000f, -40.000011f, 120.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -0.000010f, -40.004810f, 150.622498f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7964311, 4, { 0.000000f, -40.004810f, 153.622498f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Treasurecoffer", 2010410, 0, 4, { 0.000004f, -40.000000f, 130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1659", 2007457, 7966633, 4, { -1.999996f, -40.000000f, 130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1660", 2007457, 7966634, 4, { 2.000004f, -40.000000f, 130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "High", 2010422, 7964428, 4, { 1.000004f, -40.000000f, 135.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Low", 2010423, 7964429, 4, { 3.000004f, -40.000000f, 135.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4c1_b1658_3", 2007457, 7966231, 4, { 9.400000f, -0.000015f, 0.001036f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_4", 2007457, 7966229, 4, { -9.400000f, 0.000000f, 0.001024f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_5", 2007457, 7966230, 4, { 0.000000f, -0.000015f, -9.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -0.015351f, -0.004812f, 20.621849f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 7964321, 4, { -0.015176f, 0.000000f, 23.614929f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Treasurecoffer_1", 2010411, 0, 4, { 0.000004f, -0.000000f, 0.000031f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1659_1", 2007457, 7966636, 4, { -1.999982f, -0.000015f, -0.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1660_1", 2007457, 7966637, 4, { 2.000018f, -0.000015f, 0.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "High_1", 2010424, 7964439, 4, { 1.000018f, -0.000000f, 5.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Low_1", 2010425, 7964440, 4, { 3.000018f, 0.000015f, 5.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4c1_b1658_6", 2007457, 7966241, 4, { 9.400000f, 39.999908f, -129.998993f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_7", 2007457, 7966239, 4, { -9.400000f, 39.999908f, -129.998993f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_8", 2007457, 7966240, 4, { 0.000000f, 39.999931f, -139.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -0.015320f, 40.000000f, -109.385101f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7964326, 4, { 0.000000f, 40.000000f, -106.377502f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Treasurecoffer_2", 2010412, 0, 4, { 0.000004f, 40.000000f, -130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1659_2", 2007457, 7966639, 4, { -1.999969f, 39.999901f, -130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1660_2", 2007457, 7966640, 4, { 2.000031f, 39.999901f, -130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "High_2", 2010426, 7964446, 4, { 1.000032f, 39.999920f, -125.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Low_2", 2010427, 7964447, 4, { 3.000031f, 39.999939f, -125.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4c1_b1658_9", 2007457, 7966245, 4, { 9.400000f, 79.999924f, -259.998993f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_10", 2007457, 7966243, 4, { -9.400000f, 79.999939f, -259.998993f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_11", 2007457, 7966244, 4, { 0.000000f, 79.999939f, -269.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -0.015320f, 80.000000f, -239.385101f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 7964333, 4, { 0.000000f, 80.000000f, -236.377502f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Treasurecoffer_3", 2010413, 0, 4, { 0.000004f, 80.000000f, -260.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1659_3", 2007457, 7966641, 4, { -1.999956f, 79.999924f, -260.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1660_3", 2007457, 7966642, 4, { 2.000045f, 79.999924f, -260.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "High_3", 2010428, 7964452, 4, { 1.000046f, 79.999939f, -255.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Low_3", 2010429, 7964453, 4, { 3.000045f, 79.999939f, -255.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4c1_b1658_12", 2007457, 7966248, 4, { 9.400000f, 120.000000f, -389.998993f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_13", 2007457, 7966246, 4, { -9.400000f, 120.000000f, -389.998993f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "sgvf_n4c1_b1658_14", 2007457, 7966247, 4, { 0.000000f, 120.000000f, -399.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 120.000000f, -402.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { -0.015320f, 120.000000f, -369.385101f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 7964338, 4, { -0.000000f, 120.000000f, -369.377502f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b1659_4", 2007457, 7966643, 4, { -1.999942f, 120.000000f, -390.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1660_4", 2007457, 7966644, 4, { 2.000059f, 120.000000f, -390.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "High_4", 2010430, 7964458, 4, { 1.000059f, 120.000000f, -385.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Low_4", 2010431, 7964459, 4, { 3.000059f, 120.000000f, -385.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Elaborategate", 2010415, 7962642, 4, { 21.731409f, -39.963531f, 108.595299f }, 0.991760f, 0.977400f); 
    instance.registerEObj( "Elaborategate_1", 2010414, 7962641, 4, { -21.536320f, -39.963619f, 108.519096f }, 0.991760f, -0.977304f); 
    instance.registerEObj( "unknown_5", 2007457, 7962646, 4, { 23.464140f, -39.905399f, 106.765404f }, 0.991760f, 0.977400f); 
    instance.registerEObj( "unknown_6", 2007457, 7962645, 4, { -24.185551f, -39.905399f, 105.763100f }, 0.991760f, -0.977304f); 
    instance.registerEObj( "unknown_7", 2007457, 7965412, 4, { 0.000004f, -40.000000f, 130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 7945880, 4, { 0.000010f, -0.000000f, -0.000002f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Elaborategate_2", 2010417, 7930311, 4, { 21.638580f, 0.036586f, -21.527309f }, 0.991760f, 0.977496f); 
    instance.registerEObj( "Elaborategate_3", 2010416, 7966679, 4, { -21.651291f, 0.036197f, -21.359600f }, 0.991760f, -0.977304f); 
    instance.registerEObj( "unknown_9", 2007457, 7928470, 4, { 23.814819f, 0.094598f, -23.692810f }, 0.991760f, 0.977400f); 
    instance.registerEObj( "unknown_10", 2007457, 7928469, 4, { -23.036230f, 0.040430f, -22.720940f }, 0.991760f, -0.977304f); 
    instance.registerEObj( "unknown_11", 2007457, 7945881, 4, { 0.000000f, 39.999920f, -130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Elaborategate_4", 2010419, 7937564, 4, { 21.481951f, 40.037769f, -151.526901f }, 0.991760f, 0.977400f); 
    instance.registerEObj( "Elaborategate_5", 2010418, 7937563, 4, { -21.544411f, 40.038010f, -151.558807f }, 0.991760f, -0.977304f); 
    instance.registerEObj( "unknown_12", 2007457, 7937301, 4, { 23.842600f, 40.094601f, -153.755203f }, 0.991760f, 0.977400f); 
    instance.registerEObj( "unknown_13", 2007457, 7937295, 4, { -23.822081f, 40.094601f, -153.772507f }, 0.991760f, -0.977304f); 
    instance.registerEObj( "unknown_14", 2007457, 7965413, 4, { -0.000006f, 79.999947f, -260.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Elaborategate_6", 2010421, 7962468, 4, { 21.537201f, 80.037827f, -281.518402f }, 0.991760f, 0.977400f); 
    instance.registerEObj( "Elaborategate_7", 2010420, 7962467, 4, { -21.596790f, 80.037888f, -281.482208f }, 0.991760f, -0.977304f); 
    instance.registerEObj( "unknown_15", 2007457, 7962502, 4, { 23.629890f, 80.094566f, -283.563202f }, 0.991760f, 0.977400f); 
    instance.registerEObj( "unknown_16", 2007457, 7962504, 4, { -23.738070f, 80.094597f, -283.576813f }, 0.991760f, -0.977304f); 
    instance.registerEObj( "unknown_17", 2007457, 7945882, 4, { 0.000006f, 120.000000f, -390.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheDungeonsofLyheGhiah );