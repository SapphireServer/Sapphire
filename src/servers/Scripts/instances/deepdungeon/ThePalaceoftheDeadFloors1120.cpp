#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThePalaceoftheDeadFloors1120 : public InstanceContentScript
{
public:
   ThePalaceoftheDeadFloors1120() : InstanceContentScript( 60002 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "sgvf_w_lvd_b0959", 2000608, 6353850, 4, { -300.000000f, 0.000026f, -237.000000f }, 1.000000f, 0.000000f ); 
      // States -> vf_bextwall_on vf_bextwall_on2off vf_bextwall_off 

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};