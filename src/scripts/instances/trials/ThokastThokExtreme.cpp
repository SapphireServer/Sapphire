#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class ThokastThokExtreme : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThokastThokExtreme() : Sapphire::ScriptAPI::InstanceContentScript( 20032 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5774826, 5774827, 5, { -4.440430f, -0.015320f, 14.846980f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -4.440193, 1.968058, 11.871604 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -4.430756, 1.968343, 17.822166 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -1.465054, 1.968058, 14.850886 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -7.415617, 1.968344, 14.857628 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -6.522932, 1.968201, 12.764089 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -2.357738, 1.968201, 16.929682 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -2.357538, 1.968001, 12.764288 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -6.523131, 1.968400, 16.929482 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5774828, 4, { -0.068703f, -0.000001f, -13.884950f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2005385, 5674976, 5836589, 4, { -1.192890f, 0.000000f, 17.474220f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2005386, 5675419, 5836590, 4, { -13.222250f, 0.000000f, 12.212180f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2005387, 5675420, 5836591, 4, { -18.468269f, 0.000000f, 0.628434f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2005388, 5675421, 5836592, 4, { -13.285940f, 0.000000f, -12.470450f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2005389, 5675422, 5836593, 4, { 0.342176f, 0.000000f, -18.571230f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2005390, 5675423, 5836594, 4, { 12.720200f, 0.000000f, -12.658900f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2005391, 5675424, 5836595, 4, { 17.782970f, 0.000000f, -0.534297f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2005392, 5687664, 5836596, 4, { 13.452240f, 0.000000f, 12.733450f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2005393, 5797622, 5836597, 4, { -8.704693f, 0.000000f, 1.700043f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2005394, 5797549, 5836598, 4, { -1.334651f, 0.000000f, -2.316425f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2005385, 5674976, 5837553, 4, { 3.622319f, -0.000001f, 15.464100f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2005386, 5675419, 5837555, 4, { -11.612120f, -0.015320f, 13.595760f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2005387, 5675420, 5837556, 4, { -17.196960f, -0.015320f, 2.304016f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_13", 2005388, 5675421, 5837557, 4, { -13.697780f, 0.000000f, -10.715490f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2005389, 5675422, 5837558, 4, { -2.138674f, 0.000000f, -16.784149f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_15", 2005390, 5675423, 5837559, 4, { 12.378810f, 0.000000f, -10.929330f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2005391, 5675424, 5837560, 4, { 17.679670f, 0.000000f, 1.168503f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2005392, 5687664, 5837561, 4, { 12.017570f, 0.000000f, 13.670370f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_18", 2005393, 5797622, 5838026, 4, { -10.360960f, -0.015320f, 2.975464f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_19", 2005394, 5797549, 5838027, 4, { -9.475891f, -0.015320f, 4.837097f }, 0.991760f, 0.000048f, 0 ); 


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

EXPOSE_SCRIPT( ThokastThokExtreme );