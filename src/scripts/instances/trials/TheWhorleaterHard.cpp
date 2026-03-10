#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheWhorleaterHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWhorleaterHard() : Sapphire::ScriptAPI::InstanceContentScript( 20017 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 4600244, 4600249, 5, { 2.559847f, 0.025694f, 16.605810f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 2.559847, 2.025694, 13.605810 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.569650, 2.025694, 19.605810 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 5.559847, 2.025694, 16.609701 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -0.440153, 2.025694, 16.616787 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.459847, 2.025694, 14.505810 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 4.659847, 2.025694, 18.705811 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 4.659847, 2.025694, 14.505810 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.459847, 2.025694, 18.705811 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "unknown_0", 2003496, 4600311, 4600282, 4, { 4.240293f, 0.025694f, 2.306607f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2003497, 4600310, 4600283, 4, { 0.072974f, 0.025694f, 3.729535f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Elementalconverter", 2003498, 4600308, 4600284, 4, { -0.068011f, 0.025694f, 18.829760f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2003499, 4600477, 4600356, 4, { -0.427824f, 0.025694f, -1.602400f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2003503, 4536477, 4600361, 4, { -4.721506f, 0.025694f, -0.558033f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 4600461, 4, { 0.000000f, 0.025694f, -15.000000f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheWhorleaterHard );