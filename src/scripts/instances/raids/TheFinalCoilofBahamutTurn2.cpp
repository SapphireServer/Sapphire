#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFinalCoilofBahamutTurn2 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFinalCoilofBahamutTurn2() :
    Sapphire::ScriptAPI::InstanceContentScript( 30017 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2004618, 0, 4, { 8.377602f, -4.963000f, 2.130980f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w1b2_b0338", 2004622, 5004388, 4, { 0.000000f, -4.963000f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> brr_off (id: 2) brr_on2off (id: 3) brr_on (id: 4) brr_off2on (id: 5) 
    instance.registerEObj( "unknown_1", 2004138, 4985190, 4, { 3.028988f, -85.357613f, 329.862915f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -8.983331f, -89.405617f, 340.705505f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 4895376, 5, { -2.304138f, -95.841980f, 373.883514f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_2", 2004138, 4772070, 4, { -3.471196f, -85.362328f, 329.862915f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2004138, 0, 4, { 3.028988f, -85.357613f, 329.862915f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2004138, 4772073, 4, { 82.671562f, 89.558182f, 312.686188f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2004138, 4772071, 4, { -87.694283f, 61.779518f, 322.880798f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2004138, 4772074, 4, { 68.781647f, 74.135750f, 257.001312f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2004138, 4772072, 4, { -71.265640f, 50.681782f, 262.029907f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2004138, 0, 4, { 3.045514f, -50.605240f, 198.785202f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2004131, 4772088, 4, { -0.320496f, -61.905880f, 240.100693f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2004131, 4772089, 4, { -0.150618f, -58.926769f, 229.063507f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2004130, 4903493, 4, { 0.167786f, -56.382141f, 216.998505f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2004138, 4772084, 4, { 5.588670f, -50.254120f, 198.785202f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2004138, 4985729, 4, { -1.068177f, -50.250832f, 198.785202f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2004138, 4772077, 4, { 93.772713f, 2.760812f, 164.237198f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2004138, 4772078, 4, { 62.832458f, 2.703932f, 109.635002f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2004138, 4772079, 4, { -101.804497f, -15.054380f, 174.336105f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2004138, 4772080, 4, { -68.094177f, -9.272421f, 114.627701f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2004131, 4772085, 4, { -33.952530f, 1.069616f, 57.437080f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2004131, 4772087, 4, { 34.497631f, 1.062853f, 57.576210f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2004130, 4903494, 4, { -18.231251f, 0.578985f, 63.141258f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2004130, 4903495, 4, { 18.776350f, 0.578991f, 63.349949f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2004138, 4772081, 4, { 0.088281f, 0.909978f, 67.335487f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_23", 2004138, 4772082, 4, { -66.984283f, 1.029588f, -0.043371f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2004138, 4772083, 4, { 67.627632f, 1.029588f, -0.043371f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2002735, 0, 4, { 0.046454f, 0.339829f, 55.289249f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 4896001, 4, { -0.021759f, 0.578989f, 57.955990f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Allaganterminal", 2004142, 4797408, 4, { 0.001913f, -4.224863f, -30.000130f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_colwithnavi", 2004137, 4895798, 4, { -0.366558f, -4.738363f, -24.911970f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFinalCoilofBahamutTurn2 );