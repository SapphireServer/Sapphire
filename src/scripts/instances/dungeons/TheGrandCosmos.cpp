#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheGrandCosmos : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheGrandCosmos() : Sapphire::ScriptAPI::InstanceContentScript( 73 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8102947, 4, { -0.000000f, 0.000000f, 205.083206f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 0.000000f, 0.000000f, 202.712494f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8102954, 4, { -0.000000f, 0.000000f, 167.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2010798, 0, 4, { -5.035117f, 0.000000f, 178.478607f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8102899, 4, { -0.000000f, -13.585750f, -37.285641f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -0.000000f, -12.500000f, -39.250130f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 8102940, 4, { 0.000000f, -12.500000f, -83.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Leannanseed", 2010782, 0, 4, { -15.000000f, -12.500300f, -75.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Leannanseed_1", 2010783, 0, 4, { -5.000000f, -12.500010f, -75.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Leannanseed_2", 2010784, 0, 4, { 5.000000f, -12.500010f, -75.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Leannanseed_3", 2010785, 0, 4, { 15.000000f, -12.500300f, -75.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2010822, 0, 4, { -11.264170f, -12.500010f, -69.745003f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 8101553, 4, { 0.000000f, 8.000000f, -312.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2010506, 0, 4, { -0.015320f, 8.000000f, -314.268188f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_5", 2007457, 8105929, 4, { -29.068480f, -0.015320f, 321.064911f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_6", 2007457, 8105931, 4, { -40.512760f, -0.015320f, 321.064911f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_7", 2007457, 8105933, 4, { -52.338009f, -0.015560f, 321.065186f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_8", 2007457, 8105928, 4, { -28.091921f, -0.015320f, 330.342499f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_9", 2007457, 8105930, 4, { -40.451721f, -0.015320f, 330.372986f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_10", 2007457, 8105932, 4, { -52.609779f, -0.015559f, 330.373291f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_11", 2007457, 8105937, 4, { -103.685898f, 0.049963f, 299.859985f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_12", 2007457, 8107130, 4, { -26.987570f, -0.000000f, 293.505615f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_13", 2007457, 8156126, 4, { -112.725304f, -0.000100f, 310.739990f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_14", 2007457, 8156127, 4, { -112.748901f, -0.015320f, 289.478912f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_15", 2007457, 8106202, 4, { -0.044180f, -4.000000f, -154.218399f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_16", 2007457, 8059095, 4, { 54.581421f, 7.980469f, -212.237701f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_17", 2007457, 8059075, 4, { 54.581421f, 7.980469f, -225.970901f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_18", 2007457, 8059094, 4, { 42.621441f, 7.981042f, -212.238297f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_19", 2007457, 8059078, 4, { 42.618500f, 8.000000f, -226.001495f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_20", 2007457, 8100464, 4, { 26.610041f, 8.000517f, -219.098099f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_21", 2007457, 8105851, 4, { -108.537498f, -0.015232f, 286.206512f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_22", 2007457, 8105912, 4, { -0.015285f, -0.000000f, 227.656403f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_23", 2007457, 8106161, 4, { 81.999237f, -14.000000f, 34.963860f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_24", 2007457, 8106162, 4, { 0.018529f, -14.000000f, -14.362510f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_25", 2007457, 8106204, 4, { 42.461910f, 8.000008f, -184.574295f }, 0.991760f, 0.000144f); 
    instance.registerEObj( "unknown_26", 2007457, 8106205, 4, { 30.380739f, 7.980469f, -234.851700f }, 0.991760f, 0.000144f); 
    instance.registerEObj( "unknown_27", 2007457, 8106220, 4, { 0.000000f, 8.000000f, -290.000000f }, 0.991760f, 0.000144f); 
    instance.registerEObj( "Entrance", 2007457, 8101433, 5, { 4.989685f, -0.000006f, 378.244293f }, 0.991760f, 0.000048f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -4.000000f, 0.000000f, 367.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.014902f, 8.000000f, -361.013702f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheGrandCosmos );