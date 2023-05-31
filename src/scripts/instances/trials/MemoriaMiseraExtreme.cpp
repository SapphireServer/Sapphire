#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class MemoriaMiseraExtreme : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  MemoriaMiseraExtreme() : Sapphire::ScriptAPI::InstanceContentScript( 20070 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8258986, 5, { 34.289162f, -24.000000f, -664.743286f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 35.000000f, -24.000000f, -698.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Bladespulse", 2011052, 8308466, 4, { 36.200001f, -24.000000f, -682.599976f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Bladespulse_1", 2011055, 8308467, 4, { 33.799999f, -24.000000f, -682.599976f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8308408, 4, { 35.000000f, -24.000000f, -656.736328f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 35.129059f, -23.900000f, -657.250000f }, 0.800000f, -0.000000f); 
    instance.registerEObj( "Bladespulse_2", 2011051, 8308462, 4, { 36.220001f, -24.000000f, -682.650024f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Magitekarmorremnants", 2011034, 0, 4, { 7.625823f, -9.625379f, -67.736794f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Battlewornarms", 2011035, 0, 4, { 25.162109f, -4.867676f, -1.968445f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2011036, 0, 4, { 21.469419f, -6.790344f, -72.678772f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 8269037, 4, { 33.035770f, -25.009581f, -326.009003f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 8278481, 4, { 35.172001f, -22.653610f, -626.707520f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgbg_n4b2_a0_gmc13", 2007457, 8308405, 4, { 35.418800f, -22.653610f, -601.729187f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgbg_w_qic_004_03b", 2007457, 8361991, 4, { 35.012100f, -22.901550f, -630.264526f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8305646, 4, { 34.836300f, -25.162230f, -459.910004f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8305648, 4, { 34.561241f, -25.004650f, -497.656189f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { 34.900002f, -25.004700f, -464.660004f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "sgbg_n4b2_a0_gmc14", 2007457, 8338215, 4, { -1.137000f, 1.014300f, 53.453800f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4b2_a0_gmc14_1", 2007457, 8338216, 4, { 17.718800f, -8.092800f, -76.451698f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4b2_a0_gmc14_2", 2007457, 8338217, 4, { 35.058201f, -25.000000f, -252.315002f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4b2_a0_gmc14_3", 2007457, 8340998, 4, { 36.560139f, -25.000000f, -324.101898f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4b2_a0_gmc14_4", 2007457, 8340999, 4, { 34.793671f, -22.653601f, -594.831604f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Discardeddocuments", 2011062, 0, 4, { 34.175999f, -22.623699f, -602.089722f }, 1.000000f, -0.992682f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MemoriaMiseraExtreme );