#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class SpecialEventII : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SpecialEventII() : Sapphire::ScriptAPI::InstanceContentScript( 20015 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5778232, 5778233, 5, { -26.139870f, 0.000001f, -0.197510f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -26.139870, 2.000001, -3.197510 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -26.130068, 2.000001, 2.802490 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -23.139870, 2.000001, -0.193620 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -29.139870, 2.000001, -0.186534 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -28.239870, 2.000001, -2.297510 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -24.039869, 2.000001, 1.902490 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -24.039869, 2.000001, -2.297510 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -28.239870, 2.000001, 1.902490 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5778234, 4, { -4.281307f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Magitekfieldgenerator", 2005541, 0, 5862372, 4, { -15.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Dragonkiller", 2005544, 0, 5862495, 4, { -13.000000f, 0.182584f, -17.700001f }, 1.000000f, 0.261799f, 0 ); 

    pEObj = instance.addEObj( "Dragonkiller_1", 2005545, 0, 5862496, 4, { -14.150000f, 0.168036f, 19.500000f }, 1.000000f, -0.087266f, 0 ); 

    pEObj = instance.addEObj( "sgbg_a2fa_a1_bsid2", 2005847, 5865535, 5887993, 4, { -5.185479f, 0.084680f, 0.234906f }, 1.000000f, 0.000000f, 0 ); 
    // States -> collision_on (id: 1) collision_off (id: 2) 

    pEObj = instance.addEObj( "sgbg_a2fa_a1_bare1", 2005958, 5898723, 5898727, 4, { -3.398252f, 0.016719f, -0.449336f }, 1.000000f, 0.000000f, 0 ); 
    // States -> stage_ba_hide (id: 1) stage_ba_show (id: 2) stage_ba_anim1 (id: 3) stage_ba_anim2 (id: 4) 

    pEObj = instance.addEObj( "unknown_0", 2005965, 5874950, 5898907, 4, { -14.475140f, 0.010675f, 5.614964f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( SpecialEventII );