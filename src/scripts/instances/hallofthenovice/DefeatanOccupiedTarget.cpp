#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class DefeatanOccupiedTarget : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  DefeatanOccupiedTarget() : Sapphire::ScriptAPI::InstanceContentScript( 15009 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "unknown_5", 2001403, 3968682, 3969282, 4, { 30.986059f, 0.993235f, 1.480142f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 30.986059, 5.993235, 2.080142 }, -0.000000, 6.000000, 6.000000, 0.300000 );

    pEObj = instance.addEObj( "unknown_6", 2001404, 3968585, 3969283, 4, { -31.243280f, 1.043213f, 1.580577f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -31.243280, 6.043213, 2.180577 }, -0.000000, 6.000000, 6.000000, 0.300000 );

    pEObj = instance.addEObj( "Entrance", 2000182, 6215534, 6215533, 5, { 44.100491f, 1.056062f, 1.068363f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 44.100491, 3.056062, -1.931637 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 44.110294, 3.056062, 4.068363 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 47.100491, 3.056062, 1.072254 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 41.100491, 3.056062, 1.079339 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 42.000492, 3.056062, -1.031637 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 46.200489, 3.056062, 3.168363 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 46.200489, 3.056062, -1.031637 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 42.000492, 3.056062, 3.168363 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "unknown_0", 2007001, 0, 6235230, 4, { -5.135936f, -0.986339f, -0.059807f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2007004, 0, 6237020, 4, { -6.501123f, -0.986346f, 2.121102f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2007005, 0, 6237021, 4, { -5.178086f, -0.986341f, -0.227772f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2007006, 0, 6237022, 4, { -7.272448f, -0.986346f, -2.204096f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2007007, 6216275, 6237739, 4, { -30.849630f, 0.697522f, -1.415699f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -30.849630, 5.697522, -0.815699 }, -0.000000, 6.000000, 6.000000, 0.300000 );

    pEObj = instance.addEObj( "Gatelever", 2007008, 0, 6237744, 4, { -31.199289f, 1.850766f, -7.087492f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( DefeatanOccupiedTarget );