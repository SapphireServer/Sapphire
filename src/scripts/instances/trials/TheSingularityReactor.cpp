#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheSingularityReactor : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSingularityReactor() : Sapphire::ScriptAPI::InstanceContentScript( 20035 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgbg_a2fb_a1_mete2", 2005944, 5895686, 5895692, 4, { 12.728000f, 0.012478f, -12.728000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_1", 2005945, 5895687, 5895693, 4, { 12.728000f, 0.012478f, 12.728000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_2", 2005946, 5895690, 5895694, 4, { -12.728000f, 0.012478f, 12.728000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_3", 2005947, 5895691, 5895695, 4, { -12.728000f, 0.012478f, -12.728000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_4", 2005915, 5894863, 5894882, 4, { 9.000000f, 0.012478f, -16.600000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_5", 2005916, 5894864, 5894883, 4, { 18.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_6", 2005917, 5894866, 5894885, 4, { 9.000000f, 0.012478f, 16.600000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_7", 2005918, 5894867, 5894886, 4, { -9.000000f, 0.012478f, 16.600000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_8", 2005919, 5894868, 5894888, 4, { -18.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete2_9", 2005920, 5894869, 5894890, 4, { -9.000000f, 0.012478f, -16.600000f }, 1.000000f, 0.000000f, 0); 
    // States -> come_off_01 (id: 2) come_off_02 (id: 3) come_on_01 (id: 4) come_off_03 (id: 5) come_on_02 (id: 6) come_on_03 (id: 7) come_on_04 (id: 8) come_on_05 (id: 9) come_on_06 (id: 10) come_fdout (id: 15) 
    instance.addEObj( "sgbg_a2fb_a1_mete1", 2005914, 5894871, 5894892, 4, { 0.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    // States -> mete_off_01 (id: 1) mete_off_02 (id: 2) mete_on_01 (id: 3) mete_off_03 (id: 4) mete_on_02 (id: 5) mete_on_03 (id: 6) mete_on_04 (id: 7) mete_on_05 (id: 8) mete_on_06 (id: 9) mete_fdout (id: 18) 
    instance.addEObj( "sgbg_a2fb_a1_whit1", 2005913, 5894872, 5894894, 4, { 0.000000f, 0.012478f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    // States -> wo_default (id: 2) wo_end (id: 3) wo_anim (id: 4) 
    instance.addEObj( "sgbg_a2fb_a1_sod1a", 2006312, 5922953, 5922958, 4, { -7.224293f, 0.039305f, -2.496346f }, 1.000000f, 0.000000f, 0); 
    // States -> sword_hide (id: 2) sword_show (id: 3) sword_show_anim (id: 4) 
    instance.addEObj( "Entrance", 2000182, 5854853, 5854861, 5, { 0.035266f, 0.012478f, 11.380060f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 5854862, 4, { 0.000000f, 0.012478f, -18.000000f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheSingularityReactor );