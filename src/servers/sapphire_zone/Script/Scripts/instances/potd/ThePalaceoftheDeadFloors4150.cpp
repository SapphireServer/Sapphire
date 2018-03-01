#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThePalaceoftheDeadFloors4150 : public InstanceContentScript
{
public:
   ThePalaceoftheDeadFloors4150() : InstanceContentScript( 60005 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2000608, 6367892, 4, { -300.000000f, 0.000000f, -225.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002872, 6392196, 4, { 300.000000f, 0.000000f, 374.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007351, 6277715, 4, { 300.036102f, 0.000000f, 373.916687f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007352, 6394671, 4, { 307.159912f, 0.000000f, 370.556702f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007353, 6394677, 4, { 305.303894f, 0.000000f, 380.231415f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007354, 6394673, 4, { 296.024109f, -0.000000f, 381.100189f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007355, 6394675, 4, { 291.561890f, 0.000000f, 372.412689f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007356, 6394674, 4, { 298.511902f, 0.000000f, 366.134003f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};