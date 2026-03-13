#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class AlexanderTheArmoftheFatherSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheArmoftheFatherSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30027 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5787948, 5787945, 5, { -0.015320f, -0.015320f, 43.037189f }, 0.778198f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -0.015133, 1.540965, 40.702522 }, 0.000048, 1.011658, 3.112793, 0.194550 );
    pEObj->addCollisionBox( { -0.007729, 1.541188, 45.371712 }, 0.000048, 1.011658, 3.112793, 0.194550 );
    pEObj->addCollisionBox( { 2.319349, 1.540965, 43.040253 }, -1.570403, 1.011658, 3.112793, 0.194550 );
    pEObj->addCollisionBox( { -2.349840, 1.541189, 43.045544 }, -1.570403, 1.011658, 3.112793, 0.194550 );
    pEObj->addCollisionBox( { -1.649383, 1.541077, 41.402821 }, -0.785350, 1.089477, 3.112793, 0.194550 );
    pEObj->addCollisionBox( { 1.618893, 1.541077, 44.671410 }, -0.785350, 1.089477, 3.112793, 0.194550 );
    pEObj->addCollisionBox( { 1.619049, 1.540920, 41.402977 }, 0.785446, 1.089477, 3.112793, 0.194550 );
    pEObj->addCollisionBox( { -1.649540, 1.541233, 44.671253 }, 0.785446, 1.089477, 3.112793, 0.194550 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5787947, 4, { 3.252589f, 0.000000f, 30.523800f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2002735, 0, 5787961, 4, { 58.000000f, -0.000003f, -20.943159f }, 0.600000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5787963, 5787962, 4, { 58.043961f, -0.000054f, -20.107550f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 58.043961, 2.499946, -20.107550 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5787965, 4, { 100.941902f, -10.500000f, -63.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2002872, 0, 5787966, 4, { 87.814133f, -9.000000f, -61.109859f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2005314, 5878653, 5788019, 4, { 17.839520f, 42.000000f, 14.681990f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2005400, 0, 5857859, 4, { 39.638931f, -9.000000f, -67.173187f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2005911, 5814854, 5894413, 4, { 58.000000f, -8.999999f, -63.000000f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 90.324997, -1.999999, -63.000000 }, -0.000000, 0.500000, 8.000000, 2.000000 );

    pEObj = instance.addEObj( "unknown_2", 2006094, 5864098, 5908325, 4, { 58.027489f, -0.000134f, -20.193150f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_d2a2_b0721", 2006095, 5905878, 5908489, 4, { 58.000000f, -9.000000f, -63.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> thunder_off (id: 2) thunder_on2off (id: 3) thunder_on (id: 4) thunder_off2on (id: 5) 

    pEObj = instance.addEObj( "Entrance_1", 2000182, 5911899, 5911893, 5, { 58.000000f, -0.000049f, -11.175000f }, 0.800000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 58.000000, 1.599951, -13.575001 }, -0.000000, 1.040000, 3.200000, 0.200000 );
    pEObj->addCollisionBox( { 58.007843, 1.599951, -8.775000 }, -0.000000, 1.040000, 3.200000, 0.200000 );
    pEObj->addCollisionBox( { 60.400002, 1.599951, -11.171887 }, -1.570451, 1.040000, 3.200000, 0.200000 );
    pEObj->addCollisionBox( { 55.599998, 1.599951, -11.166219 }, -1.570451, 1.040000, 3.200000, 0.200000 );
    pEObj->addCollisionBox( { 56.320000, 1.599951, -12.855000 }, -0.785398, 1.120000, 3.200000, 0.200000 );
    pEObj->addCollisionBox( { 59.680000, 1.599951, -9.495000 }, -0.785398, 1.120000, 3.200000, 0.200000 );
    pEObj->addCollisionBox( { 59.680000, 1.599951, -12.855000 }, 0.785398, 1.120000, 3.200000, 0.200000 );
    pEObj->addCollisionBox( { 56.320000, 1.599951, -9.495000 }, 0.785398, 1.120000, 3.200000, 0.200000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_colwithnavi", 2000608, 5911895, 5911926, 4, { 58.000000f, 0.841694f, -1.705941f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 58.000000, 0.841694, -1.705941 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "sgpl_d2a3_wall", 2005314, 6048829, 6051134, 4, { 17.839520f, 42.000000f, 14.681990f }, 1.000000f, 0.000000f, 0 ); 
    // States -> wall_on (id: 24) wall_off (id: 25) 
    pEObj->addCollisionBox( { 17.839520, 44.500000, 14.681990 }, -0.000000, 3.400000, 3.000000, 0.100000 );


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

EXPOSE_SCRIPT( AlexanderTheArmoftheFatherSavage );