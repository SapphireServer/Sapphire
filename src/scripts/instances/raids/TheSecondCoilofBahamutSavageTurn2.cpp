#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheSecondCoilofBahamutSavageTurn2 : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSecondCoilofBahamutSavageTurn2() : Sapphire::ScriptAPI::InstanceContentScript( 30013 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Ripenedbulb", 2003293, 4646806, 4646901, 4, { -449.999908f, 800.027222f, 69.995399f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2003299, 4646804, 4646902, 4, { -449.999908f, 800.027222f, 69.995399f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2003311, 4646803, 4646903, 4, { -449.999908f, 800.027222f, 69.995354f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 4646962, 4646963, 5, { -358.417694f, -270.655487f, -0.875555f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -358.417450, -268.672119, -3.850931 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -358.408020, -268.671814, 2.099631 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -355.442322, -268.672119, -0.871649 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -361.392883, -268.671814, -0.864907 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -360.500183, -268.671967, -2.958447 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -356.334991, -268.671967, 1.207146 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -356.334808, -268.672180, -2.958247 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -360.500397, -268.671753, 1.206947 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4646964, 4, { -384.512085f, -270.435699f, -2.731445f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2002469, 4646048, 4646968, 4, { -447.239197f, 799.923584f, 70.054077f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_f1b2_bosswall", 2002872, 4646969, 4646970, 4, { -449.981689f, 801.188416f, 47.036610f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -449.993652, 804.157593, 47.036469 }, 0.000048, 5.935983, 16.777224, 0.743820 );

    pEObj = instance.addEObj( "unknown_4", 2002735, 0, 4646971, 4, { -449.981689f, 800.000000f, 47.625530f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_colwithnavi", 2002470, 4646986, 4646972, 4, { -448.371613f, 800.000000f, 20.807449f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -448.371613, 800.000000, 20.807449 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_3", 2002471, 4646049, 4646975, 4, { -372.196899f, -270.740997f, -1.014158f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char", 2002472, 4646987, 4646981, 4, { -449.121704f, 800.000000f, 91.049332f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -449.121704, 805.843445, 91.049332 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "Innerbulkhead", 2003415, 0, 4646988, 4, { -375.434814f, -268.802399f, -0.859896f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Allaganterminal", 2003417, 4682781, 4651252, 4, { -450.001099f, 799.969971f, 143.447495f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheSecondCoilofBahamutSavageTurn2 );