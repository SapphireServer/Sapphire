#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Amaurot : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Amaurot() : Sapphire::ScriptAPI::InstanceContentScript( 67 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -79.697281f, 748.232788f, 102.371300f }, 1.350000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7933936, 4, { -80.004097f, 748.000000f, 62.132141f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 7933935, 4, { -80.000000f, 748.232788f, 99.693611f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 60.023880f, 728.242981f, -341.139099f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7933938, 4, { 60.023880f, 728.242981f, -338.479187f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Aetherialflow", 2009984, 7932928, 4, { 60.018700f, 728.000000f, -369.301392f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -0.045776f, -731.502319f, 44.897202f }, 0.700000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 7933939, 4, { -0.010600f, -732.000000f, 49.149700f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.015320f, -720.004822f, -61.020870f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 7875823, 4, { -7.927958f, -720.000305f, -17.158800f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 7875816, 4, { 8.072038f, -720.000183f, -17.158800f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 7875814, 4, { -7.950014f, -720.004578f, -35.172058f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_6", 2007457, 7875809, 4, { 8.072021f, -720.004700f, -35.172070f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_7", 2007457, 7875821, 4, { -7.950012f, -720.004578f, -55.161442f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_8", 2007457, 7875818, 4, { 8.072041f, -720.000000f, -55.158791f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 7875819, 4, { 8.072041f, -720.000000f, -75.158791f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 7875820, 4, { -7.927959f, -720.000000f, -75.158791f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 7952955, 4, { 0.000000f, -720.000000f, -60.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 7880675, 4, { -7.927959f, -720.000122f, -91.158791f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2007457, 7880673, 4, { 8.072041f, -720.000122f, -91.158791f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -10.406650f, 750.061829f, 460.909698f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 7886222, 5, { -0.054596f, 750.000122f, 475.021393f }, 1.000000f, -0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_14", 2007457, 7918524, 4, { -0.076355f, 747.218994f, 278.889191f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_15", 2007457, 7918552, 4, { -79.975014f, 745.000000f, 127.939499f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_16", 2007457, 7934800, 4, { 34.142502f, 758.577576f, 383.521393f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_17", 2007457, 7918703, 4, { 59.664379f, 729.299988f, -235.055603f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_18", 2007457, 7918698, 4, { -11.161700f, 730.180420f, -164.957901f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_19", 2007457, 7953069, 4, { -0.015368f, -730.006775f, 182.567093f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_20", 2007457, 7961990, 4, { -0.008849f, -732.000000f, 49.281261f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_n4d6_b1648", 2010292, 7933010, 4, { 0.000000f, -740.000122f, 330.950897f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d6_b1648_1", 2010293, 7933011, 4, { -0.015320f, -730.000000f, 181.973495f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_n4d6_b1648_2", 2010294, 7933012, 4, { -0.015320f, -732.000000f, 48.061100f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Amaurot );