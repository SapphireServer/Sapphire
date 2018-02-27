#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheMinstrelsBalladUltimasBane : public InstanceContentScript
{
public:
   TheMinstrelsBalladUltimasBane() : InstanceContentScript( 20013 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002745, 4391076, 4, { 7.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002746, 4391074, 4, { -7.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002747, 4976890, 4, { 0.000000f, -0.131581f, -18.566719f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002748, 4391072, 4, { 17.676531f, -0.144861f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2002749, 4976892, 4, { 0.000000f, 0.000000f, 17.000000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002750, 4976891, 4, { -17.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4391941, 5, { -6.677185f, 0.068419f, 12.835030f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -16.316700f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};