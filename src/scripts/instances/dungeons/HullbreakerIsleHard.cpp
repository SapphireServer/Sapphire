#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class HullbreakerIsleHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HullbreakerIsleHard() : Sapphire::ScriptAPI::InstanceContentScript( 45 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 6245769, 6245770, 5, { 322.891693f, 3.635096f, 313.253510f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 322.891693, 5.635096, 310.253510 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 322.901489, 5.635096, 316.253510 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 325.891693, 5.635096, 313.257385 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 319.891693, 5.635096, 313.264496 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 320.791687, 5.635096, 311.153503 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 324.991699, 5.635096, 315.353516 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 324.991699, 5.635096, 311.153503 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 320.791687, 5.635096, 315.353516 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 6245781, 4, { 328.376587f, 5.844693f, 298.411591f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2007025, 6235928, 6246434, 4, { 307.237701f, 11.852150f, 276.543915f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 307.235565, 14.239261, 276.543915 }, -0.000000, 3.494607, 2.985738, 0.115662 );

    pEObj = instance.addEObj( "unknown_3", 2007026, 6240784, 6246694, 4, { 286.591309f, 19.136169f, 239.456497f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 286.589172, 21.523281, 239.456497 }, -0.000000, 3.494607, 2.985738, 0.115662 );

    pEObj = instance.addEObj( "unknown_4", 2007027, 6239711, 6246695, 4, { 306.575897f, 31.887329f, 181.107697f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 306.573761, 34.274441, 181.107697 }, -0.000000, 3.494607, 2.985738, 0.115662 );

    pEObj = instance.addEObj( "unknown_5", 2007028, 6244799, 6246696, 4, { 220.128998f, 63.509621f, 114.498398f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 220.126862, 65.896729, 114.498398 }, -0.000000, 3.494607, 2.985738, 0.115662 );

    pEObj = instance.addEObj( "unknown_8", 2007030, 6244507, 6246713, 4, { 60.801022f, 85.774963f, -64.387527f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 60.801022, 88.804626, -64.363037 }, -0.000000, 2.448475, 3.151788, 0.276526 );

    pEObj = instance.addEObj( "unknown_9", 2007034, 6232348, 6246719, 4, { -35.186840f, 44.985500f, -123.946198f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -35.188725, 50.366760, -123.946198 }, -0.000000, 4.020871, 5.635386, 0.600000 );

    pEObj = instance.addEObj( "unknown_10", 2007035, 6243845, 6246728, 4, { -235.700607f, 0.607149f, 8.445139f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -235.700607, 0.607149, 8.445139 }, -0.000000, 2.919049, 3.531481, 0.190005 );

    pEObj = instance.addEObj( "unknown_11", 2007036, 6243848, 6246729, 4, { -284.362396f, 0.606121f, 11.598470f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -284.362396, 0.606121, 11.598470 }, -0.000000, 2.919049, 3.531481, 0.190005 );

    pEObj = instance.addEObj( "unknown_12", 2007037, 6243852, 6246731, 4, { -334.528412f, 1.244455f, 21.911160f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -334.528412, 1.244455, 21.911160 }, -0.000000, 2.919049, 3.531481, 0.190005 );

    pEObj = instance.addEObj( "unknown_13", 2002735, 0, 6253106, 4, { 222.214600f, 65.079712f, 11.398440f }, 1.400000f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 6253107, 6253112, 4, { 221.229599f, 65.079712f, 13.333970f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 221.229721, 67.559113, 13.333851 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_14", 2007072, 6241286, 6253114, 4, { 198.155396f, 64.976288f, -11.912840f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 198.155396, 64.976288, -11.912840 }, -0.000000, 2.919049, 3.531481, 0.190005 );

    pEObj = instance.addEObj( "unknown_15", 2002735, 0, 6253214, 4, { -60.746220f, 44.327389f, -123.705002f }, 0.991760f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 6253215, 6253217, 4, { -58.605789f, 45.157280f, -124.548203f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -58.605789, 47.657280, -124.548203 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2007073, 6253218, 6253220, 4, { -102.000999f, 45.915119f, -123.827301f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -102.000999, 48.415119, -123.827301 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 6253634, 4, { -343.904602f, 7.822294f, 39.109711f }, 0.500000f, 0.498864f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 6253922, 6253925, 4, { -342.837006f, 6.196667f, 36.610142f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -342.837006, 8.696667, 36.610142 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6253926, 4, { -360.775909f, 7.864089f, 68.887756f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2007156, 6249693, 6263497, 4, { 308.747314f, 51.440979f, 125.671898f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2007157, 6249706, 6263498, 4, { 313.862793f, 51.438110f, 123.826897f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Treasurecoffer", 2007257, 0, 6362642, 4, { -350.992401f, 7.892528f, 56.902512f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Treasurecoffer_1", 2007258, 0, 6362643, 4, { -354.052490f, 7.892528f, 54.626640f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2007260, 6252642, 6362721, 4, { -76.831734f, 44.106281f, -123.152199f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2007359, 0, 6400929, 4, { -352.179810f, 7.927567f, 63.128880f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( HullbreakerIsleHard );