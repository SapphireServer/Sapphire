#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheMinstrelsBalladThordansReign :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheMinstrelsBalladThordansReign() :
    Sapphire::ScriptAPI::InstanceContentScript( 20036 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgbg_a2fb_a1_sod1a", 2006312, 5922953, 4, { -7.224293f, 0.039305f, -2.496346f }, 1.000000f, 0.000000f ); 
    // States -> sword_hide (id: 2) sword_show (id: 3) sword_show_anim (id: 4) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2", 2005944, 5895686, 4, { 12.728000f, 0.012478f, -12.728000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_1", 2005945, 5895687, 4, { 12.728000f, 0.012478f, 12.728000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_2", 2005946, 5895690, 4, { -12.728000f, 0.012478f, 12.728000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_3", 2005947, 5895691, 4, { -12.728000f, 0.012478f, -12.728000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_4", 2005915, 5894863, 4, { 9.000000f, 0.012478f, -16.600000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_5", 2005916, 5894864, 4, { 18.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_6", 2005917, 5894866, 4, { 9.000000f, 0.012478f, 16.600000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_7", 2005918, 5894867, 4, { -9.000000f, 0.012478f, 16.600000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_8", 2005919, 5894868, 4, { -18.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_9", 2005920, 5894869, 4, { -9.000000f, 0.012478f, -16.600000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete1", 2005914, 5894871, 4, { 0.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> mete_off_01 (id: 1) mete_off_02 (id: 2) mete_on_01 (id: 3) mete_off_03 (id: 4) mete_on_02 (id: 5) mete_on_03 (id: 6) mete_on_04 (id: 7) mete_on_05 (id: 8) mete_on_06 (id: 9) mete_fdout (id: 18) 
    instance.registerEObj( "sgbg_a2fb_a1_whit1", 2005913, 5894872, 4, { 0.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> wo_default (id: 2) wo_end (id: 3) wo_anim (id: 4) 
    instance.registerEObj( "sgbg_a2fb_a1_mete1_1", 2006575, 6061720, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> mete_off_01 (id: 1) mete_off_02 (id: 2) mete_on_01 (id: 3) mete_off_03 (id: 4) mete_on_02 (id: 5) mete_on_03 (id: 6) mete_on_04 (id: 7) mete_on_05 (id: 8) mete_on_06 (id: 9) mete_fdout (id: 18) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_10", 2006576, 6061721, 4, { 0.000000f, 0.039305f, -19.000000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_11", 2006577, 6061722, 4, { 19.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_12", 2006578, 6061723, 4, { 0.000000f, 0.039305f, 19.000000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_13", 2006579, 6061724, 4, { -19.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_14", 2006580, 6061725, 4, { 8.485300f, 0.039305f, -8.485300f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_15", 2006581, 6061727, 4, { 8.485300f, 0.039304f, 9.619522f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_16", 2006582, 6061728, 4, { -8.499329f, 0.015198f, 9.174744f }, 0.991760f, 0.000048f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "sgbg_a2fb_a1_mete2_17", 2006583, 6061730, 4, { -8.485300f, 0.039305f, -8.485300f }, 1.000000f, 0.000000f ); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.registerEObj( "unknown_0", 2006567, 6046991, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2006568, 6059913, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2006569, 6059911, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2006570, 6047214, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2006571, 6059909, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2006572, 6047213, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2006573, 6059910, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2006574, 6059912, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2006587, 6056540, 4, { -0.607457f, 0.039305f, -0.008893f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 5854853, 5, { 0.035266f, 0.012478f, 11.380060f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.012478f, -18.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheMinstrelsBalladThordansReign );