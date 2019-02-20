#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SigmascapeV10Savage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SigmascapeV10Savage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30063 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgbg_z3o7_a0_ghr01", 2007457, 7230603, 4, { -6.335131f, 0.049939f, -10.559780f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3o7_a0_ghr01_1", 2007457, 7230604, 4, { -5.699108f, 0.049922f, -2.387848f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3o7_a0_ghr01_2", 2007457, 7230605, 4, { -6.369749f, 0.050002f, 7.711805f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3o7_a0_ghr01_3", 2007457, 7230606, 4, { -6.234384f, 0.050004f, 17.721371f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b1256", 2009408, 7231049, 4, { -3.117226f, 0.050002f, 9.861297f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3o7_b1346", 2009409, 7231069, 4, { -25.851500f, 16.520651f, 22.008921f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2007457, 7274404, 4, { -22.963020f, -2.647718f, 8.151876f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3o7_b1359", 2007457, 7297633, 4, { -30.500000f, 0.552600f, 43.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009384, 0, 4, { 220.569107f, -108.812103f, 5.081238f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aetherialstream", 2009400, 7231089, 4, { 144.482300f, -110.000000f, -71.090813f }, 0.991760f, 0.000046f ); 
    instance.registerEObj( "Aetherialstream_1", 2009401, 7231090, 4, { 144.468994f, -110.000000f, -23.514120f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aetherialstream_2", 2009402, 7231091, 4, { 144.456100f, -110.000000f, 23.836590f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aetherialstream_3", 2009403, 7231092, 4, { 144.470901f, -110.000000f, 71.062202f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aetherialstream_4", 2009404, 7231093, 4, { 215.991302f, -110.000000f, -71.152832f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aetherialstream_5", 2009405, 7231096, 4, { 215.991302f, -110.000000f, -23.514160f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aetherialstream_6", 2009406, 7231097, 4, { 215.991302f, -110.000000f, 23.880310f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aetherialstream_7", 2009407, 7231098, 4, { 215.991302f, -110.000000f, 71.061279f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_z3o7_b1359_1", 2007457, 7297634, 4, { 178.511902f, -110.002403f, -0.198364f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2007457, 7181869, 5, { -3.537696f, 0.000001f, 18.750830f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.076233f, -0.015320f, -9.170715f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SigmascapeV10Savage );