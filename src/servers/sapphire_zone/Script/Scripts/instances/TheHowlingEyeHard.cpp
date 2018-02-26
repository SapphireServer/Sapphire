#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheHowlingEyeHard : public InstanceContentScript
{
public:
   TheHowlingEyeHard() : InstanceContentScript( 20006 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2000646, 4256721, 4, { -4.592406f, -1.261766f, 4.724565f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2000647, 4256725, 4, { 7.587256f, -1.233237f, 6.169516f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2000648, 4256726, 4, { -6.329784f, 3.332559f, -6.736721f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2000649, 4256727, 4, { 5.895649f, 3.275768f, -6.217119f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2000646, 4488538, 4, { -7.000000f, 0.000000f, 7.000000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2000647, 4488545, 4, { 7.000000f, 0.000000f, 7.000000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2000648, 4488546, 4, { -7.000000f, 0.000000f, -7.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2000649, 4488548, 4, { 7.000000f, 0.000000f, -7.000000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2000274, 4246117, 4, { 0.506547f, -1.935848f, 14.110570f }, 1.000000f );
      instance->registerEObj( "Exit", 2000275, 0, 4, { 1.078937f, -2.041544f, -18.363190f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};