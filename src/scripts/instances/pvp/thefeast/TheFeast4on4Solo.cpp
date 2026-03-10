#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheFeast4on4Solo : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFeast4on4Solo() : Sapphire::ScriptAPI::InstanceContentScript( 40010 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "unknown_0", 2006819, 6218908, 6212538, 4, { -89.012909f, 8.477110f, -0.326954f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -101.012909, 16.477110, -0.326955 }, 3.141593, 0.100000, 8.200000, 7.100000 );
    pEObj->addCollisionBox( { -77.012909, 16.477110, -0.326955 }, 3.141593, 0.100000, 8.200000, 7.100000 );
    pEObj->addCollisionBox( { -95.066498, 10.477110, 10.173046 }, 0.523599, 7.000000, 12.000000, 0.100000 );
    pEObj->addCollisionBox( { -82.959320, 10.477110, 10.173046 }, -0.523599, 7.000000, 12.000000, 0.100000 );
    pEObj->addCollisionBox( { -82.959320, 10.477110, -10.826954 }, 0.523599, 7.000000, 12.000000, 0.100000 );
    pEObj->addCollisionBox( { -95.066498, 10.477110, -10.826954 }, -0.523599, 7.000000, 12.000000, 0.100000 );

    pEObj = instance.addEObj( "unknown_1", 2006818, 6218909, 6212542, 4, { 95.872437f, 8.468750f, -0.320496f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 83.971695, 16.403402, -0.321447 }, -3.141545, 0.099176, 8.132435, 7.041498 );
    pEObj->addCollisionBox( { 107.773941, 16.402262, -0.320306 }, -3.141545, 0.099176, 8.132435, 7.041498 );
    pEObj->addCollisionBox( { 89.868324, 10.453057, 10.092605 }, 0.523647, 6.942322, 11.901124, 0.099176 );
    pEObj->addCollisionBox( { 101.875740, 10.452482, 10.093181 }, -0.523551, 6.942322, 11.901124, 0.099176 );
    pEObj->addCollisionBox( { 101.876740, 10.451484, -10.733787 }, 0.523647, 6.942322, 11.901124, 0.099176 );
    pEObj->addCollisionBox( { 89.869324, 10.452059, -10.734363 }, -0.523551, 6.942322, 11.901124, 0.099176 );

    pEObj = instance.addEObj( "unknown_2", 2006820, 0, 6212561, 4, { -20.356541f, 0.081192f, -7.018244f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2006821, 0, 6212562, 4, { -20.607441f, 0.090943f, -2.040527f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2006822, 0, 6212563, 4, { -21.144119f, 0.090943f, 4.589552f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2006823, 0, 6212564, 4, { -19.463131f, 0.084362f, 9.633539f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2006824, 0, 6212565, 4, { -24.609461f, 0.090945f, 3.987549f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_collison_only", 2002618, 6220121, 6220122, 4, { -78.605072f, 0.920299f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -78.605072, 0.920299, 0.000000 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_collison_only_1", 2002618, 6220123, 6220124, 4, { 79.651703f, 0.811267f, -0.306571f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 79.651703, 0.811267, -0.306571 }, 0.000048, 0.991760, 0.991760, 0.991760 );


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

EXPOSE_SCRIPT( TheFeast4on4Solo );