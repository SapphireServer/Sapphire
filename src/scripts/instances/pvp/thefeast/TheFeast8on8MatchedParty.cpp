#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheFeast8on8MatchedParty : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFeast8on8MatchedParty() : Sapphire::ScriptAPI::InstanceContentScript( 40007 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "unknown_6", 2006818, 6215082, 6173800, 4, { 91.840202f, 8.505663f, 0.062604f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 79.939461, 16.440315, 0.061653 }, -3.141545, 0.099176, 8.132435, 7.041498 );
    pEObj->addCollisionBox( { 103.741707, 16.439175, 0.062793 }, -3.141545, 0.099176, 8.132435, 7.041498 );
    pEObj->addCollisionBox( { 85.836090, 10.489970, 10.475704 }, 0.523647, 6.942322, 11.901124, 0.099176 );
    pEObj->addCollisionBox( { 97.843506, 10.489395, 10.476280 }, -0.523551, 6.942322, 11.901124, 0.099176 );
    pEObj->addCollisionBox( { 97.844505, 10.488397, -10.350687 }, 0.523647, 6.942322, 11.901124, 0.099176 );
    pEObj->addCollisionBox( { 85.837090, 10.488972, -10.351263 }, -0.523551, 6.942322, 11.901124, 0.099176 );

    pEObj = instance.addEObj( "unknown_5", 2006819, 6215081, 6173801, 4, { -91.867523f, 8.505664f, -0.043211f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -103.867523, 16.505665, -0.043212 }, 3.141593, 0.100000, 8.200000, 7.100000 );
    pEObj->addCollisionBox( { -79.867523, 16.505665, -0.043212 }, 3.141593, 0.100000, 8.200000, 7.100000 );
    pEObj->addCollisionBox( { -97.921112, 10.505664, 10.456789 }, 0.523599, 7.000000, 12.000000, 0.100000 );
    pEObj->addCollisionBox( { -85.813934, 10.505664, 10.456789 }, -0.523599, 7.000000, 12.000000, 0.100000 );
    pEObj->addCollisionBox( { -85.813934, 10.505664, -10.543211 }, 0.523599, 7.000000, 12.000000, 0.100000 );
    pEObj->addCollisionBox( { -97.921112, 10.505664, -10.543211 }, -0.523599, 7.000000, 12.000000, 0.100000 );

    pEObj = instance.addEObj( "unknown_0", 2006820, 0, 6173833, 4, { -20.356541f, 0.081192f, -7.018244f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2006821, 0, 6173834, 4, { -20.607441f, 0.090943f, -2.040527f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2006822, 0, 6173835, 4, { -21.144119f, 0.090943f, 4.589552f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2006823, 0, 6173836, 4, { -19.463131f, 0.084362f, 9.633539f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2006824, 0, 6173871, 4, { -24.609461f, 0.090945f, 3.987549f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_collison_only", 2002618, 6220113, 6220114, 4, { -80.871353f, 0.833291f, -0.275824f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -80.871353, 0.833291, -0.275824 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_collison_only_1", 2002618, 6220117, 6220118, 4, { 76.127296f, 0.920299f, 0.296099f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 76.127296, 0.920299, 0.296099 }, -0.000000, 1.000000, 1.000000, 1.000000 );


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

EXPOSE_SCRIPT( TheFeast8on8MatchedParty );