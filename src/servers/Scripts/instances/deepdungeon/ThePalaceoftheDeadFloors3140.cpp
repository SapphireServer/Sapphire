#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThePalaceoftheDeadFloors3140 : public InstanceContentScript
{
public:
   ThePalaceoftheDeadFloors3140() : InstanceContentScript( 60004 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "sgvf_w_lvd_b0959", 2000608, 6367892, 4, { -300.000000f, 0.000000f, -225.000000f }, 1.000000f, 0.000000f ); 
      // States -> vf_bextwall_on vf_bextwall_on2off vf_bextwall_off 
      instance->registerEObj( "sgvf_w_lvd_b0959_1", 2002872, 6392196, 4, { 300.000000f, 0.000000f, 374.000000f }, 1.000000f, 0.000000f ); 
      // States -> vf_bextwall_on vf_bextwall_on2off vf_bextwall_off 
      instance->registerEObj( "unknown_0", 2007351, 6277715, 4, { 300.036102f, 0.000000f, 373.916687f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_1", 2007352, 6394671, 4, { 307.159912f, 0.000000f, 370.556702f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_2", 2007353, 6394677, 4, { 305.303894f, 0.000000f, 380.231415f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_3", 2007354, 6394673, 4, { 296.024109f, -0.000000f, 381.100189f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_4", 2007355, 6394675, 4, { 291.561890f, 0.000000f, 372.412689f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_5", 2007356, 6394674, 4, { 298.511902f, 0.000000f, 366.134003f }, 1.000000f, 0.000000f ); 

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};