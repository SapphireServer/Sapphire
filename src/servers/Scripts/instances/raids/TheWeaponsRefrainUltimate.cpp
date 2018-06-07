#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheWeaponsRefrainUltimate : public InstanceContentScript
{
public:
   TheWeaponsRefrainUltimate() : InstanceContentScript( 30067 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "unknown_0", 2009480, 0, 4, { 94.011192f, 0.000000f, 107.700996f }, 1.000000f, 0.000000f );
      instance->registerEObj( "sgvf_w1fz_b1432", 2007457, 7372735, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f );
      instance->registerEObj( "unknown_1", 2007457, 7373056, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f );
      instance->registerEObj( "unknown_2", 2009481, 0, 4, { 101.695602f, 0.000000f, 101.959396f }, 1.000000f, 0.000000f );
      instance->registerEObj( "unknown_3", 2007457, 7237754, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f );
      instance->registerEObj( "unknown_4", 2007457, 7237753, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f );
      instance->registerEObj( "unknown_5", 2007457, 7237756, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f );
      instance->registerEObj( "unknown_6", 2007457, 7237755, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f );
      instance->registerEObj( "Entrance", 2007457, 7343478, 5, { 100.000000f, 0.000000f, 116.000000f }, 1.000000f, 0.000000f ); 
      // States -> vf_lock_on vf_lock_of 
      instance->registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f );
      instance->registerEObj( "unknown_7", 2007457, 7538258, 4, { 100.160004f, 0.000000f, 101.443398f }, 1.000000f, 0.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};