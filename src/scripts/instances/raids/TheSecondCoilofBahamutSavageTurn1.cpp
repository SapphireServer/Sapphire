#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheSecondCoilofBahamutSavageTurn1 : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSecondCoilofBahamutSavageTurn1() : Sapphire::ScriptAPI::InstanceContentScript( 30012 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 4614306, 4614318, 5, { -120.168602f, 11.010820f, -99.074913f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -120.168602, 13.010820, -102.074913 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -120.158798, 13.010820, -96.074913 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -117.168602, 13.010820, -99.071022 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -123.168602, 13.010820, -99.063934 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -122.268600, 13.010820, -101.174911 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -118.068604, 13.010820, -96.974915 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -118.068604, 13.010820, -101.174911 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -122.268600, 13.010820, -96.974915 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4614319, 4, { -131.611206f, 9.156082f, -82.660057f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2001269, 4544126, 4616653, 4, { -137.669403f, 9.502172f, -11.353470f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -140.437973, 12.271631, -3.777349 }, -1.271623, 0.558808, 8.528957, 18.952700 );

    pEObj = instance.addEObj( "Destination", 2002372, 4579467, 4616654, 4, { -171.978897f, -49.907219f, -10.220380f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -190.436691, -50.067837, -2.492164 }, -0.470745, 1.000000, 11.434140, 18.946760 );

    pEObj = instance.addEObj( "sgpl_f1b2_bosswall", 2002872, 4616656, 4616657, 4, { -248.873596f, 10.236450f, 33.155060f }, 1.000000f, -0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -248.885788, 13.230326, 33.155060 }, -0.000000, 5.985300, 16.916611, 0.750000 );

    pEObj = instance.addEObj( "unknown_5", 2002735, 0, 4616659, 4, { -246.919006f, 9.938496f, 34.239399f }, 1.000000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2003012, 0, 4620921, 4, { -266.882690f, 10.421330f, 43.491699f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2003043, 0, 4620922, 4, { -261.309113f, 10.383500f, 37.739429f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2003044, 0, 4620923, 4, { -259.553802f, 10.421330f, 31.442730f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2003045, 0, 4620924, 4, { -262.154510f, 10.421330f, 23.808010f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Allaganterminal", 2003416, 4664435, 4651251, 4, { -314.106995f, 9.414734f, 43.198238f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char", 2003421, 4651262, 4651263, 4, { -292.780701f, 10.351920f, 39.414989f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -292.780701, 16.195366, 39.414989 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "unknown_6", 2003428, 4615269, 4663845, 4, { -120.556702f, 8.820233f, -76.764412f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheSecondCoilofBahamutSavageTurn1 );