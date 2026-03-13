#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheFieldsofGloryShatter : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFieldsofGloryShatter() : Sapphire::ScriptAPI::InstanceContentScript( 50005 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "sgvf_w_lvd_b0286", 2007022, 6245702, 6245741, 4, { -263.444885f, 52.175270f, -209.921402f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -263.442200, 54.175270, -215.921402 }, -0.000000, 2.497972, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -263.443115, 54.175270, -203.921402 }, -0.000000, 2.500406, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -257.444885, 54.175270, -209.925797 }, -1.570451, 2.500640, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -269.444885, 54.175270, -209.922867 }, -1.570451, 2.504768, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -267.642822, 54.175270, -214.123474 }, -0.785398, 2.650707, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -259.246948, 54.175270, -205.719330 }, -0.785398, 2.644853, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -259.244873, 54.175270, -214.121399 }, 0.785398, 2.647780, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -267.644897, 54.175270, -205.721405 }, 0.785398, 2.647780, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0286_1", 2007023, 6245745, 6245742, 4, { -91.249367f, 27.082781f, 248.251297f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -91.246666, 29.082781, 242.251297 }, -0.000000, 2.497972, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -91.247604, 29.082781, 254.251297 }, -0.000000, 2.500406, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -85.249367, 29.082781, 248.246902 }, -1.570451, 2.500640, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -97.249359, 29.082781, 248.249832 }, -1.570451, 2.504768, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -95.447296, 29.082781, 244.049225 }, -0.785398, 2.650707, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -87.051437, 29.082781, 252.453369 }, -0.785398, 2.644853, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -87.049370, 29.082781, 244.051300 }, 0.785398, 2.647780, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -95.449364, 29.082781, 252.451294 }, 0.785398, 2.647780, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0286_2", 2007024, 6245744, 6245743, 4, { 262.704590f, 7.555402f, -83.636391f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 262.707642, 9.538637, -89.587051 }, 0.000048, 2.477390, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 262.706146, 9.539207, -77.685921 }, 0.000048, 2.479804, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 268.655243, 9.538637, -83.640556 }, -1.570403, 2.480036, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 256.754120, 9.539207, -83.638222 }, -1.570403, 2.484129, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 258.541534, 9.538922, -87.804131 }, -0.785350, 2.628866, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 266.867828, 9.538922, -79.468842 }, -0.785350, 2.623060, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 266.870270, 9.538523, -87.801682 }, 0.785446, 2.625963, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 258.539093, 9.539322, -79.471291 }, 0.785446, 2.625963, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col02", 2007038, 6246503, 6246634, 4, { -33.290001f, 8.500000f, -64.930000f }, 1.000000f, 0.345772f, 0 ); 
    // States -> loi_col (id: 1) loi_col_off (id: 2) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col02_1", 2007039, 6246502, 6246635, 4, { -29.181200f, 4.895900f, -181.130005f }, 1.000000f, -0.000000f, 0 ); 
    // States -> loi_col (id: 1) loi_col_off (id: 2) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col02_2", 2007040, 6246500, 6246636, 4, { 49.409801f, 1.000000f, 95.446404f }, 1.000000f, -0.000000f, 0 ); 
    // States -> loi_col (id: 1) loi_col_off (id: 2) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col02_3", 2007041, 6246488, 6246637, 4, { -139.203201f, 2.000000f, 42.698399f }, 1.000000f, -0.000000f, 0 ); 
    // States -> loi_col (id: 1) loi_col_off (id: 2) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01", 2007042, 6246517, 6246638, 4, { 10.250100f, 7.501600f, -73.703102f }, 1.000000f, -0.207694f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_3", 2007043, 6246515, 6246639, 4, { -28.053699f, 7.586800f, -20.808001f }, 1.000000f, -0.207694f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_2", 2007044, 6246516, 6246640, 4, { -57.941700f, 7.532000f, -89.861702f }, 1.000000f, -0.478128f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_17", 2007045, 6246512, 6246641, 4, { -43.203499f, 42.615501f, -229.343597f }, 1.000000f, 0.535781f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_15", 2007046, 6246511, 6246642, 4, { 121.235901f, 29.898701f, -190.225006f }, 1.000000f, -0.000000f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_14", 2007047, 6246510, 6246643, 4, { 175.149307f, 0.118000f, 8.585100f }, 1.000000f, -0.383869f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_13", 2007048, 6246509, 6246644, 4, { 174.059998f, 30.587099f, 122.660004f }, 1.000000f, -0.000000f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_12", 2007049, 6246508, 6246645, 4, { 75.684898f, 35.111000f, 149.223801f }, 1.000000f, -0.207694f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_11", 2007050, 6246507, 6246646, 4, { -8.180000f, 31.300200f, 107.550003f }, 1.000000f, -0.207694f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_9", 2007051, 6246505, 6246647, 4, { -195.641693f, 37.440800f, 80.677399f }, 1.000000f, 1.473960f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_8", 2007052, 6246514, 6246648, 4, { -148.077499f, 48.772800f, -3.141700f }, 1.000000f, -0.003491f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_6", 2007053, 6246513, 6246649, 4, { -126.529999f, 35.526501f, -132.360001f }, 1.000000f, -0.000000f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_16", 2007121, 6260294, 6260317, 4, { 29.201799f, 37.825001f, -217.776505f }, 1.000000f, 1.518110f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_5", 2007122, 6260289, 6260318, 4, { 17.876400f, 7.001300f, 11.047300f }, 1.000000f, -0.000000f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_10", 2007123, 6260290, 6260319, 4, { -107.700996f, 10.249100f, 150.690598f }, 1.000000f, -0.528624f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_4", 2007124, 6260291, 6260320, 4, { -81.065201f, 8.327300f, -23.711300f }, 1.000000f, 0.491354f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_7", 2007125, 6260292, 6260321, 4, { -224.454102f, 30.212000f, -33.290001f }, 1.000000f, 0.001382f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 

    pEObj = instance.addEObj( "sgbg_r2p1_q0_col01_1", 2007126, 6260293, 6260322, 4, { -21.009300f, 6.445800f, -124.468399f }, 1.000000f, -1.350824f, 0 ); 
    // States -> loi_col (id: 2) loi_col_off (id: 3) 


  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, Entity::EventObject& eobj, uint32_t eventId ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint64_t actorId ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

  void onLeaveTerritory( InstanceContent& instance, Entity::Player& player ) override
  {

  }

};

EXPOSE_SCRIPT( TheFieldsofGloryShatter );