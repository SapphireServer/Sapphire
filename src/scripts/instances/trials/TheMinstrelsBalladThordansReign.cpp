#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheMinstrelsBalladThordansReign : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheMinstrelsBalladThordansReign() : Sapphire::ScriptAPI::InstanceContentScript( 20036 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5854853, 5854861, 5, { 0.035266f, 0.012478f, 11.380060f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 0.035266, 2.012478, 8.380060 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.045068, 2.012478, 14.380060 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 3.035266, 2.012478, 11.383951 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.964734, 2.012478, 11.391036 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.064734, 2.012478, 9.280060 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.135266, 2.012478, 13.480061 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.135266, 2.012478, 9.280060 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.064734, 2.012478, 13.480061 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5854862, 4, { 0.000000f, 0.012478f, -18.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_4", 2005915, 5894863, 5894882, 4, { 9.000000f, 0.012478f, -16.600000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_5", 2005916, 5894864, 5894883, 4, { 18.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_6", 2005917, 5894866, 5894885, 4, { 9.000000f, 0.012478f, 16.600000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_7", 2005918, 5894867, 5894886, 4, { -9.000000f, 0.012478f, 16.600000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_8", 2005919, 5894868, 5894888, 4, { -18.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_9", 2005920, 5894869, 5894890, 4, { -9.000000f, 0.012478f, -16.600000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete1", 2005914, 5894871, 5894892, 4, { 0.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> mete_off_01 (id: 1) mete_off_02 (id: 2) mete_on_01 (id: 3) mete_off_03 (id: 4) mete_on_02 (id: 5) mete_on_03 (id: 6) mete_on_04 (id: 7) mete_on_05 (id: 8) mete_on_06 (id: 9) mete_fdout (id: 18) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_whit1", 2005913, 5894872, 5894894, 4, { 0.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> wo_default (id: 2) wo_end (id: 3) wo_anim (id: 4) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2", 2005944, 5895686, 5895692, 4, { 12.728000f, 0.012478f, -12.728000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_1", 2005945, 5895687, 5895693, 4, { 12.728000f, 0.012478f, 12.728000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_2", 2005946, 5895690, 5895694, 4, { -12.728000f, 0.012478f, 12.728000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_3", 2005947, 5895691, 5895695, 4, { -12.728000f, 0.012478f, -12.728000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_sod1a", 2006312, 5922953, 5922958, 4, { -7.224293f, 0.039305f, -2.496346f }, 1.000000f, 0.000000f, 0 ); 
    // States -> sword_hide (id: 2) sword_show (id: 3) sword_show_anim (id: 4) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_10", 2006576, 6061721, 6058747, 4, { 0.000000f, 0.039305f, -19.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_11", 2006577, 6061722, 6058748, 4, { 19.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_12", 2006578, 6061723, 6058749, 4, { 0.000000f, 0.039305f, 19.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_13", 2006579, 6061724, 6058750, 4, { -19.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_14", 2006580, 6061725, 6058751, 4, { 8.485300f, 0.039305f, -8.485300f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_15", 2006581, 6061727, 6058752, 4, { 8.485300f, 0.039304f, 9.619522f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_16", 2006582, 6061728, 6058753, 4, { -8.499329f, 0.015198f, 9.174744f }, 0.991760f, 0.000048f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete2_17", 2006583, 6061730, 6058754, 4, { -8.485300f, 0.039305f, -8.485300f }, 1.000000f, 0.000000f, 0 ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 

    pEObj = instance.addEObj( "sgbg_a2fb_a1_mete1_1", 2006575, 6061720, 6058763, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> mete_off_01 (id: 1) mete_off_02 (id: 2) mete_on_01 (id: 3) mete_off_03 (id: 4) mete_on_02 (id: 5) mete_on_03 (id: 6) mete_on_04 (id: 7) mete_on_05 (id: 8) mete_on_06 (id: 9) mete_fdout (id: 18) 

    pEObj = instance.addEObj( "unknown_0", 2006567, 6046991, 6059918, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2006568, 6059913, 6059919, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2006569, 6059911, 6059920, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2006570, 6047214, 6059921, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2006571, 6059909, 6059922, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2006572, 6047213, 6059923, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2006573, 6059910, 6059924, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2006574, 6059912, 6059925, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2006587, 6056540, 6061731, 4, { -0.607457f, 0.039305f, -0.008893f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheMinstrelsBalladThordansReign );