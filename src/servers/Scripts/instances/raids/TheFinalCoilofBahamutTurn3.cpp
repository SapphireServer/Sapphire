#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheFinalCoilofBahamutTurn3 : public InstanceContentScript
{
public:
   TheFinalCoilofBahamutTurn3() : InstanceContentScript( 30018 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "unknown_0", 2004611, 0, 4, { -7.491028f, -53.235149f, -153.215500f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "unknown_1", 2004610, 0, 4, { 22.322800f, -53.235241f, -154.775101f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "sgvf_w1b3_b0502", 2004627, 5009741, 4, { 0.000000f, -53.682961f, -160.000000f }, 1.000000f, 0.000000f ); 
      // States -> brr_off brr_on2off brr_on brr_off2on 
      instance->registerEObj( "unknown_2", 2004638, 0, 4, { -14.415940f, -53.682961f, -162.090302f }, 1.000000f, 0.000000f ); 
      instance->registerEObj( "Entrance", 2000182, 4895872, 5, { 0.005331f, -53.234989f, -140.846207f }, 1.000000f, 0.000000f ); 
      // States -> vf_lock_on vf_lock_of 
      instance->registerEObj( "Entrypoint", 2004650, 0, 4, { -0.019161f, -53.626511f, -182.364700f }, 1.000000f, 0.000000f ); 

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};