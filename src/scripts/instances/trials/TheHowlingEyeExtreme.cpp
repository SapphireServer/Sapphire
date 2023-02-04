#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheHowlingEyeExtreme : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheHowlingEyeExtreme() : Sapphire::ScriptAPI::InstanceContentScript( 20010 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgbg_r1fa_a_rockcol", 2000646, 4256721, 4297334, 4, { -4.592406f, -1.261766f, 4.724565f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_r1fa_a_rockcol_1", 2000647, 4256725, 4297335, 4, { 7.587256f, -1.233237f, 6.169516f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_r1fa_a_rockcol_2", 2000648, 4256726, 4297338, 4, { -6.329784f, 3.332559f, -6.736721f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_r1fa_a_rockcol_3", 2000649, 4256727, 4297341, 4, { 5.895649f, 3.275768f, -6.217119f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_r1fa_a_rockcol_4", 2000646, 4488538, 4488551, 4, { -7.000000f, 0.000000f, 7.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_r1fa_a_rockcol_5", 2000647, 4488545, 4488552, 4, { 7.000000f, 0.000000f, 7.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_r1fa_a_rockcol_6", 2000648, 4488546, 4488553, 4, { -7.000000f, 0.000000f, -7.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_r1fa_a_rockcol_7", 2000649, 4488548, 4488554, 4, { 7.000000f, 0.000000f, -7.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000274, 4246117, 4247837, 5, { 0.506547f, -1.935848f, 14.110570f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000275, 0, 4247840, 4, { 1.078937f, -2.041544f, -18.363190f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2002689, 0, 4374462, 4, { -83.712677f, -0.871584f, -32.616779f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheHowlingEyeExtreme );