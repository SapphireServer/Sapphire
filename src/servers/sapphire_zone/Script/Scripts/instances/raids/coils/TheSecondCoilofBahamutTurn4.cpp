#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheSecondCoilofBahamutTurn4 : public InstanceContentScript
{
public:
   TheSecondCoilofBahamutTurn4() : InstanceContentScript( 30010 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2003412, 0, 4, { -1.586798f, 0.000000f, 6.322940f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2003413, 4592650, 4, { 0.246630f, 0.000000f, -0.575616f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2003414, 4596280, 4, { 2.330916f, 0.000000f, 1.675908f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2003411, 4585907, 4, { -0.036626f, -0.000000f, -0.514996f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2003392, 4632812, 4, { 0.000000f, -0.000002f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2003393, 0, 4, { 16.296391f, -0.000002f, -4.751545f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2003394, 0, 4, { 11.781120f, -0.000001f, 4.780689f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2003391, 0, 4, { 8.938168f, 0.060000f, -11.440830f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2003427, 4664504, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4614314, 5, { -0.059309f, -0.000001f, 15.090750f }, 1.000000f );
      instance->registerEObj( "Allaganterminal", 2003419, 4682784, 4, { -15.104980f, 0.572263f, -27.316570f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2003452, 4615853, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2003678, 4663755, 4, { 16.207529f, 0.571903f, 28.091551f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};