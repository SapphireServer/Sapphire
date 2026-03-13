#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheHowlingEye : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheHowlingEye() : Sapphire::ScriptAPI::InstanceContentScript( 20003 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000274, 4246117, 4247837, 5, { 0.506547f, -1.935848f, 14.110570f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 0.506547, 0.064152, 11.110570 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.516350, 0.064152, 17.110569 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 3.506547, 0.064152, 14.114461 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.493453, 0.064152, 14.121546 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -1.593453, 0.064152, 12.010571 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.606547, 0.064152, 16.210569 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.606547, 0.064152, 12.010571 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -1.593453, 0.064152, 16.210569 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Exit", 2000275, 0, 4247840, 4, { 1.078937f, -2.041544f, -18.363190f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_r1fa_a_rockcol", 2000646, 4256721, 4297334, 4, { -4.592406f, -1.261766f, 4.724565f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_r1fa_a_rockcol_1", 2000647, 4256725, 4297335, 4, { 7.587256f, -1.233237f, 6.169516f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_r1fa_a_rockcol_2", 2000648, 4256726, 4297338, 4, { -6.329784f, 3.332559f, -6.736721f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_r1fa_a_rockcol_3", 2000649, 4256727, 4297341, 4, { 5.895649f, 3.275768f, -6.217119f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2002689, 0, 4374462, 4, { -83.712677f, -0.871584f, -32.616779f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_r1fa_a_rockcol_4", 2000646, 4488538, 4488551, 4, { -7.000000f, 0.000000f, 7.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_r1fa_a_rockcol_5", 2000647, 4488545, 4488552, 4, { 7.000000f, 0.000000f, 7.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_r1fa_a_rockcol_6", 2000648, 4488546, 4488553, 4, { -7.000000f, 0.000000f, -7.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_r1fa_a_rockcol_7", 2000649, 4488548, 4488554, 4, { 7.000000f, 0.000000f, -7.000000f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheHowlingEye );