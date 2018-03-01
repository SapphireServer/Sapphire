#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class SigmascapeV40 : public InstanceContentScript
{
public:
   SigmascapeV40() : InstanceContentScript( 30062 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007457, 7307403, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2008982, 0, 4, { -0.015320f, -0.015320f, -0.015320f }, 0.991760f );
      instance->registerEObj( "Unknown2", 2008978, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2008979, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2008980, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2008981, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2008976, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2008977, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007457, 7296769, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2000051, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2000052, 0, 4, { 0.000000f, 0.000000f, -5.000000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2008626, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2008627, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2008629, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2008630, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2006821, 0, 4, { -0.015320f, -0.015320f, -0.015320f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 7181990, 5, { 0.000000f, 0.000000f, 14.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -16.000000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};