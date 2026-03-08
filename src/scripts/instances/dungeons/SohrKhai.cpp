#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class SohrKhai : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SohrKhai() : Sapphire::ScriptAPI::InstanceContentScript( 44 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "unknown_1", 2007078, 6220718, 6255019, 4, { -400.506195f, 0.390429f, 82.229874f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -400.506195, 4.534904, 82.229874 }, -0.000000, 3.397227, 4.558921, 0.088388 );

    pEObj = instance.addEObj( "unknown_2", 2007079, 6220719, 6255024, 4, { -400.289886f, 0.381470f, -77.470093f }, 0.991760f, -1.567142f, 0 ); 
    pEObj->addCollisionBox( { -400.289703, 4.491795, -77.470093 }, -1.567142, 3.369235, 4.521357, 0.087660 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 6258645, 6258650, 4, { 400.881195f, -19.484011f, -332.214996f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 400.881195, -16.984011, -332.214996 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 6258651, 4, { 400.118713f, -18.543800f, -338.582886f }, 1.000000f, -0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 6258660, 6258661, 5, { -406.742615f, -8.000000f, 164.927795f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -406.742615, -6.000000, 161.927795 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -406.732819, -6.000000, 167.927795 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -403.742615, -6.000000, 164.931686 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -409.742615, -6.000000, 164.938766 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -408.842621, -6.000000, 162.827789 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -404.642609, -6.000000, 167.027802 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -404.642609, -6.000000, 162.827789 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -408.842621, -6.000000, 167.027802 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 6258662, 4, { -393.089386f, -8.000000f, 150.811401f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6258663, 4, { 399.538910f, -50.000011f, -494.319092f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 6258669, 6258671, 4, { -400.654388f, 9.235634f, -135.696106f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -400.654388, 11.735634, -135.696106 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2007082, 6258670, 6258672, 4, { -400.434387f, 8.000000f, -177.220200f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -400.434387, 10.500000, -177.220200 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_9", 2002735, 0, 6258674, 4, { -400.177612f, 8.431900f, -137.820801f }, 1.000000f, -0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2007083, 6238460, 6258675, 4, { -401.279297f, 9.299995f, -184.260300f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -401.279297, 17.299995, -184.760300 }, -0.000000, 8.000000, 8.000000, 0.500000 );
    pEObj->addCollisionBox( { -401.279297, 0.799995, -192.260300 }, -0.000000, 8.000000, 0.500000, 8.000000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 6258680, 6258681, 4, { 399.753113f, 9.358741f, 161.151505f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 399.753113, 11.858741, 161.151505 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_11", 2002735, 0, 6258682, 4, { 400.071198f, 9.620000f, 156.602402f }, 1.000000f, -0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2007085, 6242340, 6258683, 4, { 397.968506f, 9.664823f, 157.574600f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 397.968506, 17.664822, 157.074600 }, -0.000000, 8.000000, 8.000000, 0.500000 );
    pEObj->addCollisionBox( { 397.968506, 1.164823, 149.574600 }, -0.000000, 8.000000, 0.500000, 8.000000 );

    pEObj = instance.addEObj( "unknown_13", 2007086, 6241485, 6258684, 4, { 398.938812f, 24.959961f, 85.423576f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 398.938812, 32.959961, 84.923576 }, -0.000000, 8.000000, 8.000000, 0.500000 );
    pEObj->addCollisionBox( { 398.938812, 16.459961, 77.423576 }, -0.000000, 8.000000, 0.500000, 8.000000 );

    pEObj = instance.addEObj( "unknown_5", 2007087, 6242639, 6258717, 4, { 399.851196f, -58.700001f, -128.611893f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 399.851196, -50.700001, -129.111893 }, -0.000000, 8.000000, 8.000000, 0.500000 );
    pEObj->addCollisionBox( { 399.851196, -67.199997, -136.611893 }, -0.000000, 8.000000, 0.500000, 8.000000 );

    pEObj = instance.addEObj( "unknown_6", 2007088, 6242640, 6258719, 4, { 363.607697f, -38.700001f, -242.258194f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 363.607697, -30.700001, -242.758194 }, -0.000000, 8.000000, 8.000000, 0.500000 );
    pEObj->addCollisionBox( { 363.607697, -47.200001, -250.258194 }, -0.000000, 8.000000, 0.500000, 8.000000 );

    pEObj = instance.addEObj( "unknown_7", 2007089, 6242641, 6258720, 4, { 400.331604f, -18.700001f, -336.562897f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 400.331604, -10.700001, -337.062897 }, -0.000000, 8.000000, 8.000000, 0.500000 );
    pEObj->addCollisionBox( { 400.331604, -27.200001, -344.562897 }, -0.000000, 8.000000, 0.500000, 8.000000 );

    pEObj = instance.addEObj( "unknown_8", 2007090, 6229304, 6258749, 4, { 423.391998f, -40.024479f, -205.523697f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 445.391113, -24.157368, -205.523407 }, -1.570403, 3.967041, 15.868165, 0.247940 );
    pEObj->addCollisionBox( { 445.542206, -24.157175, -201.338470 }, -1.843023, 0.991760, 15.868165, 0.247940 );
    pEObj->addCollisionBox( { 445.586639, -24.157585, -209.875626 }, -1.277529, 0.991760, 15.868165, 0.247940 );

    pEObj = instance.addEObj( "unknown_4", 2007084, 6241486, 6259645, 4, { 377.864990f, 0.390429f, 352.375702f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 377.864990, 7.390429, 352.375702 }, -0.000000, 3.859375, 7.000000, 0.375000 );

    pEObj = instance.addEObj( "unknown_14", 2007158, 6241490, 6264479, 4, { 407.500000f, 24.959999f, 89.161400f }, 1.000000f, 1.570451f, 0 ); 
    pEObj->addCollisionBox( { 407.500000, 40.709999, 89.161400 }, 1.570451, 2.500000, 16.250000, 5.125000 );
    pEObj->addCollisionBox( { 407.500000, 24.959999, 89.161400 }, 1.570451, 2.500000, 0.467870, 5.000000 );

    pEObj = instance.addEObj( "unknown_15", 2007159, 6241491, 6264480, 4, { 407.500000f, 24.959999f, 99.161400f }, 1.000000f, 1.570451f, 0 ); 
    pEObj->addCollisionBox( { 407.500000, 40.709999, 99.161400 }, 1.570451, 2.500000, 16.250000, 5.125000 );
    pEObj->addCollisionBox( { 407.500000, 24.959999, 99.161400 }, 1.570451, 2.500000, 0.467870, 5.000000 );

    pEObj = instance.addEObj( "unknown_16", 2007160, 6241492, 6264481, 4, { 407.500000f, 24.959999f, 109.161400f }, 1.000000f, 1.570451f, 0 ); 
    pEObj->addCollisionBox( { 407.500000, 40.709999, 109.161400 }, 1.570451, 2.500000, 16.250000, 5.125000 );
    pEObj->addCollisionBox( { 407.500000, 24.959999, 109.161400 }, 1.570451, 2.500000, 0.467870, 5.000000 );

    pEObj = instance.addEObj( "unknown_17", 2007161, 6241493, 6264482, 4, { 407.500000f, 24.959999f, 119.161400f }, 1.000000f, 1.570451f, 0 ); 
    pEObj->addCollisionBox( { 407.500000, 40.709999, 119.161400 }, 1.570451, 2.500000, 16.250000, 5.125000 );
    pEObj->addCollisionBox( { 407.500000, 24.959999, 119.161400 }, 1.570451, 2.500000, 0.467870, 5.000000 );

    pEObj = instance.addEObj( "unknown_18", 2007162, 6241489, 6264483, 4, { 392.500000f, 24.959999f, 89.161400f }, 1.000000f, -1.570451f, 0 ); 
    pEObj->addCollisionBox( { 392.500000, 40.709999, 89.161400 }, -1.570451, 2.500000, 16.250000, 5.125000 );
    pEObj->addCollisionBox( { 392.500000, 24.959999, 89.161400 }, -1.570451, 2.500000, 0.467870, 5.000000 );

    pEObj = instance.addEObj( "unknown_19", 2007163, 6241488, 6264484, 4, { 392.500000f, 24.959999f, 99.161400f }, 1.000000f, -1.570451f, 0 ); 
    pEObj->addCollisionBox( { 392.500000, 40.709999, 99.161400 }, -1.570451, 2.500000, 16.250000, 5.125000 );
    pEObj->addCollisionBox( { 392.500000, 24.959999, 99.161400 }, -1.570451, 2.500000, 0.467870, 5.000000 );

    pEObj = instance.addEObj( "unknown_20", 2007164, 6241487, 6264485, 4, { 392.500000f, 24.959999f, 109.161400f }, 1.000000f, -1.570451f, 0 ); 
    pEObj->addCollisionBox( { 392.500000, 40.709999, 109.161400 }, -1.570451, 2.500000, 16.250000, 5.125000 );
    pEObj->addCollisionBox( { 392.500000, 24.959999, 109.161400 }, -1.570451, 2.500000, 0.467870, 5.000000 );

    pEObj = instance.addEObj( "unknown_21", 2007165, 6241484, 6264486, 4, { 392.500000f, 24.959999f, 119.161400f }, 1.000000f, -1.570451f, 0 ); 
    pEObj->addCollisionBox( { 392.500000, 40.709999, 119.161400 }, -1.570451, 2.500000, 16.250000, 5.125000 );
    pEObj->addCollisionBox( { 392.500000, 24.959999, 119.161400 }, -1.570451, 2.500000, 0.467870, 5.000000 );

    pEObj = instance.addEObj( "unknown_3", 2007189, 0, 6277149, 4, { -425.070587f, -0.015320f, 5.569519f }, 0.991760f, 0.000048f, 0 ); 


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

EXPOSE_SCRIPT( SohrKhai );