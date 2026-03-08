#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class ContainmentBayS1T7 : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ContainmentBayS1T7() : Sapphire::ScriptAPI::InstanceContentScript( 20037 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 6173855, 6173856, 5, { -0.006781f, 0.052026f, 13.691250f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -0.006781, 2.052026, 10.691250 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.003022, 2.052026, 16.691250 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.993219, 2.052026, 13.695141 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -3.006781, 2.052026, 13.702226 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.106781, 2.052026, 11.591249 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.093219, 2.052026, 15.791250 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.093219, 2.052026, 11.591249 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.106781, 2.052026, 15.791250 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6173857, 4, { 0.000000f, 0.000000f, -16.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818", 2006840, 6175219, 6175230, 4, { 0.000000f, 0.000000f, -10.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818_1", 2006841, 6175220, 6175231, 4, { 7.071130f, 0.000000f, -7.071100f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818_2", 2006842, 6175221, 6175232, 4, { 10.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818_3", 2006843, 6175222, 6175233, 4, { 7.071130f, 0.000000f, 7.071130f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818_4", 2006844, 6175223, 6175234, 4, { 0.000000f, 0.000000f, 10.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818_5", 2006845, 6175224, 6175235, 4, { -7.071130f, 0.000000f, 7.071100f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818_6", 2006846, 6175225, 6175236, 4, { -10.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818_7", 2006847, 6175226, 6175237, 4, { -7.071130f, 0.000000f, -7.071130f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 

    pEObj = instance.addEObj( "unknown_0", 2006837, 6174136, 6175365, 4, { 0.000000f, 0.052026f, -19.799999f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2006839, 6164929, 6175366, 4, { 0.000000f, 0.002934f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2006838, 6171564, 6175495, 4, { 0.116409f, 0.002934f, -0.768936f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2006840, 6175957, 6175496, 4, { -0.836018f, 0.050520f, -2.055523f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_a2fd_b0818_8", 2006983, 6219989, 6219992, 4, { 0.000000f, 0.043380f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> doom_hide (id: 2) doom_show1 (id: 3) doom_show_anim1 (id: 4) doom_show2 (id: 5) doom_show_anim2 (id: 6) doom_show3 (id: 7) doom_show_anim3 (id: 8) doom_hide_anim (id: 9) 


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

EXPOSE_SCRIPT( ContainmentBayS1T7 );