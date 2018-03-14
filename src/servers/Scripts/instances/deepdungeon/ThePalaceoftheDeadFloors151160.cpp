#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThePalaceoftheDeadFloors151160 : public InstanceContentScript
{
public:
   ThePalaceoftheDeadFloors151160() : InstanceContentScript( 60016 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "sgvf_w_lvd_b0959", 2000608, 6534547, 4, { -301.179504f, 0.130118f, -301.014709f }, 1.000000f, -0.000000f ); 
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