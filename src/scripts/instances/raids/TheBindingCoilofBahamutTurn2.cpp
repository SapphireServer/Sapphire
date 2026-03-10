#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheBindingCoilofBahamutTurn2 : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheBindingCoilofBahamutTurn2() : Sapphire::ScriptAPI::InstanceContentScript( 30003 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000628, 4293644, 4293648, 5, { 0.852533f, 0.148087f, 20.254930f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 0.852533, 2.148087, 17.254930 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.862335, 2.148087, 23.254930 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 3.852532, 2.148087, 20.258821 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.147468, 2.148087, 20.265907 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -1.247467, 2.148087, 18.154930 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.952532, 2.148087, 22.354931 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.952532, 2.148087, 18.154930 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -1.247467, 2.148087, 22.354931 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "unknown_1", 2000640, 4092173, 4294915, 4, { -14.019790f, -0.010602f, 31.855391f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -14.019790, 10.556038, 31.855391 }, -0.000000, 5.500000, 20.455210, 1.328650 );

    pEObj = instance.addEObj( "unknown_2", 2000641, 4092174, 4294916, 4, { 15.101930f, -0.029503f, 31.798840f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 15.101930, 10.537137, 31.798840 }, -0.000000, 5.500000, 20.455210, 1.328650 );

    pEObj = instance.addEObj( "unknown_3", 2000638, 4092177, 4294917, 4, { -58.677170f, -18.016920f, 47.536171f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -58.679352, -11.661434, 47.536171 }, -0.000000, 5.502399, 15.791030, 1.300001 );

    pEObj = instance.addEObj( "unknown_4", 2000639, 4092181, 4294918, 4, { -27.060640f, -18.102751f, 58.292858f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -27.062820, -11.747265, 58.292858 }, -0.000000, 5.502399, 15.791030, 1.300001 );

    pEObj = instance.addEObj( "unknown_5", 2000642, 4092183, 4294919, 4, { 58.277191f, -20.996519f, 62.605671f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 58.275009, -14.641033, 62.605671 }, -0.000000, 5.502399, 15.791030, 1.300001 );

    pEObj = instance.addEObj( "unknown_6", 2000643, 4092178, 4294920, 4, { 30.274019f, -20.952881f, 58.602650f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 30.271839, -14.597395, 58.602650 }, -0.000000, 5.502399, 15.791030, 1.300001 );

    pEObj = instance.addEObj( "unknown_7", 2000644, 4092182, 4294922, 4, { 29.367611f, -41.975361f, 110.864998f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 29.352291, -36.565678, 110.849678 }, -0.000000, 5.490691, 14.767500, 1.300003 );

    pEObj = instance.addEObj( "unknown_8", 2000635, 4092184, 4294923, 4, { 0.539888f, -62.460609f, 100.908897f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 0.524569, -57.050926, 100.893578 }, -0.000000, 5.490691, 14.767500, 1.300003 );

    pEObj = instance.addEObj( "unknown_9", 2000636, 4092179, 4294924, 4, { -55.941719f, -38.998539f, 78.436340f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -55.943901, -32.643051, 78.436340 }, -0.000000, 5.502399, 15.791030, 1.300001 );

    pEObj = instance.addEObj( "unknown_10", 2000637, 4092180, 4294925, 4, { -51.528130f, -38.998749f, 109.805901f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -51.543449, -33.589066, 109.790581 }, -0.000000, 5.490691, 14.767500, 1.300003 );

    pEObj = instance.addEObj( "unknown_11", 2000645, 4092175, 4294927, 4, { 0.474554f, -65.943604f, 68.078178f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 0.474554, -55.376965, 68.078178 }, -0.000000, 5.500000, 20.455210, 1.328650 );

    pEObj = instance.addEObj( "sgpl_s1b2_bossline5", 2000676, 4306493, 4306497, 4, { 52.177799f, -21.010019f, 34.437031f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_s1b2_bosswall_r_2", 2000677, 4306494, 4306498, 4, { 51.183399f, -21.011810f, 34.504452f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 51.110603, -19.319441, 34.504452 }, -0.000000, 5.174669, 3.894603, 0.750000 );

    pEObj = instance.addEObj( "sgpl_s1b2_bossline3", 2000672, 4293655, 4306506, 4, { -51.865479f, -18.020941f, 35.080441f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_s1b2_bosswall_r_1", 2000673, 4293656, 4306507, 4, { -50.583679f, -18.020941f, 35.538212f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -50.655792, -16.342512, 35.538128 }, 0.000048, 5.132031, 3.862513, 0.743820 );

    pEObj = instance.addEObj( "sgpl_s1b2_bosswall_r", 2000671, 4306763, 4306767, 4, { -66.396652f, -38.998539f, 88.058296f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -66.469444, -37.306168, 88.058296 }, -0.000000, 5.174669, 3.894603, 0.750000 );

    pEObj = instance.addEObj( "sgpl_s1b2_bossline2", 2000670, 4306762, 4306768, 4, { -65.538063f, -38.998699f, 90.104332f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_s1b2_bosswall_r_3", 2000679, 4306772, 4306773, 4, { 60.934231f, -41.989620f, 101.246002f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 60.861435, -40.297249, 101.246002 }, -0.000000, 5.174669, 3.894603, 0.750000 );

    pEObj = instance.addEObj( "sgpl_s1b2_bossline6", 2000678, 4306771, 4306774, 4, { 59.622169f, -41.994068f, 98.767616f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_s1b2_bossline", 2000621, 4307578, 4306787, 4, { 0.106751f, -65.934273f, 82.291870f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_s1b2_bosswall", 2000622, 4307579, 4306788, 4, { -0.320496f, -65.934273f, 82.322388f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -0.320496, -65.934273, 82.322388 }, 0.000048, 8.182023, 31.736330, 0.503913 );
    pEObj->addCollisionBox( { 17.281153, -51.463383, 65.466957 }, -1.570403, 5.135211, 17.263790, 0.496942 );
    pEObj->addCollisionBox( { -17.896778, -51.504681, 79.539505 }, -1.570403, 6.639968, 17.307447, 0.512003 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094", 2000668, 4307413, 4307416, 4, { -16.838060f, -60.912392f, 116.477898f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 

    pEObj = instance.addEObj( "sgpl_s1b2_bosswall_c", 2000669, 4307414, 4307417, 4, { -16.655029f, -61.041161f, 117.352303f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -16.642632, -36.374950, 117.352303 }, -0.000000, 22.000000, 26.166210, 0.750000 );

    pEObj = instance.addEObj( "unknown_0", 2000680, 0, 4309233, 4, { -48.355518f, -38.578499f, 86.879211f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Allaganterminal", 2001161, 4107517, 4330622, 4, { -0.118857f, -102.612297f, 0.534058f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0249", 2000674, 4331576, 4331581, 4, { 0.736900f, 0.033629f, 31.115801f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_line_on (id: 10) vf_line_of (id: 11) 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2000675, 4331583, 4331582, 4, { 1.580210f, 0.032013f, 29.906660f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 1.580210, 2.532013, 29.906660 }, -0.000000, 15.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_12", 2001152, 4107515, 4373157, 4, { 2.090964f, 0.000001f, 22.575050f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheBindingCoilofBahamutTurn2 );