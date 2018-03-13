#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheBowlofEmbersHard : public InstanceContentScript
{
public:
   TheBowlofEmbersHard() : InstanceContentScript( 20004 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "Entrance", 2000182, 4177874, 5, { -16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
      // States -> vf_lock_on vf_lock_of 
      instance->registerEObj( "Exit", 2000139, 0, 4, { 16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_0", 2007452, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "BladeofLight", 2007454, 0, 4, { 0.000000f, 0.000000f, 11.300000f }, 0.991760f, 0.000048f ); 

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};