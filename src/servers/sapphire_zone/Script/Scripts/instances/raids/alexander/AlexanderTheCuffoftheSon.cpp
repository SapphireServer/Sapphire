#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheCuffoftheSon : public InstanceContentScript
{
public:
   AlexanderTheCuffoftheSon() : InstanceContentScript( 30031 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2005400, 0, 4, { -0.062597f, -7.999998f, -318.102112f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2004356, 6075850, 4, { 16.000000f, 17.661369f, 68.195396f }, 1.000000f );
      instance->registerEObj( "Steamspoutingcontraption", 2004357, 6075772, 4, { 21.013269f, 19.288509f, 69.098198f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2004356, 6183194, 4, { 16.000000f, 17.933451f, 69.738426f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2004362, 6075779, 4, { 21.207670f, 12.939710f, 41.993370f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2002872, 6183959, 4, { 0.000000f, -26.000000f, -99.284462f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002872, 6185722, 4, { 0.000000f, -25.918800f, -139.159302f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002735, 0, 4, { 0.000000f, -25.959690f, -100.169899f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2002735, 0, 4, { 0.000000f, -19.459700f, -163.887405f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2002872, 6185721, 4, { 0.000000f, -19.913139f, -203.123398f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2002872, 6183975, 4, { 0.000000f, -20.000000f, -163.001999f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2002735, 0, 4, { 0.000000f, -13.500000f, -227.525406f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2002872, 6185576, 4, { 0.000000f, -14.000000f, -267.622406f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2002872, 6183981, 4, { 0.000000f, -14.000000f, -226.639999f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2002735, 0, 4, { 0.000000f, -8.000000f, -286.936798f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2002872, 6183985, 4, { 0.000000f, -8.000000f, -286.051392f }, 1.000000f );
      instance->registerEObj( "Exit", 2005313, 6186651, 4, { -0.636187f, -7.999998f, -335.408813f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, -7.921236f, -335.377502f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2006984, 6210606, 4, { -0.151275f, -14.000000f, -248.039703f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2006989, 6234539, 4, { 1.000000f, -20.000000f, -184.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6177892, 5, { 16.000000f, 21.783440f, 91.573517f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 10.387650f, 18.918310f, 75.899696f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6184206, 5, { 0.000000f, -26.000000f, -65.141693f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};