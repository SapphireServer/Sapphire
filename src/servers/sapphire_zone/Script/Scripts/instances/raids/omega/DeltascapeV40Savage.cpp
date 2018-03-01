#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class DeltascapeV40Savage : public InstanceContentScript
{
public:
   DeltascapeV40Savage() : InstanceContentScript( 30056 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007457, 6925502, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007457, 6925503, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 6925504, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007457, 6936015, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007457, 6865650, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007457, 6872744, 4, { 0.000000f, 0.000000f, 0.038952f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2008483, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -17.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6914211, 5, { 0.000000f, 0.000000f, 15.000000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};