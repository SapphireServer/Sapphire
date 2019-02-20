#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheSwallowsCompass :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSwallowsCompass() :
    Sapphire::ScriptAPI::InstanceContentScript( 61 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -240.000000f, -480.000000f, 20.149229f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7335368, 4, { -240.000000f, -480.000000f, 20.500000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 7335378, 4, { -240.000107f, -479.829407f, -20.937090f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 25.824850f, 0.000000f, 335.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7335369, 4, { 25.824900f, 0.000000f, 335.000000f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 7335384, 4, { 5.530100f, 0.066046f, 313.914093f }, 1.000000f, -1.570451f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2009482, 0, 4, { 25.617769f, -0.000000f, 313.533386f }, 0.991760f, -0.000000f ); 
    instance.registerEObj( "unknown_3", 2009483, 0, 4, { 25.639690f, 0.000000f, 313.537415f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_4", 2009484, 0, 4, { 25.639690f, -0.000000f, 313.537415f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_5", 2002735, 0, 4, { 14.984640f, 73.000053f, -214.000000f }, 1.000000f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 7335370, 4, { 14.984600f, 73.000099f, -214.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_6", 2007457, 7340414, 4, { 15.080000f, 73.000000f, -240.613205f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 7258934, 4, { -180.800003f, -478.399994f, -18.299999f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 7258961, 4, { -258.299988f, -478.399994f, -59.200001f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_9", 2007457, 7258964, 4, { -299.200012f, -478.399994f, 18.299999f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Geomanticaetheryte", 2009459, 7258990, 4, { -240.000000f, -478.149994f, -28.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 7257379, 4, { -180.800003f, -478.399994f, -0.025493f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 7257373, 4, { -240.000504f, -478.399994f, -59.200001f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 7257377, 4, { -299.206207f, -478.399994f, -0.030577f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Dragonsseal", 2009461, 7281048, 4, { -240.000000f, -478.399994f, 47.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3d6_b1392", 2007457, 7446402, 4, { -180.773697f, -478.399994f, 1.327454f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_e3d6_b1393", 2007457, 7446403, 4, { -238.718002f, -478.399994f, -59.199989f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3d6_b1394", 2007457, 7446404, 4, { -299.206207f, -478.399994f, -0.030600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 7352890, 4, { 289.021088f, -472.527893f, -139.615799f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Geomanticaetheryte_1", 2009460, 7258993, 4, { 288.165710f, -470.629913f, -186.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3d6_b1392_1", 2007457, 7446406, 4, { 219.684097f, -450.394989f, 143.129196f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2007457, 7537737, 4, { 220.000000f, -454.000000f, 34.954559f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007457, 7309347, 4, { 15.015300f, 65.000000f, -194.017807f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_e3d6_b1389", 2007457, 7446408, 4, { -48.630550f, -0.495845f, 145.921997f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_e3d6_b1389_1", 2007457, 7446409, 4, { 14.968400f, 0.846474f, -57.815701f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_e3d6_b1394_1", 2007457, 7446407, 4, { -27.118010f, 9.246044f, 277.059692f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_16", 2007457, 7344616, 4, { -1.968445f, 0.846474f, -87.815727f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_17", 2007457, 7344614, 4, { -48.630550f, -0.495845f, 145.921997f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 7335292, 5, { -240.000000f, -478.399994f, 120.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -243.776001f, -478.399994f, 110.345001f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 14.983240f, 73.000000f, -266.619385f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheSwallowsCompass );