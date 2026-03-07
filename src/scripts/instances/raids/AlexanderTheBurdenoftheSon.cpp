#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class AlexanderTheBurdenoftheSon : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheBurdenoftheSon() : Sapphire::ScriptAPI::InstanceContentScript( 30033 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 6177907, 6177906, 5, { 0.000000f, 10.500000f, 19.500000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 0.000000, 12.500000, 16.500000 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.009802, 12.500000, 22.500000 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 3.000000, 12.500000, 19.503891 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -3.000000, 12.500000, 19.510977 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.100000, 12.500000, 17.400000 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.100000, 12.500000, 21.600000 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.100000, 12.500000, 17.400000 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.100000, 12.500000, 21.600000 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6184108, 4, { 0.000000f, 10.705920f, -21.985399f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2006984, 6164617, 6220708, 4, { -0.231898f, 10.500000f, -1.988388f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_d2a8_b0882", 2006989, 6234571, 6234569, 4, { 0.000000f, 10.500000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> brr_off (id: 2) brr_on2off (id: 3) brr_off2on (id: 5) 

    pEObj = instance.addEObj( "unknown_1", 2006974, 0, 6236690, 4, { -16.291439f, 10.500000f, 4.361944f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit_1", 2005313, 6076667, 6245483, 4, { 0.000000f, 10.500000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( AlexanderTheBurdenoftheSon );