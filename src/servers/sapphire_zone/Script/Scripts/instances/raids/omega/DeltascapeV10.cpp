#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class DeltascapeV10 : public InstanceContentScript
{
public:
   DeltascapeV10() : InstanceContentScript( 30049 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007457, 6791878, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007457, 6885561, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 6852121, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6910535, 5, { 0.000000f, 0.000000f, 15.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -16.000000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};