#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class AmdaporKeepHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AmdaporKeepHard() : Sapphire::ScriptAPI::InstanceContentScript( 29 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5018466, 5018468, 5, { -255.724792f, -9.199999f, -5.249732f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -255.724792, -7.199999, -8.249732 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -255.714996, -7.199999, -2.249732 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -252.724792, -7.199999, -5.245842 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -258.724792, -7.199999, -5.238756 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -257.824799, -7.199999, -7.349732 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -253.624786, -7.199999, -3.149732 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -253.624786, -7.199999, -7.349732 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -257.824799, -7.199999, -3.149732 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5018476, 4, { -252.173401f, -9.199999f, 5.737248f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5018489, 4, { 200.798599f, -0.000008f, 240.880905f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2004696, 5009720, 5031965, 4, { -200.316895f, -4.301562f, -43.621670f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -200.316895, 1.698438, -43.621670 }, -0.000000, 4.000000, 6.000000, 2.000000 );

    pEObj = instance.addEObj( "unknown_2", 2004697, 5009721, 5031982, 4, { -47.771290f, -0.000000f, -71.658272f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -47.771290, 6.000000, -71.658272 }, -0.000000, 4.000000, 6.000000, 2.000000 );

    pEObj = instance.addEObj( "sgbg_f1d7_a1_evl01", 2004698, 5031991, 5031993, 4, { -125.087196f, -2.000000f, 28.417601f }, 1.000000f, -0.000000f, 0 ); 
    // States -> evils_def (id: 17) evils_off_anim (id: 22) evils_on (id: 23) evils_on_anim (id: 24) 

    pEObj = instance.addEObj( "sgvf_f1d7_b0574", 2004699, 5031992, 5031994, 4, { -104.790604f, -2.000000f, 47.174728f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_baria1_off (id: 3) vf_baria_on (id: 6) 
    pEObj->addCollisionBox( { -104.790604, 0.563531, 47.589394 }, -0.000000, 10.000000, 4.000000, 0.585334 );
    pEObj->addCollisionBox( { -95.790604, 0.563531, 56.174728 }, -1.570451, 10.000000, 4.000000, 1.000000 );
    pEObj->addCollisionBox( { -113.790604, 0.563531, 56.174728 }, -1.570451, 10.000000, 4.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_3", 2004700, 0, 5032105, 4, { 2.343430f, 48.179089f, -2.083742f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2004702, 5009732, 5032127, 4, { 125.604897f, 43.999989f, 3.999085f }, 1.000000f, 0.005971f, 0 ); 
    pEObj->addCollisionBox( { 125.604897, 49.999989, 3.999085 }, 0.005971, 6.000000, 6.000000, 2.000000 );

    pEObj = instance.addEObj( "unknown_5", 2004701, 0, 5032143, 4, { 149.666000f, 44.200001f, -0.006115f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2004703, 5010816, 5032160, 4, { 196.927399f, 44.000019f, -101.381798f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 196.927399, 50.000019, -101.381798 }, -0.000000, 6.000000, 6.000000, 2.000000 );

    pEObj = instance.addEObj( "sgbg_f1d7_a1_evl01_1", 2004704, 5032163, 5032165, 4, { 199.696106f, 44.000000f, -181.197006f }, 1.000000f, 0.000000f, 0 ); 
    // States -> evils_def (id: 17) evils_off_anim (id: 22) evils_on (id: 23) evils_on_anim (id: 24) 

    pEObj = instance.addEObj( "Aetherialflow", 2004705, 5032164, 5032166, 4, { 199.682800f, 44.163898f, -180.392395f }, 1.000000f, -0.000000f, 0 ); 

    pEObj = instance.addEObj( "Fellorb", 2004706, 5009746, 5033532, 4, { 200.094101f, -0.000008f, 0.050249f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Aetherialflow_1", 2004707, 5033533, 5033534, 4, { 199.899506f, 0.000000f, -3.297300f }, 1.000000f, -0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2004768, 5033548, 5033553, 4, { 210.649307f, 0.116687f, -6.120441f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2004769, 5033549, 5033554, 4, { 189.489807f, 0.116688f, -6.804901f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2004770, 5033551, 5033555, 4, { 204.506500f, 0.116687f, 9.902725f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2004708, 5034801, 5034814, 4, { -119.510101f, -2.400002f, 18.885540f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -119.510101, 0.099998, 18.885540 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5034800, 5034815, 4, { -130.314606f, -2.400000f, -18.221069f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -130.314606, 0.100000, -18.221069 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_10", 2002735, 0, 5034816, 4, { -125.041801f, -1.964380f, -20.543480f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2004782, 5038257, 5038258, 4, { 198.459198f, 43.991699f, -172.369705f }, 1.000000f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 198.459320, 46.491699, -172.369827 }, 0.000048, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_4", 2002872, 5038255, 5038261, 4, { 197.802597f, 43.991699f, -125.932701f }, 1.000000f, -0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 197.802597, 46.491699, -125.932701 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_11", 2002735, 0, 5038262, 4, { 199.511703f, 44.022221f, -130.601303f }, 1.000000f, -0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5040923, 5040924, 4, { 203.452301f, 0.116688f, 208.657593f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 203.452301, 2.616688, 208.657593 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5040925, 4, { 199.471802f, 0.116693f, 210.128204f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_f1d7_a1_gar0", 2004996, 5390927, 5390931, 4, { -112.845497f, -2.400000f, 12.122500f }, 1.000000f, 0.785314f, 0 ); 

    pEObj = instance.addEObj( "sgpl_f1d7_a1_gar0_1", 2004997, 5390928, 5390932, 4, { -112.845497f, -2.400000f, -12.378100f }, 1.000000f, 0.785457f, 0 ); 

    pEObj = instance.addEObj( "sgpl_f1d7_a1_gar0_2", 2004998, 5390929, 5390933, 4, { -137.250000f, -2.400000f, 12.122500f }, 1.000000f, -0.785410f, 0 ); 

    pEObj = instance.addEObj( "sgpl_f1d7_a1_gar0_3", 2004999, 5390930, 5390934, 4, { -137.396194f, -2.400000f, -12.366500f }, 1.000000f, -0.785398f, 0 ); 

    pEObj = instance.addEObj( "sgbg_f1d7_a4_scy01", 2005153, 5619221, 5619223, 4, { 198.706802f, -20.000010f, 229.113907f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( AmdaporKeepHard );