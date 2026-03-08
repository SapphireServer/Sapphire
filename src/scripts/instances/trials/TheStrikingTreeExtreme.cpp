#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheStrikingTreeExtreme : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheStrikingTreeExtreme() : Sapphire::ScriptAPI::InstanceContentScript( 20023 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 4712008, 4712006, 5, { 5.026201f, 74.994751f, 16.039301f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 5.026201, 76.994751, 13.039301 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 5.036003, 76.994751, 19.039301 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 8.026201, 76.994751, 16.043192 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.026201, 76.994751, 16.050278 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.926201, 76.994751, 13.939301 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 7.126201, 76.994751, 18.139301 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 7.126201, 76.994751, 13.939301 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.926201, 76.994751, 18.139301 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 4712009, 4, { 0.000000f, 75.000000f, -7.671923f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheStrikingTreeExtreme );