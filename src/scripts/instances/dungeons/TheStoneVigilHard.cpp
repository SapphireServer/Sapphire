#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheStoneVigilHard :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheStoneVigilHard() :
    Sapphire::ScriptAPI::InstanceContentScript( 25 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Exit", 2000139, 0, 4, { -138.305603f, -7.970538f, -56.005821f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -103.660202f, -7.970543f, -55.945332f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2002872, 4724293, 4, { -105.613098f, -7.970541f, -56.019131f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -47.933350f, -3.938287f, 35.426449f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 4725733, 4, { -47.291790f, -3.999902f, 33.349419f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_r1d2_b0442", 2002872, 4725734, 4, { -38.530239f, -3.999901f, 23.897659f }, 1.000000f, 0.000000f ); 
    // States -> vf_fire_on (id: 2) vf_fire_of (id: 3) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -0.189037f, 3.895030f, -223.430893f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 4724833, 4, { 0.361240f, 3.879290f, -226.177200f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Entrance", 2001869, 4559005, 5, { 131.881805f, 4.081586f, 116.103600f }, 1.000000f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 113.577202f, 8.000000f, 113.037003f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_r1d2_b0442_1", 2002872, 4864542, 4, { -24.639549f, -0.050003f, 47.771549f }, 1.000000f, 0.000000f ); 
    // States -> vf_fire_on (id: 2) vf_fire_of (id: 3) 
    instance.registerEObj( "sgvf_r1d2_b0442_2", 2004182, 4933921, 4, { -0.990592f, 0.027524f, 96.986580f }, 1.000000f, 0.000000f ); 
    // States -> vf_fire_on (id: 2) vf_fire_of (id: 3) 
    instance.registerEObj( "Bertha", 2003540, 0, 4, { 31.943810f, 0.326915f, -151.623703f }, 1.000000f, -1.363030f ); 
    instance.registerEObj( "Bertha_1", 2003541, 0, 4, { 34.257309f, 0.068675f, -143.886703f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "Bertha_2", 2003542, 0, 4, { 31.738079f, 0.068675f, -136.270004f }, 1.000000f, -1.400810f ); 
    instance.registerEObj( "unknown_3", 2003543, 4635871, 4, { 24.398520f, -0.049999f, -178.281799f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_r1d2_b0442_3", 2003544, 4724326, 4, { -7.216811f, 0.000001f, -183.345200f }, 1.000000f, 0.000000f ); 
    // States -> vf_fire_on (id: 2) vf_fire_of (id: 3) 
    instance.registerEObj( "Mainstoragevaultgate", 2003547, 4556427, 4, { -96.021538f, -1.183108f, -56.314732f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_r1d2_b0442_4", 2004183, 4933927, 4, { -48.010059f, -0.050043f, -85.297096f }, 1.000000f, 0.000000f ); 
    // States -> vf_fire_on (id: 2) vf_fire_of (id: 3) 
    instance.registerEObj( "sgvf_r1d2_b0442_5", 2004184, 4947920, 4, { -43.944740f, -0.050000f, -96.101196f }, 1.000000f, 0.000000f ); 
    // States -> vf_fire_on (id: 2) vf_fire_of (id: 3) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheStoneVigilHard );