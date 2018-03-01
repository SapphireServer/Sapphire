#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheCuffoftheFatherSavage : public InstanceContentScript
{
public:
   AlexanderTheCuffoftheFatherSavage() : InstanceContentScript( 30026 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "MagitekgobwalkerGVII", 2005126, 0, 4, { -23.299919f, -27.250000f, -93.915253f }, 2.500000f );
      instance->registerEObj( "MagitekgobwalkerGVII", 2005474, 0, 4, { -25.869850f, -27.250000f, -91.505951f }, 2.500000f );
      instance->registerEObj( "MagitekgobwalkerGVII", 2005475, 0, 4, { -28.364830f, -27.250000f, -89.139442f }, 2.500000f );
      instance->registerEObj( "MagitekgobwalkerGVII", 2005126, 0, 4, { -24.477819f, -27.250000f, -93.315643f }, 2.500000f );
      instance->registerEObj( "MagitekgobwalkerGVII", 2005474, 0, 4, { -27.127260f, -27.250000f, -90.671631f }, 2.500000f );
      instance->registerEObj( "Unknown0", 2005047, 5796486, 4, { -16.006710f, 28.995720f, 121.127502f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2005047, 5796475, 4, { -15.991690f, 25.994120f, 104.104698f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2005047, 5796479, 4, { -0.042969f, -15.876210f, 39.414860f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2005047, 5796481, 4, { -0.042969f, -22.069151f, 4.294098f }, 1.000000f );
      instance->registerEObj( "Steamspoutingcontraption", 2005048, 5828187, 4, { -20.999439f, 28.890051f, 120.379700f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2005428, 5828194, 4, { -20.812780f, 25.885040f, 102.729103f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2005428, 5828205, 4, { -5.111024f, -22.178221f, 3.677231f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -19.655809f, 31.065201f, 144.212204f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2005047, 5962936, 4, { -16.018070f, 27.033091f, 118.517899f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2005047, 5962937, 4, { 4.629210f, -8.535899f, 53.038620f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2002735, 0, 4, { 0.000000f, -28.000000f, -53.246899f }, 0.750000f );
      instance->registerEObj( "Unknown9", 2002872, 5787859, 4, { -0.137953f, -26.000000f, -52.603008f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2002872, 5787862, 4, { 0.000000f, -26.000000f, -96.909851f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2006105, 5883005, 4, { 0.000000f, -28.000000f, -75.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2005313, 5908620, 4, { 0.000000f, -26.000000f, -110.560898f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, -27.991100f, -115.007500f }, 1.000000f );
      instance->registerEObj( "Steamspoutingcontraption", 2005427, 5828202, 4, { -5.000190f, -15.985280f, 39.105530f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5787826, 5, { -16.006710f, 36.148560f, 161.008804f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 5908672, 5, { 0.002526f, -28.000019f, -23.439610f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};