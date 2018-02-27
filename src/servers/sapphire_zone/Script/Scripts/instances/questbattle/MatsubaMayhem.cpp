#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class MatsubaMayhem : public InstanceContentScript
{
public:
   MatsubaMayhem() : InstanceContentScript( 5011 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2000608, 6538194, 4, { -27.571140f, -3.000000f, 46.619968f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2000608, 6538193, 4, { -28.307659f, 3.999977f, 61.762589f }, 1.000000f );
      instance->registerEObj( "ClanHuntboard", 2008655, 6422886, 4, { -31.520060f, 0.076252f, -43.853790f }, 0.991760f );
      instance->registerEObj( "Unknown2", 2002872, 6799085, 4, { -79.087517f, -3.006042f, 41.336670f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2002872, 6799087, 4, { -61.668732f, -3.014119f, 84.855003f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2007457, 6611234, 4, { 137.621094f, 14.816470f, 92.484863f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2007457, 6538193, 4, { -27.894131f, 3.999977f, 61.384491f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007457, 6538194, 4, { -28.259020f, -3.000000f, 46.489510f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};