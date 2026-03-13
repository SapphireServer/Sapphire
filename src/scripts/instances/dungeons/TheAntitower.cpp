#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheAntitower : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheAntitower() : Sapphire::ScriptAPI::InstanceContentScript( 43 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 6168791, 6168798, 5, { -303.646912f, 230.000000f, 280.401703f }, 1.000000f, -0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -303.646912, 232.000000, 277.401703 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -303.637115, 232.000000, 283.401703 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -300.646912, 232.000000, 280.405579 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -306.646912, 232.000000, 280.412689 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -305.746918, 232.000000, 278.301697 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -301.546906, 232.000000, 282.501709 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -301.546906, 232.000000, 278.301697 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -305.746918, 232.000000, 282.501709 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "unknown_4", 2006767, 6215870, 6168857, 4, { -319.905396f, 220.000000f, 144.542892f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -320.033386, 227.000000, 152.310913 }, -0.000488, 12.000000, 8.000000, 0.200000 );

    pEObj = instance.addEObj( "unknown_5", 2006771, 6215871, 6168858, 4, { -351.689087f, 255.000000f, 14.809160f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -351.817078, 262.000000, 22.577187 }, -0.000488, 8.000000, 8.000000, 0.200000 );

    pEObj = instance.addEObj( "unknown_6", 2006778, 6215872, 6168859, 4, { -361.023285f, 290.000000f, -120.754402f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -361.151276, 297.000000, -112.986374 }, -0.000488, 8.000000, 8.000000, 0.200000 );

    pEObj = instance.addEObj( "unknown_7", 2006781, 6112286, 6168897, 4, { 202.549393f, 2.000032f, 188.466202f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2006782, 6112287, 6168898, 4, { 190.864197f, 1.999979f, 180.727493f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2006783, 6112293, 6168899, 4, { 181.429306f, 1.899876f, 187.239197f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 181.429306, 8.899876, 195.319153 }, 0.000000, 4.000000, 8.000000, 0.200000 );

    pEObj = instance.addEObj( "unknown_10", 2006786, 6112290, 6168908, 4, { 138.231400f, -16.006710f, 145.799896f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2006787, 6112291, 6168909, 4, { 125.191902f, -16.000000f, 143.181503f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2006788, 6112288, 6168910, 4, { 124.527199f, -16.000000f, 132.912994f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_13", 2006789, 6112289, 6168911, 4, { 137.132797f, -16.006710f, 128.862396f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgbg_d2d5_a0_gmc08", 2006790, 6168912, 6168913, 4, { 143.049393f, -16.000000f, 136.666702f }, 1.000000f, 0.000000f, 0 ); 
    // States -> start_al02 (id: 25) end_al02 (id: 26) show_anim_al02 (id: 27) 
    pEObj->addCollisionBox( { 143.049393, -9.000000, 144.746643 }, 0.000000, 4.000000, 8.000000, 0.200000 );

    pEObj = instance.addEObj( "unknown_15", 2006791, 6215456, 6169130, 4, { 141.712997f, 22.840740f, -75.213570f }, 1.000000f, -0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2006792, 6215659, 6169131, 4, { 143.769394f, 22.262880f, -82.780273f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2006793, 6215458, 6169132, 4, { 176.529694f, 12.734810f, -76.608017f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_18", 2006794, 6215660, 6169133, 4, { 175.971298f, 13.065370f, -83.629440f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_19", 2006795, 6140680, 6169135, 4, { 262.401794f, -0.700000f, -74.295052f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_20", 2006796, 6140674, 6169136, 4, { 262.532196f, -0.700000f, -86.662819f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_21", 2006797, 6123756, 6169137, 4, { 262.633514f, -0.700000f, -79.584007f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 262.633514, 9.513830, -79.584007 }, -0.000000, 5.500002, 11.235220, 0.100000 );

    pEObj = instance.addEObj( "unknown_22", 2006798, 0, 6169138, 4, { 291.762695f, -2.200014f, -76.847649f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_23", 2006799, 0, 6169139, 4, { 298.066406f, -2.151550f, -76.649200f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_24", 2006800, 0, 6169140, 4, { 298.579895f, -2.037392f, -84.721710f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_25", 2006801, 6215463, 6169141, 4, { 298.707794f, -2.062215f, -111.243301f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_26", 2006802, 6215464, 6169142, 4, { 291.473785f, -2.200000f, -111.318298f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_27", 2006803, 6215465, 6169143, 4, { 298.705597f, -2.065336f, -116.301102f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_28", 2006804, 6215466, 6169144, 4, { 291.648193f, -2.200000f, -116.725502f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_29", 2006805, 6215467, 6169151, 4, { 303.031708f, -0.700000f, -133.974594f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_30", 2006806, 6215468, 6169152, 4, { 286.195709f, -0.700000f, -132.797195f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_31", 2006807, 6215469, 6169153, 4, { 303.791687f, -0.717224f, -138.384094f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_32", 2006808, 6215470, 6169154, 4, { 286.152313f, -0.717224f, -136.736099f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_33", 2006809, 6215471, 6169155, 4, { 303.913788f, -0.717224f, -142.473495f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_34", 2006810, 6215472, 6169156, 4, { 286.518585f, -0.717224f, -140.550903f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_35", 2006811, 6140683, 6169157, 4, { 300.845215f, -0.700000f, -149.810699f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_36", 2006812, 6140685, 6169158, 4, { 289.275787f, -0.700000f, -149.729401f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_37", 2006813, 6123759, 6169159, 4, { 294.959503f, -0.700000f, -149.563904f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 294.959503, 9.513830, -149.563904 }, -0.000000, 5.500002, 11.235220, 0.100000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 6169306, 6169310, 4, { -367.917297f, 325.000000f, -225.755905f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -367.917297, 327.500000, -225.755905 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_1", 2002735, 0, 6169311, 4, { -365.057709f, 325.000000f, -230.778107f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2006816, 6169309, 6169312, 4, { -367.727386f, 325.000000f, -267.544891f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -367.727386, 327.500000, -267.544891 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2006817, 6169316, 6169317, 4, { 207.573303f, -22.000000f, 137.064407f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 207.573303, -19.500000, 137.064407 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_4", 2002872, 6169315, 6169318, 4, { 163.478195f, -21.493710f, 135.478806f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 163.478195, -18.993710, 135.478806 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_3", 2002735, 0, 6169319, 4, { 165.865494f, -22.000000f, 137.572006f }, 1.000000f, 1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 6169322, 4, { 252.045807f, -9.475893f, -181.933304f }, 0.991760f, -1.570796f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 6169321, 6169323, 4, { 255.394501f, -8.467778f, -179.715897f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 255.394501, -5.967778, -179.715897 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 6169331, 4, { -293.381012f, 230.000000f, 269.617188f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6169333, 4, { 216.878998f, -9.458686f, -181.220200f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2006858, 0, 6179354, 4, { -364.583893f, 324.971405f, -250.263199f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgbg_d2d5_a0_gmc01", 2006994, 6220274, 6223589, 4, { 156.748901f, -3.960001f, 175.039703f }, 1.000000f, 0.000000f, 0 ); 
    // States -> show_rc01 (id: 42) hide_rc01 (id: 43) hide_anim_rc01 (id: 44) 

    pEObj = instance.addEObj( "sgbg_d2d5_a0_gmc01_1", 2006995, 6220275, 6223590, 4, { 151.476196f, -3.952148f, 182.940308f }, 0.991760f, 0.000048f, 0 ); 
    // States -> show_rc01 (id: 42) hide_rc01 (id: 43) hide_anim_rc01 (id: 44) 

    pEObj = instance.addEObj( "sgbg_d2d5_a0_gmc02", 2006996, 6220281, 6223591, 4, { 154.570801f, -3.951959f, 179.952393f }, 1.000000f, 0.000000f, 0 ); 
    // States -> show_rc02 (id: 42) hide_rc02 (id: 43) hide_anim_rc02 (id: 44) 

    pEObj = instance.addEObj( "sgbg_d2d5_a0_gmc02_1", 2006997, 6220282, 6223592, 4, { 132.225601f, -15.960000f, 142.602600f }, 1.000000f, 0.000000f, 0 ); 
    // States -> show_rc02 (id: 42) hide_rc02 (id: 43) hide_anim_rc02 (id: 44) 

    pEObj = instance.addEObj( "unknown_14", 2007012, 6107601, 6241298, 4, { 215.289795f, -22.099991f, 137.138306f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheAntitower );