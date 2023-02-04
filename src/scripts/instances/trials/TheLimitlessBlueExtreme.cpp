#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheLimitlessBlueExtreme : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheLimitlessBlueExtreme() : Sapphire::ScriptAPI::InstanceContentScript( 20034 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "Magitekfieldgenerator", 2005541, 0, 5862372, 4, { -15.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Dragonkiller", 2005544, 0, 5862495, 4, { -13.000000f, 0.182584f, -17.700001f }, 1.000000f, 0.261799f, 0); 
    instance.addEObj( "Dragonkiller_1", 2005545, 0, 5862496, 4, { -14.150000f, 0.168036f, 19.500000f }, 1.000000f, -0.087266f, 0); 
    instance.addEObj( "sgbg_a2fa_a1_bsid2", 2005847, 5865535, 5887993, 4, { -5.185479f, 0.084680f, 0.234906f }, 1.000000f, 0.000000f, 0); 
    // States -> collision_on (id: 1) collision_off (id: 2) 
    instance.addEObj( "sgbg_a2fa_a1_bare1", 2005958, 5898723, 5898727, 4, { -3.398252f, 0.016719f, -0.449336f }, 1.000000f, 0.000000f, 0); 
    // States -> stage_ba_hide (id: 1) stage_ba_show (id: 2) stage_ba_anim1 (id: 3) stage_ba_anim2 (id: 4) 
    instance.addEObj( "unknown_0", 2005965, 5874950, 5898907, 4, { -14.475140f, 0.010675f, 5.614964f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 5778232, 5778233, 5, { -26.139870f, 0.000001f, -0.197510f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 5778234, 4, { -4.281307f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheLimitlessBlueExtreme );