#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AkhAfahAmphitheatreHard : public InstanceContentScript
{
public:
   AkhAfahAmphitheatreHard() : InstanceContentScript( 20024 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2004238, 4772738, 4, { -1.210436f, 0.000000f, -0.715586f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2004239, 4797573, 4, { 1.181316f, -0.000000f, 1.563968f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2004240, 4841629, 4, { 11.000000f, 0.000000f, -11.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2004349, 4841631, 4, { 12.811310f, -0.000000f, 9.376424f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2004350, 4841632, 4, { -8.033875f, 0.000000f, 10.406790f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2004351, 4841633, 4, { -8.319038f, -0.000001f, -10.997720f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4738599, 5, { 9.717670f, 0.000000f, 14.522430f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -15.000000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};