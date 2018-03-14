#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThornmarchHard : public InstanceContentScript
{
public:
   ThornmarchHard() : InstanceContentScript( 20011 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "Entrance", 2000182, 4377976, 5, { -5.269677f, 0.467326f, 14.257640f }, 1.000000f, 0.000000f ); 
      // States -> vf_lock_on vf_lock_of 
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.014298f, -0.000000f, -17.786249f }, 1.000000f, 0.000000f ); 

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};