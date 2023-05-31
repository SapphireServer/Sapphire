#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AkadaemiaAnyder : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AkadaemiaAnyder() : Sapphire::ScriptAPI::InstanceContentScript( 71 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7922328, 4, { -305.000000f, -23.000000f, 259.071899f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -305.000000f, -23.026390f, 259.133789f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d8_b1798", 2007457, 7942203, 4, { -305.000000f, -30.400000f, 186.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d8_b1798_1", 2007457, 7942206, 4, { -287.322296f, -30.400000f, 193.822296f }, 1.000000f, 0.785398f); 
    instance.registerEObj( "sgvf_n4d8_b1798_2", 2007457, 7942207, 4, { -280.000000f, -30.400000f, 211.491394f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "sgvf_n4d8_b1798_3", 2007457, 7942208, 4, { -287.322296f, -30.399990f, 229.177704f }, 1.000000f, 0.785398f); 
    instance.registerEObj( "sgvf_n4d8_b1798_4", 2007457, 7942209, 4, { -305.000000f, -30.400000f, 236.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d8_b1798_5", 2007457, 7942210, 4, { -322.677704f, -30.400000f, 229.177704f }, 1.000000f, -0.785398f); 
    instance.registerEObj( "sgvf_n4d8_b1798_6", 2007457, 7942211, 4, { -330.000000f, -30.400000f, 211.491394f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "sgvf_n4d8_b1798_7", 2007457, 7942212, 4, { -322.677704f, -30.400000f, 193.822296f }, 1.000000f, -0.785398f); 
    instance.registerEObj( "unknown_1", 2007457, 7955869, 4, { -305.000000f, -30.500000f, 193.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1673a", 2002872, 7923104, 4, { -224.000000f, -27.000000f, -13.000000f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b1673a_1", 2002872, 7923107, 4, { -224.000000f, -27.000000f, -63.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2007457, 7893499, 4, { -224.000000f, -27.000000f, -38.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2010506, 0, 4, { -224.000000f, -27.000000f, -13.000000f }, 0.800000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1673a_2", 2002872, 7923113, 4, { 0.000000f, 301.000000f, -359.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2010506, 0, 4, { 0.000000f, 300.799988f, -359.000000f }, 0.800000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 7892757, 4, { -206.500000f, -15.700000f, 321.250000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_n4d6_b1648", 2007457, 7964030, 4, { -305.012604f, -23.000000f, 264.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 7917732, 4, { -305.000000f, -30.500000f, 41.500000f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "unknown_7", 2007457, 7917733, 4, { -224.000000f, -30.500000f, 1.800000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d6_b1648_1", 2007457, 7964026, 4, { -305.012604f, -30.400101f, 188.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 7956011, 4, { -330.026703f, -30.500000f, 34.792450f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 7956402, 4, { -316.688385f, -30.500000f, 48.344299f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 7924361, 4, { -0.200000f, -38.000000f, -169.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 7924360, 4, { -0.200000f, -38.000000f, -284.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Visitorsguide", 2010691, 0, 4, { -172.130005f, -10.203410f, 316.292786f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Visitorsguide_1", 2010692, 0, 4, { -298.775513f, -30.504040f, 95.397873f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Researchreport", 2010693, 0, 4, { -36.462639f, -37.996059f, -230.962708f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 7923121, 5, { 0.000000f, 0.501200f, 346.265411f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.256828f, 301.000000f, -393.308502f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -8.585638f, 0.650027f, 335.942413f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AkadaemiaAnyder );