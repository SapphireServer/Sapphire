#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class AlexanderTheBurdenoftheFather : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheBurdenoftheFather() : Sapphire::ScriptAPI::InstanceContentScript( 30024 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5788043, 5788042, 5, { -0.001985f, 10.900000f, 20.255680f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -0.001985, 12.900000, 17.255680 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.007818, 12.900000, 23.255680 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.998015, 12.900000, 20.259571 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -3.001985, 12.900000, 20.266657 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.101985, 12.900000, 18.155680 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.098015, 12.900000, 22.355680 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.098015, 12.900000, 18.155680 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.101985, 12.900000, 22.355680 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5788044, 4, { -0.015320f, 10.561610f, -23.025881f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2005494, 5863691, 5858213, 4, { 102.000000f, 43.646099f, 16.000000f }, 0.991760f, 0.000048f, 0 ); 


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

EXPOSE_SCRIPT( AlexanderTheBurdenoftheFather );