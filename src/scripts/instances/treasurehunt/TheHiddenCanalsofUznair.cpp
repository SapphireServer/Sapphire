#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheHiddenCanalsofUznair :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheHiddenCanalsofUznair() :
    Sapphire::ScriptAPI::InstanceContentScript( 55003 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Sluicegate", 2008671, 6880327, 4, { 0.568258f, 100.300003f, 274.168488f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_1", 2008672, 6880319, 4, { 0.269765f, 50.299999f, 154.680405f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2007457, 6879916, 4, { -1.092401f, 100.300003f, 275.638214f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 6879843, 4, { -1.524224f, 50.299999f, 155.176193f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_2", 2008673, 6880331, 4, { 0.313768f, 0.272164f, 33.151051f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_3", 2008674, 6880926, 4, { -0.058978f, -49.700001f, -85.039810f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_4", 2008675, 6880353, 4, { -0.094499f, -99.699997f, -204.539307f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_5", 2008676, 6880364, 4, { -0.132713f, -149.699997f, -325.173187f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 6878453, 4, { -0.983721f, 0.299997f, 33.876339f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 6878661, 4, { -1.446076f, -49.700001f, -85.301064f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 6878563, 4, { -1.907748f, -99.699997f, -205.542297f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 6874398, 4, { 0.861505f, -149.699997f, -323.648102f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "High", 2008960, 7005817, 4, { 0.995313f, 100.400002f, 303.008911f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Low", 2008961, 7005818, 4, { 2.977269f, 100.400002f, 303.015686f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "High_1", 2008962, 7005819, 4, { 1.004384f, 50.369999f, 183.038193f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Low_1", 2008963, 7005820, 4, { 3.018387f, 50.400009f, 183.009003f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "High_2", 2008964, 7005821, 4, { 1.013391f, 0.381469f, 63.020931f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Low_2", 2008965, 7005822, 4, { 3.000382f, 0.400042f, 63.011879f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "High_3", 2008966, 7005823, 4, { 0.999980f, -49.628479f, -56.984692f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Low_3", 2008967, 7005824, 4, { 2.994332f, -49.599289f, -56.969849f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "High_4", 2008968, 7005825, 4, { 0.976013f, -99.617447f, -176.984695f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Low_4", 2008969, 7005826, 4, { 3.016492f, -99.599678f, -176.996704f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "High_5", 2008970, 7005827, 4, { 1.002942f, -149.605804f, -296.980713f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Low_5", 2008971, 7005828, 4, { 3.024055f, -149.599503f, -297.002808f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "High_6", 2008972, 7005829, 4, { 1.005902f, -199.603302f, -416.980988f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Low_6", 2008973, 7005830, 4, { 3.005575f, -199.600403f, -416.998596f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1231", 2007457, 6996412, 4, { -4.068258f, 100.300003f, 294.718903f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1232", 2007457, 6996413, 4, { 3.038667f, 100.300003f, 294.803009f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1231_1", 2007457, 6996415, 4, { -4.038448f, 50.400009f, 176.206604f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1232_1", 2007457, 6996416, 4, { 3.159257f, 50.400009f, 176.996399f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1231_2", 2007457, 6996417, 4, { -5.237320f, 0.309626f, 53.443291f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1232_2", 2007457, 6996418, 4, { 1.048808f, 0.300000f, 53.069832f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1231_3", 2007457, 6996420, 4, { -4.622195f, -49.700001f, -65.730782f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1232_3", 2007457, 6996419, 4, { 3.246223f, -49.700001f, -66.129990f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1231_4", 2007457, 6996421, 4, { -4.211632f, -99.699997f, -185.489395f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1232_4", 2007457, 6996422, 4, { 3.121258f, -99.697990f, -185.125397f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1231_5", 2007457, 6996424, 4, { -3.555968f, -149.663605f, -304.656311f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1232_5", 2007457, 6996423, 4, { 2.999705f, -149.599503f, -304.547394f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1231_6", 2007457, 6996425, 4, { -3.452516f, -199.699997f, -425.304108f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1232_6", 2007457, 6996426, 4, { 3.398586f, -199.699997f, -425.457886f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6904134, 5, { 2.648753f, 150.300003f, 421.065491f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 4.024228f, 150.300003f, 411.372498f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2002735, 0, 4, { 0.000000f, 100.300003f, 317.628296f }, 1.200000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6904820, 4, { 0.778198f, 99.992310f, 319.020294f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Sluicegate_6", 2008593, 6880322, 4, { -17.906931f, 99.999687f, 282.242706f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_7", 2008594, 6880329, 4, { 18.638870f, 99.999748f, 281.840912f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer", 2008566, 0, 4, { 0.000000f, 100.400002f, 300.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 6837839, 4, { -24.428419f, 99.999702f, 299.505890f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 6837819, 4, { 3.431039f, 99.999771f, 274.684387f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 6837820, 4, { 24.678801f, 99.999672f, 300.109589f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 6837843, 4, { 1.030507f, 100.399696f, 298.205200f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 6879918, 4, { -19.918140f, 99.999687f, 285.122803f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 6879917, 4, { 16.073009f, 99.999748f, 280.430511f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2002735, 0, 4, { -0.000000f, 50.299999f, 197.665695f }, 1.200000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6908678, 4, { 0.647792f, 49.999809f, 199.196106f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Sluicegate_8", 2008595, 6880321, 4, { -18.062990f, 49.999699f, 162.414703f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_9", 2008596, 6880320, 4, { 18.482809f, 49.999790f, 162.012894f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_1", 2008567, 0, 4, { 0.000000f, 50.399700f, 180.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007457, 6859376, 4, { -24.584480f, 49.999680f, 179.677902f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007457, 6859374, 4, { 3.274982f, 49.999809f, 154.856400f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2007457, 6859375, 4, { 24.522739f, 49.999729f, 180.281601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2007457, 6859377, 4, { 0.874450f, 50.399719f, 178.377197f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2007457, 6879845, 4, { -20.074200f, 49.999729f, 165.294800f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2007457, 6879844, 4, { 15.916950f, 49.999790f, 160.602493f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2002735, 0, 4, { -0.000000f, 0.300000f, 77.670822f }, 1.200000f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6908750, 4, { 0.647792f, -0.000183f, 79.265778f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Sluicegate_10", 2008597, 6880336, 4, { -18.062990f, -0.000261f, 42.484371f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_11", 2008598, 6880333, 4, { 18.482809f, -0.000181f, 42.082581f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_2", 2008568, 0, 4, { 0.000000f, 0.399994f, 60.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2007457, 6859445, 4, { -24.584480f, -0.000300f, 59.747551f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2007457, 6859443, 4, { 3.274982f, -0.000159f, 34.926048f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2007457, 6859444, 4, { 24.522739f, -0.000267f, 60.351250f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2007457, 6880919, 4, { 0.874450f, 0.399750f, 58.446869f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2007457, 6878455, 4, { -20.074200f, -0.000246f, 45.364471f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2007457, 6878454, 4, { 15.916950f, -0.000182f, 40.672180f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_27", 2002735, 0, 4, { -0.000000f, -49.700001f, -42.294621f }, 1.200000f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6910488, 4, { 0.647793f, -49.999901f, -40.657509f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Sluicegate_12", 2008599, 6880352, 4, { -18.062990f, -49.999981f, -77.438744f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_13", 2008600, 6880349, 4, { 18.478640f, -50.003849f, -77.866821f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Treasurecoffer_3", 2008569, 0, 4, { 0.000000f, -49.600010f, -60.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_28", 2007457, 6859528, 4, { -24.584480f, -50.000099f, -60.175560f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_29", 2007457, 6859530, 4, { 3.275066f, -50.000000f, -84.997147f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2007457, 6859529, 4, { 24.522739f, -49.999950f, -59.571861f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_31", 2007457, 6859527, 4, { 0.874527f, -49.599991f, -61.476238f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_32", 2007457, 6878662, 4, { -20.074200f, -49.999969f, -74.558640f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_33", 2007457, 6878660, 4, { 15.916950f, -49.999950f, -79.250931f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_34", 2002735, 0, 4, { 0.000000f, -99.699997f, -162.569397f }, 1.200000f, 0.000047f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 6910585, 4, { 0.625610f, -100.000000f, -160.942093f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Sluicegate_14", 2008601, 6880358, 4, { -18.062990f, -100.000000f, -197.715500f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sluicegate_15", 2008602, 6880354, 4, { 18.478640f, -100.022903f, -198.168900f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Treasurecoffer_4", 2008570, 0, 4, { 0.000000f, -99.600014f, -180.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_35", 2007457, 6843688, 4, { -24.612850f, -100.000099f, -180.473694f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_36", 2007457, 6843689, 4, { 3.250122f, -100.000000f, -205.284805f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_37", 2007457, 6843686, 4, { 24.521240f, -100.000000f, -179.863297f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_38", 2007457, 6843671, 4, { 0.869751f, -99.600113f, -181.755402f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_39", 2007457, 6878564, 4, { -20.096189f, -100.000000f, -194.847595f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_40", 2007457, 6878562, 4, { 15.915160f, -100.000000f, -199.547394f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_41", 2002735, 0, 4, { 0.000000f, -149.699997f, -282.259888f }, 1.200000f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2002872, 6910763, 4, { 0.625622f, -150.000107f, -281.035614f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Sluicegate_16", 2008603, 6880362, 4, { -18.081970f, -150.000107f, -317.830200f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Sluicegate_17", 2008604, 6880366, 4, { 17.127180f, -150.000107f, -317.622009f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Treasurecoffer_5", 2008571, 0, 4, { 0.000000f, -149.600006f, -300.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_42", 2007457, 6859613, 4, { -24.612820f, -150.000198f, -300.567108f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_43", 2007457, 6859615, 4, { 3.250126f, -150.000107f, -325.378296f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_44", 2007457, 6859614, 4, { 24.521259f, -150.000107f, -299.956696f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_45", 2007457, 6859612, 4, { 0.869759f, -149.600204f, -301.848907f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_46", 2007457, 6874400, 4, { -20.096189f, -150.000107f, -314.941101f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_47", 2007457, 6874396, 4, { 15.915160f, -150.000107f, -319.640900f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_48", 2002735, 0, 4, { 0.000000f, -199.699997f, -402.035004f }, 1.200000f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_6", 2002872, 6910821, 4, { 0.625622f, -200.000305f, -400.930389f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.069897f, -200.000305f, -436.982697f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_49", 2007457, 6859698, 4, { -24.612860f, -200.000504f, -420.461792f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_50", 2007457, 6859700, 4, { 3.250122f, -200.000397f, -445.273010f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_51", 2007457, 6859699, 4, { 24.521210f, -200.000305f, -419.851410f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_52", 2007457, 6859697, 4, { 0.869759f, -199.600403f, -421.743500f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheHiddenCanalsofUznair );