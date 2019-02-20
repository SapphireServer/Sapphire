#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheFistoftheFather :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheFistoftheFather() :
    Sapphire::ScriptAPI::InstanceContentScript( 30021 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005032, 0, 4, { -10.154560f, -23.900000f, -171.851105f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2005046, 0, 4, { -13.656920f, -24.002501f, -180.132797f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2005033, 0, 4, { -16.466789f, -24.000000f, -176.308197f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 0.000000f, 8.000000f, -39.386002f }, 0.750000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 5787765, 4, { -0.007763f, 8.000001f, -38.723202f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 5787769, 4, { -0.007763f, 8.000002f, -76.255096f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2005148, 5835158, 4, { -5.000000f, -4.351456f, 18.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2005149, 5835159, 4, { 5.000000f, -4.368736f, 18.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2005150, 5835148, 4, { -4.000000f, -3.485719f, 13.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2005151, 5835149, 4, { 4.000000f, -3.483227f, 13.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2005315, 5835144, 4, { -4.000000f, -2.619212f, 8.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2006035, 5835145, 4, { 4.000000f, -2.621703f, 8.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2006053, 5835143, 4, { -3.000000f, -1.918940f, 4.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2006054, 5835135, 4, { 3.000000f, -1.911465f, 4.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2006055, 5835141, 4, { -3.000000f, -1.231334f, 0.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2006056, 5835136, 4, { 3.000000f, -1.231335f, 0.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2006057, 5835153, 4, { -9.000000f, -3.642947f, 14.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2006058, 5835152, 4, { -9.000000f, -3.309154f, 12.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2006059, 5835151, 4, { 9.000000f, -3.666079f, 14.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2006060, 5835150, 4, { 9.000000f, -3.310075f, 12.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2006093, 5858144, 4, { -0.006211f, 12.000000f, -107.218903f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 5787778, 4, { 0.000000f, 12.000000f, -107.839302f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.035584f, -24.311769f, -187.660599f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2005402, 5815199, 4, { 1.317244f, -23.900000f, -173.937302f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2005401, 5837182, 4, { -0.350596f, -23.900000f, -171.328796f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit_1", 2005313, 5908619, 4, { 0.000000f, -23.476339f, -186.888397f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2002735, 0, 4, { 0.000000f, 11.993800f, -108.070297f }, 0.500000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 5786793, 5, { -0.057753f, -21.358721f, 88.563942f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -1.141299f, -16.781481f, 74.122673f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2005147, 5905927, 4, { -0.186450f, -20.599979f, 84.260910f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance_1", 2000182, 5911084, 5, { -0.057753f, 8.090733f, -31.639650f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "sgpl_w_lvd_colwithnavi", 2000608, 5911088, 4, { -0.300161f, 5.743856f, -19.072269f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2005147, 5912244, 4, { -0.186450f, 8.755365f, -27.952221f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlexanderTheFistoftheFather );