#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheBreathoftheCreatorSavage : public InstanceContentScript
{
public:
   AlexanderTheBreathoftheCreatorSavage() : InstanceContentScript( 30044 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007457, 6424853, 4, { 0.000000f, -114.849998f, 12.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007457, 6424863, 4, { 0.000000f, -114.849998f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 6424869, 4, { 0.000000f, -114.849998f, -12.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007457, 6418872, 4, { 0.000000f, -114.849998f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007457, 6421358, 4, { 0.000000f, -114.849998f, 10.000000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007457, 6421505, 4, { 0.000000f, -114.849998f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007457, 6421506, 4, { 0.000000f, -114.849998f, -10.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007496, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007457, 6515444, 4, { 0.680462f, -115.000000f, 1.219872f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007498, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007457, 0, 4, { 0.000000f, -114.849998f, 10.000000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007457, 6538404, 4, { 0.000000f, -115.000000f, 4.000000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007457, 6538406, 4, { 0.000000f, -115.000000f, -4.000006f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007457, 6294347, 4, { -17.866249f, -10.500000f, 148.102402f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007457, 6294348, 4, { -44.597561f, -10.500000f, 101.743698f }, 1.000000f );
      instance->registerEObj( "Exhaustvent", 2007470, 6367742, 4, { 1.716182f, -18.500000f, 37.358582f }, 1.000000f );
      instance->registerEObj( "Ingress", 2007471, 0, 4, { 1.998901f, -16.647579f, 36.697880f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2002735, 0, 4, { 2.000000f, -18.940580f, 37.027279f }, 0.500000f );
      instance->registerEObj( "Unknown16", 2002872, 6487232, 4, { 1.792570f, -18.500000f, 38.188919f }, 1.000000f );
      instance->registerEObj( "Exit", 2006235, 0, 4, { 11.500000f, -115.007301f, -18.204100f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 6449464, 5, { -0.025814f, -10.500000f, 188.076599f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 2.874061f, -10.500000f, 177.815994f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6449481, 5, { -7.931533f, -18.500000f, 50.286880f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};