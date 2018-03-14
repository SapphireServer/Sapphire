#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class FlickingSticksandTakingNames : public InstanceContentScript
{
public:
   FlickingSticksandTakingNames() : InstanceContentScript( 10008 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f ); 

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};