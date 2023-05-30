#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheDeadEnds : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheDeadEnds() : Sapphire::ScriptAPI::InstanceContentScript( 84 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 266.500000f, 500.955597f, -157.750000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8872994, 4, { 266.500000f, 500.955597f, -157.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8872996, 4, { 266.500000f, 501.000000f, -198.000000f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -105.000000f, 0.062747f, -189.850006f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8873050, 4, { -105.000000f, 0.062747f, -189.850006f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 8873052, 4, { -105.000000f, 0.199536f, -229.500000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -380.000000f, -576.999878f, -115.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 8873103, 4, { -380.000000f, -576.999878f, -115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Longforgottenseashell", 2012554, 0, 4, { 417.554291f, 500.297913f, 93.815643f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Longforgottenseashell_1", 2012555, 0, 4, { 254.534698f, 500.500000f, -115.808701f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Longforgottencorrespondence", 2012556, 0, 4, { -2.832205f, 0.000000f, -45.086349f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Longforgottencorrespondence_1", 2012557, 0, 4, { -99.364799f, 0.739492f, -159.007004f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Longforgottenessence", 2012558, 0, 4, { -307.556000f, -609.555786f, 98.881523f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Longforgottenessence_1", 2012559, 0, 4, { -365.726410f, -587.489319f, -43.732422f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Spatialdistortion", 2011767, 0, 4, { 266.498810f, 500.400208f, -221.362701f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Spatialdistortion_1", 2011768, 0, 4, { -110.704201f, -7.854956f, -289.387390f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8872989, 5, { 347.982086f, 499.687103f, 182.482498f }, 0.991760f, 0.000048f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -380.000000f, -576.999878f, -150.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 359.818787f, 499.561890f, 188.972504f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheDeadEnds );