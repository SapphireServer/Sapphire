#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheAurumVale : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheAurumVale() : Sapphire::ScriptAPI::InstanceContentScript( 5 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4237107, 4, { 151.384796f, -1.596331f, 86.655884f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 4237108, 4, { -410.069702f, -33.063400f, -116.395897f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 4246303, 4240234, 5, { 158.558304f, -0.023911f, 81.249123f }, 1.000000f, 1.503130f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 161.551437, 1.976089, 81.046280 }, 1.503130, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 155.565826, 1.976088, 81.461746 }, 1.503130, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 158.757263, 1.976089, 84.242523 }, -0.067321, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 158.344513, 1.976088, 78.256729 }, -0.067321, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 160.511505, 1.976089, 79.011940 }, 0.717731, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 156.605103, 1.976089, 83.486305 }, 0.717731, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 160.795486, 1.976089, 83.202324 }, 2.288528, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 156.321121, 1.976088, 79.295921 }, 2.288528, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "unknown_0", 2000272, 3643401, 4248770, 4, { -44.571659f, -16.218571f, -112.108101f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -44.184517, -13.498190, -107.124153 }, 0.000048, 2.479401, 5.308397, 1.388464 );

    pEObj = instance.addEObj( "unknown_1", 2000273, 4248891, 4248777, 4, { -333.089203f, -32.733212f, -161.730392f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -332.702057, -30.012831, -156.746445 }, 0.000048, 2.479401, 5.308397, 1.388464 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2000779, 4259184, 4249126, 4, { 58.213131f, -9.300029f, -0.564636f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 58.213249, -6.820628, -0.564755 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094", 2000780, 4259186, 4249127, 4, { 58.539280f, -8.801913f, 4.282087f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2000781, 4259189, 4249128, 4, { -127.598099f, -30.310749f, -139.019302f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -127.598099, -27.810749, -139.019302 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094_1", 2000782, 4259188, 4249129, 4, { -126.660500f, -30.285540f, -134.096695f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2000783, 4246452, 4249130, 4, { -374.789612f, -32.153561f, -140.808197f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -374.789612, -29.653561, -140.808197 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094_2", 2000784, 4246451, 4249131, 4, { -372.679901f, -32.341091f, -136.354401f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2000785, 4259185, 4259181, 4, { 34.952770f, -9.096572f, -23.527361f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 34.952770, -6.596572, -23.527361 }, -0.000000, 15.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2000786, 4259190, 4259183, 4, { -169.906296f, -27.704550f, -169.152496f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -169.906296, -25.204550, -169.152496 }, -0.000000, 7.500000, 4.000000, 0.750000 );


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

EXPOSE_SCRIPT( TheAurumVale );