#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheMinstrelsBalladUltimasBane : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheMinstrelsBalladUltimasBane() : Sapphire::ScriptAPI::InstanceContentScript( 20013 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 4391941, 4391942, 5, { -6.677185f, 0.068419f, 12.835030f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -6.677185, 2.068419, 9.835030 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -6.667383, 2.068419, 15.835030 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -3.677185, 2.068419, 12.838921 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -9.677185, 2.068419, 12.846005 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -8.777185, 2.068419, 10.735029 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -4.577185, 2.068419, 14.935030 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -4.577185, 2.068419, 10.735029 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -8.777185, 2.068419, 14.935030 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 4391943, 4, { 0.000000f, 0.000000f, -16.316700f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2002745, 4391076, 4391963, 4, { 7.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2002746, 4391074, 4391964, 4, { -7.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2002747, 4976890, 4391965, 4, { 0.000000f, -0.131581f, -18.566719f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2002748, 4391072, 4391966, 4, { 17.676531f, -0.144861f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2002749, 4976892, 4391967, 4, { 0.000000f, 0.000000f, 17.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2002750, 4976891, 4391968, 4, { -17.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheMinstrelsBalladUltimasBane );