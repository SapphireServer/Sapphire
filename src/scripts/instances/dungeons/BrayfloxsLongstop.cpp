#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class BrayfloxsLongstop : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  BrayfloxsLongstop() : Sapphire::ScriptAPI::InstanceContentScript( 8 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "unknown_1", 2001461, 0, 3999844, 4, { 142.567200f, -1.266762f, 67.804497f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "RunstopHeadgate", 2001462, 3996541, 3999853, 4, { 105.920601f, 1.745684f, 11.445460f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 105.920601, 4.467851, 11.523150 }, -0.000000, 1.331574, 2.714589, 0.260560 );

    pEObj = instance.addEObj( "RunstopGutgate", 2001463, 3970152, 3999858, 4, { 113.391296f, -0.849704f, -33.166710f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 113.391296, 1.872463, -33.089020 }, -0.000000, 1.331574, 2.714589, 0.260560 );

    pEObj = instance.addEObj( "RunstopBackgate", 2001464, 3970154, 3999862, 4, { -19.424801f, 7.919373f, -71.122383f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -19.424675, 10.619114, -71.045464 }, 0.000048, 1.320602, 2.692222, 0.258413 );

    pEObj = instance.addEObj( "LongstopHeadgate", 2001465, 3970153, 3999869, 4, { -113.634499f, 1.332127f, -58.144779f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -113.634499, 4.054294, -58.067089 }, -0.000000, 1.331574, 2.714589, 0.260560 );

    pEObj = instance.addEObj( "LongstopGutgate", 2001466, 3976772, 3999872, 4, { -89.831360f, 14.042510f, -96.676224f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -89.831360, 17.777489, -96.676224 }, -0.000000, 3.473000, 3.910320, 0.260560 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 3999874, 4, { -8.639429f, 35.641689f, -234.813797f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4086914, 4, { 113.256897f, -1.172536f, 59.115589f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2001584, 4086949, 4086950, 4, { 106.822800f, -1.629326f, 2.541263f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 106.822800, 0.870674, 2.541263 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2001585, 0, 4086952, 4, { 110.429604f, -1.663330f, 3.311157f }, 0.991760f, 0.214809f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2001586, 4088979, 4088982, 4, { 8.021301f, 5.921407f, -69.090309f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 8.021301, 8.421408, -69.090309 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_3", 2001587, 0, 4088984, 4, { 6.458210f, 5.902269f, -67.560417f }, 1.000000f, -0.788830f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2001588, 4088985, 4088987, 4, { -106.298798f, -2.123102f, -10.585170f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -106.298798, 0.376898, -10.585170 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_4", 2001589, 0, 4088988, 4, { -105.172897f, -2.123102f, -10.865350f }, 1.000000f, -0.043989f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2001590, 4088991, 4088993, 4, { -68.039551f, 33.716820f, -232.938904f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -68.039551, 36.216820, -232.938904 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_5", 2001591, 0, 4088994, 4, { -68.693542f, 33.682091f, -234.070496f }, 1.000000f, -1.318638f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 4097104, 4097108, 5, { 122.445702f, -1.119082f, 68.403687f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 122.445702, 0.880918, 65.403687 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 122.455505, 0.880918, 71.403687 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 125.445702, 0.880918, 68.407578 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 119.445702, 0.880918, 68.414665 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 120.345703, 0.880918, 66.303688 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 124.545700, 0.880918, 70.503685 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 124.545700, 0.880918, 66.303688 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 120.345703, 0.880918, 70.503685 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "unknown_0", 2001694, 0, 4107923, 4, { -36.384769f, 34.915119f, -234.568405f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( BrayfloxsLongstop );