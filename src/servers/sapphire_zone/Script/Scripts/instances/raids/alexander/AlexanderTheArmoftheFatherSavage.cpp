#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheArmoftheFatherSavage : public InstanceContentScript
{
public:
   AlexanderTheArmoftheFatherSavage() : InstanceContentScript( 30027 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2005400, 0, 4, { 39.638931f, -9.000000f, -67.173187f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2005314, 5878653, 4, { 17.839520f, 42.000000f, 14.681990f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2005314, 6048829, 4, { 17.839520f, 42.000000f, 14.681990f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2006094, 5864098, 4, { 58.027489f, -0.000134f, -20.193150f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2002735, 0, 4, { 58.000000f, -0.000003f, -20.943159f }, 0.600000f );
      instance->registerEObj( "Unknown5", 2002872, 5787963, 4, { 58.043961f, -0.000054f, -20.107550f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 100.941902f, -10.500000f, -63.000000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002872, 0, 4, { 87.814133f, -9.000000f, -61.109859f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2005911, 5814854, 4, { 58.000000f, -8.999999f, -63.000000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2006095, 5905878, 4, { 58.000000f, -9.000000f, -63.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5787948, 5, { -0.015320f, -0.015320f, 43.037189f }, 0.778198f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 3.252589f, 0.000000f, 30.523800f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5911899, 5, { 58.000000f, -0.000049f, -11.175000f }, 0.800000f );
      instance->registerEObj( "Unknown11", 2000608, 5911895, 4, { 58.000000f, 0.841694f, -1.705941f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};