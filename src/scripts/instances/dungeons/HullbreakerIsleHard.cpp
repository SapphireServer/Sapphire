#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class HullbreakerIsleHard :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HullbreakerIsleHard() :
    Sapphire::ScriptAPI::InstanceContentScript( 45 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -343.904602f, 7.822294f, 39.109711f }, 0.500000f, 0.498864f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6253922, 4, { -343.716888f, 7.647682f, 38.636318f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -360.775909f, 7.864089f, 68.887756f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer", 2007257, 0, 4, { -350.992401f, 7.892528f, 56.902512f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_1", 2007258, 0, 4, { -354.052490f, 7.892528f, 54.626640f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007359, 0, 4, { -352.179810f, 7.927567f, 63.128880f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6245769, 5, { 322.891693f, 3.635096f, 313.253510f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 328.376587f, 5.844693f, 298.411591f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007025, 6235928, 4, { 307.237701f, 11.852150f, 276.543915f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007026, 6240784, 4, { 286.591309f, 19.136169f, 239.456497f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007027, 6239711, 4, { 306.575897f, 31.887329f, 181.107697f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007028, 6244799, 4, { 220.128998f, 63.509621f, 114.498398f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007156, 6249693, 4, { 308.747314f, 51.440979f, 125.671898f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007157, 6249706, 4, { 313.862793f, 51.438110f, 123.826897f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_8", 2007030, 6244507, 4, { 60.801022f, 85.774963f, -64.387527f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007034, 6232348, 4, { -35.186840f, 44.985500f, -123.946198f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007035, 6243845, 4, { -235.700607f, 0.607149f, 8.445139f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007036, 6243848, 4, { -284.362396f, 0.606121f, 11.598470f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007037, 6243852, 4, { -334.528412f, 1.244455f, 21.911160f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2002735, 0, 4, { 222.214600f, 65.079712f, 11.398440f }, 1.400000f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6253107, 4, { 221.229599f, 65.079712f, 13.333970f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_14", 2007072, 6241286, 4, { 198.155396f, 64.976288f, -11.912840f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2002735, 0, 4, { -60.746220f, 44.327389f, -123.705002f }, 0.991760f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6253215, 4, { -58.605789f, 45.157280f, -124.548203f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007073, 6253218, 4, { -102.000999f, 45.915119f, -123.827301f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_16", 2007260, 6252642, 4, { -76.831734f, 44.106281f, -123.152199f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HullbreakerIsleHard );