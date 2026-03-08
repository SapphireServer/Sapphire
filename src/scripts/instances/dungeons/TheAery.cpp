#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheAery : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheAery() : Sapphire::ScriptAPI::InstanceContentScript( 39 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5724494, 5724482, 5, { 136.459106f, 67.985649f, 171.436401f }, 1.000000f, -1.570451f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 133.459106, 69.985649, 171.435364 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 139.459106, 69.985649, 171.427628 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 136.464035, 69.985649, 168.436401 }, -3.140902, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 136.469040, 69.985649, 174.436401 }, -3.140902, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 134.358383, 69.985649, 173.535675 }, -2.355849, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 138.559830, 69.985649, 169.337128 }, -2.355849, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 134.359833, 69.985649, 169.335678 }, -0.785053, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 138.558380, 69.985649, 173.537125 }, -0.785053, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5724570, 4, { 144.406906f, 67.985611f, 177.100906f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5725828, 4, { 21.307430f, 148.274002f, -283.827087f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2005222, 5685356, 5753296, 4, { 267.117188f, 64.682983f, 47.219650f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 267.117188, 64.682983, 47.272026 }, 0.000048, 8.670913, 20.826441, 0.539912 );

    pEObj = instance.addEObj( "unknown_6", 2005223, 5685357, 5753297, 4, { 358.511414f, 81.162720f, -120.381798f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 358.511414, 81.162720, -120.329422 }, 0.000048, 8.670913, 20.826441, 0.539912 );

    pEObj = instance.addEObj( "unknown_7", 2005224, 5821951, 5753299, 4, { 131.793304f, 5.889650f, -103.881500f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 132.793304, 12.489650, -103.881500 }, -0.000000, 0.520000, 7.900000, 15.000000 );

    pEObj = instance.addEObj( "unknown_8", 2005225, 5821943, 5753753, 4, { 50.821239f, 55.531479f, 63.561810f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 51.813313, 62.077049, 63.561543 }, 0.000048, 0.515715, 7.834907, 14.876405 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5754325, 5755388, 4, { 346.791687f, 93.919189f, -178.606903f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 346.791809, 96.398590, -178.607025 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2002872, 5795105, 5755609, 4, { 40.665161f, 59.433842f, 65.873169f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 40.665279, 61.913242, 65.873047 }, 0.000048, 14.876405, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5762428, 5762429, 4, { 37.260880f, 148.068100f, -236.237595f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 37.260880, 150.568100, -236.237595 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2005233, 5754326, 5791058, 4, { 317.558105f, 93.945251f, -180.372498f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 317.558105, 96.445251, -180.372498 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250_1", 2005234, 5795134, 5791409, 4, { -14.039410f, 61.140190f, 54.695210f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -14.039290, 63.619591, 54.695091 }, 0.000048, 14.876405, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_2", 2002735, 0, 5791452, 4, { 35.001831f, 148.194504f, -233.032303f }, 1.000000f, -0.002372f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5791486, 4, { 345.215607f, 93.945251f, -178.963303f }, 1.000000f, -0.581172f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2002587, 0, 5795126, 4, { 39.169510f, 59.433949f, 66.247253f }, 1.300000f, -1.500298f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_colwithnavi", 2005438, 5851315, 5851339, 4, { -77.756859f, 91.481842f, -15.425310f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -77.756859, 91.481842, -15.425310 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_colwithnavi_1", 2005439, 5851342, 5851343, 4, { 82.891663f, 108.510201f, -49.804409f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 82.891663, 108.510201, -49.804409 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_colwithnavi_2", 2005540, 5864523, 5862374, 4, { 33.827099f, 134.430405f, -194.964005f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 33.827099, 134.430405, -194.964005 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_3", 2005542, 0, 5862411, 4, { 36.301151f, 148.393906f, -242.999893f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2006454, 0, 5961246, 4, { 32.698120f, 148.397095f, -251.838501f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheAery );