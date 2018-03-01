#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheLimitlessBlueExtreme : public InstanceContentScript
{
public:
   TheLimitlessBlueExtreme() : InstanceContentScript( 20034 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Magitekfieldgenerator", 2005541, 0, 4, { -15.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Dragonkiller", 2005544, 0, 4, { -13.000000f, 0.182584f, -17.700001f }, 1.000000f );
      instance->registerEObj( "Dragonkiller", 2005545, 0, 4, { -14.150000f, 0.168036f, 19.500000f }, 1.000000f );
      instance->registerEObj( "Unknown0", 2005847, 5865535, 4, { -5.185479f, 0.084680f, 0.234906f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2005958, 5898723, 4, { -3.398252f, 0.016719f, -0.449336f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2005965, 5874950, 4, { -14.475140f, 0.010675f, 5.614964f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5778232, 5, { -26.139870f, 0.000001f, -0.197510f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -4.281307f, 0.000000f, 0.000000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};