#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheFistoftheSonSavage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheFistoftheSonSavage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30034 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2006093, 0, 4, { -0.030479f, -18.000000f, -87.654160f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2002872, 6179766, 4, { 0.048718f, -8.000000f, -25.550190f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6179771, 4, { 0.348718f, -8.000000f, -62.819778f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002587, 0, 4, { 0.000000f, -7.796605f, -27.253839f }, 1.400000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6179774, 4, { 0.000000f, -18.000000f, -86.751549f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 0.000000f, -18.000000f, -88.696098f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -10.159560f, -10.000000f, -208.556000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2006965, 6200579, 4, { 0.000000f, -10.000000f, -190.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_d2a0_a5_spry4", 2004870, 6200506, 4, { -0.400928f, -10.000000f, -198.953598f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_d2a0_a5_spry3", 2005111, 6200497, 4, { 9.766629f, -10.000000f, -190.029099f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Koboldkey", 2006468, 6200507, 4, { -9.431794f, -10.000000f, -190.472397f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Koboldkey_1", 2006469, 6200508, 4, { 0.206919f, -10.000000f, -180.011597f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2004363, 0, 4, { 0.000000f, -10.000000f, -190.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2004367, 0, 4, { 0.000000f, -10.000000f, -206.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2004368, 0, 4, { 16.000000f, -10.000000f, -190.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2004369, 0, 4, { -16.000000f, -10.000000f, -190.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2004575, 0, 4, { 0.000000f, -10.000000f, -174.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit_1", 2005313, 6180367, 4, { -8.545354f, -9.800000f, -209.792007f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6177861, 5, { 0.000000f, -60.199001f, 70.921097f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 1.189643f, -53.337769f, 57.917198f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2006105, 6185484, 4, { 0.000000f, -58.108219f, 65.176361f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance_1", 2000182, 6184198, 5, { 4.589292f, -3.826589f, 1.082808f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut_1", 2000700, 0, 4, { 3.135107f, -6.123573f, -3.436843f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2006105, 6198124, 4, { 4.362909f, -6.098227f, -3.232224f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlexanderTheFistoftheSonSavage );