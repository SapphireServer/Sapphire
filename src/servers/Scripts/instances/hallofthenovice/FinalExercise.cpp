#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class FinalExercise : public InstanceContentScript
{
public:
   FinalExercise() : InstanceContentScript( 15016 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "Entrance", 2000182, 6228959, 5, { 457.583801f, 5.680784f, 280.512787f }, 1.000000f, 0.000000f ); 
      // States -> vf_lock_on vf_lock_of 
      instance->registerEObj( "unknown_0", 2000608, 2807920, 4, { -95.322441f, -25.054260f, 61.518002f }, 1.000000f, 0.000000f ); 

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};