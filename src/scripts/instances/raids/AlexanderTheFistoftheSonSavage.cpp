#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class AlexanderTheFistoftheSonSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheFistoftheSonSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30034 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 6177861, 6177864, 5, { 0.000000f, -60.199001f, 70.921097f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 0.000000, -58.199001, 67.921097 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.009802, -58.199001, 73.921097 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 3.000000, -58.199001, 70.924988 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -3.000000, -58.199001, 70.932076 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.100000, -58.199001, 68.821098 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.100000, -58.199001, 73.021095 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.100000, -58.199001, 68.821098 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.100000, -58.199001, 73.021095 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 6177865, 4, { 1.189643f, -53.337769f, 57.917198f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2002587, 0, 6179760, 4, { 0.000000f, -7.796605f, -27.253839f }, 1.400000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2002872, 6179766, 6179763, 4, { 0.048718f, -8.000000f, -25.550190f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.048718, -5.500000, -25.550190 }, -0.000000, 15.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 6179771, 6179770, 4, { 0.348718f, -8.000000f, -62.819778f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.348718, -5.500000, -62.819778 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 6179774, 6179773, 4, { 0.000000f, -18.000000f, -86.751549f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.000000, -15.500000, -86.751549 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2002735, 0, 6179786, 4, { 0.000000f, -18.000000f, -88.696098f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2006105, 6185484, 6183173, 4, { 0.000000f, -58.108219f, 65.176361f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6183174, 4, { -10.159560f, -10.000000f, -208.556000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2006093, 0, 6183193, 4, { -0.030479f, -18.000000f, -87.654160f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance_1", 2000182, 6184198, 6184200, 5, { 4.589292f, -3.826589f, 1.082808f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 4.589292, -1.826589, -1.917192 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 4.599094, -1.826589, 4.082808 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 7.589292, -1.826589, 1.086699 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 1.589292, -1.826589, 1.093784 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.489292, -1.826589, -1.017192 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 6.689292, -1.826589, 3.182808 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 6.689292, -1.826589, -1.017192 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.489292, -1.826589, 3.182808 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut_1", 2000700, 0, 6184201, 4, { 3.135107f, -6.123573f, -3.436843f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2006105, 6198124, 6184204, 4, { 4.362909f, -6.098227f, -3.232224f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2004367, 0, 6210648, 4, { 0.000000f, -10.000000f, -206.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2004368, 0, 6210649, 4, { 16.000000f, -10.000000f, -190.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2004369, 0, 6210650, 4, { -16.000000f, -10.000000f, -190.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2004575, 0, 6210651, 4, { 0.000000f, -10.000000f, -174.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_d2a0_a5_spry4", 2004870, 6200506, 6210667, 4, { -0.400928f, -10.000000f, -198.953598f }, 1.000000f, 0.000000f, 0 ); 
    // States -> heal_rdy (id: 5) heal_on2rdy (id: 7) heal_on (id: 9) heal_rdy2on (id: 11) heal_end (id: 13) heal_2end (id: 15) heal_wait (id: 17) heal_wait2rdy (id: 19) 

    pEObj = instance.addEObj( "sgbg_d2a0_a5_spry3", 2005111, 6200497, 6210668, 4, { 9.766629f, -10.000000f, -190.029099f }, 1.000000f, 0.000000f, 0 ); 
    // States -> pow_rdy (id: 3) pow_on2rdy (id: 5) pow_on (id: 7) pow_rdy2on (id: 9) pow_end (id: 11) pow_2end (id: 13) pow_wait (id: 15) pow_wait2rdy (id: 17) 

    pEObj = instance.addEObj( "Koboldkey", 2006468, 6200507, 6210669, 4, { -9.431794f, -10.000000f, -190.472397f }, 1.000000f, 0.000000f, 0 ); 
    // States -> spd_rdy (id: 5) spd_on2rdy (id: 7) spd_on (id: 9) spd_rdy2on (id: 11) spd_end (id: 13) spd_2end (id: 15) spd_wait (id: 17) spd_wait2rdy (id: 19) 

    pEObj = instance.addEObj( "Koboldkey_1", 2006469, 6200508, 6210670, 4, { 0.206919f, -10.000000f, -180.011597f }, 1.000000f, 0.000000f, 0 ); 
    // States -> invis_rdy (id: 2) invis_on2rdy (id: 3) invis_on (id: 4) invis_rdy2on (id: 5) invis_end (id: 6) invis_2end (id: 7) invis_wait (id: 8) invis_wait2rdy (id: 9) 

    pEObj = instance.addEObj( "unknown_4", 2004363, 0, 6215428, 4, { 0.000000f, -10.000000f, -190.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2006965, 6200579, 6215624, 4, { 0.000000f, -10.000000f, -190.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit_1", 2005313, 6180367, 6238464, 4, { -8.545354f, -9.800000f, -209.792007f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( AlexanderTheFistoftheSonSavage );