#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheSecondCoilofBahamutTurn2 : public InstanceContentScript
{
public:
   TheSecondCoilofBahamutTurn2() : InstanceContentScript( 30008 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2003299, 4646804, 4, { -449.999908f, 800.027222f, 69.995399f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2003311, 4646803, 4, { -449.999908f, 800.027222f, 69.995354f }, 0.991760f );
      instance->registerEObj( "Ripenedbulb", 2003293, 4646806, 4, { -449.999908f, 800.027222f, 69.995399f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 4646962, 5, { -358.417694f, -270.655487f, -0.875555f }, 0.991760f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -384.512085f, -270.435699f, -2.731445f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2002469, 4646048, 4, { -447.239197f, 799.923584f, 70.054077f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2002470, 4646986, 4, { -448.371613f, 800.000000f, 20.807449f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002471, 4646049, 4, { -372.196899f, -270.740997f, -1.014158f }, 0.991760f );
      instance->registerEObj( "Innerbulkhead", 2003415, 0, 4, { -375.434814f, -268.802399f, -0.859896f }, 1.000000f );
      instance->registerEObj( "Allaganterminal", 2003417, 4682781, 4, { -450.001099f, 799.969971f, 143.447495f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002735, 0, 4, { -449.981689f, 800.000000f, 47.625530f }, 0.991760f );
      instance->registerEObj( "Unknown7", 2002872, 4646969, 4, { -449.981689f, 801.188416f, 47.036610f }, 0.991760f );
      instance->registerEObj( "Unknown8", 2002472, 4646987, 4, { -449.121704f, 800.000000f, 91.049332f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};