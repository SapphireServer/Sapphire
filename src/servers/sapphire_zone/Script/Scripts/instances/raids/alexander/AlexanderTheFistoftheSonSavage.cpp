#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheFistoftheSonSavage : public InstanceContentScript
{
public:
   AlexanderTheFistoftheSonSavage() : InstanceContentScript( 30034 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2006093, 0, 4, { -0.030479f, -18.000000f, -87.654160f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002872, 6179766, 4, { 0.048718f, -8.000000f, -25.550190f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002872, 6179771, 4, { 0.348718f, -8.000000f, -62.819778f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002587, 0, 4, { 0.000000f, -7.796605f, -27.253839f }, 1.400000f );
      instance->registerEObj( "Unknown4", 2002872, 6179774, 4, { 0.000000f, -18.000000f, -86.751549f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002735, 0, 4, { 0.000000f, -18.000000f, -88.696098f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -10.159560f, -10.000000f, -208.556000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2006965, 6200579, 4, { 0.000000f, -10.000000f, -190.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2004870, 6200506, 4, { -0.400928f, -10.000000f, -198.953598f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2005111, 6200497, 4, { 9.766629f, -10.000000f, -190.029099f }, 1.000000f );
      instance->registerEObj( "Koboldkey", 2006468, 6200507, 4, { -9.431794f, -10.000000f, -190.472397f }, 1.000000f );
      instance->registerEObj( "Koboldkey", 2006469, 6200508, 4, { 0.206919f, -10.000000f, -180.011597f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2004363, 0, 4, { 0.000000f, -10.000000f, -190.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2004367, 0, 4, { 0.000000f, -10.000000f, -206.000000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2004368, 0, 4, { 16.000000f, -10.000000f, -190.000000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2004369, 0, 4, { -16.000000f, -10.000000f, -190.000000f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2004575, 0, 4, { 0.000000f, -10.000000f, -174.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2005313, 6180367, 4, { -8.545354f, -9.800000f, -209.792007f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6177861, 5, { 0.000000f, -60.199001f, 70.921097f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 1.189643f, -53.337769f, 57.917198f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2006105, 6185484, 4, { 0.000000f, -58.108219f, 65.176361f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6184198, 5, { 4.589292f, -3.826589f, 1.082808f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 3.135107f, -6.123573f, -3.436843f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2006105, 6198124, 4, { 4.362909f, -6.098227f, -3.232224f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};