#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheBindingCoilofBahamutTurn2 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheBindingCoilofBahamutTurn2() :
    Sapphire::ScriptAPI::InstanceContentScript( 30003 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0094", 2000668, 4307413, 4, { -16.838060f, -60.912392f, 116.477898f }, 1.000000f, 0.000000f ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.registerEObj( "sgpl_s1b2_bosswall_c", 2000669, 4307414, 4, { -16.655029f, -61.041161f, 117.352303f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_s1b2_bossline2", 2000670, 4306762, 4, { -65.538063f, -38.998699f, 90.104332f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_s1b2_bosswall_r", 2000671, 4306763, 4, { -66.396652f, -38.998539f, 88.058296f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2000680, 0, 4, { -48.355518f, -38.578499f, 86.879211f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_s1b2_bossline3", 2000672, 4293655, 4, { -51.865479f, -18.020941f, 35.080441f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_s1b2_bosswall_r_1", 2000673, 4293656, 4, { -50.583679f, -18.020941f, 35.538212f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0249", 2000674, 4331576, 4, { 0.736900f, 0.033629f, 31.115801f }, 1.000000f, 0.000000f ); 
    // States -> vf_line_on (id: 10) vf_line_of (id: 11) 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2000675, 4331583, 4, { 1.580210f, 0.032013f, 29.906660f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_s1b2_bossline5", 2000676, 4306493, 4, { 52.177799f, -21.010019f, 34.437031f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_s1b2_bosswall_r_2", 2000677, 4306494, 4, { 51.183399f, -21.011810f, 34.504452f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_s1b2_bosswall_r_3", 2000679, 4306772, 4, { 60.934231f, -41.989620f, 101.246002f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_s1b2_bossline6", 2000678, 4306771, 4, { 59.622169f, -41.994068f, 98.767616f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_s1b2_bossline", 2000621, 4307578, 4, { 0.106751f, -65.934273f, 82.291870f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_s1b2_bosswall", 2000622, 4307579, 4, { -0.320496f, -65.934273f, 82.322388f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2000640, 4092173, 4, { -14.019790f, -0.010602f, 31.855391f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2000641, 4092174, 4, { 15.101930f, -0.029503f, 31.798840f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2000638, 4092177, 4, { -58.677170f, -18.016920f, 47.536171f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2000639, 4092181, 4, { -27.060640f, -18.102751f, 58.292858f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2000642, 4092183, 4, { 58.277191f, -20.996519f, 62.605671f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2000643, 4092178, 4, { 30.274019f, -20.952881f, 58.602650f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2000644, 4092182, 4, { 29.367611f, -41.975361f, 110.864998f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2000635, 4092184, 4, { 0.539888f, -62.460609f, 100.908897f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2000636, 4092179, 4, { -55.941719f, -38.998539f, 78.436340f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2000637, 4092180, 4, { -51.528130f, -38.998749f, 109.805901f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2000645, 4092175, 4, { 0.474554f, -65.943604f, 68.078178f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Allaganterminal", 2001161, 4107517, 4, { -0.118857f, -102.612297f, 0.534058f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2001152, 4107515, 4, { 2.090964f, 0.000001f, 22.575050f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000628, 4293644, 5, { 0.852533f, 0.148087f, 20.254930f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheBindingCoilofBahamutTurn2 );