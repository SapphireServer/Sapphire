#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class ThePalaceoftheDeadFloors1120 : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThePalaceoftheDeadFloors1120() : Sapphire::ScriptAPI::InstanceContentScript( 60002 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "sgvf_w_lvd_b0959", 2000608, 6353850, 6353881, 4, { -300.000000f, 0.000026f, -237.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_on2off (id: 4) vf_bextwall_off (id: 10) 
    pEObj->addCollisionBox( { -300.000000, 2.500026, -237.000000 }, -0.000000, 7.500000, 4.000000, 0.750000 );


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

EXPOSE_SCRIPT( ThePalaceoftheDeadFloors1120 );