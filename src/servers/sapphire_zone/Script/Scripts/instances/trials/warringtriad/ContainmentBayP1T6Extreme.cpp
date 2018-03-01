#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ContainmentBayP1T6Extreme : public InstanceContentScript
{
public:
   ContainmentBayP1T6Extreme() : InstanceContentScript( 20042 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007340, 6383469, 4, { -0.194161f, 0.000000f, 3.451970f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007442, 6424145, 4, { -5.251681f, 0.000000f, -1.313751f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007443, 0, 4, { -4.046182f, 0.000000f, 3.618896f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007449, 0, 4, { 2.914429f, -0.015320f, -2.731445f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2007464, 0, 4, { -0.015320f, -0.015320f, -14.419800f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2002618, 6563705, 4, { 6.090889f, 0.000000f, -1.422338f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6392588, 5, { 0.132306f, 0.592461f, 10.611330f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.001971f, 0.000000f, -11.776730f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};