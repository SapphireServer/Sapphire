#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class ThePalaceoftheDeadFloors3140 : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThePalaceoftheDeadFloors3140() : Sapphire::ScriptAPI::InstanceContentScript( 60004 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "sgvf_w_lvd_b0959", 2000608, 6367892, 6367918, 4, { -300.000000f, 0.000000f, -225.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_on2off (id: 4) vf_bextwall_off (id: 10) 
    pEObj->addCollisionBox( { -300.000000, 2.500000, -225.000000 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0959_1", 2002872, 6392196, 6392197, 4, { 300.000000f, 0.000000f, 374.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_on2off (id: 4) vf_bextwall_off (id: 10) 
    pEObj->addCollisionBox( { 300.000000, 2.500000, 374.000000 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_0", 2007351, 6277715, 6396038, 4, { 300.036102f, 0.000000f, 373.916687f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2007352, 6394671, 6396039, 4, { 307.159912f, 0.000000f, 370.556702f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2007353, 6394677, 6396040, 4, { 305.303894f, 0.000000f, 380.231415f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2007354, 6394673, 6396041, 4, { 296.024109f, -0.000000f, 381.100189f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2007355, 6394675, 6396042, 4, { 291.561890f, 0.000000f, 372.412689f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2007356, 6394674, 6396043, 4, { 298.511902f, 0.000000f, 366.134003f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( ThePalaceoftheDeadFloors3140 );