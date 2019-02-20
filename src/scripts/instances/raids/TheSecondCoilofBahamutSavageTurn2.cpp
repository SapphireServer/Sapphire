#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheSecondCoilofBahamutSavageTurn2 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSecondCoilofBahamutSavageTurn2() :
    Sapphire::ScriptAPI::InstanceContentScript( 30013 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2003299, 4646804, 4, { -449.999908f, 800.027222f, 69.995399f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2003311, 4646803, 4, { -449.999908f, 800.027222f, 69.995354f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Ripenedbulb", 2003293, 4646806, 4, { -449.999908f, 800.027222f, 69.995399f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 4646962, 5, { -358.417694f, -270.655487f, -0.875555f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -384.512085f, -270.435699f, -2.731445f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2002469, 4646048, 4, { -447.239197f, 799.923584f, 70.054077f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_w_lvd_colwithnavi", 2002470, 4646986, 4, { -448.371613f, 800.000000f, 20.807449f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2002471, 4646049, 4, { -372.196899f, -270.740997f, -1.014158f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Innerbulkhead", 2003415, 0, 4, { -375.434814f, -268.802399f, -0.859896f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Allaganterminal", 2003417, 4682781, 4, { -450.001099f, 799.969971f, 143.447495f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { -449.981689f, 800.000000f, 47.625530f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_f1b2_bosswall", 2002872, 4646969, 4, { -449.981689f, 801.188416f, 47.036610f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char", 2002472, 4646987, 4, { -449.121704f, 800.000000f, 91.049332f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheSecondCoilofBahamutSavageTurn2 );