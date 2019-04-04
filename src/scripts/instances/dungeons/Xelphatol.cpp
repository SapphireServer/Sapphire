#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Xelphatol :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Xelphatol() :
    Sapphire::ScriptAPI::InstanceContentScript( 46 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -84.755379f, 28.000000f, -51.118382f }, 1.000000f, 0.523599f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6403264, 4, { -82.540977f, 28.000000f, -53.644989f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007376, 6403259, 4, { -59.964069f, 28.000000f, -78.522522f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 223.705399f, 113.500000f, 35.108238f }, 0.500000f, 0.785398f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6403502, 4, { 224.909500f, 113.199997f, 33.535221f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007377, 6403509, 4, { 264.503998f, 113.199997f, -5.542618f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2007431, 6384823, 4, { 245.262695f, 113.500000f, 13.527060f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 336.690308f, 166.643707f, -409.414886f }, 0.472961f, -1.221690f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 6403539, 4, { 335.712402f, 166.653793f, -410.036194f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2007441, 6425251, 4, { 321.753204f, 166.653793f, -415.372711f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -204.533798f, -33.742210f, 271.416107f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 306.067810f, 166.653793f, -420.100494f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6399475, 5, { -219.983398f, -34.117180f, 275.020111f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_5", 2007371, 6572085, 4, { -124.008698f, -10.048470f, 151.735703f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_6", 2007372, 6572086, 4, { -88.521538f, 27.655760f, -44.885460f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007366, 6384146, 4, { 70.443916f, 25.187500f, -55.889919f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007367, 6384285, 4, { 178.158096f, 99.562508f, -3.919224f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007364, 6384308, 4, { 78.279350f, 25.190849f, -47.949661f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007365, 6384356, 4, { 178.228394f, 99.500000f, 8.238135f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Liftlever", 2007388, 0, 4, { 180.229706f, 56.749981f, -76.583313f }, 1.000000f, -2.356194f ); 
    instance.registerEObj( "Liftlever_1", 2007389, 0, 4, { 180.245193f, 86.749977f, -76.529610f }, 1.000000f, -0.785398f ); 
    instance.registerEObj( "Liftlever_2", 2007390, 0, 4, { 188.720001f, 56.749981f, -68.098488f }, 1.000000f, -0.785398f ); 
    instance.registerEObj( "Liftlever_3", 2007391, 0, 4, { 188.709198f, 86.749977f, -68.041428f }, 1.000000f, -0.785398f ); 
    instance.registerEObj( "Imposinggate", 2007373, 6382783, 4, { 168.614197f, 55.750000f, -60.833012f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Bonekey", 2007397, 0, 4, { 143.135406f, 52.677929f, -35.654629f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007370, 6383173, 4, { 97.740517f, 26.124990f, -40.661610f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007405, 6527474, 4, { 351.622009f, 163.753799f, -404.382599f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Airstone", 2007398, 0, 4, { 316.850586f, 142.878403f, -142.151505f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Airstone_1", 2007399, 0, 4, { 420.029205f, 149.955597f, -271.014801f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Tailwindrelic", 2007400, 6422938, 4, { 342.708191f, 145.153397f, -162.585800f }, 1.000000f, 0.000000f ); 
    // States -> start (id: 3) stop (id: 4) 
    instance.registerEObj( "Tailwindrelic_1", 2007401, 6422940, 4, { 414.549988f, 152.457504f, -298.508392f }, 0.991760f, 0.000048f ); 
    // States -> start (id: 3) stop (id: 4) 
    instance.registerEObj( "unknown_13", 2007524, 6493432, 4, { 341.786896f, 144.853806f, -164.354904f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2007525, 6493431, 4, { 412.853699f, 152.110397f, -297.974396f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Xelphatol );