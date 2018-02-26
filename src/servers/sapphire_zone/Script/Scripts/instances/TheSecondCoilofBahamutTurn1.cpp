#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheSecondCoilofBahamutTurn1 : public InstanceContentScript
{
public:
   TheSecondCoilofBahamutTurn1() : InstanceContentScript( 30007 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2003012, 0, 4, { -266.882690f, 10.421330f, 43.491699f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2003043, 0, 4, { -261.309113f, 10.383500f, 37.739429f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2003044, 0, 4, { -259.553802f, 10.421330f, 31.442730f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2003045, 0, 4, { -262.154510f, 10.421330f, 23.808010f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4614306, 5, { -120.168602f, 11.010820f, -99.074913f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -131.611206f, 9.156082f, -82.660057f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2001269, 4544126, 4, { -137.669403f, 9.502172f, -11.353470f }, 1.000000f );
      instance->registerEObj( "Destination", 2002372, 4579467, 4, { -171.978897f, -49.907219f, -10.220380f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002872, 4616656, 4, { -248.873596f, 10.236450f, 33.155060f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2002735, 0, 4, { -246.919006f, 9.938496f, 34.239399f }, 1.000000f );
      instance->registerEObj( "Allaganterminal", 2003416, 4664435, 4, { -314.106995f, 9.414734f, 43.198238f }, 0.991760f );
      instance->registerEObj( "Unknown8", 2003421, 4651262, 4, { -292.780701f, 10.351920f, 39.414989f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2003428, 4615269, 4, { -120.556702f, 8.820233f, -76.764412f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};